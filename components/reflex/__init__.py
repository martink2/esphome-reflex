import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, binary_sensor, text_sensor, uart
from esphome.const import *
reflex_ns = cg.esphome_ns.namespace('reflex')
ReflexComponent = reflex_ns.class_('ReflexComponent', cg.PollingComponent)

DEPENDENCIES = ['uart']
AUTO_LOAD = ['uart', 'sensor', 'text_sensor', 'binary_sensor']

CONF_TYPE_SERIAL = "type_serial"
CONF_TYPE_VERSION = "type_version"
CONF_TYPE_CONTROLLER = "type_controller"
CONF_TYPE_TYPE = "type_type"
CONF_TYPE_LEVELCONTROL = "type_levelcontrol"

CONF_PARA_PRESSUREP0 = "para_pressurep0"
CONF_PARA_PARAPRESSUREMAX = "para_pressuremax"
CONF_PARA_PARACONDUCTIVITYMAX = "para_conductivitymax"
CONF_PARA_PARAPRESSURENSP = "para_pressurensp"
CONF_PARA_PARAPRESSURESSV = "para_pressuressv"
CONF_PARA_PARAPRESSUREPF = "para_pressurepf"
CONF_PARA_PARAWATERLEVELON = "para_waterlevelon"
CONF_PARA_PARAWATERLEVELOFF = "para_waterleveloff"
CONF_PARA_PARAFILLON = "para_fillon"
CONF_PARA_PARAFILLOFF = "para_filloff"
CONF_PARA_PARAMAXFILLVOLUME = "para_maxfillvolume"
CONF_PARA_PARAMAXFILLCYCLES = "para_maxfillcycles"
CONF_PARA_PARAMAXFILLTIME = "para_maxfilltime"
CONF_PARA_PARAMAXFILLIMPULSE = "para_maxfillimpulse"
CONF_PARA_PARASCUSTOMER = "para_scustomer"
CONF_PARA_PARASSERVICE = "para_sservice"
CONF_PARA_PARASRO = "para_sro"
CONF_PARA_PARASPARAMETER = "para_sparameter"
CONF_PARA_PARACONTAINERSIZE = "para_containersize"
CONF_PARA_PARACONTAINERWEIGHT = "para_containerweight"
CONF_PARA_PARACONTAINERDIFFERENZ = "para_containerdifferenz"
CONF_PARA_PARAMAINTENANCE = "para_maintenance"
CONF_PARA_PARAHIGHWATER = "para_highwater"
CONF_PARA_PARADESCALER = "para_descaler"
CONF_PARA_PARADESCALERREMAINING = "para_descalerremaining"
CONF_PARA_PARAPROGRAMM = "para_programm"

