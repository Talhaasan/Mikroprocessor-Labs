#include "p16f877a.inc"

__CONFIG _FOSC_XT & _WDTE_OFF & _PWRTE_OFF & _BOREN_OFF & _LVP_OFF & _CPD_OFF & _WRT_OFF & _CP_OFF

W_TEMP EQU 0x70
STATUS_TEMP EQU 0x71
PCLATH_TEMP EQU 0x72
FSR_TEMP EQU 0x73 
TIMER_DIVIDER EQU 0x20 ; for 1 second timing
    
 
RES_VECT  CODE    0x0000            ; processor reset vector
    GOTO    START                   ; go to beginning of program
    
ISR       CODE    0x0004           ; interrupt vector location
    BCF INTCON,GIE
    MOVWF W_TEMP ;Copy W to TEMP register
    SWAPF STATUS,W ;Swap status to be saved into W
    CLRF STATUS ;bank 0, regardless of current bank, Clears IRP,RP1,RP0
    MOVWF STATUS_TEMP ;Save status to bank zero STATUS_TEMP register
    MOVF FSR,W
    MOVWF FSR_TEMP; Save current FSR to FSR_TEMP
    MOVF PCLATH, W ;Only required if using pages 1, 2 and/or 3
    MOVWF PCLATH_TEMP ;Save PCLATH into W
    CLRF PCLATH ;Page zero, regardless of current page
    
    BTFSS  INTCON,TMR0IF ; is this a timer interrupt?
    GOTO EXIT_ISR
    GOTO TIMER_ISR
TIMER_ISR
    BCF STATUS,RP0
    BCF STATUS,RP1   ; ensure Bank0
    BCF INTCON,TMR0IF
    MOVLW .61	    ; reinit timer0
    MOVWF TMR0
    CALL TOGGLE_LED
    GOTO EXIT_TIMER
EXIT_TIMER 
    GOTO EXIT_ISR    
EXIT_ISR
    MOVF PCLATH_TEMP, W ;Restore PCLATH
    MOVWF PCLATH ;Move W into PCLATH
    MOVF FSR_TEMP,W ;Restore FSR
    MOVWF FSR ;Move W into FSR
    SWAPF STATUS_TEMP,W ;Swap STATUS_TEMP register into W
    ;(sets bank to original state)
    MOVWF STATUS ;Move W into STATUS register
    SWAPF W_TEMP,F ;Swap W_TEMP
    SWAPF W_TEMP,W ;Swap W_TEMP into W  
    BSF INTCON,GIE
    RETFIE   
START
    BCF STATUS,RP1    
    BSF STATUS,RP0   ; Bank 1
    BCF TRISB,3
    BCF TRISB,2
    BCF TRISB,1    
    BCF TRISB,0
    BCF OPTION_REG,T0CS   ; Clock source = Internal instruction cycle clock
    BCF OPTION_REG,T0SE	  ; Increment on low-to-high transition
    BCF OPTION_REG,PSA	    ; Prescaler is assigned to the Timer0 module
    MOVLW b'00000111'	    ;     1 : 256 prescaler
    IORWF OPTION_REG	    ;     1 : 256 prescaler
    MOVLW b'11111111'	    ;     1 : 256 prescaler
    ANDWF OPTION_REG 	    ;     1 : 256 prescaler
    BCF STATUS,RP0 ; Bank 0
    BCF PORTD,0  
    MOVLW .61  
    MOVWF TMR0  
    BSF INTCON,TMR0IE
    BSF INTCON,GIE
LOOP
    GOTO LOOP                          ; loop forever
TOGGLE_LED
    BTFSC PORTB,0
    GOTO TURN_LED_OFF
    GOTO TURN_LED_ON
TURN_LED_OFF
    BCF PORTB,0
    RETURN
TURN_LED_ON
    BSF PORTB,0
    RETURN       
    END