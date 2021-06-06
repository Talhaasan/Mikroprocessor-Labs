#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
void display (unsigned char number, unsigned char disp_num);
void convert_num_to_digits (unsigned int number,  unsigned char *hundreds, unsigned char *tens, unsigned char *ones);

void main(void) 
{
    unsigned int adc_result;
    unsigned char  hndrd, ten, one;
    
    TRISD = 0; 
    TRISBbits.TRISB4 = 0;   
    TRISBbits.TRISB5 = 0;   
    TRISBbits.TRISB6 = 0;   
    TRISBbits.TRISB7 = 0;   
    ADCON0 &= 0b11000111;  
    ADCON0 |= 0b00001000;  
    ADCON0bits.ADON = 1;   
    ADCON1 &= 0b10111111;  
    ADCON0 &= 0b01111111;  
    ADCON0 |= 0b01000000;  
                                               
    ADCON1bits.ADFM = 0;   
    ADCON1 |= 0b00000100;  
    ADCON1 &= 0b11110100;   
                           
    while (1)
    {
        ADCON0bits.GO = 1;
        while (ADCON0bits.GO) {}  
        adc_result = 0;          
        adc_result |= ADRESL>>8;
        adc_result |= ADRESH;
        if (PORTBbits.RB0)
        {
            PORTBbits.RB1 = 0;
        }
        else
        {
            PORTBbits.RB1 = 1;
        }           
        convert_num_to_digits (adc_result, &hndrd, &ten, &one);
                
        display(hndrd,1);
        display(ten,2);
        display(one,3);         
    }
    return;
}

void display (unsigned char number, unsigned char disp_num)
{    
    switch (disp_num)
    {
        case 1:
            PORTBbits.RB4 = 0;  
            PORTBbits.RB5 = 0;
            PORTBbits.RB6 = 1;
            PORTBbits.RB7 = 0;
            break;
        case 2:
            PORTBbits.RB4 = 0;  
            PORTBbits.RB5 = 1;
            PORTBbits.RB6 = 0;
            PORTBbits.RB7 = 0;
            break;
        case 3:
            PORTBbits.RB4 = 1;     
            PORTBbits.RB5 = 0;
            PORTBbits.RB6 = 0;
            PORTBbits.RB7 = 0;
            break;
        default:
            break;
    }   
    
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
    _delay(1000);   
    PORTBbits.RB4 = 0;
    PORTBbits.RB5 = 0;
    PORTBbits.RB6 = 0;
    PORTBbits.RB7 = 0;    
}

void convert_num_to_digits (unsigned int number, unsigned char *hundreds, unsigned char *tens, unsigned char *ones)
{
    *hundreds = 0; 
    *tens = 0;      
    *ones = 0;     
   
    while (number>99)
    {
        number-= 100;  
        (*hundreds)++;  
          
    } 
    while (number>9)
    {
        number-= 10;  
        (*tens)++;      
    }
    while (number>0)
    {
        number--;  
        (*ones)++; 
    }       
}