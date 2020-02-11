/*
** mrb_narya_display.c - Narya Display class
**
** Copyright (c) KAGEYAMA Katsuhiko 2019
**
** See Copyright Notice in LICENSE
*/

#include "mruby.h"
#include "mruby/data.h"
#include "mruby/variable.h"
#include "mrb_narya.h"

#include "fabgl.h"
#include "fabutils.h"


#include "fmruby.h"
#include "fmruby_app.h"


extern fabgl::VGAController VGAController;
extern fabgl::Canvas        FMRB_canvas;
extern FmrbFileService      FMRB_storage;;


MRB_BEGIN_DECL

#define MAX_SPRITES (10)
Sprite* sprites_list = nullptr; 

static RGB888 str_to_color(mrb_state *mrb, const char* in);

void mrb_narya_init_resouce(mrb_state *mrb){
  FMRB_DEBUG(FMRB_LOG::DEBUG,"mrb_narya_init_resouce\n");
  sprites_list = new Sprite[MAX_SPRITES];

  FMRB_canvas.setPenColor(str_to_color(mrb,"333"));
  FMRB_canvas.setBrushColor(str_to_color(mrb,"000"));
  FMRB_canvas.selectFont(fabgl::getPresetFixedFont(8,8));

  FMRB_canvas.setGlyphOptions(GlyphOptions().FillBackground(false));
}

void mrb_narya_finalize_resouce(mrb_state *mrb){
  FMRB_DEBUG(FMRB_LOG::DEBUG,"mrb_narya_finalize_resouce\n");
  VGAController.removeSprites();
  if(sprites_list){
    delete[] sprites_list;
  }
  sprites_list = nullptr;
  FMRB_DEBUG(FMRB_LOG::DEBUG,"mrb_narya_finalize_resouce done\n");
}

RGB888 str_to_color(mrb_state *mrb, const char* in){
  RGB888 out = RGB888(255,255,255);
  if(!in)return out;
  if(strlen(in) > 0){
    if(*in >= 0x30 && *in <= 0x33){
      // "333" => WHITE
      // "000" => BLACK
      //   0 ..  63 => 0
      //  64 .. 127 => 1
      // 128 .. 191 => 2
      // 192 .. 255 => 3
      uint8_t r = (*in     - 0x30) * 64;
      uint8_t g = (*(in+1) - 0x30) * 64;
      uint8_t b = (*(in+2) - 0x30) * 64;
      out = RGB888(r,g,b);
    }else{
      if(strcmp(in,"BLACK")==0){
        out = RGB888(Color::Black);
      }else if(strcmp(in,"RED")==0){
        out = RGB888(Color::Red);
      }else if(strcmp(in,"GREEN")==0){
        out = RGB888(Color::Green);
      }else if(strcmp(in,"YELLOW")==0){
        out = RGB888(Color::Yellow);
      }else if(strcmp(in,"BLUE")==0){
        out = RGB888(Color::Blue);
      }else if(strcmp(in,"MAGENTA")==0){
        out = RGB888(Color::Magenta);
      }else if(strcmp(in,"CYAN")==0){
        out = RGB888(Color::Cyan);
      }else if(strcmp(in,"WHITE")==0){
        out = RGB888(Color::White);
      }else{
        mrb_raisef(mrb,E_ARGUMENT_ERROR,"Bad Color formart(%s)\n",in);
      }
    }
  }else{
    mrb_raise(mrb,E_ARGUMENT_ERROR,"Bad Color formart\n");
  }
  return out;
}

mrb_value mrb_narya_display_draw_circle(mrb_state *mrb, mrb_value self)
{
  mrb_int x;
  mrb_int y;
  mrb_int r;
  char * col = NULL;
  char * col2 = NULL;
  bool opt = false;
  mrb_get_args(mrb, "iiiz|z?", &x,&y,&r,&col,&col2,&opt);

  if(opt){
    FMRB_canvas.setBrushColor(str_to_color(mrb,col2));
    FMRB_canvas.fillEllipse(x, y, r, r);
  }
  FMRB_canvas.setPenColor(str_to_color(mrb,col));
  FMRB_canvas.drawEllipse(x,y,r,r);
  return self;
}

