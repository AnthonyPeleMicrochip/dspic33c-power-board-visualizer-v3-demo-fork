/**
 * ADC2 Generated Driver Source File
 * 
 * @file      adc2.c
 *            
 * @ingroup   adcdriver
 *            
 * @brief     This is the generated driver source file for ADC2 driver        
 *
 * @skipline @version   PLIB Version 1.1.0
 *           
 * @skipline  Device : dsPIC33AK512MPS506
*/

/*disclaimer*/

// Section: Included Files
#include <stddef.h>
#include "../adc2.h"

// Section: File specific functions

static void (*ADC2_ChannelHandler)(enum ADC2_CHANNEL channel, uint16_t adcVal) = NULL;
static void (*ADC2_Result32BitChannelHandler)(enum ADC2_CHANNEL channel, uint32_t adcVal) = NULL;
static void (*ADC2_ComparatorHandler)(enum ADC2_CMP comparator) = NULL;

// Section: File specific data type definitions

/**
 @ingroup  adcdriver
 @enum     ADC2_PWM_TRIG_SRCS
 @brief    Defines the PWM ADC TRIGGER sources available for the module to use.
*/
enum ADC2_PWM_TRIG_SRCS {
    PWM8_TRIGGER2 = 0x13, 
    PWM8_TRIGGER1 = 0x12, 
    PWM7_TRIGGER2 = 0x11, 
    PWM7_TRIGGER1 = 0x10, 
    PWM6_TRIGGER2 = 0xf, 
    PWM6_TRIGGER1 = 0xe, 
    PWM5_TRIGGER2 = 0xd, 
    PWM5_TRIGGER1 = 0xc, 
    PWM4_TRIGGER2 = 0xb, 
    PWM4_TRIGGER1 = 0xa, 
    PWM3_TRIGGER2 = 0x9, 
    PWM3_TRIGGER1 = 0x8, 
    PWM2_TRIGGER2 = 0x7, 
    PWM2_TRIGGER1 = 0x6, 
    PWM1_TRIGGER2 = 0x5, 
    PWM1_TRIGGER1 = 0x4, 
};

//Defines an object for ADC_MULTICORE.
static const struct ADC_MULTICORE adc2Multicore = {
    .ChannelSoftwareTriggerEnable           = &ADC2_ChannelSoftwareTriggerEnable,
    .ChannelSoftwareTriggerDisable          = &ADC2_ChannelSoftwareTriggerDisable,
    .SampleCountGet                         = NULL,
    .SampleCountStatusGet                   = NULL,
    .ChannelTasks                           = &ADC2_ChannelTasks, 
    .ComparatorTasks                        = NULL,
    .IndividualChannelInterruptEnable       = &ADC2_IndividualChannelInterruptEnable,
    .IndividualChannelInterruptDisable      = &ADC2_IndividualChannelInterruptDisable,
    .IndividualChannelInterruptFlagClear    = &ADC2_IndividualChannelInterruptFlagClear,
    .IndividualChannelInterruptPrioritySet  = &ADC2_IndividualChannelInterruptPrioritySet,
    .ChannelCallbackRegister                = &ADC2_ChannelCallbackRegister,
    .Result32BitChannelCallbackRegister     = &ADC2_Result32BitChannelCallbackRegister,
    .ComparatorCallbackRegister             = &ADC2_ComparatorCallbackRegister,
    .CorePowerEnable                        = NULL,
    .SharedCorePowerEnable                  = &ADC2_SharedCorePowerEnable,
    .CoreCalibration                        = NULL,
    .SharedCoreCalibration                  = &ADC2_SharedCoreCalibration,
    .PWMTriggerSourceSet                    = &ADC2_PWMTriggerSourceSet
};

//Defines an object for ADC_INTERFACE.

