# BresserWeatherSensorReceiver
[![CI](https://github.com/matthias-bs/BresserWeatherSensorReceiver/actions/workflows/CI.yml/badge.svg)](https://github.com/matthias-bs/BresserWeatherSensorReceiver/actions/workflows/CI.yml)
[![Build Status](https://app.travis-ci.com/matthias-bs/BresserWeatherSensorReceiver.svg?branch=main)](https://app.travis-ci.com/matthias-bs/BresserWeatherSensorReceiver)
[![GitHub release](https://img.shields.io/github/release/matthias-bs/BresserWeatherSensorReceiver?maxAge=3600)](https://github.com/matthias-bs/BresserWeatherSensorReceiver/releases)
[![License: MIT](https://img.shields.io/badge/license-MIT-green)](https://github.com/matthias-bs/BresserWeatherSensorReceiver/blob/main/LICENSE)

Bresser 5-in-1/6-in-1 868 MHz Weather Sensor Radio Receiver for Arduino based on CC1101 or SX1276/RFM95W

The Bresser 5-in-1 Weather Stations seem to use two different protocols. First, the 6-in-1 decoder is tried. If this fails, the 5-in-1 decoder is tried.

| Model         | Decoder Function                |
| ------------- | ------------------------------- |
| 7002510..12   | decodeBresser**5In1**Payload()  |
| 7902510..12   | decodeBresser**5In1**Payload()  |
| 7002585       | decodeBresser**6In1**Payload()  |

Configure the desired radio module by (un-)commenting `USE_CC1101` or `USE_SX1276` in `WeatherSensor.h`.

## SW Examples
### [BresserWeatherSensorMQTT](https://github.com/matthias-bs/BresserWeatherSensorReceiver/examples/BresserWeatherSensorMQTT)

MQTT publications:

`<base_topic>/data/<ID|name>`    sensor data as JSON string - see `publishWeatherdata()`
     
`<base_topic>/radio`             CC1101 radio transceiver info as JSON string - see `publishRadio()`
     
`<base_topic>/status`            "online"|"offline"|"dead"$

$ via LWT

`<base_topic>` is set by `#define HOSTNAME ...`

`<base_topic>/data` JSON Example:
```
{"sensor_id":12345678,"ch":0,"battery_ok":true,"humidity":44,"wind_gust":1.2,"wind_avg":1.2,"wind_dir":150,"rain":146}
```
**Dashboard with [IoT MQTT Panel](https://snrlab.in/iot/iot-mqtt-panel-user-guide) (Example)**

![IoTMQTTPanel_Bresser_5-in-1](https://user-images.githubusercontent.com/83612361/158457786-516467f9-2eec-4726-a9bd-36e9dc9eec5c.png)

# HW Examples

## ESP8266 D1 Mini with CC1101

![Bresser5in1_CC1101_D1-Mini](https://user-images.githubusercontent.com/83612361/158458191-b5cabad3-3515-45d0-98e3-94b0fa13b8ef.jpg)

### CC1101

[Texas Instruments CC1101 Product Page](https://www.ti.com/product/CC1101)

**Note: CC1101 Module Connector Pitch is 2.0mm!!!**

Unlike most modules/breakout boards, most (if not all) CC1101 modules sold on common e-commerce platforms have a pitch (distance between pins) of 2.0mm. To connect it to breadboards or jumper wires with 2.54mm/100mil pitch (standard), the following options exist:

* solder wires directly to the module
* use a 2.0mm pin header and make/buy jumper wires with 2.54mm at one end and 2.0mm at the other (e.g. [Adafruit Female-Female 2.54 to 2.0mm Jumper Wires](https://www.adafruit.com/product/1919))
* use a [2.0mm to 2.54 adapter PCB](https://www.amazon.de/Lazmin-1-27MM-2-54MM-Adapter-Platten-Brett-drahtlose-default/dp/B07V873N52)

**Note 2: Make sure to use the 868MHz version!**

## Adafruit RFM95W LoRa Radio Transceiver Breakout

**Note: Make sure to use the 868MHz version!**
* [ADA3072](https://www.adafruit.com/product/3072) - 868/915 MHz version
* [ADA3073](https://www.adafruit.com/product/3073) - 433 MHz version
* RF connector
* Antenna

**Note:**
The RFM95W also supports FSK modulation and thus can be used to receive the weather sensor data.

## Antennas and RF Connectors

The required antenna depends on the signal path between weather sensor and CC1101 or RFM95W receiver. 

Some options are:
* wire antenna
* spring antenna (helical wire coil)
* rubber antenna

See [Adafruit Tutorial - Antenna Options](https://learn.adafruit.com/adafruit-feather-32u4-radio-with-lora-radio-module/antenna-options) for wire antenna lengths and uFL connector soldering.

The [Data Alliance](https://www.data-alliance.net/mhf-series-mhf1-mhf2-mhf3-mhf4/) website helped to sort out my RF connector confusion:

> Applications of MHF Connectors & Cables
>
> The MHF series of RF micro-connectors (mating heights listed below are the maximum):
> * MHF1 (also known as MHF) has a Mating Height of 2.5mm
> * MHF2 has a Mating Height of 2.1mm
> * MHF3 has a Mating Height of 1.6mm
> * MHF4 has a Mating Height of 1.2mm
>
> MHF3 connector is compatible with a W.FL connector while MHF2 connector is equivalent of U.FL connector. The MHF4 cable connector is the smallest while MHF1 connector is the largest which is comparable to a U.FL connector.

Personally I prefer the SMA connector over the uFL connector -  but be aware of the (usual) male/female connector types and the normal/reverse polarity types. See [SMA vs RP-SMA what is the difference?](https://forum.digikey.com/t/sma-vs-rp-sma-what-is-the-difference/550) by Digikey.

## Source Documentation

https://matthias-bs.github.io/BresserWeatherSensorReceiver/