mrb_value mrb_narya_display_draw_line(mrb_state *mrb, mrb_value self){
  mrb_int x0;
  mrb_int y0;
  mrb_int x1;
  mrb_int y1;
  char * col = NULL;
  mrb_get_args(mrb, "iiiiz", &x0,&y0,&x1,&y1,&col);

  FMRB_canvas.setPenColor(str_to_color(mrb,col));
  FMRB_canvas.drawLine(x0, y0, x1, y1);
  return self;
}

mrb_value mrb_narya_display_draw_rect(mrb_state *mrb, mrb_value self){
  mrb_int x0;
  mrb_int y0;
  mrb_int x1;
  mrb_int y1;
  char * col = NULL;
  char * col2 = NULL;
  bool opt = false;
  mrb_get_args(mrb, "iiiiz|z?", &x0,&y0,&x1,&y1,&col,&col2,&opt);

  if(opt){
    FMRB_canvas.setBrushColor(str_to_color(mrb,col2));
    FMRB_canvas.fillRectangle(x0, y0, x1, y1);
    if(col!=col2){
      FMRB_canvas.setPenColor(str_to_color(mrb,col));
      FMRB_canvas.drawRectangle(x0, y0, x1, y1);
    }
  }else{
    FMRB_canvas.setPenColor(str_to_color(mrb,col));
    FMRB_canvas.drawRectangle(x0, y0, x1, y1);
  }
  return self;
}

mrb_value mrb_narya_display_draw_pixel(mrb_state *mrb, mrb_value self){
  mrb_int x0;
  mrb_int y0;
  char * col = NULL;
  mrb_get_args(mrb, "iiz", &x0,&y0,&col);

  FMRB_canvas.setPenColor(str_to_color(mrb,col));
  FMRB_canvas.setPixel(x0, y0);
  return self;
}

mrb_value mrb_narya_display_font_size(mrb_state *mrb, mrb_value self)
{
  mrb_int w;
  mrb_int h;
  mrb_get_args(mrb, "ii", &w,&h);
  if(w<0 || h<0){
    mrb_raise(mrb,E_ARGUMENT_ERROR,"Bad argument\n");
  } 
  const fabgl::FontInfo *info = fabgl::getPresetFixedFont(w,h);
  if(info==nullptr){
    mrb_raise(mrb,E_RUNTIME_ERROR,"Font not found\n");
  }else{
    FMRB_canvas.selectFont(info);
  }
  return self;
}

mrb_value mrb_narya_display_draw_text(mrb_state *mrb, mrb_value self)
{
  mrb_int x;
  mrb_int y;
  char * string = NULL;
  char * col = NULL;
  char * col2 = NULL; //BG color option
  bool opt = false;
  mrb_get_args(mrb, "iizz|z?", &x,&y,&string,&col,&col2,&opt);

  FMRB_canvas.setPenColor(str_to_color(mrb,col));
  if(opt){
    FMRB_canvas.setBrushColor(str_to_color(mrb,col2));
    FMRB_canvas.setGlyphOptions(GlyphOptions().FillBackground(true));
  }else{
    FMRB_canvas.setGlyphOptions(GlyphOptions().FillBackground(false));
  }
  //FMRB_canvas.drawTextFmt(x, y, "%s", string);
  FMRB_canvas.drawText(x,y,string);
  return self;
}

mrb_value mrb_narya_display_clear(mrb_state *mrb, mrb_value self)
{
  FMRB_canvas.setBrushColor(Color::Black);
  FMRB_canvas.clear();
  return self;
}

mrb_value mrb_narya_display_double_buffered(mrb_state *mrb, mrb_value self)
{
  if(VGAController.isDoubleBuffered()){
    return mrb_true_value();
  }
  return mrb_false_value();
}

