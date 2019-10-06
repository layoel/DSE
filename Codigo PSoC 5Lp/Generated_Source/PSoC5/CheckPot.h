/*******************************************************************************
* File Name: CheckPot.h
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
#if !defined(CY_ISR_CheckPot_H)
#define CY_ISR_CheckPot_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void CheckPot_Start(void);
void CheckPot_StartEx(cyisraddress address);
void CheckPot_Stop(void);

CY_ISR_PROTO(CheckPot_Interrupt);

void CheckPot_SetVector(cyisraddress address);
cyisraddress CheckPot_GetVector(void);

void CheckPot_SetPriority(uint8 priority);
uint8 CheckPot_GetPriority(void);

void CheckPot_Enable(void);
uint8 CheckPot_GetState(void);
void CheckPot_Disable(void);

void CheckPot_SetPending(void);
void CheckPot_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the CheckPot ISR. */
#define CheckPot_INTC_VECTOR            ((reg32 *) CheckPot__INTC_VECT)

/* Address of the CheckPot ISR priority. */
#define CheckPot_INTC_PRIOR             ((reg8 *) CheckPot__INTC_PRIOR_REG)

/* Priority of the CheckPot interrupt. */
#define CheckPot_INTC_PRIOR_NUMBER      CheckPot__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable CheckPot interrupt. */
#define CheckPot_INTC_SET_EN            ((reg32 *) CheckPot__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the CheckPot interrupt. */
#define CheckPot_INTC_CLR_EN            ((reg32 *) CheckPot__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the CheckPot interrupt state to pending. */
#define CheckPot_INTC_SET_PD            ((reg32 *) CheckPot__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the CheckPot interrupt. */
#define CheckPot_INTC_CLR_PD            ((reg32 *) CheckPot__INTC_CLR_PD_REG)


#endif /* CY_ISR_CheckPot_H */


/* [] END OF FILE */
