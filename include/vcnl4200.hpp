/**
 * @file vcnl4200.hpp
 * @brief VCNL4200 proximity and ambient light sensor driver.
 */

#pragma once

#include <cstdint>

namespace vcnl4200
{

/// @brief VCNL4200 I2C device address.
  inline constexpr std::uint8_t kDeviceAddress = 0x51;

/// @brief Default driver configuration.
  struct DefaultConfig
  {
	  /// @brief Number of attempts to check device readiness.
	  static constexpr std::uint8_t kReadyRetryCount = 3;

	  /// @brief Timeout for the device readiness check, in milliseconds.
	  static constexpr std::uint32_t kReadyTimeoutMs = 100;

	  /// @brief Timeout for register reads, in milliseconds.
	  static constexpr std::uint32_t kReadTimeoutMs = 300;
  };

/// @brief Result of a VCNL4200 driver operation.
  enum class Vcnl4200Error : std::int8_t
  {
	Success = 0,
	NullPointer = -1,
	InvalidArg = -2,
	InvalidLength = -3,
	TransferError = -100
  };

/// @brief ALS integration time.
  enum class AlsIntegrationTime : std::uint8_t
  {
	Ms50 = 0U,   ///< 50 ms.
	Ms100 = 1U,  ///< 100 ms.
	Ms200 = 2U,  ///< 200 ms.
	Ms400 = 3U   ///< 400 ms.
  };

/// @brief ALS interrupt persistence.
  enum class AlsInterruptPersistence : std::uint8_t
  {
	Samples1 = 0U,  ///< 1 sample.
	Samples2 = 1U,  ///< 2 samples.
	Samples4 = 2U,  ///< 4 samples.
	Samples8 = 3U   ///< 8 samples.
  };

/// @brief ALS interrupt source.
  enum class AlsInterruptChannel : std::uint8_t
  {
	Als = 0U,    ///< ALS channel.
	White = 1U   ///< White channel.
  };

/// @brief Proximity sensor LED duty ratio.
  enum class PsDuty : std::uint8_t
  {
	Ratio1_160 = 0U,   ///< 1/160.
	Ratio1_320 = 1U,   ///< 1/320.
	Ratio1_640 = 2U,   ///< 1/640.
	Ratio1_1280 = 3U   ///< 1/1280.
  };

/// @brief Proximity interrupt persistence.
  enum class PsPersistence : std::uint8_t
  {
	Samples1 = 0U,  ///< 1 sample.
	Samples2 = 1U,  ///< 2 samples.
	Samples3 = 2U,  ///< 3 samples.
	Samples4 = 3U   ///< 4 samples.
  };

/// @brief Proximity integration time.
  enum class PsIntegrationTime : std::uint8_t
  {
	Time1T = 0U,    ///< 1T.
	Time1_5T = 1U,  ///< 1.5T.
	Time2T = 2U,    ///< 2T.
	Time4T = 3U,    ///< 4T.
	Time8T = 4U,    ///< 8T.
	Time9T = 5U     ///< 9T.
  };

/// @brief Proximity output resolution.
  enum class PsOutputResolution : std::uint8_t
  {
	Bits12 = 0U,  ///< 12-bit output.
	Bits16 = 1U   ///< 16-bit output.
  };

/// @brief Proximity interrupt mode.
  enum class PsInterruptMode : std::uint8_t
  {
	Disabled = 0U,       ///< Interrupt disabled.
	Closing = 1U,        ///< Closing detection.
	Away = 2U,           ///< Away detection.
	ClosingAndAway = 3U  ///< Closing and away detection.
  };

/// @brief Number of proximity measurement pulses.
  enum class PsMultiPulse : std::uint8_t
  {
	Pulses1 = 0U,  ///< 1 pulse.
	Pulses2 = 1U,  ///< 2 pulses.
	Pulses4 = 2U,  ///< 4 pulses.
	Pulses8 = 3U   ///< 8 pulses.
  };

/// @brief Proximity sunlight immunity level.
  enum class PsSunlightImmunity : std::uint8_t
  {
	Typical = 0U,   ///< Typical sunlight immunity.
	Enhanced = 1U   ///< Enhanced sunlight immunity.
  };

/// @brief Proximity operating mode.
  enum class PsOperationMode : std::uint8_t
  {
	Normal = 0U,       ///< Normal proximity operation.
	LogicOutput = 1U  ///< Logic output mode.
  };

/// @brief Proximity sunlight capability.
  enum class PsSunlightCapability : std::uint8_t
  {
	Typical = 0U,   ///< Typical sunlight capability.
	Enhanced = 1U   ///< Enhanced sunlight capability.
  };

/// @brief Proximity sunlight protection output.
  enum class PsSunlightProtectionOutput : std::uint8_t
  {
	Zero = 0U,      ///< Output zero.
	FullScale = 1U  ///< Output full scale.
  };

/// @brief Proximity LED current.
  enum class PsLedCurrent : std::uint8_t
  {
	Ma50 = 0U,
	Ma75 = 1U,
	Ma100 = 2U,
	Ma120 = 3U,
	Ma140 = 4U,
	Ma160 = 5U,
	Ma180 = 6U,
	Ma200 = 7U
  };

/// @brief Enable or disable a sensor feature.
  enum class Enable : std::uint8_t
  {
	No = 0U,
	Yes = 1U
  };

