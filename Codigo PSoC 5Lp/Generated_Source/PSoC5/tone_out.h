/*******************************************************************************
* File Name: tone_out.h  
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

#if !defined(CY_PINS_tone_out_H) /* Pins tone_out_H */
#define CY_PINS_tone_out_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "tone_out_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 tone_out__PORT == 15 && ((tone_out__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    tone_out_Write(uint8 value);
void    tone_out_SetDriveMode(uint8 mode);
uint8   tone_out_ReadDataReg(void);
uint8   tone_out_Read(void);
void    tone_out_SetInterruptMode(uint16 position, uint16 mode);
uint8   tone_out_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the tone_out_SetDriveMode() function.
     *  @{
     */
        #define tone_out_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define tone_out_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define tone_out_DM_RES_UP          PIN_DM_RES_UP
        #define tone_out_DM_RES_DWN         PIN_DM_RES_DWN
        #define tone_out_DM_OD_LO           PIN_DM_OD_LO
        #define tone_out_DM_OD_HI           PIN_DM_OD_HI
        #define tone_out_DM_STRONG          PIN_DM_STRONG
        #define tone_out_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define tone_out_MASK               tone_out__MASK
#define tone_out_SHIFT              tone_out__SHIFT
#define tone_out_WIDTH              1u

/* Interrupt constants */
#if defined(tone_out__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in tone_out_SetInterruptMode() function.
     *  @{
     */
        #define tone_out_INTR_NONE      (uint16)(0x0000u)
        #define tone_out_INTR_RISING    (uint16)(0x0001u)
        #define tone_out_INTR_FALLING   (uint16)(0x0002u)
        #define tone_out_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define tone_out_INTR_MASK      (0x01u) 
#endif /* (tone_out__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define tone_out_PS                     (* (reg8 *) tone_out__PS)
/* Data Register */
#define tone_out_DR                     (* (reg8 *) tone_out__DR)
/* Port Number */
#define tone_out_PRT_NUM                (* (reg8 *) tone_out__PRT) 
/* Connect to Analog Globals */                                                  
#define tone_out_AG                     (* (reg8 *) tone_out__AG)                       
/* Analog MUX bux enable */
#define tone_out_AMUX                   (* (reg8 *) tone_out__AMUX) 
/* Bidirectional Enable */                                                        
#define tone_out_BIE                    (* (reg8 *) tone_out__BIE)
/* Bit-mask for Aliased Register Access */
#define tone_out_BIT_MASK               (* (reg8 *) tone_out__BIT_MASK)
/* Bypass Enable */
#define tone_out_BYP                    (* (reg8 *) tone_out__BYP)
/* Port wide control signals */                                                   
#define tone_out_CTL                    (* (reg8 *) tone_out__CTL)
/* Drive Modes */
#define tone_out_DM0                    (* (reg8 *) tone_out__DM0) 
#define tone_out_DM1                    (* (reg8 *) tone_out__DM1)
#define tone_out_DM2                    (* (reg8 *) tone_out__DM2) 
/* Input Buffer Disable Override */
#define tone_out_INP_DIS                (* (reg8 *) tone_out__INP_DIS)
/* LCD Common or Segment Drive */
#define tone_out_LCD_COM_SEG            (* (reg8 *) tone_out__LCD_COM_SEG)
/* Enable Segment LCD */
#define tone_out_LCD_EN                 (* (reg8 *) tone_out__LCD_EN)
/* Slew Rate Control */
#define tone_out_SLW                    (* (reg8 *) tone_out__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define tone_out_PRTDSI__CAPS_SEL       (* (reg8 *) tone_out__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define tone_out_PRTDSI__DBL_SYNC_IN    (* (reg8 *) tone_out__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define tone_out_PRTDSI__OE_SEL0        (* (reg8 *) tone_out__PRTDSI__OE_SEL0) 
#define tone_out_PRTDSI__OE_SEL1        (* (reg8 *) tone_out__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define tone_out_PRTDSI__OUT_SEL0       (* (reg8 *) tone_out__PRTDSI__OUT_SEL0) 
#define tone_out_PRTDSI__OUT_SEL1       (* (reg8 *) tone_out__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define tone_out_PRTDSI__SYNC_OUT       (* (reg8 *) tone_out__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(tone_out__SIO_CFG)
    #define tone_out_SIO_HYST_EN        (* (reg8 *) tone_out__SIO_HYST_EN)
    #define tone_out_SIO_REG_HIFREQ     (* (reg8 *) tone_out__SIO_REG_HIFREQ)
    #define tone_out_SIO_CFG            (* (reg8 *) tone_out__SIO_CFG)
    #define tone_out_SIO_DIFF           (* (reg8 *) tone_out__SIO_DIFF)
#endif /* (tone_out__SIO_CFG) */

/* Interrupt Registers */
#if defined(tone_out__INTSTAT)
    #define tone_out_INTSTAT            (* (reg8 *) tone_out__INTSTAT)
    #define tone_out_SNAP               (* (reg8 *) tone_out__SNAP)
    
	#define tone_out_0_INTTYPE_REG 		(* (reg8 *) tone_out__0__INTTYPE)
#endif /* (tone_out__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_tone_out_H */


/* [] END OF FILE */
