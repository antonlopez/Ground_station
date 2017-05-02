#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h"
#include "driverlib/pwm.h"
#include "inc/hw_gpio.h"


void PwmConfig(uint32_t ui32Load, uint16_t Roll, uint16_t Pitch);
void PWMDCSet (uint32_t ui32Load, uint16_t Roll, uint16_t Pitch);
