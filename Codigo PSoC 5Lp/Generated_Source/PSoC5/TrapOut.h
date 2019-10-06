/*******************************************************************************
* File Name: TrapOut.h  
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

#if !defined(CY_PINS_TrapOut_H) /* Pins TrapOut_H */
#define CY_PINS_TrapOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "TrapOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 TrapOut__PORT == 15 && ((TrapOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    TrapOut_Write(uint8 value);
void    TrapOut_SetDriveMode(uint8 mode);
uint8   TrapOut_ReadDataReg(void);
uint8   TrapOut_Read(void);
void    TrapOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   TrapOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the TrapOut_SetDriveMode() function.
     *  @{
     */
        #define TrapOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define TrapOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define TrapOut_DM_RES_UP          PIN_DM_RES_UP
        #define TrapOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define TrapOut_DM_OD_LO           PIN_DM_OD_LO
        #define TrapOut_DM_OD_HI           PIN_DM_OD_HI
        #define TrapOut_DM_STRONG          PIN_DM_STRONG
        #define TrapOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define TrapOut_MASK               TrapOut__MASK
#define TrapOut_SHIFT              TrapOut__SHIFT
#define TrapOut_WIDTH              1u

/* Interrupt constants */
#if defined(TrapOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in TrapOut_SetInterruptMode() function.
     *  @{
     */
        #define TrapOut_INTR_NONE      (uint16)(0x0000u)
        #define TrapOut_INTR_RISING    (uint16)(0x0001u)
        #define TrapOut_INTR_FALLING   (uint16)(0x0002u)
        #define TrapOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define TrapOut_INTR_MASK      (0x01u) 
#endif /* (TrapOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TrapOut_PS                     (* (reg8 *) TrapOut__PS)
/* Data Register */
#define TrapOut_DR                     (* (reg8 *) TrapOut__DR)
/* Port Number */
#define TrapOut_PRT_NUM                (* (reg8 *) TrapOut__PRT) 
/* Connect to Analog Globals */                                                  
#define TrapOut_AG                     (* (reg8 *) TrapOut__AG)                       
/* Analog MUX bux enable */
#define TrapOut_AMUX                   (* (reg8 *) TrapOut__AMUX) 
/* Bidirectional Enable */                                                        
#define TrapOut_BIE                    (* (reg8 *) TrapOut__BIE)
/* Bit-mask for Aliased Register Access */
#define TrapOut_BIT_MASK               (* (reg8 *) TrapOut__BIT_MASK)
/* Bypass Enable */
#define TrapOut_BYP                    (* (reg8 *) TrapOut__BYP)
/* Port wide control signals */                                                   
#define TrapOut_CTL                    (* (reg8 *) TrapOut__CTL)
/* Drive Modes */
#define TrapOut_DM0                    (* (reg8 *) TrapOut__DM0) 
#define TrapOut_DM1                    (* (reg8 *) TrapOut__DM1)
#define TrapOut_DM2                    (* (reg8 *) TrapOut__DM2) 
/* Input Buffer Disable Override */
#define TrapOut_INP_DIS                (* (reg8 *) TrapOut__INP_DIS)
/* LCD Common or Segment Drive */
#define TrapOut_LCD_COM_SEG            (* (reg8 *) TrapOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define TrapOut_LCD_EN                 (* (reg8 *) TrapOut__LCD_EN)
/* Slew Rate Control */
#define TrapOut_SLW                    (* (reg8 *) TrapOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define TrapOut_PRTDSI__CAPS_SEL       (* (reg8 *) TrapOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define TrapOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) TrapOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define TrapOut_PRTDSI__OE_SEL0        (* (reg8 *) TrapOut__PRTDSI__OE_SEL0) 
#define TrapOut_PRTDSI__OE_SEL1        (* (reg8 *) TrapOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define TrapOut_PRTDSI__OUT_SEL0       (* (reg8 *) TrapOut__PRTDSI__OUT_SEL0) 
#define TrapOut_PRTDSI__OUT_SEL1       (* (reg8 *) TrapOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define TrapOut_PRTDSI__SYNC_OUT       (* (reg8 *) TrapOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(TrapOut__SIO_CFG)
    #define TrapOut_SIO_HYST_EN        (* (reg8 *) TrapOut__SIO_HYST_EN)
    #define TrapOut_SIO_REG_HIFREQ     (* (reg8 *) TrapOut__SIO_REG_HIFREQ)
    #define TrapOut_SIO_CFG            (* (reg8 *) TrapOut__SIO_CFG)
    #define TrapOut_SIO_DIFF           (* (reg8 *) TrapOut__SIO_DIFF)
#endif /* (TrapOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(TrapOut__INTSTAT)
    #define TrapOut_INTSTAT            (* (reg8 *) TrapOut__INTSTAT)
    #define TrapOut_SNAP               (* (reg8 *) TrapOut__SNAP)
    
	#define TrapOut_0_INTTYPE_REG 		(* (reg8 *) TrapOut__0__INTTYPE)
#endif /* (TrapOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_TrapOut_H */


/* [] END OF FILE */
