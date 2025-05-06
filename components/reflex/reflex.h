#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/uart/uart.h"

#define REFLEX_LOOP_WAIT 3
#define REFLEX_SERIAL_BUFFER_LEN 47

#define REFLEX_MSG_MEASUREMENTS 0x14
#define REFLEX_MSG_TYPE 0x22
#define REFLEX_MSG_EXTPARAMETERS 0x23

namespace esphome {
namespace reflex {

class ReflexComponent : public PollingComponent, public uart::UARTDevice {
  public:

    void setup() override;
    void loop() override;
    void update() override;
    void dump_config() override;
    
    void dump_data();
    void restore_msb(char *buffer, int offset, int size);
    void send_master(uint8_t address, uint8_t command);

    struct reflex_measurement{
      bool updated;
      uint16_t pressure;
      uint16_t level;
      bool r_pump2_on;
      bool r_pump1_on;
      bool r_overflow2_open;
      bool r_overflow1_open;
      bool r_makeup_open;
      bool r_minlevel;
      bool r_error;
      bool d_pump1;
      bool d_pump2;
      bool d_lackofwater;
      bool d_watermeter;
      bool d_softstart;
      bool e2_mainboard;
      bool e2_digitalv;
      bool e2_analogv;
      bool e2_valve1;
      bool e2_valve2;
      bool e2_jpressure;
      bool e2_jlevel;
      bool e2_dryrun;
      bool e2_lackofwater3;
      bool e2_lackofwater4;
      bool e2_lfsensor;
      bool e1_extensionmodule;
      bool e1_eeprom;
      bool e1_undervoltage;
      bool e1_minpressure;
      bool e1_lackofwater1;
      bool e1_pump1;
      bool e1_compressor1;
      bool e1_pump2;
      bool e1_compressor2;
      bool e1_pressuresensor;
      bool e1_levelsensor;
      bool e1_pressuresensorpipe;
      bool e1_sto4h;
      bool e1_lackofwater2;
      bool e1_eeprom2;
      bool w2_battery;
      bool w2_descalechange;
      bool w2_datalogger;
      bool w2_busmodule;
      bool w2_stop4h;
      bool w2_conductivity;
      bool w1_maxlevel;
      bool w1_pumpruntime;
      bool w1_makeuptime;
      bool w1_maekupcycles;
      bool w1_maxpressure;
      bool w1_makeupvolume;
      bool w1_expulsiontime;
      bool w1_filltime;
      bool w1_fillvolume;
      bool w1_makeupvalve;
      bool w1_voltage;
      bool w1_zerolevel;
      bool w1_parameter;
      bool w1_maxmakeupvolume;
      bool w1_maintenance;
      long hours_pump1;
      long hours_pump2;
      long watermeter;
      std::string s_modus;
      bool s_manual;
      bool s_stop;
      bool s_auto;
      bool s_pump1;
      bool s_pump2;
      bool s_error;
      bool s_waterlevel;
      bool s_degas;
      bool s_makeupvalve;
      bool s_overflow1;
      bool s_overflow2;
      bool s_pump1_on;
      bool s_pump2_on;
      uint8_t p_valve1;
      uint8_t p_valve2;
      uint8_t type;
      std::string type_name;
      bool levelcontrol;
      uint8_t conductivity;
    };

    struct reflex_type{
      bool updated;
      char serial[15];
      std::string version;
      std::string controller;
      std::string type;
      bool levelcontrol;
    };

    struct reflex_parameter{
      bool updated;
      uint16_t pressure_p0;
      uint16_t pressure_max;
      uint16_t conductivity_max;
      uint16_t pressure_nsp;
      uint16_t pressures_sv;
      uint16_t pressure_pf;
      uint8_t waterlevel_on;
      uint8_t waterlevel_off;
      uint8_t fill_on;
      uint8_t fill_off;
      long max_fillvolume;
      uint8_t max_fillcycles;
      uint8_t max_filltime;
      uint8_t max_fillimpulse;
      bool s_customer;
      bool s_service;
      bool s_ro;
      bool s_parameter;
      uint16_t container_size;
      uint16_t container_weight;
      uint16_t container_differenz;
      uint8_t maintenance;
      uint8_t highwater;
      uint8_t descaler;
      uint16_t descaler_remaining;
      std::string programm;
    };

