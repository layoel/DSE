/*******************************************************************************
* File Name: PWM_ServoP_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWM_ServoP.h"

static PWM_ServoP_backupStruct PWM_ServoP_backup;


/*******************************************************************************
* Function Name: PWM_ServoP_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_ServoP_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_ServoP_SaveConfig(void) 
{

    #if(!PWM_ServoP_UsingFixedFunction)
        #if(!PWM_ServoP_PWMModeIsCenterAligned)
            PWM_ServoP_backup.PWMPeriod = PWM_ServoP_ReadPeriod();
        #endif /* (!PWM_ServoP_PWMModeIsCenterAligned) */
        PWM_ServoP_backup.PWMUdb = PWM_ServoP_ReadCounter();
        #if (PWM_ServoP_UseStatus)
            PWM_ServoP_backup.InterruptMaskValue = PWM_ServoP_STATUS_MASK;
        #endif /* (PWM_ServoP_UseStatus) */

        #if(PWM_ServoP_DeadBandMode == PWM_ServoP__B_PWM__DBM_256_CLOCKS || \
            PWM_ServoP_DeadBandMode == PWM_ServoP__B_PWM__DBM_2_4_CLOCKS)
            PWM_ServoP_backup.PWMdeadBandValue = PWM_ServoP_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_ServoP_KillModeMinTime)
             PWM_ServoP_backup.PWMKillCounterPeriod = PWM_ServoP_ReadKillTime();
        #endif /* (PWM_ServoP_KillModeMinTime) */

        #if(PWM_ServoP_UseControl)
            PWM_ServoP_backup.PWMControlRegister = PWM_ServoP_ReadControlRegister();
        #endif /* (PWM_ServoP_UseControl) */
    #endif  /* (!PWM_ServoP_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_ServoP_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_ServoP_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_ServoP_RestoreConfig(void) 
{
        #if(!PWM_ServoP_UsingFixedFunction)
            #if(!PWM_ServoP_PWMModeIsCenterAligned)
                PWM_ServoP_WritePeriod(PWM_ServoP_backup.PWMPeriod);
            #endif /* (!PWM_ServoP_PWMModeIsCenterAligned) */

            PWM_ServoP_WriteCounter(PWM_ServoP_backup.PWMUdb);

            #if (PWM_ServoP_UseStatus)
                PWM_ServoP_STATUS_MASK = PWM_ServoP_backup.InterruptMaskValue;
            #endif /* (PWM_ServoP_UseStatus) */

            #if(PWM_ServoP_DeadBandMode == PWM_ServoP__B_PWM__DBM_256_CLOCKS || \
                PWM_ServoP_DeadBandMode == PWM_ServoP__B_PWM__DBM_2_4_CLOCKS)
                PWM_ServoP_WriteDeadTime(PWM_ServoP_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_ServoP_KillModeMinTime)
                PWM_ServoP_WriteKillTime(PWM_ServoP_backup.PWMKillCounterPeriod);
            #endif /* (PWM_ServoP_KillModeMinTime) */

            #if(PWM_ServoP_UseControl)
                PWM_ServoP_WriteControlRegister(PWM_ServoP_backup.PWMControlRegister);
            #endif /* (PWM_ServoP_UseControl) */
        #endif  /* (!PWM_ServoP_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_ServoP_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_ServoP_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_ServoP_Sleep(void) 
{
    #if(PWM_ServoP_UseControl)
        if(PWM_ServoP_CTRL_ENABLE == (PWM_ServoP_CONTROL & PWM_ServoP_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_ServoP_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_ServoP_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_ServoP_UseControl) */

    /* Stop component */
    PWM_ServoP_Stop();

    /* Save registers configuration */
    PWM_ServoP_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_ServoP_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_ServoP_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_ServoP_Wakeup(void) 
{
     /* Restore registers values */
    PWM_ServoP_RestoreConfig();

    if(PWM_ServoP_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_ServoP_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
