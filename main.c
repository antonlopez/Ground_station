#include "uart.h"
#include <math.h>
#include <stdio.h>
#include "pwm.h"

#define PWM_FREQUENCY 60
#define M_PI    3.14159265359
float Duty ;
uint8_t dataReceived[40];
float number;
uint8_t numberBytes[4];
char identifier;

char dataArray[40];

float pitchNum;
float rollNum;
char *pitch;
char *roll;

void delayMS(int ms);

int main(void) {

    // DEFINE PWM VARIABLES
    volatile uint32_t ui32Load; // Load count for PWM counter
    volatile uint32_t ui32PWMClock; // PWM Clock
     float Roll; // Adjust parameter for PWM1 period
     float Pitch; // Adjust parameter for PWM2 period
     uint16_t dutyRoll = 495;
     uint16_t dutyPitch=30;

    
    // SET SYSTEM CLOCK AT 80MHz
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    
    // SET PWM CLOCK
    ui32PWMClock = SysCtlClockGet() / 64;
    ui32Load = (ui32PWMClock / PWM_FREQUENCY) - 1;

    // INITIALIZE COMMUNICATIONS MODULES
    UART_XbeeInit(115200);
    //UART_BluetoothInit(115200);

    // INITIALIZE PWM
    PwmConfig(ui32Load, dutyRoll, dutyPitch);
    
    //UART_XBeeWriteString("Hello from XBee\n");
    // UART_XBeeWriteUint(12674);
    // UART_XBeeWriteFloat(3.1415);
    while(1){
        UART_XBeeRead(dataReceived, sizeof(dataReceived));
        memcpy(&dataArray,&dataReceived, sizeof(dataReceived));
        pitch = strtok(dataArray, " "); // split data where there is a space, pitch angle is before space
        pitchNum = atof(pitch); // convert pitch angle to a number

        roll = strtok(NULL, "\n"); // split data where there's a new line to take out roll angle
        rollNum = atof(roll); // convert roll angle to a number


        Roll= 10.98 * rollNum  + 504.9;
        Pitch = .26* pitchNum + 18.2;

        dutyRoll = (uint16_t) Roll;
        dutyPitch = (uint16_t) Pitch;


        if ( dutyRoll < 10) {
           dutyRoll = 10;
        }
        if ( dutyRoll > 999) {
           dutyRoll = 999;
              }

        if ( dutyPitch < 10) {
           dutyPitch = 10;
              }
        if ( dutyPitch > 26) {
           dutyPitch = 26;
                    }



        PWMDCSet (ui32Load, dutyRoll, dutyPitch);

        delayMS(20);



    }

}



void delayMS(int ms){
    SysCtlDelay((SysCtlClockGet()/(3*1000))*ms );

}















