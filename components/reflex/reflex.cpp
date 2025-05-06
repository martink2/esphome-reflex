#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/uart/uart.h"
#include "esphome/core/log.h"
#include "reflex.h"

namespace esphome {
namespace reflex {

static const char *TAG = "reflex";

void ReflexComponent::setup() {
  // nothing to do here
}

void ReflexComponent::send_master(uint8_t address, uint8_t command) {
  ESP_LOGV(TAG, "send_master(%d): %X", address, command );
  static uint8_t telegram[4] = {0};
  static uint16_t cs = 0;
  
  telegram[0] = address | 0b11100000;
  telegram[1] = command;
  cs = ( telegram[0] + telegram[1] ) & 0b0001111111111;
  telegram[2] = cs & 0b0000000001111111;
  telegram[3] = ( ( ( cs >> 7 ) & 0b0000000000111111 ) | 0b10000000 );
  this->write_array(telegram, 4);
}

void ReflexComponent::loop() {

  static char buffer[REFLEX_SERIAL_BUFFER_LEN] = {0};
  static uint8_t index = 0;
  static uint8_t loopwait = 0;
  static uint16_t cs_msg = 0;
  static uint16_t cs1_msg = 0;
  static uint16_t cs2_msg = 0;

  while (available()) {
    buffer[index] = read();
    index++;
    index%=REFLEX_SERIAL_BUFFER_LEN;
    loopwait = 0;
  }

  if (index > 0) {
    loopwait++;
  }
  
  if (loopwait > REFLEX_LOOP_WAIT) { // some time has passed without receiving another character. this should be the end of a message.

    if ( (buffer[0] & 0b11100000) == 0xc0) { // message starts with the right preamble
      cs_msg = 0;
      for (int i = 0; i < (index - 3); i++) {
        cs_msg += buffer[i];
      }

      cs_msg = cs_msg & 0b0001111111111111;
      cs1_msg = cs_msg & 0b0000000001111111;
      cs2_msg = ( ( cs_msg >> 7 ) & 0b0000000000111111 ) | 0b10000000;

      if ( cs2_msg == buffer[index - 1] ) { // message ends with the right end character
        if ( cs1_msg == buffer[index - 2] ) {

          switch(buffer[1]) {
            case REFLEX_MSG_MEASUREMENTS:
              this->restore_msb(buffer, 2, 7);
              this->restore_msb(buffer, 10, 7);
              this->restore_msb(buffer, 18, 7);
              this->restore_msb(buffer, 26, 7);
              this->restore_msb(buffer, 34, 7);
              this->restore_msb(buffer, 42, 1);

              // D1 + D2, D3 + D4
              this->state_measurment.pressure = buffer[2] * 256 + buffer[3];
              if (this->sensor_mespressure != nullptr) { this->sensor_mespressure->publish_state((float)this->state_measurment.pressure*0.01f); }
              ESP_LOGV(TAG, "Systemdruck = %d", this->state_measurment.pressure);
              this->state_measurment.level = buffer[4] * 256 + buffer[5];
              if (this->sensor_meslevel != nullptr) { this->sensor_meslevel->publish_state(this->state_measurment.level); }
              ESP_LOGV(TAG, "Fuellstand = %d%", this->state_measurment.level);
              
              // D5 Relay Outputs
              ESP_LOGV(TAG, "Register Relaisausgaenge: ");
              this->state_measurment.r_pump2_on = buffer[6] & (1 << 0);
              if (this->sensor_mesrpump2on != nullptr) { this->sensor_mesrpump2on->publish_state(this->state_measurment.r_pump2_on); }
              ESP_LOGV(TAG, "   Relaisausgang Pumpe2 Ein = %d", this->state_measurment.r_pump2_on);
              this->state_measurment.r_pump1_on = buffer[6] & (1 << 1);
              if (this->sensor_mesrpump1on != nullptr) { this->sensor_mesrpump1on->publish_state(this->state_measurment.r_pump1_on); }
              ESP_LOGV(TAG, "   Relaisausgang Pumpe1 Ein = %d", this->state_measurment.r_pump1_on);
              this->state_measurment.r_overflow2_open = buffer[6] & (1 << 2);
              if (this->sensor_mesroverflow2open != nullptr) { this->sensor_mesroverflow2open->publish_state(this->state_measurment.r_overflow2_open); }
              ESP_LOGV(TAG, "   Ueberstroemventil 2 Auf = %d", this->state_measurment.r_overflow2_open);
              this->state_measurment.r_overflow1_open = buffer[6] & (1 << 3);
              if (this->sensor_mesroverflow1open != nullptr) { this->sensor_mesroverflow1open->publish_state(this->state_measurment.r_overflow1_open); }
              ESP_LOGV(TAG, "   Ueberstroemventil 1 Auf = %d", this->state_measurment.r_overflow1_open);
              this->state_measurment.r_makeup_open = buffer[6] & (1 << 4);
              if (this->sensor_mesrmakeupopen != nullptr) { this->sensor_mesrmakeupopen->publish_state(this->state_measurment.r_makeup_open); }
              ESP_LOGV(TAG, "   Nachspeiseventiel Auf = %d", this->state_measurment.r_makeup_open);
              this->state_measurment.r_minlevel = buffer[6] & (1 << 5);
              if (this->sensor_mesrminlevel != nullptr) { this->sensor_mesrminlevel->publish_state(this->state_measurment.r_minlevel); }
              ESP_LOGV(TAG, "   Meldung min. Niveau = %d", this->state_measurment.r_minlevel);
              this->state_measurment.r_error = buffer[6] & (1 << 6);
              if (this->sensor_mesrerror != nullptr) { this->sensor_mesrerror->publish_state(this->state_measurment.r_error); }
              ESP_LOGV(TAG, "   Meldung Sammelstoerung = %d", this->state_measurment.r_error);
              
              // D6 Digital Inputs
              ESP_LOGV(TAG, "Register Digitaleingaenge: ");
              this->state_measurment.d_pump1 = buffer[7] & (1 << 0);
              if (this->sensor_mesdpump1 != nullptr) { this->sensor_mesdpump1->publish_state(this->state_measurment.d_pump1); }
              ESP_LOGV(TAG, "   Rueckmeldung Pumpe 1 = %d", this->state_measurment.d_pump1);
              this->state_measurment.d_pump2 = buffer[7] & (1 << 1);
              if (this->sensor_mesdpump2 != nullptr) { this->sensor_mesdpump2->publish_state(this->state_measurment.d_pump2); }
              ESP_LOGV(TAG, "   Rueckmeldung Pumpe 2 = %d", this->state_measurment.d_pump2);
              this->state_measurment.d_lackofwater = buffer[7] & (1 << 2);
              if (this->sensor_mesdlackofwater != nullptr) { this->sensor_mesdlackofwater->publish_state(this->state_measurment.d_lackofwater); }
              ESP_LOGV(TAG, "   Wassermangel-Schalter = %d", this->state_measurment.d_lackofwater);
              this->state_measurment.d_watermeter = buffer[7] & (1 << 3);
              if (this->sensor_mesdwatermeter != nullptr) { this->sensor_mesdwatermeter->publish_state(this->state_measurment.d_watermeter); }
              ESP_LOGV(TAG, "   Wasserzaehler Impuls  = %d", this->state_measurment.d_watermeter);
              this->state_measurment.d_softstart = buffer[7] & (1 << 7);
              if (this->sensor_mesdsoftstart != nullptr) { this->sensor_mesdsoftstart->publish_state(this->state_measurment.d_softstart); }
              ESP_LOGV(TAG, "   Sanftanlauf = %d", this->state_measurment.d_softstart);

              // D9 + D10 Error Messages 2
              ESP_LOGV(TAG, "Register Stoermeldungen 2: ");
              this->state_measurment.e2_mainboard = buffer[12] & (1 << 0);
              if (this->sensor_mese2mainboard != nullptr) { this->sensor_mese2mainboard->publish_state(this->state_measurment.e2_mainboard); }
              ESP_LOGV(TAG, "   Stoerung Grundplatine= %d", this->state_measurment.e2_mainboard);
              this->state_measurment.e2_digitalv = buffer[12] & (1 << 1);
              if (this->sensor_mese2digitalv != nullptr) { this->sensor_mese2digitalv->publish_state(this->state_measurment.e2_digitalv); }
              ESP_LOGV(TAG, "   Stoerung digitale Geberspannung = %d", this->state_measurment.e2_digitalv);
              this->state_measurment.e2_analogv = buffer[12] & (1 << 2);
              if (this->sensor_mese2analogv != nullptr) { this->sensor_mese2analogv->publish_state(this->state_measurment.e2_analogv); }
              ESP_LOGV(TAG, "   Stoerung analoge Geberspannung = %d", this->state_measurment.e2_analogv);
              this->state_measurment.e2_valve1 = buffer[12] & (1 << 3);
              if (this->sensor_mese2valve1 != nullptr) { this->sensor_mese2valve1->publish_state(this->state_measurment.e2_valve1); }
              ESP_LOGV(TAG, "   Stoerung Geberspannung Kugelhahn 1  = %d", this->state_measurment.e2_valve1);
              this->state_measurment.e2_valve2 = buffer[12] & (1 << 4);
              if (this->sensor_mese2valve2 != nullptr) { this->sensor_mese2valve2->publish_state(this->state_measurment.e2_valve2); }
              ESP_LOGV(TAG, "   Stoerung Geberspannung Kugelhahn 2 = %d", this->state_measurment.e2_valve2);
              this->state_measurment.e2_jpressure = buffer[12] & (1 << 5);
              if (this->sensor_mese2jpressure != nullptr) { this->sensor_mese2jpressure->publish_state(this->state_measurment.e2_jpressure); }
              ESP_LOGV(TAG, "   Stoerung Jumper Druck = %d", this->state_measurment.e2_jpressure);
              this->state_measurment.e2_jlevel = buffer[12] & (1 << 6);
              if (this->sensor_mese2jlevel != nullptr) { this->sensor_mese2jlevel->publish_state(this->state_measurment.e2_jlevel); }
              ESP_LOGV(TAG, "   Stoerung Jumper Niveau = %d", this->state_measurment.e2_jlevel);
              this->state_measurment.e2_dryrun = buffer[12] & (1 << 7);
              if (this->sensor_mese2dryrun != nullptr) { this->sensor_mese2dryrun->publish_state(this->state_measurment.e2_dryrun); }
              ESP_LOGV(TAG, "   Trockenlauf = %d", this->state_measurment.e2_dryrun);
              this->state_measurment.e2_lackofwater3 = buffer[11] & (1 << 0);
              if (this->sensor_mese2lackofwater3 != nullptr) { this->sensor_mese2lackofwater3->publish_state(this->state_measurment.e2_lackofwater3); }
              ESP_LOGV(TAG, "   Wassermangel 3 = %d", this->state_measurment.e2_lackofwater3);
              this->state_measurment.e2_lackofwater4 = buffer[11] & (1 << 1);
              if (this->sensor_mese2lackofwater4 != nullptr) { this->sensor_mese2lackofwater4->publish_state(this->state_measurment.e2_lackofwater4); }
              ESP_LOGV(TAG, "   Wassermangel 4 = %d", this->state_measurment.e2_lackofwater4);
              this->state_measurment.e2_lfsensor = buffer[11] & (1 << 2);
              if (this->sensor_mese2lfsensor != nullptr) { this->sensor_mese2lfsensor->publish_state(this->state_measurment.e2_lfsensor); }
              ESP_LOGV(TAG, "   LF-Sensor defekt = %d", this->state_measurment.e2_lfsensor);

              // D11 + D12 Error Messages 1
              ESP_LOGV(TAG, "Register Stoermeldungen 1: ");
              this->state_measurment.e1_extensionmodule = buffer[14] & (1 << 0);
              if (this->sensor_mese1extensionmodule != nullptr) { this->sensor_mese1extensionmodule->publish_state(this->state_measurment.e1_extensionmodule); }
              ESP_LOGV(TAG, "   Erweiterungsmodul = %d", this->state_measurment.e1_extensionmodule);
              this->state_measurment.e1_eeprom = buffer[14] & (1 << 1);
              if (this->sensor_mese1eeprom != nullptr) { this->sensor_mese1eeprom->publish_state(this->state_measurment.e1_eeprom); }
              ESP_LOGV(TAG, "   EEPROM Defekt = %d", this->state_measurment.e1_eeprom);
              this->state_measurment.e1_undervoltage = buffer[14] & (1 << 2);
              if (this->sensor_mese1undervoltage != nullptr) { this->sensor_mese1undervoltage->publish_state(this->state_measurment.e1_undervoltage); }
              ESP_LOGV(TAG, "   Unterspannung = %d", this->state_measurment.e1_undervoltage);
              this->state_measurment.e1_minpressure = buffer[14] & (1 << 3);
              if (this->sensor_mese1minpressure != nullptr) { this->sensor_mese1minpressure->publish_state(this->state_measurment.e1_minpressure); }
              ESP_LOGV(TAG, "   Min Druck unterschritten = %d", this->state_measurment.e1_minpressure);
              this->state_measurment.e1_lackofwater1 = buffer[14] & (1 << 4);
              if (this->sensor_mese1lackofwater1 != nullptr) { this->sensor_mese1lackofwater1->publish_state(this->state_measurment.e1_lackofwater1); }
              ESP_LOGV(TAG, "   Wassermangel 1 = %d", this->state_measurment.e1_lackofwater1);
              this->state_measurment.e1_pump1 = buffer[14] & (1 << 5);
              if (this->sensor_mese1pump1 != nullptr) { this->sensor_mese1pump1->publish_state(this->state_measurment.e1_pump1); }
              ESP_LOGV(TAG, "   Pumpe 1 gestoert = %d", this->state_measurment.e1_pump1);
              this->state_measurment.e1_compressor1 = buffer[14] & (1 << 6);
              if (this->sensor_mese1compressor1 != nullptr) { this->sensor_mese1compressor1->publish_state(this->state_measurment.e1_compressor1); }
              ESP_LOGV(TAG, "   Kompressor 1 gestoert = %d", this->state_measurment.e1_compressor1);
              this->state_measurment.e1_pump2 = buffer[14] & (1 << 7);
              if (this->sensor_mese1pump2 != nullptr) { this->sensor_mese1pump2->publish_state(this->state_measurment.e1_pump2); }
              ESP_LOGV(TAG, "   Pumpe 2 gestoert = %d", this->state_measurment.e1_pump2);
              this->state_measurment.e1_compressor2 = buffer[13] & (1 << 0);
              if (this->sensor_mese1compressor2 != nullptr) { this->sensor_mese1compressor2->publish_state(this->state_measurment.e1_compressor2); }
              ESP_LOGV(TAG, "   Kompressor 2 gestoert = %d", this->state_measurment.e1_compressor2);
              this->state_measurment.e1_pressuresensor = buffer[13] & (1 << 1);
              if (this->sensor_mese1pressuresensor != nullptr) { this->sensor_mese1pressuresensor->publish_state(this->state_measurment.e1_pressuresensor); }
              ESP_LOGV(TAG, "   Druckmessung gestoert = %d", this->state_measurment.e1_pressuresensor);
              this->state_measurment.e1_levelsensor = buffer[13] & (1 << 2);
              if (this->sensor_mese1levelsensor != nullptr) { this->sensor_mese1levelsensor->publish_state(this->state_measurment.e1_levelsensor); }
              ESP_LOGV(TAG, "   Niveaumessung gestoert = %d", this->state_measurment.e1_levelsensor);
              this->state_measurment.e1_pressuresensorpipe = buffer[13] & (1 << 3);
              if (this->sensor_mese1pressuresensorpipe != nullptr) { this->sensor_mese1pressuresensorpipe->publish_state(this->state_measurment.e1_pressuresensorpipe); }
              ESP_LOGV(TAG, "   Druckmessung Spruehrohr gestoert = %d", this->state_measurment.e1_pressuresensorpipe);
              this->state_measurment.e1_sto4h = buffer[13] & (1 << 4);
              if (this->sensor_mese1sto4h != nullptr) { this->sensor_mese1sto4h->publish_state(this->state_measurment.e1_sto4h); }
              ESP_LOGV(TAG, "   Laenger als 4 Stunden Stop = %d", this->state_measurment.e1_sto4h);
              this->state_measurment.e1_lackofwater2 = buffer[13] & (1 << 5);
              if (this->sensor_mese1lackofwater2 != nullptr) { this->sensor_mese1lackofwater2->publish_state(this->state_measurment.e1_lackofwater2); }
              ESP_LOGV(TAG, "   Wassermangel 2 = %d", this->state_measurment.e1_lackofwater2);
              this->state_measurment.e1_eeprom2 = buffer[13] & (1 << 6);
              if (this->sensor_mese1eeprom2 != nullptr) { this->sensor_mese1eeprom2->publish_state(this->state_measurment.e1_eeprom2); }
              ESP_LOGV(TAG, "   EEPROM Abgleich = %d", this->state_measurment.e1_eeprom2);

              // D15 + D16 Warning Messages 2
              ESP_LOGV(TAG, "Register Warnungen 2: ");
              this->state_measurment.w2_battery = buffer[19] & (1 << 0);
              if (this->sensor_mesw2battery != nullptr) { this->sensor_mesw2battery->publish_state(this->state_measurment.w2_battery); }
              ESP_LOGV(TAG, "   Batterie Tauschen = %d", this->state_measurment.w2_battery);
              this->state_measurment.w2_descalechange = buffer[19] & (1 << 1);
              if (this->sensor_mesw2descalechange != nullptr) { this->sensor_mesw2descalechange->publish_state(this->state_measurment.w2_descalechange); }
              ESP_LOGV(TAG, "   Enthaerter Patrone Tauschen  = %d", this->state_measurment.w2_descalechange);
              this->state_measurment.w2_datalogger = buffer[19] & (1 << 2);
              if (this->sensor_mesw2datalogger != nullptr) { this->sensor_mesw2datalogger->publish_state(this->state_measurment.w2_datalogger); }
              ESP_LOGV(TAG, "   Datenlogger pruefen = %d", this->state_measurment.w2_datalogger);
              this->state_measurment.w2_busmodule = buffer[19] & (1 << 3);
              if (this->sensor_mesw2busmodule != nullptr) { this->sensor_mesw2busmodule->publish_state(this->state_measurment.w2_busmodule); }
              ESP_LOGV(TAG, "   Busmodul pruefen = %d", this->state_measurment.w2_busmodule);
              this->state_measurment.w2_stop4h = buffer[19] & (1 << 4);
              if (this->sensor_mesw2stop4h != nullptr) { this->sensor_mesw2stop4h->publish_state(this->state_measurment.w2_stop4h); }
              ESP_LOGV(TAG, "   Laenger als 4h im Stop = %d", this->state_measurment.w2_stop4h);
              this->state_measurment.w2_conductivity = buffer[19] & (1 << 5);
              if (this->sensor_mesw2conductivity != nullptr) { this->sensor_mesw2conductivity->publish_state(this->state_measurment.w2_conductivity); }
              ESP_LOGV(TAG, "   Leitfaehigkeit ueberschritten = %d", this->state_measurment.w2_conductivity);

              // D17 + D18 Warning Messages 1
              ESP_LOGV(TAG, "Register Warnungen 1: ");
              this->state_measurment.w1_maxlevel = buffer[21] & (1 << 1);
              if (this->sensor_mesw1maxlevel != nullptr) { this->sensor_mesw1maxlevel->publish_state(this->state_measurment.w1_maxlevel); }
              ESP_LOGV(TAG, "   Max. Niveau ueberschritten = %d", this->state_measurment.w1_maxlevel);
              this->state_measurment.w1_pumpruntime = buffer[21] & (1 << 2);
              if (this->sensor_mesw1pumpruntime != nullptr) { this->sensor_mesw1pumpruntime->publish_state(this->state_measurment.w1_pumpruntime); }
              ESP_LOGV(TAG, "   Pumpenlaufzeit ueberschritten  = %d", this->state_measurment.w1_pumpruntime);
              this->state_measurment.w1_makeuptime = buffer[21] & (1 << 3);
              if (this->sensor_mesw1makeuptime != nullptr) { this->sensor_mesw1makeuptime->publish_state(this->state_measurment.w1_makeuptime); }
              ESP_LOGV(TAG, "   Nachspeisezeit ueberschritten = %d", this->state_measurment.w1_makeuptime);
              this->state_measurment.w1_maekupcycles = buffer[21] & (1 << 4);
              if (this->sensor_mesw1maekupcycles != nullptr) { this->sensor_mesw1maekupcycles->publish_state(this->state_measurment.w1_maekupcycles); }
              ESP_LOGV(TAG, "   Nachspeisezyklen ueberschritten = %d", this->state_measurment.w1_maekupcycles);
              this->state_measurment.w1_maxpressure = buffer[21] & (1 << 5);
              if (this->sensor_mesw1maxpressure != nullptr) { this->sensor_mesw1maxpressure->publish_state(this->state_measurment.w1_maxpressure); }
              ESP_LOGV(TAG, "   Max. Druck ueberschritten = %d", this->state_measurment.w1_maxpressure);
              this->state_measurment.w1_makeupvolume = buffer[21] & (1 << 6);
              if (this->sensor_mesw1makeupvolume != nullptr) { this->sensor_mesw1makeupvolume->publish_state(this->state_measurment.w1_makeupvolume); }
              ESP_LOGV(TAG, "   Nachspeisemaenge ueberschritten = %d", this->state_measurment.w1_makeupvolume);
              this->state_measurment.w1_filltime = buffer[21] & (1 << 7);
              if (this->sensor_mesw1filltime != nullptr) { this->sensor_mesw1filltime->publish_state(this->state_measurment.w1_filltime); }
              ESP_LOGV(TAG, "   Fuellzeit ueberschritten = %d", this->state_measurment.w1_filltime);
              this->state_measurment.w1_fillvolume = buffer[20] & (1 << 0);
              if (this->sensor_mesw1fillvolume != nullptr) { this->sensor_mesw1fillvolume->publish_state(this->state_measurment.w1_fillvolume); }
              ESP_LOGV(TAG, "   Fuellmenge ueberschritten = %d", this->state_measurment.w1_fillvolume);
              this->state_measurment.w1_expulsiontime = buffer[20] & (1 << 1);
              if (this->sensor_mesw1expulsiontime != nullptr) { this->sensor_mesw1expulsiontime->publish_state(this->state_measurment.w1_expulsiontime); }
              ESP_LOGV(TAG, "   Ausschiebezeit ueberschritten = %d", this->state_measurment.w1_expulsiontime);
              this->state_measurment.w1_makeupvalve = buffer[20] & (1 << 2);
              if (this->sensor_mesw1makeupvalve != nullptr) { this->sensor_mesw1makeupvalve->publish_state(this->state_measurment.w1_makeupvalve); }
              ESP_LOGV(TAG, "   Nachspeiseventil undicht = %d", this->state_measurment.w1_makeupvalve);
              this->state_measurment.w1_voltage = buffer[20] & (1 << 3);
              if (this->sensor_mesw1voltage != nullptr) { this->sensor_mesw1voltage->publish_state(this->state_measurment.w1_voltage); }
              ESP_LOGV(TAG, "   Spannungsabfall = %d", this->state_measurment.w1_voltage);
              this->state_measurment.w1_zerolevel = buffer[20] & (1 << 4);
              if (this->sensor_mesw1zerolevel != nullptr) { this->sensor_mesw1zerolevel->publish_state(this->state_measurment.w1_zerolevel); }
              ESP_LOGV(TAG, "   Nullabgleich fehlerhaft = %d", this->state_measurment.w1_zerolevel);
              this->state_measurment.w1_parameter = buffer[20] & (1 << 5);
              if (this->sensor_mesw1parameter != nullptr) { this->sensor_mesw1parameter->publish_state(this->state_measurment.w1_parameter); }
              ESP_LOGV(TAG, "   Parameter fehlerhaft = %d", this->state_measurment.w1_parameter);
              this->state_measurment.w1_maxmakeupvolume = buffer[20] & (1 << 6);
              if (this->sensor_mesw1maxmakeupvolume != nullptr) { this->sensor_mesw1maxmakeupvolume->publish_state(this->state_measurment.w1_maxmakeupvolume); }
              ESP_LOGV(TAG, "   Max Nachspeisemenge ueberschritten = %d", this->state_measurment.w1_maxmakeupvolume);
              this->state_measurment.w1_maintenance = buffer[20] & (1 << 7);
              if (this->sensor_mesw1maintenance != nullptr) { this->sensor_mesw1maintenance->publish_state(this->state_measurment.w1_maintenance); }
              ESP_LOGV(TAG, "   Wartungsanforderung = %d", this->state_measurment.w1_maintenance);
              // D19 - D22
              this->state_measurment.hours_pump1 = ( (buffer[22] * 256 + buffer[23] ) * 256 + buffer[24] ) * 256 + buffer[26];
              if (this->sensor_meshourspump1 != nullptr) { this->sensor_meshourspump1->publish_state(this->state_measurment.hours_pump1); }
              ESP_LOGV(TAG, "Betriebsstunden Pumpe 1 = %d", this->state_measurment.hours_pump1);
              // D23 - D26
              this->state_measurment.hours_pump2 = ( (buffer[27] * 256 + buffer[28] ) * 256 + buffer[29] ) * 256 + buffer[30];
              if (this->sensor_meshourspump2 != nullptr) { this->sensor_meshourspump2->publish_state(this->state_measurment.hours_pump2); }
              ESP_LOGV(TAG, "Betriebsstunden Pumpe 2 = %d", this->state_measurment.hours_pump2);
              // D27 - D30
              this->state_measurment.watermeter = ( (buffer[31] * 256 + buffer[32] ) * 256 + buffer[34] ) * 256 + buffer[35];
              if (this->sensor_meswatermeter != nullptr) { this->sensor_meswatermeter->publish_state(this->state_measurment.watermeter); }
              ESP_LOGV(TAG, "Wasserzaehler = %d", this->state_measurment.watermeter);
              // D31 Status Messages 1
              ESP_LOGV(TAG, "Register Statusmeldungen 1: ");
              this->state_measurment.s_manual = buffer[36] & (1 << 0);
              if (this->state_measurment.s_manual) {this->state_measurment.s_modus = "Manual";}
              if (this->sensor_messmanual != nullptr) { this->sensor_messmanual->publish_state(this->state_measurment.s_manual); }
              ESP_LOGV(TAG, "   Manual = %d", this->state_measurment.s_manual);
              this->state_measurment.s_stop = buffer[36] & (1 << 1);
              if (this->state_measurment.s_stop) {this->state_measurment.s_modus = "Stop";}
              if (this->sensor_messstop != nullptr) { this->sensor_messstop->publish_state(this->state_measurment.s_stop); }
              ESP_LOGV(TAG, "   Stop  = %d", this->state_measurment.s_stop);
              this->state_measurment.s_auto = buffer[36] & (1 << 2);
              if (this->state_measurment.s_auto) {this->state_measurment.s_modus = "Automatik";}
              if (this->sensor_messauto != nullptr) { this->sensor_messauto->publish_state(this->state_measurment.s_auto); }
              ESP_LOGV(TAG, "   Automatik = %d", this->state_measurment.s_auto);
              if (this->sensor_messmodus != nullptr) { this->sensor_messmodus->publish_state(this->state_measurment.s_modus); }
              ESP_LOGV(TAG, "   Modus = %s", this->state_measurment.s_modus.c_str());
              this->state_measurment.s_pump1 = buffer[36] & (1 << 4);
              if (this->sensor_messpump1 != nullptr) { this->sensor_messpump1->publish_state(this->state_measurment.s_pump1); }
              ESP_LOGV(TAG, "   1 Pumpe/Kompressor = %d", this->state_measurment.s_pump1);
              this->state_measurment.s_pump2 = buffer[36] & (1 << 5);
              if (this->sensor_messpump2 != nullptr) { this->sensor_messpump2->publish_state(this->state_measurment.s_pump2); }
              ESP_LOGV(TAG, "   2 Pumpe Kompressor = %d", this->state_measurment.s_pump2);

              // D32 Status Messages 2
              ESP_LOGV(TAG, "Register Statusmeldungen 2: ");
              this->state_measurment.s_error = buffer[37] & (1 << 0);
              if (this->sensor_messerror != nullptr) { this->sensor_messerror->publish_state(this->state_measurment.s_error); }
              ESP_LOGV(TAG, "   Sammlestoerung = %d", this->state_measurment.s_error);
              this->state_measurment.s_waterlevel = buffer[37] & (1 << 1);
              if (this->sensor_messwaterlevel != nullptr) { this->sensor_messwaterlevel->publish_state(this->state_measurment.s_waterlevel); }
              ESP_LOGV(TAG, "   Wassermangel  = %d", this->state_measurment.s_waterlevel);
              this->state_measurment.s_degas = buffer[37] & (1 << 2);
              if (this->sensor_messdegas != nullptr) { this->sensor_messdegas->publish_state(this->state_measurment.s_degas); }
              ESP_LOGV(TAG, "   Entgasung auf= %d", this->state_measurment.s_degas);
              this->state_measurment.s_makeupvalve = buffer[37] & (1 << 3);
              if (this->sensor_messmakeupvalve != nullptr) { this->sensor_messmakeupvalve->publish_state(this->state_measurment.s_makeupvalve); }
              ESP_LOGV(TAG, "   Nachspeiseventil auf = %d", this->state_measurment.s_makeupvalve);
              this->state_measurment.s_overflow1 = buffer[37] & (1 << 4);
              if (this->sensor_messoverflow1 != nullptr) { this->sensor_messoverflow1->publish_state(this->state_measurment.s_overflow1); }
              ESP_LOGV(TAG, "   Kugelhahn 1 auf = %d", this->state_measurment.s_overflow1);
              this->state_measurment.s_overflow2 = buffer[37] & (1 << 5);
              if (this->sensor_messoverflow2 != nullptr) { this->sensor_messoverflow2->publish_state(this->state_measurment.s_overflow2); }
              ESP_LOGV(TAG, "   Kugelhahn 2 auf = %d", this->state_measurment.s_overflow2);
              this->state_measurment.s_pump1_on = buffer[37] & (1 << 6);
              if (this->sensor_messpump1on != nullptr) { this->sensor_messpump1on->publish_state(this->state_measurment.s_pump1_on); }
              ESP_LOGV(TAG, "   Pumpe 1 ein = %d", this->state_measurment.s_pump1_on);
              this->state_measurment.s_pump2_on = buffer[37] & (1 << 7);
              if (this->sensor_messpump2on != nullptr) { this->sensor_messpump2on->publish_state(this->state_measurment.s_pump2_on); }
              ESP_LOGV(TAG, "   Pumpe 2 ein = %d", this->state_measurment.s_pump2_on);

              // D33 Valve 1 Position
              this->state_measurment.p_valve1 = buffer[38];
              if (this->sensor_mespvalve1 != nullptr) { this->sensor_mespvalve1->publish_state(this->state_measurment.p_valve1); }
              ESP_LOGV(TAG, "Motorkugelhahn 1 = %d %", this->state_measurment.p_valve1);
              // D34 Valve 2 Position
              this->state_measurment.p_valve2 = buffer[39];
              if (this->sensor_mespvalve2 != nullptr) { this->sensor_mespvalve2->publish_state(this->state_measurment.p_valve2); }
              ESP_LOGV(TAG, "Motorkugelhahn 2 = %d %", this->state_measurment.p_valve2);
              // D35 Equipment Type and Level Control Modus
              this->state_measurment.type = buffer[40] & 0b10111111;
              ESP_LOGV(TAG, "Anlagentyp = %d", this->state_measurment.type);
              this->state_measurment.levelcontrol = buffer[40] & (1 << 7);
              switch(this->state_measurment.type) {
                case 1:
                  this->state_measurment.type_name = "Variomat";
                break;
                case 2:
                  this->state_measurment.type_name = "Variomat Giga";
                break;
                case 3:
                  this->state_measurment.type_name = "Reflexomat / C";
                break;
                case 4:
                  this->state_measurment.type_name = "Servitec";
                break;
                case 5:
                  this->state_measurment.type_name = "Fillcontrol Auto";
                break;
                case 6:
                  this->state_measurment.type_name = "Servitec-25";
                break;
                case 7:
                  this->state_measurment.type_name = "Servitec-35";
                break;
                case 8:
                  this->state_measurment.type_name = "Fillcontrol Auto-Compact";
                break;
                case 9:
                  this->state_measurment.type_name = "Fillcontrol Plus";
                break;
              }
              ESP_LOGV(TAG, "Anlagentyp = %s", this->state_measurment.type_name.c_str());
              ESP_LOGV(TAG, "Modus Levelcontrol = %d", this->state_measurment.levelcontrol);
              // D36 Measurement Conductivity
              this->state_measurment.conductivity = buffer[41];
              if (this->sensor_mesconductivity != nullptr) { this->sensor_mesconductivity->publish_state(this->state_measurment.conductivity); }
              ESP_LOGV(TAG, "Leitfaehigkeit = %d uS/cm", this->state_measurment.conductivity);

              this->state_measurment.updated = 1;
              break;
            case REFLEX_MSG_TYPE:
              this->restore_msb(buffer, 2, 7);
              this->restore_msb(buffer, 10, 7);
              this->restore_msb(buffer, 18, 4);

              memcpy(&this->state_type.serial[0], &buffer[2], 7);
              memcpy(&this->state_type.serial[7], &buffer[10], 7);
              if (this->sensor_typeserial != nullptr) { this->sensor_typeserial->publish_state(this->state_type.serial); }
              ESP_LOGV(TAG, "Seriennummer = %s", this->state_type.serial);
              this->state_type.version = std::to_string(buffer[18]) + "." + std::to_string(buffer[19]);
              if (this->sensor_typeversion != nullptr) { this->sensor_typeversion->publish_state(this->state_type.version); }
              ESP_LOGV(TAG, "SW Version = %s", this->state_type.version.c_str());
              switch (buffer[20]) {
                case 10:
                  this->state_type.controller = "Control-Basic";
                  break;
                case 11:
                  this->state_type.controller = "Conntrol-Touch";
                  break;
                default:
                  this->state_type.controller = "UNKNOWN";
              }
              if (this->sensor_typecontroller != nullptr) { this->sensor_typecontroller->publish_state(this->state_type.controller); }
              ESP_LOGV(TAG, "Steuerungstyp = %s", this->state_type.controller.c_str());
              switch(buffer[21] & 0b10111111) {
                case 1:
                  this->state_type.type = "Variomat";
                break;
                case 2:
                  this->state_type.type = "Variomat Giga";
                break;
                case 3:
                  this->state_type.type = "Reflexomat / C";
                break;
                case 4:
                  this->state_type.type = "Servitec";
                break;
                case 5:
                  this->state_type.type = "Fillcontrol Auto";
                break;
                case 6:
                  this->state_type.type = "Servitec-25";
                break;
                case 7:
                  this->state_type.type = "Servitec-35";
                break;
                case 8:
                  this->state_type.type = "Fillcontrol Auto-Compact";
                break;
                case 9:
                  this->state_type.type = "Fillcontrol Plus";
                break;
              }
              ESP_LOGV(TAG, "Anlagentyp = %s", this->state_type.type.c_str());
              if (this->sensor_typetype != nullptr) { this->sensor_typetype->publish_state(this->state_type.type); }
              this->state_type.levelcontrol = buffer[21] & (1 << 7);
              if (this->sensor_typelevelcontrol != nullptr) { this->sensor_typelevelcontrol->publish_state(this->state_type.levelcontrol); }
              ESP_LOGV(TAG, "Modus Levelcontrol = %d", this->state_type.levelcontrol);

              this->state_type.updated = 1;
              break;
            case REFLEX_MSG_EXTPARAMETERS:
              this->restore_msb(buffer, 2, 7);
              this->restore_msb(buffer, 10, 7);
              this->restore_msb(buffer, 18, 7);
              this->restore_msb(buffer, 26, 7);
              this->restore_msb(buffer, 34, 7);
              this->restore_msb(buffer, 42, 1);

              this->state_parameter.pressure_p0 = buffer[2] * 256 + buffer[3];
              if (this->sensor_parapressurep0 != nullptr) { this->sensor_parapressurep0->publish_state((float)this->state_parameter.pressure_p0*0.1f); }
              ESP_LOGV(TAG, "Betriebsdruck P0 = %d", this->state_parameter.pressure_p0);
              this->state_parameter.pressure_max = buffer[4] * 256 + buffer[5];
              if (this->sensor_parapressuremax != nullptr) { this->sensor_parapressuremax->publish_state((float)this->state_parameter.pressure_max*0.1f); }
              ESP_LOGV(TAG, "Diff. Max. Druck = %d", this->state_parameter.pressure_max);
              this->state_parameter.conductivity_max = buffer[6] * 256 + buffer[7];
              if (this->sensor_paraconductivitymax != nullptr) { this->sensor_paraconductivitymax->publish_state(this->state_parameter.conductivity_max); }
              ESP_LOGV(TAG, "Leitfaehigkeit max. = %d", this->state_parameter.conductivity_max);
              this->state_parameter.pressure_nsp = buffer[8] * 256 + buffer[10];
              if (this->sensor_parapressurensp != nullptr) { this->sensor_parapressurensp->publish_state((float)this->state_parameter.pressure_nsp*0.1f); }
              ESP_LOGV(TAG, "Druckdiff. NSP = %d", this->state_parameter.pressure_nsp);
              this->state_parameter.pressures_sv = buffer[11] * 256 + buffer[12];
              if (this->sensor_parapressuressv != nullptr) { this->sensor_parapressuressv->publish_state((float)this->state_parameter.pressures_sv*0.1f); }
              ESP_LOGV(TAG, "Druckdiff. SV = %d", this->state_parameter.pressures_sv);
              this->state_parameter.pressure_pf = buffer[13] * 256 + buffer[14];
              if (this->sensor_parapressurepf != nullptr) { this->sensor_parapressurepf->publish_state((float)this->state_parameter.pressure_pf*0.1f); }
              ESP_LOGV(TAG, "Druckdiff. pf-p0 = %d", this->state_parameter.pressure_pf);
              this->state_parameter.waterlevel_on = buffer[15];
              if (this->sensor_parawaterlevelon != nullptr) { this->sensor_parawaterlevelon->publish_state(this->state_parameter.waterlevel_on); }
              ESP_LOGV(TAG, "Wassermangel EIN = %d %", this->state_parameter.waterlevel_on);
              this->state_parameter.waterlevel_off = buffer[16];
              if (this->sensor_parawaterleveloff != nullptr) { this->sensor_parawaterleveloff->publish_state(this->state_parameter.waterlevel_off); }
              ESP_LOGV(TAG, "Wassermangel AUS = %d %", this->state_parameter.waterlevel_off);
              this->state_parameter.fill_on = buffer[18];
              if (this->sensor_parafillon != nullptr) { this->sensor_parafillon->publish_state(this->state_parameter.fill_on); }
              ESP_LOGV(TAG, "Nachspeisung EIN = %d %", this->state_parameter.fill_on);
              this->state_parameter.fill_off = buffer[19];
              if (this->sensor_parafilloff != nullptr) { this->sensor_parafilloff->publish_state(this->state_parameter.fill_off); }
              ESP_LOGV(TAG, "Nachspeisung AUS = %d %", this->state_parameter.fill_off);
              this->state_parameter.max_fillvolume = ( (buffer[20] * 256 + buffer[21] ) * 256 + buffer[22] ) * 256 + buffer[23];
              if (this->sensor_paramaxfillvolume != nullptr) { this->sensor_paramaxfillvolume->publish_state(this->state_parameter.max_fillvolume); }
              ESP_LOGV(TAG, "Max. Nachspeisemenge = %d", this->state_parameter.max_fillvolume);
              this->state_parameter.max_fillcycles = buffer[24];
              if (this->sensor_paramaxfillcycles != nullptr) { this->sensor_paramaxfillcycles->publish_state(this->state_parameter.max_fillcycles); }
              ESP_LOGV(TAG, "Max. Nachspeisezyklen = %d", this->state_parameter.max_fillcycles);
              this->state_parameter.max_filltime = buffer[26];
              if (this->sensor_paramaxfilltime != nullptr) { this->sensor_paramaxfilltime->publish_state(this->state_parameter.max_filltime); }
              ESP_LOGV(TAG, "Max. Nachspeisezeit = %d", this->state_parameter.max_filltime);
              this->state_parameter.max_fillimpulse = buffer[27];
              if (this->sensor_paramaxfillimpulse != nullptr) { this->sensor_paramaxfillimpulse->publish_state(this->state_parameter.max_fillimpulse); }
              ESP_LOGV(TAG, "Max. Nachspeiseimpulse = %d", this->state_parameter.max_fillimpulse);
              ESP_LOGV(TAG, "Register Menuestatus: ");
              this->state_parameter.s_customer = buffer[28] & (1 << 0);
              if (this->sensor_parascustomer != nullptr) { this->sensor_parascustomer->publish_state(this->state_parameter.s_customer); }
              ESP_LOGV(TAG, "   Kundenmenue Aktiv = %d", this->state_parameter.s_customer);
              this->state_parameter.s_service = buffer[28] & (1 << 1);
              if (this->sensor_parasservice != nullptr) { this->sensor_parasservice->publish_state(this->state_parameter.s_service); }
              ESP_LOGV(TAG, "   Servicemenue Aktiv = %d", this->state_parameter.s_service);
              this->state_parameter.s_ro = buffer[28] & (1 << 4);
              if (this->sensor_parasro != nullptr) { this->sensor_parasro->publish_state(this->state_parameter.s_ro); }
              ESP_LOGV(TAG, "   Schreibzugriff gesperrt = %d", this->state_parameter.s_ro);
              this->state_parameter.s_parameter = buffer[28] & (1 << 6);
              if (this->sensor_parasparameter != nullptr) { this->sensor_parasparameter->publish_state(this->state_parameter.s_parameter); }
              ESP_LOGV(TAG, "   Parameter lokal geaendert = %d", this->state_parameter.s_parameter);
              this->state_parameter.container_size = buffer[29] * 256 + buffer[30];
              if (this->sensor_paracontainersize != nullptr) { this->sensor_paracontainersize->publish_state(this->state_parameter.container_size); }
              ESP_LOGV(TAG, "Behaeltergroesse = %d", this->state_parameter.container_size);
              this->state_parameter.container_weight = buffer[31] * 256 + buffer[32];
              if (this->sensor_paracontainerweight != nullptr) { this->sensor_paracontainerweight->publish_state((float)this->state_parameter.container_weight*0.01f); }
              ESP_LOGV(TAG, "Behaeltergewicht leer = %d", this->state_parameter.container_weight);
              this->state_parameter.container_differenz = buffer[34] * 256 + buffer[35];
              if (this->sensor_paracontainerdifferenz != nullptr) { this->sensor_paracontainerdifferenz->publish_state((float)this->state_parameter.container_differenz*0.01f); }
              ESP_LOGV(TAG, "Behaeltergewicht voll-leer = %d", this->state_parameter.container_differenz);
              this->state_parameter.maintenance = buffer[36];
              if (this->sensor_paramaintenance != nullptr) { this->sensor_paramaintenance->publish_state(this->state_parameter.maintenance); }
              ESP_LOGV(TAG, "Restzeit Wartungsinterval = %d", this->state_parameter.maintenance);
              this->state_parameter.highwater = buffer[37];
              if (this->sensor_parahighwater != nullptr) { this->sensor_parahighwater->publish_state(this->state_parameter.highwater); }
              ESP_LOGV(TAG, "Hochwasser EIN = %d", this->state_parameter.highwater);
              this->state_parameter.descaler = buffer[38];
              if (this->sensor_paradescaler != nullptr) { this->sensor_paradescaler->publish_state(this->state_parameter.descaler); }
              ESP_LOGV(TAG, "Kartusche tauschen in = %d", this->state_parameter.descaler);
              this->state_parameter.descaler_remaining = buffer[39] * 256 + buffer[40];
              if (this->sensor_paradescalerremaining != nullptr) { this->sensor_paradescalerremaining->publish_state(this->state_parameter.descaler_remaining); }
              ESP_LOGV(TAG, "Restkapazitaet Weichwasser = %d", this->state_parameter.descaler_remaining);
              this->state_parameter.programm = buffer[42];
              switch (buffer[42]) {
                case 0:
                  this->state_parameter.programm = "-";
                  break;
                case 1:
                  this->state_parameter.programm = "DE";
                  break;
                case 2:
                  this->state_parameter.programm = "IE";
                  break;
                case 3:
                  this->state_parameter.programm = "NE";
                  break;
                case 4:
                  this->state_parameter.programm = "NSP";
                  break;
                default:
                  this->state_parameter.programm = "UNKNOWN";
              }
              if (this->sensor_paraprogramm != nullptr) { this->sensor_paraprogramm->publish_state(this->state_parameter.programm); }
              ESP_LOGV(TAG, "Entgasungsprogramm = %s", this->state_parameter.programm.c_str());
              this->state_parameter.updated = 1;
              break;
            default:
              ESP_LOGE(TAG, "Unknown Reflex message type %X", buffer[1]);
          }
        } else {
          ESP_LOGE(TAG, "message received, invalid checksum");
        }
      } else {
        ESP_LOGE(TAG, "message received, invalid end character");
      }
    } else {
      ESP_LOGE(TAG, "message received, invalid start character");
    }
    loopwait = 0;
    index = 0;
  }

}

void ReflexComponent::dump_data() {

      ESP_LOGI(TAG, "Systemdruck = %d", this->state_measurment.pressure);
      ESP_LOGI(TAG, "Fuellstand = %d%", this->state_measurment.level);
      ESP_LOGI(TAG, "Register Relaisausgaenge: ");

      ESP_LOGI(TAG, "   Relaisausgang Pumpe2 Ein = %d", this->state_measurment.r_pump2_on);
      ESP_LOGI(TAG, "   Relaisausgang Pumpe1 Ein = %d", this->state_measurment.r_pump1_on);
      ESP_LOGI(TAG, "   Ueberstroemventil 2 Auf = %d", this->state_measurment.r_overflow2_open);
      ESP_LOGI(TAG, "   Ueberstroemventil 1 Auf = %d", this->state_measurment.r_overflow1_open);
      ESP_LOGI(TAG, "   Nachspeiseventiel Auf = %d", this->state_measurment.r_makeup_open);
      ESP_LOGI(TAG, "   Meldung min. Niveau = %d", this->state_measurment.r_minlevel);
      ESP_LOGI(TAG, "   Meldung Sammelstoerung = %d", this->state_measurment.r_error);
      
      // D6 Digital Inputs
      ESP_LOGI(TAG, "Register Digitaleingaenge: ");
      ESP_LOGI(TAG, "   Rueckmeldung Pumpe 1 = %d", this->state_measurment.d_pump1);
      ESP_LOGI(TAG, "   Rueckmeldung Pumpe 2 = %d", this->state_measurment.d_pump2);
      ESP_LOGI(TAG, "   Wassermangel-Schalter = %d", this->state_measurment.d_lackofwater);
      ESP_LOGI(TAG, "   Wasserzaehler Impuls  = %d", this->state_measurment.d_watermeter);
      ESP_LOGI(TAG, "   Sanftanlauf = %d", this->state_measurment.d_softstart);

      // D9 + D10 Error Messages 2
      ESP_LOGI(TAG, "Register Stoermeldungen 2: ");
      ESP_LOGI(TAG, "   Stoerung Grundplatine= %d", this->state_measurment.e2_mainboard);
      ESP_LOGI(TAG, "   Stoerung digitale Geberspannung = %d", this->state_measurment.e2_digitalv);
      ESP_LOGI(TAG, "   Stoerung analoge Geberspannung = %d", this->state_measurment.e2_analogv);
      ESP_LOGI(TAG, "   Stoerung Geberspannung Kugelhahn 1  = %d", this->state_measurment.e2_valve1);
      ESP_LOGI(TAG, "   Stoerung Geberspannung Kugelhahn 2 = %d", this->state_measurment.e2_valve2);
      ESP_LOGI(TAG, "   Stoerung Jumper Druck = %d", this->state_measurment.e2_jpressure);
      ESP_LOGI(TAG, "   Stoerung Jumper Niveau = %d", this->state_measurment.e2_jlevel);
      ESP_LOGI(TAG, "   Trockenlauf = %d", this->state_measurment.e2_dryrun);
      ESP_LOGI(TAG, "   Wassermangel 3 = %d", this->state_measurment.e2_lackofwater3);
      ESP_LOGI(TAG, "   Wassermangel 4 = %d", this->state_measurment.e2_lackofwater4);
      ESP_LOGI(TAG, "   LF-Sensor defekt = %d", this->state_measurment.e2_lfsensor);

      // D11 + D12 Error Messages 1
      ESP_LOGI(TAG, "Register Stoermeldungen 1: ");
      ESP_LOGI(TAG, "   Erweiterungsmodul = %d", this->state_measurment.e1_extensionmodule);
      ESP_LOGI(TAG, "   EEPROM Defekt = %d", this->state_measurment.e1_eeprom);
      ESP_LOGI(TAG, "   Unterspannung = %d", this->state_measurment.e1_undervoltage);
      ESP_LOGI(TAG, "   Min Druck unterschritten = %d", this->state_measurment.e1_minpressure);
      ESP_LOGI(TAG, "   Wassermangel 1 = %d", this->state_measurment.e1_lackofwater1);
      ESP_LOGI(TAG, "   Pumpe 1 gestoert = %d", this->state_measurment.e1_pump1);
      ESP_LOGI(TAG, "   Kompressor 1 gestoert = %d", this->state_measurment.e1_compressor1);
      ESP_LOGI(TAG, "   Pumpe 2 gestoert = %d", this->state_measurment.e1_pump2);
      ESP_LOGI(TAG, "   Kompressor 2 gestoert = %d", this->state_measurment.e1_compressor2);
      ESP_LOGI(TAG, "   Druckmessung gestoert = %d", this->state_measurment.e1_pressuresensor);
      ESP_LOGI(TAG, "   Niveaumessung gestoert = %d", this->state_measurment.e1_levelsensor);
      ESP_LOGI(TAG, "   Druckmessung Spruehrohr gestoert = %d", this->state_measurment.e1_pressuresensorpipe);
      ESP_LOGI(TAG, "   Laenger als 4 Stunden Stop = %d", this->state_measurment.e1_sto4h);
      ESP_LOGI(TAG, "   Wassermangel 2 = %d", this->state_measurment.e1_lackofwater2);
      ESP_LOGI(TAG, "   EEPROM Abgleich = %d", this->state_measurment.e1_eeprom2);

      // D15 + D16 Warning Messages 2
      ESP_LOGI(TAG, "Register Warnungen 2: ");
      ESP_LOGI(TAG, "   Batterie Tauschen = %d", this->state_measurment.w2_battery);
      ESP_LOGI(TAG, "   Enthaerter Patrone Tauschen  = %d", this->state_measurment.w2_descalechange);
      ESP_LOGI(TAG, "   Datenlogger pruefen = %d", this->state_measurment.w2_datalogger);
      ESP_LOGI(TAG, "   Busmodul pruefen = %d", this->state_measurment.w2_busmodule);
      ESP_LOGI(TAG, "   Laenger als 4h im Stop = %d", this->state_measurment.w2_stop4h);
      ESP_LOGI(TAG, "   Leitfaehigkeit ueberschritten = %d", this->state_measurment.w2_conductivity);

      // D17 + D18 Warning Messages 1
      ESP_LOGI(TAG, "Register Warnungen 1: ");
      ESP_LOGI(TAG, "   Max. Niveau ueberschritten = %d", this->state_measurment.w1_maxlevel);
      ESP_LOGI(TAG, "   Pumpenlaufzeit ueberschritten  = %d", this->state_measurment.w1_pumpruntime);
      ESP_LOGI(TAG, "   Nachspeisezeit ueberschritten = %d", this->state_measurment.w1_makeuptime);
      ESP_LOGI(TAG, "   Nachspeisezyklen ueberschritten = %d", this->state_measurment.w1_maekupcycles);
      ESP_LOGI(TAG, "   Max. Druck ueberschritten = %d", this->state_measurment.w1_maxpressure);
      ESP_LOGI(TAG, "   Nachspeisemaenge ueberschritten = %d", this->state_measurment.w1_makeupvolume);
      ESP_LOGI(TAG, "   Fuellzeit ueberschritten = %d", this->state_measurment.w1_filltime);
      ESP_LOGI(TAG, "   Fuellmenge ueberschritten = %d", this->state_measurment.w1_fillvolume);
      ESP_LOGI(TAG, "   Ausschiebezeit ueberschritten = %d", this->state_measurment.w1_expulsiontime);
      ESP_LOGI(TAG, "   Nachspeiseventil undicht = %d", this->state_measurment.w1_makeupvalve);
      ESP_LOGI(TAG, "   Spannungsabfall = %d", this->state_measurment.w1_voltage);
      ESP_LOGI(TAG, "   Nullabgleich fehlerhaft = %d", this->state_measurment.w1_zerolevel);
      ESP_LOGI(TAG, "   Parameter fehlerhaft = %d", this->state_measurment.w1_parameter);
      ESP_LOGI(TAG, "   Max Nachspeisemenge ueberschritten = %d", this->state_measurment.w1_maxmakeupvolume);
      ESP_LOGI(TAG, "   Wartungsanforderung = %d", this->state_measurment.w1_maintenance);

      // D19 - D22
      ESP_LOGI(TAG, "Betriebsstunden Pumpe 1 = %d", this->state_measurment.hours_pump1);
      // D23 - D26
      ESP_LOGI(TAG, "Betriebsstunden Pumpe 2 = %d", this->state_measurment.hours_pump2);
      // D27 - D30
      ESP_LOGI(TAG, "Wasserzaehler = %d", this->state_measurment.watermeter);
      // D31 Status Messages 1
      ESP_LOGI(TAG, "Register Statusmeldungen 1: ");
      ESP_LOGI(TAG, "   Modus = %s", this->state_measurment.s_modus.c_str());
      ESP_LOGI(TAG, "   Manual = %d", this->state_measurment.s_manual);
      ESP_LOGI(TAG, "   Stop  = %d", this->state_measurment.s_stop);
      ESP_LOGI(TAG, "   Automatik = %d", this->state_measurment.s_auto);
      ESP_LOGI(TAG, "   1 Pumpe/Kompressor = %d", this->state_measurment.s_pump1);
      ESP_LOGI(TAG, "   2 Pumpe Kompressor = %d", this->state_measurment.s_pump2);

      // D32 Status Messages 2
      ESP_LOGI(TAG, "Register Statusmeldungen 2: ");
      ESP_LOGI(TAG, "   Sammlestoerung = %d", this->state_measurment.s_error);
      ESP_LOGI(TAG, "   Wassermangel  = %d", this->state_measurment.s_waterlevel);
      ESP_LOGI(TAG, "   Entgasung auf= %d", this->state_measurment.s_degas);
      ESP_LOGI(TAG, "   Nachspeiseventil auf = %d", this->state_measurment.s_makeupvalve);
      ESP_LOGI(TAG, "   Kugelhahn 1 auf = %d", this->state_measurment.s_overflow1);
      ESP_LOGI(TAG, "   Kugelhahn 2 auf = %d", this->state_measurment.s_overflow2);
      ESP_LOGI(TAG, "   Pumpe 1 ein = %d", this->state_measurment.s_pump1_on);
      ESP_LOGI(TAG, "   Pumpe 2 ein = %d", this->state_measurment.s_pump2_on);

      // D33 Valve 1 Position
      ESP_LOGI(TAG, "Motorkugelhahn 1 = %d %", this->state_measurment.p_valve1);
      // D34 Valve 2 Position
      ESP_LOGI(TAG, "Motorkugelhahn 2 = %d %", this->state_measurment.p_valve2);
      // D35 Equipment Type and Level Control Modus
      ESP_LOGI(TAG, "Anlagentyp = %d", this->state_measurment.type);
      ESP_LOGI(TAG, "Anlagentyp = %s", this->state_measurment.type_name.c_str());
      ESP_LOGI(TAG, "Modus Levelcontrol = %d", this->state_measurment.levelcontrol);
      // D36 Measurement Conductivity
      ESP_LOGI(TAG, "Leitfaehigkeit = %d uS/cm", this->state_measurment.conductivity);
      ESP_LOGI(TAG, "Seriennummer = %s", this->state_type.serial);
      ESP_LOGI(TAG, "SW Version = %s", this->state_type.version.c_str());
      ESP_LOGI(TAG, "Steuerungstyp = %s", this->state_type.controller.c_str());
      ESP_LOGI(TAG, "Anlagentyp = %s", this->state_type.type.c_str());
      ESP_LOGI(TAG, "Modus Levelcontrol = %d", this->state_type.levelcontrol);


      ESP_LOGI(TAG, "Betriebsdruck P0 = %d", this->state_parameter.pressure_p0);
      ESP_LOGI(TAG, "Diff. Max. Druck = %d", this->state_parameter.pressure_max);
      ESP_LOGI(TAG, "Leitfaehigkeit max. = %d", this->state_parameter.conductivity_max);
      ESP_LOGI(TAG, "Druckdiff. NSP = %d", this->state_parameter.pressure_nsp);
      ESP_LOGI(TAG, "Druckdiff. SV = %d", this->state_parameter.pressures_sv);
      ESP_LOGI(TAG, "Druckdiff. pf-p0 = %d", this->state_parameter.pressure_pf);
      ESP_LOGI(TAG, "Wassermangel EIN = %d %", this->state_parameter.waterlevel_on);
      ESP_LOGI(TAG, "Wassermangel AUS = %d %", this->state_parameter.waterlevel_off);
      ESP_LOGI(TAG, "Nachspeisung EIN = %d %", this->state_parameter.fill_on);
      ESP_LOGI(TAG, "Nachspeisung AUS = %d %", this->state_parameter.fill_off);
      ESP_LOGI(TAG, "Max. Nachspeisemenge = %d", this->state_parameter.max_fillvolume);
      ESP_LOGI(TAG, "Max. Nachspeisezyklen = %d", this->state_parameter.max_fillcycles);
      ESP_LOGI(TAG, "Max. Nachspeisezeit = %d", this->state_parameter.max_filltime);
      ESP_LOGI(TAG, "Max. Nachspeiseimpulse = %d", this->state_parameter.max_fillimpulse);
      ESP_LOGI(TAG, "Register Menuestatus: ");
      ESP_LOGI(TAG, "   Kundenmenue Aktiv = %d", this->state_parameter.s_customer);
      ESP_LOGI(TAG, "   Servicemenue Aktiv = %d", this->state_parameter.s_service);
      ESP_LOGI(TAG, "   Schreibzugriff gesperrt = %d", this->state_parameter.s_ro);
      ESP_LOGI(TAG, "   Parameter lokal geaendert = %d", this->state_parameter.s_parameter);
      ESP_LOGI(TAG, "Behaeltergroesse = %d", this->state_parameter.container_size);
      ESP_LOGI(TAG, "Behaeltergewicht leer = %d", this->state_parameter.container_weight);
      ESP_LOGI(TAG, "Behaeltergewicht voll-leer = %d", this->state_parameter.container_differenz);
      ESP_LOGI(TAG, "Restzeit Wartungsinterval = %d", this->state_parameter.maintenance);
      ESP_LOGI(TAG, "Hochwasser EIN = %d", this->state_parameter.highwater);
      ESP_LOGI(TAG, "Kartusche tauschen in = %d", this->state_parameter.descaler);
      ESP_LOGI(TAG, "Restkapazitaet Weichwasser = %d", this->state_parameter.descaler_remaining);
      ESP_LOGI(TAG, "Entgasungsprogramm = %s", this->state_parameter.programm.c_str());

}

void ReflexComponent::restore_msb(char *buffer, int offset, int size) {

  for (int i = 0; i < size; i++) {
    buffer[offset+i] = buffer[offset+i] | (buffer[offset+size] << (7-i) & 0b10000000); // Restore MSB
  }

}

void ReflexComponent::update() {

  ESP_LOGV(TAG, "reflex update called %d %d %d", this->state_type.updated,  this->state_parameter.updated, this->state_measurment.updated);
  static uint16_t iteration = 0;
  
  iteration++;

  if (iteration % 1440 == 0) {

    this->state_type.updated = 0;

  }

  if (this->state_type.updated) {

    if (iteration % 10 == 0) {

      this->state_parameter.updated = 0;

    }
    
    if (this->state_parameter.updated) {
    
      this->state_measurment.updated = 0;

      if (this->state_measurment.updated) {
    
      } else {

        this->send_master(1, REFLEX_MSG_MEASUREMENTS);
        ESP_LOGI(TAG, "Update Measurement");
      
      }

    } else {

      this->send_master(1, REFLEX_MSG_EXTPARAMETERS);
      ESP_LOGI(TAG, "Update Parameter");

    }

  } else {

    this->send_master(1, REFLEX_MSG_TYPE);
    ESP_LOGI(TAG, "Update Type");

  } 

}

void ReflexComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "Reflex Component");
}

} // namespace reflex
} // namespace esphome
