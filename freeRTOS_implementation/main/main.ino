#include <Arduino_FreeRTOS.h>
#include <queue.h>


/*

=============================
Algorithm
=============================

- repeat

    - if there is no currently passing car, then let this car pass
      
    - if the trajectories of the currently passing car
      and that of this car don't intersect, then let this car pass


*/

// a Car structure that contains a unique ID, the lane it currently travels on, and the target lane it wishes to merge into

struct Car {

  char ID;
  int currentLane;
  int targetLane;

};

// a handle to interface with a queue

QueueHandle_t structQueue;

int currentlyPassingCarBlockedLanes;
int thisCarBlockedLanes;

void setup() {

  Serial.begin(9600);
  
  // create a queue for the cars to communicate when any one of them passes
  // the intersection area, and to check which car is currently passing

  structQueue = xQueueCreate(4, sizeof(struct Car));

  Serial.println("Queue created\n");

  xTaskCreate(

    Car_P,
    "Car P",
    128,
    NULL,
    1,
    NULL

  );

  Serial.println("Car P task created\n");

  xTaskCreate(

    Car_Q,
    "Car Q",
    128,
    NULL,
    1,
    NULL

  );

  Serial.println("Car Q task created\n");

}

void loop() {}

// matrix containing conflict information
int directions_matrix[4][4][4]={
  {{0},{2},{2,3},{2,3,4}},
  {{3,4,1},{0},{3},{3,4}},
  {{4,1},{4,1,2},{0},{4}},
  {{1},{1,2},{1,2,3},{0}}
};
//return a int containing digits representing lanes blocked by the given car source and targer
int getBlockedLanes(int target,int destination){
  if (target==0||destination==0){return 0;}
  float blocked=0;
  for (int i = 0; i < 4; i++) {
    int x=directions_matrix[target-1][destination-1][i];
    blocked=blocked+x*pow(10,i); 
  }
  return (int)(round(blocked));
}
bool carsDontIntersect(int currentlyPassingCarLanes, int thisCarLanes){
  int CurrentCarLanesList[4]={0,0,0,0};
  //turns given int back into arrays
  for(int i =0;i<4;i++){
    CurrentCarLanesList[3-i]=currentlyPassingCarLanes/pow(10,3-i);
    currentlyPassingCarLanes=currentlyPassingCarLanes%(int)(round(pow(10,3-i)));
  }
  int thisCarLanesList[4]={0,0,0,0};
  for(int i =0;i<4;i++){
    thisCarLanesList[3-i]=thisCarLanes/pow(10,3-i);
    thisCarLanes=thisCarLanes%(int)(round(pow(10,3-i)));
  } 
  // loops both arrays searching for matches
  for(int i=0;i<4;i++){
    for(int j =0;j<4;j++){
      if(CurrentCarLanesList[i]==thisCarLanesList[j]&&thisCarLanesList[j]!=0){
        Serial.print("found conflict \n");
        return false;
      }
    }
  }
  Serial.print("found no conflict\n");
  return true ;
}


void handleCarCheckingBlockedLanes(struct Car* currentlyPassingCar, struct Car* thisCar){

  currentlyPassingCarBlockedLanes=getBlockedLanes(currentlyPassingCar->currentLane,currentlyPassingCar->targetLane);

  switch(thisCar->ID){

    case 'P':

      Serial.print("car P checked currently passing car is ");
      break;

    case 'Q':

      Serial.print("car Q checked currently passing car is ");
      break;

  }

 
  Serial.print(currentlyPassingCar->ID);
  Serial.print("\n");
  Serial.print("currently passing car occupying lanes ");
  Serial.print(currentlyPassingCarBlockedLanes);
  Serial.print("\n");


  thisCarBlockedLanes =getBlockedLanes(thisCar->currentLane,thisCar->targetLane);


  switch(thisCar->ID){

    case 'P':

      Serial.print("car P blocks the following lanes: ");
      break;

    case 'Q':

      Serial.print("car Q blocks the following lanes: ");
      break;

  }

  Serial.print(thisCarBlockedLanes);
  Serial.print("\n");

}