    void set_typeserial_sensor(text_sensor::TextSensor *s) { sensor_typeserial = s; }
    void set_typeversion_sensor(text_sensor::TextSensor *s) { sensor_typeversion = s; }
    void set_typecontroller_sensor(text_sensor::TextSensor *s) { sensor_typecontroller = s; }
    void set_typetype_sensor(text_sensor::TextSensor *s) { sensor_typetype = s; }
    void set_typelevelcontrol_sensor(binary_sensor::BinarySensor *s) { sensor_typelevelcontrol = s; }

    void set_parapressurep0_sensor (sensor::Sensor *s) { sensor_parapressurep0 = s; }
    void set_parapressuremax_sensor (sensor::Sensor *s) { sensor_parapressuremax = s; }
    void set_paraconductivitymax_sensor (sensor::Sensor *s) { sensor_paraconductivitymax = s; }
    void set_parapressurensp_sensor (sensor::Sensor *s) { sensor_parapressurensp = s; }
    void set_parapressuressv_sensor (sensor::Sensor *s) { sensor_parapressuressv = s; }
    void set_parapressurepf_sensor (sensor::Sensor *s) { sensor_parapressurepf = s; }
    void set_parawaterlevelon_sensor (sensor::Sensor *s) { sensor_parawaterlevelon = s; }
    void set_parawaterleveloff_sensor (sensor::Sensor *s) { sensor_parawaterleveloff = s; }
    void set_parafillon_sensor (sensor::Sensor *s) { sensor_parafillon = s; }
    void set_parafilloff_sensor (sensor::Sensor *s) { sensor_parafilloff = s; }
    void set_paramaxfillvolume_sensor (sensor::Sensor *s) { sensor_paramaxfillvolume = s; }
    void set_paramaxfillcycles_sensor (sensor::Sensor *s) { sensor_paramaxfillcycles = s; }
    void set_paramaxfilltime_sensor (sensor::Sensor *s) { sensor_paramaxfilltime = s; }
    void set_paramaxfillimpulse_sensor (sensor::Sensor *s) { sensor_paramaxfillimpulse = s; }
    void set_parascustomer_sensor (binary_sensor::BinarySensor *s) { sensor_parascustomer = s; }
    void set_parasservice_sensor (binary_sensor::BinarySensor *s) { sensor_parasservice = s; }
    void set_parasro_sensor (binary_sensor::BinarySensor *s) { sensor_parasro = s; }
    void set_parasparameter_sensor (binary_sensor::BinarySensor *s) { sensor_parasparameter = s; }
    void set_paracontainersize_sensor (sensor::Sensor *s) { sensor_paracontainersize = s; }
    void set_paracontainerweight_sensor (sensor::Sensor *s) { sensor_paracontainerweight = s; }
    void set_paracontainerdifferenz_sensor (sensor::Sensor *s) { sensor_paracontainerdifferenz = s; }
    void set_paramaintenance_sensor (sensor::Sensor *s) { sensor_paramaintenance = s; }
    void set_parahighwater_sensor (sensor::Sensor *s) { sensor_parahighwater = s; }
    void set_paradescaler_sensor (sensor::Sensor *s) { sensor_paradescaler = s; }
    void set_paradescalerremaining_sensor (sensor::Sensor *s) { sensor_paradescalerremaining = s; }
    void set_paraprogramm_sensor (text_sensor::TextSensor *s) { sensor_paraprogramm = s; }

