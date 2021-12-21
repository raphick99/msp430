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
	WDTCTL = WDTPW + WDTHOLD; // Stop WDT

	/* Configure the clock module - MCLK = 1MHz */
	DCOCTL = 0;
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;

	P1DIR |= BIT0 | BIT6; // P1.0 output, P1.6 output

	P1OUT &= ~BIT0;  // P1.0 off
	P1OUT |= BIT6;  // P1.6 on

	while(1)
	{
		/* Wait for LED_DELAY_CYCLES cycles */
		__delay_cycles(LED_DELAY_CYCLES);
		P1OUT ^= BIT0 | BIT6;
	}
	return 0;
}

