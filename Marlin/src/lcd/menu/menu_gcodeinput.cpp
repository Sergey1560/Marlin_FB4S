//
// Gcode input Menu
//

#include "../../inc/MarlinConfigPre.h"

#if HAS_MARLINUI_MENU && ENABLED(MENU_ENABLE_GCODE_INPUT)

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

char entered_code[65];
int curr_code_idx = 0;
char gtouch_char = '?';
const char gkeyboard_row0[] =  "   1  2  3  G  P  U  J  R  K ";
const char gkeyboard_row1[] =  "   4  5  6  M  X  V  D  Q  N ";
const char gkeyboard_row2[] =  "   7  8  9  T  Y  W  H  E ";
const char gkeyboard_row3[] =  "   -  0  .  S  Z  I  F  L ";

void _menu_gcodeinput_touch(uint16_t x, uint16_t y) {
  // SERIAL_ECHO_MSG("touch", x, " ", y);
  uint16_t space_width = TFT_String::glyph(' ')->DWidth;
  uint16_t lb = 0;
  uint16_t hb = 0;
  if(y >= MENU_LINE_HEIGHT*2+FONT_LINE_HEIGHT*3) {
    //row3
    for(uint i = 3; i < sizeof(gkeyboard_row3); i+=3) {
      lb = hb;
      hb += (TFT_String::glyph(gkeyboard_row3[i])->DWidth + 2*space_width);
      if(x > lb && x < hb) {
        gtouch_char = gkeyboard_row3[i];
        break;
      }
    }
  } else if(y >= MENU_LINE_HEIGHT*2+FONT_LINE_HEIGHT*2) {
    //row2
    if(x >= TFT_WIDTH-24*2-2*space_width) {
      //space
      gtouch_char = ' ';
      goto _append;
    }
    for(uint i = 3; i < sizeof(gkeyboard_row2); i+=3) {
      lb = hb;
      hb += (TFT_String::glyph(gkeyboard_row2[i])->DWidth + 2*space_width);
      if(x > lb && x < hb) {
        gtouch_char = gkeyboard_row2[i];
        break;
      }
    }
  } else if(y >= MENU_LINE_HEIGHT*2+FONT_LINE_HEIGHT) {
    //row1
    if(x >= TFT_WIDTH-24*2-2*space_width) {
      //backspace
      if(curr_code_idx > 0) {
        entered_code[--curr_code_idx] = 0;
      }
      return;
    }
    for(uint i = 3; i < sizeof(gkeyboard_row1); i+=3) {
      lb = hb;
      hb += (TFT_String::glyph(gkeyboard_row1[i])->DWidth + 2*space_width);
      if(x > lb && x < hb) {
        gtouch_char = gkeyboard_row1[i];
        break;
      }
    }
  } else if(y >= MENU_LINE_HEIGHT*2) {
    //row0
    if(x >= TFT_WIDTH-24*2-2*space_width) {
      //enter
      GCodeQueue::ring_buffer.enqueue((const char *)entered_code);
      curr_code_idx = 0;
      memset(entered_code, 0, sizeof(entered_code));
      return;
    }
    for(uint i = 3; i < sizeof(gkeyboard_row0); i+=3) {
      lb = hb;
      hb += (TFT_String::glyph(gkeyboard_row0[i])->DWidth + 2*space_width);
      if(x > lb && x < hb) {
        gtouch_char = gkeyboard_row0[i];
        break;
      }
    }
  } else {
    gtouch_char = '?';
    return;
  }
_append:
  if(curr_code_idx < 64) {
    entered_code[curr_code_idx++] = gtouch_char;
  }
}

void _menu_gcodeinput_main() {
    ui.refresh(LCDVIEW_CALL_REDRAW_NEXT);
    if(ui.should_draw()) {
      START_MENU();
      //DWIDTH = 18
      STATIC_ITEM_F(GET_TEXT_F(MSG_GCODEIN_CODE), SS_CENTER|SS_INVERT, entered_code);

      END_MENU();

       //Откалибровано для этого экрана
      #if HAS_UI_480x320
        tft.canvas(0, MENU_LINE_HEIGHT*2, TFT_WIDTH, TFT_HEIGHT-MENU_LINE_HEIGHT*3);
        tft.set_background(0x2104);
        tft_string.set(gkeyboard_row0);
        tft.add_text(0, 0, COLOR_STATUS_MESSAGE, tft_string);
        tft_string.set(gkeyboard_row1);
        tft.add_text(0, FONT_LINE_HEIGHT, COLOR_STATUS_MESSAGE, tft_string);
        tft_string.set(gkeyboard_row2);
        tft.add_text(0, FONT_LINE_HEIGHT*2, COLOR_STATUS_MESSAGE, tft_string);
        tft_string.set(gkeyboard_row3);
        tft.add_text(0, FONT_LINE_HEIGHT*3, COLOR_STATUS_MESSAGE, tft_string);
        tft_string.set("-->");
        tft.add_text(TFT_WIDTH-24*2, 0, COLOR_STATUS_MESSAGE, tft_string);
        tft_string.set("<--");
        tft.add_text(TFT_WIDTH-24*2, FONT_LINE_HEIGHT*1, COLOR_STATUS_MESSAGE, tft_string);
        tft_string.set("|_|");
        tft.add_text(TFT_WIDTH-24*2, FONT_LINE_HEIGHT*2, COLOR_STATUS_MESSAGE, tft_string);
        touch.add_control(BUTTON, 0, MENU_LINE_HEIGHT*2, TFT_WIDTH, TFT_HEIGHT-MENU_LINE_HEIGHT*3, (intptr_t)_menu_gcodeinput_touch);
      #endif
  }
}

void menu_gcodeinput() {
    curr_code_idx = 0;
    memset(entered_code, 0, sizeof(entered_code));
    ui.goto_screen(_menu_gcodeinput_main);
}

#endif // HAS_MARLINUI_MENU