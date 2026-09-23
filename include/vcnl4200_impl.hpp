/**
 * @file        vcnl4200_impl.hpp
 * @brief       Internal implementation of the VCNL4200 driver.
 *
 *              Contains the template method implementations.
 */

#pragma once

#include <cstdint>

#include "i2c_interface.hpp"
#include "vcnl4200_registers.hpp"

namespace vcnl4200
{

template <
    typename I2CBus,
    typename OS,
    std::uint8_t Address,
    typename Config>
Vcnl4200Error Driver<I2CBus, OS, Address, Config>::init()
{
    if (m_i2cBus.isDeviceReady(
            Address,
            Config::kReadyRetryCount,
            Config::kReadyTimeoutMs) != interface::I2cError::Success)
    {
        return Vcnl4200Error::TransferError;
    }

    return Vcnl4200Error::Success;
}

template <
    typename I2CBus,
    typename OS,
    std::uint8_t Address,
    typename Config>
Vcnl4200Error Driver<I2CBus, OS, Address, Config>::readDeviceId(
    std::uint16_t& id)
{
    std::uint8_t rx[2] = {};

    if (m_i2cBus.readRegister(
            Address,
            reg::ID,
            rx,
            sizeof(rx),
            Config::kReadTimeoutMs) != interface::I2cError::Success)
    {
        return Vcnl4200Error::TransferError;
    }

    id = static_cast<std::uint16_t>(rx[0]) |
         (static_cast<std::uint16_t>(rx[1]) << 8U);

    return Vcnl4200Error::Success;
}

} // namespace vcnl4200
