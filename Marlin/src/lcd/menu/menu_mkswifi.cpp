
//
// MKS WIFI config Menu
//

#include "../../inc/MarlinConfigPre.h"

#if HAS_MARLINUI_MENU && ENABLED(MENU_ENABLE_MKS_WIFI)

#include "../../lcd/tft/tft_string.h"
#include "../../lcd/tft/touch.h"
#include "../../lcd/tft/tft.h"
#include "../../lcd/tft/ui_480x320.h"

#include "menu_item.h"
#include "menu_addon.h"

#include "../../MarlinCore.h"

#if HAS_FILAMENT_SENSOR
  #include "../../feature/runout.h"
#endif

#if HAS_FANCHECK
  #include "../../feature/fancheck.h"
#endif

#if ENABLED(POWER_LOSS_RECOVERY)
  #include "../../feature/powerloss.h"
#endif

#if HAS_BED_PROBE
  #include "../../module/probe.h"
  #if ENABLED(BLTOUCH)
    #include "../../feature/bltouch.h"
  #endif
#endif

#if ENABLED(SOUND_MENU_ITEM)
  #include "../../libs/buzzer.h"
#endif

#include "../../core/debug_out.h"

#include "../../module/mks_wifi/mks_wifi.h"


uint8_t net_prev_state = ESP_NET_WIFI_FAIL;
uint8_t net_prev_wifi_namelen = 0;
uint8_t curr_connecting_net_idx = 0;
char entered_pass[65];
int curr_pass_idx = 0;
char touch_char = '?';
const char keyboard_row0_shift[] =        "   1  2  3  4  5  6  7  8  9  0  +  | ";
const char keyboard_row1_shift[] =        "   Q  W  E  R  T  Y  U  I  O  P  [  ] ";
const char keyboard_row2_shift[] =        "   A  S  D  F  G  H  J  K  L  :  '  \" ";
const char keyboard_row3_shift[] =        "   Z  X  C  V  B  N  M  ,  .  \\  _  + ";
const char keyboard_row4_shift[] =        "   !  @  #  $  %  ^  &  *  (  )  ~  { ";
bool shift = false;
const char keyboard_row0[] =  "   1  2  3  4  5  6  7  8  9  0  -  = ";
const char keyboard_row1[] =  "   q  w  e  r  t  y  u  i  o  p  [  ] ";
const char keyboard_row2[] =  "   a  s  d  f  g  h  j  k  l  ;  '  \" ";
const char keyboard_row3[] =  "   z  x  c  v  b  n  m  ,  .  /  _  + ";
const char keyboard_row4[] =  "   !  @  #  $  %  ^  &  *  (  )  ~  } ";
millis_t scan_restart_timeout = 0;

void _menu_mkswifi_act_disconn() {
    mks_wifi_send_wifi_connect(ESP_WIFI_ACT_DISCONN);
    ui.refresh(LCDVIEW_CLEAR_CALL_REDRAW);
}

void _menu_mkswifi_act_conn_saved() {
    mks_wifi_send_wifi_connect(ESP_WIFI_ACT_CONN);
    ui.refresh(LCDVIEW_CLEAR_CALL_REDRAW);
}

void _menu_mkswifi_act_forget() {
    mks_wifi_send_wifi_connect(ESP_WIFI_ACT_FORGET);
    ui.refresh(LCDVIEW_CLEAR_CALL_REDRAW);
}

void _menu_mkswifi_act_unbind() {
    mks_wifi_send_unbind();
    ui.refresh(LCDVIEW_CLEAR_CALL_REDRAW);
}

void _menu_mkswifi_act_resetmodule() {
    mks_wifi_reset();
    ui.refresh(LCDVIEW_CLEAR_CALL_REDRAW);
}

