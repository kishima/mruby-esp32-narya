#include "mruby.h"
#include "mruby/data.h"
#include "mrb_narya.h"

#include "fabgl.h"
#include "fabutils.h"

// select one color configuration
#define USE_8_COLORS  0
#define USE_64_COLORS 1

// indicate VGA GPIOs to use for selected color configuration
#if USE_8_COLORS
  #define VGA_RED    GPIO_NUM_22
  #define VGA_GREEN  GPIO_NUM_21
  #define VGA_BLUE   GPIO_NUM_19
  #define VGA_HSYNC  GPIO_NUM_18
  #define VGA_VSYNC  GPIO_NUM_5
#elif USE_64_COLORS
  #define VGA_RED1   GPIO_NUM_22
  #define VGA_RED0   GPIO_NUM_21
  #define VGA_GREEN1 GPIO_NUM_19
  #define VGA_GREEN0 GPIO_NUM_18
  #define VGA_BLUE1  GPIO_NUM_5
  #define VGA_BLUE0  GPIO_NUM_4
  #define VGA_HSYNC  GPIO_NUM_23
  #define VGA_VSYNC  GPIO_NUM_15
#endif

#define DOUBLEBUFFERING 1


struct Test {
  virtual ~Test() { };
  virtual void update() = 0;
  virtual bool nextState() = 0;
  virtual int testState() = 0;
  virtual char const * name() = 0;
};


#include "ballstest.h"
#include "polygonstest.h"
#include "spritestest.h"


/* 
typedef struct {
  char *str;
  mrb_int len;
} mrb_narya_data;


static const struct mrb_data_type mrb_narya_data_type = {
  "mrb_narya_data", mrb_free,
};
*/

MRB_BEGIN_DECL

mrb_value mrb_narya_init(mrb_state *mrb, mrb_value self)
{
  /* 
  mrb_narya_data *data;
  char *str;
  mrb_int len;

  data = (mrb_narya_data *)DATA_PTR(self);
  if (data) {
    mrb_free(mrb, data);
  }
  DATA_TYPE(self) = &mrb_narya_data_type;
  DATA_PTR(self) = NULL;

  mrb_get_args(mrb, "s", &str, &len);
  data = (mrb_narya_data *)mrb_malloc(mrb, sizeof(mrb_narya_data));
  data->str = str;
  data->len = len;
  DATA_PTR(self) = data;
  */

  return self;
}

mrb_value mrb_narya_start(mrb_state *mrb, mrb_value self)
{
  ESP_LOGI("narya", "mrb_narya_start");

  #if USE_8_COLORS
  VGAController.begin(VGA_RED, VGA_GREEN, VGA_BLUE, VGA_HSYNC, VGA_VSYNC);
  #elif USE_64_COLORS
  VGAController.begin(VGA_RED1, VGA_RED0, VGA_GREEN1, VGA_GREEN0, VGA_BLUE1, VGA_BLUE0, VGA_HSYNC, VGA_VSYNC);
  #endif

  VGAController.setResolution(VGA_320x200_75Hz, -1, -1, DOUBLEBUFFERING);
  //VGAController.moveScreen(20, 0);
  //VGAController.moveScreen(-8, 0);
  Canvas.selectFont(Canvas.getPresetFontInfo(40, 14)); // get a font for about 40x14 text screen
  Canvas.setGlyphOptions(GlyphOptions().FillBackground(true));


  //mrb_narya_data *data = DATA_PTR(self);
  //return mrb_str_new(mrb, data->str, data->len);
  return self;
}



mrb_value mrb_narya_demo(mrb_state *mrb, mrb_value self)
{
  ESP_LOGI("narya", "mrb_narya_demo");

  static int64_t stime  = esp_timer_get_time();
  static int FPS        = 0;
  static int FPSCounter = 0;
  static int testIndex  = 0;
  static Test * test    = new BallsTest;

  if (test->nextState() == false) {
    delete test;
    ++testIndex;
    switch (testIndex) {
      case 1:
        test = new PolygonsTest;
        break;
      case 2:
        test = new SpritesTest;
        break;
      default:
        testIndex = 0;
        test = new BallsTest;
        break;
    }
  }

  if (esp_timer_get_time() - stime > 1000000) {
    // calculate FPS
    FPS = FPSCounter;
    stime = esp_timer_get_time();
    FPSCounter = 0;
  }
  ++FPSCounter;

  test->update();

  // display test state and FPS
  Canvas.setPenColor(Color::Blue);
  Canvas.setBrushColor(Color::Yellow);
  Canvas.drawTextFmt(80, 5, " %d %s at %d FPS ", test->testState(), test->name(), FPS);

  if (DOUBLEBUFFERING)
    Canvas.swapBuffers();

  //return mrb_str_new_cstr(mrb, "hi!!");
  return self;
}

MRB_END_DECL
