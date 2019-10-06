#ifndef __HCSR04__
    #define __HCSR04_
    /*
    * Autor: Hulidex
    * Fecha de última modificación: 17/04/2018
    * Probado en: PSoC 5LP, El modelo del sensor de ultrasonidos es HC-SR04 fabricado por ELEGOO
    * DESCRIPCIÓN GENERAL: Biblioteca para controlar un sensor de ultra sonidos HC-SR04, para ello se hace uso de un
    * elemento "Timer_v2_80" al cual le conectamos en las entradas "Trigger" y "Capture" un "digital_input_pin" donde
    * se conecta la patilla echo del sensor.
    *
    * REQUERIMIENROS: Dentro del esquemático Necesitaremos agregar los siguientes componentes:
    *   -> Timer_v2_80 con las siguientes opciones de configuración:
    *       -- Resolution -> 16-Bit
    *       -- Implementation -> UDB
    *       -- Period -> Pulsamos botón "Max", lo que debe poner el periodo a 65536
    *       -- Trigger Mode -> Rising Edge
    *       -- Capture Mode -> Falling Edge y NO habilitamos la casilla "Enable Capture Counter"
    *       -- Enable Mode -> Software Only
    *       -- Run Mode -> Continuous
    *       -- Interrups -> Todas las casillas deshabilitadas menos la de "On Capture[1-4]" con valor 1.
    *       -- Le conectaremos un Reloj a 1092267 Hz a su entrada "Clock" de esta forma el periodo sobre el que el timer cuenta es de 60ms aprox.
    *       -- Le conectaremos un componente "Interrupt [v1.70]" conectado a la salida del timer "Interrupt" con la siguiente configuración:
    *           -- IterruptType -> "RISING_EDGE"
    *           -- El nombre de este componente DEBE ser "isrPulseWidthFallingEdge".
    *       -- EL TIMER DEBE LLAMARSE CON EL SIGUIENTE NOMBRE -> "TimerCountWidth"
    *       -- ES MUY IMPORTANTE QUE LA SALIDA del timer "capture_out" esté conectada a la ENTRADA del timer "Reset"
    *
    *   -> Digital_input_pin_pin donde conectaremos la patilla "Echo" del sensor. El nombre del pin es SR04Echo.
    *       -- En la columna "Type" solo marcamos las casilla "digital input" y "HW connection".
    *       -- En la columna "Drive mode" lo ponemos en "High impedance digital".
    *       -- En la columna "Initial drive state" lo ponemos en "low(0)"
    *   -> Digital_output_pin donde conectaremos la patilla "Trigger" del sensor. El nombre del pin DEBE ser SR04Trig con la siguiente configuración:
    *       -- En la columna "Type" solo marcamos la casilla "digital output".
    *       -- En la columna "Drive mode" lo ponemos en "Strong Drive".
    *       -- En la columna "Initial drive state" lo ponemos en "low(0)"
    *       
    */
    #include <project.h>
    #include<stdio.h>
    
    
    //PARAMETROS:
    #define VSOUND  34000 //Velocidad del sonido en cm/s aproximada (ya que varía en función del medio de propagación).
    #define FREQ    1092267//Frecuencia de funcionamiento del reloj conectado al timer, con el valor 1092267 y Resolución del timer de 16 bits, nuestro periodo es de 60ms
    #define RESOL   65536//Resolución del timer
    #define LOW 0
    #define HIGH 1
    
    uint32 interval;
    
    
    //MÉTODOS:
    /*
    * DESCRIPCIÓN: Inicia todos los componentes necesarios para utilizar el sensor
    */
    void Init_hcsr04();
    
     /*
    * DESCRIPCIÓN: deshabilita el sensor el sensor
    */
    void Stop_hcsr04();
    
    
    /*
    * DESCRIPCIÓN: Indica al sensor que realice una medida.
    */
    void InitMeasure_hcsr04();
    
    /*
    * DESCRIPCIÓN: Recoje los datos de la última medida en centímetros
    */
    float32 GetCentimeters_hcsr04();
    
    /*
    * DESCRIPCIÓN: Recoje los datos de la última medida en Metros
    */
    float32 GetMeters_hcsr04();
    
    /*
    * DESCRIPCIÓN: Toma una medida, para ello: Indica al sensor que mida, espera un tiempo suficiente para que la medida
    * esté lista, y la retorna en centimetros.
    */
    float32 Measure_hcsr04();
    
    
    
    
    
    //IMPLEMENTACION

    CY_ISR(isrPulseWidthFallingEdge)
    {
        interval =  TimerCountWidth_ReadCounter();
        TimerCountWidth_ReadControlRegister();
        TimerCountWidth_ClearFIFO();
    }


    void Init_hcsr04()
    {
        isrPulseWidthFallingEdge_StartEx(&isrPulseWidthFallingEdge);
        TimerCountWidth_Start();
    }
    
     void Stop_hcsr04()
    {
       isrPulseWidthFallingEdge_Stop();
       TimerCountWidth_Stop();
    }

    void InitMeasure_hcsr04()
    {
      SR04Trig_Write(HIGH);
      CyDelayUs(10);
      SR04Trig_Write(LOW);
    }
    
    float32 GetCentimeters_hcsr04()
    {
        return (RESOL-interval)*(1.0/FREQ)*VSOUND/2;
    }
    
    float32 GetMeters_hcsr04()
    {
        return GetCentimeters_hcsr04()/100;
    }
    
    float32 Measure_hcsr04()
    {   
        InitMeasure_hcsr04();//Iniciamos la medida
        CyDelay(70);//Esperamos un tiempo suficiente
        
        return GetCentimeters_hcsr04();
    }
#endif
