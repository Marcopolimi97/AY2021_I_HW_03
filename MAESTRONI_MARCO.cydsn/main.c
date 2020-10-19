/*
* MARCO MAESTRONI
*
* MAIN: gestione macchina a stati
*
*/
#include "project.h"
#include "UART_InterruptRoutine.h"
#include "Timer_InterruptRoutine.h"

#define IDLE_STATE              0
#define HEADER_BYTE_RECEIVED    1
#define RED_BYTE_RECEIVED       2
#define GREEN_BYTE_RECEIVED     3
#define BLUE_BYTE_RECEIVED      4
#define TAIL_BYTE_RECEIVED      5

uint8_t rec = 0;
int state = 0;
int received=0;


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    // Start UART component
    UART_Start();
    // Enable the isr and timer
    //isr_UART_StartEx(Custom_UART_RX_ISR);
    //isr_Timer_StartEx(ISR_TIMER);
    
    //Timer_Enable();
    
    // Start PWM Components
    PWM_RG_Start(); // Start PWM connected to red and green channels
    PWM_B_Start();  // Start PWM connected to blu channel
    
    //"BLACK_COLOR" settato all'avvio
    PWM_RG_WriteCompare1(255);
    PWM_RG_WriteCompare2(255);
    PWM_B_WriteCompare(255);
    
    //UART_PutString("Inserisci HEADER_BYTE:\r\n");
    

    for(;;)
    {   
        if(state==IDLE_STATE)
        {
            //"BLACK_COLOR" settato all'avvio
            PWM_RG_WriteCompare1(255);
            PWM_RG_WriteCompare2(255);
            PWM_B_WriteCompare(255);
            
            // se ho ricevuto un messaggio la flag rec è stata messa a 1
            if (rec == 1)
            {
                rec=0;
                //leggo il messaggio
                received=UART_ReadRxData();
                if(received==160)
                {
                    state=HEADER_BYTE_RECEIVED;
                }
            }        
        }
        
        if(state==HEADER_BYTE_RECEIVED)
        {
            // faccio partire il TIMER.
            //isr_Timer_Start();
            // se ho ricevuto un messaggio la flag rec è stata messa a 1
            if (rec == 1)
            {
                rec=0;
                //leggo il messaggio
                received = UART_ReadRxData();
                if(received>=0 && received<=255)
                {
                    state=RED_BYTE_RECEIVED;
                }
            }        
        }
        
        if(state==RED_BYTE_RECEIVED)
        {
            //imposto il colore rosso
            PWM_RG_WriteCompare1(255-received);
            // faccio partire il TIMER.
            //isr_Timer_Start();
            // se ho ricevuto un messaggio la flag rec è stata messa a 1
            if (rec == 1)
            {
                rec=0;
                //leggo il messaggio
                received = UART_ReadRxData();
                if(received>=0 && received<=255)
                {
                    state=GREEN_BYTE_RECEIVED;
                }
            }        
        }
        
        if(state==GREEN_BYTE_RECEIVED)
        {
            //imposto il colore verde
            PWM_RG_WriteCompare2(255-received);
            // faccio partire il TIMER.
            //isr_Timer_Start();
            // se ho ricevuto un messaggio la flag rec è stata messa a 1
            if (rec == 1)
            {
                rec=0;
                //leggo il messaggio
                received = UART_ReadRxData();
                if(received>=0 && received<=255)
                {
                    state=BLUE_BYTE_RECEIVED;
                }
            }        
        }
        
        if(state==BLUE_BYTE_RECEIVED)
        {
            //imposto il colore blu
            PWM_B_WriteCompare(255-received);
            // faccio partire il TIMER.
            //isr_Timer_Start();
            // se ho ricevuto un messaggio la flag rec è stata messa a 1
            if (rec == 1)
            {
                rec=0;
                //leggo il messaggio
                received = UART_ReadRxData();
                if(received==192)
                {
                    state=TAIL_BYTE_RECEIVED;
                }
            }        
        }
        
        if(state==TAIL_BYTE_RECEIVED)
        {
            // faccio partire il TIMER.
            //isr_Timer_Stop();
            //imposto "BLACK_COLOR" e torno allo stato iniziale
            PWM_RG_WriteCompare1(255);
            PWM_RG_WriteCompare2(255);
            PWM_B_WriteCompare(255);
            
            state=IDLE_STATE;
        }    
    }
}

    
    
/* [] END OF FILE */
