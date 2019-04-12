/******************************************************************************
* Title                 :   Sigfox Wisol header file  
* Filename              :   sigfox_wisol.h
* Author                :   Maximiliano Valencia
* Origin Date           :   29/03/2019
* Version               :   1.0.0
* Compiler              :   avr-gcc
* Target                :   AVR
* Notes                 :   None
******************************************************************************/
/*! @file sigfox_wisol.h
 *  @brief Defines the Sigfox Wisol function definitions.
 * 
 *  This is the header file for the definition of the Sigfox Wisol function 
 *  prototypes of the methods of the driver.
 */

#ifndef __SIGFOX_WISOL_H
#define __SIGFOX_WISOL_H

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* Includes
******************************************************************************/
#include "gpio.h"
#include "uart.h"

/******************************************************************************
* Preprocessor Constants
******************************************************************************/

/******************************************************************************
* Configuration Constants
******************************************************************************/

/******************************************************************************
* Macros
******************************************************************************/

/******************************************************************************
* Typedefs
******************************************************************************/

/******************************************************************************
* Variables
******************************************************************************/

/******************************************************************************
* Function Prototypes
******************************************************************************/
void sigfox_wisol_init(void);
void sigfox_wisol_get_id(char* id, uint8_t size);
void sigfox_wisol_get_pac(char* pac, uint8_t size);
void sigfox_wisol_send_msg(const char* msg, uint8_t size);

#ifdef __cplusplus
}
#endif

#endif /* __SIGFOX_WISOL_H */
