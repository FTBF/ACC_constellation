/**
 * @file
 * @brief ACC data producer (transmitting satellite)
 *
 */

#pragma once

#include <cstddef>
#include <cstdint>
#include <limits>
#include <random>
#include <stop_token>
#include <string_view>

#include "constellation/core/config/Configuration.hpp"
#include "constellation/satellite/TransmitterSatellite.hpp"

class ACCTransmitterSatellite final : public constellation::satellite::TransmitterSatellite
{
public:
    ACCTransmitterSatellite(std::string_view type, std::string_view name);

    void initializing(constellation::config::Configuration& config) final;
    void reconfiguring(const constellation::config::Configuration& partial_config) final;
    void starting(std::string_view run_identifier) final;
    void running(const std::stop_token& stop_token) final;
    void stopping() final;

private:


};