CONF_MES_PRESSURE = "mes_pressure"
CONF_MES_LEVEL = "mes_level"
CONF_MES_HOURSPUMP1 = "mes_hourspump1"
CONF_MES_HOURSPUMP2 = "mes_hourspump2"
CONF_MES_WATERMETER = "mes_watermeter"
CONF_MES_PVALVE1 = "mes_pvalve1"
CONF_MES_PVALVE2 = "mes_pvalve2"
CONF_MES_CONDUCTIVITY = "mes_conductivity"
CONF_MES_SMODUS = "mes_smodus"
CONF_MES_RPUMP2ON = "mes_rpump2on"
CONF_MES_RPUMP1ON = "mes_rpump1on"
CONF_MES_ROVERFLOW2OPEN = "mes_roverflow2open"
CONF_MES_ROVERFLOW1OPEN = "mes_roverflow1open"
CONF_MES_RMAKEUPOPEN = "mes_rmakeupopen"
CONF_MES_RMINLEVEL = "mes_rminlevel"
CONF_MES_RERROR = "mes_rerror"
CONF_MES_DPUMP1 = "mes_dpump1"
CONF_MES_DPUMP2 = "mes_dpump2"
CONF_MES_DLACKOFWATER = "mes_dlackofwater"
CONF_MES_DWATERMETER = "mes_dwatermeter"
CONF_MES_DSOFTSTART = "mes_dsoftstart"
CONF_MES_E2MAINBOARD = "mes_e2mainboard"
CONF_MES_E2DIGITALV = "mes_e2digitalv"
CONF_MES_E2ANALOGV = "mes_e2analogv"
CONF_MES_E2VALVE1 = "mes_e2valve1"
CONF_MES_E2VALVE2 = "mes_e2valve2"
CONF_MES_E2JPRESSURE = "mes_e2jpressure"
CONF_MES_E2JLEVEL = "mes_e2jlevel"
CONF_MES_E2DRYRUN = "mes_e2dryrun"
CONF_MES_E2LACKOFWATER3 = "mes_e2lackofwater3"
CONF_MES_E2LACKOFWATER4 = "mes_e2lackofwater4"
CONF_MES_E2LFSENSOR = "mes_e2lfsensor"
CONF_MES_E1EXTENSIONMODULE = "mes_e1extensionmodule"
CONF_MES_E1EEPROM = "mes_e1eeprom"
CONF_MES_E1UNDERVOLTAGE = "mes_e1undervoltage"
CONF_MES_E1MINPRESSURE = "mes_e1minpressure"
CONF_MES_E1LACKOFWATER1 = "mes_e1lackofwater1"
CONF_MES_E1PUMP1 = "mes_e1pump1"
CONF_MES_E1COMPRESSOR1 = "mes_e1compressor1"
CONF_MES_E1PUMP2 = "mes_e1pump2"
CONF_MES_E1COMPRESSOR2 = "mes_e1compressor2"
CONF_MES_E1PRESSURESENSOR = "mes_e1pressuresensor"
CONF_MES_E1LEVELSENSOR = "mes_e1levelsensor"
CONF_MES_E1PRESSURESENSORPIPE = "mes_e1pressuresensorpipe"
CONF_MES_E1STO4H = "mes_e1sto4h"
CONF_MES_E1LACKOFWATER2 = "mes_e1lackofwater2"
CONF_MES_E1EEPROM2 = "mes_e1eeprom2"
CONF_MES_W2BATTERY = "mes_w2battery"
CONF_MES_W2DESCALECHANGE = "mes_w2descalechange"
CONF_MES_W2DATALOGGER = "mes_w2datalogger"
CONF_MES_W2BUSMODULE = "mes_w2busmodule"
CONF_MES_W2STOP4H = "mes_w2stop4h"
CONF_MES_W2CONDUCTIVITY = "mes_w2conductivity"
CONF_MES_W1MAXLEVEL = "mes_w1maxlevel"
CONF_MES_W1PUMPRUNTIME = "mes_w1pumpruntime"
CONF_MES_W1MAKEUPTIME = "mes_w1makeuptime"
CONF_MES_W1MAEKUPCYCLES = "mes_w1maekupcycles"
CONF_MES_W1MAXPRESSURE = "mes_w1maxpressure"
CONF_MES_W1MAKEUPVOLUME = "mes_w1makeupvolume"
CONF_MES_W1EXPULSIONTIME = "mes_w1expulsiontime"
CONF_MES_W1FILLTIME = "mes_w1filltime"
CONF_MES_W1FILLVOLUME = "mes_w1fillvolume"
CONF_MES_W1MAKEUPVALVE = "mes_w1makeupvalve"
CONF_MES_W1VOLTAGE = "mes_w1voltage"
CONF_MES_W1ZEROLEVEL = "mes_w1zerolevel"
CONF_MES_W1PARAMETER = "mes_w1parameter"
CONF_MES_W1MAXMAKEUPVOLUME = "mes_w1maxmakeupvolume"
CONF_MES_W1MAINTENANCE = "mes_w1maintenance"
CONF_MES_SMANUAL = "mes_smanual"
CONF_MES_SSTOP = "mes_sstop"
CONF_MES_SAUTO = "mes_sauto"
CONF_MES_SPUMP1 = "mes_spump1"
CONF_MES_SPUMP2 = "mes_spump2"
CONF_MES_SERROR = "mes_serror"
CONF_MES_SWATERLEVEL = "mes_swaterlevel"
CONF_MES_SDEGAS = "mes_sdegas"
CONF_MES_SMAKEUPVALVE = "mes_smakeupvalve"
CONF_MES_SOVERFLOW1 = "mes_soverflow1"
CONF_MES_SOVERFLOW2 = "mes_soverflow2"
CONF_MES_SPUMP1ON = "mes_spump1on"
CONF_MES_SPUMP2ON = "mes_spump2on"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(ReflexComponent),

    cv.Optional(CONF_TYPE_SERIAL):
        text_sensor.text_sensor_schema(icon="mdi:numeric", entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_TYPE_VERSION):
        text_sensor.text_sensor_schema(icon="mdi:application-variable-outline", entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_TYPE_CONTROLLER):
        text_sensor.text_sensor_schema(icon="mdi:cpu-64-bit", entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_TYPE_TYPE):
        text_sensor.text_sensor_schema(icon="mdi:water-boiler", entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_TYPE_LEVELCONTROL):
        binary_sensor.binary_sensor_schema(icon="mdi:waves-arrow-up", entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),

    cv.Optional(CONF_PARA_PRESSUREP0):
       sensor.sensor_schema(icon="mdi:gauge", device_class=DEVICE_CLASS_PRESSURE,unit_of_measurement='bar',accuracy_decimals=2,state_class=STATE_CLASS_MEASUREMENT, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_PARA_PARAPRESSUREMAX):
       sensor.sensor_schema(icon="mdi:gauge-full", device_class=DEVICE_CLASS_PRESSURE,unit_of_measurement='bar',accuracy_decimals=2,state_class=STATE_CLASS_MEASUREMENT, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_PARA_PARACONDUCTIVITYMAX):
       sensor.sensor_schema(icon="mdi:waves-arrow-left", unit_of_measurement='µS/cm',state_class=STATE_CLASS_MEASUREMENT, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_PARA_PARAPRESSURENSP):
       sensor.sensor_schema(icon="mdi:gauge", device_class=DEVICE_CLASS_PRESSURE,unit_of_measurement='bar',accuracy_decimals=2,state_class=STATE_CLASS_MEASUREMENT, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_PARA_PARAPRESSURESSV):
       sensor.sensor_schema(icon="mdi:gauge", device_class=DEVICE_CLASS_PRESSURE,unit_of_measurement='bar',accuracy_decimals=2,state_class=STATE_CLASS_MEASUREMENT, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_PARA_PARAPRESSUREPF):
       sensor.sensor_schema(icon="mdi:gauge", device_class=DEVICE_CLASS_PRESSURE,unit_of_measurement='bar',accuracy_decimals=2,state_class=STATE_CLASS_MEASUREMENT, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_PARA_PARAWATERLEVELON):
       sensor.sensor_schema(icon="mdi:toggle-switch-variant", unit_of_measurement='%',state_class=STATE_CLASS_MEASUREMENT, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_PARA_PARAWATERLEVELOFF):
       sensor.sensor_schema(icon="mdi:toggle-switch-variant-off", unit_of_measurement='%',state_class=STATE_CLASS_MEASUREMENT, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_PARA_PARAFILLON):
       sensor.sensor_schema(icon="mdi:toggle-switch-variant", unit_of_measurement='%',state_class=STATE_CLASS_MEASUREMENT, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_PARA_PARAFILLOFF):
       sensor.sensor_schema(icon="mdi:toggle-switch-variant-off", unit_of_measurement='%',state_class=STATE_CLASS_MEASUREMENT, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_PARA_PARAMAXFILLVOLUME):
       sensor.sensor_schema(icon="mdi:waves", device_class=DEVICE_CLASS_VOLUME,unit_of_measurement='L',accuracy_decimals=2,state_class=STATE_CLASS_MEASUREMENT, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_PARA_PARAMAXFILLCYCLES):
       sensor.sensor_schema(icon="mdi:numeric", state_class=STATE_CLASS_MEASUREMENT, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_PARA_PARAMAXFILLTIME):
       sensor.sensor_schema(icon="mdi:numeric", unit_of_measurement='m',accuracy_decimals=2,state_class=STATE_CLASS_MEASUREMENT, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_PARA_PARAMAXFILLIMPULSE):
       sensor.sensor_schema(icon="mdi:numeric", device_class=DEVICE_CLASS_PRESSURE,accuracy_decimals=2,state_class=STATE_CLASS_MEASUREMENT, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_PARA_PARASCUSTOMER):
       binary_sensor.binary_sensor_schema(entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_PARA_PARASSERVICE):
       binary_sensor.binary_sensor_schema(entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_PARA_PARASRO):
       binary_sensor.binary_sensor_schema(entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_PARA_PARASPARAMETER):
       binary_sensor.binary_sensor_schema(entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_PARA_PARACONTAINERSIZE):
       sensor.sensor_schema(device_class=DEVICE_CLASS_VOLUME,unit_of_measurement='L',accuracy_decimals=2,state_class=STATE_CLASS_MEASUREMENT, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_PARA_PARACONTAINERWEIGHT):
       sensor.sensor_schema(device_class=DEVICE_CLASS_CURRENT,unit_of_measurement='mA',accuracy_decimals=2,state_class=STATE_CLASS_MEASUREMENT, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_PARA_PARACONTAINERDIFFERENZ):
       sensor.sensor_schema(device_class=DEVICE_CLASS_CURRENT,unit_of_measurement='mA',accuracy_decimals=2,state_class=STATE_CLASS_MEASUREMENT, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_PARA_PARAMAINTENANCE):
       sensor.sensor_schema(icon="mdi:calendar-clock", unit_of_measurement='m',state_class=STATE_CLASS_MEASUREMENT).extend(),
    cv.Optional(CONF_PARA_PARAHIGHWATER):
       sensor.sensor_schema(icon="mdi:gauge", unit_of_measurement='%',state_class=STATE_CLASS_MEASUREMENT, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_PARA_PARADESCALER):
       sensor.sensor_schema(icon="mdi:calendar-clock", unit_of_measurement='m',state_class=STATE_CLASS_MEASUREMENT).extend(),
    cv.Optional(CONF_PARA_PARADESCALERREMAINING):
       sensor.sensor_schema(icon="mdi:numeric", device_class=DEVICE_CLASS_VOLUME,unit_of_measurement='L',state_class=STATE_CLASS_MEASUREMENT, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_PARA_PARAPROGRAMM):
       text_sensor.text_sensor_schema(icon="mdi:application-cog-outline", entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),

    cv.Optional(CONF_MES_PRESSURE):
       sensor.sensor_schema(icon="mdi:gauge", device_class=DEVICE_CLASS_PRESSURE,unit_of_measurement='bar',accuracy_decimals=2,state_class=STATE_CLASS_MEASUREMENT).extend(),
    cv.Optional(CONF_MES_LEVEL):
       sensor.sensor_schema(icon="mdi:gauge", unit_of_measurement='%',state_class=STATE_CLASS_MEASUREMENT).extend(),
    cv.Optional(CONF_MES_HOURSPUMP1):
       sensor.sensor_schema(icon="mdi:hours-24", unit_of_measurement='h',state_class=STATE_CLASS_MEASUREMENT).extend(),
    cv.Optional(CONF_MES_HOURSPUMP2):
       sensor.sensor_schema(icon="mdi:hours-24", unit_of_measurement='h',state_class=STATE_CLASS_MEASUREMENT).extend(),
    cv.Optional(CONF_MES_WATERMETER):
       sensor.sensor_schema(device_class=DEVICE_CLASS_VOLUME, unit_of_measurement='L',state_class=STATE_CLASS_MEASUREMENT).extend(),
    cv.Optional(CONF_MES_PVALVE1):
       sensor.sensor_schema(icon="mdi:valve", unit_of_measurement='%',state_class=STATE_CLASS_MEASUREMENT).extend(),
    cv.Optional(CONF_MES_PVALVE2):
       sensor.sensor_schema(icon="mdi:valve", unit_of_measurement='%',state_class=STATE_CLASS_MEASUREMENT).extend(),
    cv.Optional(CONF_MES_CONDUCTIVITY):
       sensor.sensor_schema(icon="mdi:waves-arrow-left", unit_of_measurement='µS/cm',state_class=STATE_CLASS_MEASUREMENT).extend(),
    cv.Optional(CONF_MES_SMODUS):
       text_sensor.text_sensor_schema(icon="mdi:application-cog-outline").extend(),
    cv.Optional(CONF_MES_RPUMP2ON):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PLUG, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_RPUMP1ON):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PLUG, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_ROVERFLOW2OPEN):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PLUG, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_ROVERFLOW1OPEN):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PLUG, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_RMAKEUPOPEN):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PLUG, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_RMINLEVEL):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PLUG, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_RERROR):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PLUG, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_DPUMP1):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_RUNNING, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_DPUMP2):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_RUNNING, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_DLACKOFWATER):
        binary_sensor.binary_sensor_schema(entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_DWATERMETER):
        binary_sensor.binary_sensor_schema(entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_DSOFTSTART):
        binary_sensor.binary_sensor_schema(entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_E2MAINBOARD):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_E2DIGITALV):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_E2ANALOGV):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_E2VALVE1):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_E2VALVE2):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_E2JPRESSURE):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_E2JLEVEL):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_E2DRYRUN):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_E2LACKOFWATER3):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_E2LACKOFWATER4):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_E2LFSENSOR):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_E1EXTENSIONMODULE):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_E1EEPROM):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_E1UNDERVOLTAGE):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_E1MINPRESSURE):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_E1LACKOFWATER1):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_E1PUMP1):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_E1COMPRESSOR1):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_E1PUMP2):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_E1COMPRESSOR2):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_E1PRESSURESENSOR):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_E1LEVELSENSOR):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_E1PRESSURESENSORPIPE):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_E1STO4H):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_E1LACKOFWATER2):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_E1EEPROM2):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_W2BATTERY):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_W2DESCALECHANGE):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM).extend(),
    cv.Optional(CONF_MES_W2DATALOGGER):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_W2BUSMODULE):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_W2STOP4H):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_W2CONDUCTIVITY):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_W1MAXLEVEL):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_W1PUMPRUNTIME):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_W1MAKEUPTIME):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_W1MAEKUPCYCLES):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_W1MAXPRESSURE):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_W1MAKEUPVOLUME):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_W1EXPULSIONTIME):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_W1FILLTIME):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_W1FILLVOLUME):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_W1MAKEUPVALVE):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_W1VOLTAGE):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_W1ZEROLEVEL):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_W1PARAMETER):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_W1MAXMAKEUPVOLUME):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM, entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_W1MAINTENANCE):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM).extend(),
    cv.Optional(CONF_MES_SMANUAL):
        binary_sensor.binary_sensor_schema(entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_SSTOP):
        binary_sensor.binary_sensor_schema(entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_SAUTO):
        binary_sensor.binary_sensor_schema(entity_category=ENTITY_CATEGORY_DIAGNOSTIC).extend(),
    cv.Optional(CONF_MES_SPUMP1):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_RUNNING).extend(),
    cv.Optional(CONF_MES_SPUMP2):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_RUNNING).extend(),
    cv.Optional(CONF_MES_SERROR):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_PROBLEM).extend(),
    cv.Optional(CONF_MES_SWATERLEVEL):
        binary_sensor.binary_sensor_schema().extend(),
    cv.Optional(CONF_MES_SDEGAS):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_RUNNING).extend(),
    cv.Optional(CONF_MES_SMAKEUPVALVE):
        binary_sensor.binary_sensor_schema().extend(),
    cv.Optional(CONF_MES_SOVERFLOW1):
        binary_sensor.binary_sensor_schema().extend(),
    cv.Optional(CONF_MES_SOVERFLOW2):
        binary_sensor.binary_sensor_schema().extend(),
    cv.Optional(CONF_MES_SPUMP1ON):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_RUNNING).extend(),
    cv.Optional(CONF_MES_SPUMP2ON):
        binary_sensor.binary_sensor_schema(device_class=DEVICE_CLASS_RUNNING).extend(),

}).extend(cv.polling_component_schema('60s')).extend(uart.UART_DEVICE_SCHEMA)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield uart.register_uart_device(var, config)

    if CONF_TYPE_SERIAL in config:
        conf = config[CONF_TYPE_SERIAL]
        sens = yield text_sensor.new_text_sensor(conf)
        cg.add(var.set_typeserial_sensor(sens))

    if CONF_TYPE_VERSION in config:
        conf = config[CONF_TYPE_VERSION]
        sens = yield text_sensor.new_text_sensor(conf)
        cg.add(var.set_typeversion_sensor(sens))

    if CONF_TYPE_CONTROLLER in config:
        conf = config[CONF_TYPE_CONTROLLER]
        sens = yield text_sensor.new_text_sensor(conf)
        cg.add(var.set_typecontroller_sensor(sens))
    
    if CONF_TYPE_TYPE in config:
        conf = config[CONF_TYPE_TYPE]
        sens = yield text_sensor.new_text_sensor(conf)
        cg.add(var.set_typetype_sensor(sens))

    if CONF_TYPE_LEVELCONTROL in config:
        conf = config[CONF_TYPE_LEVELCONTROL]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_typelevelcontrol_sensor(sens))

    if CONF_PARA_PRESSUREP0  in config:
        conf = config[CONF_PARA_PRESSUREP0 ]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_parapressurep0_sensor(sens))

    if CONF_PARA_PARAPRESSUREMAX  in config:
        conf = config[CONF_PARA_PARAPRESSUREMAX ]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_parapressuremax_sensor(sens))

    if CONF_PARA_PARACONDUCTIVITYMAX  in config:
        conf = config[CONF_PARA_PARACONDUCTIVITYMAX ]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_paraconductivitymax_sensor(sens))

    if CONF_PARA_PARAPRESSURENSP  in config:
        conf = config[CONF_PARA_PARAPRESSURENSP ]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_parapressurensp_sensor(sens))

    if CONF_PARA_PARAPRESSURESSV  in config:
        conf = config[CONF_PARA_PARAPRESSURESSV ]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_parapressuressv_sensor(sens))

    if CONF_PARA_PARAPRESSUREPF  in config:
        conf = config[CONF_PARA_PARAPRESSUREPF ]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_parapressurepf_sensor(sens))

    if CONF_PARA_PARAWATERLEVELON  in config:
        conf = config[CONF_PARA_PARAWATERLEVELON ]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_parawaterlevelon_sensor(sens))

    if CONF_PARA_PARAWATERLEVELOFF  in config:
        conf = config[CONF_PARA_PARAWATERLEVELOFF ]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_parawaterleveloff_sensor(sens))

    if CONF_PARA_PARAFILLON  in config:
        conf = config[CONF_PARA_PARAFILLON ]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_parafillon_sensor(sens))

    if CONF_PARA_PARAFILLOFF  in config:
        conf = config[CONF_PARA_PARAFILLOFF ]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_parafilloff_sensor(sens))

    if CONF_PARA_PARAMAXFILLVOLUME  in config:
        conf = config[CONF_PARA_PARAMAXFILLVOLUME ]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_paramaxfillvolume_sensor(sens))

    if CONF_PARA_PARAMAXFILLCYCLES  in config:
        conf = config[CONF_PARA_PARAMAXFILLCYCLES ]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_paramaxfillcycles_sensor(sens))

    if CONF_PARA_PARAMAXFILLTIME  in config:
        conf = config[CONF_PARA_PARAMAXFILLTIME ]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_paramaxfilltime_sensor(sens))

    if CONF_PARA_PARAMAXFILLIMPULSE  in config:
        conf = config[CONF_PARA_PARAMAXFILLIMPULSE ]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_paramaxfillimpulse_sensor(sens))

    if CONF_PARA_PARASCUSTOMER  in config:
        conf = config[CONF_PARA_PARASCUSTOMER ]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_parascustomer_sensor(sens))

    if CONF_PARA_PARASSERVICE  in config:
        conf = config[CONF_PARA_PARASSERVICE ]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_parasservice_sensor(sens))

    if CONF_PARA_PARASRO  in config:
        conf = config[CONF_PARA_PARASRO ]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_parasro_sensor(sens))

    if CONF_PARA_PARASPARAMETER  in config:
        conf = config[CONF_PARA_PARASPARAMETER ]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_parasparameter_sensor(sens))

    if CONF_PARA_PARACONTAINERSIZE  in config:
        conf = config[CONF_PARA_PARACONTAINERSIZE ]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_paracontainersize_sensor(sens))

    if CONF_PARA_PARACONTAINERWEIGHT  in config:
        conf = config[CONF_PARA_PARACONTAINERWEIGHT ]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_paracontainerweight_sensor(sens))

    if CONF_PARA_PARACONTAINERDIFFERENZ  in config:
        conf = config[CONF_PARA_PARACONTAINERDIFFERENZ ]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_paracontainerdifferenz_sensor(sens))

    if CONF_PARA_PARAMAINTENANCE  in config:
        conf = config[CONF_PARA_PARAMAINTENANCE ]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_paramaintenance_sensor(sens))

    if CONF_PARA_PARAHIGHWATER  in config:
        conf = config[CONF_PARA_PARAHIGHWATER ]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_parahighwater_sensor(sens))

    if CONF_PARA_PARADESCALER  in config:
        conf = config[CONF_PARA_PARADESCALER ]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_paradescaler_sensor(sens))

    if CONF_PARA_PARADESCALERREMAINING  in config:
        conf = config[CONF_PARA_PARADESCALERREMAINING ]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_paradescalerremaining_sensor(sens))

    if CONF_PARA_PARAPROGRAMM  in config:
        conf = config[CONF_PARA_PARAPROGRAMM ]
        sens = yield text_sensor.new_text_sensor(conf)
        cg.add(var.set_paraprogramm_sensor(sens))

    if CONF_MES_PRESSURE  in config:
        conf = config[CONF_MES_PRESSURE]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_mespressure_sensor(sens))

    if CONF_MES_LEVEL  in config:
        conf = config[CONF_MES_LEVEL]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_meslevel_sensor(sens))

    if CONF_MES_HOURSPUMP1  in config:
        conf = config[CONF_MES_HOURSPUMP1]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_meshourspump1_sensor(sens))

    if CONF_MES_HOURSPUMP2  in config:
        conf = config[CONF_MES_HOURSPUMP2]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_meshourspump2_sensor(sens))

    if CONF_MES_WATERMETER  in config:
        conf = config[CONF_MES_WATERMETER]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_meswatermeter_sensor(sens))

    if CONF_MES_PVALVE1  in config:
        conf = config[CONF_MES_PVALVE1]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_mespvalve1_sensor(sens))

    if CONF_MES_PVALVE2  in config:
        conf = config[CONF_MES_PVALVE2]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_mespvalve2_sensor(sens))

    if CONF_MES_CONDUCTIVITY  in config:
        conf = config[CONF_MES_CONDUCTIVITY]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_mesconductivity_sensor(sens))

    if CONF_MES_SMODUS  in config:
        conf = config[CONF_MES_SMODUS]
        sens = yield text_sensor.new_text_sensor(conf)
        cg.add(var.set_messmodus_sensor(sens))

    if CONF_MES_RPUMP2ON in config:
        conf = config[CONF_MES_RPUMP2ON]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mesrpump2on_sensor(sens))

    if CONF_MES_RPUMP1ON in config:
        conf = config[CONF_MES_RPUMP1ON]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mesrpump1on_sensor(sens))

    if CONF_MES_ROVERFLOW2OPEN in config:
        conf = config[CONF_MES_ROVERFLOW2OPEN]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mesroverflow2open_sensor(sens))

    if CONF_MES_ROVERFLOW1OPEN in config:
        conf = config[CONF_MES_ROVERFLOW1OPEN]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mesroverflow1open_sensor(sens))

    if CONF_MES_RMAKEUPOPEN in config:
        conf = config[CONF_MES_RMAKEUPOPEN]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mesrmakeupopen_sensor(sens))

    if CONF_MES_RMINLEVEL in config:
        conf = config[CONF_MES_RMINLEVEL]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mesrminlevel_sensor(sens))

    if CONF_MES_RERROR in config:
        conf = config[CONF_MES_RERROR]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mesrerror_sensor(sens))

    if CONF_MES_DPUMP1 in config:
        conf = config[CONF_MES_DPUMP1]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mesdpump1_sensor(sens))

    if CONF_MES_DPUMP2 in config:
        conf = config[CONF_MES_DPUMP2]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mesdpump2_sensor(sens))

    if CONF_MES_DLACKOFWATER in config:
        conf = config[CONF_MES_DLACKOFWATER]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mesdlackofwater_sensor(sens))

    if CONF_MES_DWATERMETER in config:
        conf = config[CONF_MES_DWATERMETER]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mesdwatermeter_sensor(sens))

    if CONF_MES_DSOFTSTART in config:
        conf = config[CONF_MES_DSOFTSTART]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mesdsoftstart_sensor(sens))

    if CONF_MES_E2MAINBOARD in config:
        conf = config[CONF_MES_E2MAINBOARD]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mese2mainboard_sensor(sens))

    if CONF_MES_E2DIGITALV in config:
        conf = config[CONF_MES_E2DIGITALV]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mese2digitalv_sensor(sens))

    if CONF_MES_E2ANALOGV in config:
        conf = config[CONF_MES_E2ANALOGV]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mese2analogv_sensor(sens))

    if CONF_MES_E2VALVE1 in config:
        conf = config[CONF_MES_E2VALVE1]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mese2valve1_sensor(sens))

    if CONF_MES_E2VALVE2 in config:
        conf = config[CONF_MES_E2VALVE2]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mese2valve2_sensor(sens))

    if CONF_MES_E2JPRESSURE in config:
        conf = config[CONF_MES_E2JPRESSURE]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mese2jpressure_sensor(sens))

    if CONF_MES_E2JLEVEL in config:
        conf = config[CONF_MES_E2JLEVEL]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mese2jlevel_sensor(sens))

    if CONF_MES_E2DRYRUN in config:
        conf = config[CONF_MES_E2DRYRUN]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mese2dryrun_sensor(sens))

    if CONF_MES_E2LACKOFWATER3 in config:
        conf = config[CONF_MES_E2LACKOFWATER3]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mese2lackofwater3_sensor(sens))

    if CONF_MES_E2LACKOFWATER4 in config:
        conf = config[CONF_MES_E2LACKOFWATER4]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mese2lackofwater4_sensor(sens))

    if CONF_MES_E2LFSENSOR in config:
        conf = config[CONF_MES_E2LFSENSOR]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mese2lfsensor_sensor(sens))

    if CONF_MES_E1EXTENSIONMODULE in config:
        conf = config[CONF_MES_E1EXTENSIONMODULE]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mese1extensionmodule_sensor(sens))

    if CONF_MES_E1EEPROM in config:
        conf = config[CONF_MES_E1EEPROM]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mese1eeprom_sensor(sens))

    if CONF_MES_E1UNDERVOLTAGE in config:
        conf = config[CONF_MES_E1UNDERVOLTAGE]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mese1undervoltage_sensor(sens))

    if CONF_MES_E1MINPRESSURE in config:
        conf = config[CONF_MES_E1MINPRESSURE]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mese1minpressure_sensor(sens))

    if CONF_MES_E1LACKOFWATER1 in config:
        conf = config[CONF_MES_E1LACKOFWATER1]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mese1lackofwater1_sensor(sens))

    if CONF_MES_E1PUMP1 in config:
        conf = config[CONF_MES_E1PUMP1]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mese1pump1_sensor(sens))

    if CONF_MES_E1COMPRESSOR1 in config:
        conf = config[CONF_MES_E1COMPRESSOR1]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mese1compressor1_sensor(sens))

    if CONF_MES_E1PUMP2 in config:
        conf = config[CONF_MES_E1PUMP2]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mese1pump2_sensor(sens))

    if CONF_MES_E1COMPRESSOR2 in config:
        conf = config[CONF_MES_E1COMPRESSOR2]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mese1compressor2_sensor(sens))

    if CONF_MES_E1PRESSURESENSOR in config:
        conf = config[CONF_MES_E1PRESSURESENSOR]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mese1pressuresensor_sensor(sens))

    if CONF_MES_E1LEVELSENSOR in config:
        conf = config[CONF_MES_E1LEVELSENSOR]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mese1levelsensor_sensor(sens))

    if CONF_MES_E1PRESSURESENSORPIPE in config:
        conf = config[CONF_MES_E1PRESSURESENSORPIPE]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mese1pressuresensorpipe_sensor(sens))

    if CONF_MES_E1STO4H in config:
        conf = config[CONF_MES_E1STO4H]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mese1sto4h_sensor(sens))

    if CONF_MES_E1LACKOFWATER2 in config:
        conf = config[CONF_MES_E1LACKOFWATER2]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mese1lackofwater2_sensor(sens))

    if CONF_MES_E1EEPROM2 in config:
        conf = config[CONF_MES_E1EEPROM2]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mese1eeprom2_sensor(sens))

    if CONF_MES_W2BATTERY in config:
        conf = config[CONF_MES_W2BATTERY]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mesw2battery_sensor(sens))

    if CONF_MES_W2DESCALECHANGE in config:
        conf = config[CONF_MES_W2DESCALECHANGE]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mesw2descalechange_sensor(sens))

    if CONF_MES_W2DATALOGGER in config:
        conf = config[CONF_MES_W2DATALOGGER]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mesw2datalogger_sensor(sens))

    if CONF_MES_W2BUSMODULE in config:
        conf = config[CONF_MES_W2BUSMODULE]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mesw2busmodule_sensor(sens))

    if CONF_MES_W2STOP4H in config:
        conf = config[CONF_MES_W2STOP4H]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mesw2stop4h_sensor(sens))

    if CONF_MES_W2CONDUCTIVITY in config:
        conf = config[CONF_MES_W2CONDUCTIVITY]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mesw2conductivity_sensor(sens))

    if CONF_MES_W1MAXLEVEL in config:
        conf = config[CONF_MES_W1MAXLEVEL]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mesw1maxlevel_sensor(sens))

    if CONF_MES_W1PUMPRUNTIME in config:
        conf = config[CONF_MES_W1PUMPRUNTIME]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mesw1pumpruntime_sensor(sens))

    if CONF_MES_W1MAKEUPTIME in config:
        conf = config[CONF_MES_W1MAKEUPTIME]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mesw1makeuptime_sensor(sens))

    if CONF_MES_W1MAEKUPCYCLES in config:
        conf = config[CONF_MES_W1MAEKUPCYCLES]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mesw1maekupcycles_sensor(sens))

    if CONF_MES_W1MAXPRESSURE in config:
        conf = config[CONF_MES_W1MAXPRESSURE]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mesw1maxpressure_sensor(sens))

    if CONF_MES_W1MAKEUPVOLUME in config:
        conf = config[CONF_MES_W1MAKEUPVOLUME]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mesw1makeupvolume_sensor(sens))

    if CONF_MES_W1EXPULSIONTIME in config:
        conf = config[CONF_MES_W1EXPULSIONTIME]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mesw1expulsiontime_sensor(sens))

    if CONF_MES_W1FILLTIME in config:
        conf = config[CONF_MES_W1FILLTIME]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mesw1filltime_sensor(sens))

    if CONF_MES_W1FILLVOLUME in config:
        conf = config[CONF_MES_W1FILLVOLUME]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mesw1fillvolume_sensor(sens))

    if CONF_MES_W1MAKEUPVALVE in config:
        conf = config[CONF_MES_W1MAKEUPVALVE]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mesw1makeupvalve_sensor(sens))

    if CONF_MES_W1VOLTAGE in config:
        conf = config[CONF_MES_W1VOLTAGE]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mesw1voltage_sensor(sens))

    if CONF_MES_W1ZEROLEVEL in config:
        conf = config[CONF_MES_W1ZEROLEVEL]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mesw1zerolevel_sensor(sens))

    if CONF_MES_W1PARAMETER in config:
        conf = config[CONF_MES_W1PARAMETER]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mesw1parameter_sensor(sens))

    if CONF_MES_W1MAXMAKEUPVOLUME in config:
        conf = config[CONF_MES_W1MAXMAKEUPVOLUME]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mesw1maxmakeupvolume_sensor(sens))

    if CONF_MES_W1MAINTENANCE in config:
        conf = config[CONF_MES_W1MAINTENANCE]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_mesw1maintenance_sensor(sens))

    if CONF_MES_SMANUAL in config:
        conf = config[CONF_MES_SMANUAL]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_messmanual_sensor(sens))

    if CONF_MES_SSTOP in config:
        conf = config[CONF_MES_SSTOP]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_messstop_sensor(sens))

    if CONF_MES_SAUTO in config:
        conf = config[CONF_MES_SAUTO]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_messauto_sensor(sens))

    if CONF_MES_SPUMP1 in config:
        conf = config[CONF_MES_SPUMP1]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_messpump1_sensor(sens))

    if CONF_MES_SPUMP2 in config:
        conf = config[CONF_MES_SPUMP2]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_messpump2_sensor(sens))

    if CONF_MES_SERROR in config:
        conf = config[CONF_MES_SERROR]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_messerror_sensor(sens))

    if CONF_MES_SWATERLEVEL in config:
        conf = config[CONF_MES_SWATERLEVEL]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_messwaterlevel_sensor(sens))

    if CONF_MES_SDEGAS in config:
        conf = config[CONF_MES_SDEGAS]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_messdegas_sensor(sens))

    if CONF_MES_SMAKEUPVALVE in config:
        conf = config[CONF_MES_SMAKEUPVALVE]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_messmakeupvalve_sensor(sens))

    if CONF_MES_SOVERFLOW1 in config:
        conf = config[CONF_MES_SOVERFLOW1]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_messoverflow1_sensor(sens))

    if CONF_MES_SOVERFLOW2 in config:
        conf = config[CONF_MES_SOVERFLOW2]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_messoverflow2_sensor(sens))

    if CONF_MES_SPUMP1ON in config:
        conf = config[CONF_MES_SPUMP1ON]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_messpump1on_sensor(sens))

    if CONF_MES_SPUMP2ON in config:
        conf = config[CONF_MES_SPUMP2ON]
        sens = yield binary_sensor.new_binary_sensor(conf)
        cg.add(var.set_messpump2on_sensor(sens))
