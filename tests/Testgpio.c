#include "unity.h"
#include "gpio.h"

// The PINX, DDRX and PORTX registers are simulated as an array of dimension 3
// because the registers are located together
uint8_t port_registers[3];
uint8_t* port_address;

void
setUp(void)
{
    for (uint8_t i = 0; i < 3; i++)
    {
        port_registers[i] = 0;
    }

    port_address = &port_registers[2];
}

void
tearDown(void)
{

}

void
test_Gpio_should_InitializePinAsInput(void)
{
    gpio_init_pin(port_address, 1, GPIO_PIN_INPUT);

    TEST_ASSERT_EQUAL_UINT8(0x00, port_registers[0]);
    TEST_ASSERT_EQUAL_UINT8(0x00, port_registers[1]);
    TEST_ASSERT_EQUAL_UINT8(0x00, port_registers[2]);
}

void
test_Gpio_should_InitializePinAsInputPullup(void)
{
    gpio_init_pin(port_address, 1, GPIO_PIN_INPUT_PULLUP);

    TEST_ASSERT_EQUAL_UINT8(0x00, port_registers[0]);
    TEST_ASSERT_EQUAL_UINT8(0x00, port_registers[1]);
    TEST_ASSERT_EQUAL_UINT8(0x02, port_registers[2]);
}

void
test_Gpio_should_InitializePinAsOutput(void)
{
    gpio_init_pin(port_address, 1, GPIO_PIN_OUTPUT);

    TEST_ASSERT_EQUAL_UINT8(0x00, port_registers[0]);
    TEST_ASSERT_EQUAL_UINT8(0x02, port_registers[1]);
    TEST_ASSERT_EQUAL_UINT8(0x00, port_registers[2]);
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_Gpio_should_InitializePinAsInput);
    RUN_TEST(test_Gpio_should_InitializePinAsInputPullup);
    RUN_TEST(test_Gpio_should_InitializePinAsOutput);

    return UNITY_END();
}