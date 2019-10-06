/*******************************************************************************
* File Name: DoorOut.h  
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

#if !defined(CY_PINS_DoorOut_H) /* Pins DoorOut_H */
#define CY_PINS_DoorOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DoorOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DoorOut__PORT == 15 && ((DoorOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    DoorOut_Write(uint8 value);
void    DoorOut_SetDriveMode(uint8 mode);
uint8   DoorOut_ReadDataReg(void);
uint8   DoorOut_Read(void);
void    DoorOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   DoorOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the DoorOut_SetDriveMode() function.
     *  @{
     */
        #define DoorOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define DoorOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define DoorOut_DM_RES_UP          PIN_DM_RES_UP
        #define DoorOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define DoorOut_DM_OD_LO           PIN_DM_OD_LO
        #define DoorOut_DM_OD_HI           PIN_DM_OD_HI
        #define DoorOut_DM_STRONG          PIN_DM_STRONG
        #define DoorOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define DoorOut_MASK               DoorOut__MASK
#define DoorOut_SHIFT              DoorOut__SHIFT
#define DoorOut_WIDTH              1u

/* Interrupt constants */
#if defined(DoorOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DoorOut_SetInterruptMode() function.
     *  @{
     */
        #define DoorOut_INTR_NONE      (uint16)(0x0000u)
        #define DoorOut_INTR_RISING    (uint16)(0x0001u)
        #define DoorOut_INTR_FALLING   (uint16)(0x0002u)
        #define DoorOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define DoorOut_INTR_MASK      (0x01u) 
#endif /* (DoorOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DoorOut_PS                     (* (reg8 *) DoorOut__PS)
/* Data Register */
#define DoorOut_DR                     (* (reg8 *) DoorOut__DR)
/* Port Number */
#define DoorOut_PRT_NUM                (* (reg8 *) DoorOut__PRT) 
/* Connect to Analog Globals */                                                  
#define DoorOut_AG                     (* (reg8 *) DoorOut__AG)                       
/* Analog MUX bux enable */
#define DoorOut_AMUX                   (* (reg8 *) DoorOut__AMUX) 
/* Bidirectional Enable */                                                        
#define DoorOut_BIE                    (* (reg8 *) DoorOut__BIE)
/* Bit-mask for Aliased Register Access */
#define DoorOut_BIT_MASK               (* (reg8 *) DoorOut__BIT_MASK)
/* Bypass Enable */
#define DoorOut_BYP                    (* (reg8 *) DoorOut__BYP)
/* Port wide control signals */                                                   
#define DoorOut_CTL                    (* (reg8 *) DoorOut__CTL)
/* Drive Modes */
#define DoorOut_DM0                    (* (reg8 *) DoorOut__DM0) 
#define DoorOut_DM1                    (* (reg8 *) DoorOut__DM1)
#define DoorOut_DM2                    (* (reg8 *) DoorOut__DM2) 
/* Input Buffer Disable Override */
#define DoorOut_INP_DIS                (* (reg8 *) DoorOut__INP_DIS)
/* LCD Common or Segment Drive */
#define DoorOut_LCD_COM_SEG            (* (reg8 *) DoorOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define DoorOut_LCD_EN                 (* (reg8 *) DoorOut__LCD_EN)
/* Slew Rate Control */
#define DoorOut_SLW                    (* (reg8 *) DoorOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DoorOut_PRTDSI__CAPS_SEL       (* (reg8 *) DoorOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DoorOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DoorOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DoorOut_PRTDSI__OE_SEL0        (* (reg8 *) DoorOut__PRTDSI__OE_SEL0) 
#define DoorOut_PRTDSI__OE_SEL1        (* (reg8 *) DoorOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DoorOut_PRTDSI__OUT_SEL0       (* (reg8 *) DoorOut__PRTDSI__OUT_SEL0) 
#define DoorOut_PRTDSI__OUT_SEL1       (* (reg8 *) DoorOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DoorOut_PRTDSI__SYNC_OUT       (* (reg8 *) DoorOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(DoorOut__SIO_CFG)
    #define DoorOut_SIO_HYST_EN        (* (reg8 *) DoorOut__SIO_HYST_EN)
    #define DoorOut_SIO_REG_HIFREQ     (* (reg8 *) DoorOut__SIO_REG_HIFREQ)
    #define DoorOut_SIO_CFG            (* (reg8 *) DoorOut__SIO_CFG)
    #define DoorOut_SIO_DIFF           (* (reg8 *) DoorOut__SIO_DIFF)
#endif /* (DoorOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(DoorOut__INTSTAT)
    #define DoorOut_INTSTAT            (* (reg8 *) DoorOut__INTSTAT)
    #define DoorOut_SNAP               (* (reg8 *) DoorOut__SNAP)
    
	#define DoorOut_0_INTTYPE_REG 		(* (reg8 *) DoorOut__0__INTTYPE)
#endif /* (DoorOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DoorOut_H */


/* [] END OF FILE */
