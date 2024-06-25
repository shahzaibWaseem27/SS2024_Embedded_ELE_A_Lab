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
  char currentLane;
  char targetLane;

};


QueueHandle_t structQueue;


void setup() {

  Serial.begin(9600);
  
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

  // xTaskCreate(

  //   Car_R,
  //   "Car R",
  //   128,
  //   NULL,
  //   2,
  //   NULL

  // );

  // xTaskCreate(

  //   Car_S,
  //   "Car S",
  //   128,
  //   NULL,
  //   3,
  //   NULL

  // );

}

void loop() {}


bool carsDontIntersect(struct Car *currentlyPassingCar, struct Car *thisCar){

  // to do

  //if currentlyPassingCar.currentlLane == 'A' && thisCar.currentlLane == 'B' return true

  // currentCarBlockedLanes = checkBlock(currentlyPassingCar);
  //         car_P_blockedLanes =[1,2]
  //         for (int i =0;i<4;i++){
  //           for(int j =0;j<4;j++){
  //             if(currentCarBlockedLanes[i]==car_P_blockedLanes[j]){
  //               canPass=false;
  //             }
  //           }
  //         }

  return false;

}


void Car_P(void *pvParameters) {

  (void) pvParameters;

  struct Car car_P;
  car_P.ID = 'P';
  car_P.currentLane = 'A';
  car_P.targetLane = 'B';

  Serial.println("Initizalized car P\n");

  struct Car currentlyPassingCar;

  struct Car no_Car;
  no_Car.ID = 'X';
  no_Car.currentLane = 'X';
  no_Car.targetLane = 'X';

  currentlyPassingCar = no_Car;
  xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);

  while (1) {

    xQueueReceive(structQueue, &currentlyPassingCar, portMAX_DELAY);  // get up-to-date contents of currently passing car


      if(currentlyPassingCar.ID == 'X' || carsDontIntersect(&currentlyPassingCar, &car_P)){

        Serial.println("Car P is passing ... \n");
        currentlyPassingCar = car_P;
        xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);
        vTaskDelay( 2000 / portTICK_PERIOD_MS ); // car takes 2 seconds to pass
        currentlyPassingCar = no_Car;
        xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);
        Serial.println("Car P has passed. \n");

      } 

    }

  }

}



void Car_Q(void *pvParameters) {

  (void) pvParameters;

  struct Car car_Q;
  car_Q.ID = 'Q';
  car_Q.currentLane = 'A';
  car_Q.targetLane = 'B';

  Serial.println("Initizalized car Q\n");

  struct Car currentlyPassingCar;

  struct Car no_Car;
  no_Car.ID = 'X';
  no_Car.currentLane = 'X';
  no_Car.targetLane = 'X';

  currentlyPassingCar = no_Car;
  xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);

  while (1) {

    xQueueReceive(structQueue, &currentlyPassingCar, portMAX_DELAY);  // get up-to-date contents of currently passing car

      if(currentlyPassingCar.ID == 'X' || carsDontIntersect(&currentlyPassingCar, &car_Q)){

        Serial.println("Car Q is passing ... \n");
        currentlyPassingCar = car_Q;
        xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);
        vTaskDelay( 3000 / portTICK_PERIOD_MS ); // car takes 2 seconds to pass
        currentlyPassingCar = no_Car;
        xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);
        Serial.println("Car Q has passed. \n");

      } 

    }

  }

}

void Car_R(void *pvParameters) {

  (void) pvParameters;

  struct Car car_R;
  car_R.ID = 'R';
  car_R.currentLane = 'A';
  car_R.targetLane = 'B';

  Serial.println("Initizalized car R\n");

  struct Car currentlyPassingCar;

  struct Car no_Car;
  no_Car.ID = 'X';
  no_Car.currentLane = 'X';
  no_Car.targetLane = 'X';

  currentlyPassingCar = no_Car;
  xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);

  while (1) {

    xQueueReceive(structQueue, &currentlyPassingCar, portMAX_DELAY);  // get up-to-date contents of currently passing car

      if(currentlyPassingCar.ID == 'X' || carsDontIntersect(&currentlyPassingCar, &car_R)){

        Serial.println("Car R is passing ... \n");
        currentlyPassingCar = car_R;
        xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);
        vTaskDelay( 3500 / portTICK_PERIOD_MS ); // car takes 2 seconds to pass
        currentlyPassingCar = no_Car;
        xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);
        Serial.println("Car R has passed. \n");

      } 

    }

  }

  }

}


void Car_S(void *pvParameters) {

  (void) pvParameters;

  struct Car car_S;
  car_S.ID = 'S';
  car_S.currentLane = 'A';
  car_S.targetLane = 'B';

  Serial.println("Initizalized car S\n");

  struct Car currentlyPassingCar;

  struct Car no_Car;
  no_Car.ID = 'X';
  no_Car.currentLane = 'X';
  no_Car.targetLane = 'X';

  currentlyPassingCar = no_Car;
  xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);

  while (1) {

    xQueueReceive(structQueue, &currentlyPassingCar, portMAX_DELAY);  // get up-to-date contents of currently passing car

      if(currentlyPassingCar.ID == 'X' || carsDontIntersect(&currentlyPassingCar, &car_S)){

        Serial.println("Car S is passing ... \n");
        currentlyPassingCar = car_S;
        xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);
        vTaskDelay( 3800 / portTICK_PERIOD_MS ); // car takes 2 seconds to pass
        currentlyPassingCar = no_Car;
        xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);
        Serial.println("Car S has passed. \n");

      } 

    }

  }

}
