# VCNL4200

A lightweight C++ driver for the **Vishay VCNL4200** proximity and ambient light sensor.

This driver is written with embedded systems in mind. The sensor code is kept separate from the platform-specific I2C code, so it can be reused across different microcontrollers and projects.

## Features

* Proximity sensor support
* Ambient light sensor support
* I2C communication
* Register-level configuration
* No dynamic memory allocation
* Platform-independent sensor code
* Suitable for bare-metal and RTOS-based projects

## Project Structure

```text
vcnl4200/
├── vcnl4200.hpp
├── vcnl4200_impl.hpp
├── vcnl4200_registers.hpp
│
└── Port/
    └── i2c_interface.hpp.template
```

### Driver

`vcnl4200.hpp` contains the public API used by the application.

`vcnl4200_impl.hpp` contains the driver implementation.

`vcnl4200_registers.hpp` contains the VCNL4200 register addresses, bit definitions, and related constants.

### Port

The `Port/` directory contains templates for connecting the driver to a platform-specific I2C implementation.

For example, an STM32 project can provide an I2C implementation using STM32 HAL without making the VCNL4200 driver depend on STM32 HAL.

## How It Works

The driver is split into two parts:

```text
Application
    │
    ▼
VCNL4200 Driver
    │
    ▼
I2C Interface
    │
    ▼
Platform I2C
    │
    ▼
MCU / HAL
```

This keeps the sensor driver portable while allowing each project to use its own I2C implementation.

## Example

A typical application can use the driver like this:

```cpp
#include "vcnl4200.hpp"

vcnl4200::Driver sensor(i2c);

if (sensor.init() == vcnl4200::Error::Success)
{
    // Read proximity / ambient light data
}
```

The API is still evolving as the driver is developed.

## Platform Support

The VCNL4200 driver does not depend on a particular MCU, HAL, or RTOS.

A platform-specific I2C implementation can be added for:

* STM32
* Zephyr
* Other microcontrollers and embedded platforms

## Design Goals

The main goal is to have a **small, reusable VCNL4200 driver** that can be dropped into different embedded projects without having to rewrite the sensor code.

The project also follows a few simple principles:

* Keep hardware-specific code outside the driver.
* Avoid dynamic memory allocation.
* Keep the API simple.
* Keep register definitions easy to understand.
* Make the driver easy to test and reuse.

## Status

Work in progress. The driver is being developed and tested on embedded hardware.

## License

See [LICENSE](LICENSE) for license information.
