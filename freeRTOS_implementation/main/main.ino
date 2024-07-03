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


=============================
Task structure
=============================


We have 4 tasks called, Car_P, Car_Q, Car_R, and Car_S

Each of these tasks would follow the following code pattern, taking an example of car P:

struct Car car_P;
car_P.ID = 'P';
car_P.currentLane = 'A';
car_P.targetLane = 'B';

struct Car currentlyPassingCar;

struct Car no_Car;
no_Car.ID = 'X';
no_Car.currentLane = 'X';
no_Car.targetLane = 'X';

while (1) {

  xQueueReceive(structQueue, &currentlyPassingCar, portMAX_DELAY) // get up-to-date contents of currently passing car

  if(currentlyPassingCar.ID == 'X'){

    // letting this car pass
    currentlyPassingCar = car_P;
    xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY)
    vTaskDelay( 2000 / portTICK_PERIOD_MS ); // car takes 2 seconds to pass
    currentlyPassingCar = no_Car;
    xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY)

  } else {

    if(carsDontIntersect(currentlyPassingCar, car_P)){

      currentlyPassingCar = car_P;
      xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY)
      vTaskDelay( 2000 / portTICK_PERIOD_MS ); // car takes 2 seconds to pass
      currentlyPassingCar = no_Car;
      xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY)

    }

  }

}


*/

struct Car {

  char ID;
  int currentLane;
  int targetLane;

};


QueueHandle_t structQueue;


void setup() {

  Serial.begin(9600);
  
  structQueue = xQueueCreate(8, sizeof(struct Car));

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

  xTaskCreate(

    Car_R,
    "Car R",
    128,
    NULL,
    1,
    NULL

  );
Serial.println("Car R task created\n");
  // xTaskCreate(

  //   Car_S,
  //   "Car S",
  //   128,
  //   NULL,
  //   2,
  //   NULL

  // );
// Serial.println("Car S task created\n");
}

void loop() {}
int directions_matrix[4][4][4]={
  {{0},{2},{2,3},{2,3,4}},
  {{3,4,1},{0},{3},{3,4}},
  {{4,1},{4,1,2},{0},{4}},
  {{1},{1,2},{1,2,3},{0}}
};
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
  for(int i =0;i<4;i++){
    CurrentCarLanesList[3-i]=currentlyPassingCarLanes/pow(10,3-i);
    currentlyPassingCarLanes=currentlyPassingCarLanes%(int)(round(pow(10,3-i)));
  }
  int thisCarLanesList[4]={0,0,0,0};
  for(int i =0;i<4;i++){
    thisCarLanesList[3-i]=thisCarLanes/pow(10,3-i);
    thisCarLanes=thisCarLanes%(int)(round(pow(10,3-i)));
  } 
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


void Car_P(void *pvParameters) {

  (void) pvParameters;

  struct Car car_P;
  car_P.ID = 'P';
  car_P.currentLane = 1;
  car_P.targetLane = 2;

  Serial.println("Initizalized car P\n");

  struct Car currentlyPassingCar;

  struct Car no_Car;
  no_Car.ID = 'X';
  no_Car.currentLane = 0;
  no_Car.targetLane = 0;

  // currentlyPassingCar = no_Car;
  // xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);

  while (1) {

    xQueueReceive(structQueue, &currentlyPassingCar, portMAX_DELAY);  // get up-to-date contents of currently passing car

      int currentlyPassingCarBlockedLanes=getBlockedLanes(currentlyPassingCar.currentLane,currentlyPassingCar.targetLane);
      Serial.print("car P checked currently passing car is ");
      Serial.print(currentlyPassingCar.ID);
      Serial.print("\n");
      Serial.print("currently passing car occupying lanes ");
      Serial.print(currentlyPassingCarBlockedLanes);
      Serial.print("\n");
      int car_pBlockedLanesget=getBlockedLanes(car_P.currentLane,car_P.targetLane);
      Serial.print("car p occupying lanes ");
      Serial.print(car_pBlockedLanesget);
      Serial.print("\n");
      if(currentlyPassingCar.ID == 'X' || carsDontIntersect(currentlyPassingCarBlockedLanes,car_pBlockedLanesget )){

        Serial.println("Car P is passing ... \n");
        currentlyPassingCar = car_P;
        xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);
        vTaskDelay( 2000 / portTICK_PERIOD_MS ); // car takes 2 seconds to pass
        Serial.println("Car P has passed. \n");
        currentlyPassingCar = no_Car;
        xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);
        vTaskDelay( 1000 / portTICK_PERIOD_MS ); // car takes 2 seconds to pass
        

      } 

    }

}


