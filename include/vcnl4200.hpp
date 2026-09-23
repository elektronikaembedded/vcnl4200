/**
 * @file        vcnl4200.hpp
 * @brief       VCNL4200 proximity and ambient light sensor driver.
 */

#pragma once

#include <cstdint>

namespace vcnl4200
{

inline constexpr std::uint8_t kDeviceAddress = 0x51;

struct DefaultConfig
{
    static constexpr std::uint8_t kReadyRetryCount = 3;
    static constexpr std::uint32_t kReadyTimeoutMs = 100;
    static constexpr std::uint32_t kReadTimeoutMs = 300;
};

enum class Vcnl4200Error : std::int8_t
{
    Success        = 0,
    NullPointer    = -1,
    InvalidArg     = -2,
    InvalidLength  = -3,
    TransferError  = -100
};

template <
    typename I2CBus,
    typename OS,
    std::uint8_t Address,
    typename Config = DefaultConfig>
class Driver
{
public:
    explicit Driver(I2CBus& bus)
        : m_i2cBus(bus)
    {
    }

    [[nodiscard]] Vcnl4200Error init();

    [[nodiscard]] Vcnl4200Error readDeviceId(std::uint16_t& id);

private:
    I2CBus& m_i2cBus;
};

} // namespace vcnl4200

#include "vcnl4200_impl.hpp"
