#include "uart.h"
#include <math.h>
#include <stdio.h>
#include "pwm.h"

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




void float2Bytes(float val,uint8_t* bytes_array);
void UART_XBeeWriteBytes(uint8_t *data, uint32_t size);

int main(void) {

    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    UART_XbeeInit(115200);
    UART_BluetoothInit(115200);





    //UART_XBeeWriteString("Hello from XBee\n");
   // UART_XBeeWriteUint(12674);
   // UART_XBeeWriteFloat(3.1415);




        while(1){





            UART_XBeeRead(dataReceived, sizeof(dataReceived));


            memcpy(&dataArray,&dataReceived, sizeof(dataReceived));

            roll = strtok(dataArray, " "); // split data where there is a space, pitch angle is before space
            rollNum = atof(roll); // convert pitch angle to a number


            pitch = strtok(NULL, "\n"); // split data where there's a new line to take out roll angle
            pitchNum = atof(pitch); // convert roll angle to a number
























        }








}

