const struct ADC_INTERFACE ADC2 = {
    .Initialize             = &ADC2_Initialize,
    .Deinitialize           = &ADC2_Deinitialize,
    .Enable                 = &ADC2_Enable,
    .Disable                = &ADC2_Disable,
    .SoftwareTriggerEnable  = &ADC2_SoftwareTriggerEnable,
    .SoftwareTriggerDisable = &ADC2_SoftwareTriggerDisable,
    .ChannelSelect          = NULL, 
    .ConversionResultGet    = &ADC2_ConversionResultGet,
    .SecondaryAccumulatorGet= NULL,
    .IsConversionComplete   = &ADC2_IsConversionComplete,
    .ResolutionSet          = NULL,
    .InterruptEnable        = NULL,
    .InterruptDisable       = NULL,
    .InterruptFlagClear     = NULL,
    .InterruptPrioritySet   = NULL,
    .CommonCallbackRegister = NULL,
    .Tasks                  = NULL,
    .adcMulticoreInterface = &adc2Multicore,
};

// Section: Driver Interface Function Definitions

void ADC2_Initialize(void)
{
    //CALCNT Wait for 2 activity free ADC clock cycles; BUFEN disabled; TSTEN disabled; ON enabled; STNDBY disabled; RPTCNT 1 ADC clock cycles between triggers; CALRATE Every second; ACALEN disabled; CALREQ Calibration cycle is not requested; 
    AD2CON = 0x8000UL;
    //DATAOVR 0x0; 
    AD2DATAOVR = 0x0UL;
    //CH0RDY disabled; CH1RDY disabled; CH2RDY disabled; CH3RDY disabled; CH4RDY disabled; CH5RDY disabled; CH6RDY disabled; CH7RDY disabled; 
    AD2STAT = 0x0UL;
    //CH0RRDY disabled; CH1RRDY disabled; CH2RRDY disabled; CH3RRDY disabled; CH4RRDY disabled; CH5RRDY disabled; CH6RRDY disabled; CH7RRDY disabled; 
    AD2RSTAT = 0x0UL;
    //CH0CMP disabled; CH1CMP disabled; CH2CMP disabled; CH3CMP disabled; CH4CMP disabled; CH5CMP disabled; CH6CMP disabled; CH7CMP disabled; 
    AD2CMPSTAT = 0x0UL;
    //CH0TRG disabled; CH1TRG disabled; CH2TRG disabled; CH3TRG disabled; CH4TRG disabled; CH5TRG disabled; CH6TRG disabled; CH7TRG disabled; 
    AD2SWTRG = 0x0UL;
    //TRG1SRC Triggers are disabled; MODE Single sample initiated by TRG1SRC[4:0] trigger; TRG2SRC Triggers are disabled; ACCNUM 4 samples, 13 bits result; SAMC 0.5 TAD; IRQSEL enabled; EIEN disabled; TRG1POL disabled; PINSEL AD2AN0; NINSEL disabled; FRAC Integer; DIFF disabled; 
    AD2CH0CON1 = 0x200000UL;
    //TRG1SRC Triggers are disabled; MODE Single sample initiated by TRG1SRC[4:0] trigger; TRG2SRC Triggers are disabled; ACCNUM 4 samples, 13 bits result; SAMC 0.5 TAD; IRQSEL enabled; EIEN disabled; TRG1POL disabled; PINSEL AD2AN0; NINSEL disabled; FRAC Integer; DIFF disabled; 
    AD2CH1CON1 = 0x200000UL;
    //TRG1SRC Triggers are disabled; MODE Single sample initiated by TRG1SRC[4:0] trigger; TRG2SRC Triggers are disabled; ACCNUM 4 samples, 13 bits result; SAMC 0.5 TAD; IRQSEL enabled; EIEN disabled; TRG1POL disabled; PINSEL AD2AN0; NINSEL disabled; FRAC Integer; DIFF disabled; 
    AD2CH2CON1 = 0x200000UL;
    //TRG1SRC Triggers are disabled; MODE Single sample initiated by TRG1SRC[4:0] trigger; TRG2SRC Triggers are disabled; ACCNUM 4 samples, 13 bits result; SAMC 0.5 TAD; IRQSEL enabled; EIEN disabled; TRG1POL disabled; PINSEL AD2AN0; NINSEL disabled; FRAC Integer; DIFF disabled; 
    AD2CH3CON1 = 0x200000UL;
    //TRG1SRC Software trigger initiated by using ADnSWTRG register; MODE Single sample initiated by TRG1SRC[4:0] trigger; TRG2SRC Triggers are disabled; ACCNUM 4 samples, 13 bits result; SAMC 0.5 TAD; IRQSEL enabled; EIEN disabled; TRG1POL disabled; PINSEL AD2AN4; NINSEL disabled; FRAC Integer; DIFF disabled; 
    AD2CH4CON1 = 0x4200001UL;
    //TRG1SRC Triggers are disabled; MODE Single sample initiated by TRG1SRC[4:0] trigger; TRG2SRC Triggers are disabled; ACCNUM 4 samples, 13 bits result; SAMC 0.5 TAD; IRQSEL enabled; EIEN disabled; TRG1POL disabled; PINSEL AD2AN0; NINSEL disabled; FRAC Integer; DIFF disabled; 
    AD2CH5CON1 = 0x200000UL;
    //TRG1SRC Triggers are disabled; MODE Single sample initiated by TRG1SRC[4:0] trigger; TRG2SRC Triggers are disabled; ACCNUM 4 samples, 13 bits result; SAMC 0.5 TAD; IRQSEL enabled; EIEN disabled; TRG1POL disabled; PINSEL AD2AN0; NINSEL disabled; FRAC Integer; DIFF disabled; 
    AD2CH6CON1 = 0x200000UL;
    //TRG1SRC Triggers are disabled; MODE Single sample initiated by TRG1SRC[4:0] trigger; TRG2SRC Triggers are disabled; ACCNUM 4 samples, 13 bits result; SAMC 0.5 TAD; IRQSEL enabled; EIEN disabled; TRG1POL disabled; PINSEL AD2AN0; NINSEL disabled; FRAC Integer; DIFF disabled; 
    AD2CH7CON1 = 0x200000UL;
    //ADCMPCNT disabled; CMPMOD NONE; CMPCNTMOD disabled; CMPVAL enabled; ACCBRST disabled; ACCRO disabled; 
    AD2CH0CON2 = 0x20000000UL;
    //ADCMPCNT disabled; CMPMOD NONE; CMPCNTMOD disabled; CMPVAL enabled; ACCBRST disabled; ACCRO disabled; 
    AD2CH1CON2 = 0x20000000UL;
    //ADCMPCNT disabled; CMPMOD NONE; CMPCNTMOD disabled; CMPVAL enabled; ACCBRST disabled; ACCRO disabled; 
    AD2CH2CON2 = 0x20000000UL;
    //ADCMPCNT disabled; CMPMOD NONE; CMPCNTMOD disabled; CMPVAL enabled; ACCBRST disabled; ACCRO disabled; 
    AD2CH3CON2 = 0x20000000UL;
    //ADCMPCNT disabled; CMPMOD NONE; CMPCNTMOD disabled; CMPVAL enabled; ACCBRST disabled; ACCRO disabled; 
    AD2CH4CON2 = 0x20000000UL;
    //ADCMPCNT disabled; CMPMOD NONE; CMPCNTMOD disabled; CMPVAL enabled; ACCBRST disabled; ACCRO disabled; 
    AD2CH5CON2 = 0x20000000UL;
    //ADCMPCNT disabled; CMPMOD NONE; CMPCNTMOD disabled; CMPVAL enabled; ACCBRST disabled; ACCRO disabled; 
    AD2CH6CON2 = 0x20000000UL;
    //ADCMPCNT disabled; CMPMOD NONE; CMPCNTMOD disabled; CMPVAL enabled; ACCBRST disabled; ACCRO disabled; 
    AD2CH7CON2 = 0x20000000UL;
    //
    AD2CH0RES = 0x0UL;
    //
    AD2CH1RES = 0x0UL;
    //
    AD2CH2RES = 0x0UL;
    //
    AD2CH3RES = 0x0UL;
    //
    AD2CH4RES = 0x0UL;
    //
    AD2CH5RES = 0x0UL;
    //
    AD2CH6RES = 0x0UL;
    //
    AD2CH7RES = 0x0UL;
    //CNT 0x0; 
    AD2CH0CNT = 0x0UL;
    //CNT 0x0; 
    AD2CH1CNT = 0x0UL;
    //CNT 0x0; 
    AD2CH2CNT = 0x0UL;
    //CNT 0x0; 
    AD2CH3CNT = 0x0UL;
    //CNT 0x0; 
    AD2CH4CNT = 0x0UL;
    //CNT 0x0; 
    AD2CH5CNT = 0x0UL;
    //CNT 0x0; 
    AD2CH6CNT = 0x0UL;
    //CNT 0x0; 
    AD2CH7CNT = 0x0UL;
    //CMPLO 0x0; 
    AD2CH0CMPLO = 0x0UL;
    //CMPLO 0x0; 
    AD2CH1CMPLO = 0x0UL;
    //CMPLO 0x0; 
    AD2CH2CMPLO = 0x0UL;
    //CMPLO 0x0; 
    AD2CH3CMPLO = 0x0UL;
    //CMPLO 0x0; 
    AD2CH4CMPLO = 0x0UL;
    //CMPLO 0x0; 
    AD2CH5CMPLO = 0x0UL;
    //CMPLO 0x0; 
    AD2CH6CMPLO = 0x0UL;
    //CMPLO 0x0; 
    AD2CH7CMPLO = 0x0UL;
    //CMPHI 0x0; 
    AD2CH0CMPHI = 0x0UL;
    //CMPHI 0x0; 
    AD2CH1CMPHI = 0x0UL;
    //CMPHI 0x0; 
    AD2CH2CMPHI = 0x0UL;
    //CMPHI 0x0; 
    AD2CH3CMPHI = 0x0UL;
    //CMPHI 0x0; 
    AD2CH4CMPHI = 0x0UL;
    //CMPHI 0x0; 
    AD2CH5CMPHI = 0x0UL;
    //CMPHI 0x0; 
    AD2CH6CMPHI = 0x0UL;
    //CMPHI 0x0; 
    AD2CH7CMPHI = 0x0UL;

    ADC2_ChannelCallbackRegister(&ADC2_ChannelCallback);
    ADC2_Result32BitChannelCallbackRegister(&ADC2_Result32BitChannelCallback);
    ADC2_ComparatorCallbackRegister(&ADC2_ComparatorCallback);
    
    // Clearing ADC2_Channel4 interrupt flag.
    IFS5bits.AD2CH4IF = 0U;
    // Enabling ADC2_Channel4 interrupt.
    IEC5bits.AD2CH4IE = 1U;
    
    // ADC Mode change to run mode
    ADC2_SharedCorePowerEnable();
}

