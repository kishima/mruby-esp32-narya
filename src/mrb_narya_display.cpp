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

MRB_BEGIN_DECL

mrb_value mrb_narya_display_draw_circle(mrb_state *mrb, mrb_value self)
{
  mrb_int x;
  mrb_int y;
  mrb_int r;
  mrb_int col;
  mrb_get_args(mrb, "iiii", &x,&y,&r,&col);

  Color color;
  switch(col){
    case 0:
      color = Color::Black;
      break;
    case 1:
      color = Color::Red;
      break;
    case 2:
      color = Color::Green;
      break;
    case 3:
      color = Color::Yellow;
      break;
    case 4:
      color = Color::Blue;
      break;
    case 5:
      color = Color::Magenta;
      break;
    case 6:
      color = Color::Cyan;
      break;
    case 7:
      color = Color::White;
      break;
    default:
      color = Color::Black;
      break;
  }

  Canvas.setBrushColor(color);
  Canvas.fillEllipse(x, y, r, r);
  return self;
}

mrb_value mrb_narya_display_draw_text(mrb_state *mrb, mrb_value self)
{
  mrb_int x;
  mrb_int y;
  char * string = NULL;
  mrb_get_args(mrb, "iiz", &x,&y,&string);
  Canvas.setPenColor(Color::Blue);
  Canvas.setBrushColor(Color::Yellow);
  Canvas.drawTextFmt(x, y, "%s", string);
  return self;
}

mrb_value mrb_narya_display_clear(mrb_state *mrb, mrb_value self)
{
  Canvas.setBrushColor(Color::Black);
  Canvas.clear();
  return self;
}

mrb_value mrb_narya_display_swap(mrb_state *mrb, mrb_value self)
{
  VGAController.refreshSprites();
  Canvas.swapBuffers();
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

  return self;
}

mrb_value mrb_narya_display_load_bitmap(mrb_state *mrb, mrb_value self)
{
  return self;
}

/**
 * Bitmap
 **/

static void bitmap_cdata_free(mrb_state *mrb, void* value)
{
  mrb_free(mrb,value);
}
static struct mrb_data_type mrb_bitmap_cdata_type = { "Bitmap", bitmap_cdata_free };

const Bitmap spaceship = Bitmap(16, 16, &spaceship_data[0]);
Bitmap testimg = Bitmap(145, 160, &testimg_data[0]);

mrb_value mrb_narya_bitmap_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_int width;
  mrb_int height;
  mrb_get_args(mrb, "ii", &width,&height);
  DATA_TYPE(self) = &mrb_bitmap_cdata_type;
  DATA_PTR(self) = &testimg;
  return self;
}

mrb_value mrb_narya_bitmap_draw(mrb_state *mrb, mrb_value self)
{
  return self;
}

/**
 * Sprite
 */

Sprite *sprites_list = new Sprite[10];

static void sprite_cdata_free(mrb_state *mrb, void* value)
{
  mrb_free(mrb,value);
}
static struct mrb_data_type mrb_sprite_cdata_type = { "Sprite", sprite_cdata_free };

mrb_value mrb_narya_sprite_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_value bitmap_obj;
  //mrb_get_args(mrb, "o", &bitmap_obj);

  Sprite * newSprite = &sprites_list[0];
  newSprite->addBitmap(&spaceship);
  
  VGAController.setSprites(sprites_list, 1);

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
  sprite->move(x, y, true);
  return self;
}


MRB_END_DECL
