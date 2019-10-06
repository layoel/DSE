#ifndef __LCD03__H__
#define __LCD03__H__

#include <project.h>

#define LCD03 0x63 //Direccion LCD
#define WRITE 0x00 
#define COMMANDREG 0x00
#define MAXCOLUMNS 20 //Número máximo de columnas de la pantalla 
#define MAXFILES    4 //Número máximo de filas
#define delay 10

void LCD_Start()
{
    I2C_Start();
    CyDelay(500);
}

    
    
void LCD_Clear()
{
    I2C_MasterSendStart(LCD03, WRITE);
    I2C_MasterWriteByte(COMMANDREG);
    CyDelay(delay);
    I2C_MasterWriteByte(12);
    I2C_MasterSendStop();
}

void LCD_LightOn()
{
    I2C_MasterSendStart(LCD03, WRITE);
    I2C_MasterWriteByte(COMMANDREG);
    CyDelay(delay);
    I2C_MasterWriteByte(19);
    I2C_MasterSendStop();
}


void LCD_LightOff()
{
    I2C_MasterSendStart(LCD03, WRITE);
    I2C_MasterWriteByte(COMMANDREG);
    CyDelay(delay);
    I2C_MasterWriteByte(20);
    I2C_MasterSendStop();
}

void LCD_Print(uint8 fil, uint8 col, const char *str)
{
    int i, charsleft;
    
    if ((fil < 1) || (fil > MAXFILES))
        fil = 1;
    if ((col < 1) ||(col > MAXCOLUMNS))
        col = 1;
    
    I2C_MasterSendStart(LCD03, WRITE);
    I2C_MasterWriteByte(COMMANDREG);  
    CyDelay(delay);
    I2C_MasterWriteByte(3);
    CyDelay(delay);
    I2C_MasterWriteByte(fil);
    CyDelay(delay);
    I2C_MasterWriteByte(col);
    
    charsleft = MAXFILES*MAXCOLUMNS - ((fil-1)*MAXCOLUMNS+col-1);
    for (i  = 0; str[i] != '\0' && charsleft > 0; ++i, --charsleft ){
        CyDelay(delay);
        I2C_MasterWriteByte(str[i]);
    }
    
     I2C_MasterSendStop();
    
}

#endif