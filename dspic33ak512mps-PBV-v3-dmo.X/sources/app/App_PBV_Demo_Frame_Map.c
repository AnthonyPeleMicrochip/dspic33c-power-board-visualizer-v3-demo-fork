// MCC header files

// other header files
#include "App_PBV_Demo_Frame_Map.h"
#include "../../mcc_generated_files/system/pins.h"
#include "../device/dev_led.h"
#include "float.h"

/*********************************************************************************
 * @ingroup PBV_DEMO_FRAME_MAP
 * @def     FIRMWARE_PROTOCOL_ID
 * @brief   Protocol ID on which firmware ID is sent
 **********************************************************************************/
#define FIRMWARE_PROTOCOL_ID            0x1000          ///< Firmware ID

/*********************************************************************************
 * @ingroup PBV_DEMO_FRAME_MAP
 * @def     PBV_GUI_TO_SYSTEM_ID
 * @brief   ID on which data is received
 **********************************************************************************/
#define PBV_GUI_TO_SYSTEM_ID            0x202           ///< ID on which data is received.  

/*********************************************************************************
 * @ingroup PBV_DEMO_FRAME_MAP
 * @def     PBV_SYSTEM_TO_GUI_ID
 * @brief   ID on which data is sent
 **********************************************************************************/
#define PBV_SYSTEM_TO_GUI_ID            0x205           ///< ID on which data is sent. 

/*********************************************************************************
 * @ingroup PBV_DEMO_FRAME_MAP
 * @def     PBV_SYSTEM_TO_GUI_ID
 * @brief   ID on which log data is sent
 **********************************************************************************/
#define PBV_SYSTEM_TO_GUI_ASCII_ID      0x206           ///< ID on which log data is sent. 

/***********************************************************************************
 * @ingroup PBV_DEMO_FRAME_MAP
 * @struct  App_PBV_Demo_TX
 * @brief   Application TX object
 **********************************************************************************/
static PBV_Datatype_TX_t App_PBV_Demo_TX;          ///< Application TX object

/***********************************************************************************
 * @ingroup PBV_DEMO_FRAME_MAP
 * @struct  App_PBV_Demo_RX
 * @brief   Application RX object
 **********************************************************************************/
static PBV_Datatype_RX_t App_PBV_Demo_RX;          ///< Application RX object

/***********************************************************************************
 * @ingroup PBV_DEMO_FRAME_MAP
 * @struct  App_PBV_Demo_ASCII
 * @brief   Application TX object for ascii
 **********************************************************************************/
static PBV_Datatype_TX_t App_PBV_Demo_ASCII;       ///< Application TX object for ascii

/***********************************************************************************
 * @ingroup PBV_DEMO_FRAME_MAP
 * @def  App_PBV_Demo_TX_ptr
 * @brief   pointer to the object. this is if you want to extend the interface, and 
 * have a get function to get the pointer and transmit data from other files.
 **********************************************************************************/
static PBV_Datatype_TX_t * App_PBV_Demo_TX_Ptr = &App_PBV_Demo_TX;        ///< Application TX object pointer

/***********************************************************************************
 * @ingroup PBV_DEMO_FRAME_MAP
 * @def  App_PBV_Demo_RX_Ptr
 * @brief   pointer to the RX object. for uniform look and feel
 **********************************************************************************/
static PBV_Datatype_RX_t * App_PBV_Demo_RX_Ptr = &App_PBV_Demo_RX;        ///< Application RX object pointer

/***********************************************************************************
 * @ingroup PBV_DEMO_FRAME_MAP
 * @def  App_PBV_Demo_ASCII_Ptr
 * @brief   pointer to the Ascii object. This can be used to send log data from other 
 * files by getting this pointer
 **********************************************************************************/
static PBV_Datatype_TX_t * App_PBV_Demo_ASCII_Ptr = &App_PBV_Demo_ASCII;  ///< Application TX object ascii pointer


/***********************************************************************************
 * @ingroup PBV_DEMO_FRAME_MAP
 * @var     buffer_sixteen_bit 
 * @brief   buffer for 16 byte data for TX
 **********************************************************************************/
uint16_t buffer_sixteen_bit[32];

