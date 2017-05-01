#include "pwm.h"



void PwmConfig(uint32_t ui32Load, uint16_t Roll, uint16_t Pitch)
{
	// SET PWM CLOCK
	SysCtlPWMClockSet(SYSCTL_PERIPH_64);
	
	// SETUP PWM PERIPHERAL
	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
	SysCTLPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	
	// ENABLE PWM PINS ON PERIPHERAL C
	GPIOPinTypePWM(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);
	GPIOPinConfigure(GPIO_PC4_M0PWM6);
	GPIOPinConfigure(GPIO_PC5_M0PWM7);
	
	// ENABLE GENERATORS
	PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN);
	PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, ui32Load);
	
	// SET PULSEWIDTH
	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, Roll * ui32Load / 1000);
	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, Pitch * ui32Load / 1000);
	
	// ENABLE OUTPUTS
	PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT | PWM_OUT_7_BIT, true);
	PWMGenEnable(PWM1_BASE, PWM_GEN_3);
	
}

void PWMDCSet (uint32_t ui32Load, uint16_t Roll, uint16_t Pitch)
{
	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, Roll * ui32Load / 1000);
	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, Pitch * ui32Load / 1000);
}
