/*******************************************************************************
* File Name: ErrorLed.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_ErrorLed_H) /* Pins ErrorLed_H */
#define CY_PINS_ErrorLed_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ErrorLed_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ErrorLed__PORT == 15 && ((ErrorLed__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ErrorLed_Write(uint8 value);
void    ErrorLed_SetDriveMode(uint8 mode);
uint8   ErrorLed_ReadDataReg(void);
uint8   ErrorLed_Read(void);
void    ErrorLed_SetInterruptMode(uint16 position, uint16 mode);
uint8   ErrorLed_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ErrorLed_SetDriveMode() function.
     *  @{
     */
        #define ErrorLed_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ErrorLed_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ErrorLed_DM_RES_UP          PIN_DM_RES_UP
        #define ErrorLed_DM_RES_DWN         PIN_DM_RES_DWN
        #define ErrorLed_DM_OD_LO           PIN_DM_OD_LO
        #define ErrorLed_DM_OD_HI           PIN_DM_OD_HI
        #define ErrorLed_DM_STRONG          PIN_DM_STRONG
        #define ErrorLed_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ErrorLed_MASK               ErrorLed__MASK
#define ErrorLed_SHIFT              ErrorLed__SHIFT
#define ErrorLed_WIDTH              1u

/* Interrupt constants */
#if defined(ErrorLed__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ErrorLed_SetInterruptMode() function.
     *  @{
     */
        #define ErrorLed_INTR_NONE      (uint16)(0x0000u)
        #define ErrorLed_INTR_RISING    (uint16)(0x0001u)
        #define ErrorLed_INTR_FALLING   (uint16)(0x0002u)
        #define ErrorLed_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ErrorLed_INTR_MASK      (0x01u) 
#endif /* (ErrorLed__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ErrorLed_PS                     (* (reg8 *) ErrorLed__PS)
/* Data Register */
#define ErrorLed_DR                     (* (reg8 *) ErrorLed__DR)
/* Port Number */
#define ErrorLed_PRT_NUM                (* (reg8 *) ErrorLed__PRT) 
/* Connect to Analog Globals */                                                  
#define ErrorLed_AG                     (* (reg8 *) ErrorLed__AG)                       
/* Analog MUX bux enable */
#define ErrorLed_AMUX                   (* (reg8 *) ErrorLed__AMUX) 
/* Bidirectional Enable */                                                        
#define ErrorLed_BIE                    (* (reg8 *) ErrorLed__BIE)
/* Bit-mask for Aliased Register Access */
#define ErrorLed_BIT_MASK               (* (reg8 *) ErrorLed__BIT_MASK)
/* Bypass Enable */
#define ErrorLed_BYP                    (* (reg8 *) ErrorLed__BYP)
/* Port wide control signals */                                                   
#define ErrorLed_CTL                    (* (reg8 *) ErrorLed__CTL)
/* Drive Modes */
#define ErrorLed_DM0                    (* (reg8 *) ErrorLed__DM0) 
#define ErrorLed_DM1                    (* (reg8 *) ErrorLed__DM1)
#define ErrorLed_DM2                    (* (reg8 *) ErrorLed__DM2) 
/* Input Buffer Disable Override */
#define ErrorLed_INP_DIS                (* (reg8 *) ErrorLed__INP_DIS)
/* LCD Common or Segment Drive */
#define ErrorLed_LCD_COM_SEG            (* (reg8 *) ErrorLed__LCD_COM_SEG)
/* Enable Segment LCD */
#define ErrorLed_LCD_EN                 (* (reg8 *) ErrorLed__LCD_EN)
/* Slew Rate Control */
#define ErrorLed_SLW                    (* (reg8 *) ErrorLed__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ErrorLed_PRTDSI__CAPS_SEL       (* (reg8 *) ErrorLed__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ErrorLed_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ErrorLed__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ErrorLed_PRTDSI__OE_SEL0        (* (reg8 *) ErrorLed__PRTDSI__OE_SEL0) 
#define ErrorLed_PRTDSI__OE_SEL1        (* (reg8 *) ErrorLed__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ErrorLed_PRTDSI__OUT_SEL0       (* (reg8 *) ErrorLed__PRTDSI__OUT_SEL0) 
#define ErrorLed_PRTDSI__OUT_SEL1       (* (reg8 *) ErrorLed__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ErrorLed_PRTDSI__SYNC_OUT       (* (reg8 *) ErrorLed__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ErrorLed__SIO_CFG)
    #define ErrorLed_SIO_HYST_EN        (* (reg8 *) ErrorLed__SIO_HYST_EN)
    #define ErrorLed_SIO_REG_HIFREQ     (* (reg8 *) ErrorLed__SIO_REG_HIFREQ)
    #define ErrorLed_SIO_CFG            (* (reg8 *) ErrorLed__SIO_CFG)
    #define ErrorLed_SIO_DIFF           (* (reg8 *) ErrorLed__SIO_DIFF)
#endif /* (ErrorLed__SIO_CFG) */

/* Interrupt Registers */
#if defined(ErrorLed__INTSTAT)
    #define ErrorLed_INTSTAT            (* (reg8 *) ErrorLed__INTSTAT)
    #define ErrorLed_SNAP               (* (reg8 *) ErrorLed__SNAP)
    
	#define ErrorLed_0_INTTYPE_REG 		(* (reg8 *) ErrorLed__0__INTTYPE)
#endif /* (ErrorLed__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ErrorLed_H */


/* [] END OF FILE */
