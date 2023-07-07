#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <DHT.h>

#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22 
#define RELAY_PIN 3   // Digital pin connected to the relay (IN)

DHT dht(DHTPIN, DHTTYPE);

#define OLED_RESET 4    // Reset pin for the OLED display
Adafruit_SSD1306 display(OLED_RESET);

bool splashScreenShown = false;
unsigned long splashScreenStartTime;

void setup() {
  Serial.begin(9600);
  dht.begin();
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);  // Initially turn off the relay

  // Initialize splash screen
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(2, 6);
  display.println("     Solar Dryer v4.0");
  display.println("      >>KOPERNIK 2023");
  display.display();
  splashScreenStartTime = millis();
  splashScreenShown = true;
}

void loop() {
  if (splashScreenShown) {
    // Check if 5 seconds have passed since showing the splash screen
    if (millis() - splashScreenStartTime >= 1000) {
      splashScreenShown = false;  // Splash screen time is up
      display.clearDisplay();
    } else {
      return;  // Continue showing the splash screen
    }
  }

  delay(5000);
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    //Serial.println(F("Failed to read from DHT sensor!"));
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Failed DHT sensor!");
    display.display();
    digitalWrite(RELAY_PIN, LOW);   // Turn off the relay
    return;
  }

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Humidity    : " + String(h) + "%");
  display.println("Temperature : " + String(t) + "C");
  display.println("Heat Index  : " + String(hic) + "C");
  
  // Check if temperature reaches 30 degrees Celsius
  if (t >= 30) {
    digitalWrite(RELAY_PIN, HIGH);  // Turn on the relay
    display.println("Fan status  : ON");
  } else {
    digitalWrite(RELAY_PIN, LOW);   // Turn off the relay
    display.println("Fan status  : OFF");
  }

  display.display();

  Serial.print("H:");
  Serial.print(h);
  Serial.print(", ");
  Serial.print("T:");
  Serial.print(t);
  Serial.print(", ");
  Serial.print("I:");
  Serial.print(hic);
  Serial.print(", ");
    
}
