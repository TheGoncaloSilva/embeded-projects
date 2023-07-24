# The ESP32

The ESP32 is cheap and reliable micro-controller used mostly for IOT applications. It support wifi and Bluetooth, including Bluetooth Low energy. The following image retracts the pin layout of the board.

![esp32 pins](./ESP32_devkit_1_pin_layout.png)

## Initial environment and chip configuration

For a initial installation and configuration guide, head to [esp_32](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/linux-macos-setup.html) website

On every new terminal window, execute the command `get_idf` for the development functionalities to be available

If you wanna tailor the project to a specific device or make some default configurations on the ESP32, use the following command to set device

```
idf.py set-target esp32
```

And the next one to make changes on the configuration

```
idf.py menuconfig
```

## Development

To build and compile the program for the esp, use

```
idf.py build
```

### Project Creation

A project can be created by executing the command

```
idf.py create-project <PROJECT_NAME>
```

**NOTE**: the project should be created within 'esp' installation folder, otherwise, adjustments should be made

### Flash and monitor the program on the board

Execute the following command to flash the program into the esp board

```
idf.py -p <PORT> flash
```

**TIP**: for the board to be in flashing mode, press and hold the **BOOT** while the program is flashing. Remeber to check the port in linux, by executing

```
ls /dev/tty*
```

In the command line an checking with entry bellongs to the board (Generally ttyUSB `x` or ttyACM `x`)

To monitor the program and check it's output, execute the command

```
idf.py -p <PORT> monitor
```

To exit this view, use ``ctrl + ]``

### Erase program stored in Flash

#### Method 1

Erase flash: ``idf.py -p <PORT> erase-flash``
Erase OTAdata: ``idf.py -p PORT erase-otadata``

#### Method 2

Install the esptool

```
pip install esptool
```

Press and Hold the **BOOT** button and execute

```
esptool.py --chip esp32 --port /dev/ttyUSB0 erase_flash
```

# Problems
Problem connecting to port, specially in Arduino IDE [^1]. Give permission to access the port, by your user, with the following commands:

```
sudo adduser <username> dialout
sudo chmod a+rw /dev/ttyUSB0
```

[^1]: https://stackoverflow.com/questions/73923341/unable-to-flash-esp32-the-port-doesnt-exist