void ADC2_Deinitialize (void)
{
    uint32_t  __attribute__ ((unused)) dummy; //buffers has to be read before clearing interrupt flags
    AD2CONbits.ON = 0U;
    
    dummy = AD2CH4DATA;
    IFS5bits.AD2CH4IF = 0U;
    IEC5bits.AD2CH4IE = 0U;
    
    AD2CON = 0x480000UL;
    AD2DATAOVR = 0x0UL;
    AD2STAT = 0x0UL;
    AD2RSTAT = 0x0UL;
    AD2CMPSTAT = 0x0UL;
    AD2SWTRG = 0x0UL;
    AD2CH0CON1 = 0x0UL;
    AD2CH1CON1 = 0x0UL;
    AD2CH2CON1 = 0x0UL;
    AD2CH3CON1 = 0x0UL;
    AD2CH4CON1 = 0x0UL;
    AD2CH5CON1 = 0x0UL;
    AD2CH6CON1 = 0x0UL;
    AD2CH7CON1 = 0x0UL;
    AD2CH0CON2 = 0x1UL;
    AD2CH1CON2 = 0x1UL;
    AD2CH2CON2 = 0x1UL;
    AD2CH3CON2 = 0x1UL;
    AD2CH4CON2 = 0x1UL;
    AD2CH5CON2 = 0x1UL;
    AD2CH6CON2 = 0x1UL;
    AD2CH7CON2 = 0x1UL;
    AD2CH0RES = 0x0UL;
    AD2CH1RES = 0x0UL;
    AD2CH2RES = 0x0UL;
    AD2CH3RES = 0x0UL;
    AD2CH4RES = 0x0UL;
    AD2CH5RES = 0x0UL;
    AD2CH6RES = 0x0UL;
    AD2CH7RES = 0x0UL;
    AD2CH0CNT = 0x0UL;
    AD2CH1CNT = 0x0UL;
    AD2CH2CNT = 0x0UL;
    AD2CH3CNT = 0x0UL;
    AD2CH4CNT = 0x0UL;
    AD2CH5CNT = 0x0UL;
    AD2CH6CNT = 0x0UL;
    AD2CH7CNT = 0x0UL;
    AD2CH0CMPLO = 0x0UL;
    AD2CH1CMPLO = 0x0UL;
    AD2CH2CMPLO = 0x0UL;
    AD2CH3CMPLO = 0x0UL;
    AD2CH4CMPLO = 0x0UL;
    AD2CH5CMPLO = 0x0UL;
    AD2CH6CMPLO = 0x0UL;
    AD2CH7CMPLO = 0x0UL;
    AD2CH0CMPHI = 0x0UL;
    AD2CH1CMPHI = 0x0UL;
    AD2CH2CMPHI = 0x0UL;
    AD2CH3CMPHI = 0x0UL;
    AD2CH4CMPHI = 0x0UL;
    AD2CH5CMPHI = 0x0UL;
    AD2CH6CMPHI = 0x0UL;
    AD2CH7CMPHI = 0x0UL;
}

