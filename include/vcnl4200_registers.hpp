/**
 * @file        vcnl4200_registers.hpp
 * @brief       VCNL4200 register definitions.
 */

#pragma once

#include <cstdint>

namespace vcnl4200 {
namespace reg {
constexpr std::uint8_t ALS_CONF = 0x00;
constexpr std::uint8_t ALS_THDH = 0x01;
constexpr std::uint8_t ALS_THDL = 0x02;

constexpr std::uint8_t PS_CONF1 = 0x03;
constexpr std::uint8_t PS_CONF3 = 0x04;
constexpr std::uint8_t PS_CANC = 0x05;
constexpr std::uint8_t PS_THDL = 0x06;
constexpr std::uint8_t PS_THDH = 0x07;

constexpr std::uint8_t PS_DATA = 0x08;
constexpr std::uint8_t ALS_DATA = 0x09;
constexpr std::uint8_t WHITE_DATA = 0x0A;

constexpr std::uint8_t INT_FLAG = 0x0D;
constexpr std::uint8_t ID = 0x0E;
} // namespace reg

namespace reg_mask {
constexpr std::uint16_t kAlsShutdownMask = (1U << 0U);
constexpr std::uint16_t kAlsInterruptEnMask = (1U << 1U);
constexpr std::uint16_t kAlsPersistenceMask = (0x03U << 2U);
constexpr std::uint16_t kAlsInterruptChMask = (1U << 5U);
constexpr std::uint16_t kAlsIntegrationMask = (0x03U << 6U);
constexpr std::uint16_t kPsShutdownMask = (1U << 0U);
constexpr std::uint16_t kPsDutyMask = (0x03U << 6U);
constexpr std::uint16_t kPsPersistenceMask = (0x03U << 4U);
constexpr std::uint16_t kPsIntegrationMask = (0x07U << 1U);
constexpr std::uint16_t kPsOutputResolutionMask = (1U << 3U);
constexpr std::uint16_t kPsInterruptModeMask = (0x03U << 0U);
constexpr std::uint16_t kPsMultiPulseMask = (0x03U << 5U);

constexpr std::uint16_t kPsSmartPersistenceMask = (1U << 4U);

constexpr std::uint16_t kPsActiveForceMask = (1U << 3U);

constexpr std::uint16_t kPsActiveForceTriggerMask = (1U << 2U);

constexpr std::uint16_t kPsSunlightImmunityMask = (1U << 1U);

constexpr std::uint16_t kPsSunlightCancellationMask = (1U << 0U);

constexpr std::uint16_t kPsOperationModeMask = (1U << 13U);
constexpr std::uint16_t kPsSunlightCapabilityMask = (1U << 12U);
constexpr std::uint16_t kPsSunlightProtectionMask = (1U << 11U);
constexpr std::uint16_t kPsLedCurrentMask = (0x07U << 8U);
} // namespace reg_mask

constexpr std::uint16_t DEVICE_ID = 0x1058;

} // namespace vcnl4200
