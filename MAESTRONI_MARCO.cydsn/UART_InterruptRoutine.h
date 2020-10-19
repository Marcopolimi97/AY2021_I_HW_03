/**
*   \file UART_InterruptRoutine.h
*   \brief Header file for UART interrupt routines.
*/

#ifndef __UART_INTERRUPT_ROUTINES_H__
    #define __UART_INTERRUPT_ROUTINES_H__
    
    #include "cytypes.h"
    
    /**
    *   \brief ISR to be called on UART byte received
    */
    CY_ISR_PROTO(Custom_UART_RX_ISR);
    
#endif

/* [] END OF FILE */

