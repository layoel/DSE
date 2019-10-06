#ifndef __SERVO__H__
#define __SERVO__H__
#include <project.h>
#define OPEN 18000
#define MAX 15500
#define CLOSE 19000
    
    
void ServoStart()
{
    PWM_ServoP_Start();
    PWM_ServoT_Start();
    Clock_3_Start();
    Clock_4_Start();
}

void openDoor()
{
    PWM_ServoP_WriteCompare(MAX);
}

void openTrap()
{
    PWM_ServoT_WriteCompare(MAX);
}

void closeDoor()
{
    PWM_ServoP_WriteCompare(CLOSE);
}

void closeTrap()
{
    PWM_ServoT_WriteCompare(CLOSE);
}



    
#endif