#include <Arduino_FreeRTOS.h>
#include <queue.h>


/*

=============================
Algorithm
=============================

- repeat

    - if there is no currently passing car, then let this car pass

    - else
      
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

  xTaskCreate(

    Car_P,
    "Car P",
    128,
    NULL,
    1,
    NULL

  );

  // xTaskCreate(

  //   Car_Q,
  //   "Car Q",
  //   128,
  //   NULL,
  //   2,
  //   NULL

  // );

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


bool carsDontIntersect(struct Car currentlyPassingCar, struct Car thisCar){

  return false;

}


void Car_P(void *pvParameters) {

  (void) pvParameters;

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

    xQueueReceive(structQueue, &currentlyPassingCar, portMAX_DELAY);  // get up-to-date contents of currently passing car


      if(currentlyPassingCar.ID == 'X'){

      Serial.println("Car P is passing ... \n");
      currentlyPassingCar = car_P;
      xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);
      vTaskDelay( 2000 / portTICK_PERIOD_MS ); // car takes 2 seconds to pass
      currentlyPassingCar = no_Car;
      xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);
      Serial.println("Car P has passed. \n");

      } else {

        if(carsDontIntersect(currentlyPassingCar, car_P)){

          currentlyPassingCar = car_P;
          xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);
          vTaskDelay( 2000 / portTICK_PERIOD_MS ); // car takes 2 seconds to pass
          currentlyPassingCar = no_Car;
          xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);

        }

      }

  }

}



void Car_Q(void *pvParameters) {

  (void) pvParameters;

  struct Car car_Q;
  car_Q.ID = 'P';
  car_Q.currentLane = 'A';
  car_Q.targetLane = 'B';

  struct Car currentlyPassingCar;

  struct Car no_Car;
  no_Car.ID = 'X';
  no_Car.currentLane = 'X';
  no_Car.targetLane = 'X';

  while (1) {

    xQueueReceive(structQueue, &currentlyPassingCar, portMAX_DELAY);  // get up-to-date contents of currently passing car

      if(currentlyPassingCar.ID == 'X'){

      currentlyPassingCar = car_Q;
      xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);
      vTaskDelay( 2000 / portTICK_PERIOD_MS ); // car takes 2 seconds to pass
      currentlyPassingCar = no_Car;
      xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);

      } else {

        if(carsDontIntersect(currentlyPassingCar, car_Q)){

          currentlyPassingCar = car_Q;
          xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);
          vTaskDelay( 2000 / portTICK_PERIOD_MS ); // car takes 2 seconds to pass
          currentlyPassingCar = no_Car;
          xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);

        }

      }

  }

}

void Car_R(void *pvParameters) {

  (void) pvParameters;

  struct Car car_R;
  car_R.ID = 'P';
  car_R.currentLane = 'A';
  car_R.targetLane = 'B';

  struct Car currentlyPassingCar;

  struct Car no_Car;
  no_Car.ID = 'X';
  no_Car.currentLane = 'X';
  no_Car.targetLane = 'X';

  while (1) {

    xQueueReceive(structQueue, &currentlyPassingCar, portMAX_DELAY); // get up-to-date contents of currently passing car

      if(currentlyPassingCar.ID == 'X'){

      currentlyPassingCar = car_R;
      xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);
      vTaskDelay( 2000 / portTICK_PERIOD_MS ); // car takes 2 seconds to pass
      currentlyPassingCar = no_Car;
      xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);

      } else {

        if(carsDontIntersect(currentlyPassingCar, car_R)){

          currentlyPassingCar = car_R;
          xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);
          vTaskDelay( 2000 / portTICK_PERIOD_MS ); // car takes 2 seconds to pass
          currentlyPassingCar = no_Car;
          xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);

        }

      }

  }

}


void Car_S(void *pvParameters) {

  (void) pvParameters;

  struct Car car_S;
  car_S.ID = 'P';
  car_S.currentLane = 'A';
  car_S.targetLane = 'B';

  struct Car currentlyPassingCar;

  struct Car no_Car;
  no_Car.ID = 'X';
  no_Car.currentLane = 'X';
  no_Car.targetLane = 'X';

  while (1) {

    xQueueReceive(structQueue, &currentlyPassingCar, portMAX_DELAY); // get up-to-date contents of currently passing car

      if(currentlyPassingCar.ID == 'X'){

      currentlyPassingCar = car_S;
      xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);
      vTaskDelay( 2000 / portTICK_PERIOD_MS ); // car takes 2 seconds to pass
      currentlyPassingCar = no_Car;
      xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);

      } else {

        if(carsDontIntersect(currentlyPassingCar, car_S)){

          currentlyPassingCar = car_S;
          xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);
          vTaskDelay( 2000 / portTICK_PERIOD_MS ); // car takes 2 seconds to pass
          currentlyPassingCar = no_Car;
          xQueueSend(structQueue, &currentlyPassingCar, portMAX_DELAY);

        }

      }
    
  }

}