mrb_value mrb_narya_display_swap(mrb_state *mrb, mrb_value self)
{
  //VGAController.refreshSprites();
  if(VGAController.isDoubleBuffered()){
    FMRB_canvas.swapBuffers();
  }
  return self;
}

mrb_value mrb_narya_display_width(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(VGAController.getScreenWidth());
}

mrb_value mrb_narya_display_height(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(VGAController.getScreenHeight());
}

mrb_value mrb_narya_display_scroll(mrb_state *mrb, mrb_value self)
{
  mrb_int x;
  mrb_int y;
  mrb_get_args(mrb, "ii", &x,&y);
  FMRB_canvas.scroll(x,y);
  return self;
}

mrb_value mrb_narya_display_load_bitmap(mrb_state *mrb, mrb_value self)
{
  return self;
}

mrb_value mrb_narya_display_draw_picture(mrb_state *mrb, mrb_value self)
{
  //draw picuture of a file on storage instead of Bitmap
  mrb_int x0;
  mrb_int y0;
  char * string = NULL;
  mrb_get_args(mrb, "iiz", &x0,&y0,&string);
  uint32_t fsize;

  uint8_t* data = (uint8_t*)FMRB_storage.load(string,fsize,false,false);
  const int header = 4;

  uint16_t maxx = VGAController.getScreenWidth();
  uint16_t maxy = VGAController.getScreenHeight();

  uint16_t width  = (data[header]) + (data[header+1]<<8);
  uint16_t height = (data[header+2]) + (data[header+3]<<8);
  FMRB_DEBUG(FMRB_LOG::DEBUG,"img:%d,%d\n",width,height);

  uint8_t* p = data+header+4;
  for(uint16_t y=0;y<height;y++){
    if(maxy<=y0+y) break;
    for(uint16_t x=0;x<width;x++){
      if(maxx<=x0+x) break;
      if(((*p)&0xC0) == 0 ){ //check alpha
        VGAController.setRawPixel(x0+x,y0+y,
          VGAController.createRawPixel(RGB222((*p)&0x03, ((*p)&0x0C) >> 2, ((*p)&0x30) >> 4)));
      }
      p++;
    }
  }
  return self;
}

/**
 * Bitmap
 **/

static void bitmap_cdata_free(mrb_state *mrb, void* value)
{
  //free alloced heap
  if(value){
    Bitmap* bitmap_p = (Bitmap*)value;
    FMRB_DEBUG(FMRB_LOG::DEBUG,"bitmap free:%p\n",bitmap_p);
    fmrb_free((bitmap_p->data)-(FMRB_BITMAP_HEADER_SIZE+4));
  }

  mrb_free(mrb,value);
}
static struct mrb_data_type mrb_bitmap_cdata_type = { "Bitmap", bitmap_cdata_free };

mrb_value mrb_narya_bitmap_initialize(mrb_state *mrb, mrb_value self)
{
  DATA_TYPE(self) = &mrb_bitmap_cdata_type;
  DATA_PTR(self) = NULL;
  return self;
}

mrb_value mrb_narya_bitmap_draw(mrb_state *mrb, mrb_value self)
{
  Bitmap* bitmap_p = (Bitmap*)DATA_PTR(self);
  mrb_int x0;
  mrb_int y0;
  mrb_get_args(mrb, "ii", &x0,&y0);
  //FMRB_DEBUG(FMRB_LOG::DEBUG,"bitmap_p:%p\n",bitmap_p);
  //FMRB_DEBUG(FMRB_LOG::DEBUG,"draw:%d %d\n",x0,y0);
  FMRB_canvas.drawBitmap(x0,y0,bitmap_p);
  return self;
}

