/*******************************************************************************
* File Name: OneSec.h
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
#if !defined(CY_ISR_OneSec_H)
#define CY_ISR_OneSec_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void OneSec_Start(void);
void OneSec_StartEx(cyisraddress address);
void OneSec_Stop(void);

CY_ISR_PROTO(OneSec_Interrupt);

void OneSec_SetVector(cyisraddress address);
cyisraddress OneSec_GetVector(void);

void OneSec_SetPriority(uint8 priority);
uint8 OneSec_GetPriority(void);

void OneSec_Enable(void);
uint8 OneSec_GetState(void);
void OneSec_Disable(void);

void OneSec_SetPending(void);
void OneSec_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the OneSec ISR. */
#define OneSec_INTC_VECTOR            ((reg32 *) OneSec__INTC_VECT)

/* Address of the OneSec ISR priority. */
#define OneSec_INTC_PRIOR             ((reg8 *) OneSec__INTC_PRIOR_REG)

/* Priority of the OneSec interrupt. */
#define OneSec_INTC_PRIOR_NUMBER      OneSec__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable OneSec interrupt. */
#define OneSec_INTC_SET_EN            ((reg32 *) OneSec__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the OneSec interrupt. */
#define OneSec_INTC_CLR_EN            ((reg32 *) OneSec__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the OneSec interrupt state to pending. */
#define OneSec_INTC_SET_PD            ((reg32 *) OneSec__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the OneSec interrupt. */
#define OneSec_INTC_CLR_PD            ((reg32 *) OneSec__INTC_CLR_PD_REG)


#endif /* CY_ISR_OneSec_H */


/* [] END OF FILE */
