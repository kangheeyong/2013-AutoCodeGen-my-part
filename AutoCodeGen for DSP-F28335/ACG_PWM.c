#include "ACG_PWM.h"


double before_period[6] = {0,0,0,0,0,0};
Uint16 PWM_A_using[6] = {0,0,0,0,0,0};
Uint16 PWM_B_using[6] = {0,0,0,0,0,0};

extern float SystemClock;

volatile struct EPWM_REGS *EPwm_Regs[6] ={&EPwm1Regs,&EPwm2Regs,&EPwm3Regs,&EPwm4Regs,&EPwm5Regs,&EPwm6Regs};

void EPwmxRegs(Uint16 num, Uint16 period)
{
	Uint16  temp = 0;
	float SYSCLK = SystemClock;

	if(SYSCLK*period <= 65536)
	{
		temp = (Uint16)(SYSCLK*period);
		EPwm_Regs[num]->TBCTL.bit.HSPCLKDIV = 0;	/* TBCLK = SYSCLKOUT / (HSPCLKDIV * CLKDIV) = SYSCLK */
		EPwm_Regs[num]->TBCTL.bit.CLKDIV = 0;
	}
	else if(SYSCLK*period/16 <= 9375)
	{
		temp = (Uint16)(SYSCLK*period/16);
		EPwm_Regs[num]->TBCTL.bit.HSPCLKDIV = 2;	/* TBCLK = SYSCLKOUT / (HSPCLKDIV * CLKDIV) = SYSCLK/16 */
		EPwm_Regs[num]->TBCTL.bit.CLKDIV = 2;
	}
	else if(SYSCLK*period/160 <= 9375)
	{
		temp = (Uint16)(SYSCLK*period/160);
		EPwm_Regs[num]->TBCTL.bit.HSPCLKDIV = 5;	/* TBCLK = SYSCLKOUT / (HSPCLKDIV * CLKDIV) = SYSCLK/160 */
		EPwm_Regs[num]->TBCTL.bit.CLKDIV = 4;
	}
	else if(SYSCLK*period/640 <= 9375)
	{
		temp = (Uint16)(SYSCLK*period/640);
		EPwm_Regs[num]->TBCTL.bit.HSPCLKDIV = 5;	/* TBCLK = SYSCLKOUT / (HSPCLKDIV * CLKDIV) = SYSCLK/640 */
		EPwm_Regs[num]->TBCTL.bit.CLKDIV = 6;
	}
	else
	{
		temp = (Uint16)(SYSCLK*period/1792);
		EPwm_Regs[num]->TBCTL.bit.HSPCLKDIV = 7;	/* TBCLK = SYSCLKOUT / (HSPCLKDIV * CLKDIV) = SYSCLK/1792 */
		EPwm_Regs[num]->TBCTL.bit.CLKDIV = 7;
	}

	/* Setup Counter Mode and Clock */
	EPwm_Regs[num]->TBCTL.bit.CTRMODE = 2;	/* Count Up and Down (Symmetric) */


	/* Setup Phase */
	EPwm_Regs[num]->TBPHS.half.TBPHS = 0;		/* Phase is 0 */
	EPwm1Regs.TBCTL.bit.PHSEN = 0;		/* Disable phase loading */

			/* Setup Period (Carrier Frequency) */
	EPwm_Regs[num]->TBPRD = temp/2;	/* Set Timer Period, аж╠Б= (TBPRD+1)/SYSCLK */
	EPwm_Regs[num]->TBCTR = 0;						/* Clear Counter */

			/* Setup shadowing */
	EPwm_Regs[num]->TBCTL.bit.PRDLD = 0;		/* Period Register is loaded from its shadow when CNTR=Zero */
	EPwm_Regs[num]->CMPCTL.bit.SHDWAMODE = 0;	/* Compare A Register is loaded from its shadow when CNTR=Zero */
	EPwm_Regs[num]->CMPCTL.bit.LOADAMODE = 0;
	EPwm_Regs[num]->CMPCTL.bit.SHDWBMODE = 0;	/* Compare B Register is loaded from its shadow when CNTR=Zero */
	EPwm_Regs[num]->CMPCTL.bit.LOADBMODE = 0;
}

