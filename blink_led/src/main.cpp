#include <Arduino.h>

// Olimex ESP32-S3-DevKit-LiPo: green user LED on GPIO38
constexpr uint8_t LED_PIN = 38;

// 10 Hz blink -> 100 ms period -> 50 ms ON, 50 ms OFF
constexpr uint32_t HALF_PERIOD_MS = 50;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // With ARDUINO_USB_CDC_ON_BOOT=1, "Serial" is the native USB port.
  // "Serial0" is UART0, which goes to the USB-UART connector.
  Serial0.begin(115200);
  delay(5000);

    Serial0.println("\n--- ESP Hardware Info------------------");
    
    // Display ESP Information
    Serial0.printf("Chip ID: %u\n", ESP.getChipModel()); // Get the 24-bit chip ID
    Serial0.printf("CPU Frequency: %u MHz\n", ESP.getCpuFreqMHz()); // Get CPU frequency
    Serial0.printf("SDK Version: %s\n", ESP.getSdkVersion()); // Get SDK version

    // Get and print flash memory information
    Serial0.printf("Flash Chip Size: %u bytes\n", ESP.getFlashChipSize()); // Get total flash size
   
    // Get and print SRAM memory information
    Serial0.printf("Internal free Heap at setup: %d bytes\n", ESP.getFreeHeap());
    if(psramFound()){
        Serial0.printf("Total PSRAM Size: %d bytes", ESP.getPsramSize());
    } else {
         Serial0.print("No PSRAM found");
    }
  
  Serial0.println();
  Serial0.println("ESP32-S3-DevKit-LiPo: blinking LED on GPIO38 at 10 Hz");

  //Serial0.printf("PSRAM found: %s\n", psramFound() ? "yes" : "no");
  //Serial0.printf("PSRAM size:  %u bytes\n", ESP.getPsramSize());
  //Serial0.printf("PSRAM free:  %u bytes\n", ESP.getFreePsram());

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
      Serial0.printf("Uptime: %lu s\n", (unsigned long)(now / 1000));
    }
  }
}