void ADC2_SharedCorePowerEnable (void) 
{
    AD2CONbits.ON = 1U;   
    while(AD2CONbits.ADRDY == 0U)
    {
    }
}

void ADC2_SharedCoreCalibration (void) 
{
    AD2CONbits.CALREQ = 1U;    
    while(AD2CONbits.CALRDY == 0U)
    {
    }  
}

static uint16_t ADC2_TriggerSourceValueGet(enum ADC_PWM_INSTANCE pwmInstance, enum ADC_PWM_TRIGGERS triggerNumber)
{
    uint16_t adcTriggerSourceValue = 0x0U;
    switch(pwmInstance)
    {
        case ADC_PWM_GENERATOR_8:
                if(triggerNumber == ADC_PWM_TRIGGER_1)
                {
                    adcTriggerSourceValue = PWM8_TRIGGER1;
                }
                else if(triggerNumber == ADC_PWM_TRIGGER_2)
                {
                    adcTriggerSourceValue = PWM8_TRIGGER2;
                }
                else
                {
                }
                break;
        case ADC_PWM_GENERATOR_7:
                if(triggerNumber == ADC_PWM_TRIGGER_1)
                {
                    adcTriggerSourceValue = PWM7_TRIGGER1;
                }
                else if(triggerNumber == ADC_PWM_TRIGGER_2)
                {
                    adcTriggerSourceValue = PWM7_TRIGGER2;
                }
                else
                {
                }
                break;
        case ADC_PWM_GENERATOR_6:
                if(triggerNumber == ADC_PWM_TRIGGER_1)
                {
                    adcTriggerSourceValue = PWM6_TRIGGER1;
                }
                else if(triggerNumber == ADC_PWM_TRIGGER_2)
                {
                    adcTriggerSourceValue = PWM6_TRIGGER2;
                }
                else
                {
                }
                break;
        case ADC_PWM_GENERATOR_5:
                if(triggerNumber == ADC_PWM_TRIGGER_1)
                {
                    adcTriggerSourceValue = PWM5_TRIGGER1;
                }
                else if(triggerNumber == ADC_PWM_TRIGGER_2)
                {
                    adcTriggerSourceValue = PWM5_TRIGGER2;
                }
                else
                {
                }
                break;
        case ADC_PWM_GENERATOR_4:
                if(triggerNumber == ADC_PWM_TRIGGER_1)
                {
                    adcTriggerSourceValue = PWM4_TRIGGER1;
                }
                else if(triggerNumber == ADC_PWM_TRIGGER_2)
                {
                    adcTriggerSourceValue = PWM4_TRIGGER2;
                }
                else
                {
                }
                break;
        case ADC_PWM_GENERATOR_3:
                if(triggerNumber == ADC_PWM_TRIGGER_1)
                {
                    adcTriggerSourceValue = PWM3_TRIGGER1;
                }
                else if(triggerNumber == ADC_PWM_TRIGGER_2)
                {
                    adcTriggerSourceValue = PWM3_TRIGGER2;
                }
                else
                {
                }
                break;
        case ADC_PWM_GENERATOR_2:
                if(triggerNumber == ADC_PWM_TRIGGER_1)
                {
                    adcTriggerSourceValue = PWM2_TRIGGER1;
                }
                else if(triggerNumber == ADC_PWM_TRIGGER_2)
                {
                    adcTriggerSourceValue = PWM2_TRIGGER2;
                }
                else
                {
                }
                break;
        case ADC_PWM_GENERATOR_1:
                if(triggerNumber == ADC_PWM_TRIGGER_1)
                {
                    adcTriggerSourceValue = PWM1_TRIGGER1;
                }
                else if(triggerNumber == ADC_PWM_TRIGGER_2)
                {
                    adcTriggerSourceValue = PWM1_TRIGGER2;
                }
                else
                {
                }
                break;
         default:
                break;
    }
    return adcTriggerSourceValue;
}

