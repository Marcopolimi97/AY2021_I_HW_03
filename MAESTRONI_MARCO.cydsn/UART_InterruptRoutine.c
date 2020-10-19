/*
* MARCO MAESTRONI
*
* UART INTERRUPT: segnalazione della ricezione e invio stringa per GUI
*
*/

//#include "project.h"
#include "UART_InterruptRoutine.h"
//#include "Timer_InterruptRoutine.h"

#include "UART.h"
#include "stdio.h" // --> sprintf function

extern uint8_t rec;
extern int state;

char test_variable;
char string[]={'\0'};

CY_ISR(Custom_UART_RX_ISR)
{
    // Check UART Status, se non è vuoto e quindi ho ricevuto qualcosa
    if (UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY)
    {
        rec=1;
        
        test_variable = UART_ReadRxData();
        
        if(test_variable=='v')
        {
            char string[]={"RGB LED Program $$$"};
            UART_PutString(string);
        } 
    }
}

/* [] END OF FILE */