void AcgPWM1_Setting(PWMChannel ch, Uint16 period)
{
	int dutycycle = 0;
	 if(before_period[0] != period)
	 {
		 before_period[0] = period;

		 EPwmxRegs(0,period);

	 }

	 if(ch & TIMER_01)
	 {
		 if(PWM_A_using[0] == 0)
		 {
			PWM_A_using[0] = 1;
			EALLOW;
			GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;	/* Enable pull-up on GPIO0 (EPWM1A) */
			GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;	/* Configure GPIO0 as EPWM1A */
			EDIS;
			 /* Set actions */
			EPwm1Regs.AQCTLA.bit.CAU = 2;		/* Set EPWM4A on CNTR=CMPA, Up-Count */
			EPwm1Regs.AQCTLA.bit.CAD = 1;		/* Clear EPWM4A on CNTR=CMPA, Down-Count */
		 }
		 /* Set Compare Value */
		 EPwm1Regs.CMPA.half.CMPA = (Uint16)(EPwm1Regs.TBPRD - (EPwm1Regs.TBPRD *(double)dutycycle/100));	/* Set Compare A Value */
	 }

	 if(ch & TIMER_02)
	 {
	 	 if(PWM_B_using[0] == 0)
	 	 {
	 		PWM_B_using[0] = 1;
 			EALLOW;
 			GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;	/* Enable pull-up on GPIO1 (EPWM1B) */
 			GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;	/* Configure GPIO1 as EPWM1B */
 			EDIS;
			 /* Set actions */
 			EPwm1Regs.AQCTLB.bit.CBU = 2;		/* Set EPWM4A on CNTR=CMPB, Up-Count */
 			EPwm1Regs.AQCTLB.bit.CBD = 1;		/* Clear EPWM4A on CNTR=CMPB, Down-Count */
 		 }
	 		 /* Set Compare Value */
	 		EPwm1Regs.CMPB = (Uint16)(EPwm1Regs.TBPRD - (EPwm1Regs.TBPRD *(double)dutycycle/100));	/* Set Compare B Value */
	 }

}
void AcgPWM1(PWMChannel ch, int dutycycle)
{
	 if(ch & TIMER_01)
	 {
		 /* Set Compare Value */
		 EPwm1Regs.CMPA.half.CMPA = (Uint16)(EPwm1Regs.TBPRD - (EPwm1Regs.TBPRD *(double)dutycycle/100));	/* Set Compare A Value */
	 }

	 if(ch & TIMER_02)
	 {
	 	/* Set Compare Value */
	 	EPwm1Regs.CMPB = (Uint16)(EPwm1Regs.TBPRD - (EPwm1Regs.TBPRD *(double)dutycycle/100));	/* Set Compare B Value */
	 }

}
void AcgPWM2_Setting(PWMChannel ch, Uint16 period)
{
	int dutycycle = 0;
	 if(before_period[1] != period)
	 {
		 before_period[1] = period;

		 EPwmxRegs(1,period);
	 }

	 if(ch  & TIMER_01)
	 {
		 if(PWM_A_using[1] == 0)
		 {
			PWM_A_using[1] = 1;
			EALLOW;
			GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;	/* Enable pull-up on GPIO0 (EPWM1A) */
			GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;	/* Configure GPIO0 as EPWM1A */
			EDIS;
			 /* Set actions */
			EPwm2Regs.AQCTLA.bit.CAU = 2;		/* Set EPWM4A on CNTR=CMPA, Up-Count */
			EPwm2Regs.AQCTLA.bit.CAD = 1;		/* Clear EPWM4A on CNTR=CMPA, Down-Count */
		 }
		 /* Set Compare Value */
		 EPwm2Regs.CMPA.half.CMPA = (Uint16)(EPwm2Regs.TBPRD - (EPwm2Regs.TBPRD *(double)dutycycle/100));	/* Set Compare A Value */
	 }

	 if(ch & TIMER_02)
	 {
	 	 if(PWM_B_using[1] == 0)
	 	 {
	 		PWM_B_using[1] = 1;
 			EALLOW;
 			GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;	/* Enable pull-up on GPIO1 (EPWM1B) */
 			GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;	/* Configure GPIO1 as EPWM1B */
 			EDIS;
			 /* Set actions */
 			EPwm2Regs.AQCTLB.bit.CBU = 2;		/* Set EPWM4A on CNTR=CMPB, Up-Count */
 			EPwm2Regs.AQCTLB.bit.CBD = 1;		/* Clear EPWM4A on CNTR=CMPB, Down-Count */
 		 }
	 		 /* Set Compare Value */
	 		EPwm2Regs.CMPB = (Uint16)(EPwm2Regs.TBPRD - (EPwm2Regs.TBPRD *(double)dutycycle/100));	/* Set Compare B Value */
	 }

}
void AcgPWM2(PWMChannel ch, int dutycycle)
{
	 if(ch  & TIMER_01)
	 {
		 /* Set Compare Value */
		 EPwm2Regs.CMPA.half.CMPA = (Uint16)(EPwm2Regs.TBPRD - (EPwm2Regs.TBPRD *(double)dutycycle/100));	/* Set Compare A Value */
	 }

	 if(ch & TIMER_02)
	 {
	 	/* Set Compare Value */
	 	EPwm2Regs.CMPB = (Uint16)(EPwm2Regs.TBPRD - (EPwm2Regs.TBPRD *(double)dutycycle/100));	/* Set Compare B Value */
	 }

}

