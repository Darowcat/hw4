#include"mbed.h"
#include "bbcar.h"

BufferedSerial pc(USBTX,USBRX); //tx,rx
BufferedSerial uart(D1,D0); //tx,rx
Ticker servo_ticker;
PwmOut pin5(D5), pin6(D6);
BBCar car(pin5, pin6, servo_ticker);

int pid = 0;
int i = 0;
bool m = false;

int main(){
   uart.set_baud(9600);
   while(1){
      
      if(uart.readable()){
         char recv[1];
         uart.read(recv, sizeof(recv));

         if (recv[0] != '\n'){
            pid = pid * 10 + atoi(recv);
         } else {
            printf("%d\n", pid);
            i = pid;
            pid = 0;
            /*if (i > 10){ //+l-r
               car.turn(40, 0.4);
            } else if (i > 2){
               car.turn(40, -0.4);
            } else {
               car.goStraight(40);
            }*/
            if (i > 2 && i < 40){
                car.turn(20, 0.4);
            } else if (i < 358 && i > 320){
                car.turn(20, -0.4);
            } else {
                car.goStraight(20);
            }
         }
      }
   }
}