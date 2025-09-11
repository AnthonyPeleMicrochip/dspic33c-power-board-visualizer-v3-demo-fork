#include "drv_adc.h"

/*********************************************************************************
 * @ingroup adc-drv-private-variables
 * @var     ADC_VALUES_t
 * @brief   adc values object
 * @details 'adc_val' is the object providing access to all the adc values.
 **********************************************************************************/
ADC_VALUES_t adc_val;
ADC_VALUES_t * adc_val_pt = &adc_val;


/*********************************************************************************
 * @ingroup adc-drv-private
 * @var     counter
 * @brief   ticking away
 * @details 
 *          to sample every 5ms
 **********************************************************************************/
uint8_t static counter = 0;



/***********************************************************************************
 * @ingroup drv-adc-public-functions
 * @fn     drv_adc_Task_1ms
 * @param  void
 * @return nothing
 * @brief this function needs to be called every 1ms
 *        it contains the code to trigger the ADC from software
 * @details
 *   this function needs to be called every 1ms. It triggers the ADC conversion. Since all are
 * enabled through Interrupts, the sampled result is stored in the adc data object as soon as 
 * it is available.
 * it also uses the PG1PER (Period register of the PWM generator 1 and ADV value at TP5 to 
 * update the duty cycle)
  **********************************************************************************/

void drv_adc_Task_1ms(){
    
    ADC1_ChannelSoftwareTriggerEnable (ADC1_Channel3);
    ADC2_ChannelSoftwareTriggerEnable (ADC2_Channel4);
    ADC3_ChannelSoftwareTriggerEnable (ADC3_Channel5);
    ADC4_ChannelSoftwareTriggerEnable (ADC4_Channel2);
    
    
    // every 5ms
    if (counter++>4){
        if (adc_val.TP5 * 8 > PG1PER)   // PER 32000; 
            adc_val.pwm_dc_val = PG1PER  ;        
        else if (adc_val.TP5 * 8 < 128)   
            adc_val.pwm_dc_val = 128  ;
        else
            adc_val.pwm_dc_val = adc_val.TP5 * 8; 
        
        PWM_DutyCycleSet(1, adc_val.pwm_dc_val);
        counter = 0;
    }

}
/***********************************************************************************
 * @ingroup drv-adc-public-functions
 * @fn     drv_adc_Task_1ms
 * @param  void
 * @return nothing
 * @brief up and down counter
  **********************************************************************************/
void drv_adc_Task_1s() {
    if (adc_val.upcount++ > 65500)  adc_val.upcount = 0 ;
    if (adc_val.downcount-- < 10)   adc_val.downcount = 65500 ;
}
/***********************************************************************************
 * @ingroup drv-adc-public-functions
 * @fn     drv_adc_init
 * @param  void
 * @return nothing
 * @brief initializes adcval values
  **********************************************************************************/
void drv_adc_init() {
    adc_val.upcount = 0;
    adc_val.downcount = 65500;
    adc_val.TP12 = 0;
    adc_val.TP5 = 0;
    adc_val.TP13 = 0;
    adc_val.TP14 = 0;
}

/***********************************************************************************
 * @ingroup drv-adc-internal-functions
 * @fn     AD1CH3Interrupt
 * @param  void
 * @return nothing
 * @brief ADC 1 Channel 3 Interrupt Service Routine
  **********************************************************************************/
void __attribute__((interrupt)) _AD1CH3Interrupt(void)
{
   adc_val.TP13 = AD1CH3DATA;
   IFS5bits.AD1CH3IF = 0;
}

/***********************************************************************************
 * @ingroup drv-adc-internal-functions
 * @fn     AD2CH4Interrupt
 * @param  void
 * @return nothing
 * @brief ADC 2 Channel 4 Interrupt Service Routine
  **********************************************************************************/
void __attribute__((interrupt)) _AD2CH4Interrupt(void)
{
  adc_val.TP12 = AD2CH4DATA;
      
  IFS5bits.AD2CH4IF = 0;
}
/***********************************************************************************
 * @ingroup drv-adc-internal-functions
 * @fn     AD3CH5Interrupt
 * @param  void
 * @return nothing
 * @brief ADC 3 Channel 5 Interrupt Service Routine
  **********************************************************************************/
void __attribute__((interrupt)) _AD3CH5Interrupt(void)
{
  adc_val.TP5 = AD3CH5DATA;
  IFS6bits.AD3CH5IF = 0;
}
/***********************************************************************************
 * @ingroup drv-adc-internal-functions
 * @fn     AD4CH2Interrupt
 * @param  void
 * @return nothing
 * @brief ADC 4 Channel 2 Interrupt Service Routine
  **********************************************************************************/
void __attribute__((interrupt)) _AD4CH2Interrupt(void)
{
  adc_val.TP14 = AD4CH2DATA; 
  IFS7bits.AD4CH2IF = 0;
}

