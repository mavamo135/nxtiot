/******************************************************************************
* Title                 :   NXTIOT board configuration header file  
* Filename              :   nxtiot_board.h
* Author                :   Maximiliano Valencia
* Origin Date           :   28/03/2019
* Version               :   1.0.0
* Compiler              :   avr-gcc
* Target                :   AVR
* Notes                 :   None
******************************************************************************/
/** @file nxtiot_board.h
 *  @brief Defines the configuration of the NXTIOT board.
 * 
 *  This is the header file for the configuration of the pins used by the 
 *  NXTIOT board.
 * 
 */

#ifndef __NXTIOT_BOARD_H
#define __NXTIOT_BOARD_H

/******************************************************************************
* Includes
******************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/******************************************************************************
* Preprocessor Constants
******************************************************************************/
/*! CPU Clock Frequency */
#ifndef F_CPU
    #define F_CPU 16000000
#endif

/*! CPU Module */
#ifndef __AVR_ATmega328P__
    #define __AVR_ATmega328P__
#endif

/*!
 * Ports Memory Addresses
 * 
 * @note Have to reference the ports because the AVR library (avr/io.h) macro 
 *       dereferences the address of the GPIO ports.
 */
/*! Port A Memory Address */
#define PORTA_ADDR      &PORTA
/*! Port B Memory Address */
#define PORTB_ADDR      &PORTB
/*! Port C Memory Address */
#define PORTC_ADDR      &PORTC
/*! Port D Memory Address */
#define PORTD_ADDR      &PORTD

/******************************************************************************
* Configuration Constants
******************************************************************************/

/**** Digital IO Pins Definitions ********************************************/

/*! On board LED port address */
#define LED_PORT        PORTB_ADDR
/*! On board LED pin number */
#define LED_PIN         PB0

/*! On board push button port address */
#define SW_PORT         PORTD_ADDR
/*! On board push button pin number */
#define SW_PIN          PD6

/*! PD2 port address */
#define D2_PORT         PORTD_ADDR
/*! PD2 pin number */
#define D2_PIN          PIND2

/*! PD3 port address */
#define D3_PORT         PORTD_ADDR
/*! PD3 pin number */
#define D3_PIN          PD3

/*! PD4 port address */
#define D4_PORT         PORTD_ADDR
/*! PD4 pin number */
#define D4_PIN          PD4

/*! PD5 port address */
#define D5_PORT         PORTD_ADDR
/*! PD5 pin number */
#define D5_PIN          PD5

/*! PB1 port address */
#define B1_PORT         PORTB_ADDR
/*! PB1 pin number */
#define B1_PIN          PB1

/*! PD2 port address */
#define C2_PORT         PORTC_ADDR
/*! PD2 pin number */
#define C2_PIN          PC2

/**** ADC Pins Definitions ***************************************************/

/*! ADC0 port address */
#define ADC0_PORT       PORTC_ADDR
/*! ADC0 pin number */
#define ADC0_PIN        PC0

/*! ADC1 port address */
#define ADC1_PORT       PORTC_ADDR
/*! ADC1 pin number */
#define ADC1_PIN        PC1

/*! ADC2 port address */
#define ADC2_PORT       PORTC_ADDR
/*! ADC2 pin number */
#define ADC2_PIN        PC2

/*! ADC3 port address */
#define ADC3_PORT       PORTC_ADDR
/*! ADC3 pin number */
#define ADC3_PIN        PC3

/*! ADC4 port address */
#define ADC4_PORT       PORTC_ADDR
/*! ADC4 pin number */
#define ADC4_PIN        PC4

/*! ADC5 port address */
#define ADC5_PORT       PORTC_ADDR
/*! ADC5 pin number */
#define ADC5_PIN        PC5

/**** Sigfox Wisol Pins Definitions ******************************************/

/*! Wisol TX port address */
#define WISOL_TX_PORT   PORTD_ADDR
/*! Wisol TX pin number */
#define WISOL_TX_PIN    PD1

/*! Wisol RX port address */
#define WISOL_RX_PORT   PORTD_ADDR
/*! Wisol RX pin number */
#define WISOL_RX_PIN    PD0

/*! Wisol EN port address */
#define WISOL_EN_PORT   PORTD_ADDR
/*! Wisol EN pin number */
#define WISOL_EN_PIN    PD7

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

#endif /* __NXTIOT_BOARD_H */
