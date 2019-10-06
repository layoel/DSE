#ifndef __GENTONE__H__
#define __GENTONE__H__

#include <project.h>
#include <math.h>
#define REF 440 //FRECUENCIA DE REFERENCIA EN HZ (el tono LA en la 4 octava)
#define CLOCK 24 // Frecuencia en MHz del reloj que usa el PWM para generar sus señales a partir de este.

void StartTone()
{
     PWM_Start();
}

void StopTone()
{
     PWM_Stop();
}


//Función para calcular el valor al que el PWM se desborda generando una frecuencia aproxima a la dada en
//en su primer parámetro.
//El parametro freq_hz debe ir en HZ, no en multiplos ni en submultiplos
double calculateFreq(uint8 tone, uint8 octave)
{
    return REF * exp( ((octave-4)+((tone-10)/12.0))* log(2) );
}

uint16 calculatePeriod(double freq_hz)
{
    double TcicloDeseado = (1.0/freq_hz) * 1e9;
    double TcicloReloj = (1.0/(CLOCK*1e6)) * 1e9;
    
    return (uint16)(TcicloDeseado/TcicloReloj) + 1;
}

void setTone(uint8 tone, uint8 octave, uint16 volume){
    uint16 period = calculatePeriod(calculateFreq(tone, octave)); 
    
    PWM_WritePeriod(period);
    PWM_WriteCompare(period/volume);
}

void PlayTones(uint8 * tones, uint8 size)
{
    for (int i = 0; i < size; ++i){
        StartTone();
        setTone(tones[i], 4, 2);
        CyDelay(500);
        StopTone();
    }

}
    
    
    
    
#endif
/* [] END OF FILE */
