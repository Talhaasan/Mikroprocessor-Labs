#include "p16f877a.inc"
  __CONFIG _FOSC_XT & _WDTE_OFF & _PWRTE_OFF & _BOREN_OFF & _LVP_OFF & _CPD_OFF & _WRT_OFF & _CP_OFF 

RES_VECT CODE 0x0000 
    GOTO START 

START 
    BSF STATUS,RP0 
    CLRF TRISB 
    BSF TRISB,0 
    BSF TRISB,2 
    BCF STATUS,RP0 
    CLRF PORTB

MAIN 
    CALL TURN_LED2;Calling TURN_LED2
    CALL TURN_LED4;Calling TURN_LED4
    GOTO MAIN

TURN_LED2
    BTFSS PORTB,0;bit test f skip if set (contol the PortB's 0.bit)	
    BSF	  PORTB,1;PortB's 1.bit set	
    BTFSC PORTB,0;bit test f skip if clear (contol the PortB's 0.bit)	
    BCF	  PORTB,1;PortB's 1.bit clear
    RETURN	
    
TURN_LED4   
    BTFSS PORTB,2;bit test f skip if set (contol the PortB's 2.bit)	
    BSF	  PORTB,3;PortB's 3.bit set	
    BTFSC PORTB,2;bit test f skip if clear(conrtol the PortB's 2.bit)	
    BCF	  PORTB,3;PortB's 3.bit clear
    RETURN	
    
END