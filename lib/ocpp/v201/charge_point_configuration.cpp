// SPDX-License-Identifier: Apache-2.0
// Copyright 2020 - 2023 Pionix GmbH and Contributors to EVerest
#include <fstream>

#include <ocpp/common/schemas.hpp>
#include <ocpp/v201/charge_point_configuration.hpp>

namespace ocpp {
namespace v201 {

// from: StandardizedComponent
namespace conversions {
std::string standardized_component_to_string(StandardizedComponent e) {
    switch (e) {
    case StandardizedComponent::ConnectedEV:
        return "ConnectedEV";
    case StandardizedComponent::SecurityCtrlr:
        return "SecurityCtrlr";
    case StandardizedComponent::DeviceDataCtrlr:
        return "DeviceDataCtrlr";
    case StandardizedComponent::ReservationCtrlr:
        return "ReservationCtrlr";
    case StandardizedComponent::CustomizationCtrlr:
        return "CustomizationCtrlr";
    case StandardizedComponent::OCPPCommCtrlr:
        return "OCPPCommCtrlr";
    case StandardizedComponent::DistributionPanel:
        return "DistributionPanel";
    case StandardizedComponent::MonitoringCtrlr:
        return "MonitoringCtrlr";
    case StandardizedComponent::TxCtrlr:
        return "TxCtrlr";
    case StandardizedComponent::EVSE:
        return "EVSE";
    case StandardizedComponent::InternalCtrlr:
        return "InternalCtrlr";
    case StandardizedComponent::SmartChargingCtrlr:
        return "SmartChargingCtrlr";
    case StandardizedComponent::AlignedDataCtrlr:
        return "AlignedDataCtrlr";
    case StandardizedComponent::ChargingStation:
        return "ChargingStation";
    case StandardizedComponent::Controller:
        return "Controller";
    case StandardizedComponent::FiscalMetering:
        return "FiscalMetering";
    case StandardizedComponent::ClockCtrlr:
        return "ClockCtrlr";
    case StandardizedComponent::CHAdeMOCtrlr:
        return "CHAdeMOCtrlr";
    case StandardizedComponent::TokenReader:
        return "TokenReader";
    case StandardizedComponent::LocalEnergyStorage:
        return "LocalEnergyStorage";
    case StandardizedComponent::Connector:
        return "Connector";
    case StandardizedComponent::LocalAuthListCtrlr:
        return "LocalAuthListCtrlr";
    case StandardizedComponent::AuthCacheCtrlr:
        return "AuthCacheCtrlr";
    case StandardizedComponent::AuthCtrlr:
        return "AuthCtrlr";
    case StandardizedComponent::CPPWMController:
        return "CPPWMController";
    case StandardizedComponent::DisplayMessageCtrlr:
        return "DisplayMessageCtrlr";
    case StandardizedComponent::ISO15118Ctrlr:
        return "ISO15118Ctrlr";
    case StandardizedComponent::TariffCostCtrlr:
        return "TariffCostCtrlr";
    case StandardizedComponent::SampledDataCtrlr:
        return "SampledDataCtrlr";
    }

    throw std::out_of_range("No known string conversion for provided enum of type StandardizedComponent");
}

StandardizedComponent string_to_standardized_component(const std::string& s) {
    if (s == "ConnectedEV") {
        return StandardizedComponent::ConnectedEV;
    }
    if (s == "SecurityCtrlr") {
        return StandardizedComponent::SecurityCtrlr;
    }
    if (s == "DeviceDataCtrlr") {
        return StandardizedComponent::DeviceDataCtrlr;
    }
    if (s == "ReservationCtrlr") {
        return StandardizedComponent::ReservationCtrlr;
    }
    if (s == "CustomizationCtrlr") {
        return StandardizedComponent::CustomizationCtrlr;
    }
    if (s == "OCPPCommCtrlr") {
        return StandardizedComponent::OCPPCommCtrlr;
    }
    if (s == "DistributionPanel") {
        return StandardizedComponent::DistributionPanel;
    }
    if (s == "MonitoringCtrlr") {
        return StandardizedComponent::MonitoringCtrlr;
    }
    if (s == "TxCtrlr") {
        return StandardizedComponent::TxCtrlr;
    }
    if (s == "EVSE") {
        return StandardizedComponent::EVSE;
    }
    if (s == "InternalCtrlr") {
        return StandardizedComponent::InternalCtrlr;
    }
    if (s == "SmartChargingCtrlr") {
        return StandardizedComponent::SmartChargingCtrlr;
    }
    if (s == "AlignedDataCtrlr") {
        return StandardizedComponent::AlignedDataCtrlr;
    }
    if (s == "ChargingStation") {
        return StandardizedComponent::ChargingStation;
    }
    if (s == "Controller") {
        return StandardizedComponent::Controller;
    }
    if (s == "FiscalMetering") {
        return StandardizedComponent::FiscalMetering;
    }
    if (s == "ClockCtrlr") {
        return StandardizedComponent::ClockCtrlr;
    }
    if (s == "CHAdeMOCtrlr") {
        return StandardizedComponent::CHAdeMOCtrlr;
    }
    if (s == "TokenReader") {
        return StandardizedComponent::TokenReader;
    }
    if (s == "LocalEnergyStorage") {
        return StandardizedComponent::LocalEnergyStorage;
    }
    if (s == "Connector") {
        return StandardizedComponent::Connector;
    }
    if (s == "LocalAuthListCtrlr") {
        return StandardizedComponent::LocalAuthListCtrlr;
    }
    if (s == "AuthCacheCtrlr") {
        return StandardizedComponent::AuthCacheCtrlr;
    }
    if (s == "AuthCtrlr") {
        return StandardizedComponent::AuthCtrlr;
    }
    if (s == "CPPWMController") {
        return StandardizedComponent::CPPWMController;
    }
    if (s == "DisplayMessageCtrlr") {
        return StandardizedComponent::DisplayMessageCtrlr;
    }
    if (s == "ISO15118Ctrlr") {
        return StandardizedComponent::ISO15118Ctrlr;
    }
    if (s == "TariffCostCtrlr") {
        return StandardizedComponent::TariffCostCtrlr;
    }
    if (s == "SampledDataCtrlr") {
        return StandardizedComponent::SampledDataCtrlr;
    }

    throw std::out_of_range("Provided string " + s + " could not be converted to enum of type StandardizedComponent");
}
} // namespace conversions

std::ostream& operator<<(std::ostream& os, const StandardizedComponent& standardized_component) {
    os << conversions::standardized_component_to_string(standardized_component);
    return os;
}

ChargePointConfiguration::ChargePointConfiguration(const json& config, const std::string& ocpp_main_path,
                                                   std::shared_ptr<ocpp::PkiHandler> pki_handler) {
    auto json_config = config;

    // validate config entries
    Schemas schemas = Schemas(boost::filesystem::path(ocpp_main_path) / "component_schemas");
    try {
        const auto patch = schemas.get_validator()->validate(json_config);
        if (!patch.is_null()) {
            // extend config with default values
            EVLOG_debug << "Adding the following default values to the charge point configuration: " << patch;
            json_config = json_config.patch(patch);
        }
    } catch (const std::exception& e) {
        EVLOG_error << "Validation failed, here is why: " << e.what() << "\n";
    }

    std::set<boost::filesystem::path> available_schemas_paths;
    const auto profile_schemas_path = boost::filesystem::path(ocpp_main_path) / "profile_schemas";

    // iterating over schemas to initialize standardized components and variables
    for (auto file : boost::filesystem::directory_iterator(profile_schemas_path)) {
        if (file.path().filename() != "Config.json") {

            auto component_name = file.path().filename().replace_extension("").string();
            this->components.insert(std::pair<StandardizedComponent, EnhancedComponent>(
                conversions::string_to_standardized_component(component_name), EnhancedComponent(component_name)));

            std::ifstream ifs(file.path().c_str());
            std::string schema_file((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
            const auto schema = json::parse(schema_file);

            json properties = schema["properties"];
            for (auto property_it = properties.begin(); property_it != properties.end(); ++property_it) {
                VariableCharacteristics characteristics(property_it.value()["characteristics"]);
                VariableAttribute attribute(property_it.value()["attributes"][0]);
                EnhancedVariable enhanced_variable;
                enhanced_variable.name = property_it.key();
                enhanced_variable.characteristics.emplace(characteristics);
                enhanced_variable.attributes[AttributeEnum::Actual] = attribute;

                this->components.at(conversions::string_to_standardized_component(component_name))
                    .variables[property_it.key()] = enhanced_variable;
            }
        }
    }

    // components and respective variables are initialized
    // insert variables of components using the given config file
    for (auto component_it = config.begin(); component_it != config.end(); ++component_it) {
        auto component_name = component_it.key();
        auto component_obj = component_it.value();

        for (auto variable_it = component_obj.begin(); variable_it != component_obj.end(); ++variable_it) {
            const auto variable_name = variable_it.key();
            CiString<2500> value;

            if (variable_it.value().type() == json::value_t::boolean) {
                value.set(ocpp::conversions::bool_to_string(variable_it.value()));
            } else if (variable_it.value().type() == json::value_t::number_unsigned) {
                value.set(std::to_string(variable_it.value().get<int>()));
            } else if (variable_it.value().type() == json::value_t::number_integer) {
                value.set(std::to_string(variable_it.value().get<int>()));
            } else if (variable_it.value().type() == json::value_t::number_float) {
                value.set(ocpp::conversions::double_to_string(variable_it.value()));
            } else if (variable_it.value().type() == json::value_t::array) {
                value.set("[]");
            } else if (variable_it.value().type() == json::value_t::string) {
                value.set(variable_it.value());
            } else {
                EVLOG_AND_THROW(std::runtime_error("Could not initialize enhanced variable with name"));
            }

            this->components.at(conversions::string_to_standardized_component(component_name))
                .variables.at(variable_name)
                .attributes.at(AttributeEnum::Actual)
                .value.emplace(value);
        }
    }
}

std::string ChargePointConfiguration::get_charge_point_id() {
    return this->components.at(StandardizedComponent::InternalCtrlr)
        .variables.at("ChargePointId")
        .attributes.at(AttributeEnum::Actual)
        .value.value();
}

void ChargePointConfiguration::set_charge_point_id(const std::string& charge_point_id) {
    this->components.at(StandardizedComponent::InternalCtrlr)
        .variables.at("ChargePointId")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(charge_point_id);
}

std::string ChargePointConfiguration::get_central_system_uri() {
    return this->components.at(StandardizedComponent::InternalCtrlr)
        .variables.at("CentralSystemURI")
        .attributes.at(AttributeEnum::Actual)
        .value.value();
}

void ChargePointConfiguration::set_central_system_uri(const std::string& central_system_uri) {
    this->components.at(StandardizedComponent::InternalCtrlr)
        .variables.at("CentralSystemURI")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(central_system_uri);
}

std::string ChargePointConfiguration::get_charge_box_serial_number() {
    return this->components.at(StandardizedComponent::InternalCtrlr)
        .variables.at("ChargeBoxSerialNumber")
        .attributes.at(AttributeEnum::Actual)
        .value.value();
}

void ChargePointConfiguration::set_charge_box_serial_number(const std::string& charge_box_serial_number) {
    this->components.at(StandardizedComponent::InternalCtrlr)
        .variables.at("ChargeBoxSerialNumber")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(charge_box_serial_number);
}

std::string ChargePointConfiguration::get_charge_point_model() {
    return this->components.at(StandardizedComponent::InternalCtrlr)
        .variables.at("ChargePointModel")
        .attributes.at(AttributeEnum::Actual)
        .value.value();
}

void ChargePointConfiguration::set_charge_point_model(const std::string& charge_point_model) {
    this->components.at(StandardizedComponent::InternalCtrlr)
        .variables.at("ChargePointModel")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(charge_point_model);
}

std::string ChargePointConfiguration::get_charge_point_vendor() {
    return this->components.at(StandardizedComponent::InternalCtrlr)
        .variables.at("ChargePointVendor")
        .attributes.at(AttributeEnum::Actual)
        .value.value();
}

void ChargePointConfiguration::set_charge_point_vendor(const std::string& charge_point_vendor) {
    this->components.at(StandardizedComponent::InternalCtrlr)
        .variables.at("ChargePointVendor")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(charge_point_vendor);
}

std::string ChargePointConfiguration::get_firmware_version() {
    return this->components.at(StandardizedComponent::InternalCtrlr)
        .variables.at("FirmwareVersion")
        .attributes.at(AttributeEnum::Actual)
        .value.value();
}

void ChargePointConfiguration::set_firmware_version(const std::string& firmware_version) {
    this->components.at(StandardizedComponent::InternalCtrlr)
        .variables.at("FirmwareVersion")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(firmware_version);
}

std::string ChargePointConfiguration::get_supported_ciphers12() {
    return this->components.at(StandardizedComponent::InternalCtrlr)
        .variables.at("SupportedCiphers12")
        .attributes.at(AttributeEnum::Actual)
        .value.value();
}

void ChargePointConfiguration::set_supported_ciphers12(const std::string& supported_ciphers12) {
    this->components.at(StandardizedComponent::InternalCtrlr)
        .variables.at("SupportedCiphers12")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(supported_ciphers12);
}

std::string ChargePointConfiguration::get_supported_ciphers13() {
    return this->components.at(StandardizedComponent::InternalCtrlr)
        .variables.at("SupportedCiphers13")
        .attributes.at(AttributeEnum::Actual)
        .value.value();
}

void ChargePointConfiguration::set_supported_ciphers13(const std::string& supported_ciphers13) {
    this->components.at(StandardizedComponent::InternalCtrlr)
        .variables.at("SupportedCiphers13")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(supported_ciphers13);
}

int32_t ChargePointConfiguration::get_websocket_reconnect_interval() {
    return std::stoi(this->components.at(StandardizedComponent::InternalCtrlr)
                         .variables.at("WebsocketReconnectInterval")
                         .attributes.at(AttributeEnum::Actual)
                         .value.value());
}

void ChargePointConfiguration::set_websocket_reconnect_interval(const int32_t& websocket_reconnect_interval) {
    this->components.at(StandardizedComponent::InternalCtrlr)
        .variables.at("WebsocketReconnectInterval")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(std::to_string(websocket_reconnect_interval));
}

int32_t ChargePointConfiguration::get_interval() {
    return std::stoi(this->components.at(StandardizedComponent::AlignedDataCtrlr)
                         .variables.at("Interval")
                         .attributes.at(AttributeEnum::Actual)
                         .value.value());
}

void ChargePointConfiguration::set_interval(const int32_t& interval) {
    this->components.at(StandardizedComponent::AlignedDataCtrlr)
        .variables.at("Interval")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(std::to_string(interval));
}

std::string ChargePointConfiguration::get_measurands() {
    return this->components.at(StandardizedComponent::AlignedDataCtrlr)
        .variables.at("Measurands")
        .attributes.at(AttributeEnum::Actual)
        .value.value();
}

void ChargePointConfiguration::set_measurands(const std::string& measurands) {
    this->components.at(StandardizedComponent::AlignedDataCtrlr)
        .variables.at("Measurands")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(measurands);
}

int32_t ChargePointConfiguration::get_aligned_data_ctrlr_tx_ended_interval() {
    return std::stoi(this->components.at(StandardizedComponent::AlignedDataCtrlr)
                         .variables.at("TxEndedInterval")
                         .attributes.at(AttributeEnum::Actual)
                         .value.value());
}

void ChargePointConfiguration::set_aligned_data_ctrlr_tx_ended_interval(
    const int32_t& aligned_data_ctrlr_tx_ended_interval) {
    this->components.at(StandardizedComponent::AlignedDataCtrlr)
        .variables.at("TxEndedInterval")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(std::to_string(aligned_data_ctrlr_tx_ended_interval));
}

std::string ChargePointConfiguration::get_aligned_data_ctrlr_tx_ended_measurands() {
    return this->components.at(StandardizedComponent::AlignedDataCtrlr)
        .variables.at("TxEndedMeasurands")
        .attributes.at(AttributeEnum::Actual)
        .value.value();
}

void ChargePointConfiguration::set_aligned_data_ctrlr_tx_ended_measurands(
    const std::string& aligned_data_ctrlr_tx_ended_measurands) {
    this->components.at(StandardizedComponent::AlignedDataCtrlr)
        .variables.at("TxEndedMeasurands")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(aligned_data_ctrlr_tx_ended_measurands);
}

bool ChargePointConfiguration::get_authorize_remote_start() {
    return ocpp::conversions::string_to_bool(this->components.at(StandardizedComponent::AuthCtrlr)
                                                 .variables.at("AuthorizeRemoteStart")
                                                 .attributes.at(AttributeEnum::Actual)
                                                 .value.value());
}

void ChargePointConfiguration::set_authorize_remote_start(const bool& authorize_remote_start) {
    this->components.at(StandardizedComponent::AuthCtrlr)
        .variables.at("AuthorizeRemoteStart")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(ocpp::conversions::bool_to_string(authorize_remote_start));
}

bool ChargePointConfiguration::get_local_authorize_offline() {
    return ocpp::conversions::string_to_bool(this->components.at(StandardizedComponent::AuthCtrlr)
                                                 .variables.at("LocalAuthorizeOffline")
                                                 .attributes.at(AttributeEnum::Actual)
                                                 .value.value());
}

void ChargePointConfiguration::set_local_authorize_offline(const bool& local_authorize_offline) {
    this->components.at(StandardizedComponent::AuthCtrlr)
        .variables.at("LocalAuthorizeOffline")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(ocpp::conversions::bool_to_string(local_authorize_offline));
}

bool ChargePointConfiguration::get_local_pre_authorize() {
    return ocpp::conversions::string_to_bool(this->components.at(StandardizedComponent::AuthCtrlr)
                                                 .variables.at("LocalPreAuthorize")
                                                 .attributes.at(AttributeEnum::Actual)
                                                 .value.value());
}

void ChargePointConfiguration::set_local_pre_authorize(const bool& local_pre_authorize) {
    this->components.at(StandardizedComponent::AuthCtrlr)
        .variables.at("LocalPreAuthorize")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(ocpp::conversions::bool_to_string(local_pre_authorize));
}

std::string ChargePointConfiguration::get_charging_station_availability_state() {
    return this->components.at(StandardizedComponent::ChargingStation)
        .variables.at("AvailabilityState")
        .attributes.at(AttributeEnum::Actual)
        .value.value();
}

void ChargePointConfiguration::set_charging_station_availability_state(
    const std::string& charging_station_availability_state) {
    this->components.at(StandardizedComponent::ChargingStation)
        .variables.at("AvailabilityState")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(charging_station_availability_state);
}

bool ChargePointConfiguration::get_charging_station_available() {
    return ocpp::conversions::string_to_bool(this->components.at(StandardizedComponent::ChargingStation)
                                                 .variables.at("Available")
                                                 .attributes.at(AttributeEnum::Actual)
                                                 .value.value());
}

void ChargePointConfiguration::set_charging_station_available(const bool& charging_station_available) {
    this->components.at(StandardizedComponent::ChargingStation)
        .variables.at("Available")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(ocpp::conversions::bool_to_string(charging_station_available));
}

int32_t ChargePointConfiguration::get_charging_station_supply_phases() {
    return std::stoi(this->components.at(StandardizedComponent::ChargingStation)
                         .variables.at("SupplyPhases")
                         .attributes.at(AttributeEnum::Actual)
                         .value.value());
}

void ChargePointConfiguration::set_charging_station_supply_phases(const int32_t& charging_station_supply_phases) {
    this->components.at(StandardizedComponent::ChargingStation)
        .variables.at("SupplyPhases")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(std::to_string(charging_station_supply_phases));
}

ocpp::DateTime ChargePointConfiguration::get_date_time() {
    return ocpp::DateTime(this->components.at(StandardizedComponent::ClockCtrlr)
                              .variables.at("DateTime")
                              .attributes.at(AttributeEnum::Actual)
                              .value.value());
}

void ChargePointConfiguration::set_date_time(const ocpp::DateTime& date_time) {
    this->components.at(StandardizedComponent::ClockCtrlr)
        .variables.at("DateTime")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(date_time.to_rfc3339());
}

std::string ChargePointConfiguration::get_time_source() {
    return this->components.at(StandardizedComponent::ClockCtrlr)
        .variables.at("TimeSource")
        .attributes.at(AttributeEnum::Actual)
        .value.value();
}

void ChargePointConfiguration::set_time_source(const std::string& time_source) {
    this->components.at(StandardizedComponent::ClockCtrlr)
        .variables.at("TimeSource")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(time_source);
}

bool ChargePointConfiguration::get_connector_available() {
    return ocpp::conversions::string_to_bool(this->components.at(StandardizedComponent::Connector)
                                                 .variables.at("Available")
                                                 .attributes.at(AttributeEnum::Actual)
                                                 .value.value());
}

void ChargePointConfiguration::set_connector_available(const bool& connector_available) {
    this->components.at(StandardizedComponent::Connector)
        .variables.at("Available")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(ocpp::conversions::bool_to_string(connector_available));
}

std::string ChargePointConfiguration::get_connector_type() {
    return this->components.at(StandardizedComponent::Connector)
        .variables.at("ConnectorType")
        .attributes.at(AttributeEnum::Actual)
        .value.value();
}

void ChargePointConfiguration::set_connector_type(const std::string& connector_type) {
    this->components.at(StandardizedComponent::Connector)
        .variables.at("ConnectorType")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(connector_type);
}

int32_t ChargePointConfiguration::get_connector_supply_phases() {
    return std::stoi(this->components.at(StandardizedComponent::Connector)
                         .variables.at("SupplyPhases")
                         .attributes.at(AttributeEnum::Actual)
                         .value.value());
}

void ChargePointConfiguration::set_connector_supply_phases(const int32_t& connector_supply_phases) {
    this->components.at(StandardizedComponent::Connector)
        .variables.at("SupplyPhases")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(std::to_string(connector_supply_phases));
}

int32_t ChargePointConfiguration::get_bytes_per_message_get_report() {
    return std::stoi(this->components.at(StandardizedComponent::DeviceDataCtrlr)
                         .variables.at("BytesPerMessage")
                         .attributes.at(AttributeEnum::Actual)
                         .value.value());
}

void ChargePointConfiguration::set_bytes_per_message_get_report(const int32_t& bytes_per_message_get_report) {
    this->components.at(StandardizedComponent::DeviceDataCtrlr)
        .variables.at("BytesPerMessage")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(std::to_string(bytes_per_message_get_report));
}

int32_t ChargePointConfiguration::get_bytes_per_message_get_variables() {
    return std::stoi(this->components.at(StandardizedComponent::DeviceDataCtrlr)
                         .variables.at("BytesPerMessage")
                         .attributes.at(AttributeEnum::Actual)
                         .value.value());
}

void ChargePointConfiguration::set_bytes_per_message_get_variables(const int32_t& bytes_per_message_get_variables) {
    this->components.at(StandardizedComponent::DeviceDataCtrlr)
        .variables.at("BytesPerMessage")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(std::to_string(bytes_per_message_get_variables));
}

int32_t ChargePointConfiguration::get_bytes_per_message_set_variables() {
    return std::stoi(this->components.at(StandardizedComponent::DeviceDataCtrlr)
                         .variables.at("BytesPerMessage")
                         .attributes.at(AttributeEnum::Actual)
                         .value.value());
}

void ChargePointConfiguration::set_bytes_per_message_set_variables(const int32_t& bytes_per_message_set_variables) {
    this->components.at(StandardizedComponent::DeviceDataCtrlr)
        .variables.at("BytesPerMessage")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(std::to_string(bytes_per_message_set_variables));
}

int32_t ChargePointConfiguration::get_items_per_message_get_report() {
    return std::stoi(this->components.at(StandardizedComponent::DeviceDataCtrlr)
                         .variables.at("ItemsPerMessage")
                         .attributes.at(AttributeEnum::Actual)
                         .value.value());
}

void ChargePointConfiguration::set_items_per_message_get_report(const int32_t& items_per_message_get_report) {
    this->components.at(StandardizedComponent::DeviceDataCtrlr)
        .variables.at("ItemsPerMessage")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(std::to_string(items_per_message_get_report));
}

int32_t ChargePointConfiguration::get_items_per_message_get_variables() {
    return std::stoi(this->components.at(StandardizedComponent::DeviceDataCtrlr)
                         .variables.at("ItemsPerMessage")
                         .attributes.at(AttributeEnum::Actual)
                         .value.value());
}

void ChargePointConfiguration::set_items_per_message_get_variables(const int32_t& items_per_message_get_variables) {
    this->components.at(StandardizedComponent::DeviceDataCtrlr)
        .variables.at("ItemsPerMessage")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(std::to_string(items_per_message_get_variables));
}

int32_t ChargePointConfiguration::get_items_per_message_set_variables() {
    return std::stoi(this->components.at(StandardizedComponent::DeviceDataCtrlr)
                         .variables.at("ItemsPerMessage")
                         .attributes.at(AttributeEnum::Actual)
                         .value.value());
}

void ChargePointConfiguration::set_items_per_message_set_variables(const int32_t& items_per_message_set_variables) {
    this->components.at(StandardizedComponent::DeviceDataCtrlr)
        .variables.at("ItemsPerMessage")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(std::to_string(items_per_message_set_variables));
}

int32_t ChargePointConfiguration::get_display_messages() {
    return std::stoi(this->components.at(StandardizedComponent::DisplayMessageCtrlr)
                         .variables.at("DisplayMessages")
                         .attributes.at(AttributeEnum::Actual)
                         .value.value());
}

void ChargePointConfiguration::set_display_messages(const int32_t& display_messages) {
    this->components.at(StandardizedComponent::DisplayMessageCtrlr)
        .variables.at("DisplayMessages")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(std::to_string(display_messages));
}

std::string ChargePointConfiguration::get_supported_formats() {
    return this->components.at(StandardizedComponent::DisplayMessageCtrlr)
        .variables.at("SupportedFormats")
        .attributes.at(AttributeEnum::Actual)
        .value.value();
}

void ChargePointConfiguration::set_supported_formats(const std::string& supported_formats) {
    this->components.at(StandardizedComponent::DisplayMessageCtrlr)
        .variables.at("SupportedFormats")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(supported_formats);
}

std::string ChargePointConfiguration::get_supported_priorities() {
    return this->components.at(StandardizedComponent::DisplayMessageCtrlr)
        .variables.at("SupportedPriorities")
        .attributes.at(AttributeEnum::Actual)
        .value.value();
}

void ChargePointConfiguration::set_supported_priorities(const std::string& supported_priorities) {
    this->components.at(StandardizedComponent::DisplayMessageCtrlr)
        .variables.at("SupportedPriorities")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(supported_priorities);
}

std::string ChargePointConfiguration::get_evse_availability_state() {
    return this->components.at(StandardizedComponent::EVSE)
        .variables.at("AvailabilityState")
        .attributes.at(AttributeEnum::Actual)
        .value.value();
}

void ChargePointConfiguration::set_evse_availability_state(const std::string& evse_availability_state) {
    this->components.at(StandardizedComponent::EVSE)
        .variables.at("AvailabilityState")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(evse_availability_state);
}

bool ChargePointConfiguration::get_evse_available() {
    return ocpp::conversions::string_to_bool(this->components.at(StandardizedComponent::EVSE)
                                                 .variables.at("Available")
                                                 .attributes.at(AttributeEnum::Actual)
                                                 .value.value());
}

void ChargePointConfiguration::set_evse_available(const bool& evse_available) {
    this->components.at(StandardizedComponent::EVSE)
        .variables.at("Available")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(ocpp::conversions::bool_to_string(evse_available));
}

double ChargePointConfiguration::get_power() {
    return std::stod(this->components.at(StandardizedComponent::EVSE)
                         .variables.at("Power")
                         .attributes.at(AttributeEnum::Actual)
                         .value.value());
}

void ChargePointConfiguration::set_power(const double& power) {
    this->components.at(StandardizedComponent::EVSE)
        .variables.at("Power")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(ocpp::conversions::double_to_string(power));
}

int32_t ChargePointConfiguration::get_evse_supply_phases() {
    return std::stoi(this->components.at(StandardizedComponent::EVSE)
                         .variables.at("SupplyPhases")
                         .attributes.at(AttributeEnum::Actual)
                         .value.value());
}

void ChargePointConfiguration::set_evse_supply_phases(const int32_t& evse_supply_phases) {
    this->components.at(StandardizedComponent::EVSE)
        .variables.at("SupplyPhases")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(std::to_string(evse_supply_phases));
}

bool ChargePointConfiguration::get_contract_validation_offline() {
    return ocpp::conversions::string_to_bool(this->components.at(StandardizedComponent::ISO15118Ctrlr)
                                                 .variables.at("ContractValidationOffline")
                                                 .attributes.at(AttributeEnum::Actual)
                                                 .value.value());
}

void ChargePointConfiguration::set_contract_validation_offline(const bool& contract_validation_offline) {
    this->components.at(StandardizedComponent::ISO15118Ctrlr)
        .variables.at("ContractValidationOffline")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(ocpp::conversions::bool_to_string(contract_validation_offline));
}

int32_t ChargePointConfiguration::get_bytes_per_message() {
    return std::stoi(this->components.at(StandardizedComponent::LocalAuthListCtrlr)
                         .variables.at("BytesPerMessage")
                         .attributes.at(AttributeEnum::Actual)
                         .value.value());
}

void ChargePointConfiguration::set_bytes_per_message(const int32_t& bytes_per_message) {
    this->components.at(StandardizedComponent::LocalAuthListCtrlr)
        .variables.at("BytesPerMessage")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(std::to_string(bytes_per_message));
}

int32_t ChargePointConfiguration::get_entries() {
    return std::stoi(this->components.at(StandardizedComponent::LocalAuthListCtrlr)
                         .variables.at("Entries")
                         .attributes.at(AttributeEnum::Actual)
                         .value.value());
}

void ChargePointConfiguration::set_entries(const int32_t& entries) {
    this->components.at(StandardizedComponent::LocalAuthListCtrlr)
        .variables.at("Entries")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(std::to_string(entries));
}

int32_t ChargePointConfiguration::get_items_per_message() {
    return std::stoi(this->components.at(StandardizedComponent::LocalAuthListCtrlr)
                         .variables.at("ItemsPerMessage")
                         .attributes.at(AttributeEnum::Actual)
                         .value.value());
}

void ChargePointConfiguration::set_items_per_message(const int32_t& items_per_message) {
    this->components.at(StandardizedComponent::LocalAuthListCtrlr)
        .variables.at("ItemsPerMessage")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(std::to_string(items_per_message));
}

int32_t ChargePointConfiguration::get_bytes_per_message_set_variable_monitoring() {
    return std::stoi(this->components.at(StandardizedComponent::MonitoringCtrlr)
                         .variables.at("BytesPerMessage")
                         .attributes.at(AttributeEnum::Actual)
                         .value.value());
}

void ChargePointConfiguration::set_bytes_per_message_set_variable_monitoring(
    const int32_t& bytes_per_message_set_variable_monitoring) {
    this->components.at(StandardizedComponent::MonitoringCtrlr)
        .variables.at("BytesPerMessage")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(std::to_string(bytes_per_message_set_variable_monitoring));
}

int32_t ChargePointConfiguration::get_items_per_message_set_variable_monitoring() {
    return std::stoi(this->components.at(StandardizedComponent::MonitoringCtrlr)
                         .variables.at("ItemsPerMessage")
                         .attributes.at(AttributeEnum::Actual)
                         .value.value());
}

void ChargePointConfiguration::set_items_per_message_set_variable_monitoring(
    const int32_t& items_per_message_set_variable_monitoring) {
    this->components.at(StandardizedComponent::MonitoringCtrlr)
        .variables.at("ItemsPerMessage")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(std::to_string(items_per_message_set_variable_monitoring));
}

std::string ChargePointConfiguration::get_file_transfer_protocols() {
    return this->components.at(StandardizedComponent::OCPPCommCtrlr)
        .variables.at("FileTransferProtocols")
        .attributes.at(AttributeEnum::Actual)
        .value.value();
}

void ChargePointConfiguration::set_file_transfer_protocols(const std::string& file_transfer_protocols) {
    this->components.at(StandardizedComponent::OCPPCommCtrlr)
        .variables.at("FileTransferProtocols")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(file_transfer_protocols);
}

int32_t ChargePointConfiguration::get_message_timeout_default() {
    return std::stoi(this->components.at(StandardizedComponent::OCPPCommCtrlr)
                         .variables.at("MessageTimeout")
                         .attributes.at(AttributeEnum::Actual)
                         .value.value());
}

void ChargePointConfiguration::set_message_timeout_default(const int32_t& message_timeout_default) {
    this->components.at(StandardizedComponent::OCPPCommCtrlr)
        .variables.at("MessageTimeout")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(std::to_string(message_timeout_default));
}

int32_t ChargePointConfiguration::get_message_attempt_interval_transaction_event() {
    return std::stoi(this->components.at(StandardizedComponent::OCPPCommCtrlr)
                         .variables.at("MessageAttemptInterval")
                         .attributes.at(AttributeEnum::Actual)
                         .value.value());
}

void ChargePointConfiguration::set_message_attempt_interval_transaction_event(
    const int32_t& message_attempt_interval_transaction_event) {
    this->components.at(StandardizedComponent::OCPPCommCtrlr)
        .variables.at("MessageAttemptInterval")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(std::to_string(message_attempt_interval_transaction_event));
}

int32_t ChargePointConfiguration::get_message_attempts_transaction_event() {
    return std::stoi(this->components.at(StandardizedComponent::OCPPCommCtrlr)
                         .variables.at("MessageAttempts")
                         .attributes.at(AttributeEnum::Actual)
                         .value.value());
}

void ChargePointConfiguration::set_message_attempts_transaction_event(
    const int32_t& message_attempts_transaction_event) {
    this->components.at(StandardizedComponent::OCPPCommCtrlr)
        .variables.at("MessageAttempts")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(std::to_string(message_attempts_transaction_event));
}

std::string ChargePointConfiguration::get_network_configuration_priority() {
    return this->components.at(StandardizedComponent::OCPPCommCtrlr)
        .variables.at("NetworkConfigurationPriority")
        .attributes.at(AttributeEnum::Actual)
        .value.value();
}

void ChargePointConfiguration::set_network_configuration_priority(const std::string& network_configuration_priority) {
    this->components.at(StandardizedComponent::OCPPCommCtrlr)
        .variables.at("NetworkConfigurationPriority")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(network_configuration_priority);
}

int32_t ChargePointConfiguration::get_network_profile_connection_attempts() {
    return std::stoi(this->components.at(StandardizedComponent::OCPPCommCtrlr)
                         .variables.at("NetworkProfileConnectionAttempts")
                         .attributes.at(AttributeEnum::Actual)
                         .value.value());
}

void ChargePointConfiguration::set_network_profile_connection_attempts(
    const int32_t& network_profile_connection_attempts) {
    this->components.at(StandardizedComponent::OCPPCommCtrlr)
        .variables.at("NetworkProfileConnectionAttempts")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(std::to_string(network_profile_connection_attempts));
}

int32_t ChargePointConfiguration::get_offline_threshold() {
    return std::stoi(this->components.at(StandardizedComponent::OCPPCommCtrlr)
                         .variables.at("OfflineThreshold")
                         .attributes.at(AttributeEnum::Actual)
                         .value.value());
}

void ChargePointConfiguration::set_offline_threshold(const int32_t& offline_threshold) {
    this->components.at(StandardizedComponent::OCPPCommCtrlr)
        .variables.at("OfflineThreshold")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(std::to_string(offline_threshold));
}

int32_t ChargePointConfiguration::get_reset_retries() {
    return std::stoi(this->components.at(StandardizedComponent::OCPPCommCtrlr)
                         .variables.at("ResetRetries")
                         .attributes.at(AttributeEnum::Actual)
                         .value.value());
}

void ChargePointConfiguration::set_reset_retries(const int32_t& reset_retries) {
    this->components.at(StandardizedComponent::OCPPCommCtrlr)
        .variables.at("ResetRetries")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(std::to_string(reset_retries));
}

bool ChargePointConfiguration::get_unlock_on_evside_disconnect() {
    return ocpp::conversions::string_to_bool(this->components.at(StandardizedComponent::OCPPCommCtrlr)
                                                 .variables.at("UnlockOnEVSideDisconnect")
                                                 .attributes.at(AttributeEnum::Actual)
                                                 .value.value());
}

void ChargePointConfiguration::set_unlock_on_evside_disconnect(const bool& unlock_on_evside_disconnect) {
    this->components.at(StandardizedComponent::OCPPCommCtrlr)
        .variables.at("UnlockOnEVSideDisconnect")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(ocpp::conversions::bool_to_string(unlock_on_evside_disconnect));
}

int32_t ChargePointConfiguration::get_sampled_data_ctrlr_tx_ended_interval() {
    return std::stoi(this->components.at(StandardizedComponent::SampledDataCtrlr)
                         .variables.at("TxEndedInterval")
                         .attributes.at(AttributeEnum::Actual)
                         .value.value());
}

void ChargePointConfiguration::set_sampled_data_ctrlr_tx_ended_interval(
    const int32_t& sampled_data_ctrlr_tx_ended_interval) {
    this->components.at(StandardizedComponent::SampledDataCtrlr)
        .variables.at("TxEndedInterval")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(std::to_string(sampled_data_ctrlr_tx_ended_interval));
}

std::string ChargePointConfiguration::get_sampled_data_ctrlr_tx_ended_measurands() {
    return this->components.at(StandardizedComponent::SampledDataCtrlr)
        .variables.at("TxEndedMeasurands")
        .attributes.at(AttributeEnum::Actual)
        .value.value();
}

void ChargePointConfiguration::set_sampled_data_ctrlr_tx_ended_measurands(
    const std::string& sampled_data_ctrlr_tx_ended_measurands) {
    this->components.at(StandardizedComponent::SampledDataCtrlr)
        .variables.at("TxEndedMeasurands")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(sampled_data_ctrlr_tx_ended_measurands);
}

std::string ChargePointConfiguration::get_tx_started_measurands() {
    return this->components.at(StandardizedComponent::SampledDataCtrlr)
        .variables.at("TxStartedMeasurands")
        .attributes.at(AttributeEnum::Actual)
        .value.value();
}

void ChargePointConfiguration::set_tx_started_measurands(const std::string& tx_started_measurands) {
    this->components.at(StandardizedComponent::SampledDataCtrlr)
        .variables.at("TxStartedMeasurands")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(tx_started_measurands);
}

int32_t ChargePointConfiguration::get_tx_updated_interval() {
    return std::stoi(this->components.at(StandardizedComponent::SampledDataCtrlr)
                         .variables.at("TxUpdatedInterval")
                         .attributes.at(AttributeEnum::Actual)
                         .value.value());
}

void ChargePointConfiguration::set_tx_updated_interval(const int32_t& tx_updated_interval) {
    this->components.at(StandardizedComponent::SampledDataCtrlr)
        .variables.at("TxUpdatedInterval")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(std::to_string(tx_updated_interval));
}

std::string ChargePointConfiguration::get_tx_updated_measurands() {
    return this->components.at(StandardizedComponent::SampledDataCtrlr)
        .variables.at("TxUpdatedMeasurands")
        .attributes.at(AttributeEnum::Actual)
        .value.value();
}

void ChargePointConfiguration::set_tx_updated_measurands(const std::string& tx_updated_measurands) {
    this->components.at(StandardizedComponent::SampledDataCtrlr)
        .variables.at("TxUpdatedMeasurands")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(tx_updated_measurands);
}

int32_t ChargePointConfiguration::get_certificate_entries() {
    return std::stoi(this->components.at(StandardizedComponent::SecurityCtrlr)
                         .variables.at("CertificateEntries")
                         .attributes.at(AttributeEnum::Actual)
                         .value.value());
}

void ChargePointConfiguration::set_certificate_entries(const int32_t& certificate_entries) {
    this->components.at(StandardizedComponent::SecurityCtrlr)
        .variables.at("CertificateEntries")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(std::to_string(certificate_entries));
}

std::string ChargePointConfiguration::get_security_ctrlr_organization_name() {
    return this->components.at(StandardizedComponent::SecurityCtrlr)
        .variables.at("OrganizationName")
        .attributes.at(AttributeEnum::Actual)
        .value.value();
}

void ChargePointConfiguration::set_security_ctrlr_organization_name(
    const std::string& security_ctrlr_organization_name) {
    this->components.at(StandardizedComponent::SecurityCtrlr)
        .variables.at("OrganizationName")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(security_ctrlr_organization_name);
}

int32_t ChargePointConfiguration::get_security_profile() {
    return std::stoi(this->components.at(StandardizedComponent::SecurityCtrlr)
                         .variables.at("SecurityProfile")
                         .attributes.at(AttributeEnum::Actual)
                         .value.value());
}

void ChargePointConfiguration::set_security_profile(const int32_t& security_profile) {
    this->components.at(StandardizedComponent::SecurityCtrlr)
        .variables.at("SecurityProfile")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(std::to_string(security_profile));
}

int32_t ChargePointConfiguration::get_entries_charging_profiles() {
    return std::stoi(this->components.at(StandardizedComponent::SmartChargingCtrlr)
                         .variables.at("Entries")
                         .attributes.at(AttributeEnum::Actual)
                         .value.value());
}

void ChargePointConfiguration::set_entries_charging_profiles(const int32_t& entries_charging_profiles) {
    this->components.at(StandardizedComponent::SmartChargingCtrlr)
        .variables.at("Entries")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(std::to_string(entries_charging_profiles));
}

double ChargePointConfiguration::get_limit_change_significance() {
    return std::stod(this->components.at(StandardizedComponent::SmartChargingCtrlr)
                         .variables.at("LimitChangeSignificance")
                         .attributes.at(AttributeEnum::Actual)
                         .value.value());
}

void ChargePointConfiguration::set_limit_change_significance(const double& limit_change_significance) {
    this->components.at(StandardizedComponent::SmartChargingCtrlr)
        .variables.at("LimitChangeSignificance")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(ocpp::conversions::double_to_string(limit_change_significance));
}

int32_t ChargePointConfiguration::get_periods_per_schedule() {
    return std::stoi(this->components.at(StandardizedComponent::SmartChargingCtrlr)
                         .variables.at("PeriodsPerSchedule")
                         .attributes.at(AttributeEnum::Actual)
                         .value.value());
}

void ChargePointConfiguration::set_periods_per_schedule(const int32_t& periods_per_schedule) {
    this->components.at(StandardizedComponent::SmartChargingCtrlr)
        .variables.at("PeriodsPerSchedule")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(std::to_string(periods_per_schedule));
}

int32_t ChargePointConfiguration::get_profile_stack_level() {
    return std::stoi(this->components.at(StandardizedComponent::SmartChargingCtrlr)
                         .variables.at("ProfileStackLevel")
                         .attributes.at(AttributeEnum::Actual)
                         .value.value());
}

void ChargePointConfiguration::set_profile_stack_level(const int32_t& profile_stack_level) {
    this->components.at(StandardizedComponent::SmartChargingCtrlr)
        .variables.at("ProfileStackLevel")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(std::to_string(profile_stack_level));
}

std::string ChargePointConfiguration::get_rate_unit() {
    return this->components.at(StandardizedComponent::SmartChargingCtrlr)
        .variables.at("RateUnit")
        .attributes.at(AttributeEnum::Actual)
        .value.value();
}

void ChargePointConfiguration::set_rate_unit(const std::string& rate_unit) {
    this->components.at(StandardizedComponent::SmartChargingCtrlr)
        .variables.at("RateUnit")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(rate_unit);
}

std::string ChargePointConfiguration::get_currency() {
    return this->components.at(StandardizedComponent::TariffCostCtrlr)
        .variables.at("Currency")
        .attributes.at(AttributeEnum::Actual)
        .value.value();
}

void ChargePointConfiguration::set_currency(const std::string& currency) {
    this->components.at(StandardizedComponent::TariffCostCtrlr)
        .variables.at("Currency")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(currency);
}

std::string ChargePointConfiguration::get_tariff_fallback_message() {
    return this->components.at(StandardizedComponent::TariffCostCtrlr)
        .variables.at("TariffFallbackMessage")
        .attributes.at(AttributeEnum::Actual)
        .value.value();
}

void ChargePointConfiguration::set_tariff_fallback_message(const std::string& tariff_fallback_message) {
    this->components.at(StandardizedComponent::TariffCostCtrlr)
        .variables.at("TariffFallbackMessage")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(tariff_fallback_message);
}

std::string ChargePointConfiguration::get_total_cost_fallback_message() {
    return this->components.at(StandardizedComponent::TariffCostCtrlr)
        .variables.at("TotalCostFallbackMessage")
        .attributes.at(AttributeEnum::Actual)
        .value.value();
}

void ChargePointConfiguration::set_total_cost_fallback_message(const std::string& total_cost_fallback_message) {
    this->components.at(StandardizedComponent::TariffCostCtrlr)
        .variables.at("TotalCostFallbackMessage")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(total_cost_fallback_message);
}

int32_t ChargePointConfiguration::get_evconnection_time_out() {
    return std::stoi(this->components.at(StandardizedComponent::TxCtrlr)
                         .variables.at("EVConnectionTimeOut")
                         .attributes.at(AttributeEnum::Actual)
                         .value.value());
}

void ChargePointConfiguration::set_evconnection_time_out(const int32_t& evconnection_time_out) {
    this->components.at(StandardizedComponent::TxCtrlr)
        .variables.at("EVConnectionTimeOut")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(std::to_string(evconnection_time_out));
}

bool ChargePointConfiguration::get_stop_tx_on_evside_disconnect() {
    return ocpp::conversions::string_to_bool(this->components.at(StandardizedComponent::TxCtrlr)
                                                 .variables.at("StopTxOnEVSideDisconnect")
                                                 .attributes.at(AttributeEnum::Actual)
                                                 .value.value());
}

void ChargePointConfiguration::set_stop_tx_on_evside_disconnect(const bool& stop_tx_on_evside_disconnect) {
    this->components.at(StandardizedComponent::TxCtrlr)
        .variables.at("StopTxOnEVSideDisconnect")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(ocpp::conversions::bool_to_string(stop_tx_on_evside_disconnect));
}

bool ChargePointConfiguration::get_stop_tx_on_invalid_id() {
    return ocpp::conversions::string_to_bool(this->components.at(StandardizedComponent::TxCtrlr)
                                                 .variables.at("StopTxOnInvalidId")
                                                 .attributes.at(AttributeEnum::Actual)
                                                 .value.value());
}

void ChargePointConfiguration::set_stop_tx_on_invalid_id(const bool& stop_tx_on_invalid_id) {
    this->components.at(StandardizedComponent::TxCtrlr)
        .variables.at("StopTxOnInvalidId")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(ocpp::conversions::bool_to_string(stop_tx_on_invalid_id));
}

std::string ChargePointConfiguration::get_tx_start_point() {
    return this->components.at(StandardizedComponent::TxCtrlr)
        .variables.at("TxStartPoint")
        .attributes.at(AttributeEnum::Actual)
        .value.value();
}

void ChargePointConfiguration::set_tx_start_point(const std::string& tx_start_point) {
    this->components.at(StandardizedComponent::TxCtrlr)
        .variables.at("TxStartPoint")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(tx_start_point);
}

std::string ChargePointConfiguration::get_tx_stop_point() {
    return this->components.at(StandardizedComponent::TxCtrlr)
        .variables.at("TxStopPoint")
        .attributes.at(AttributeEnum::Actual)
        .value.value();
}

void ChargePointConfiguration::set_tx_stop_point(const std::string& tx_stop_point) {
    this->components.at(StandardizedComponent::TxCtrlr)
        .variables.at("TxStopPoint")
        .attributes.at(AttributeEnum::Actual)
        .value.emplace(tx_stop_point);
}

} // namespace v201
} // namespace ocpp
