/**
 * @file ACCReceiverSatellite.hpp
 * @brief Implementation of random data transmitting satellite
 *
 * @copyright Copyright (c) 2024 DESY and the Constellation authors.
 * This software is distributed under the terms of the EUPL-1.2 License, copied verbatim in the file "LICENSE.md".
 * SPDX-License-Identifier: EUPL-1.2
 */

#include "ACCReceiverSatellite.hpp"

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
#include "constellation/satellite/ReceiverSatellite.hpp"
#include "constellation/core/message/CDTP1Message.hpp"
#include "constellation/core/protocol/CSCP_definitions.hpp"
#include "ACC.h"

using namespace constellation::config;
using namespace constellation::satellite;
using namespace constellation::utils;



ACCReceiverSatellite::ACCReceiverSatellite(std::string_view type, std::string_view name)
    : ReceiverSatellite(type, name)
{ support_reconfigure();
    // acc_.setName(name);
    // acc_.setType(type);
}

void ACCReceiverSatellite::initializing(constellation::config::Configuration& config)
{
std::string timestamp = "";

}

void ACCReceiverSatellite::launching(){
    LOG(INFO) << "Launching";
    LOG(INFO) << "Get Status";
    submit_status(std::string(getStatus()));

}


void ACCReceiverSatellite::starting(std::string_view run_identifier)
{
    // TODO: set as parameter (config)
    std::filesystem::path base_path_ = "/constellation/results";
    std::string fileName = acc_.nameFile();
    LOG(DEBUG) << "Create File" << run_identifier;
    file_ = create_output_file(base_path_, fileName + std::string(run_identifier), "raw", true);
    if (!file_.is_open()) {
        throw SatelliteError("Could not open output file for writing");
    }
    LOG(INFO) << "Opened output file: " << fileName;
    LOG(INFO) << "Starting run " << run_identifier;
    
    

}


void ACCReceiverSatellite::receive_data(constellation::message::CDTP1Message data_message){
    LOG(INFO) << "Received Data message";
    const auto& header = data_message.getHeader();
    auto payload = data_message.getPayload();
    LOG(DEBUG) << "Writing data event";
    LOG(DEBUG) << "Received data message from " << header.getSender();
    file_.write(reinterpret_cast<const char*>(payload.data()), static_cast<std::streamsize>(payload.size()));
    LOG(DEBUG) << "Wrote " << payload.size() << " bytes to file";
    if(!file_.good()) {
        throw SatelliteError("Error writing to file");
    }

}



void ACCReceiverSatellite::stopping()
{
    //acc_.joinDAQThread();

    LOG(INFO)<<"Stopping";
    file_.close();
    LOG(INFO)<<"Stopped";
    
}

void ACCReceiverSatellite::landing(std::string_view run_identifier)
{
    // nothing?
    LOG(INFO)<<"Landing"<< run_identifier;

    
}



