#include <stddef.h>
#include <stdint.h>
#include <msp430.h>

/* LED blinking frequency */
#define LED_BLINK_FREQ_HZ 1
 
/* Number of cycles to delay based on 1MHz MCLK */
#define LED_DELAY_CYCLES (1000000 / (2 * LED_BLINK_FREQ_HZ))

static int _verify_cal_data(void)
{
    size_t len = 62 / 2;
    uint16_t *data = (uint16_t *) 0x10c2;
    uint16_t crc = 0;
 
    while (len-- > 0) {
        crc ^= *(data++);
    }
 
    return (TLV_CHECKSUM + crc);
}

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD; /* Stop WDT */

	if (_verify_cal_data() != 0) {
		/*  Calibration data is corrupted...hang */
		while(1);
	}

	/* Configure the clock module - MCLK = 1MHz */
	DCOCTL = 0;
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;

	P1DIR |= BIT0 | BIT6; /* P1.0 output, P1.6 output */

	P1OUT &= ~BIT0;  /* P1.0 off */
	P1OUT |= BIT6;  /* P1.6 on */

	/* Configure P1.3 to digital input */
	P1SEL &= ~BIT3;
	P1SEL2 &= ~BIT3;
	P1DIR &= ~BIT3;

	/* Pull-up required for rev 1.5 Launchpad */
	P1REN |= BIT3;
	P1OUT |= BIT3;

	/* Wait forever until the button is pressed */
	while (P1IN & BIT3);

	while(1)
	{
		P1OUT ^= BIT0 | BIT6;

		/* Wait for LED_DELAY_CYCLES cycles */
		__delay_cycles(LED_DELAY_CYCLES);
	}
	return 0;
}

