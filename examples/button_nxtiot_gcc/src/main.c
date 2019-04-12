#include "nxtiot_board.h"
#include "gpio.h"
#include "uart.h"
#include "sigfox_wisol.h"

uint8_t serialAvailable = 0;

int main(void)
{
    char fooStr[] = "Hello from NXTIOT board!\n";
    char str[20];

    gpio_init_pin(LED_PORT, LED_PIN, GPIO_PIN_OUTPUT);
    gpio_init_pin(SW_PORT, SW_PIN, GPIO_PIN_INPUT);
    gpio_write_pin(LED_PORT, LED_PIN, GPIO_PIN_LOW);

    while (1)
    {
        if (gpio_read_pin(SW_PORT, SW_PIN) == GPIO_PIN_LOW)
        {
            gpio_write_pin(LED_PORT, LED_PIN, GPIO_PIN_HIGH);
            _delay_ms(1000);
            gpio_write_pin(LED_PORT, LED_PIN, GPIO_PIN_LOW);
            uart_send(fooStr);
        }

        if (serialAvailable == 1)
        {
            serialAvailable = 0;
            uart_read(str, sizeof(str));
            uart_send(str);
            uart_flush();
            uart_enable_rx_isr();
        }
    }
}

ISR(USART_RX_vect)
{
    serialAvailable = 1;
    uart_disable_rx_isr();
}