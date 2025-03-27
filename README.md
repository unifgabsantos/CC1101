
# Receptor RF com ESP32 e CC1101 E07-M1101D

Este projeto utiliza o ESP32 e o módulo CC1101 E07-M1101D para receber sinais RF via SPI. Através da biblioteca **RCSwitch**, o código configura o módulo para receber sinais e imprimir os valores recebidos no monitor serial.

## Componentes Necessários

- **ESP32**: Microcontrolador para processamento e controle.
- **CC1101 E07-M1101D**: Módulo RF para comunicação via rádio.
- **Cabos Jumper**: Para conectar o ESP32 ao CC1101.

## Conexões

Faça as conexões conforme abaixo:

| Pino CC1101  | Pino ESP32   |
|--------------|--------------|
| SCK          | GPIO 18      |
| MISO         | GPIO 19      |
| MOSI         | GPIO 23      |
| CS           | GPIO 5       |
| GDO0         | GPIO 2       |
| GDO2         | GPIO 4       |

## Código

O código realiza a leitura de sinais recebidos pelo módulo CC1101 e imprime os valores no monitor serial. Quando um sinal válido é recebido, o valor é exibido. Se um sinal inválido for detectado, uma mensagem de erro é exibida.

```cpp
#include <RCSwitch.h>

#define CC1101_SCK   18  // Clock SPI (SCK)
#define CC1101_MISO  19  // Dados SPI (Saída do CC1101)
#define CC1101_MOSI  23  // Dados SPI (Entrada no CC1101)
#define CC1101_CS    5   // Chip Select (CS)
#define CC1101_GDO0  2   // Interrupção (Recepção)
#define CC1101_GDO2  4   // Interrupção Secundária (Opcional)

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Inicializando o receptor RF...");
  
  mySwitch.enableReceive(digitalPinToInterrupt(CC1101_GDO0));  // Use a função digitalPinToInterrupt para especificar GPIO2
}

void loop() {
  if (mySwitch.available()) {
    int value = mySwitch.getReceivedValue();
    if (value == 0) {
      Serial.println("Valor inválido recebido.");
    } else {
      Serial.print("Sinal recebido: ");
      Serial.println(value);
    }
    mySwitch.resetAvailable();
  }
}
```

## Como Usar

1. **Conecte os pinos do CC1101 ao ESP32** conforme a tabela acima.
2. **Instale a biblioteca RCSwitch** em seu ambiente de desenvolvimento Arduino (ou outro IDE de sua escolha).
3. **Carregue o código** no ESP32.
4. **Abra o monitor serial** para ver os valores dos sinais recebidos.
