#include "pwm.h"



void PwmConfig(uint32_t ui32Load, uint16_t Roll, uint16_t Pitch)
{

    // SET PWM CLOCK
        SysCtlPWMClockSet(SYSCTL_PWMDIV_64);

        // SETUP PWM PERIPHERAL
        SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);



        // ENABLE PWM PINS ON PERIPHERAL A
        GPIOPinTypePWM(GPIO_PORTA_BASE, GPIO_PIN_6 | GPIO_PIN_7);
        GPIOPinConfigure(GPIO_PA6_M1PWM2);
        GPIOPinConfigure(GPIO_PA7_M1PWM3);

        // ENABLE GENERATORS
        PWMGenConfigure(PWM1_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN);
        PWMGenPeriodSet(PWM1_BASE, PWM_GEN_1, ui32Load);

        // SET PULSEWIDTH
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2, Roll * ui32Load / 1000);
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_3, Pitch * ui32Load / 1000);

        // ENABLE OUTPUTS
        PWMGenEnable(PWM1_BASE, PWM_GEN_1);
        PWMOutputState(PWM1_BASE, PWM_OUT_2_BIT | PWM_OUT_3_BIT, true);




	
}

void PWMDCSet (uint32_t ui32Load, uint16_t Roll, uint16_t Pitch)
{
	

    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2, Roll * ui32Load / 1000);
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_3, Pitch * ui32Load / 1000);



}