    void set_mespressure_sensor (sensor::Sensor *s) { sensor_mespressure = s; }
    void set_meslevel_sensor (sensor::Sensor *s) { sensor_meslevel = s; }
    void set_meshourspump1_sensor (sensor::Sensor *s) { sensor_meshourspump1 = s; }
    void set_meshourspump2_sensor (sensor::Sensor *s) { sensor_meshourspump2 = s; }
    void set_meswatermeter_sensor (sensor::Sensor *s) { sensor_meswatermeter = s; }
    void set_mespvalve1_sensor (sensor::Sensor *s) { sensor_mespvalve1 = s; }
    void set_mespvalve2_sensor (sensor::Sensor *s) { sensor_mespvalve2 = s; }
    void set_mesconductivity_sensor (sensor::Sensor *s) { sensor_mesconductivity = s; }
    void set_messmodus_sensor (text_sensor::TextSensor *s) { sensor_messmodus = s; }
    void set_mesrpump2on_sensor (binary_sensor::BinarySensor *s) { sensor_mesrpump2on = s; }
    void set_mesrpump1on_sensor (binary_sensor::BinarySensor *s) { sensor_mesrpump1on = s; }
    void set_mesroverflow2open_sensor (binary_sensor::BinarySensor *s) { sensor_mesroverflow2open = s; }
    void set_mesroverflow1open_sensor (binary_sensor::BinarySensor *s) { sensor_mesroverflow1open = s; }
    void set_mesrmakeupopen_sensor (binary_sensor::BinarySensor *s) { sensor_mesrmakeupopen = s; }
    void set_mesrminlevel_sensor (binary_sensor::BinarySensor *s) { sensor_mesrminlevel = s; }
    void set_mesrerror_sensor (binary_sensor::BinarySensor *s) { sensor_mesrerror = s; }
    void set_mesdpump1_sensor (binary_sensor::BinarySensor *s) { sensor_mesdpump1 = s; }
    void set_mesdpump2_sensor (binary_sensor::BinarySensor *s) { sensor_mesdpump2 = s; }
    void set_mesdlackofwater_sensor (binary_sensor::BinarySensor *s) { sensor_mesdlackofwater = s; }
    void set_mesdwatermeter_sensor (binary_sensor::BinarySensor *s) { sensor_mesdwatermeter = s; }
    void set_mesdsoftstart_sensor (binary_sensor::BinarySensor *s) { sensor_mesdsoftstart = s; }
    void set_mese2mainboard_sensor (binary_sensor::BinarySensor *s) { sensor_mese2mainboard = s; }
    void set_mese2digitalv_sensor (binary_sensor::BinarySensor *s) { sensor_mese2digitalv = s; }
    void set_mese2analogv_sensor (binary_sensor::BinarySensor *s) { sensor_mese2analogv = s; }
    void set_mese2valve1_sensor (binary_sensor::BinarySensor *s) { sensor_mese2valve1 = s; }
    void set_mese2valve2_sensor (binary_sensor::BinarySensor *s) { sensor_mese2valve2 = s; }
    void set_mese2jpressure_sensor (binary_sensor::BinarySensor *s) { sensor_mese2jpressure = s; }
    void set_mese2jlevel_sensor (binary_sensor::BinarySensor *s) { sensor_mese2jlevel = s; }
    void set_mese2dryrun_sensor (binary_sensor::BinarySensor *s) { sensor_mese2dryrun = s; }
    void set_mese2lackofwater3_sensor (binary_sensor::BinarySensor *s) { sensor_mese2lackofwater3 = s; }
    void set_mese2lackofwater4_sensor (binary_sensor::BinarySensor *s) { sensor_mese2lackofwater4 = s; }
    void set_mese2lfsensor_sensor (binary_sensor::BinarySensor *s) { sensor_mese2lfsensor = s; }
    void set_mese1extensionmodule_sensor (binary_sensor::BinarySensor *s) { sensor_mese1extensionmodule = s; }
    void set_mese1eeprom_sensor (binary_sensor::BinarySensor *s) { sensor_mese1eeprom = s; }
    void set_mese1undervoltage_sensor (binary_sensor::BinarySensor *s) { sensor_mese1undervoltage = s; }
    void set_mese1minpressure_sensor (binary_sensor::BinarySensor *s) { sensor_mese1minpressure = s; }
    void set_mese1lackofwater1_sensor (binary_sensor::BinarySensor *s) { sensor_mese1lackofwater1 = s; }
    void set_mese1pump1_sensor (binary_sensor::BinarySensor *s) { sensor_mese1pump1 = s; }
    void set_mese1compressor1_sensor (binary_sensor::BinarySensor *s) { sensor_mese1compressor1 = s; }
    void set_mese1pump2_sensor (binary_sensor::BinarySensor *s) { sensor_mese1pump2 = s; }
    void set_mese1compressor2_sensor (binary_sensor::BinarySensor *s) { sensor_mese1compressor2 = s; }
    void set_mese1pressuresensor_sensor (binary_sensor::BinarySensor *s) { sensor_mese1pressuresensor = s; }
    void set_mese1levelsensor_sensor (binary_sensor::BinarySensor *s) { sensor_mese1levelsensor = s; }
    void set_mese1pressuresensorpipe_sensor (binary_sensor::BinarySensor *s) { sensor_mese1pressuresensorpipe = s; }
    void set_mese1sto4h_sensor (binary_sensor::BinarySensor *s) { sensor_mese1sto4h = s; }
    void set_mese1lackofwater2_sensor (binary_sensor::BinarySensor *s) { sensor_mese1lackofwater2 = s; }
    void set_mese1eeprom2_sensor (binary_sensor::BinarySensor *s) { sensor_mese1eeprom2 = s; }
    void set_mesw2battery_sensor (binary_sensor::BinarySensor *s) { sensor_mesw2battery = s; }
    void set_mesw2descalechange_sensor (binary_sensor::BinarySensor *s) { sensor_mesw2descalechange = s; }
    void set_mesw2datalogger_sensor (binary_sensor::BinarySensor *s) { sensor_mesw2datalogger = s; }
    void set_mesw2busmodule_sensor (binary_sensor::BinarySensor *s) { sensor_mesw2busmodule = s; }
    void set_mesw2stop4h_sensor (binary_sensor::BinarySensor *s) { sensor_mesw2stop4h = s; }
    void set_mesw2conductivity_sensor (binary_sensor::BinarySensor *s) { sensor_mesw2conductivity = s; }
    void set_mesw1maxlevel_sensor (binary_sensor::BinarySensor *s) { sensor_mesw1maxlevel = s; }
    void set_mesw1pumpruntime_sensor (binary_sensor::BinarySensor *s) { sensor_mesw1pumpruntime = s; }
    void set_mesw1makeuptime_sensor (binary_sensor::BinarySensor *s) { sensor_mesw1makeuptime = s; }
    void set_mesw1maekupcycles_sensor (binary_sensor::BinarySensor *s) { sensor_mesw1maekupcycles = s; }
    void set_mesw1maxpressure_sensor (binary_sensor::BinarySensor *s) { sensor_mesw1maxpressure = s; }
    void set_mesw1makeupvolume_sensor (binary_sensor::BinarySensor *s) { sensor_mesw1makeupvolume = s; }
    void set_mesw1expulsiontime_sensor (binary_sensor::BinarySensor *s) { sensor_mesw1expulsiontime = s; }
    void set_mesw1filltime_sensor (binary_sensor::BinarySensor *s) { sensor_mesw1filltime = s; }
    void set_mesw1fillvolume_sensor (binary_sensor::BinarySensor *s) { sensor_mesw1fillvolume = s; }
    void set_mesw1makeupvalve_sensor (binary_sensor::BinarySensor *s) { sensor_mesw1makeupvalve = s; }
    void set_mesw1voltage_sensor (binary_sensor::BinarySensor *s) { sensor_mesw1voltage = s; }
    void set_mesw1zerolevel_sensor (binary_sensor::BinarySensor *s) { sensor_mesw1zerolevel = s; }
    void set_mesw1parameter_sensor (binary_sensor::BinarySensor *s) { sensor_mesw1parameter = s; }
    void set_mesw1maxmakeupvolume_sensor (binary_sensor::BinarySensor *s) { sensor_mesw1maxmakeupvolume = s; }
    void set_mesw1maintenance_sensor (binary_sensor::BinarySensor *s) { sensor_mesw1maintenance = s; }
    void set_messmanual_sensor (binary_sensor::BinarySensor *s) { sensor_messmanual = s; }
    void set_messstop_sensor (binary_sensor::BinarySensor *s) { sensor_messstop = s; }
    void set_messauto_sensor (binary_sensor::BinarySensor *s) { sensor_messauto = s; }
    void set_messpump1_sensor (binary_sensor::BinarySensor *s) { sensor_messpump1 = s; }
    void set_messpump2_sensor (binary_sensor::BinarySensor *s) { sensor_messpump2 = s; }
    void set_messerror_sensor (binary_sensor::BinarySensor *s) { sensor_messerror = s; }
    void set_messwaterlevel_sensor (binary_sensor::BinarySensor *s) { sensor_messwaterlevel = s; }
    void set_messdegas_sensor (binary_sensor::BinarySensor *s) { sensor_messdegas = s; }
    void set_messmakeupvalve_sensor (binary_sensor::BinarySensor *s) { sensor_messmakeupvalve = s; }
    void set_messoverflow1_sensor (binary_sensor::BinarySensor *s) { sensor_messoverflow1 = s; }
    void set_messoverflow2_sensor (binary_sensor::BinarySensor *s) { sensor_messoverflow2 = s; }
    void set_messpump1on_sensor (binary_sensor::BinarySensor *s) { sensor_messpump1on = s; }
    void set_messpump2on_sensor (binary_sensor::BinarySensor *s) { sensor_messpump2on = s; }

