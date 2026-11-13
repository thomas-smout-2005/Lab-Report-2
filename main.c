/* waveform generation lab report 2*/
/*main.c*/
#include <zephyr/kernel.h> 
#include <zephyr/drivers/gpio.h>



#define LSB_NODE DT_NODELABEL(bus_lsb) 
#define SB2_NODE DT_NODELABEL(bus_sb2) 
#define SB3_NODE DT_NODELABEL(bus_sb3) 
#define MSB_NODE DT_NODELABEL(bus_msb) 


 
static const struct gpio_dt_spec lsb = 
    GPIO_DT_SPEC_GET(LSB_NODE, gpios); 
static const struct gpio_dt_spec sb2 = 
    GPIO_DT_SPEC_GET(SB2_NODE, gpios); 
static const struct gpio_dt_spec sb3 = 
    GPIO_DT_SPEC_GET(SB3_NODE, gpios); 
static const struct gpio_dt_spec msb = 
    GPIO_DT_SPEC_GET(MSB_NODE, gpios); 



static void write_bus(uint8_t value) 
{   gpio_pin_set_dt(&lsb, (value >> 0) & 1); 
    gpio_pin_set_dt(&sb2, (value >> 1) & 1); 
    gpio_pin_set_dt(&sb3, (value >> 2) & 1); 
    gpio_pin_set_dt(&msb, (value >> 3) & 1); 
}



int main(void)
{
    int count;
    uint8_t value[10] = { 0xF, 0xF, 0xF, 0xE, 0xC, 0x8, 0x0, 0x0, 0x0, 0x0 };
    
    gpio_pin_configure_dt(&lsb, GPIO_OUTPUT_ACTIVE);
    gpio_pin_configure_dt(&sb2, GPIO_OUTPUT_ACTIVE);
    gpio_pin_configure_dt(&sb3, GPIO_OUTPUT_ACTIVE);
    gpio_pin_configure_dt(&msb, GPIO_OUTPUT_ACTIVE);
    
    while (1) {
        for (count = 0; count < 10; count++) {
            write_bus(value[count]);
            k_sleep(K_MSEC(20));
        }
    }
    return 0;
}