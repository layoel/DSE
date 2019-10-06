/*******************************************************************************
* File Name: Po3.h  
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

#if !defined(CY_PINS_Po3_H) /* Pins Po3_H */
#define CY_PINS_Po3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Po3_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Po3__PORT == 15 && ((Po3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Po3_Write(uint8 value);
void    Po3_SetDriveMode(uint8 mode);
uint8   Po3_ReadDataReg(void);
uint8   Po3_Read(void);
void    Po3_SetInterruptMode(uint16 position, uint16 mode);
uint8   Po3_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Po3_SetDriveMode() function.
     *  @{
     */
        #define Po3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Po3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Po3_DM_RES_UP          PIN_DM_RES_UP
        #define Po3_DM_RES_DWN         PIN_DM_RES_DWN
        #define Po3_DM_OD_LO           PIN_DM_OD_LO
        #define Po3_DM_OD_HI           PIN_DM_OD_HI
        #define Po3_DM_STRONG          PIN_DM_STRONG
        #define Po3_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Po3_MASK               Po3__MASK
#define Po3_SHIFT              Po3__SHIFT
#define Po3_WIDTH              1u

/* Interrupt constants */
#if defined(Po3__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Po3_SetInterruptMode() function.
     *  @{
     */
        #define Po3_INTR_NONE      (uint16)(0x0000u)
        #define Po3_INTR_RISING    (uint16)(0x0001u)
        #define Po3_INTR_FALLING   (uint16)(0x0002u)
        #define Po3_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Po3_INTR_MASK      (0x01u) 
#endif /* (Po3__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Po3_PS                     (* (reg8 *) Po3__PS)
/* Data Register */
#define Po3_DR                     (* (reg8 *) Po3__DR)
/* Port Number */
#define Po3_PRT_NUM                (* (reg8 *) Po3__PRT) 
/* Connect to Analog Globals */                                                  
#define Po3_AG                     (* (reg8 *) Po3__AG)                       
/* Analog MUX bux enable */
#define Po3_AMUX                   (* (reg8 *) Po3__AMUX) 
/* Bidirectional Enable */                                                        
#define Po3_BIE                    (* (reg8 *) Po3__BIE)
/* Bit-mask for Aliased Register Access */
#define Po3_BIT_MASK               (* (reg8 *) Po3__BIT_MASK)
/* Bypass Enable */
#define Po3_BYP                    (* (reg8 *) Po3__BYP)
/* Port wide control signals */                                                   
#define Po3_CTL                    (* (reg8 *) Po3__CTL)
/* Drive Modes */
#define Po3_DM0                    (* (reg8 *) Po3__DM0) 
#define Po3_DM1                    (* (reg8 *) Po3__DM1)
#define Po3_DM2                    (* (reg8 *) Po3__DM2) 
/* Input Buffer Disable Override */
#define Po3_INP_DIS                (* (reg8 *) Po3__INP_DIS)
/* LCD Common or Segment Drive */
#define Po3_LCD_COM_SEG            (* (reg8 *) Po3__LCD_COM_SEG)
/* Enable Segment LCD */
#define Po3_LCD_EN                 (* (reg8 *) Po3__LCD_EN)
/* Slew Rate Control */
#define Po3_SLW                    (* (reg8 *) Po3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Po3_PRTDSI__CAPS_SEL       (* (reg8 *) Po3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Po3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Po3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Po3_PRTDSI__OE_SEL0        (* (reg8 *) Po3__PRTDSI__OE_SEL0) 
#define Po3_PRTDSI__OE_SEL1        (* (reg8 *) Po3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Po3_PRTDSI__OUT_SEL0       (* (reg8 *) Po3__PRTDSI__OUT_SEL0) 
#define Po3_PRTDSI__OUT_SEL1       (* (reg8 *) Po3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Po3_PRTDSI__SYNC_OUT       (* (reg8 *) Po3__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Po3__SIO_CFG)
    #define Po3_SIO_HYST_EN        (* (reg8 *) Po3__SIO_HYST_EN)
    #define Po3_SIO_REG_HIFREQ     (* (reg8 *) Po3__SIO_REG_HIFREQ)
    #define Po3_SIO_CFG            (* (reg8 *) Po3__SIO_CFG)
    #define Po3_SIO_DIFF           (* (reg8 *) Po3__SIO_DIFF)
#endif /* (Po3__SIO_CFG) */

/* Interrupt Registers */
#if defined(Po3__INTSTAT)
    #define Po3_INTSTAT            (* (reg8 *) Po3__INTSTAT)
    #define Po3_SNAP               (* (reg8 *) Po3__SNAP)
    
	#define Po3_0_INTTYPE_REG 		(* (reg8 *) Po3__0__INTTYPE)
#endif /* (Po3__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Po3_H */


/* [] END OF FILE */
