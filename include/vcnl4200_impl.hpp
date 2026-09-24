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

namespace vcnl4200 {

template <typename I2CBus, typename OS, std::uint8_t Address, typename Config>
Vcnl4200Error Driver<I2CBus, OS, Address, Config>::init() {
  if (m_i2cBus.isDeviceReady(Address, Config::kReadyRetryCount,
                             Config::kReadyTimeoutMs) !=
      interface::I2cError::Success) {
    return Vcnl4200Error::TransferError;
  }

  return Vcnl4200Error::Success;
}

template <typename I2CBus, typename OS, std::uint8_t Address, typename Config>
Vcnl4200Error
Driver<I2CBus, OS, Address, Config>::getDeviceId(std::uint16_t &id) {
  return readRegister(reg::ID, id);
}

/* ALS Settings and Configurations */

template <typename I2CBus, typename OS, std::uint8_t Address, typename Config>
Vcnl4200Error
Driver<I2CBus, OS, Address, Config>::setAlsEnabled(Enable enable) {

  std::uint16_t config = 0U;

  auto result = readRegister(reg::ALS_CONF, config);
  if (result != Vcnl4200Error::Success) {
    return result;
  }
  if (Enable::Yes == enable) {
    config &= ~reg_mask::kAlsShutdownMask; // ALS_SD = 0, ALS enabled
  } else {
    config |= reg_mask::kAlsShutdownMask; // ALS_SD = 1, ALS disabled
  }

  return writeRegister(reg::ALS_CONF, config);
}

template <typename I2CBus, typename OS, std::uint8_t Address, typename Config>
Vcnl4200Error
Driver<I2CBus, OS, Address, Config>::getAlsConfig(std::uint16_t &config) {

  return readRegister(reg::ALS_CONF, config);
}

template <typename I2CBus, typename OS, std::uint8_t Address, typename Config>
Vcnl4200Error
Driver<I2CBus, OS, Address, Config>::setAlsConfig(std::uint16_t config) {

  return writeRegister(reg::ALS_CONF, config);
}

template <typename I2CBus, typename OS, std::uint8_t Address, typename Config>
Vcnl4200Error Driver<I2CBus, OS, Address, Config>::getAlsHighInterruptThreshold(
    std::uint16_t &threshold) {

  return readRegister(reg::ALS_THDH, threshold);
}

template <typename I2CBus, typename OS, std::uint8_t Address, typename Config>
Vcnl4200Error Driver<I2CBus, OS, Address, Config>::getAlsLowInterruptThreshold(
    std::uint16_t &threshold) {

  return readRegister(reg::ALS_THDL, threshold);
}

template <typename I2CBus, typename OS, std::uint8_t Address, typename Config>
Vcnl4200Error Driver<I2CBus, OS, Address, Config>::setAlsHighInterruptThreshold(
    std::uint16_t threshold) {

  return writeRegister(reg::ALS_THDH, threshold);
}

template <typename I2CBus, typename OS, std::uint8_t Address, typename Config>
Vcnl4200Error Driver<I2CBus, OS, Address, Config>::setAlsLowInterruptThreshold(
    std::uint16_t threshold) {

  return writeRegister(reg::ALS_THDL, threshold);
}

template <typename I2CBus, typename OS, std::uint8_t Address, typename Config>
Vcnl4200Error
Driver<I2CBus, OS, Address, Config>::setAlsInterruptEnabled(Enable enable) {

  std::uint16_t config = 0U;

  auto result = readRegister(reg::ALS_CONF, config);
  if (result != Vcnl4200Error::Success) {
    return result;
  }
  if (Enable::Yes == enable) {
    config |=
        reg_mask::kAlsInterruptEnMask; // ALS_INT_EN = 1, ALS interrupt enabled
  } else {
    config &= ~reg_mask::kAlsInterruptEnMask; // ALS_INT_EN = 0, ALS interrupt
                                              // disabled
  }

  return writeRegister(reg::ALS_CONF, config);
}

template <typename I2CBus, typename OS, std::uint8_t Address, typename Config>
Vcnl4200Error Driver<I2CBus, OS, Address, Config>::setAlsInterruptPersistence(
    AlsInterruptPersistence persistence) {

  std::uint16_t config = 0U;

  auto result = readRegister(reg::ALS_CONF, config);
  if (result != Vcnl4200Error::Success) {
    return result;
  }
  config &= ~reg_mask::kAlsPersistenceMask;
  config |= (static_cast<std::uint16_t>(persistence) << 2U);

  return writeRegister(reg::ALS_CONF, config);
}

template <typename I2CBus, typename OS, std::uint8_t Address, typename Config>
Vcnl4200Error Driver<I2CBus, OS, Address, Config>::setAlsInterruptChannel(
    AlsInterruptChannel channel) {

  std::uint16_t config = 0U;

  auto result = readRegister(reg::ALS_CONF, config);
  if (result != Vcnl4200Error::Success) {
    return result;
  }
  config &= ~reg_mask::kAlsInterruptChMask;
  config |= (static_cast<std::uint16_t>(channel) << 5U);

  return writeRegister(reg::ALS_CONF, config);
}

template <typename I2CBus, typename OS, std::uint8_t Address, typename Config>
Vcnl4200Error Driver<I2CBus, OS, Address, Config>::setAlsIntegrationTime(
    AlsIntegrationTime time) {

  std::uint16_t config = 0U;

  auto result = readRegister(reg::ALS_CONF, config);
  if (result != Vcnl4200Error::Success) {
    return result;
  }
  config &= ~reg_mask::kAlsIntegrationMask; /// Clear the bits
  config |= (static_cast<std::uint16_t>(time) << 6U);

  return writeRegister(reg::ALS_CONF, config);
}

template <typename I2CBus, typename OS, std::uint8_t Address, typename Config>
Vcnl4200Error
Driver<I2CBus, OS, Address, Config>::getAlsData(std::uint16_t &value) {

  return readRegister(reg::ALS_DATA, value);
}

/* PS  Settings and Configurations */

template <typename I2CBus, typename OS, std::uint8_t Address, typename Config>
Vcnl4200Error Driver<I2CBus, OS, Address, Config>::setEnablePs(Enable enable) {

  std::uint16_t config = 0U;

  auto result = readRegister(reg::PS_CONF1, config);
  if (result != Vcnl4200Error::Success) {
    return result;
  }
  if (Enable::Yes == enable) {
    config &= ~reg_mask::kPsShutdownMask; // PS_SD = 0, PS enabled
  } else {
    config |= reg_mask::kPsShutdownMask; // PS_SD = 1, PS disabled
  }

  return writeRegister(reg::PS_CONF1, config);
}

template <typename I2CBus, typename OS, std::uint8_t Address, typename Config>
Vcnl4200Error
Driver<I2CBus, OS, Address, Config>::getPsConfig1(std::uint16_t &config) {

  return readRegister(reg::PS_CONF1, config);
}

template <typename I2CBus, typename OS, std::uint8_t Address, typename Config>
Vcnl4200Error
Driver<I2CBus, OS, Address, Config>::getPsConfig3(std::uint16_t &config) {

  return readRegister(reg::PS_CONF3, config);
}

template <typename I2CBus, typename OS, std::uint8_t Address, typename Config>
Vcnl4200Error
Driver<I2CBus, OS, Address, Config>::getPsData(std::uint16_t &value) {

  return readRegister(reg::PS_DATA, value);
}

/* White  Settings and Configurations */

template <typename I2CBus, typename OS, std::uint8_t Address, typename Config>
Vcnl4200Error
Driver<I2CBus, OS, Address, Config>::getWhiteData(std::uint16_t &value) {

  return readRegister(reg::WHITE_DATA, value);
}

/* Private Methods */

template <typename I2CBus, typename OS, std::uint8_t Address, typename Config>
Vcnl4200Error
Driver<I2CBus, OS, Address, Config>::readRegister(std::uint8_t reg,
                                                  std::uint16_t &data) {

  std::uint8_t rx[2] = {};

  if (m_i2cBus.readRegister(Address, reg, rx, sizeof(rx),
                            Config::kReadTimeoutMs) !=
      interface::I2cError::Success) {
    return Vcnl4200Error::TransferError;
  }

  // LOG::info("reg=%02x rx0=%02x rx1=%02x", reg, rx[0], rx[1]);
  data = static_cast<std::uint16_t>(rx[0]) |
         (static_cast<std::uint16_t>(rx[1]) << 8U);

  return Vcnl4200Error::Success;
}

template <typename I2CBus, typename OS, std::uint8_t Address, typename Config>
Vcnl4200Error
Driver<I2CBus, OS, Address, Config>::writeRegister(std::uint8_t reg,
                                                   std::uint16_t data) {

  std::uint8_t tx[2] = {};
  tx[0] = data & 0xFF;
  tx[1] = (data >> 8);

  if (m_i2cBus.writeRegister(Address, reg, tx, sizeof(tx),
                             Config::kReadTimeoutMs) !=
      interface::I2cError::Success) {
    return Vcnl4200Error::TransferError;
  }

  return Vcnl4200Error::Success;
}

} // namespace vcnl4200
