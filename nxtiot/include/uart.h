/******************************************************************************
* Title                 :   UART header file  
* Filename              :   uart.h
* Author                :   Maximiliano Valencia
* Origin Date           :   02/04/2019
* Version               :   1.0.0
* Compiler              :   avr-gcc
* Target                :   AVR
* Notes                 :   None
******************************************************************************/
/*! @file uart.h
 *  @brief Defines the UART function definitions.
 * 
 *  This is the header file for the definition of the uart function prototypes
 *  of the methods of the driver.
 */

#ifndef __UART_H
#define __UART_H

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* Includes
******************************************************************************/
#include <stdint.h>
#include <string.h>
#include "nxtiot_board.h"

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
void uart_init(void);
void uart_send(const char* str);
void uart_read(char* str, uint8_t size);
void uart_enable_rx_isr(void);
void uart_disable_rx_isr(void);
void uart_flush(void);

#ifdef __cplusplus
}
#endif

#endif /* __UART_H */
