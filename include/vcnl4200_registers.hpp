/**
 * @file vcnl4200_registers.hpp
 * @brief VCNL4200 register definitions.
 */

#pragma once

#include <cstdint>

namespace vcnl4200
{

  namespace reg
  {

/// @brief ALS configuration register.
	constexpr std::uint8_t ALS_CONF = 0x00;

/// @brief ALS high interrupt threshold register.
	constexpr std::uint8_t ALS_THDH = 0x01;

/// @brief ALS low interrupt threshold register.
	constexpr std::uint8_t ALS_THDL = 0x02;

/// @brief Proximity configuration 1 register.
	constexpr std::uint8_t PS_CONF1 = 0x03;

/// @brief Proximity configuration 3 register.
	constexpr std::uint8_t PS_CONF3 = 0x04;

/// @brief Proximity cancellation register.
	constexpr std::uint8_t PS_CANC = 0x05;

/// @brief Proximity low interrupt threshold register.
	constexpr std::uint8_t PS_THDL = 0x06;

/// @brief Proximity high interrupt threshold register.
	constexpr std::uint8_t PS_THDH = 0x07;

/// @brief Proximity data register.
	constexpr std::uint8_t PS_DATA = 0x08;

/// @brief ALS data register.
	constexpr std::uint8_t ALS_DATA = 0x09;

/// @brief White channel data register.
	constexpr std::uint8_t WHITE_DATA = 0x0A;

/// @brief Interrupt flag register.
	constexpr std::uint8_t INT_FLAG = 0x0D;

/// @brief Device ID register.
	constexpr std::uint8_t ID = 0x0E;

  } // namespace reg

  namespace reg_mask
  {

/// @brief ALS shutdown bit mask.
	constexpr std::uint16_t kAlsShutdownMask = (1U << 0U);

/// @brief ALS interrupt enable bit mask.
	constexpr std::uint16_t kAlsInterruptEnMask = (1U << 1U);

/// @brief ALS interrupt persistence bit mask.
	constexpr std::uint16_t kAlsPersistenceMask = (0x03U << 2U);

/// @brief ALS interrupt channel bit mask.
	constexpr std::uint16_t kAlsInterruptChMask = (1U << 5U);

/// @brief ALS integration time bit mask.
	constexpr std::uint16_t kAlsIntegrationMask = (0x03U << 6U);

/// @brief Proximity shutdown bit mask.
	constexpr std::uint16_t kPsShutdownMask = (1U << 0U);

/// @brief Proximity LED duty bit mask.
	constexpr std::uint16_t kPsDutyMask = (0x03U << 6U);

/// @brief Proximity persistence bit mask.
	constexpr std::uint16_t kPsPersistenceMask = (0x03U << 4U);

/// @brief Proximity integration time bit mask.
	constexpr std::uint16_t kPsIntegrationMask = (0x07U << 1U);

/// @brief Proximity output resolution bit mask.
	constexpr std::uint16_t kPsOutputResolutionMask = (1U << 3U);

/// @brief Proximity interrupt mode bit mask.
	constexpr std::uint16_t kPsInterruptModeMask = (0x03U << 0U);

/// @brief Proximity multi-pulse bit mask.
	constexpr std::uint16_t kPsMultiPulseMask = (0x03U << 5U);

/// @brief Proximity smart persistence bit mask.
	constexpr std::uint16_t kPsSmartPersistenceMask = (1U << 4U);

/// @brief Proximity active force bit mask.
	constexpr std::uint16_t kPsActiveForceMask = (1U << 3U);

/// @brief Proximity active force trigger bit mask.
	constexpr std::uint16_t kPsActiveForceTriggerMask = (1U << 2U);

/// @brief Proximity sunlight immunity bit mask.
	constexpr std::uint16_t kPsSunlightImmunityMask = (1U << 1U);

/// @brief Proximity sunlight cancellation bit mask.
	constexpr std::uint16_t kPsSunlightCancellationMask = (1U << 0U);

/// @brief Proximity operation mode bit mask.
	constexpr std::uint16_t kPsOperationModeMask = (1U << 13U);

/// @brief Proximity sunlight capability bit mask.
	constexpr std::uint16_t kPsSunlightCapabilityMask = (1U << 12U);

/// @brief Proximity sunlight protection output bit mask.
	constexpr std::uint16_t kPsSunlightProtectionMask = (1U << 11U);

/// @brief Proximity LED current bit mask.
	constexpr std::uint16_t kPsLedCurrentMask = (0x07U << 8U);

  } // namespace reg_mask

/// @brief Expected VCNL4200 device ID.
  constexpr std::uint16_t kDeviceId = 0x1058;

} // namespace vcnl4200
