///////////////////////////////////////////////////////////////////////////////////////////////////
// BresserWeatherSensorBasic.ino
//
// Example for BresserWeatherSensorReceiver - 
// Using getMessage() for non-blocking reception of a single data message.
//
// The data may be incomplete, because certain sensors need two messages to
// transmit a complete data set.
// Which sensor data is received in case of multiple sensors are in range
// depends on the timing of transmitter and receiver.  
//
// https://github.com/matthias-bs/BresserWeatherSensorReceiver
//
//
// created: 05/2022
//
//
// MIT License
//
// Copyright (c) 2022 Matthias Prinke
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// History:
//
// 20220523 Created from https://github.com/matthias-bs/Bresser5in1-CC1101
// 20220524 Moved code to class WeatherSensor
// 20220810 Changed to modified WeatherSensor class; fixed Soil Moisture Sensor Handling
// 20220815 Changed to modified WeatherSensor class; added support of multiple sensors
// 20221227 Replaced DEBUG_PRINT/DEBUG_PRINTLN by Arduino logging functions
//
// ToDo: 
// - 
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <Arduino.h>
#include "WeatherSensorCfg.h"
#include "WeatherSensor.h"


WeatherSensor weatherSensor;


void setup() {    
    Serial.begin(115200);
    Serial.setDebugOutput(true);

    Serial.printf("Starting execution...\n");

    weatherSensor.begin();
}


void loop() 
{   
    // This example uses only a single slot in the sensor data array
    int const i=0;

//    Serial.printf("Hola (2)");

    // Clear all sensor data
    weatherSensor.clearSlots();

//    Serial.printf("Hola (3)");
    
    // Tries to receive radio message (non-blocking) and to decode it.
    // Timeout occurs after a small multiple of expected time-on-air.
    int decode_status = weatherSensor.getMessage();

//    Serial.printf("Hola (4)");

/*    if (decode_status != DECODE_INVALID) {
      Serial.printf("Decode status: %d\n", decode_status);
    }
*/
    if (decode_status == DECODE_OK || decode_status == DECODE_PAR_ERR) {
    
      Serial.printf("Id: [%8X] Typ: [%X] Battery: [%s] ",
          weatherSensor.sensor[i].sensor_id,
          weatherSensor.sensor[i].s_type,
          weatherSensor.sensor[i].battery_ok ? "OK " : "Low");
      #ifdef BRESSER_6_IN_1
          Serial.printf("Ch: [%d] ", weatherSensor.sensor[i].chan);
      #endif
      if (weatherSensor.sensor[i].temp_ok) {
          Serial.printf("Temp: [%5.1fC] ",
              weatherSensor.sensor[i].temp_c);
      } else {
          Serial.printf("Temp: [---.-C] ");
      }
      if (weatherSensor.sensor[i].humidity_ok) {
          Serial.printf("Hum: [%3d%%] ",
              weatherSensor.sensor[i].humidity);
      }
      else {
          Serial.printf("Hum: [---%%] ");
      }
      if (weatherSensor.sensor[i].wind_ok) {
          Serial.printf("Wind max: [%4.1fm/s] Wind avg: [%4.1fm/s] Wind dir: [%5.1fdeg] ",
                  weatherSensor.sensor[i].wind_gust_meter_sec,
                  weatherSensor.sensor[i].wind_avg_meter_sec,
                  weatherSensor.sensor[i].wind_direction_deg);
      } else {
          Serial.printf("Wind max: [--.-m/s] Wind avg: [--.-m/s] Wind dir: [---.-deg] ");
      }
      if (weatherSensor.sensor[i].rain_ok) {
          Serial.printf("Rain: [%7.1fmm] ",  
              weatherSensor.sensor[i].rain_mm);
      } else {
          Serial.printf("Rain: [-----.-mm] "); 
      }
      if (weatherSensor.sensor[i].moisture_ok) {
          Serial.printf("Moisture: [%2d%%] ",
              weatherSensor.sensor[i].moisture);
      }
      else {
          Serial.printf("Moisture: [--%%] ");
      }
      if (weatherSensor.sensor[i].uv_ok) {
          Serial.printf("UV index: [%1.1f] ",
              weatherSensor.sensor[i].uv);
      }
      else {
          Serial.printf("UV index: [-.-%%] ");
      }
      if (weatherSensor.sensor[i].light_ok) {
          Serial.printf("Light (Klux): [%2.1fKlux] ",
              weatherSensor.sensor[i].light_klx);
      }
      else {
          Serial.printf("Light (lux): [--.-Klux] ");
      }
      Serial.printf("RSSI: [%5.1fdBm]\n", weatherSensor.sensor[i].rssi);
    } // if (decode_status == DECODE_OK)
    delay(100);
} // loop()
