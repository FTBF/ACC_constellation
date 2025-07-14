// /**
//  * @file ACCTransmitterSatellite.hpp
//  * @brief Implementation of random data transmitting satellite
//  *
//  * @copyright Copyright (c) 2024 DESY and the Constellation authors.
//  * This software is distributed under the terms of the EUPL-1.2 License, copied verbatim in the file "LICENSE.md".
//  * SPDX-License-Identifier: EUPL-1.2
//  */

// #include "ACCReceiverSatellite.hpp"

// #include <algorithm>
// #include <cstdint>
// #include <functional>
// #include <random>
// #include <stop_token>
// #include <string_view>
// #include <utility>
// #include <vector>

// #include "constellation/core/config/Configuration.hpp"
// #include "constellation/core/log/log.hpp"
// #include "constellation/core/utils/string.hpp"
// #include "constellation/satellite/ReceiverSatellite.hpp"
// #include "constellation/core/message/CDTP1Message.hpp"
// #include "constellation/core/protocol/CSCP_definitions.hpp"
// #include "ACC.h"

// using namespace constellation::config;
// using namespace constellation::satellite;
// using namespace constellation::utils;



// ACCReceiverSatellite::ACCReceiverSatellite(std::string_view type, std::string_view name)
//     : ReceiverSatellite(type, name)
// { support_reconfigure();
//     // acc_.setName(name);
//     // acc_.setType(type);
// }

// void ACCReceiverSatellite::initializing(constellation::config::Configuration& config)
// {
// }

// void ACCReceiverSatellite::launching(){
// LOG(INFO)<<"Launching";
// LOG(INFO)<<"Get Status";
//     submit_status(std::string(getStatus()));
// // acc_.createAcdcs();
// // acc_.whichAcdcsConnected();
// // acc_.setHardwareTrigSrc(1, 0xff); 
// // acc_.toggleCal(1, 0x7FFF, 0xff);
// // setPedestals(unsigned int boardmask, unsigned int chipmask, unsigned int adc); 
// // acc_.setPedestals(0x7FFF, 0xff, 0xff);
//     LOG(INFO)<<"VDD_DLL setting";
//     vector<uint32_t> vdd_dll_vec(5, 0x1f);
//     acc_.setVddDLL(vdd_dll_vec, true);

// }

// void ACCReceiverSatellite::reconfiguring(const constellation::config::Configuration& partial_config)
// {
//     LOG(INFO)<<"Reconfiguring";
//     acc_.parseConfig(partial_config);
//     LOG(INFO)<<"Reinitializing for run";
//     acc_.initializeForDataReadout(partial_config, "");

// }

// void ACCReceiverSatellite::starting(std::string_view run_identifier)
// {
//     // write new method for data transmission
//     LOG(INFO)<<"Starting DAQ thread"<< run_identifier;
//     acc_.startRun_R();
    
//     //acc_.startDAQThread();
// }

// void ACCReceiverSatellite::running(const std::stop_token& stop_token)
// {
//     // LOG(INFO)<<"Running, Listening Data";
//     // acc_.listenForAcdcData();
//     // while(!stop_token.stop_requested()) {
//     //     // Do work
//     //     if(stop_token.stop_requested()) {
//     //         // Handle stop request
//     //         LOG(INFO)<<"Ending Run";
//     //         acc_.stopRun();
//     //         break;
//     //     }
//     // }





// }



// void ACCReceiverSatellite::stopping()
// {
//     //acc_.joinDAQThread();

//     LOG(INFO)<<"Stopping";
//     acc_.stopRun();
//     LOG(INFO)<<"Stopped";
    
// }

// void ACCReceiverSatellite::landing(std::string_view run_identifier)
// {
//     // nothing?
//     LOG(INFO)<<"Landing"<< run_identifier;

    
// }



