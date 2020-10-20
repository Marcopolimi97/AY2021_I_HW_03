/*
* MARCO MAESTRONI
*
* MAIN: 
* Gestione macchina a stati.
* Implemento il codice impostando la ricezione di un byte alla volta.
*
* Ho messo come commenti i vari 'UART_PutString' poichè mi ostacolavano
* l'invio dei byte da CoolTerm
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
    isr_UART_StartEx(Custom_UART_RX_ISR);
    isr_Timer_StartEx(ISR_TIMER);
    
    // Start PWM Components
    PWM_RG_Start(); // Start PWM connected to red and green channels
    PWM_B_Start();  // Start PWM connected to blu channel
    
    //"BLACK_COLOR" settato all'avvio
    PWM_RG_WriteCompare1(255);
    PWM_RG_WriteCompare2(255);
    PWM_B_WriteCompare(255);
    
    //UART_PutString("Inserisci HEADER:\r\n");
    

    for(;;)
    {   
        if(state==IDLE_STATE)
        {
            // se ho ricevuto un messaggio la flag rec è stata messa a 1
            if (rec == 1)
            {
                rec=0;
                //leggo il messaggio
                received=UART_ReadRxData();
                //se il byte letto coincide con l'HEADER_BYTE
                if(received==160)
                {
                    // faccio partire il TIMER, che parte inizializzato e attiva Timer_Enable () [vedi dichiarazione funzione]
                    Timer_Start();
                    state=HEADER_BYTE_RECEIVED;
                    //UART_PutString("Inserisci RED:\r\n");
                }
            }        
        }
        
        if(state==HEADER_BYTE_RECEIVED)
        {
            // se ho ricevuto un messaggio la flag rec è stata messa a 1
            if (rec == 1)
            {
                rec=0;
                //leggo il messaggio
                received = UART_ReadRxData();
                //controllo sul valore letto
                if(received>=0 && received<=255)
                {
                    // faccio partire il TIMER, che parte inizializzato e attiva Timer_Enable () [vedi dichiarazione funzione]
                    Timer_Start();
                    state=RED_BYTE_RECEIVED;
                    //UART_PutString("Inserisci GREEN:\r\n");
                }
            }        
        }
        
        if(state==RED_BYTE_RECEIVED)
        {
            //imposto il colore rosso
            PWM_RG_WriteCompare1(255-received);
            // se ho ricevuto un messaggio la flag rec è stata messa a 1
            if (rec == 1)
            {
                rec=0;
                //leggo il messaggio
                received = UART_ReadRxData();
                 //controllo sul valore letto
                if(received>=0 && received<=255)
                {
                    // faccio partire il TIMER, che parte inizializzato e attiva Timer_Enable () [vedi dichiarazione funzione]
                    Timer_Start();
                    state=GREEN_BYTE_RECEIVED;
                    //UART_PutString("Inserisci BLUE:\r\n");
                }
            }        
        }
        
        if(state==GREEN_BYTE_RECEIVED)
        {
            //imposto il colore verde
            PWM_RG_WriteCompare2(255-received);
            // se ho ricevuto un messaggio la flag rec è stata messa a 1
            if (rec == 1)
            {
                rec=0;
                //leggo il messaggio
                received = UART_ReadRxData();
                //controllo sul valore letto
                if(received>=0 && received<=255)
                {
                    // faccio partire il TIMER, che parte inizializzato e attiva Timer_Enable () [vedi dichiarazione funzione]
                    Timer_Start();
                    state=BLUE_BYTE_RECEIVED;
                    //UART_PutString("Inserisci TAIL:\r\n");
                }
            }        
        }
        
        if(state==BLUE_BYTE_RECEIVED)
        {
            //imposto il colore blu
            PWM_B_WriteCompare(255-received);
            // se ho ricevuto un messaggio la flag rec è stata messa a 1
            if (rec == 1)
            {
                rec=0;
                //leggo il messaggio
                received = UART_ReadRxData();
                //se il byte letto coincide con il TAIL_BYTE
                if(received==192)
                {
                    state=TAIL_BYTE_RECEIVED;
                }
            }        
        }
        
        if(state==TAIL_BYTE_RECEIVED)
        {
            state=IDLE_STATE;
            //UART_PutString("Inserisci HEADER:\r\n");
        }    
    }
}

    
    
/* [] END OF FILE */
