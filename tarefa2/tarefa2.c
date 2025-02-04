#include "pico/stdlib.h"
#include "pico/time.h"

#define LED_R 12
#define LED_G 13
#define LED_B 11
#define BOT_A 5

// função de inicialização dos GPIO
void gpio_config(){
    gpio_init(LED_B);
    gpio_init(LED_G);
    gpio_init(LED_R);
    gpio_init(BOT_A);
    gpio_set_dir(LED_B,GPIO_OUT);
    gpio_set_dir(LED_G,GPIO_OUT);
    gpio_set_dir(LED_R,GPIO_OUT);
    gpio_set_dir(BOT_A, GPIO_IN);
    gpio_pull_up(BOT_A);
}

// callback que desliga o primeiro led
int64_t alarme1(alarm_id_t id, void *user_data){
    gpio_put(LED_B, false);
    return 0;
}

// callback que desliga o segundo led
int64_t alarme2(alarm_id_t id, void *user_data){
    gpio_put(LED_R, false);
    return 0;
}

// callback que desliga o terceiro led
int64_t alarme3(alarm_id_t id, void *user_data){
    gpio_put(LED_G, false);
    gpio_set_irq_enabled(BOT_A, GPIO_IRQ_EDGE_FALL, true); // ativar IRQ novamente
    return 0;
}

/*
Não foi necessário fazer um sistema de debounce por conta que
a função callback do botão se desativa no final e só volta a 
funcionar quando a ultima função callback de atualizar os leds
(alarme 3) for chamada
*/

void botao(uint gpio, uint32_t events){

    //acender todos os leds
    gpio_put(LED_B, true);
    gpio_put(LED_G, true);
    gpio_put(LED_R, true);

    add_alarm_in_ms(3000, alarme1, NULL, false);
    add_alarm_in_ms(6000, alarme2, NULL, false);
    add_alarm_in_ms(9000, alarme3, NULL, false);

    gpio_set_irq_enabled(BOT_A, GPIO_IRQ_EDGE_FALL, false); // desativar IRQ

    gpio_acknowledge_irq(gpio, events); // limpeza dos registradores 
}

int main(){

    gpio_config();
    gpio_set_irq_enabled_with_callback(BOT_A, GPIO_IRQ_EDGE_FALL, true, botao);

    while (true){
        tight_loop_contents();
    }
}
