#include "mks_wifi_gcodes.h"

const char m997_idle[]="M997 IDLE\n";
const char m997_printing[]="M997 PRINTING\n";
const char m997_pause[]="M997 PAUSE\n";

void mks_m991(void){

  const int8_t target_extruder = GcodeSuite::get_target_extruder_from_command();
  if (target_extruder < 0) return;

  #if HAS_TEMP_SENSOR

    thermalManager.print_heater_states(target_extruder
      #if ENABLED(TEMP_SENSOR_1_AS_REDUNDANT)
        , parser.boolval('R')
      #endif
    );

    SERIAL_EOL();

  #else

    SERIAL_ECHOLNPGM(" T:0"); // Some hosts send M105 to test the serial connection

  #endif
}


void mks_m997(void){

  if(CardReader::isPrinting()){
    mks_wifi_out_add((uint8_t *)m997_printing,strlen(m997_printing));
  }else if(CardReader::isPaused()){
    mks_wifi_out_add((uint8_t *)m997_pause,strlen(m997_pause));
  }else{
    mks_wifi_out_add((uint8_t *)m997_idle,strlen(m997_idle));
  }

}