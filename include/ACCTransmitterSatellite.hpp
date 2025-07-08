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
#include "constellation/core/config/Dictionary.hpp"
#include "constellation/satellite/TransmitterSatellite.hpp"
#include "ACC.h"

class ACCTransmitterSatellite final : public constellation::satellite::TransmitterSatellite
{
public:
    ACCTransmitterSatellite(std::string_view type, std::string_view name);
    void launching();
    void initializing(constellation::config::Configuration& config);
    void reconfiguring(const constellation::config::Configuration& partial_config);
    void starting(std::string_view run_identifier);
    void running(const std::stop_token& stop_token);
    void stopping();
    void landing(std::string_view run_identifier);

private:
    ACC acc_;

};