/***********************************************************************************
 * @ingroup PBV_DEMO_FRAME_MAP
 * @var     buffer_eight_bit 
 * @brief   buffer for 8 bit data for TX
 **********************************************************************************/
uint8_t buffer_eight_bit[64];

/***********************************************************************************
 * @ingroup PBV_DEMO_FRAME_MAP
 * @var     buffer_eight_bit_rx 
 * @brief   buffer for 8 bit data for RX
 **********************************************************************************/
uint16_t buffer_eight_bit_rx[32];

/***********************************************************************************
 * @ingroup PBV_DEMO_FRAME_MAP
 * @var     counter 
 * @brief   a variable to increase cycle count for the TX message
 **********************************************************************************/
static uint32_t counter = 0;

/***********************************************************************************
 * @ingroup PBV_DEMO_FRAME_MAP
 * @var     flag
 * @brief   flag to switch between firmware version TX on ID 1000, and log messages on ID 206
 **********************************************************************************/
static uint8_t flag = 0;
/***********************************************************************************
 * @ingroup PBV_DEMO_FRAME_MAP
 * @var     slider_value
 * @brief   where the slider value from GUI is stored for further processing
 **********************************************************************************/
static uint16_t slider_value = 0;

/***********************************************************************************
 * @ingroup PBV_DEMO_FRAME_MAP
 * @var     up_count
 * @brief   up counter
 **********************************************************************************/
static uint16_t up_count    =   0;

/***********************************************************************************
 * @ingroup PBV_DEMO_FRAME_MAP
 * @var     down_count
 * @brief   down counter 
 **********************************************************************************/
static uint16_t down_count  = 65535;


static uint16_t cir = 1;
static uint8_t dir = 0;
static delay_count = 0;

// custom data types

signal_U16_t slider_value_unsigned_16;
signal_U16_t app_bank1_16;
signal_U16_t app_bank2_16;
signal_U16_t up_counter_16;
signal_U16_t down_counter_16;
signal_S16_t example_16;
signal_S32_t signed_example_32;
signal_float32_t float_example_32;
signal_double64_t double_example_64;


/***********************************************************************************
 * Private Function Call Prototypes
 **********************************************************************************/
uint16_t app_round(void);
uint16_t app_Concatenate_Bank(void);
void app_Generate_data(void);
void app_Develop_callback(uint16_t length, uint8_t * data);


/***********************************************************************************
 * Public Functions Definitions
 **********************************************************************************/

/***********************************************************************************
 * @ingroup app_pbv_demo_public_function
 * @fn     app_PBV_Demo_init
 * @param  void
 * @return nothing
 * @brief this function initializes the app_pbv rx and tx objects and 
 * calls the app_pbv_init which links the CAN/RX objects
 **********************************************************************************/
void app_PBV_Demo_init(void)
{
    App_PBV_Demo_TX_Ptr->PBV_Protcol_ID        = PBV_SYSTEM_TO_GUI_ID;
    App_PBV_Demo_TX_Ptr->PBV_Signal_Ascii      = PBV_SIGNAL_MODE;
    App_PBV_Demo_TX_Ptr->PBV_Message_State     = PBV_MESSAGE_INIT;
    App_PBV_Demo_TX_Ptr->Length                = 64;

    App_PBV_Demo_RX_Ptr->PBV_Message_State     = PBV_MESSAGE_READY_TO_RECEIVE;
    App_PBV_Demo_RX_Ptr->Callback_Function     = &app_Develop_callback;

    App_PBV_Demo_ASCII_Ptr->PBV_Protcol_ID     = FIRMWARE_PROTOCOL_ID;
    App_PBV_Demo_ASCII_Ptr->PBV_Signal_Ascii   = PBV_ASCII_MODE;
    App_PBV_Demo_ASCII_Ptr->PBV_Message_State  = PBV_MESSAGE_INIT;
    App_PBV_Demo_ASCII_Ptr->Length             = 64;

    app_PBV_Init(App_PBV_Demo_TX_Ptr, App_PBV_Demo_ASCII_Ptr, App_PBV_Demo_RX_Ptr);
}


/***********************************************************************************
 * @ingroup app_pbv_demo_public_function
 * @fn     app_PBV_Demo_Task_10ms
 * @param  void
 * @return nothing
 * @brief this task checks periodically at 10 ms if any message has been received, and 
 * builds frame and transmits data
 * @details 
 *         this task is added to the main tasks file. this can be called at higher 
 * frequencies. but the user must be vary of the hardware capabilities. 
 **********************************************************************************/
