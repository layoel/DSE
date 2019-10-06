/*******************************************************************************
* File Name: TimerCountWidth_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "TimerCountWidth.h"

static TimerCountWidth_backupStruct TimerCountWidth_backup;


/*******************************************************************************
* Function Name: TimerCountWidth_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  TimerCountWidth_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void TimerCountWidth_SaveConfig(void) 
{
    #if (!TimerCountWidth_UsingFixedFunction)
        TimerCountWidth_backup.TimerUdb = TimerCountWidth_ReadCounter();
        TimerCountWidth_backup.InterruptMaskValue = TimerCountWidth_STATUS_MASK;
        #if (TimerCountWidth_UsingHWCaptureCounter)
            TimerCountWidth_backup.TimerCaptureCounter = TimerCountWidth_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!TimerCountWidth_UDB_CONTROL_REG_REMOVED)
            TimerCountWidth_backup.TimerControlRegister = TimerCountWidth_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: TimerCountWidth_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  TimerCountWidth_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void TimerCountWidth_RestoreConfig(void) 
{   
    #if (!TimerCountWidth_UsingFixedFunction)

        TimerCountWidth_WriteCounter(TimerCountWidth_backup.TimerUdb);
        TimerCountWidth_STATUS_MASK =TimerCountWidth_backup.InterruptMaskValue;
        #if (TimerCountWidth_UsingHWCaptureCounter)
            TimerCountWidth_SetCaptureCount(TimerCountWidth_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!TimerCountWidth_UDB_CONTROL_REG_REMOVED)
            TimerCountWidth_WriteControlRegister(TimerCountWidth_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: TimerCountWidth_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  TimerCountWidth_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void TimerCountWidth_Sleep(void) 
{
    #if(!TimerCountWidth_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(TimerCountWidth_CTRL_ENABLE == (TimerCountWidth_CONTROL & TimerCountWidth_CTRL_ENABLE))
        {
            /* Timer is enabled */
            TimerCountWidth_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            TimerCountWidth_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    TimerCountWidth_Stop();
    TimerCountWidth_SaveConfig();
}


/*******************************************************************************
* Function Name: TimerCountWidth_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  TimerCountWidth_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void TimerCountWidth_Wakeup(void) 
{
    TimerCountWidth_RestoreConfig();
    #if(!TimerCountWidth_UDB_CONTROL_REG_REMOVED)
        if(TimerCountWidth_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                TimerCountWidth_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
