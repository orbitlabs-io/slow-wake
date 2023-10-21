## Soft Wake

Replace sound with light for your alarm. Simulates a slow sunrise using RGB LED strip for walking up. Available on [Amazon](https://www.amazon.ca/dp/B092ZP6VZ4?psc=1&ref=ppx_yo2ov_dt_b_product_details)

### This project uses:

- Arduino Uni Rev 2 WIFI
- The RGB LED linked above

### A background on the RGB LED:

It used BLE for interaction. This BLE uses Nordic UART Service (NUS) for writing - RX Characteristic to be precise (Read more about it here - [NUS](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/libraries/bluetooth_services/services/nus.html)). So it connects to the BLE and the attempts to get the RX characteristics to write the data from Serial Monitor (Currently to test if this concept would work). The plan it to connect update the LED via firebase realtime database.

Idealy meant to be control with a phone app, I was able to sniff the packets to get the values. The input looks like `55700 FFFFFF`. While I am unsure what the first 6 digits do, the last 6 digits implies HEX code of the colors.

The darkers the light the dimmer the light will be. For example #000000 implies black. Hence, it is expected for the LED to be completely off.

#### More to follow
