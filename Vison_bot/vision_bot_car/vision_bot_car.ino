#include "BluetoothSerial.h"
#include "SetMotor.h"

// Verificar si el Bluetooth clásico está habilitado en la placa
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error El Bluetooth no está habilitado para esta placa.
#endif

#define SPEED 200

BluetoothSerial SerialBT;

void setup() {
  // Inicializar el protocolo I2C
  i2c_init();

  // Inicializar el puerto serie para depuración con el ordenador
  Serial.begin(115200);

  // Inicializar el Bluetooth con el nombre que aparecerá en tu móvil
  SerialBT.begin("Vision-Bot"); 
  Serial.println("Dispositivo Bluetooth iniciado. Ya puedes emparejarlo.");
}

void loop() {
  // Comprobar si hay datos disponibles enviados por Bluetooth
  if (SerialBT.available()) {
    char comando = SerialBT.read(); // Leer el carácter entrante

    // Imprimir el comando recibido en el Monitor Serie para depuración
    Serial.print("Comando recibido: ");
    Serial.println(comando);

    // Procesar la acción según el carácter recibido
    switch (comando) {
      case 'F':
        // Código para AVANZAR
        Serial.println("-> Accion: Avanzar");
        Car_forward(SPEED, SPEED);
        break;

      case 'B':
        // Código para RETROCEDER
        Serial.println("-> Accion: Retroceder");
        Car_backwards(SPEED, SPEED);
        break;

      case 'L':
        // Código para girar a la IZQUIERDA (Left)
        Serial.println("-> Accion: Izquierda");
        Car_left(SPEED/2, SPEED/2);
        break;

      case 'R':
        // Código para girar a la DERECHA (Right)
        Serial.println("-> Accion: Derecha");
        Car_right(SPEED/2, SPEED/2);
        break;

      case 'S':
        // Código para DETENERSE (Stop)
        Serial.println("-> Accion: Detener");
        Car_stop();
        break;

      default:
        // Si se recibe un carácter no esperado
        break;
    }
  }
  
  delay(20); // Pequeña pausa para estabilidad
}