void app_PBV_Demo_Task_10ms(void)
{
    // Reading received message
    if (App_PBV_Demo_RX_Ptr->PBV_Message_State == PBV_MESSAGE_RECEIVED)
    {        
        app_Read_Received_From_PBV(App_PBV_Demo_RX_Ptr);
        App_PBV_Demo_RX_Ptr->Callback_Function(App_PBV_Demo_RX_Ptr->Length, App_PBV_Demo_RX_Ptr->Data_Buffer);
        //App_PBV_Demo_RX_Ptr->PBV_Message_State = PBV_MESSAGE_READY_TO_RECEIVE;
        // data exchange
        App_PBV_Demo_TX_Ptr->Data_Buffer = App_PBV_Demo_RX_Ptr->Data_Buffer;
        // msg read. Read another
        app_Receive_From_PBV(App_PBV_Demo_RX_Ptr); 
    } 
    ///< 500ms sending 
    if (++counter > 2)
    {
        app_Generate_data();
        app_Send_To_PBV(App_PBV_Demo_TX_Ptr);
        counter = 0;
    }
}
/***********************************************************************************
 * @ingroup app_pbv_demo_public_function
 * @fn     app_PBV_Demo_Task_1s
 * @param  void
 * @return nothing
 * @brief this task periodically at 1s tranmsmits a sample log message
 * @details 
 *         this task is added to the main tasks file. this is a sample function,
 * logging from other files can be done by
 * 1. get the app_pbv_demo_ascii_ptr address
 * 2. append data to the buffer (ideally 64 bytes, or padded with spaces, else new line characters 
 *      might show undesirable visual effects)
 * 3. optionally reinit to new id.
 * 4. call app_Send_To_PBV.
 **********************************************************************************/
void app_PBV_Demo_Task_1s(void)
{
    if (App_PBV_Demo_ASCII_Ptr->PBV_Protcol_ID == FIRMWARE_PROTOCOL_ID)
    {
        App_PBV_Demo_ASCII_Ptr->Data_Buffer = "Firmware Version 1.0.0.0.......................................!";
        app_Send_To_PBV(App_PBV_Demo_ASCII_Ptr);
        App_PBV_Demo_ASCII_Ptr->PBV_Protcol_ID = PBV_SYSTEM_TO_GUI_ASCII_ID;
        flag = 1;
        return;
    }
    if (App_PBV_Demo_ASCII_Ptr->PBV_Protcol_ID == PBV_SYSTEM_TO_GUI_ASCII_ID)
    {
        if (flag) app_PBV_Re_Init(App_PBV_Demo_ASCII_Ptr);     ///< reinit to new id
        flag = 0; 
    }
    App_PBV_Demo_ASCII_Ptr->Data_Buffer = "Log Message From Protocol ID 0x206.............................\r";
    app_Send_To_PBV(App_PBV_Demo_ASCII_Ptr);
}

/***********************************************************************************
 * @ingroup app_pbv_demo_private_function
 * @fn      app_Generate_data
 * @param   void
 * @return  nothing
 * @brief   this generates a frame for transmission
 **********************************************************************************/
