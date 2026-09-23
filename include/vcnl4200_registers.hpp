/**
 * @file        vcnl4200_registers.hpp
 * @brief       VCNL4200 register definitions.
 */

#pragma once

#include <cstdint>

namespace vcnl4200
{
namespace reg
{
    constexpr std::uint8_t ALS_CONF    = 0x00;
    constexpr std::uint8_t ALS_THDH    = 0x01;
    constexpr std::uint8_t ALS_THDL    = 0x02;

    constexpr std::uint8_t PS_CONF1    = 0x03;
    constexpr std::uint8_t PS_CONF3    = 0x04;
    constexpr std::uint8_t PS_CANC     = 0x05;
    constexpr std::uint8_t PS_THDL     = 0x06;
    constexpr std::uint8_t PS_THDH     = 0x07;

    constexpr std::uint8_t PS_DATA     = 0x08;
    constexpr std::uint8_t ALS_DATA    = 0x09;
    constexpr std::uint8_t WHITE_DATA  = 0x0A;

    constexpr std::uint8_t INT_FLAG    = 0x0D;
    constexpr std::uint8_t ID          = 0x0E;
}

constexpr std::uint16_t DEVICE_ID = 0x1058;

} // namespace vcnl4200
