# The ESP32

The ESP32 is cheap and reliable micro-controller used mostly for IOT applications. It support wifi and Bluetooth, including Bluetooth Low energy. The following image retracts the pin layout of the board.

![esp32 pins](./ESP32_devkit_1_pin_layout.png)

The Board used in this guides was the ESP-WROOM-32

# Development Environment

Most of the guides and commands present in this documentation were created and intended to run on the Linux environment, mainly Ubuntu 22.04.

# Folder Structure

Since the ESP32 board supports programming both in native C/C++ and using Arduino IDE tools, the two folders in this project approach experimentations conducted using this two approaches:
* `arduino_ide`: Projects developed using the Arduino IDE, which provided more flexibility and ease of use
* `c_cpp`: Projects developed in native C/C++ and compiled with the board in mind. This approach provides more control and access to low-level functionalities of the ESP32 board