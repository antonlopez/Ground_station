#include "pwm.h"



void PwmConfig(void){


		//**********PWM*************

		uint32_t period = 5000; //20ms (16Mhz / 64pwm_divider / 50)
		uint32_t duty = 400;    //1.5ms pulse width


		 //Configure PWM Clock divide system clock by 64
			SysCtlPWMClockSet(SYSCTL_PWMDIV_64);

		    // Enable the peripherals used by this program.
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
		    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
		    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);


		    // Unlock the Pin PF0 and Set the Commit Bit
		    // See datasheet table 10-1 for explanation of
		    // why this pin needs unlocking
		    //HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
		    //HWREG(GPIO_PORTF_BASE + GPIO_O_CR)   |= 0x01;




			//Configure PF0,PF1,PF2,PF3,PA6 Pins as PWM          PF1 servo 1.     PF2 servo2
		    //GPIOPinConfigure(GPIO_PF0_M1PWM4);          //PWM_OUT_4
			GPIOPinConfigure(GPIO_PF1_M1PWM5);          //PWM_OUT_5
			GPIOPinConfigure(GPIO_PF2_M1PWM6);          //PWM_OUT_6
			GPIOPinConfigure(GPIO_PF3_M1PWM7);          //PWM_OUT_7
			GPIOPinConfigure(GPIO_PA6_M1PWM2);          //PWM_OUT_2

			GPIOPinTypePWM(GPIO_PORTA_BASE, GPIO_PIN_6);
			GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

			//Configure PWM Options
			//PWM_GEN_1 covers ...
			//PWM_GEN_2 Covers M1PWM4 and M1PWM5
			//PWM_GEN_3 Covers M1PWM6 and M1PWM7
			PWMGenConfigure(PWM1_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
			PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
			PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

			//Set the Period (expressed in clock ticks)
			 PWMGenPeriodSet(PWM1_BASE, PWM_GEN_1, period);
			 PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, period);
			 PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, period);

			//Set PWM duty
			 PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2,duty);
			 //PWMPulseWidthSet(PWM1_BASE, PWM_OUT_4,duty);
			 PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5,duty);
		     PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6,duty);
			 PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7,duty);

			 // Enable the PWM generator
			 PWMGenEnable(PWM1_BASE, PWM_GEN_1);
			 PWMGenEnable(PWM1_BASE, PWM_GEN_2);
			 PWMGenEnable(PWM1_BASE, PWM_GEN_3);

			 // Turn on the Output pins PF1,PF2, PF3,
			 PWMOutputState(PWM1_BASE, PWM_OUT_2_BIT | PWM_OUT_5_BIT | PWM_OUT_6_BIT | PWM_OUT_7_BIT, true);



	}

