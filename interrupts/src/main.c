#include <stddef.h>
#include <stdint.h>
#include <msp430.h>

/* LED blinking frequency */
#define LED_BLINK_FREQ_HZ 2
 
/* Number of cycles to delay based on 1MHz MCLK */
#define LED_DELAY_CYCLES (1000000 / (2 * LED_BLINK_FREQ_HZ))

static void _watchdog_disable(void);
static void _watchdog_pet(void);
static void _watchdog_enable(void);
static volatile int _blink_enable = 0;
__attribute__((interrupt(PORT1_VECTOR))) void port1_isr(void);

int main(void)
{
	/* Disable watchdog until led blinks */
	_watchdog_disable();

	/* Configure the clock module - MCLK = 1MHz */
	DCOCTL = 0;
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;

	/* Configure ACLK to to be sourced from VLO = ~12KHz */
	BCSCTL3 |= LFXT1S_2;

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

	/* Set P1.3 interrupt to active-low edge  */
	P1IES |= BIT3; 

	/* Enable interrupt on P1.3 */
	P1IE |= BIT3;

	/* Global interrupt enable */
	__enable_interrupt();

	/* Wait forever until the button is pressed */
	while (P1IN & BIT3);

	/* Button pressed, enable */
	_watchdog_enable();

	while(1)
	{
		_watchdog_pet();
		if (_blink_enable != 0)
		{
			P1OUT ^= BIT0 | BIT6;

			/* Wait for LED_DELAY_CYCLES cycles */
			__delay_cycles(LED_DELAY_CYCLES);
		}
	}
	return 0;
}

static void _watchdog_disable(void)
{
    /* Hold the watchdog */
    WDTCTL = WDTPW + WDTHOLD;
}
 
static void _watchdog_pet(void)
{
    /**
     * Enable the watchdog with following settings
     * - sourced by ACLK
     * - interval = 32768 / 12000 = 2.73s
     */
    WDTCTL = WDTPW + (WDTSSEL | WDTCNTCL);
}

static void _watchdog_enable(void)
{
    /* Read the watchdog interrupt flag */
    if (IFG1 & WDTIFG) {
        /* Clear if set */
        IFG1 &= ~WDTIFG;
    }
 
    _watchdog_pet();
}

__attribute__((interrupt(PORT1_VECTOR))) void port1_isr(void)
{
    if (P1IFG & BIT3) {
        /* Clear the interrupt flag */
        P1IFG &= ~BIT3;

        /* Toggle the blink enable */
        _blink_enable ^= 1;
    }
}
