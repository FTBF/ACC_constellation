/**
 * @file 
 * @brief ACC data acceptor (receiving satellite)
 *
 */

#pragma once

#include <cstddef>
#include <cstdint>
#include <limits>
#include <random>
#include <stop_token>
#include <string_view>
#include "constellation/core/message/CDTP1Message.hpp"
#include "constellation/core/config/Configuration.hpp"
#include "constellation/core/config/Dictionary.hpp"
#include "constellation/core/config/Value.hpp"
#include "constellation/satellite/ReceiverSatellite.hpp"
#include "ACC.h"

class ACCReceiverSatellite final : public constellation::satellite::ReceiverSatellite
{
public:
    ACCReceiverSatellite(std::string_view type, std::string_view name);
    void launching();
    void initializing(constellation::config::Configuration& config);
    void reconfiguring(const constellation::config::Configuration& partial_config);
    void starting(std::string_view run_identifier);
    void receive_bor(const constellation::message::CDTP1Message::Header& header, constellation::config::Configuration config);
    void receive_data(constellation::message::CDTP1Message data_message);
    void receive_eor(const constellation::message::CDTP1Message::Header& header, constellation::config::Dictionary run_metadata);
    void stopping();
    void landing(std::string_view run_identifier);

private:
    ACC acc_;
    std::ofstream file_;

};
