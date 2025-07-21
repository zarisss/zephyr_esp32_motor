#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>


/* Define motor control pins*/
#define IN1_NODE DT_NODELABEL(in1)  
#define IN2_NODE DT_NODELABEL(in2)
#define IN3_NODE DT_NODELABEL(in3)
#define IN4_NODE DT_NODELABEL(in4)

static const struct gpio_dt_spec motor1 = GPIO_DT_SPEC_GET(IN1_NODE, gpios);
static const struct gpio_dt_spec motor2 = GPIO_DT_SPEC_GET(IN2_NODE, gpios);
static const struct gpio_dt_spec motor3 = GPIO_DT_SPEC_GET(IN3_NODE, gpios);
static const struct gpio_dt_spec motor4 = GPIO_DT_SPEC_GET(IN4_NODE, gpios);


/* Function to rotate motor forward */
void fwd(const struct gpio_dt_spec *in, const struct gpio_dt_spec *in2) {
    gpio_pin_set_dt(in, 1);
    gpio_pin_set_dt(in2, 0);
}

/* Function to rotate motor backward */
void bwd(const struct gpio_dt_spec *in, const struct gpio_dt_spec *in2) {
    gpio_pin_set_dt(in, 0);
    gpio_pin_set_dt(in2, 1);
}

/* Function to stop motor */
void stp(const struct gpio_dt_spec *in, const struct gpio_dt_spec *in2) {
    gpio_pin_set_dt(in, 0);
    gpio_pin_set_dt(in2, 0);
}
void main(void) {
     /* Configuring all motor GPIO pins as outputs */

    int ret = gpio_pin_configure_dt(&motor1, GPIO_OUTPUT_ACTIVE) || gpio_pin_configure_dt(&motor2, GPIO_OUTPUT_ACTIVE) 
    || gpio_pin_configure_dt(&motor3, GPIO_OUTPUT_ACTIVE) || gpio_pin_configure_dt(&motor4, GPIO_OUTPUT_ACTIVE) ;
    if (ret < 0) {
        printk("Failed to configure motor1 GPIO\n");
        return;
    }

    while (1) {
        /* Moving both motors forward */
        fwd(&motor1, &motor2);
        fwd(&motor4, &motor3);
        k_sleep(K_MSEC(1000));

        /* Stopping both motors */
        stp(&motor1, &motor2);
        stp(&motor4, &motor3);
        k_sleep(K_MSEC(1000));

        /* Moving both motors backward */
        bwd(&motor1, &motor2);
        bwd(&motor4, &motor3);
        k_sleep(K_MSEC(1000));

        /* Stopping again */
        stp(&motor1, &motor2);
        stp(&motor4, &motor3);
        k_sleep(K_MSEC(1000));
    }
}

