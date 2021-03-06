/*
* MARCO MAESTRONI
*
* TIMER INTERRUPT: setting del timeout
*
*/


#include "Timer_InterruptRoutine.h"

int state;

CY_ISR(ISR_TIMER)
{
    /* nel caso in cui siano passati 5 sec da quando è stato attivato il TIMER, 
     * ovvero è avvenuta una interrupt, torno allo stato IDLE
     */
    state=0;
    
    // rimetto il valore della interrupt basso
    Timer_ReadStatusRegister();
}

/* [] END OF FILE */
