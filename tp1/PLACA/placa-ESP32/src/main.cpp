#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  delay(3000); 

  // Las frecuencias que vamos a probar
  int frecuencias[] = {240, 160, 80, 40, 20, 10};
  int cantidadDePruebas = 6;
  
  // Arreglos (memoria) para guardar los tiempos de cada prueba
  unsigned long tiemposInt[6];
  unsigned long tiemposFloat[6];

  Serial.println("\n==================================================");
  Serial.println("🚀 INICIANDO BATERIA DE PRUEBAS EN MODO SILENCIOSO");
  Serial.println("==================================================");
  Serial.println("El ESP32 esta calculando. Esto tomara aprox 10-15 minutos...");
  Serial.println("No desconectes la placa. Al final se imprimira la tabla.");

  // Hacemos el bucle pero SIN usar Serial.print adentro
  for (int i = 0; i < cantidadDePruebas; i++) {
    setCpuFrequencyMhz(frecuencias[i]); // Cambiamos la velocidad
    
    // --- 1. Prueba de Enteros ---
    unsigned long inicioInt = millis();
    volatile int sumaInt = 0; 
    for(long j = 0; j < 150000000; j++) { 
      sumaInt += 1; 
    }
    tiemposInt[i] = millis() - inicioInt; // Guardamos el tiempo en la memoria

    // --- 2. Prueba de Flotantes ---
    unsigned long inicioFloat = millis();
    volatile float sumaFloat = 0.0;
    for(long j = 0; j < 150000000; j++) { 
      sumaFloat += 1.5; 
    }
    tiemposFloat[i] = millis() - inicioFloat; // Guardamos el tiempo en la memoria
  }

  // --- RESTAURAMOS LA VELOCIDAD PARA PODER HABLAR CON LA PC ---
  setCpuFrequencyMhz(240); 
  delay(100); // Le damos un respiro para que estabilice el USB
  
  // Imprimimos la tabla con todos los resultados guardados
  Serial.println("\n\n✅ ¡PRUEBAS FINALIZADAS! Aqui tienes tus datos:");
  Serial.println("==================================================");
  Serial.println("FRECUENCIA | TIEMPO INT (ms) | TIEMPO FLOAT (ms)");
  Serial.println("--------------------------------------------------");
  
  for (int i = 0; i < cantidadDePruebas; i++) {
    Serial.printf("%3d MHz    | %15lu | %17lu\n", frecuencias[i], tiemposInt[i], tiemposFloat[i]);
  }
  Serial.println("==================================================");
}

void loop() {
  // Vacio
}