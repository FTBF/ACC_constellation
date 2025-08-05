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
{ 
    // support_reconfigure();
    // acc_.setName(name);
    // acc_.setType(type);
}

void ACCReceiverSatellite::initializing(constellation::config::Configuration& config)
{
base_path_ = config.getPath("output_directory");
LOG(DEBUG)  << "Base path: " << base_path_;
validate_output_directory(base_path_);
LOG(DEBUG) << "Validating output directory: " << base_path_;


std::string timestamp = "";

}

void ACCReceiverSatellite::launching(){
    LOG(INFO) << "Launching";
    LOG(INFO) << "Get Status";
    submit_status(std::string(getStatus()));

}


void ACCReceiverSatellite::starting(std::string_view run_identifier)
{
    LOG(DEBUG) << "Starting ACC Receiver Satellite with run identifier: ";
    // TODO: set as parameter (config)
    // std::filesystem::path base_path_ = "~/constellation/results";
    std::string fileName = acc_.nameFile();
    LOG(INFO) << "Create File" << run_identifier;
    // filename const
    file_ = create_output_file(base_path_, fileName + "_" + std::string(run_identifier), "raw", true);
    if (!file_.is_open()) {
        throw SatelliteError("Could not open output file for writing");
    }
    LOG(INFO) << "Output path: " << base_path_;
    LOG(INFO) << "Final file name: " << fileName + std::string(run_identifier) << ".raw";
    LOG(INFO) << "Starting " << run_identifier;
    
    

}

void ACCReceiverSatellite::receive_bor(const constellation::message::CDTP1Message::Header& header, constellation::config::Configuration config){

}


void ACCReceiverSatellite::receive_eor(const constellation::message::CDTP1Message::Header& header, constellation::config::Dictionary run_metadata){

}
// void EudaqNativeWriterSatellite::FileSerializer::write(std::span<const std::byte> data) {
//     file_.write(to_char_ptr(data.data()), static_cast<std::streamsize>(data.size_bytes()));
//     if(!file_.good()) {
//         throw SatelliteError("Error writing to file");
//     }
// }

// void ACCReceiverSatellite::dataAddress(const constellation::message::CDTP1Message& data_message){

// }



// void ACDC::writeRawDataToFile(const vector<uint64_t>& buffer) const//, string rawfn)
// {
//     if(outFile_) outFile_->write(reinterpret_cast<const char*>(buffer.data()), buffer.size()*sizeof(uint64_t));
//     else         writeErrorLog("No File!!!");
//     return;
// }
        // /** Write integers of different sizes to file */
        // template <typename T> void write_int(T t) {
        //     static_assert(sizeof(t) > 1, "Only supports integers of size > 1 byte");
        //     std::array<std::byte, sizeof t> buf;
        //     for(std::size_t i = 0; i < sizeof t; ++i) {
        //         buf[i] = static_cast<std::byte>(t & 0xff);
        //         t >>= 8;
        //     }
        //     write({buf.data(), buf.size()});
        // }


// void EudaqNativeWriterSatellite::FileSerializer::write_blocks(const std::vector<PayloadBuffer>& payload) {
//     LOG(DEBUG) << "Writing " << payload.size() << " data blocks";

//     // EUDAQ expects a map with frame number as key and vector of uint8_t as value:
//     write_int(static_cast<std::uint32_t>(payload.size()));
//     for(std::uint32_t key = 0; key < static_cast<std::uint32_t>(payload.size()); key++) {
//         write_block(key, payload.at(key));
//     }
// }







// void EudaqNativeWriterSatellite::FileSerializer::serializeDataMsg(const CDTP1Message& data_message) {

//     LOG(DEBUG) << "Writing data event";

//     const auto& header = data_message.getHeader();
//     serialize_header(header, header.getTags());

//     const auto canonical_name = std::string(header.getSender());
//     if(frames_as_blocks_.at(canonical_name)) {
//         // Interpret multiple frames as individual blocks of EUDAQ data:

//         // Write block data:
//         write_blocks(data_message.getPayload());

//         // Zero sub-events:
//         write_int<std::uint32_t>(0);
//     } else {
//         // Interpret each payload frame as a EUDAQ sub-event:

//         // Write zero blocks:
//         write_blocks({});

//         // Write subevents:
//         const auto& payload = data_message.getPayload();
//         write_int(static_cast<std::uint32_t>(payload.size()));

//         for(const auto& frame : payload) {
//             // Repeat the event header of this event - FIXME adjust event number!
//             serialize_header(header, header.getTags());

//             // Write number of blocks and the block itself
//             write_int<std::uint32_t>(1);
//             write_block(0, frame);

//             // Zero sub-sub-events:
//             write_int<std::uint32_t>(0);
//         }
//     }
// }


void ACCReceiverSatellite::receive_data(constellation::message::CDTP1Message data_message){



    LOG(INFO) << "Received Data message";
    const auto& header = data_message.getHeader();
    LOG(DEBUG) << "Writing data event";
    LOG(DEBUG) << "Received data message from " << header.getSender();
    for (const auto& buffer : data_message.getPayload()) {
        std::span<const std::byte> span = buffer.span();
        file_.write(reinterpret_cast<const char*>(span.data()), static_cast<std::streamsize>(span.size()));
    }
    LOG(DEBUG) << "Wrote " << data_message.getPayload().size() << " bytes to file";
    if(!file_.good()) {
        throw SatelliteError("Error writing to file");
    }

    // reassign?


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



