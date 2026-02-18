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
