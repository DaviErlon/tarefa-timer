# tarefa-timer
## Descrição:
  Este repositório é dedicado a uma Tarefa da capacitação EmbarcaTech, tarefa esta composta por 2 problemas.
Cada pasta contém uma solução, com os arquivos de compilação CMake e CMakeLists, o arquivo principal na
linguagem C e os arquivos de simulação [Wokwi](https://wokwi.com/) que contém também os periféricos utilizados.
***

### Funções da Tarefa 1:
  - `void gpio_config()`: Contem as inicializações das GPIO e as configurações delas como saída.
  - `add_repeating_timer_ms(3000, semaforo, NULL, &timer)`: Está é a IRQ da função `semaforo(...)` e a aciona a cada 3000ms.
  - `bool semaforo(struct repeating_timer *t)`: Esta é a IRS da função acima. Guarda um led em uma variavél `static`,
  apaga o led anterior, acende o atual e passa essa variável para outro led.
  - `printf("Loop em execução!\n")`: Imprime mensagem no monitor serial a cada 1000ms.
***

### Funções da Tarefa 2: 
  - `void gpio_config()`: Contem as inicializações das GPIO e as configurações como entrada ou saída e a configuração
  de pull_up para a GPIO do botão.
  - `gpio_set_irq_enabled_with_callback(BOT_A, GPIO_IRQ_EDGE_FALL, true, botao)`: IRQ principal. Chama a função `botao(...)`
  quando ocorre uma borda de descida na GPIO do botão, ou seja, quando o botão for precionado.
  - `void botao(uint gpio, uint32_t events)`: Esta é a IRS da função acima. Aciona os 3 leds e 3 IRQ de funções explicadas abaixo,
  desativa sua propria IRQ para não serem geradas mais interrupções até o fim da animação dos leds, e por fim limpa
  os registradores para evitar erros conforme novas chamadas a esta função. 
  - `int64_t alarme1(alarm_id_t id, void *user_data)`: Apaga o led azul.
  - `int64_t alarme2(alarm_id_t id, void *user_data)`: Apaga o led vermelho.
  - `int64_t alarme3(alarm_id_t id, void *user_data)`: Apaga o led verde e reaciona a IRQ principal para novas interrupções.
