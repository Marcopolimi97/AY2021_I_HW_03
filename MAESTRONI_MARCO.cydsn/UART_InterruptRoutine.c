/*
* MARCO MAESTRONI
*
* UART INTERRUPT: segnalazione della ricezione e invio stringa per GUI
*
*/

#include "UART_InterruptRoutine.h"

#include "UART.h"
#include "stdio.h" // --> sprintf function

extern uint8_t rec;
extern int state;

char test_variable;

CY_ISR(Custom_UART_RX_ISR)
{
    // Check UART Status, se non è vuoto e quindi ho ricevuto qualcosa
    if (UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY)
    {
        rec=1;
        
        test_variable = UART_ReadRxData();
        
        //se leggo il carattere v, mando la stringa seguente per attivare la GUI
        if(test_variable=='v')
        {
            UART_PutString("RGB LED Program $$$");
        } 
    }
}

/* [] END OF FILE */