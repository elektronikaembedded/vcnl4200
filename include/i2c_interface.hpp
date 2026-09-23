/**
 * @file        i2c_interface.hpp
 * @brief       I2C interface definitions.
 *
 *              The platform provides the actual I2C transfer implementation.
 */

#pragma once

#include <cstdint>

namespace interface {

enum class I2cError : std::int8_t {
    Success        = 0,   ///< Transfer completed successfully.
    TransferError  = -1,  ///< Transfer failed.
    Timeout        = -2,  ///< Transfer timed out.
    Nack           = -3   ///< Device did not acknowledge.
};

} // namespace port
