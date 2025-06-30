/**
 * @file
 * @brief Implementation of random data transmitting satellite
 *
 * @copyright Copyright (c) 2024 DESY and the Constellation authors.
 * This software is distributed under the terms of the EUPL-1.2 License, copied verbatim in the file "LICENSE.md".
 * SPDX-License-Identifier: EUPL-1.2
 */

#include "ACCTransmitterSatellite.hpp"

#include <algorithm>
#include <cstdint>
#include <functional>
#include <random>
#include <stop_token>
#include <string_view>
#include <utility>
#include <vector>

#include "constellation/core/config/Configuration.hpp"
#include "constellation/core/log/log.hpp"
#include "constellation/core/utils/string.hpp"
#include "constellation/satellite/TransmitterSatellite.hpp"

using namespace constellation::config;
using namespace constellation::satellite;
using namespace constellation::utils;

ACCTransmitterSatellite::ACCTransmitterSatellite(std::string_view type, std::string_view name)
    : TransmitterSatellite(type, name)
{
    support_reconfigure();
}

void ACCTransmitterSatellite::initializing(Configuration& config)
{
}

void ACCTransmitterSatellite::reconfiguring(const Configuration& partial_config)
{
}

void ACCTransmitterSatellite::starting(std::string_view run_identifier)
{
//    LOG(INFO) << "Starting run " << run_identifier << " with seed " << to_string(seed_);
}

void ACCTransmitterSatellite::running(const std::stop_token& stop_token)
{
}


void ACCTransmitterSatellite::stopping()
{
//    LOG_IF(WARNING, hwm_reached_ > 0) << "Could not send " << hwm_reached_ << " messages";
}
