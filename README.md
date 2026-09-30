# VCNL4200

A lightweight C++ driver for the **Vishay VCNL4200** proximity and ambient light sensor.

The driver is written for embedded systems and keeps the sensor logic separate from the platform-specific I2C implementation. This makes it easier to reuse the driver across different microcontrollers and projects.

## Features

* Proximity sensing
* Ambient light sensing
* I2C communication
* Register-level configuration
* No dynamic memory allocation
* Platform-independent driver code
* Suitable for bare-metal and RTOS-based projects

## Repository Structure

```text
vcnl4200/
├── include/
│   ├── vcnl4200.hpp
│   ├── vcnl4200_impl.hpp
│   └── vcnl4200_registers.hpp
│
├── template/
│   └── i2c_interface.hpp.template
│
└── README.md
```

### `include`

Contains the main VCNL4200 driver.

* `vcnl4200.hpp` — Public driver API
* `vcnl4200_impl.hpp` — Driver implementation
* `vcnl4200_registers.hpp` — Register addresses, bit definitions, and related constants

The code in this directory is intended to remain independent of a specific MCU, HAL, or RTOS.

### `template`

Contains templates for implementing the platform-specific interfaces required by the driver.

For example, an STM32 project can adapt the I2C interface template to use STM32 HAL without adding STM32-specific code to the VCNL4200 driver.

## Architecture

The driver is organized around a simple separation between the sensor and the hardware interface:

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

The VCNL4200 driver only depends on the I2C interface. The actual I2C implementation is provided by the target platform.

## Usage

A platform-specific I2C implementation is passed to the VCNL4200 driver.

For example:

```cpp
#include "vcnl4200.hpp"

vcnl4200::Driver sensor(i2c);

if (sensor.init() == vcnl4200::Error::Success)
{
    // Use the sensor
}
```

The API is still evolving as the driver is developed and tested.

## Platform Support

The driver is not tied to a particular microcontroller or operating system.

The platform interface can be adapted for:

* STM32 HAL
* Zephyr
* Bare-metal applications
* Other embedded platforms

## Design Goals

The project is intended to be a small and reusable VCNL4200 driver that can be dropped into different embedded projects with minimal changes.

The main design goals are:

* Keep the driver platform independent.
* Keep hardware-specific code outside the driver.
* Avoid dynamic memory allocation.
* Keep the API simple.
* Keep register definitions clear and easy to maintain.
* Make the driver suitable for both bare-metal and RTOS-based applications.

## Status

Work in progress.

The driver is currently being developed and tested on embedded hardware. APIs and supported features may change as development continues.

## License

See [LICENSE](LICENSE) for license information.
