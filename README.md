# IoT Project: STM32F4 to ESP32 to ThingSpeak

This project demonstrates an IoT system where ADC values are read using DMA and Timer on an STM32F4 microcontroller, transmitted via UART to an ESP32, and then sent to the ThingSpeak IoT platform for visualization and analysis.

## Features

- **STM32F4**:
  - Reads analog values using ADC with DMA for efficient data transfer.
  - Uses a Timer to periodically send ADC values via UART.
  - Controls GPIO pins based on ADC thresholds.

- **ESP32**:
  - Receives ADC values from STM32F4 via UART.
  - Connects to WiFi and sends the received data to ThingSpeak.
  - Provides feedback through an onboard LED for successful or failed transmissions.

- **ThingSpeak**:
  - Visualizes the ADC data in real-time.

## System Overview

1. **STM32F4**:
   - Reads ADC values from a sensor connected to pin `PA1`.
   - Processes the ADC values to control LEDs connected to pins `PD12`, `PD13`, `PD14`, and `PD15`.
   - Sends the ADC values to the ESP32 via UART using DMA.

2. **ESP32**:
   - Receives ADC values from STM32F4.
   - Connects to a WiFi network and sends the data to ThingSpeak using HTTP requests.

3. **ThingSpeak**:
   - Displays the ADC values in a user-friendly graph.

## Hardware Requirements

- STM32F4 Discovery Board (STM32F407VGTx)
- ESP32 Development Board
- Analog sensor (e.g., potentiometer)
- LEDs and resistors
- Jumper wires and breadboard

## Software Requirements

- STM32CubeIDE for STM32 firmware development
- Arduino IDE for ESP32 firmware development
- ThingSpeak account for data visualization

## Setup Instructions

### STM32F4 Configuration

1. **ADC Configuration**:
   - ADC1 is configured to read analog input from pin `PA1`.
   - DMA is used for continuous data transfer.

2. **Timer Configuration**:
   - Timer 6 is configured to trigger periodic UART transmissions.

3. **UART Configuration**:
   - USART2 is used for communication with the ESP32.

4. **GPIO Configuration**:
   - Pins `PD12`, `PD13`, `PD14`, and `PD15` are configured as output for LED control.

5. **Code Deployment**:
   - Use STM32CubeIDE to build and flash the firmware to the STM32F4 board.

### ESP32 Configuration

1. **WiFi Setup**:
   - Update the `ssid` and `password` variables in the `esp32_iot.ino` file with your WiFi credentials.

2. **ThingSpeak API Key**:
   - Replace the `apiKey` variable with your ThingSpeak Write API Key.

3. **UART Configuration**:
   - Ensure the RX and TX pins are correctly connected to the STM32F4.

4. **Code Deployment**:
   - Use Arduino IDE to upload the `esp32_iot.ino` sketch to the ESP32.

### ThingSpeak Setup

1. Create a new channel on ThingSpeak.
2. Note the Write API Key and update it in the ESP32 code.
3. Configure the channel to display the data in a graph.

## Wiring Diagram

| STM32F4 Pin | ESP32 Pin | Description          |
|-------------|-----------|----------------------|
| PA2         | RX (GPIO3)| UART TX from STM32   |
| PA3         | TX (GPIO1)| UART RX to STM32     |
| PA1         | -         | Analog input (sensor)|
| PD12-15     | -         | LEDs for indication  |

## How It Works

1. The STM32F4 reads ADC values and processes them to control LEDs.
2. The ADC values are sent to the ESP32 via UART.
3. The ESP32 connects to WiFi and sends the data to ThingSpeak.
4. ThingSpeak visualizes the data in real-time.


## License

This project is licensed under the MIT License. See the LICENSE file for details.

## Acknowledgments

- [STMicroelectronics](https://www.st.com) for STM32CubeIDE and HAL libraries.
- [Espressif Systems](https://www.espressif.com) for ESP32 development tools.
- [ThingSpeak](https://thingspeak.com) for IoT data visualization.

## Contact

For questions or feedback, please contact [Yassineg07](mailto:gharbiyasine040@gmail.com).
