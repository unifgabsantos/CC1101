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