void ADC2_PWMTriggerSourceSet(enum ADC2_CHANNEL channel, enum ADC_PWM_INSTANCE pwmInstance, enum ADC_PWM_TRIGGERS triggerNumber)
{
    uint16_t adcTriggerValue;
    adcTriggerValue= ADC2_TriggerSourceValueGet(pwmInstance, triggerNumber);
    switch(channel)
    {
        case ADC2_Channel4:
                AD2SWTRGbits.CH4TRG = adcTriggerValue;
                break;
        default:
                break;
    }
}

void ADC2_ChannelCallbackRegister(void(*callback)(enum ADC2_CHANNEL channel, uint16_t adcVal))
{
    if(NULL != callback)
    {
        ADC2_ChannelHandler = callback;
    }
}

void __attribute__ ((weak)) ADC2_ChannelCallback (enum ADC2_CHANNEL channel, uint16_t adcVal)
{ 
    (void)channel;
    (void)adcVal;
} 

void ADC2_Result32BitChannelCallbackRegister(void(*callback)(enum ADC2_CHANNEL channel, uint32_t adcVal))
{
    if(NULL != callback)
    {
        ADC2_Result32BitChannelHandler = callback;
    }
}

void __attribute__ ((weak)) ADC2_Result32BitChannelCallback (enum ADC2_CHANNEL channel, uint32_t adcVal)
{ 
    (void)channel;
    (void)adcVal;
} 


