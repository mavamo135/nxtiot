#include "nxtiot_board.h"
#include "gpio.h"
#include "uart.h"
#include "sigfox_wisol.h"

uint8_t serialAvailable = 0;

int main(void)
{
    char fooStr[] = "Checkpoint!\n";
    char str[20];

    gpio_init_pin(LED_PORT, LED_PIN, GPIO_PIN_OUTPUT);
    gpio_init_pin(SW_PORT, SW_PIN, GPIO_PIN_INPUT);

    // Set LOW to LED
    gpio_write_pin(LED_PORT, LED_PIN, GPIO_PIN_LOW);

    sigfox_wisol_init();

    sigfox_wisol_get_id(str, sizeof(str));
    uart_send(str);

    sigfox_wisol_get_pac(str, sizeof(str));
    uart_send(str);

    while (1)
    {
        gpio_write_pin(LED_PORT, LED_PIN, GPIO_PIN_HIGH);
        _delay_ms(1000);
        gpio_write_pin(LED_PORT, LED_PIN, GPIO_PIN_LOW);
        _delay_ms(1000);
    }
}
