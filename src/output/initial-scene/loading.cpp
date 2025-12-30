#include "loading.h"

extern TFT_eSPI tft;

constexpr uint16_t BASE_SCREEN_BG = 0x0042,
          n_points = 128;

static uint8_t point_x[n_points] = {},  point_y[n_points] = {}, point_c[n_points] = {};
static TFT_eSprite txt_sprite(&tft);
static int16_t txt_width, txt_height;

void initScene(){ 
  tft.fillScreen(BASE_SCREEN_BG);

  // Draw the title
  tft.setTextSize(2);
  tft.setTextFont(4);
  auto width = tft.textWidth("EStation");
  auto height = tft.fontHeight();

  txt_sprite.setColorDepth(16);
  txt_sprite.createSprite(width, height);
  txt_sprite.fillSprite(TFT_BLACK);
  txt_sprite.setTextSize(2);
  txt_sprite.setTextColor(TFT_WHITE);
  txt_sprite.fillSprite(BASE_SCREEN_BG);
  txt_sprite.drawString("EStation", 0, 0, 4);

  txt_width = width;
  txt_height = height;
}

bool inSpriteArea(int x, int y){
  return x >= 160 - txt_width/2 && x <= 160 + txt_width/2 &&
         y >= 120 - txt_height/2 && y <= 120 + txt_height/2;
}

// All credits to Bodmer's TFT_eSPI example: TFT_Starfield
// Slighly modified to fit the project
void drawInitialSceneFrame(){
  static int32_t last_time = 0;

  if (millis() - last_time < 20){
    return;
  }
  last_time = millis();

  uint8_t depth = 255;
  // Draw the particles
  for (int i = 0; i < n_points; i++){
    if (point_c[i] <= 1){
      point_x[i] = random(255);
      point_y[i] = random(255);
      point_c[i] = depth--;
    } else {
      int old_screen_x = (point_x[i] - 160) * 256 / point_c[i] + 160;
      int old_screen_y = (point_y[i] - 120) * 256 / point_c[i] + 120;

      if (inSpriteArea(old_screen_x, old_screen_y)){
        point_c[i] = 0;
        continue;
      }

      tft.drawPixel(old_screen_x, old_screen_y, BASE_SCREEN_BG);
      tft.drawPixel(old_screen_x + 1, old_screen_y, BASE_SCREEN_BG);
      tft.drawPixel(old_screen_x, old_screen_y + 1, BASE_SCREEN_BG);
      tft.drawPixel(old_screen_x + 1, old_screen_y + 1, BASE_SCREEN_BG);

      point_c[i] -= 2;
      if (point_c[i] > 1){
        int screen_x = (point_x[i] - 160) * 256 / point_c[i] + 160;
        int screen_y = (point_y[i] - 120) * 256 / point_c[i] + 120;

        if (screen_x >= 0 && screen_y >= 0 && screen_x < 320 && screen_y < 240){
          uint8_t r, g, b;
          r = g = b = 255 - point_c[i];
          tft.drawPixel(screen_x, screen_y, tft.color565(r, g, b));
          tft.drawPixel(screen_x + 1, screen_y, tft.color565(r, g, b));
          tft.drawPixel(screen_x, screen_y + 1, tft.color565(r, g, b));
          tft.drawPixel(screen_x + 1, screen_y + 1, tft.color565(r, g, b));
        } else {
          point_c[i] = 0;
        }
      }
    }
  }
  
  txt_sprite.pushSprite(160 - txt_sprite.width()/2, 120 - txt_sprite.height()/2);
}