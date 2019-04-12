/******************************************************************************
* Title                 :   GPIO driver source file 
* Filename              :   gpio.c
* Author                :   Maximiliano Valencia
* Origin Date           :   28/03/2019
* Version               :   1.0.0
* Compiler              :   avr-gcc
* Target                :   AVR
* Notes                 :   None
******************************************************************************/
/*! @file        gpio.c
 *  @brief       GPIO driver implementation
 *
 *  To use the GPIO driver, include this header file as follows:
 *  @code
 *      #include "gpio.h"
 *  @endcode
 *
 *  ## Overview ##
 *  The GPIO driver implements functions to write and read the state of a GPIO 
 *  pin.
 *
 *  ## Usage ##
 *
 *  To use the GPIO driver, the GPIO pin must be first initialized using the
 *  gpio_init_pin function passing as parameter the GPIO port address, the 
 *  GPIO pin number and the mode of operation of the GPIO.
 * 
 *  The driver uses the fact that the GPIO addresses are located together in 
 *  the following order: PINX, DDRX and PORTX. For example,
 *      PINB -> 0x23
 *      DDRB -> 0x24
 *      PORTB -> 0x25
 *  This is used so that the user only pass the GPIO pin port address and then 
 *  the driver offsets this address to access the PINX and DDRX addresses.
 * 
 *  The following code example initializes two pins, writes to a pin, and
 *  then reads the state of a pin.
 * 
 *  @code
 *      #include "gpio.h"
 *
 *      gpio_pin_state state;
 *
 *      gpio_init_pin(&PORTB, PB1, GPIO_PIN_OUTPUT);
 *      gpio_init_pin(&PORTB, PB2, GPIO_PIN_INPUT);
 * 
 *      gpio_write_pin(&PORTB, PB1, GPIO_PIN_HIGH);
 *      state = gpio_read_pin(&PORTB, PB2);
 *  @endcode
 */
/******************************************************************************
* Includes
******************************************************************************/
#include "gpio.h"

/******************************************************************************
* Module Preprocessor Constants
******************************************************************************/
/*! 
 * @brief PINX register offset from PORTX register 
 */
#define OFFSET_PIN      0x02
/*! 
 * @brief DDRX register offset from PORTX register 
 */
#define OFFSET_DDR      0x01
/*! 
 * @brief PORTX register offset from PORTX register 
 */
#define OFFSET_PORT     0x00

/******************************************************************************
* Module Preprocessor Macros
******************************************************************************/
/*! Macro used to dereference an IO memory address */
#define MMIO(addr)      (*(volatile uint8_t *)(addr))

/******************************************************************************
* Module Typedefs
******************************************************************************/

/******************************************************************************
* Module Variable Definitions
******************************************************************************/

/******************************************************************************
* Private Function Prototypes
******************************************************************************/

/******************************************************************************
* Function Definitions
******************************************************************************/

/*****************************************************************************/
/*!
 * @addtogroup gpio
 * @{
 */
/*****************************************************************************/

/*****************************************************************************/
/*!
 * Function used to initialize a GPIO pin.
 * 
 * @param port GPIO pin port address (ex. &PORTA).
 * @param pin GPIO pin number (ex. PA1).
 * @param mode GPIO pin mode of operation: GPIO_INPUT, GPIO_INPUT_PULLUP or 
 *             GPIO_OUTPUT.
 * 
 * @return None.
 * 
 * \b Example:
 * @code
 *      gpio_init_pin(&PORTA, PA1, GPIO_PIN_OUTPUT);
 * @endcode
 * 
 */
/*****************************************************************************/
void gpio_init_pin(uint8_t* port, uint8_t pin, gpio_pin_mode mode)
{
    if (mode == GPIO_PIN_INPUT)
    {
        MMIO(port - OFFSET_DDR) &= ~_BV(pin);
        MMIO(port - OFFSET_PORT) &= ~_BV(pin);
    }
    else if (mode == GPIO_PIN_INPUT_PULLUP)
    {
        MMIO(port - OFFSET_DDR) &= ~_BV(pin);
        MMIO(port - OFFSET_PORT) |= _BV(pin);
    }
    else
    {
        MMIO(port - OFFSET_DDR) |= _BV(pin);
    }
}

/*****************************************************************************/
/*!
 * Function used to write a value to a GPIO pin.
 * 
 * @pre GPIO pin must be first initialized using the gpio_init_pin function.
 * 
 * @param port GPIO pin port address (ex. &PORTA).
 * @param pin GPIO pin number (ex. PA1).
 * @param state State to write to the pin: GPIO_PIN_LOW or GPIO_PIN_HIGH.
 * 
 * @return None.
 * 
 * \b Example:
 * @code
 *      gpio_init_pin(&PORTA, PA1, GPIO_PIN_OUTPUT);
 *      gpio_write_pin(&PORTA, PA1, GPIO_PIN_HIGH);
 * @endcode
 * 
 */
/*****************************************************************************/
void gpio_write_pin(uint8_t* port, uint8_t pin, gpio_pin_state state)
{
    if (state == GPIO_PIN_LOW)
    {
        MMIO(port - OFFSET_PORT) &= ~_BV(pin);
    }
    else
    {
        MMIO(port - OFFSET_PORT) |= _BV(pin);
    }
}

/*****************************************************************************/
/*!
 *
 * \b Description:
 * Function used to toggle the value of a GPIO pin.
 * 
 * @pre GPIO pin must be first initialized using the gpio_init_pin function.
 * 
 * @param port GPIO pin port address (ex. &PORTA).
 * @param pin GPIO pin number (ex. PA1).
 * 
 * @return None.
 * 
 * \b Example:
 * @code
 *      gpio_init_pin(&PORTA, PA1, GPIO_PIN_OUTPUT);
 *      gpio_toggle_pin(&PORTA, PA1);
 * @endcode
 * 
 */
/*****************************************************************************/
void gpio_toggle_pin(uint8_t* port, uint8_t pin)
{
    MMIO(port - OFFSET_PORT) ^= _BV(pin);
}

/*****************************************************************************/
/*!
 * Function used to read the state of a GPIO pin.
 * 
 * @pre GPIO pin must be first initialized using the gpio_init_pin function.
 * 
 * @param port GPIO pin port address (ex. &PORTA).
 * @param pin GPIO pin number (ex. PA1).
 * 
 * @return The current state of the GPIO pin: GPIO_PIN_LOW or GPIO_PIN_HIGH.
 * 
 * \b Example:
 * @code
 *      gpio_pin_state state;
 *
 *      gpio_init_pin(&PORTA, PA1, GPIO_PIN_OUTPUT);
 *      state = gpio_read_pin(&PORTA, PA1);
 * @endcode
 * 
 */
/*****************************************************************************/
gpio_pin_state gpio_read_pin(uint8_t* port, uint8_t pin)
{
    uint8_t state = 0;

    state = (MMIO(port - OFFSET_PIN) & _BV(pin));
    if (state)
    {
        return GPIO_PIN_HIGH;
    }
    else
    {
        return GPIO_PIN_LOW;
    }
}

/*****************************************************************************/
/*!
 * Close the Doxygen group.
 * @}
 */
/*****************************************************************************/
