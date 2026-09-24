/**
 * @file        vcnl4200.hpp
 * @brief       VCNL4200 proximity and ambient light sensor driver.
 */

#pragma once

#include <cstdint>

namespace vcnl4200 {

inline constexpr std::uint8_t kDeviceAddress = 0x51;

struct DefaultConfig {
  static constexpr std::uint8_t kReadyRetryCount = 3;
  static constexpr std::uint32_t kReadyTimeoutMs = 100;
  static constexpr std::uint32_t kReadTimeoutMs = 300;
};

enum class Vcnl4200Error : std::int8_t {
  Success = 0,
  NullPointer = -1,
  InvalidArg = -2,
  InvalidLength = -3,
  TransferError = -100
};

enum class AlsIntegrationTime : std::uint8_t {
  Ms50 = 0U,  // 00b = 50 ms
  Ms100 = 1U, // 01b = 100 ms
  Ms200 = 2U, // 10b = 200 ms
  Ms400 = 3U  // 11b = 400 ms
};

enum class AlsInterruptPersistence : std::uint8_t {
  Samples1 = 0U, // 00b = 1 sample
  Samples2 = 1U, // 01b = 2 samples
  Samples4 = 2U, // 10b = 4 samples
  Samples8 = 3U  // 11b = 8 samples
};

enum class AlsInterruptChannel : std::uint8_t {
  Als = 0U,  // 0 = ALS channel interrupt
  White = 1U // 1 = White channel interrupt
};

enum class PsDuty : std::uint8_t {
  Ratio1_160 = 0U, // 00 = 1/160
  Ratio1_320 = 1U, // 01 = 1/320
  Ratio1_640 = 2U, // 10 = 1/640
  Ratio1_1280 = 3U // 11 = 1/1280
};

enum class PsPersistence : std::uint8_t {
  Samples1 = 0U, // 00 = 1
  Samples2 = 1U, // 01 = 2
  Samples3 = 2U, // 10 = 3
  Samples4 = 3U  // 11 = 4
};

enum class PsIntegrationTime : std::uint8_t {
  Time1T = 0U,   // 000 = 1T
  Time1_5T = 1U, // 001 = 1.5T
  Time2T = 2U,   // 010 = 2T
  Time4T = 3U,   // 011 = 4T
  Time8T = 4U,   // 100 = 8T
  Time9T = 5U    // 101 = 9T
};

enum class PsOutputResolution : std::uint8_t {
  Bits12 = 0U, // 0 = 12-bit output
  Bits16 = 1U  // 1 = 16-bit output
};

enum class PsInterruptMode : std::uint8_t {
  Disabled = 0U,      // 00
  Closing = 1U,       // 01
  Away = 2U,          // 10
  ClosingAndAway = 3U // 11
};

enum class PsMultiPulse : std::uint8_t {
  Pulses1 = 0U, // 00 = 1 pulse
  Pulses2 = 1U, // 01 = 2 pulses
  Pulses4 = 2U, // 10 = 4 pulses
  Pulses8 = 3U  // 11 = 8 pulses
};

enum class PsSunlightImmunity : std::uint8_t {
  Typical = 0U, // 0 = typical sunlight immunity
  Enhanced = 1U // 1 = 2x typical sunlight immunity
};

enum class PsOperationMode : std::uint8_t { Normal = 0U, LogicOutput = 1U };

enum class PsSunlightCapability : std::uint8_t { Typical = 0U, Enhanced = 1U };
enum class PsSunlightProtectionOutput : std::uint8_t {
  Zero = 0U,
  FullScale = 1U
};

enum class PsLedCurrent : std::uint8_t {
  Ma50 = 0U,
  Ma75 = 1U,
  Ma100 = 2U,
  Ma120 = 3U,
  Ma140 = 4U,
  Ma160 = 5U,
  Ma180 = 6U,
  Ma200 = 7U
};

enum class Enable : std::uint8_t { No = 0U, Yes = 1U };

template <typename I2CBus, typename OS, std::uint8_t Address,
          typename Config = DefaultConfig>
class Driver {
public:
  explicit Driver(I2CBus &bus) : m_i2cBus(bus) {}

  [[nodiscard]] Vcnl4200Error init();

  [[nodiscard]] Vcnl4200Error getDeviceId(std::uint16_t &id);
  /* ALS */

  [[nodiscard]] Vcnl4200Error setAlsEnabled(Enable enable);
  [[nodiscard]] Vcnl4200Error getAlsConfig(std::uint16_t &config);
  [[nodiscard]] Vcnl4200Error setAlsConfig(std::uint16_t config);

  [[nodiscard]] Vcnl4200Error
  getAlsHighInterruptThreshold(std::uint16_t &threshold);
  [[nodiscard]] Vcnl4200Error
  getAlsLowInterruptThreshold(std::uint16_t &threshold);
  [[nodiscard]] Vcnl4200Error
  setAlsHighInterruptThreshold(std::uint16_t threshold);
  [[nodiscard]] Vcnl4200Error
  setAlsLowInterruptThreshold(std::uint16_t threshold);
  [[nodiscard]] Vcnl4200Error setAlsInterruptEnabled(Enable enable);
  [[nodiscard]] Vcnl4200Error
  setAlsInterruptPersistence(AlsInterruptPersistence persistence);
  [[nodiscard]] Vcnl4200Error
  setAlsInterruptChannel(AlsInterruptChannel channel);
  [[nodiscard]] Vcnl4200Error setAlsIntegrationTime(AlsIntegrationTime time);
  [[nodiscard]] Vcnl4200Error getAlsData(std::uint16_t &value);

  /* PS */

  [[nodiscard]] Vcnl4200Error setEnablePs(Enable enable);
  [[nodiscard]] Vcnl4200Error getPsConfig1(std::uint16_t &config);
  [[nodiscard]] Vcnl4200Error getPsConfig3(std::uint16_t &config);
  [[nodiscard]] Vcnl4200Error getPsData(std::uint16_t &value);
  /*
    // PS_CONF1
    enablePs(...)
    setPsDuty(...)
    setPsPersistence(...)
    setPsIntegrationTime(...)

    // PS_CONF2
    setPsOutputResolution(...)
    setPsInterruptMode(...)

    // PS_CONF3
    setPsMultiPulse(...)
    enablePsSmartPersistence(...)
    enablePsActiveForce(...)
    triggerPsActiveForce()
    setPsSunlightImmunity(...)
    enablePsSunlightCancellation(...)

    Vcnl4200Error triggerPsActiveForce();
    Vcnl4200Error setPsOperationMode(PsOperationMode mode);
    Vcnl4200Error setPsSunlightCapability(PsSunlightCapability capability);
    Vcnl4200Error setPsSunlightProtectionOutput(PsSunlightProtectionOutput
    output); Vcnl4200Error setPsLedCurrent(PsLedCurrent current);
  */
  /* White */
  [[nodiscard]] Vcnl4200Error getWhiteData(std::uint16_t &value);

private:
  [[nodiscard]] Vcnl4200Error readRegister(std::uint8_t reg,
                                           std::uint16_t &data);
  [[nodiscard]] Vcnl4200Error writeRegister(std::uint8_t reg,
                                            std::uint16_t data);
  I2CBus &m_i2cBus;
};

} // namespace vcnl4200

#include "vcnl4200_impl.hpp"
