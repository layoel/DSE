/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include <lcd03.h>
#include <hcsr04.h>
#include <tone.h>
#include <potenciometros.h>
#include <servo.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define PASSLENGTH 3
#define MINDISTANCE 6 //en centimetros
#define OPENTIME 5 //en segundos


volatile bool byteReady = false;
volatile bool _1sec = false;
volatile bool _0_3sec = false; 
char byte;
enum state {init, config, measure, countDown, unlockdoor, unlocktrap, ajustarPass, ajustarCountDown, ajustarTries, opendoor, opentrap, closedoor, closetrap, error};


CY_ISR(ISR_ByteReceived)
{
  byteReady = true;
  byte = UART_GetChar();
}

CY_ISR(OneSec)
{
    _1sec = true;
}

CY_ISR(CheckPot)
{
    _0_3sec = true;
}



int main(void)
{
    float32 centimetros = 65535;
    bool passwordSet = false, trySet = false, timeSet = false, trapOpen = false, doorOpen = false;
    uint8 aux = 0;
    bool correcta = false;
    char  errorMsg[20], str[20], passToTone[PASSLENGTH][9];
    enum state estado = init;
    
    //Variables de configuracion
    uint8 password[PASSLENGTH];
    uint8 tries;
    uint16 timeCountDown;
    
    //Variables temporales 
    uint8 numFails = 0;
    uint16 secondsleft;
    uint8 currentPass[PASSLENGTH];
    float32 po1 , po2, po3;
    
    
    CyGlobalIntEnable;
    ISR_ByteReceived_StartEx(&ISR_ByteReceived);
    OneSec_StartEx(&OneSec);
    CheckPot_StartEx(&CheckPot);
    UART_Start();
    LCD_Start();
    LCD_Clear();
    Init_hcsr04();
    Potentiometer_Init();
    ServoStart();
    closeDoor();
    closeTrap();
    
    //Esperamos un segunfo antes de comenzar con la ejecución 
    CyDelay(1000);

 
    for(;;)
    {
        switch(estado){
            case init:
                if (byteReady){
                    byteReady = false;
                   
                    if (byte != 'A' ){
                        sprintf(errorMsg, "Error estableciendo\n\rconexion con ESP32");
                        estado = error;
                    }
                    else {
                        UART_PutChar('A');
                        LCD_Clear();
                        LCD_Print(1,1, "Comunicacion Establecida");
                        CyDelay(1000);
                        
                        passwordSet = trySet = timeSet = false;
                        estado = config;
                    }
                }
                break;
                
                
                
            case config:
                
                if (_1sec){
                    _1sec = false;
                    LCD_Clear();
                    LCD_Print(1,1,"Configurando");
                }
                if (!passwordSet || !trySet || !timeSet || doorOpen || trapOpen){
                    if (byteReady){
                        byteReady = false;
                        
                        switch(byte){
                            case 'C':
                                aux = 0;
                                for (int i = 0; i < PASSLENGTH; ++i)
                                    password[i] = 0;
                                estado = ajustarPass;
                                break;
                            case 'F':
                               
                                aux = 0;
                                timeCountDown = 0;
                                estado = ajustarCountDown;
                                break;
                            case 'N':
                                
                                aux = tries = 0;
                                estado = ajustarTries;
                                break;
                            case 'T':
                                estado = opentrap;
                                break;
                            case 'P':
                                estado = opendoor;
                                break;
                            case 't':
                                estado = closetrap;
                                break;
                            case 'p':
                                estado = closedoor;
                                break;
                            
                        }
                        UART_PutChar('A');
                    }    
                }else{
                    LCD_Clear();
                    LCD_Print(1,1, "Configuracion realizada con exito");
                    numFails = 0;
                    CyDelay(1000);
                    estado = measure;
                }
                break;
                
                
            case measure:
                    if (_1sec){
                        _1sec = false;
                        centimetros = Measure_hcsr04();
                        LCD_Clear();
                        sprintf(str, "Midiendo");
                        LCD_Print(1,1, str);
                    }
                    
                    if (centimetros < MINDISTANCE){
                        secondsleft = timeCountDown;
                        ++numFails;
                        LCD_Clear();
                        estado = countDown;
                    }
                    
                    if (byteReady){
                        byteReady = false;
                        
                        switch(byte){
                            case 'C':
                                
                                aux = 0;
                                for (int i = 0; i < PASSLENGTH; ++i)
                                    password[i] = 0;
                                estado = ajustarPass;
                                break;
                            case 'F':
                                
                                aux = 0;
                                timeCountDown = 0;
                                estado = ajustarCountDown;
                                break;
                            case 'N':
                               
                                aux = tries = 0;
                                estado = ajustarTries;
                                break;
                            case 'T':
                                estado = opentrap;
                                break;
                            case 'P':
                                estado = opendoor;
                                break;
                            case 't':
                                estado = closetrap;
                                break;
                            case 'p':
                                estado = closedoor;
                                break;
                            
                        }
                        UART_PutChar('A');
                    }    
                    
                break;
                    
                    
                    
            case countDown:     
                    if (_1sec){
                        _1sec = false;
                        LCD_Print(1,18,"   ");
                        sprintf(str, "Tiempo restante: %d", secondsleft--);
                        LCD_Print(1,1, str);
                        sprintf(str, "Intentos restantes:%d", tries - numFails);
                        LCD_Print(2,1, str);
                    }
                    
                    if (_0_3sec){
                        _0_3sec = false;
                        po1 = measurePotentiometer(0);
                        po2 = measurePotentiometer(1);
                        po3 = measurePotentiometer(2);
                        
                        currentPass[0] = (po1 * 2) + 1;
                        currentPass[1] = (po2 * 2) + 1;
                        currentPass[2] = (po3 * 2) + 1;
                        
                        if ( (currentPass[2] == password[0]) && (currentPass[1] == password[1]) && (currentPass[0] == password[2]) )
                            correcta = true;
                        
                        for (int i = 0; i < PASSLENGTH; ++i){
                            switch(currentPass[i]){
                                case 1:
                                    sprintf(passToTone[i], "do ");
                                    break;
                                case 2:
                                    sprintf(passToTone[i], "do#");
                                    break;
                                case 3:
                                    sprintf(passToTone[i], "re ");
                                    break;
                                case 4:
                                    sprintf(passToTone[i], "re#");
                                    break;
                                case 5:
                                    sprintf(passToTone[i], "mi ");
                                    break;
                                case 6:
                                    sprintf(passToTone[i], "fa ");
                                    break;
                                case 7:
                                    sprintf(passToTone[i], "fa#");
                                    break;
                                case 8:
                                    sprintf(passToTone[i], "sol ");
                                    break;
                                case 9:
                                    sprintf(passToTone[i], "sol#");
                                    break;
                                case 10:
                                    sprintf(passToTone[i], "la ");
                                    break;
                            }
                        }
                        
                        sprintf(str, "p1:%sp2:%sp3:%s", passToTone[0], passToTone[1], passToTone[2]);
                        LCD_Print(4, 1, str);
                    }
                    
                    if (correcta){
                         correcta = false;
                        
                         PlayTones(currentPass, PASSLENGTH);
                         secondsleft = OPENTIME;
                         estado = unlockdoor;
                    }else if (secondsleft == 0 ){
                        
                        PlayTones(currentPass, PASSLENGTH);
                        /*sprintf(str, "%d %d %d | %d %d %d", password[0], password[1], password[2], currentPass[0], currentPass[1], currentPass[2]);
                        LCD_Print(4,1, str);*/
                        CyDelay(2000);
                        if (numFails == tries){
                            secondsleft = OPENTIME;
                            estado = unlocktrap;
                        }else{
                            centimetros = 65535;
                            estado = measure;
                        }
                    }
                
                break;
                
                
                
            case unlockdoor:
                    
                if (secondsleft == OPENTIME){
                    //ABRIR PUERTA
                    openDoor();
                    LCD_Clear();
                    sprintf(str, "Puerta abierta");
                    LCD_Print(1,1, str);
                    
                }
                
                if (_1sec){
                    _1sec = false;
                    --secondsleft;
                }
                
                if (secondsleft == 0){
                    //CIERRO PUERTA
                    closeDoor();
                    LCD_Clear();
                    sprintf(str, "Puerta cerrada");
                    LCD_Print(1,1, str);
                    
                    centimetros = 65535;
                    numFails = 0;
                    estado = measure;
                }
                break;
                
                
            case unlocktrap:
                if (secondsleft == OPENTIME){
                    //ABRIR TRAMPILLA
                    openTrap();
                    LCD_Clear();
                    sprintf(str, "Trampilla abierta");
                    LCD_Print(1,1, str);
                    
                }
                
                if (_1sec){
                    _1sec = false;
                    --secondsleft;
                }
                
                if (secondsleft == 0){
                    //CIERRO TRAMPILLA
                    closeTrap();
                    LCD_Clear();
                    sprintf(str, "Trampilla cerrada");
                    LCD_Print(1,1, str);
                    
                    centimetros = 65535;
                    numFails = 0;
                    estado = measure;
                }
                break;
                
                
            case ajustarCountDown:
                if (byteReady){
                    byteReady = false;
                    
                    if ((byte < '0' || byte > '9') && byte != 'f'){
                        sprintf(errorMsg, "En numero de intentos\n\rValor no numerico");
                        LCD_Clear();
                        estado = error;
                    }
                    else if (byte == 'f'){
                        LCD_Clear();
                        LCD_Print(1, 1, "CountDown ajustado");
                        CyDelay(1000);
                        LCD_Clear();
                        estado = config;
                        timeSet = true;
                    }else timeCountDown += (byte - '0') * pow(10.0, aux++); //Aqui enviar digitos tal cual
                    
                   /* sprintf(str, ":%d", timeCountDown);
                    LCD_Print(1,1, str);*/
                    UART_PutChar('A');
                }
                break;
            case ajustarPass:
                if (byteReady){
                    byteReady = false;
                    
                    if (aux > PASSLENGTH){
                        sprintf(errorMsg, "Contrasenia muy larga");
                        LCD_Clear();
                        estado = error;
                    }
                    else if (byte == 'c'){
                        if (aux < PASSLENGTH){
                            sprintf(errorMsg, "Contrasenia corta");
                            estado = error;
                        }else{
                            LCD_Clear();
                            LCD_Print(1, 1, "Ajustada Contrasenia");
                            CyDelay(1000);
                            LCD_Clear();
                            passwordSet = true;
                            estado = config;
                        }
                    }
                    else password[aux++] = (byte - '0') + 1;
                    /*sprintf(str, ":%d", password[aux++]);
                    LCD_Print(1,1, str);*/
                    UART_PutChar('A');
                }
                break;
            case ajustarTries:
                 if (byteReady){
                    byteReady = false;
                    
                    if ((byte < '0' || byte > '9') && byte != 'n'){
                        sprintf(errorMsg, "En numero de intentos\n\rValor no numerico");
                        LCD_Clear();
                        estado = error;
                    }else if (byte == 'n'){
                        LCD_Clear();
                        LCD_Print(1, 1, "Intentos Ajustados");
                        CyDelay(1000);
                        LCD_Clear();
                        estado = config;
                        trySet = true;
                    }else tries += (byte - '0') * pow(10.0, aux++); //Aqui enviar digitos tal cual
                    
                    /*sprintf(str, ":%d", tries);
                    LCD_Print(1,1, str);*/
                    UART_PutChar('A');
                }
                break;
            
            case opendoor:
                LCD_Clear();
                LCD_Print(1,1, "Puerta Abierta");
                openDoor();
                doorOpen = true;
                estado = config;
                break;
                
                
            case opentrap:
                LCD_Clear();
                LCD_Print(1,1, "Trampilla Abierta");
                openTrap();
                trapOpen = true;
                estado = config;
                break;
                
            case closedoor:
                LCD_Clear();
                LCD_Print(1,1, "Puerta Cerrada");
                closeDoor();
                doorOpen = false;
                estado = config;
                break;
                
            case closetrap:
                LCD_Clear();
                LCD_Print(1,1, "Trampilla Cerrada");
                closeTrap();
                trapOpen = false;
                estado = config;
                break;
            
            case error:
                ErrorLed_Write(HIGH);
                LCD_Print(1,1, errorMsg);
                LCD_Print(4,1, "Pulsar S para seguir");
                if(byteReady){
                    byteReady = false;
                    if (byte == 'S'){
                        ErrorLed_Write(LOW);
                        LCD_Clear();
                        estado = config;
                    }
                }
                break;
        }
    }
}

/* [] END OF FILE */