void _menu_mkswifi_touch(uint16_t x, uint16_t y) {
  // SERIAL_ECHO_MSG("touch", x, " ", y);
  uint16_t space_width = TFT_String::glyph(' ')->DWidth;
  uint16_t lb = 0;
  uint16_t hb = 0;
  if(y >= MENU_LINE_HEIGHT*2+FONT_LINE_HEIGHT*4) {
    //row4
    for(uint i = 3; i < sizeof(keyboard_row4); i+=3) {
      lb = hb;
      hb += (TFT_String::glyph((shift ? keyboard_row4_shift : keyboard_row4)[i])->DWidth + 2*space_width);
      if(x > lb && x < hb) {
        touch_char = (shift ? keyboard_row4_shift : keyboard_row4)[i];
        break;
      }
    }
  } else if(y >= MENU_LINE_HEIGHT*2+FONT_LINE_HEIGHT*3) {
    //row3
    if(x >= TFT_WIDTH-24*4-2*space_width) {
      //shift
      shift = !shift;
      return;
    }
    for(uint i = 3; i < sizeof(keyboard_row3); i+=3) {
      lb = hb;
      hb += (TFT_String::glyph((shift ? keyboard_row3_shift : keyboard_row3)[i])->DWidth + 2*space_width);
      if(x > lb && x < hb) {
        touch_char = (shift ? keyboard_row3_shift : keyboard_row3)[i];
        break;
      }
    }
  } else if(y >= MENU_LINE_HEIGHT*2+FONT_LINE_HEIGHT*2) {
    //row2
    if(x >= TFT_WIDTH-24*2-2*space_width) {
      //space
      touch_char = ' ';
      goto _append;
    }
    for(uint i = 3; i < sizeof(keyboard_row2); i+=3) {
      lb = hb;
      hb += (TFT_String::glyph((shift ? keyboard_row2_shift : keyboard_row2)[i])->DWidth + 2*space_width);
      if(x > lb && x < hb) {
        touch_char = (shift ? keyboard_row2_shift : keyboard_row2)[i];
        break;
      }
    }
  } else if(y >= MENU_LINE_HEIGHT*2+FONT_LINE_HEIGHT) {
    //row1
    if(x >= TFT_WIDTH-24*2-2*space_width) {
      //backspace
      if(curr_pass_idx > 0) {
        entered_pass[--curr_pass_idx] = 0;
      }
      return;
    }
    for(uint i = 3; i < sizeof(keyboard_row1); i+=3) {
      lb = hb;
      hb += (TFT_String::glyph((shift ? keyboard_row1_shift : keyboard_row1)[i])->DWidth + 2*space_width);
      if(x > lb && x < hb) {
        touch_char = (shift ? keyboard_row1_shift : keyboard_row1)[i];
        break;
      }
    }
  } else if(y >= MENU_LINE_HEIGHT*2) {
    //row0
    if(x >= TFT_WIDTH-24*2-2*space_width) {
      //enter
      //отправить запрос на подключение к сети
      mks_wifi_send_netconf(WIFI_MODE_CLIENT, mks_global_scan_result.networks[curr_connecting_net_idx].name_len, mks_global_scan_result.networks[curr_connecting_net_idx].name, curr_pass_idx, entered_pass);
      ui.goto_previous_screen();
      ui.goto_previous_screen(); //вернуться назад к менюшке mks wifi
      return;
    }
    for(uint i = 3; i < sizeof(keyboard_row0); i+=3) {
      lb = hb;
      hb += (TFT_String::glyph((shift ? keyboard_row0_shift : keyboard_row0)[i])->DWidth + 2*space_width);
      if(x > lb && x < hb) {
        touch_char = (shift ? keyboard_row0_shift : keyboard_row0)[i];
        break;
      }
    }
  } else {
    touch_char = '?';
    return;
  }
_append:
  if(curr_pass_idx < 64) {
    entered_pass[curr_pass_idx++] = touch_char;
  }
}

