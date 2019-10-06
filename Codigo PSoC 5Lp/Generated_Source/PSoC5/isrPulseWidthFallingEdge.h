/*******************************************************************************
* File Name: isrPulseWidthFallingEdge.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_isrPulseWidthFallingEdge_H)
#define CY_ISR_isrPulseWidthFallingEdge_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void isrPulseWidthFallingEdge_Start(void);
void isrPulseWidthFallingEdge_StartEx(cyisraddress address);
void isrPulseWidthFallingEdge_Stop(void);

CY_ISR_PROTO(isrPulseWidthFallingEdge_Interrupt);

void isrPulseWidthFallingEdge_SetVector(cyisraddress address);
cyisraddress isrPulseWidthFallingEdge_GetVector(void);

void isrPulseWidthFallingEdge_SetPriority(uint8 priority);
uint8 isrPulseWidthFallingEdge_GetPriority(void);

void isrPulseWidthFallingEdge_Enable(void);
uint8 isrPulseWidthFallingEdge_GetState(void);
void isrPulseWidthFallingEdge_Disable(void);

void isrPulseWidthFallingEdge_SetPending(void);
void isrPulseWidthFallingEdge_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the isrPulseWidthFallingEdge ISR. */
#define isrPulseWidthFallingEdge_INTC_VECTOR            ((reg32 *) isrPulseWidthFallingEdge__INTC_VECT)

/* Address of the isrPulseWidthFallingEdge ISR priority. */
#define isrPulseWidthFallingEdge_INTC_PRIOR             ((reg8 *) isrPulseWidthFallingEdge__INTC_PRIOR_REG)

/* Priority of the isrPulseWidthFallingEdge interrupt. */
#define isrPulseWidthFallingEdge_INTC_PRIOR_NUMBER      isrPulseWidthFallingEdge__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable isrPulseWidthFallingEdge interrupt. */
#define isrPulseWidthFallingEdge_INTC_SET_EN            ((reg32 *) isrPulseWidthFallingEdge__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the isrPulseWidthFallingEdge interrupt. */
#define isrPulseWidthFallingEdge_INTC_CLR_EN            ((reg32 *) isrPulseWidthFallingEdge__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the isrPulseWidthFallingEdge interrupt state to pending. */
#define isrPulseWidthFallingEdge_INTC_SET_PD            ((reg32 *) isrPulseWidthFallingEdge__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the isrPulseWidthFallingEdge interrupt. */
#define isrPulseWidthFallingEdge_INTC_CLR_PD            ((reg32 *) isrPulseWidthFallingEdge__INTC_CLR_PD_REG)


#endif /* CY_ISR_isrPulseWidthFallingEdge_H */


/* [] END OF FILE */
