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

struct Car no_Car;
no_Car.ID = 'X';
no_Car.currentLane = 'X';
no_Car.targetLane = 'X';

while (1) {

  if(currentlyPassingCar.ID == 'X'){

    currentlyPassingCar = car_P;
    vTaskDelay( 2000 / portTICK_PERIOD_MS ); // car takes 2 seconds to pass
    currentlyPassingCar = no_Car;

  } else {

    if(carsDontIntersect(currentlyPassingCar, car_P)){

      currentlyPassingCar = car_P;
      vTaskDelay( 2000 / portTICK_PERIOD_MS ); // car takes 2 seconds to pass
      currentlyPassingCar = no_Car;

    }

  }

}


*/







void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
