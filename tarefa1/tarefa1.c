#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

// Leds usados na simulação
#define LED_R 11
#define LED_Y 12 
#define LED_G 13

// Função de inicialização das GPIO dos leds
void gpio_config(){
    gpio_init(LED_R);
    gpio_init(LED_Y);
    gpio_init(LED_G);

    gpio_set_dir(LED_R, GPIO_OUT);
    gpio_set_dir(LED_Y, GPIO_OUT);
    gpio_set_dir(LED_G, GPIO_OUT);
}

// Função de callback  
bool semaforo(struct repeating_timer *t){

    static uint8_t led_ativo = LED_R;
    (led_ativo == LED_R)? gpio_put(LED_G, false) : gpio_put(led_ativo - 1, false);
    gpio_put(led_ativo, true);
    led_ativo++;
    if(led_ativo > LED_G) led_ativo = LED_R;

    return true;
}

int main(){

    stdio_init_all();
    gpio_config();

    struct repeating_timer timer;
    add_repeating_timer_ms(3000, semaforo, NULL, &timer);

    while(1){
        printf("Loop em execução!\n");
        sleep_ms(1000);
    }
}