#ifndef __POTENCIOMETROS__H__
#define __POTENCIOMETROS__H__
#include <project.h>
    

void Potentiometer_Init()
{
    AMux_Init();
    ADC_DelSig_Start();
}
    
    
float32 measurePotentiometer(uint8 sel)
{
    AMux_Select(sel);
    CyDelay(20);
    ADC_DelSig_StartConvert();
    
    ADC_DelSig_IsEndConversion(ADC_DelSig_WAIT_FOR_RESULT);
    
    int32 output = ADC_DelSig_GetResult32(); 
    return (5.000000/1048576)*output;
}

#endif 