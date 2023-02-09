/*
 * OccupancyDetector.c
 *
 *  Created on: Jan 30, 2023
 *      Author: Chris Stanski
 */
#include <msp430.h>

void dects();

int Time = 0;

int main(void)
{


    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    P6OUT &= ~BIT6;                         // Clear P1.0 output latch for a defined power-on state
    P6DIR |= BIT6;
    P1OUT &= ~BIT0;                         // Clear P1.0 output latch for a defined power-on state
    P1DIR |= BIT0;

    P2OUT |= BIT3;
    P2DIR &= ~BIT3;
    P2REN |= BIT3;

    P4OUT |= BIT1;
    P4DIR &= ~BIT1;
    P4REN |= BIT1;


    while(1)
       {
           P6OUT |= BIT6;
           __delay_cycles(100000);             // Delay for 100000*(1/MCLK)=0.1s
           P6OUT &= ~BIT6;
           __delay_cycles(3000000);

           if((P2IN & BIT3) == 0)
           {
               dects();

               }

           }
       }

void dects(){

    while(1)
        {
            P1OUT |= BIT0;
            __delay_cycles(500000);
            P1OUT &= ~BIT0;
            __delay_cycles(500000);
            P6OUT &= ~BIT6;

            Time= Time + 1;

            if((P2IN & BIT3)){
                main();
            }


            if(Time == 11)
            {
                while(1)
                {
                    P1OUT |= BIT0;
                    if((P4IN & BIT1) == 0){
                        main();
                    }
                 }

                }


            }
  }





