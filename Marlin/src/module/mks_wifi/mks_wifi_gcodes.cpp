#include "mks_wifi_gcodes.h"
#ifdef MKS_WIFI
#include "../../module/printcounter.h"
#include "../../libs/duration_t.h"



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

  SERIAL_ECHOPGM(STR_OK);
  SERIAL_EOL();
}

void mks_m105(void){
  char tempBuf[100];
  const int8_t target_extruder = GcodeSuite::get_target_extruder_from_command();
  if (target_extruder < 0) return;

  memset(tempBuf,0,100);

  sprintf((char *)tempBuf,"T:%.1f /%.1f B:%.1f /%.1f T0:%.1f /%.1f T1:0.0 /0.0 @:0 B@:0\n",
  Temperature::degHotend(target_extruder),(float)Temperature::degTargetHotend(target_extruder),
  Temperature::degBed(),(float)Temperature::degTargetBed(),
  Temperature::degHotend(target_extruder),(float)Temperature::degTargetHotend(target_extruder));

  mks_wifi_out_add((uint8_t *)tempBuf,strlen(tempBuf));

  SERIAL_ECHOPGM(STR_OK);
  SERIAL_EOL();

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


void mks_m115(void){
  mks_wifi_out_add((uint8_t *)m115_firmware,strlen(m115_firmware));
}


void mks_m992(void){
  char buffer[30];
  uint32_t duration_sec = print_job_timer.duration();
  uint16_t hours = duration_sec / 3600;
  uint16_t minutes = (duration_sec - hours*3600) / 60;
  uint16_t seconds = (duration_sec - hours*3600 - minutes*60);

  if(CardReader::isPrinting()){
    sprintf((char *)buffer, "M992 %02d:%02d:%02d\r\n", hours, minutes, seconds);
    mks_wifi_out_add((uint8_t *)buffer,strlen(buffer));
  };
}

void mks_m994(void){
  char buffer[150];
  char filename[101];

  if(CardReader::isPrinting()){
    CardReader::GetSelectedFilename(filename);
    sprintf((char *)buffer, ("M994 %s;%ld\n"), filename, CardReader::GetSelectedFilesize());
    mks_wifi_out_add((uint8_t *)buffer,strlen(buffer));
  }
  
}


void mks_m27(void){

  // if (CardReader::isPrinting()) {
  //   SERIAL_ECHOPGM(STR_SD_PRINTING_BYTE);
  //   SERIAL_ECHO(0);
  //   SERIAL_CHAR('/');
  //   SERIAL_ECHOLN(100);
  
  //   SERIAL_ECHOPGM(STR_OK);
  //   SERIAL_EOL();

  // }
}

void mks_m30(char *filename){
  
  filename[0]='0';
  DEBUG("M30: %s",filename);
  sd_delete_file(filename);

  SERIAL_ECHOPGM(STR_OK);
  SERIAL_EOL();

}

void mks_m23(char *filename){
    char dosfilename[14];
    uint8_t dot_pos;

    DEBUG("M23: %s",filename);

    if(filename[0] == '/'){
      DEBUG("Strip slash");
      for(uint32_t i = 0; i < strlen(filename) ; i++){
        filename[i] = filename[i+1];
      }
      DEBUG("Fixed name: %s",filename);
    }

    //Имя файла может быть меньше 12 символов, но с расширением .gcode
    //С конца имени файла шагаем к началу, считаем сколько символов до точки
    dot_pos=0;
    for (char *fn = (filename+strlen(filename) - 1); fn > filename; --fn){
      dot_pos++;  
      if (*fn == '.') break;
    }
   
    if((strlen(filename) > 12) || (dot_pos > 4)){
      DEBUG("Long file name");
      if(get_dos_filename(filename,dosfilename)){
        strcpy(CardReader::longFilename,filename); //Для отображения на экране
        DEBUG("DOS file name: %s",dosfilename);
        card.openFileRead(dosfilename);
    }else{
      ERROR("Can't find dos file name");
    }

    }else{
      DEBUG("DOS file name");
      card.openFileRead(filename);
    }

  SERIAL_ECHOPGM(STR_OK);
  SERIAL_EOL();

}

#endif
