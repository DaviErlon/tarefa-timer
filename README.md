# tarefa-timer
## Descrição:
  Este repositório é dedicado a uma Tarefa da capacitação EmbarcaTech, tarefa esta composta por 2 problemas.
Cada pasta contém uma solução, com os arquivos de compilação CMake e CMakeLists, o arquivo principal na
linguagem C e os arquivos de simulação [Wokwi](https://wokwi.com/) que contém também os periféricos utilizados.
***
### Funções da Tarefa 1:
  - `void gpio_config()`: Contem as inicializações das GPIO e as configurações delas como saída.
  - `bool semaforo(struct repeating_timer *t)`: Esta é uma IRS. Guarda um led em uma variavél `static`,
  apaga o led anterior, acende o atual e passa essa variável para outro led.
  - `add_repeating_timer_ms(3000, semaforo, NULL, &timer)`: Está é a IRQ da função acima e a aciona a cada 3000ms.
  - `printf("Loop em execução!\n")`: Imprime mensagem no monitor serial a cada 1000ms.