//Меню ввода пароля сети
void _menu_mkswifi_connect() {
  ui.refresh(LCDVIEW_CALL_REDRAW_NEXT);
  if(ui.should_draw()) {
      START_MENU();
      //DWIDTH = 18
      STATIC_ITEM_F(GET_TEXT_F(MSG_MKSWIFI_CONNECTING), SS_CENTER|SS_INVERT, mks_global_scan_result.networks[curr_connecting_net_idx].name);
      STATIC_ITEM_F(GET_TEXT_F(MSG_MKSWIFI_PASSWORD), SS_CENTER|SS_INVERT, entered_pass);

      END_MENU();

       //Откалибровано для этого экрана
      #if HAS_UI_480x320
        tft.canvas(0, MENU_LINE_HEIGHT*2, TFT_WIDTH, TFT_HEIGHT-MENU_LINE_HEIGHT*3);
        tft.set_background(0x2104);
        tft_string.set(shift ? keyboard_row0_shift : keyboard_row0);
        tft.add_text(0, 0, COLOR_STATUS_MESSAGE, tft_string);
        tft_string.set(shift ? keyboard_row1_shift : keyboard_row1);
        tft.add_text(0, FONT_LINE_HEIGHT, COLOR_STATUS_MESSAGE, tft_string);
        tft_string.set(shift ? keyboard_row2_shift : keyboard_row2);
        tft.add_text(0, FONT_LINE_HEIGHT*2, COLOR_STATUS_MESSAGE, tft_string);
        tft_string.set(shift ? keyboard_row3_shift : keyboard_row3);
        tft.add_text(0, FONT_LINE_HEIGHT*3, COLOR_STATUS_MESSAGE, tft_string);
        tft_string.set(shift ? keyboard_row4_shift : keyboard_row4);
        tft.add_text(0, FONT_LINE_HEIGHT*4, COLOR_STATUS_MESSAGE, tft_string);
        tft_string.set("-->");
        tft.add_text(TFT_WIDTH-24*2, 0, COLOR_STATUS_MESSAGE, tft_string);
        tft_string.set("<--");
        tft.add_text(TFT_WIDTH-24*2, FONT_LINE_HEIGHT*1, COLOR_STATUS_MESSAGE, tft_string);
        tft_string.set("|_|");
        tft.add_text(TFT_WIDTH-24*2, FONT_LINE_HEIGHT*2, COLOR_STATUS_MESSAGE, tft_string);
        tft_string.set(shift ? "shift" : "SHIFT");
        tft.add_text(TFT_WIDTH-24*4, FONT_LINE_HEIGHT*3, COLOR_STATUS_MESSAGE, tft_string);
        touch.add_control(BUTTON, 0, MENU_LINE_HEIGHT*2, TFT_WIDTH, TFT_HEIGHT-MENU_LINE_HEIGHT*3, (intptr_t)_menu_mkswifi_touch);
      #endif
  }
}

void _menu_mkswifi_act_selectnetwork2(int idx) {
    curr_connecting_net_idx = idx;
    curr_pass_idx = 0;
    memset(entered_pass, 0, sizeof(entered_pass));
    ui.push_current_screen();
    shift = false;
    ui.goto_screen(_menu_mkswifi_connect);
}

void _menu_mkswifi_scan() {
    ui.refresh(LCDVIEW_CALL_REDRAW_NEXT);
    if (ui.should_draw()) {
        START_MENU();
        BACK_ITEM(MSG_MKSWIFI_MENU);
        if(mks_global_scan_result.net_cnt > 0) {
          //TODO: может добавить отображение RSSI?
          for(int i = 0; i < mks_global_scan_result.net_cnt; i++) {
            //ACTION_ITEM_F unwrapped
            if (_menuLineNr == _thisItemNr) {
              _skipStatic = false;
              {
                FSTR_P const flabel = FPSTR(mks_global_scan_result.networks[i].name);
                if (encoderLine == _thisItemNr && ui.use_click()) {
                  _MENU_ITEM_MULTIPLIER_CHECK(false);
                  // MenuItem_function::action(flabel, func); //just calls the function passed
                  _menu_mkswifi_act_selectnetwork2(i);
                  if (ui.screen_changed) return;
                }
                if (ui.should_draw())
                  MenuItem_function::draw(encoderLine == _thisItemNr, _lcdLineNr, flabel);
              }
            }
            NEXT_ITEM();
          }
        } else {
          STATIC_ITEM_F(GET_TEXT_F(MSG_MKSWIFI_SCAN_WAIT), SS_CENTER|SS_INVERT);
          if(millis() >= scan_restart_timeout + 2000UL) {
            mks_wifi_send_scan();
            scan_restart_timeout = millis();
          }
        }
        END_MENU();
    }
}