    protected:

    text_sensor::TextSensor *sensor_typeserial;
    text_sensor::TextSensor *sensor_typeversion;
    text_sensor::TextSensor *sensor_typecontroller;
    text_sensor::TextSensor *sensor_typetype;
    binary_sensor::BinarySensor *sensor_typelevelcontrol;

    sensor::Sensor *sensor_parapressurep0;
    sensor::Sensor *sensor_parapressuremax;
    sensor::Sensor *sensor_paraconductivitymax;
    sensor::Sensor *sensor_parapressurensp;
    sensor::Sensor *sensor_parapressuressv;
    sensor::Sensor *sensor_parapressurepf;
    sensor::Sensor *sensor_parawaterlevelon;
    sensor::Sensor *sensor_parawaterleveloff;
    sensor::Sensor *sensor_parafillon;
    sensor::Sensor *sensor_parafilloff;
    sensor::Sensor *sensor_paramaxfillvolume;
    sensor::Sensor *sensor_paramaxfillcycles;
    sensor::Sensor *sensor_paramaxfilltime;
    sensor::Sensor *sensor_paramaxfillimpulse;
    binary_sensor::BinarySensor *sensor_parascustomer;
    binary_sensor::BinarySensor *sensor_parasservice;
    binary_sensor::BinarySensor *sensor_parasro;
    binary_sensor::BinarySensor *sensor_parasparameter;
    sensor::Sensor *sensor_paracontainersize;
    sensor::Sensor *sensor_paracontainerweight;
    sensor::Sensor *sensor_paracontainerdifferenz;
    sensor::Sensor *sensor_paramaintenance;
    sensor::Sensor *sensor_parahighwater;
    sensor::Sensor *sensor_paradescaler;
    sensor::Sensor *sensor_paradescalerremaining;
    text_sensor::TextSensor *sensor_paraprogramm;

