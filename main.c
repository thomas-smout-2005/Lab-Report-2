/* waveform generation lab report 2*/
/*main.c*/
#include <zephyr/kernel.h> 
#include <zephyr/drivers/gpio.h>



#define LSB_NODE DT_NODELABEL(bus_lsb) /* connects LSB_NODE variable to data from bus_lsb found in app.overlay */
#define SB2_NODE DT_NODELABEL(bus_sb2) /* connects SB2_NODE variable to data from bus_sb2 found in app.overlay */
#define SB3_NODE DT_NODELABEL(bus_sb3) /* connects SB3_NODE variable to data from bus_sb3 found in app.overlay */
#define MSB_NODE DT_NODELABEL(bus_msb) /* connects MSB_NODE variable to data from bus_msb found in app.overlay */


 
static const struct gpio_dt_spec lsb = 
    GPIO_DT_SPEC_GET(LSB_NODE, gpios); /* creates an array to store data about our LSB */
static const struct gpio_dt_spec sb2 =
    GPIO_DT_SPEC_GET(SB2_NODE, gpios); /* creates an array to store data about our SB2 */ 
static const struct gpio_dt_spec sb3 = 
    GPIO_DT_SPEC_GET(SB3_NODE, gpios); /* creates an array to store data about our SB3 */
static const struct gpio_dt_spec msb = 
    GPIO_DT_SPEC_GET(MSB_NODE, gpios); /* creates an array to store data about our MSB */



static void write_bus(uint8_t value)
    /* "value >>" evaluates the value of the number in postion 0(rightmost), 1(left), 2(left), or 3(leftmost) and if true = return 1, if false = return 0 */
{   gpio_pin_set_dt(&lsb, (value >> 0) & 1);
    gpio_pin_set_dt(&sb2, (value >> 1) & 1);
    gpio_pin_set_dt(&sb3, (value >> 2) & 1); 
    gpio_pin_set_dt(&msb, (value >> 3) & 1); 
}



int main(void)
{
    int count; /* counter keeps track of what value in our values list we're focused on */
    /* creates a fixed width unsigned integer type variable called value that will hold the data about our waveforms */
    uint8_t value[10] = { 0xF, 0xF, 0xF, 0xE, 0xC, 0x8, 0x0, 0x0, 0x0, 0x0 };
    
    /* all our leds start active */
    gpio_pin_configure_dt(&lsb, GPIO_OUTPUT_ACTIVE);
    gpio_pin_configure_dt(&sb2, GPIO_OUTPUT_ACTIVE);
    gpio_pin_configure_dt(&sb3, GPIO_OUTPUT_ACTIVE);
    gpio_pin_configure_dt(&msb, GPIO_OUTPUT_ACTIVE);
    
    while (1) { /* creates a loop to cycle endlessly */
        for (count = 0; count < 10; count++) { /* creates a loop to cycle through our 10 values */
            write_bus(value[count]); /* calls our write_bus function passing our values and what count we're up to */
            k_sleep(K_MSEC(20)); /* waits 20ms */
        }
    }
    return 0;
}