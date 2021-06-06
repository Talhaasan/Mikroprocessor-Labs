#include "p16f877a.inc"
    
__CONFIG _FOSC_XT & _WDTE_OFF & _PWRTE_OFF & _BOREN_OFF & _LVP_OFF & _CPD_OFF &_WRT_OFF & _CP_OFF
    
RES_VECT  CODE    0x0000            ; processor reset vector
    GOTO    START                   ; go to beginning of program

START
    BSF STATUS,RP0
    MOVLW b'00001111'
    MOVWF TRISB
    CLRF TRISD
    BCF STATUS,RP0
    CLRF PORTD

TURN_S1
    MOVLW 0X06
    CALL SEVEN_SEGMENT
    MOVWF PORTD
    BCF PORTB,4
    BTFSS PORTB,0
    BSF PORTB,7
    
TURN_S4
    MOVLW 0X09
    CALL SEVEN_SEGMENT
    MOVWF PORTD
    BCF PORTB,7
    BTFSS PORTB,3
    BSF PORTB,4
    
LOOP
    GOTO TURN_S1
    GOTO TURN_S4
    GOTO LOOP

SEVEN_SEGMENT
    ADDWF PCL
    RETLW 0X1F    ;0
    RETLW 0X06    ;1
    RETLW 0X5B    ;2
    RETLW 0X4F    ;3
    RETLW 0X66    ;4 
    RETLW 0X6D    ;5
    RETLW 0X7D    ;6
    RETLW 0X07    ;7
    RETLW 0X7F    ;8
    RETLW 0X6F    ;9

    END