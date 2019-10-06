/*******************************************************************************
* File Name: Po2.h  
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

#if !defined(CY_PINS_Po2_H) /* Pins Po2_H */
#define CY_PINS_Po2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Po2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Po2__PORT == 15 && ((Po2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Po2_Write(uint8 value);
void    Po2_SetDriveMode(uint8 mode);
uint8   Po2_ReadDataReg(void);
uint8   Po2_Read(void);
void    Po2_SetInterruptMode(uint16 position, uint16 mode);
uint8   Po2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Po2_SetDriveMode() function.
     *  @{
     */
        #define Po2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Po2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Po2_DM_RES_UP          PIN_DM_RES_UP
        #define Po2_DM_RES_DWN         PIN_DM_RES_DWN
        #define Po2_DM_OD_LO           PIN_DM_OD_LO
        #define Po2_DM_OD_HI           PIN_DM_OD_HI
        #define Po2_DM_STRONG          PIN_DM_STRONG
        #define Po2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Po2_MASK               Po2__MASK
#define Po2_SHIFT              Po2__SHIFT
#define Po2_WIDTH              1u

/* Interrupt constants */
#if defined(Po2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Po2_SetInterruptMode() function.
     *  @{
     */
        #define Po2_INTR_NONE      (uint16)(0x0000u)
        #define Po2_INTR_RISING    (uint16)(0x0001u)
        #define Po2_INTR_FALLING   (uint16)(0x0002u)
        #define Po2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Po2_INTR_MASK      (0x01u) 
#endif /* (Po2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Po2_PS                     (* (reg8 *) Po2__PS)
/* Data Register */
#define Po2_DR                     (* (reg8 *) Po2__DR)
/* Port Number */
#define Po2_PRT_NUM                (* (reg8 *) Po2__PRT) 
/* Connect to Analog Globals */                                                  
#define Po2_AG                     (* (reg8 *) Po2__AG)                       
/* Analog MUX bux enable */
#define Po2_AMUX                   (* (reg8 *) Po2__AMUX) 
/* Bidirectional Enable */                                                        
#define Po2_BIE                    (* (reg8 *) Po2__BIE)
/* Bit-mask for Aliased Register Access */
#define Po2_BIT_MASK               (* (reg8 *) Po2__BIT_MASK)
/* Bypass Enable */
#define Po2_BYP                    (* (reg8 *) Po2__BYP)
/* Port wide control signals */                                                   
#define Po2_CTL                    (* (reg8 *) Po2__CTL)
/* Drive Modes */
#define Po2_DM0                    (* (reg8 *) Po2__DM0) 
#define Po2_DM1                    (* (reg8 *) Po2__DM1)
#define Po2_DM2                    (* (reg8 *) Po2__DM2) 
/* Input Buffer Disable Override */
#define Po2_INP_DIS                (* (reg8 *) Po2__INP_DIS)
/* LCD Common or Segment Drive */
#define Po2_LCD_COM_SEG            (* (reg8 *) Po2__LCD_COM_SEG)
/* Enable Segment LCD */
#define Po2_LCD_EN                 (* (reg8 *) Po2__LCD_EN)
/* Slew Rate Control */
#define Po2_SLW                    (* (reg8 *) Po2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Po2_PRTDSI__CAPS_SEL       (* (reg8 *) Po2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Po2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Po2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Po2_PRTDSI__OE_SEL0        (* (reg8 *) Po2__PRTDSI__OE_SEL0) 
#define Po2_PRTDSI__OE_SEL1        (* (reg8 *) Po2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Po2_PRTDSI__OUT_SEL0       (* (reg8 *) Po2__PRTDSI__OUT_SEL0) 
#define Po2_PRTDSI__OUT_SEL1       (* (reg8 *) Po2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Po2_PRTDSI__SYNC_OUT       (* (reg8 *) Po2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Po2__SIO_CFG)
    #define Po2_SIO_HYST_EN        (* (reg8 *) Po2__SIO_HYST_EN)
    #define Po2_SIO_REG_HIFREQ     (* (reg8 *) Po2__SIO_REG_HIFREQ)
    #define Po2_SIO_CFG            (* (reg8 *) Po2__SIO_CFG)
    #define Po2_SIO_DIFF           (* (reg8 *) Po2__SIO_DIFF)
#endif /* (Po2__SIO_CFG) */

/* Interrupt Registers */
#if defined(Po2__INTSTAT)
    #define Po2_INTSTAT            (* (reg8 *) Po2__INTSTAT)
    #define Po2_SNAP               (* (reg8 *) Po2__SNAP)
    
	#define Po2_0_INTTYPE_REG 		(* (reg8 *) Po2__0__INTTYPE)
#endif /* (Po2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Po2_H */


/* [] END OF FILE */