void AcgPWM3_Setting(PWMChannel ch, Uint16 period)
{
	int dutycycle = 0;
	 if(before_period[2] != period)
	 {
		 before_period[2] = period;

		 EPwmxRegs(2,period);
	 }

	 if(ch & TIMER_01)
	 {
		 if(PWM_A_using[2] == 0)
		 {
			PWM_A_using[2] = 1;
			EALLOW;
			GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;	/* Enable pull-up on GPIO0 (EPWM1A) */
			GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;	/* Configure GPIO0 as EPWM1A */
			EDIS;
			 /* Set actions */
			EPwm3Regs.AQCTLA.bit.CAU = 2;		/* Set EPWM4A on CNTR=CMPA, Up-Count */
			EPwm3Regs.AQCTLA.bit.CAD = 1;		/* Clear EPWM4A on CNTR=CMPA, Down-Count */
		 }
		 /* Set Compare Value */
		 EPwm3Regs.CMPA.half.CMPA = (Uint16)(EPwm3Regs.TBPRD - (EPwm3Regs.TBPRD *(double)dutycycle/100));	/* Set Compare A Value */
	 }

	 if(ch & TIMER_02)
	 {
	 	 if(PWM_B_using[2] == 0)
	 	 {
	 		PWM_B_using[2] = 1;
 			EALLOW;
 			GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;	/* Enable pull-up on GPIO1 (EPWM1B) */
 			GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;	/* Configure GPIO1 as EPWM1B */
 			EDIS;
			 /* Set actions */
 			EPwm3Regs.AQCTLB.bit.CBU = 2;		/* Set EPWM4A on CNTR=CMPB, Up-Count */
 			EPwm3Regs.AQCTLB.bit.CBD = 1;		/* Clear EPWM4A on CNTR=CMPB, Down-Count */
 		 }
	 		 /* Set Compare Value */
	 		EPwm3Regs.CMPB = (Uint16)(EPwm3Regs.TBPRD - (EPwm3Regs.TBPRD *(double)dutycycle/100));	/* Set Compare B Value */
	 }

}
void AcgPWM3(PWMChannel ch, int dutycycle)
{
	 if(ch & TIMER_01)
	 {
		 /* Set Compare Value */
		 EPwm3Regs.CMPA.half.CMPA = (Uint16)(EPwm3Regs.TBPRD - (EPwm3Regs.TBPRD *(double)dutycycle/100));	/* Set Compare A Value */
	 }

	 if(ch & TIMER_02)
	 {
	 	/* Set Compare Value */
	 	EPwm3Regs.CMPB = (Uint16)(EPwm3Regs.TBPRD - (EPwm3Regs.TBPRD *(double)dutycycle/100));	/* Set Compare B Value */
	 }

}
void AcgPWM4_Setting(PWMChannel ch, Uint16 period)
{
	int dutycycle = 0;
	 if(before_period[3] != period)
	 {
		 before_period[3] = period;

		 EPwmxRegs(3,period);
	 }
	 if(ch & TIMER_01)
	 {
		 if(PWM_A_using[3] == 0)
		 {
			PWM_A_using[3] = 1;
			EALLOW;
			GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;	/* Enable pull-up on GPIO0 (EPWM1A) */
			GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;	/* Configure GPIO0 as EPWM1A */
			EDIS;
			 /* Set actions */
			EPwm4Regs.AQCTLA.bit.CAU = 2;		/* Set EPWM4A on CNTR=CMPA, Up-Count */
			EPwm4Regs.AQCTLA.bit.CAD = 1;		/* Clear EPWM4A on CNTR=CMPA, Down-Count */
		 }
		 /* Set Compare Value */
		 EPwm4Regs.CMPA.half.CMPA = (Uint16)(EPwm4Regs.TBPRD - (EPwm4Regs.TBPRD *(double)dutycycle/100));	/* Set Compare A Value */
	 }

	 if(ch & TIMER_02)
	 {
	 	 if(PWM_B_using[3] == 0)
	 	 {
	 		PWM_B_using[3] = 1;
 			EALLOW;
 			GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;	/* Enable pull-up on GPIO1 (EPWM1B) */
 			GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;	/* Configure GPIO1 as EPWM1B */
 			EDIS;
			 /* Set actions */
 			EPwm4Regs.AQCTLB.bit.CBU = 2;		/* Set EPWM4A on CNTR=CMPB, Up-Count */
 			EPwm4Regs.AQCTLB.bit.CBD = 1;		/* Clear EPWM4A on CNTR=CMPB, Down-Count */
 		 }
	 		 /* Set Compare Value */
	 		EPwm4Regs.CMPB = (Uint16)(EPwm4Regs.TBPRD - (EPwm4Regs.TBPRD *(double)dutycycle/100));	/* Set Compare B Value */
	 }

}
void AcgPWM4(PWMChannel ch,int dutycycle)
{
	 if(ch & TIMER_01)
	 {
		 /* Set Compare Value */
		 EPwm4Regs.CMPA.half.CMPA = (Uint16)(EPwm4Regs.TBPRD - (EPwm4Regs.TBPRD *(double)dutycycle/100));	/* Set Compare A Value */
	 }

	 if(ch & TIMER_02)
	 {
	 	/* Set Compare Value */
	 	EPwm4Regs.CMPB = (Uint16)(EPwm4Regs.TBPRD - (EPwm4Regs.TBPRD *(double)dutycycle/100));	/* Set Compare B Value */
	 }
}
void AcgPWM5_Setting(PWMChannel ch, Uint16 period)
{
	 int dutycycle = 0;
	 if(before_period[4] != period)
	 {
		 before_period[4] = period;

		 EPwmxRegs(4,period);
	 }

	 if(ch & TIMER_01)
	 {
		 if(PWM_A_using[4] == 0)
		 {
			PWM_A_using[4] = 1;
			EALLOW;
			GpioCtrlRegs.GPAPUD.bit.GPIO8 = 0;	/* Enable pull-up on GPIO0 (EPWM1A) */
			GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 1;	/* Configure GPIO0 as EPWM1A */
			EDIS;
			 /* Set actions */
			EPwm5Regs.AQCTLA.bit.CAU = 2;		/* Set EPWM4A on CNTR=CMPA, Up-Count */
			EPwm5Regs.AQCTLA.bit.CAD = 1;		/* Clear EPWM4A on CNTR=CMPA, Down-Count */
		 }
		 /* Set Compare Value */
		 EPwm5Regs.CMPA.half.CMPA = (Uint16)(EPwm5Regs.TBPRD - (EPwm5Regs.TBPRD *(double)dutycycle/100));	/* Set Compare A Value */
	 }

	 if(ch & TIMER_02)
	 {
	 	 if(PWM_B_using[4] == 0)
	 	 {
	 		PWM_B_using[4] = 1;
 			EALLOW;
 			GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;	/* Enable pull-up on GPIO1 (EPWM1B) */
 			GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 1;	/* Configure GPIO1 as EPWM1B */
 			EDIS;
			 /* Set actions */
 			EPwm5Regs.AQCTLB.bit.CBU = 2;		/* Set EPWM4A on CNTR=CMPB, Up-Count */
 			EPwm5Regs.AQCTLB.bit.CBD = 1;		/* Clear EPWM4A on CNTR=CMPB, Down-Count */
 		 }
	 		 /* Set Compare Value */
	 		EPwm5Regs.CMPB = (Uint16)(EPwm5Regs.TBPRD - (EPwm5Regs.TBPRD *(double)dutycycle/100));	/* Set Compare B Value */
	 }

}
void AcgPWM5(PWMChannel ch,int dutycycle)
{
	 if(ch & TIMER_01)
	 {
		 /* Set Compare Value */
		 EPwm5Regs.CMPA.half.CMPA = (Uint16)(EPwm5Regs.TBPRD - (EPwm5Regs.TBPRD *(double)dutycycle/100));	/* Set Compare A Value */
	 }

	 if(ch & TIMER_02)
	 {
	 	/* Set Compare Value */
	 	EPwm5Regs.CMPB = (Uint16)(EPwm5Regs.TBPRD - (EPwm5Regs.TBPRD *(double)dutycycle/100));	/* Set Compare B Value */
	 }
}
void AcgPWM6_Setting(PWMChannel ch, Uint16 period)
{

	 int dutycycle = 0;
	 if(before_period[5] != period)
	 {
		 before_period[5] = period;

		 EPwmxRegs(5,period);
	 }

	 if(ch & TIMER_01)
	 {
		 if(PWM_A_using[5] == 0)
		 {
			PWM_A_using[5] = 1;
			EALLOW;
			GpioCtrlRegs.GPAPUD.bit.GPIO10 = 0;	/* Enable pull-up on GPIO0 (EPWM1A) */
			GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 1;	/* Configure GPIO0 as EPWM1A */
			EDIS;
			 /* Set actions */
			EPwm6Regs.AQCTLA.bit.CAU = 2;		/* Set EPWM4A on CNTR=CMPA, Up-Count */
			EPwm6Regs.AQCTLA.bit.CAD = 1;		/* Clear EPWM4A on CNTR=CMPA, Down-Count */
		 }
		 /* Set Compare Value */
		 EPwm6Regs.CMPA.half.CMPA = (Uint16)(EPwm6Regs.TBPRD - (EPwm6Regs.TBPRD *(double)dutycycle/100));	/* Set Compare A Value */
	 }

	 if(ch & TIMER_02)
	 {
	 	 if(PWM_B_using[5] == 0)
	 	 {
	 		PWM_B_using[5] = 1;
 			EALLOW;
 			GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;	/* Enable pull-up on GPIO1 (EPWM1B) */
 			GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 1;	/* Configure GPIO1 as EPWM1B */
 			EDIS;
			 /* Set actions */
 			EPwm6Regs.AQCTLB.bit.CBU = 2;		/* Set EPWM4A on CNTR=CMPB, Up-Count */
 			EPwm6Regs.AQCTLB.bit.CBD = 1;		/* Clear EPWM4A on CNTR=CMPB, Down-Count */
 		 }
	 		 /* Set Compare Value */
	 		EPwm6Regs.CMPB = (Uint16)(EPwm6Regs.TBPRD - (EPwm6Regs.TBPRD *(double)dutycycle/100));	/* Set Compare B Value */
	 }

}
void AcgPWM6(PWMChannel ch,int dutycycle)
{
	if(ch & TIMER_01)
	{

		/* Set Compare Value */
		EPwm6Regs.CMPA.half.CMPA = (Uint16)(EPwm6Regs.TBPRD - (EPwm6Regs.TBPRD *(double)dutycycle/100));	/* Set Compare A Value */
	}

	if(ch & TIMER_02)
	{

		 /* Set Compare Value */
		 EPwm6Regs.CMPB = (Uint16)(EPwm6Regs.TBPRD - (EPwm6Regs.TBPRD *(double)dutycycle/100));	/* Set Compare B Value */
	}

}