mrb_value mrb_narya_bitmap_load(mrb_state *mrb, mrb_value self)
{
  fmrb_dump_mem_stat();
  char * string = NULL;
  mrb_get_args(mrb, "z", &string);
  
  uint16_t width;
  uint16_t height;
  uint32_t type;
  char* data = FMRB_storage.load_bitmap(string,width,height,type);
  if(!data)
  {
    mrb_raise(mrb,E_RUNTIME_ERROR,"load bitmap error");
  }
  const int header = 4;
  //FMRB_DEBUG(FMRB_LOG::DEBUG,"w:%d h:%d\n",(int)width,(int)height);
  mrb_iv_set(mrb,self,mrb_intern_cstr(mrb, "@width"),mrb_fixnum_value(width));
  mrb_iv_set(mrb,self,mrb_intern_cstr(mrb, "@height"),mrb_fixnum_value(height));

  Bitmap* bitmap_p = (Bitmap*)malloc(sizeof(Bitmap));
  *bitmap_p = Bitmap((int)width, (int)height, (void*)(data+FMRB_BITMAP_HEADER_SIZE+4), PixelFormat::RGBA2222);
  //FMRB_DEBUG(FMRB_LOG::DEBUG,"bitmap_p:%p\n",bitmap_p);
  DATA_PTR(self) = bitmap_p;

  return self;
}

/**
 * Sprite
 */
static Sprite* get_sprite_ref(void){
  int i=0;
  for(i=0;i<MAX_SPRITES;i++){
    if(sprites_list[i].framesCount==0){
      FMRB_DEBUG(FMRB_LOG::DEBUG,"get_sprite_ref[%d]:%p\n",i,&sprites_list[i]);
      return &sprites_list[i];
    }
  }
  return NULL;
}

static void free_sprite(Sprite* ptr){
  //Sprite will be free by finalize function
}

static void sprite_cdata_free(mrb_state *mrb, void* value)
{
  if(value){
    Sprite* sprite_p = (Sprite*)value;
    FMRB_DEBUG(FMRB_LOG::DEBUG,"Sprite:free sprite_p:%p\n",sprite_p);
    free_sprite(sprite_p);
  }
  //Sprite will be free by finalize function
}
static struct mrb_data_type mrb_sprite_cdata_type = { "Sprite", sprite_cdata_free };

mrb_value mrb_narya_sprite_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_value bitmap_obj;
  mrb_get_args(mrb, "o", &bitmap_obj);

  Bitmap* bitmap_p = (Bitmap*)DATA_PTR(bitmap_obj);
  if(!bitmap_p){
    mrb_raise(mrb,E_RUNTIME_ERROR,"null bitmap ptr");
  } 
  FMRB_DEBUG(FMRB_LOG::DEBUG,"Sprite:bitmap_p:%p\n",bitmap_p);

  AutoSuspendInterrupts autoSuspendInt;

  Sprite* newSprite = get_sprite_ref();
  if(!newSprite){
    mrb_raise(mrb,E_RUNTIME_ERROR,"Sprite alloc error");
  }
  newSprite->addBitmap(bitmap_p);
  FMRB_DEBUG(FMRB_LOG::DEBUG,"newSprite:%p\n",newSprite);
  
  VGAController.setSprites(sprites_list, MAX_SPRITES);

  DATA_TYPE(self) = &mrb_sprite_cdata_type;
  DATA_PTR(self) = newSprite;
  return self;
}

mrb_value mrb_narya_sprite_move_to(mrb_state *mrb, mrb_value self)
{
  mrb_int x;
  mrb_int y;
  mrb_get_args(mrb, "ii", &x,&y);
  Sprite * sprite = (Sprite*)DATA_PTR(self);
  sprite->moveTo(x, y);
  return self;
}

mrb_value mrb_narya_sprite_move(mrb_state *mrb, mrb_value self)
{
  mrb_int x;
  mrb_int y;
  mrb_get_args(mrb, "ii", &x,&y);
  Sprite * sprite = (Sprite*)DATA_PTR(self);
  sprite->moveBy(x, y);
  return self;
}


MRB_END_DECL
