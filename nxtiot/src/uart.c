/******************************************************************************
* Title                 :   UART driver source file 
* Filename              :   uart.c
* Author                :   Maximiliano Valencia
* Origin Date           :   02/04/2019
* Version               :   1.0.0
* Compiler              :   avr-gcc
* Target                :   AVR
* Notes                 :   None
******************************************************************************/
/*! @file        uart.c
 *  @brief       UART driver implementation
 *
 *  To use the UART driver, include this header file as follows:
 *  @code
 *      #include "uart.h"
 *  @endcode
 *
 *  ## Overview ##
 *  The UART driver implements functions initialize, write and read from the
 *  UART.
 *
 *  ## Usage ##
 *
 *  To use the UART driver, the UART must be first initialized using the
 *  uart_init function.
 * 
 *  The following code example initializes the UART and writes and receives 
 *  data from the UART.
 * 
 *  @code
 *      #include "uart.h"
 *
 *      char rxStr[20];
 *      char txStr[] = "Hello!\n";
 * 
 *      uart_send(fooStr); 
 *      uart_read(rxStr, sizeof(rxStr));
 *  @endcode
 */
/******************************************************************************
* Includes
******************************************************************************/
#include "uart.h"

/******************************************************************************
* Module Preprocessor Constants
******************************************************************************/
/*! UCSR0A Memory Address */
#define UCSR0A_ADDR     &UCSR0A
/*! UCSR0B Memory Address */
#define UCSR0B_ADDR     &UCSR0B
/*! UCSR0C Memory Address */
#define UCSR0C_ADDR     &UCSR0C
/*! UBBR0 Low Memory Address */
#define UBRR0L_ADDR     &UBRR0L
/*! UBBR0 High Memory Address */
#define UBRR0H_ADDR     &UBRR0H
/*! UDR0 Memory Address */
#define UDR0_ADDR       &UDR0
/*! Uart baud rate constant */
#define BAUD_RATE       9600
/*! Uart baud rate prescaler */
#define BAUD_PRESCALE   ((F_CPU / (16UL * BAUD_RATE)) - 1)

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
static void _uart_send_char(unsigned char lChar);
static unsigned char _uart_read_char(void);

/******************************************************************************
* Function Definitions
******************************************************************************/

/*****************************************************************************/
/*!
 * @addtogroup uart
 * @{
 */
/*****************************************************************************/

/*****************************************************************************/
/*!
 * Function used to initialize the UART.
 * 
 * The UART baud rate is initialized using the BAUD_RATE constant defined in
 * this file. The configuration of the UART port is the following:
 *  * Double speed asynchronous mode disabled
 *  * RX and TX enabled
 *  * Asynchronous operation mode
 *  * Parity disabled
 *  * Serial frame with 8 data bits and 1 stop bit
 * 
 * @return None.
 * 
 * \b Example:
 * @code
 *      uart_init();
 * @endcode
 * 
 */
/*****************************************************************************/
void
uart_init(void)
{
    // Set baud rate value
    UBRR0H = (BAUD_PRESCALE >> 8);
    UBRR0L = BAUD_PRESCALE;

    // Disable double speed - asynch mode
    UCSR0A &= ~_BV(U2X0);

    // Enable RX and TX
    UCSR0B |= (_BV(RXEN0) | _BV(TXEN0));

    // Set asynchronous operation mode
    UCSR0C &= ~(_BV(UMSEL01) | _BV(UMSEL00));
    // Disable parity
    UCSR0C &= ~(_BV(UPM01) | _BV(UPM00));
    // Set serial frame: 8 data bits, 1 stop bit
    UCSR0C |= (_BV(UCSZ01) | _BV(UCSZ00));
    UCSR0C &= ~_BV(USBS0);
}

/*****************************************************************************/
/*!
 * Function used to send a string through the UART.
 * 
 * @param str Pointer to the string to be sent. Must be NULL terminated.
 * 
 * @return None.
 * 
 * \b Example:
 * @code
 *      char fooStr[] = "Hello!\n";
 *      uart_send(fooStr); 
 *      // OR
 *      uart_send(&fooStr[0]);
 * @endcode
 * 
 */
/*****************************************************************************/
void
uart_send(const char* str)
{
    while (*str != 0x00)
    {
        _uart_send_char(*str);
        str++;
    }
}

/*****************************************************************************/
/*!
 * Function used to read a string from the UART.
 * 
 * This functions read the characters received from UART until a new line ('\n)
 * character is received or the UART receives more elements than the size of 
 * the string.
 * 
 * @param str Pointer to the string where the received string will be written.
 * @param size Size of the string.
 * 
 * @return None.
 * 
 * \b Example:
 * @code
 *      char fooStr[20];
 *      uart_read(fooStr, sizeof(fooStr)); 
 *      // OR
 *      uart_send(&fooStr[0], sizeof(fooStr));
 * @endcode
 * 
 */
/*****************************************************************************/
void
uart_read(char* str, uint8_t size)
{
    uint8_t i = 0;
    unsigned char data = 0x00;

    memset((void *) str, 0x00, size);

    while ( (i < (size-1)) && ((data = _uart_read_char()) != '\n') )
    {
        *str++ = data;
        i++;
    }

    *str = '\0';
}

/*****************************************************************************/
/*!
 * Function used to enable the UART RX interrupt.
 * 
 * @return None.
 */
/*****************************************************************************/
void
uart_enable_rx_isr(void)
{
    // Enable RX interrupt
    UCSR0B |= _BV(RXCIE0);
}

/*****************************************************************************/
/*!
 * Function used to enable the UART TX interrupt.
 * 
 * @return None.
 */
/*****************************************************************************/
void
uart_disable_rx_isr(void)
{
    // Disable RX interrupt
    UCSR0B &= ~_BV(RXCIE0);
}

/*****************************************************************************/
/*!
 * Function used to flush all the available characters in the UART.
 * 
 * @return None.
 */
/*****************************************************************************/
void
uart_flush(void)
{
    unsigned char dummy;
    
    while ( UCSR0A & _BV(RXC0) ) dummy = UDR0;
}

/*****************************************************************************/
/*!
 * Function used to send a character through the UART.
 * 
 * @param data Character to be sent.
 * 
 * @return None.
 */
/*****************************************************************************/
static void
_uart_send_char(unsigned char data)
{
    // Wait until the trasmit buffer is empty
    while ( !( UCSR0A & _BV(UDRE0) ) );

    // Put the data in the buffer, sends the data
    UDR0 = data;
}

/*****************************************************************************/
/*!
 * Function used to read a character from the UART.
 * 
 * @param None.
 * 
 * @return Character received from the UART.
 */
/*****************************************************************************/
static unsigned char
_uart_read_char(void)
{
    // Wait until data is received
    while ( !( UCSR0A & _BV(RXC0) ) );

    return UDR0;
}

/*****************************************************************************/
/*!
 * Close the Doxygen group.
 * @}
 */
/*****************************************************************************/
