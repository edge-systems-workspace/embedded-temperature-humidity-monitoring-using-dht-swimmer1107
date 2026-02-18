/**
 * @file main.cpp
 * @version 1.0
 * @date 18 Feb 2026
 * @author Pulkit Kulshreshtha
 *
 * @brief Temperature and Humidity Monitoring System using DHT11 and SSD1306 OLED.
 *
 * @details
 * This embedded application reads temperature and humidity data
 * from a DHT11 sensor and displays the readings on a 128x64 SSD1306
 * OLED display using I2C communication.
 *
 * The system performs periodic sensor sampling every 2 seconds
 * (as required by DHT11 timing specifications). If a sensor read
 * fails, an error message is displayed on the OLED.
 *
 * @section hardware Hardware Configuration
 * - Microcontroller: Arduino (ATmega328P or compatible)
 * - Sensor: DHT11 (Digital Temperature & Humidity Sensor)
 * - Display: SSD1306 128x64 OLED (I2C)
 *
 * @section wiring Wiring Details
 * - DHT11 Data Pin  -> Digital Pin 2
 * - OLED SDA        -> Arduino SDA (A4 on Uno)
 * - OLED SCL        -> Arduino SCL (A5 on Uno)
 * - OLED I2C Addr   -> 0x3C
 *
 * @section dependencies Library Dependencies
 * - Arduino.h
 * - Wire.h
 * - Adafruit_GFX.h
 * - Adafruit_SSD1306.h
 * - DHT.h
 */

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

/** @brief OLED display width in pixels */
#define SCREEN_WIDTH 128

/** @brief OLED display height in pixels */
#define SCREEN_HEIGHT 64

/** @brief OLED reset pin (-1 if shared reset line is used) */
#define OLED_RESET -1

/**
 * @brief SSD1306 OLED display object.
 * 
 * Uses I2C communication via the default Wire interface.
 */
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/** @brief Digital pin connected to DHT11 data line */
#define DHTPIN 2

/** @brief DHT sensor type definition */
#define DHTTYPE DHT11

/**
 * @brief DHT sensor object instance.
 */
DHT dht(DHTPIN, DHTTYPE);

/**
 * @brief System initialization routine.
 *
 * @details
 * - Initializes Serial communication at 9600 baud.
 * - Initializes DHT11 sensor.
 * - Initializes OLED display.
 * - Displays startup splash message.
 * - Halts execution if OLED initialization fails.
 */

void setup() {
    Serial.begin(9600);
    dht.begin();

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("OLED not found");
        while (1);   ///< Halt system if OLED is not detected
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("DHT11 Sensor");
    display.display();
    delay(2000);
}


/**
 * @brief Main execution loop.
 *
 * @details
 * - Waits 2 seconds (mandatory for DHT11 stability).
 * - Reads temperature (°C) and humidity (%).
 * - Validates sensor data.
 * - Displays readings on OLED.
 * - Displays error message if reading fails.
 *
 * @note DHT11 requires a minimum 2-second interval between reads.
 */
void loop() {

    delay(2000);   ///< Required delay for DHT11 sampling rate

    float temp = dht.readTemperature();   ///< Temperature in Celsius
    float hum  = dht.readHumidity();      ///< Relative humidity percentage

    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);

    if (isnan(temp) || isnan(hum)) {
        display.println("Sensor Error!");
        display.display();
        return;
    }

    display.println("DHT11 Reading");
    display.println("----------------");

    display.print("Temp: ");
    display.print(temp);
    display.println(" C");

    display.print("Humidity: ");
    display.print(hum);
    display.println(" %");

    display.display();   ///< Updates OLED buffer to screen
}
