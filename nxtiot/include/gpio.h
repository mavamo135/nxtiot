/******************************************************************************
* Title                 :   GPIO driver header file  
* Filename              :   gpio.h
* Author                :   Maximiliano Valencia
* Origin Date           :   28/03/2019
* Version               :   1.0.0
* Compiler              :   avr-gcc
* Target                :   AVR
* Notes                 :   None
******************************************************************************/
/*! @file gpio.h
 *  @brief Defines the GPIO pin state and mode enumerations.
 * 
 *  This is the header file for the definition of the function prototypes of 
 *  the methods of the driver.
 */

#ifndef __GPIO_H
#define __GPIO_H

#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************
* Includes
******************************************************************************/
#include <stdint.h>

#ifndef TEST
  #include "nxtiot_board.h"
#endif

/******************************************************************************
* Preprocessor Constants
******************************************************************************/

/******************************************************************************
* Configuration Constants
******************************************************************************/


/******************************************************************************
* Macros
******************************************************************************/
#ifdef TEST
  #define _BV(bit) (1 << (bit))
#endif

/******************************************************************************
* Typedefs
******************************************************************************/
/*!
  * @brief  GPIO Pin LOW and Pin HIGH enumeration
  */
typedef enum
{
    GPIO_PIN_LOW = 0U,
    GPIO_PIN_HIGH
} gpio_pin_state;

/*!
  * @brief  GPIO Pin INPUT, INPUT_PULLUP and OUTPUT enumeration
  */
typedef enum
{
    GPIO_PIN_INPUT = 0U,
    GPIO_PIN_INPUT_PULLUP,
    GPIO_PIN_OUTPUT
} gpio_pin_mode;

/******************************************************************************
* Variables
******************************************************************************/


/******************************************************************************
* Function Prototypes
******************************************************************************/
void gpio_init_pin(uint8_t* port, uint8_t pin, gpio_pin_mode mode);
void gpio_write_pin(uint8_t* port, uint8_t pin, gpio_pin_state state);
void gpio_toggle_pin(uint8_t* port, uint8_t pin);
gpio_pin_state gpio_read_pin(uint8_t* port, uint8_t pin);

#ifdef __cplusplus
}
#endif

#endif /* __GPIO_H */
