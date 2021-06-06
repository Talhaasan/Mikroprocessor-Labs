// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>

unsigned char timer_divider;
unsigned char number;

void display (unsigned char number, unsigned char display_num);

void interrupt isr_vector (void)  
{
    INTCONbits.GIE = 0;
    if (INTCONbits.T0IF)
    {
        INTCONbits.T0IF = 0;
        TMR0 = 240;
        timer_divider--;
        if (timer_divider == 0)
        {
            if (PORTBbits.RB3)
            {   
                if (number == 9)   
                    number = 0;
                else
                    number++;
            }                
            if(PORTBbits.RB2)
            {   
                if (number == 0)  
                    number = 9;
                else
                    number--;
            }
            display (number,3);
            timer_divider = 100;
        }
    }
    INTCONbits.GIE = 1;
}

void main(void) 
{
    ADCON1 |= 0b00000111;   // Adjust ADCON1,PCFG3:PCFG0 bits
    ADCON1 &= 0b11110111;   // Adjust ADCON1,PCFG3:PCFG0 bits
                            // Now all PORTA pins are digital I/O. See 
				    // ADCON1 register in 
                            // datasheet for details. 
    TRISB = 0;
    TRISBbits.TRISB2 = 1;
    TRISBbits.TRISB3 = 1;
    TRISD = 0;             
    OPTION_REGbits.T0CS = 0;  //Clock source = Internal instruction cycle 
					// clock
    OPTION_REGbits.T0SE	= 0;  //Increment on low-to-high transition
    OPTION_REGbits.PSA	= 0;  //Prescaler is assigned to the Timer0 module
    OPTION_REG |= 0b00000110;  //   1 : 128 prescaler 
    OPTION_REG &= 0b11111110; //   1 : 128 prescaler
    
    timer_divider = 100;
    TMR0 = 240;     
    INTCONbits.T0IE = 1;
    INTCONbits.GIE = 1;    
    while (1)
    {
        // loop forever
    }
    return;
}

void display (unsigned char number, unsigned char display_num)
{   
    
    switch (number)
    {
        case 0:
            PORTD = 0b00111111;
            break;
        case 1:
            PORTD = 0b00000110;
            break;
        case 2:
            PORTD = 0b01011011;
            break;
        case 3:
            PORTD = 0b01001111;
            break;
        case 4:
            PORTD = 0b01100110;
            break;
        case 5:
            PORTD = 0b01101101;
            break;
        case 6:
            PORTD = 0b01111101;
            break;
        case 7:
            PORTD = 0b00000111;
            break;
        case 8:
            PORTD = 0b01111111;
            break;
        case 9:
            PORTD = 0b01101111;
            break;
        default:
            break;
    }    
    
    switch (display_num)
{
        case 3:
            PORTBbits.RB4 = 1;
            PORTBbits.RB5 = 0;
            PORTBbits.RB6 = 0;
            PORTBbits.RB7 = 0;
            break;
        default:
            break;
}   
   
}