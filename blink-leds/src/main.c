#include <msp430.h>


int main(void)
{
	WDTCTL = WDTPW + WDTHOLD; // Stop WDT
	//PMSCTL0 &= ~LOCKLPMS;

	P1DIR |= 0x01; // P1.0 output
	P1DIR |= 0x01 << 6; // P1.6 output
	P1OUT ^= 0x01;

	for (;;)
	{
		volatile unsigned int i;
		P1OUT ^= 0x01;
		P1OUT ^= 0x01 << 6;

		i = 20000;
		do i--;
		while (i != 0);
	}
	return 0;
}

