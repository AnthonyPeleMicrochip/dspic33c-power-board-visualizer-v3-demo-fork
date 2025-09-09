/* 
 * @file    app_PBV_interface.h   
 * @author  M70027
 * @brief   Power Board Visualizer application interface 
 */

#ifndef APP_PBV_INTERFACE_H
#define	APP_PBV_INTERFACE_H

///< includes
#include <xc.h> // include processor files - each processor file is guarded.  
#include "config/config.h"

/***********************************************************************************
 * @ingroup APP_PBV
 * @brief   Power Board Visualizer TX type
 * @details This type defines if the TX Object is transmitting numbers or ASCII
 **********************************************************************************/
enum PBV_SIGNAL_ASCII_MODE 
{   
    PBV_SIGNAL_MODE    = 0,    ///< Object will transmit/receive signals 
    PBV_ASCII_MODE     = 1     ///< Object will transmit Ascii data
} ;

/***********************************************************************************
 * @ingroup APP_PBV
 * @brief   Power Board Visualizer TX Object transmission states
 * @details 
 *      These states are used to keep track of the transmission of message
 **********************************************************************************/
enum PBV_MESSAGE_TX_STATE
{    
    PBV_MESSAGE_TRANSMITTED     = 0,    ///< Message transmitted. successful transmit
    PBV_MESSAGE_INIT            = 1,    ///< Init State. Only Send Messages in this State    
    PBV_MESSAGE_TRANSMIT_START  = 2,    ///< Start Transmitting message
    PBV_MESSAGE_TRANSMITTING    = 3,    ///< Transmitting Message
    PBV_MESSAGE_TX_ERROR        = 4    ///< if some error happens. unsuccessful transmit
};
typedef enum PBV_MESSAGE_TX_STATE PBV_MESSAGE_TX_STATE_t;

/***********************************************************************************
 * @ingroup APP_PBV
 * @brief   Power Board Visualizer RX Object Receiving states
 * @details 
 *      These states are used to keep track of the receiving of messages
 **********************************************************************************/
enum PBV_MESSAGE_RX_STATE
{
    PBV_MESSAGE_RECEIVED = 0,           ///< Message Received
    PBV_MESSAGE_READY_TO_RECEIVE = 1,   ///< Message Reception triggered
    PBV_STATE_RECEIVING = 2,            ///< Message beinf received
    PBV_MESSAGE_RX_ERROR = 3           ///< if some error happens (CRC ?)
};
typedef enum PBV_MESSAGE_RX_STATE PBV_MESSAGE_RX_STATE_t;

/*********************************************************************************
 * @ingroup APP_PBV
 * @var     func_p
 * @brief   function pointer typedef for callbacks
 * @param   length - length of passed eight bit buffer
 * @param   ptr    - pointer to eight bit data
 * @details function pointer typedef for callback after receiving data. 
 *********************************************************************************/
typedef void (*func_p)(uint16_t, uint8_t *);    

/*********************************************************************************
 * @ingroup APP_PBV
 * @struct PBV_Datatype_TX_t
 * @brief   
 * @details pbv App TX data type definition structure   
 *********************************************************************************/

typedef struct { 
    uint16_t Length;                                ///< Length of transmitted message in Bytes
    uint32_t PBV_Protcol_ID;                        ///< Protocol ID
    uint16_t current_offset;                        ///< current offset
    enum PBV_SIGNAL_ASCII_MODE  PBV_Signal_Ascii;   ///< Object will transmit Signals or ASCII
    PBV_MESSAGE_TX_STATE_t  PBV_Message_State;      ///< State of the TX object
    uint8_t * Data_Buffer;                          ///< Pointer to the data to be transmitted
    uint8_t ptr[64];
}PBV_Datatype_TX_t;

/*********************************************************************************
 * @ingroup 
 * @struct     PBV_Datatype_RX_t
 * @brief   
 * @details pbv App RX data type definition structure 
 *********************************************************************************/
typedef struct { 
    uint16_t Length;                                ///< Length of received message in Bytes
    uint32_t PBV_Protcol_ID;                        ///< Protocol ID of the received message
    func_p Callback_Function ;                      ///< Callback function 
    PBV_MESSAGE_RX_STATE_t  PBV_Message_State;      ///< State of the received message
    uint8_t * Data_Buffer;                          ///< Received Data pointer
}PBV_Datatype_RX_t;



typedef enum datatype 
{
    TYPE_U16,
    TYPE_S16,
    TYPE_U32,
    TYPE_S32,
    TYPE_FLO,
    TYPE_DOUB,
} datatype;


/////////////
typedef union __attribute__ ((packed)) signal_Float32_union{
    float data;
    uint8_t bytes[4];
} signal_float32_union_t;

typedef struct signal_float32_struct{
    datatype type;
    signal_float32_union_t signal_float32;
} signal_float32_t;

//signal_float32_t sample_float_32;

/////////////
typedef union __attribute__ ((packed)) signal_double64_union{
    long double data;
    uint8_t bytes[8];
} signal_double64_union_t;

typedef struct signal_double64_struct{
    datatype type;
    signal_double64_union_t signal_double64;
} signal_double64_t;

//signal_double64_t sample_double_64;

////////////
typedef union __attribute__ ((packed)) signal_U32_union{
    uint32_t data;
    uint8_t bytes[4];
} signal_U32_union_t;

typedef struct signal_U32_struct{
    datatype type;
    signal_U32_union_t signal_U32;
} signal_U32_t;

//signal_U32_t sample_unsigned_32;


/////////////
typedef union __attribute__ ((packed)) signal_S32_union{
    int32_t data;
    uint8_t bytes[4];
} signal_S32_union_t;

typedef struct signal_S32_struct{
   datatype type;
   signal_S32_union_t signal_S32;
} signal_S32_t;

//signal_S32_t sample_signed_32;

/////////////
typedef union __attribute__ ((packed)) signal_U16_union{
    uint16_t data;
    uint8_t bytes[2];
} signal_U16_union_t;

typedef struct signal_U16_struct{
   datatype type;
   signal_U16_union_t signal_U16;
} signal_U16_t;

//signal_U16_t sample_unsigned_16;

////////////
typedef union __attribute__ ((packed)) signal_S16_union{
    int16_t data;
    uint8_t bytes[2];
} signal_S16_union_t;

typedef struct signal_S16_struct{
   datatype type;
   signal_S16_union_t signal_S16;
} signal_S16_t;

//signal_S16_t sample_signed_16;

///< functions
void app_PBV_Init(PBV_Datatype_TX_t * system_to_PBV, PBV_Datatype_TX_t * system_To_PBV_Ascii, PBV_Datatype_RX_t *App_PBV_To_System_Ptr);
void app_Send_To_PBV (PBV_Datatype_TX_t * ptr);
void app_Receive_From_PBV(PBV_Datatype_RX_t * ptr);
void app_Read_Received_From_PBV(PBV_Datatype_RX_t * ptr);

void PBV_Change_from_Sixteen_to_Eight(uint16_t * sixteen_ptr, uint8_t * eight_ptr, uint16_t length);
void PBV_Change_from_Eight_to_Sixteen(uint8_t * eight_ptr, uint16_t * sixteen_ptr, uint16_t length);

void add_signal_to_frame(PBV_Datatype_TX_t* frame_object, void* signal_to_be_added, datatype type);

void app_PBV_Re_Init(PBV_Datatype_TX_t * ptr);

void app_PBV_Task_10ms(void);
void app_PBV_Task_100us(void);

#endif	/*  APP_PBV_INTERFACE_H */
