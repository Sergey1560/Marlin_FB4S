#include "mks_wifi_gcodes.h"

const uint8_t pak[5]={0xA5,0x07,0x00,0x00,0xFC};

const char m997_idle[]="M997 IDLE\n";
const char m997_printing[]="M997 PRINTING\n";
const char m997_pause[]="M997 PAUSE\n";

const char m115_firmware[]="FIRMWARE_NAME:TFT24\n";

void mks_m991(void){
  char tempBuf[100];
  const int8_t target_extruder = GcodeSuite::get_target_extruder_from_command();
  if (target_extruder < 0) return;

  memset(tempBuf,0,100);

  sprintf((char *)tempBuf,"T:%d /%d B:%d /%d T0:%d /%d T1:0 /0 @:0 B@:0\n", 
  (int)Temperature::degHotend(target_extruder),Temperature::degTargetHotend(target_extruder),
  (int)Temperature::degBed(),Temperature::degTargetBed(),
  (int)Temperature::degHotend(target_extruder),Temperature::degTargetHotend(target_extruder));

  mks_wifi_out_add((uint8_t *)tempBuf,strlen(tempBuf));
}

void mks_m105(void){
  char tempBuf[100];
  const int8_t target_extruder = GcodeSuite::get_target_extruder_from_command();
  if (target_extruder < 0) return;

  memset(tempBuf,0,100);

  SERIAL_ECHOPGM(STR_OK);
  SERIAL_EOL();

  sprintf((char *)tempBuf,"T:%.1f /%.1f B:%.1f /%.1f T0:%.1f /%.1f T1:0.0 /0.0 @:0 B@:0\n",
  Temperature::degHotend(target_extruder),(float)Temperature::degTargetHotend(target_extruder),
  Temperature::degBed(),(float)Temperature::degTargetBed(),
  Temperature::degHotend(target_extruder),(float)Temperature::degTargetHotend(target_extruder));

  mks_wifi_out_add((uint8_t *)tempBuf,strlen(tempBuf));
}



void mks_m997(void){
  static uint8_t call_cnt=0;

  if(CardReader::isPrinting()){
    mks_wifi_out_add((uint8_t *)m997_printing,strlen(m997_printing));
  }else if(CardReader::isPaused()){
    mks_wifi_out_add((uint8_t *)m997_pause,strlen(m997_pause));
  }else{
    mks_wifi_out_add((uint8_t *)m997_idle,strlen(m997_idle));
  }

  if(call_cnt == 0){
      call_cnt=1;
    	mks_wifi_send((uint8_t *)pak, 4); //Внутри +1
  }

}


void mks_m115(void){
  SERIAL_ECHOPGM(STR_OK);
  SERIAL_EOL();
  mks_wifi_out_add((uint8_t *)m115_firmware,strlen(m115_firmware));
}

void mks_m27(void){

  if (CardReader::isPrinting()) {
    SERIAL_ECHOPGM(STR_SD_PRINTING_BYTE);
    SERIAL_ECHO(0);
    SERIAL_CHAR('/');
    SERIAL_ECHOLN(100);
  }
}

void mks_m30(char *filename){
  
  filename[0]='0';
  DEBUG("M30: %s",filename);
  sd_delete_file(filename);

}