    sensor::Sensor *sensor_mespressure;
    sensor::Sensor *sensor_meslevel;
    sensor::Sensor *sensor_meshourspump1;
    sensor::Sensor *sensor_meshourspump2;
    sensor::Sensor *sensor_meswatermeter;
    sensor::Sensor *sensor_mespvalve1;
    sensor::Sensor *sensor_mespvalve2;
    sensor::Sensor *sensor_mesconductivity;
    text_sensor::TextSensor *sensor_messmodus;
    binary_sensor::BinarySensor *sensor_mesrpump2on;
    binary_sensor::BinarySensor *sensor_mesrpump1on;
    binary_sensor::BinarySensor *sensor_mesroverflow2open;
    binary_sensor::BinarySensor *sensor_mesroverflow1open;
    binary_sensor::BinarySensor *sensor_mesrmakeupopen;
    binary_sensor::BinarySensor *sensor_mesrminlevel;
    binary_sensor::BinarySensor *sensor_mesrerror;
    binary_sensor::BinarySensor *sensor_mesdpump1;
    binary_sensor::BinarySensor *sensor_mesdpump2;
    binary_sensor::BinarySensor *sensor_mesdlackofwater;
    binary_sensor::BinarySensor *sensor_mesdwatermeter;
    binary_sensor::BinarySensor *sensor_mesdsoftstart;
    binary_sensor::BinarySensor *sensor_mese2mainboard;
    binary_sensor::BinarySensor *sensor_mese2digitalv;
    binary_sensor::BinarySensor *sensor_mese2analogv;
    binary_sensor::BinarySensor *sensor_mese2valve1;
    binary_sensor::BinarySensor *sensor_mese2valve2;
    binary_sensor::BinarySensor *sensor_mese2jpressure;
    binary_sensor::BinarySensor *sensor_mese2jlevel;
    binary_sensor::BinarySensor *sensor_mese2dryrun;
    binary_sensor::BinarySensor *sensor_mese2lackofwater3;
    binary_sensor::BinarySensor *sensor_mese2lackofwater4;
    binary_sensor::BinarySensor *sensor_mese2lfsensor;
    binary_sensor::BinarySensor *sensor_mese1extensionmodule;
    binary_sensor::BinarySensor *sensor_mese1eeprom;
    binary_sensor::BinarySensor *sensor_mese1undervoltage;
    binary_sensor::BinarySensor *sensor_mese1minpressure;
    binary_sensor::BinarySensor *sensor_mese1lackofwater1;
    binary_sensor::BinarySensor *sensor_mese1pump1;
    binary_sensor::BinarySensor *sensor_mese1compressor1;
    binary_sensor::BinarySensor *sensor_mese1pump2;
    binary_sensor::BinarySensor *sensor_mese1compressor2;
    binary_sensor::BinarySensor *sensor_mese1pressuresensor;
    binary_sensor::BinarySensor *sensor_mese1levelsensor;
    binary_sensor::BinarySensor *sensor_mese1pressuresensorpipe;
    binary_sensor::BinarySensor *sensor_mese1sto4h;
    binary_sensor::BinarySensor *sensor_mese1lackofwater2;
    binary_sensor::BinarySensor *sensor_mese1eeprom2;
    binary_sensor::BinarySensor *sensor_mesw2battery;
    binary_sensor::BinarySensor *sensor_mesw2descalechange;
    binary_sensor::BinarySensor *sensor_mesw2datalogger;
    binary_sensor::BinarySensor *sensor_mesw2busmodule;
    binary_sensor::BinarySensor *sensor_mesw2stop4h;
    binary_sensor::BinarySensor *sensor_mesw2conductivity;
    binary_sensor::BinarySensor *sensor_mesw1maxlevel;
    binary_sensor::BinarySensor *sensor_mesw1pumpruntime;
    binary_sensor::BinarySensor *sensor_mesw1makeuptime;
    binary_sensor::BinarySensor *sensor_mesw1maekupcycles;
    binary_sensor::BinarySensor *sensor_mesw1maxpressure;
    binary_sensor::BinarySensor *sensor_mesw1makeupvolume;
    binary_sensor::BinarySensor *sensor_mesw1expulsiontime;
    binary_sensor::BinarySensor *sensor_mesw1filltime;
    binary_sensor::BinarySensor *sensor_mesw1fillvolume;
    binary_sensor::BinarySensor *sensor_mesw1makeupvalve;
    binary_sensor::BinarySensor *sensor_mesw1voltage;
    binary_sensor::BinarySensor *sensor_mesw1zerolevel;
    binary_sensor::BinarySensor *sensor_mesw1parameter;
    binary_sensor::BinarySensor *sensor_mesw1maxmakeupvolume;
    binary_sensor::BinarySensor *sensor_mesw1maintenance;
    binary_sensor::BinarySensor *sensor_messmanual;
    binary_sensor::BinarySensor *sensor_messstop;
    binary_sensor::BinarySensor *sensor_messauto;
    binary_sensor::BinarySensor *sensor_messpump1;
    binary_sensor::BinarySensor *sensor_messpump2;
    binary_sensor::BinarySensor *sensor_messerror;
    binary_sensor::BinarySensor *sensor_messwaterlevel;
    binary_sensor::BinarySensor *sensor_messdegas;
    binary_sensor::BinarySensor *sensor_messmakeupvalve;
    binary_sensor::BinarySensor *sensor_messoverflow1;
    binary_sensor::BinarySensor *sensor_messoverflow2;
    binary_sensor::BinarySensor *sensor_messpump1on;
    binary_sensor::BinarySensor *sensor_messpump2on;

    reflex_measurement state_measurment = {0};
    reflex_type state_type = {0};
    reflex_parameter state_parameter = {0};
};
} // namespace reflex_s5
} // namespace esphome

