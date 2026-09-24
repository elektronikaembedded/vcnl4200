/**
 * @file        i2c_interface.hpp
 * @brief       I2C interface definitions.
 *
 *              Defines the common I2C error codes used by platform
 *              specific I2C implementations.
 *
 * Template usage:
 *              Platform implementations are provided as templates in
 *              the Port/ folder. Copy and adapt the required template
 *              files for the target platform.
 *
 *              The I2C implementation should provide the operations
 *              required by the device drivers, such as read, write,
 *              register access, and device-ready checks.
 */

#pragma once

#include <cstdint>

namespace interface
{

/**
 * @brief I2C transfer error codes.
 */
enum class I2cError : std::int8_t
{
    Success       = 0,   ///< Transfer completed successfully.
    TransferError = -1,  ///< Transfer failed.
    Timeout       = -2,  ///< Transfer timed out.
    Nack          = -3   ///< Device did not acknowledge.
};

} // namespace interface

