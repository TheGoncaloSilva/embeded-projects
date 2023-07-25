# Arduino Uno

The Arduino Uno is a versatile and popular micro-controller board, widely used for various electronics projects and prototyping. It offers a cost-effective and reliable solution for hobbyists and professionals. The board is equipped with a range of input/output pins, making it suitable for a wide array of applications.

![uno pins](./arduino_uno_pins.png)

The Arduino Uno supports various communication interfaces and protocols, including Universal Serial Bus (USB) for easy programming and power supply. One of the main selling points is that you can easily extend its functionalities by using external modules and shields.

# Development Environment
The development environment for Arduino Uno involves using the Arduino IDE, a cross-platform application that supports programming the board with ease. In this documentation, we'll focus on using the Linux environment, specifically Ubuntu 22.04, for running and executing the Arduino Uno projects.

# Problems
* Problem connecting to port, specially in Arduino IDE [^1]. Give permission to access the port, by your user, with the following commands:
    ```
    sudo adduser <username> dialout
    sudo chmod a+rw /dev/ttyUSB0
    ```

[^1]: https://stackoverflow.com/questions/73923341/unable-to-flash-esp32-the-port-doesnt-exist