void _menu_mkswifi_act_scan() {
    mks_global_scan_result.net_cnt = 0;
    scan_restart_timeout = millis();
    mks_wifi_send_scan();
    ui.push_current_screen();
    ui.goto_screen(_menu_mkswifi_scan);
}

void _menu_mkswifi_main() {
    ui.refresh(LCDVIEW_CALL_REDRAW_NEXT);
    if(net_prev_state != mks_global_net_status.state || net_prev_wifi_namelen != mks_global_net_status.wifi_name_len) {
      ui.refresh(LCDVIEW_CLEAR_CALL_REDRAW);
      net_prev_state = mks_global_net_status.state;
      net_prev_wifi_namelen = mks_global_net_status.wifi_name_len;
    }
    if (ui.should_draw()) {
        START_MENU();
        BACK_ITEM(MSG_CONFIGURATION);
        if(mks_global_net_status.state == ESP_NET_WIFI_CONNECTED && mks_global_net_status.mode == WIFI_MODE_CLIENT) {
            STATIC_ITEM_F(GET_TEXT_F(MSG_MKSWIFI_STATUS_CONN), SS_CENTER|SS_INVERT);
            STATIC_ITEM_F(GET_TEXT_F(MSG_MKSWIFI_NETNAME), SS_CENTER, mks_global_net_status.wifi_name);
            char ip_str[16];
            sprintf(ip_str,"%d.%d.%d.%d", mks_global_net_status.ip[0], mks_global_net_status.ip[1], mks_global_net_status.ip[2], mks_global_net_status.ip[3]);
            STATIC_ITEM_F(GET_TEXT_F(MSG_MKSWIFI_ADDR), SS_CENTER, ip_str);
            //TODO: cloud support
            ACTION_ITEM(MSG_MKSWIFI_DISC, _menu_mkswifi_act_disconn);
            ACTION_ITEM(MSG_MKSWIFI_FORGET, _menu_mkswifi_act_forget);
            ACTION_ITEM(MSG_MKSWIFI_UNBIND, _menu_mkswifi_act_unbind);
        } else {
            STATIC_ITEM_F(mks_global_net_status.state == ESP_NET_WIFI_EXCEPTION ? GET_TEXT_F(MSG_MKSWIFI_STATUS_EXC) : GET_TEXT_F(MSG_MKSWIFI_STATUS_NOTCONN), SS_CENTER|SS_INVERT);
            if(mks_global_net_status.wifi_name_len > 0) {
              STATIC_ITEM_F(GET_TEXT_F(MSG_MKSWIFI_SAVEDNETNAME), SS_CENTER, mks_global_net_status.wifi_name);
              ACTION_ITEM(MSG_MKSWIFI_CONNSAVED, _menu_mkswifi_act_conn_saved);
              ACTION_ITEM(MSG_MKSWIFI_FORGET, _menu_mkswifi_act_forget);
              ACTION_ITEM(MSG_MKSWIFI_UNBIND, _menu_mkswifi_act_unbind);
            }
            ACTION_ITEM(MSG_MKSWIFI_SCAN, _menu_mkswifi_act_scan);
        }
        ACTION_ITEM(MSG_MKSWIFI_RESET, _menu_mkswifi_act_resetmodule);
        END_MENU();
    }
}

void menu_mkswifi() {
    ui.goto_screen(_menu_mkswifi_main);
}

#endif // HAS_MARLINUI_MENU