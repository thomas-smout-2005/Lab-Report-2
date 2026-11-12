



static void write_bus(uint8_t value)
{
    gpio_pin_set_dt(&lsb, (value >> 0) & 1)
}


int main(void)
{
    int count;
    uint8_t value[10] = { 0xF, 0xF, 0xF, 0xE, 0xC, 0x8, 0x0, 0x0, 0x0, 0x0 };

    gpio_pin_configure_dt(&lsb, GPIO_OUTPUT_ACTIVE);
    gpio_pin_configure_dt(&sb2, GPIO_OUTPUT_ACTIVE);
    gpio_pin_configure_dt(&sb3, GPIO_OUTPUT_ACTIVE);
    gpio_pin_configure_dt(&msb, GPIO_OUTPUT_ACTIVE);

    while (1)
    {
        for (count = 0; count < 10; count++) {
            write_bus(values[count]);
            k_sleep(K_MSEC(20));
        }
    }
    return 0;
}
