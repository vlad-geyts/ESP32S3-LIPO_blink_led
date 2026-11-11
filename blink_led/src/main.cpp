#include <Arduino.h>

// Olimex ESP32-S3-DevKit-LiPo: green user LED on GPIO38
constexpr uint8_t LED_PIN = 38;

// 10 Hz blink -> 100 ms period -> 50 ms ON, 50 ms OFF
constexpr uint32_t HALF_PERIOD_MS = 50;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // With ARDUINO_USB_CDC_ON_BOOT=0
  // "Serial" is UART0, which goes to the USB-UART connector.
  Serial.begin(115200);
  delay(5000);

    Serial.println("\n--- ESP Hardware Info------------------");
    
    // Display ESP Information
    Serial.printf("Chip ID: %s\n", ESP.getChipModel()); // Get the 24-bit chip ID
    Serial.printf("CPU Frequency: %lu MHz\n", ESP.getCpuFreqMHz()); // Get CPU frequency
    Serial.printf("SDK Version: %s\n", ESP.getSdkVersion()); // Get SDK version

    // Get and print flash memory information
    Serial.printf("Flash Chip Size: %lu bytes\n", ESP.getFlashChipSize()); // Get total flash size
   
    // Get and print SRAM memory information
    Serial.printf("Internal free Heap at setup: %ld bytes\n", ESP.getFreeHeap());
    if(psramFound()){
        Serial.printf("Total PSRAM Size: %ld bytes\n", ESP.getPsramSize());
        Serial.printf("PSRAM free:  %lu bytes\n", ESP.getFreePsram());
    } else {
         Serial.print("No PSRAM found");
    }
  
  Serial.println();
  Serial.println("ESP32-S3-DevKit-LiPo: blinking LED on GPIO38 at 10 Hz");
}

void loop() {
  static uint32_t lastToggle = 0;
  static bool ledOn = false;
  static uint32_t count = 0;

  uint32_t now = millis();
  if (now - lastToggle >= HALF_PERIOD_MS) {
    lastToggle = now;
    ledOn = !ledOn;
    digitalWrite(LED_PIN, ledOn ? HIGH : LOW);

    // Print a heartbeat once per second (every 10 full blinks)
    if (ledOn && (++count % 10 == 0)) {
      Serial.printf("Uptime: %lu s\n", (unsigned long)(now / 1000));
    }
  }
}