void __attribute__ ( ( __interrupt__ , auto_psv, weak ) ) _AD2CH4Interrupt ( void )
{
    uint32_t valADC2_Channel4;
    //Read the ADC value from the ADCBUF
    valADC2_Channel4 = AD2CH4DATA;

    if(NULL != ADC2_ChannelHandler)
    {
        (*ADC2_ChannelHandler)(ADC2_Channel4, valADC2_Channel4);
    }
    if(NULL != ADC2_Result32BitChannelHandler)
    {
        (*ADC2_Result32BitChannelHandler)(ADC2_Channel4, valADC2_Channel4);
    }

    //clear the ADC2_Channel4 interrupt flag
    IFS5bits.AD2CH4IF = 0U;
}


void __attribute__ ((weak)) ADC2_ChannelTasks (enum ADC2_CHANNEL channel)
{
    uint32_t adcVal;
    
    switch(channel)
    {   
        case ADC2_Channel4:
            if((bool)AD2STATbits.CH4RDY == 1U)
            {
                //Read the ADC value from the ADCBUF
                adcVal = AD2CH4DATA;

                if(NULL != ADC2_ChannelHandler)
                {
                    (*ADC2_ChannelHandler)(channel, adcVal);
                }
                if(NULL != ADC2_Result32BitChannelHandler)
                {
                    (*ADC2_Result32BitChannelHandler)(channel, adcVal);
                }
            }
            break;
        default:
            break;
    }            
}

void ADC2_ComparatorCallbackRegister(void(*callback)(enum ADC2_CMP comparator))
{
    if(NULL != callback)
    {
        ADC2_ComparatorHandler = callback;
    }
}

void __attribute__ ((weak)) ADC2_ComparatorCallback (enum ADC2_CMP comparator)
{ 
    (void)comparator;
} 



