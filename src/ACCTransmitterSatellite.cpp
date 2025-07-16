/**
 * @file ACCTransmitterSatellite.hpp
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
#include "ACC.h"

using namespace constellation::config;
using namespace constellation::satellite;
using namespace constellation::utils;
using namespace constellation::protocol::CSCP;



ACCTransmitterSatellite::ACCTransmitterSatellite(std::string_view type, std::string_view name)
    : TransmitterSatellite(type, name)
{   register_command("checkVersion",
                     "Command to check connected ACDCs for their firmware version",
                     {State::NEW, State::INIT, State::ORBIT},
                     &ACCTransmitterSatellite::checkVersion,
                     this);
    support_reconfigure();
}




std::string ACCTransmitterSatellite::checkVersion()
{
    return acc_->versionCheck(true);
}


void ACCTransmitterSatellite::initializing(constellation::config::Configuration& config)
{
    LOG(INFO)<<"Initializing ACC Transmitter Satellite";
    acc_.reset(new ACC());
    acc_->initializeConfig(config);

}

void ACCTransmitterSatellite::launching(){
LOG(INFO)<<"Launching";
LOG(INFO)<<"Get Status";
    submit_status(std::string(getStatus()));
    acc_->initializeForDataReadout("");


}

void ACCTransmitterSatellite::reconfiguring(const constellation::config::Configuration& partial_config)
{
    LOG(INFO)<<"Reconfiguring";
    // acc_->parseConfig(partial_config);
    LOG(INFO)<<"Reinitializing for run";
    acc_->initializeConfig(partial_config);

}

void ACCTransmitterSatellite::starting(std::string_view run_identifier)
{
    // write new method for data transmission
    LOG(INFO)<<"Starting DAQ thread"<< run_identifier;
    hwm_reached_ = 0;
    acc_->startRun();

    
    //acc_->startDAQThread();
}

void ACCTransmitterSatellite::running(const std::stop_token& stop_token)
{

    while(!stop_token.stop_requested()) {

        LOG(INFO)<<"Running, Listening Data";
        acc_->listenForAcdcData();
        LOG(INFO)<<"Transmitting Data";
        std::vector<std::vector<uint64_t>> acdc_data = acc_->transmitData();
        LOG(INFO)<< "Transmitted" << acdc_data.size() << " frames";
        auto msg = newDataMessage(acdc_data.size());
        LOG(INFO) << "Data message created with " << acdc_data.size() << " frames";
        for(const auto& frame : acdc_data) {
            // Copy vector to frame
            msg.addFrame(std::vector{frame});
            LOG(INFO) << "Added frame of size " << frame.size() << " to message";
        }

        const auto success = trySendDataMessage(msg);
        if(!success) {
            // receiver overloaded or not connected?
            ++hwm_reached_;
            LOG_N(WARNING, 5) << "Could not send message, skipping...";
        }
    }

}


void ACCTransmitterSatellite::stopping()
{
    //acc_->joinDAQThread();
    LOG_IF(WARNING, hwm_reached_ > 0) << "Could not send " << hwm_reached_ << " messages";
    LOG(INFO)<<"Stopping";
    acc_->endRun();
    LOG(INFO)<<"Stopped";
    
}

void ACCTransmitterSatellite::landing(std::string_view run_identifier)
{
    // nothing?
    LOG(INFO)<<"Landing"<< run_identifier;

    
}


// // Logging a message with the given level:
// LOG(INFO) << Received configuration";

// // Logging a message only once (e.g. in a loop):
// LOG_ONCE(WARNING) << "This message appears only once even if the statement "
//                   << "is executed many times";

// // Logging a message N times:
// LOG_N(STATUS, 3) << "This message is logged at most 3 times.";

// // Logging only when a condition evaluates to true:
// LOG_IF(WARNING, parameter == 5) << "Parameter 5 is set "
//                                << "- be careful when opening the box!";

// // Logging a message only every Nth time:
// LOG_NTH(STATUS, 100) << "This message is logged every 100th call to the logging macro.";

// // Logging a message only every T seconds:
// LOG_T(DEBUG, 5s) << "This message is logged at most every 5s";
