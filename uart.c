#include "uart.h"
#include "buffer.h"

Buffer RX_Buffer;
uint8_t RX_Data[RX_BUFFER_SIZE];



void UART_XbeeInit(uint32_t baud_rate){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    GPIOPinConfigure(GPIO_PC6_U3RX);                // Connected to DOUT XBEE --> PC6
    GPIOPinConfigure(GPIO_PC7_U3TX);                // Connected to DIN XBEE  --> PC7
    GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_6 | GPIO_PIN_7);



    UARTConfigSetExpClk(UART3_BASE, SysCtlClockGet(), baud_rate,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));


    IntMasterEnable();
    IntEnable(INT_UART3);
    UARTIntEnable(UART3_BASE, UART_INT_RX | UART_INT_RT);
    Buffer_Init(&RX_Buffer, RX_Data, RX_BUFFER_SIZE);
}



void UART_BluetoothInit(uint32_t baud_rate){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinConfigure(GPIO_PB0_U1RX);
    GPIOPinConfigure(GPIO_PB1_U1TX);
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);



    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), baud_rate,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));


    IntMasterEnable();
    IntEnable(INT_UART1);
    UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT);
    Buffer_Init(&RX_Buffer, RX_Data, RX_BUFFER_SIZE);
}




/*
void UART_ConsoleInit(uint32_t baud_rate){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTStdioConfig(0, baud_rate, 16000000);
}
*/



void UART_XBeeWriteBytes(uint8_t *data, uint32_t size){
    uint32_t i;
    for(i = 0; i < size; i++){
        UARTCharPut(UART3_BASE, data[i]);
    }
}

void UART_BluetoothWriteBytes(uint8_t *data, uint32_t size){
    uint32_t i;
    for(i = 0; i < size; i++){
        UARTCharPut(UART1_BASE, data[i]);
    }
}



void UART_XBeeWriteString(const char *string){
    while(*string){
        UARTCharPut(UART3_BASE, *string++);
    }
}


void UART_BluetoothWriteString(const char *string){
    while(*string){
        UARTCharPut(UART1_BASE, *string++);
    }
}



void UART_XBeeWriteFloat(const float fp){
    union{
        float value;
        uint8_t bytes[sizeof(float)];
    }FloatBytes;

    FloatBytes.value = fp;
    UART_XBeeWriteBytes(FloatBytes.bytes, sizeof(float));
}

void UART_BluetoothWriteFloat(const float fp){
    union{
        float value;
        uint8_t bytes[sizeof(float)];
    }FloatBytes;

    FloatBytes.value = fp;
    UART_BluetoothWriteBytes(FloatBytes.bytes, sizeof(float));
}



void UART_XBeeWriteUint(const uint32_t uint){
    uint8_t bytes[4];

    bytes[0] = (uint >> 24) & 0xFF;
    bytes[1] = (uint >> 16) & 0xFF;
    bytes[2] = (uint >> 8) & 0xFF;
    bytes[3] =  uint & 0xFF;

    UART_XBeeWriteBytes(bytes, 4);
}



void UART_BluetoothWriteUint(const uint32_t uint){
    uint8_t bytes[4];

    bytes[0] = (uint >> 24) & 0xFF;
    bytes[1] = (uint >> 16) & 0xFF;
    bytes[2] = (uint >> 8) & 0xFF;
    bytes[3] =  uint & 0xFF;

    UART_BluetoothWriteBytes(bytes, 4);
}


void UART_XBeeRead(uint8_t *data, uint32_t size){
    Buffer_Read(&RX_Buffer, data, size);
}

void UART_BluetoothRead(uint8_t *data, uint32_t size){
    Buffer_Read(&RX_Buffer, data, size);
}




void UART_XbeeInt(void){
    int8_t cChar;
    uint32_t i32Char;
    uint32_t ui32Status;

    ui32Status = UARTIntStatus(UART3_BASE, true);
    UARTIntClear(UART3_BASE, ui32Status);

    if(ui32Status & (UART_INT_RX | UART_INT_RT)){
        /*Store received data in the receive buffer*/
        while(UARTCharsAvail(UART3_BASE)){
            i32Char = UARTCharGetNonBlocking(UART3_BASE);
            cChar = (unsigned char)(i32Char & 0xFF);
            Buffer_Write(&RX_Buffer, (uint8_t*)&cChar, 1);
            /*echo received character*/
          //  UART_BluetoothWriteBytes((uint8_t*)&cChar, 1);
        }
    }
}




void UART_BluetoothInt(void){
    int8_t cChar;
    uint32_t i32Char;
    uint32_t ui32Status;

    ui32Status = UARTIntStatus(UART1_BASE, true);
    UARTIntClear(UART1_BASE, ui32Status);

    if(ui32Status & (UART_INT_RX | UART_INT_RT)){
        /*Store received data in the receive buffer*/
        while(UARTCharsAvail(UART1_BASE)){
            i32Char = UARTCharGetNonBlocking(UART1_BASE);
            cChar = (unsigned char)(i32Char & 0xFF);
            Buffer_Write(&RX_Buffer, (uint8_t*)&cChar, 1);

            /*send received character through xbee*/
            UART_XBeeWriteBytes((uint8_t*)&cChar, 1);
        }
    }
}