void Car_Q(void *pvParameters) {


  (void) pvParameters;

  struct Car car_Q;
  car_Q.ID = 'Q';
  car_Q.currentLane = 3;
  car_Q.targetLane = 4;

  Serial.println("Initizalized car Q\n");

  struct Car currentlyPassingCar;
  struct Car peekedCar;
  struct Car no_Car;
  no_Car.ID = 'X';
  no_Car.currentLane = 0;
  no_Car.targetLane = 0;
  Serial.print("set car to none \n");
  currentlyPassingCar = no_Car;
  xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);

  while (1) {

    xQueueReceive(structQueue, &currentlyPassingCar, portMAX_DELAY);  // get up-to-date contents of currently passing car
      int currentlyPassingCarBlockedLanes=getBlockedLanes(currentlyPassingCar.currentLane,currentlyPassingCar.targetLane);
      Serial.print("car Q checked currently passing car is ");
      Serial.print(currentlyPassingCar.ID);
      Serial.print("\n");
      Serial.print("currently passing car occupying lanes ");
      Serial.print(currentlyPassingCarBlockedLanes);
      Serial.print("\n");
      int car_QBlockedLanesget=getBlockedLanes(car_Q.currentLane,car_Q.targetLane);
      Serial.print("car Q occupying lanes ");
      Serial.print(car_QBlockedLanesget);
      Serial.print("\n");
      
      if(currentlyPassingCar.ID == 'X' || carsDontIntersect(currentlyPassingCarBlockedLanes,car_QBlockedLanesget)){

        Serial.println("Car Q is passing ... \n");
        currentlyPassingCar = car_Q;
        xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);
        vTaskDelay( 2000 / portTICK_PERIOD_MS ); // car takes 2 seconds to pass
        Serial.println("Car Q has passed. \n");
        currentlyPassingCar = no_Car;
        xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);
        vTaskDelay( 1000 / portTICK_PERIOD_MS ); // car takes 2 seconds to pass

      } 

    }

  }

void Car_R(void *pvParameters) {
// Serial.print("car r is running");
  (void) pvParameters;

  struct Car car_R;
  car_R.ID = 'R';
  car_R.currentLane = 4;
  car_R.targetLane = 2;

  Serial.println("Initizalized car R\n");

  struct Car currentlyPassingCar;
  struct Car peekedCar;
  struct Car no_Car;
  no_Car.ID = 'X';
  no_Car.currentLane = 0;
  no_Car.targetLane = 0;
  Serial.print("set car to none \n");
  currentlyPassingCar = no_Car;
  xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);

  while (1) {

    xQueueReceive(structQueue, &currentlyPassingCar, portMAX_DELAY);  // get up-to-date contents of currently passing car
      int currentlyPassingCarBlockedLanes=getBlockedLanes(currentlyPassingCar.currentLane,currentlyPassingCar.targetLane);
      Serial.print("car R checked currently passing car is ");
      Serial.print(currentlyPassingCar.ID);
      Serial.print("\n");
      Serial.print("currently passing car occupying lanes ");
      Serial.print(currentlyPassingCarBlockedLanes);
      Serial.print("\n");
      int car_RBlockedLanesget=getBlockedLanes(car_R.currentLane,car_R.targetLane);
      Serial.print("car R occupying lanes ");
      Serial.print(car_RBlockedLanesget);
      Serial.print("\n");
      
      if(currentlyPassingCar.ID == 'X' || carsDontIntersect(currentlyPassingCarBlockedLanes,car_RBlockedLanesget)){

        Serial.println("Car R is passing ... \n");
        currentlyPassingCar = car_R;
        xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);
        vTaskDelay( 2000 / portTICK_PERIOD_MS ); // car takes 2 seconds to pass
        Serial.println("Car R has passed. \n");
        currentlyPassingCar = no_Car;
        xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);
        vTaskDelay( 1000 / portTICK_PERIOD_MS ); // car takes 2 seconds to pass

      } 

    }

  }

// void Car_S(void *pvParameters) {
//   Serial.print("car s is running");

  // (void) pvParameters;

  // struct Car car_S;
  // car_S.ID = 'S';
  // car_S.currentLane = 0;
  // car_S.targetLane = 0;

  // Serial.println("Initizalized car S\n");

  // struct Car currentlyPassingCar;

  // struct Car no_Car;
  // no_Car.ID = 'X';
  // no_Car.currentLane = 0;
  // no_Car.targetLane = 0;

  // currentlyPassingCar = no_Car;
  // xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);

  // while (1) {

  //   xQueueReceive(structQueue, &currentlyPassingCar, portMAX_DELAY);  // get up-to-date contents of currently passing car

  //     if(currentlyPassingCar.ID == 'X' || carsDontIntersect(&currentlyPassingCar, &car_S)){

  //       Serial.println("Car S is passing ... \n");
  //       currentlyPassingCar = car_S;
  //       xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);
  //       vTaskDelay( 3800 / portTICK_PERIOD_MS ); // car takes 2 seconds to pass
  //       currentlyPassingCar = no_Car;
  //       xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);
  //       Serial.println("Car S has passed. \n");

  //     } 

  //   }

  // }