  /**
   * @brief VCNL4200 sensor driver.
   *
   * @tparam I2CBus I2C bus interface.
   * @tparam OS Operating system interface.
   * @tparam Address I2C device address.
   * @tparam Config Driver configuration.
   */
  template<typename I2CBus, typename OS, std::uint8_t Address,
	  typename Config = DefaultConfig>
	class Driver
	{
	  public:
		/**
		 * @brief Creates a driver using the given I2C bus.
		 *
		 * @param bus I2C bus interface.
		 */
		explicit Driver(I2CBus &bus) :
			m_i2cBus(bus)
		{
		}

		/// @brief Initializes the VCNL4200.
		[[nodiscard]] Vcnl4200Error init();

		/// @brief Reads the device ID.
		/// @param[out] id Receives the device ID.
		[[nodiscard]] Vcnl4200Error getDeviceId(std::uint16_t &id);

		/// @brief Enables or disables the ambient light sensor.
		[[nodiscard]] Vcnl4200Error setAlsEnabled(Enable enable);

		/// @brief Reads the ALS configuration.
		/// @param[out] config Receives the ALS configuration.
		[[nodiscard]] Vcnl4200Error getAlsConfig(std::uint16_t &config);

		/// @brief Writes the ALS configuration.
		/// @param config ALS configuration value.
		[[nodiscard]] Vcnl4200Error setAlsConfig(std::uint16_t config);

		/// @brief Reads the ALS high interrupt threshold.
		/// @param[out] threshold Receives the threshold value.
		[[nodiscard]] Vcnl4200Error
		getAlsHighInterruptThreshold(std::uint16_t &threshold);

		/// @brief Reads the ALS low interrupt threshold.
		/// @param[out] threshold Receives the threshold value.
		[[nodiscard]] Vcnl4200Error
		getAlsLowInterruptThreshold(std::uint16_t &threshold);

		/// @brief Sets the ALS high interrupt threshold.
		/// @param threshold Threshold value.
		[[nodiscard]] Vcnl4200Error
		setAlsHighInterruptThreshold(std::uint16_t threshold);

		/// @brief Sets the ALS low interrupt threshold.
		/// @param threshold Threshold value.
		[[nodiscard]] Vcnl4200Error
		setAlsLowInterruptThreshold(std::uint16_t threshold);

		/// @brief Enables or disables the ALS interrupt.
		[[nodiscard]] Vcnl4200Error setAlsInterruptEnabled(Enable enable);

		/// @brief Sets the ALS interrupt persistence.
		[[nodiscard]] Vcnl4200Error
		setAlsInterruptPersistence(AlsInterruptPersistence persistence);

		/// @brief Selects the ALS interrupt channel.
		[[nodiscard]] Vcnl4200Error
		setAlsInterruptChannel(AlsInterruptChannel channel);

		/// @brief Sets the ALS integration time.
		[[nodiscard]] Vcnl4200Error
		setAlsIntegrationTime(AlsIntegrationTime time);

		/// @brief Reads the ambient light sensor value.
		/// @param[out] value Receives the ALS value.
		[[nodiscard]] Vcnl4200Error getAlsData(std::uint16_t &value);

		/// @brief Enables or disables the proximity sensor.
		[[nodiscard]] Vcnl4200Error setEnablePs(Enable enable);

		/// @brief Reads the proximity configuration 1.
		/// @param[out] config Receives the configuration value.
		[[nodiscard]] Vcnl4200Error getPsConfig1(std::uint16_t &config);

		/// @brief Reads the proximity configuration 3.
		/// @param[out] config Receives the configuration value.
		[[nodiscard]] Vcnl4200Error getPsConfig3(std::uint16_t &config);

		/// @brief Reads the proximity sensor value.
		/// @param[out] value Receives the proximity value.
		[[nodiscard]] Vcnl4200Error getPsData(std::uint16_t &value);

		/// @brief Reads the white channel value.
		/// @param[out] value Receives the white channel value.
		[[nodiscard]] Vcnl4200Error getWhiteData(std::uint16_t &value);

	  private:
		[[nodiscard]] Vcnl4200Error
		readRegister(std::uint8_t reg, std::uint16_t &data);

		[[nodiscard]] Vcnl4200Error
		writeRegister(std::uint8_t reg, std::uint16_t data);

		I2CBus &m_i2cBus;
	};

} // namespace vcnl4200

#include "vcnl4200_impl.hpp"