void app_Generate_data(void)
{
    slider_value_unsigned_16.signal_U16.data = slider_value;
    slider_value_unsigned_16.type = TYPE_U16;
    add_signal_to_frame(App_PBV_Demo_TX_Ptr, &slider_value_unsigned_16, slider_value_unsigned_16.type);
    
    app_bank1_16.signal_U16.data = app_round() ;
    app_bank1_16.type = TYPE_U16;
    add_signal_to_frame(App_PBV_Demo_TX_Ptr, &app_bank1_16, app_bank1_16.type);
    
    app_bank2_16.signal_U16.data = app_Concatenate_Bank() ;
    app_bank2_16.type = TYPE_U16;
    add_signal_to_frame(App_PBV_Demo_TX_Ptr, &app_bank2_16, app_bank2_16.type);
    
    up_counter_16.signal_U16.data =     up_count++ ;
    up_counter_16.type = TYPE_U16;
    add_signal_to_frame(App_PBV_Demo_TX_Ptr, &up_counter_16, up_counter_16.type);
    
    down_counter_16.signal_U16.data =   down_count-- ;
    add_signal_to_frame(App_PBV_Demo_TX_Ptr, &down_counter_16, TYPE_U16);

    example_16.signal_S16.data =   -1 ;
    down_counter_16.type = TYPE_U16;
    add_signal_to_frame(App_PBV_Demo_TX_Ptr, &example_16, down_counter_16.type);
    
    signed_example_32.signal_S32.data = 123;
    signed_example_32.type = TYPE_S32;
    add_signal_to_frame(App_PBV_Demo_TX_Ptr, &signed_example_32, signed_example_32.type);
    
    //double_example_64.signal_double64.data = -456464.323;
    double_example_64.type = TYPE_DOUB;
    add_signal_to_frame(App_PBV_Demo_TX_Ptr, &double_example_64, double_example_64.type);
    
    float_example_32.signal_float32.data = -4660.32;
    float_example_32.type = TYPE_FLO;
    add_signal_to_frame(App_PBV_Demo_TX_Ptr, &float_example_32, float_example_32.type);
 
    App_PBV_Demo_TX_Ptr->current_offset = 0;
    
    App_PBV_Demo_TX_Ptr->Data_Buffer = App_PBV_Demo_TX_Ptr->ptr;
    
    //App_PBV_Demo_TX_Ptr->Data_Buffer = buffer_eight_bit;
}
/***********************************************************************************
 * @ingroup app_pbv_demo_private_function
 * @fn      app_Develop_callback
 * @param   void
 * @return  nothing
 * @brief   this is a simplified sample callback. this checks for the first bytes to switch 
 *  between different actions.
 **********************************************************************************/
void app_Develop_callback(uint16_t length, uint8_t * data)
{
    PBV_Change_from_Eight_to_Sixteen(data, buffer_eight_bit_rx, length);
    uint16_t switchcase = buffer_eight_bit_rx[0];
    switch (switchcase) {
        case 0x0002:
            if (buffer_eight_bit_rx[1] == 1)
            {
                Dev_LED_On(LED_PIM_RED);
            }
            if (buffer_eight_bit_rx[1] == 0)
            {
                Dev_LED_Off(LED_PIM_RED);
            }
            break;
        case 0xFF00:
            switch(buffer_eight_bit_rx[1])
            {
                case 1:
                {
                    Dev_LED_Blink_Slow(LED_PIM_RED);
                    break;
                }
                case 2:
                {
                    Dev_LED_Blink(LED_PIM_RED);
                    break;
                }       
                case 3:
                {
                    Dev_LED_Blink_Fast(LED_PIM_RED);
                    break;
                } 
            }
            break;
        case 0xFFFF:
            slider_value = buffer_eight_bit_rx[1];
            break;
        default:
            break; 
    }
}

/***********************************************************************************
 * @ingroup app_pbv_demo_private_function
 * @fn      app_Concatenate_Bank1
 * @param   void
 * @return  uint16_t
 * @brief   this gets the current values of all the available digital IOs 
 *          on the digital power plug in module as they are mapped on to 
 *          digital power development board.
 **********************************************************************************/
uint16_t app_round(void){
    if (delay_count++>10) {
    if (dir) 
        cir = cir>>1;
    else 
        cir = cir<<1;
    
    if (cir == 0x8000) {
        dir = 1 ;
        double_example_64.signal_double64.data = LDBL_MAX;
    }
    if (cir == 0x0001) {
        dir = 0; 
        double_example_64.signal_double64.data = LDBL_MIN;
    }
    //LDBL_MAX;
    
    delay_count = 0;
    }        
    return cir;
}

/***********************************************************************************
 * @ingroup app_pbv_demo_private_function
 * @fn      app_Concatenate_Bank2
 * @param   void
 * @return  uint16_t
 * @brief   this gets the current values of all the available digital IOs 
 *          on the digital power plug in module as they are mapped on to 
 *          digital power development board.
 **********************************************************************************/
uint16_t app_Concatenate_Bank(void) {
    return (
            ((LED_DP_PIM_GetValue() << 0) & 0x0001 )
            );
    }

/*******************************************************************************
 * end of file
 *******************************************************************************/