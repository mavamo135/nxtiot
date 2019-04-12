/******************************************************************************
* Title                 :   Sigfox Wisol driver source file 
* Filename              :   sigfox_wisol.c
* Author                :   Maximiliano Valencia
* Origin Date           :   29/03/2019
* Version               :   1.0.0
* Compiler              :   avr-gcc
* Target                :   AVR
* Notes                 :   None
******************************************************************************/
/*! @file        sigfox_wisol.c
 *  @brief       Sigfox Wisol driver implementation
 *
 *  To use the Sigfox Wisol driver, include this header file as follows:
 *  @code
 *      #include "sigfox_wisol.h"
 *  @endcode
 *
 *  ## Overview ##
 *  The Sigfox Wisol driver implements funtions to write and read to the Sigfox
 *  Wisol module via ATT commands.
 *
 *  ## Usage ##
 *
 *  To use the Sigfox Wisol driver, the driver must be first initialized using 
 *  the sigfox_wisol_init function.
 * 
 *  The following code example initializes the module and reads the ID and PAC 
 *  from the module.
 * 
 *  @code
 *      #include "sigfox_wisol.h"
 *
 *      char str[20];
 * 
 *      sigfox_wisol_init();
 * 
 *      sigfox_wisol_get_id(str, sizeof(str));
 *      sigfox_wisol_get_pac(str, sizeof(str));
 *  @endcode
 */
/******************************************************************************
* Includes
******************************************************************************/
#include "sigfox_wisol.h"

/******************************************************************************
* Module Preprocessor Constants
******************************************************************************/
const char* sigfox_wisol_cmds[] = 
{
    "AT\n",               /*! Attention command / check status */
    "AT$SB=%s\n",         /*! Send Bit (and downlink flag) */
    "AT$SF=%s%s\n",       /*! Send Frame (and bit) */
    "AT$I=10\n",          /*! Get chip information */
    "AT$I=11\n",          /*! Get chip information */
    "AT$P=%u\n",          /*! Set power module */
    "AT$RC\n"             /*! Module reset */
};

/******************************************************************************
* Module Preprocessor Macros
******************************************************************************/

/******************************************************************************
* Module Typedefs
******************************************************************************/
/*!
 * Commands as indexes into command array above.
 * Commands defined here are implemented, the rest are not (yet)
 */
typedef enum {
    WISOL_CMD_STATUS = 0,
    WISOL_CMD_SEND_BIT = 1,
    WISOL_CMD_SEND_FRAME = 2,
    WISOL_CMD_INFORMATION_ID = 3,
    WISOL_CMD_INFORMATION_PAC = 4,
    WISOL_CMD_SET_POWER_MODE = 5,
    WISOL_CMD_RESET_MODULE = 6
} sigfox_wisol_cmds_enum;

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
 * @addtogroup sigfox_wisol
 * @{
 */
/*****************************************************************************/

/*****************************************************************************/
/*!
 * Function used to initialize the Sigfox Wisol module.
 * 
 * This function initializes the UART and initializes the Wisol enable pin.
 * 
 * @return None. 
 */
/*****************************************************************************/
void
sigfox_wisol_init(void)
{
    gpio_init_pin(WISOL_EN_PORT, WISOL_EN_PIN, GPIO_PIN_OUTPUT);
    uart_init();
}

/*****************************************************************************/
/*!
 * Function used to get the ID of the Sigfox Wisol module.
 * 
 * @param id Pointer to the string where the ID will be written.
 * @param size Size of the string.
 * 
 * @return None. 
 */
/*****************************************************************************/
void
sigfox_wisol_get_id(char* id, uint8_t size)
{
    gpio_write_pin(WISOL_EN_PORT, WISOL_EN_PIN, GPIO_PIN_HIGH);
    _delay_ms(1000);

    uart_send(sigfox_wisol_cmds[WISOL_CMD_INFORMATION_ID]);
    uart_read(id, size);

    _delay_ms(1000);
    gpio_write_pin(WISOL_EN_PORT, WISOL_EN_PIN, GPIO_PIN_LOW);
}

/*****************************************************************************/
/*!
 * Function used to get the PAC of the Sigfox Wisol module.
 * 
 * @param pac Pointer to the string where the PAC will be written.
 * @param size Size of the string.
 * 
 * @return None. 
 */
/*****************************************************************************/
void
sigfox_wisol_get_pac(char* pac, uint8_t size)
{
    gpio_write_pin(WISOL_EN_PORT, WISOL_EN_PIN, GPIO_PIN_HIGH);
    _delay_ms(1000);

    uart_send(sigfox_wisol_cmds[WISOL_CMD_INFORMATION_PAC]);
    uart_read(pac, size);

    _delay_ms(1000);
    gpio_write_pin(WISOL_EN_PORT, WISOL_EN_PIN, GPIO_PIN_LOW);
}

/*****************************************************************************/
/*!
 * Function used to send a message using the Sigfox Wisol module.
 * 
 * @param msg Pointer to the string that store the message to be sent.
 * @param size Size of the string.
 * 
 * @return None. 
 */
/*****************************************************************************/
void
sigfox_wisol_send_msg(const char* msg, uint8_t size)
{
    gpio_write_pin(WISOL_EN_PORT, WISOL_EN_PIN, GPIO_PIN_HIGH);
    _delay_ms(1000);

    uart_send(sigfox_wisol_cmds[WISOL_CMD_SEND_FRAME]);

    _delay_ms(1000);
    gpio_write_pin(WISOL_EN_PORT, WISOL_EN_PIN, GPIO_PIN_LOW);
}

/*****************************************************************************/
/*!
 * Close the Doxygen group.
 * @}
 */
/*****************************************************************************/