void Car_P(void *pvParameters) {

  (void) pvParameters;

  // initialize car P attributes

  struct Car car_P;
  car_P.ID = 'P';
  car_P.currentLane = 1;
  car_P.targetLane = 2;

  Serial.println("Initizalized car P\n");


  // create an empty struct which would be filled with
  // information about currently passing car from the queue

  struct Car currentlyPassingCar;

  // create a car structure to represent that the lane is free
  // makes it easier to reset lane back to free

  struct Car no_Car;
  no_Car.ID = 'X';
  no_Car.currentLane = 0;
  no_Car.targetLane = 0;

  // currentlyPassingCar = no_Car;
  // xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);

  while (1) {

    // get up-to-date contents of currently passing car, and store in
    // local struct currentlyPassingCar

    xQueueReceive(structQueue, &currentlyPassingCar, portMAX_DELAY);

      // prints the blocking lanes of currently passing car, and car P

      handleCarCheckingBlockedLanes(&currentlyPassingCar, &car_P);  

      // if lanes are free, or if the currently passing car's path doesn't intersect with car P's path
      if(currentlyPassingCar.ID == 'X' || carsDontIntersect(currentlyPassingCarBlockedLanes,thisCarBlockedLanes)){

        Serial.println("Car P is passing ... \n");

        // set currently passing car to car P
        currentlyPassingCar = car_P;

        // send currentlyPassingCar's contents to the queue for the other car to receive and work with up-to-date knowledge
        xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);

        vTaskDelay( 2000 / portTICK_PERIOD_MS ); // car takes 2 seconds to pass
        Serial.println("Car P has passed. \n");

        // reset currently passing car back to being free
        currentlyPassingCar = no_Car;
        
        // send currentlyPassingCar's contents to the queue for the other car to receive and work with up-to-date knowledge
        xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);


        // delay to avoid this car immediately checking if lane is free which could cause the other car to starve
        vTaskDelay( 1000 / portTICK_PERIOD_MS );
        

      } 

    }

}


void Car_Q(void *pvParameters) {


  (void) pvParameters;

  // initialize car Q attributes

  struct Car car_Q;
  car_Q.ID = 'Q';
  car_Q.currentLane = 3;
  car_Q.targetLane = 4;

  Serial.println("Initizalized car Q\n");

  // create an empty struct which would be filled with
  // information about currently passing car from the queue

  struct Car currentlyPassingCar;

  // create a car structure to represent that the lane is free
  // makes it easier to reset lane back to free

  struct Car no_Car;
  no_Car.ID = 'X';
  no_Car.currentLane = 0;
  no_Car.targetLane = 0;

  // initialize lanes as free once

  currentlyPassingCar = no_Car;
  xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);

  while (1) {
    
    // get up-to-date contents of currently passing car, and store in
    // local struct currentlyPassingCar

    xQueueReceive(structQueue, &currentlyPassingCar, portMAX_DELAY);
      
      // prints the blocking lanes of currently passing car, and car Q

      handleCarCheckingBlockedLanes(&currentlyPassingCar, &car_Q);
      
      // if lanes are free, or if the currently passing car's path doesn't intersect with car Q's path
      if(currentlyPassingCar.ID == 'X' || carsDontIntersect(currentlyPassingCarBlockedLanes,thisCarBlockedLanes)){

        Serial.println("Car Q is passing ... \n");

        // set currently passing car to car Q
        currentlyPassingCar = car_Q;

        // send currentlyPassingCar's contents to the queue for the other car to receive and work with up-to-date knowledge
        xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);

        vTaskDelay( 2000 / portTICK_PERIOD_MS ); // car takes 2 seconds to pass
        Serial.println("Car Q has passed. \n");

        // reset currently passing car back to being free
        currentlyPassingCar = no_Car;

        // send currentlyPassingCar's contents to the queue for the other car to receive and work with up-to-date knowledge
        xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);

        // delay to avoid this car immediately checking if lane is free which could cause the other car to starve
        vTaskDelay( 1000 / portTICK_PERIOD_MS );

      } 

    }

  }

