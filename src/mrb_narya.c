/*
** mrb_narya.c - Narya class
**
** Copyright (c) KAGEYAMA Katsuhiko 2019
**
** See Copyright Notice in LICENSE
*/

#include "mruby.h"
#include "mruby/data.h"
#include "mruby/class.h"
#include "mruby/value.h"
#include "mrb_narya.h"

#define DONE mrb_gc_arena_restore(mrb, 0);

void mrb_mruby_esp32_narya_gem_init(mrb_state *mrb)
{
  mrb_narya_init_resouce(mrb);

  struct RClass *narya_module = mrb_define_module(mrb, "Narya");

  // Display
  struct RClass *display_module = mrb_define_module_under(mrb, narya_module, "Display");
  mrb_define_module_function(mrb, display_module, "width", mrb_narya_display_width, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, display_module, "height", mrb_narya_display_height, MRB_ARGS_NONE());

  mrb_define_module_function(mrb, display_module, "draw_circle", mrb_narya_display_draw_circle, MRB_ARGS_REQ(4));
  mrb_define_module_function(mrb, display_module, "draw_line", mrb_narya_display_draw_line, MRB_ARGS_REQ(5));
  mrb_define_module_function(mrb, display_module, "draw_rect", mrb_narya_display_draw_rect, MRB_ARGS_ARG(5,1));
  mrb_define_module_function(mrb, display_module, "draw_pixel", mrb_narya_display_draw_pixel, MRB_ARGS_REQ(3));

  mrb_define_module_function(mrb, display_module, "clear", mrb_narya_display_clear, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, display_module, "double_buffered?", mrb_narya_display_double_buffered, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, display_module, "swap", mrb_narya_display_swap, MRB_ARGS_NONE());

  mrb_define_module_function(mrb, display_module, "draw_picture", mrb_narya_display_draw_picture, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, display_module, "load_bitmap", mrb_narya_display_load_bitmap, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, display_module, "scroll", mrb_narya_display_scroll, MRB_ARGS_REQ(2));

  mrb_define_module_function(mrb, display_module, "font_size", mrb_narya_display_font_size, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, display_module, "draw_text", mrb_narya_display_draw_text, MRB_ARGS_ARG(4,1));

  // Input
  struct RClass *input_module = mrb_define_module_under(mrb, narya_module, "Input");
  mrb_define_module_function(mrb, input_module, "available", mrb_narya_input_available, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, input_module, "keydown?", mrb_narya_input_keydown, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, input_module, "get_key", mrb_narya_input_get_key, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, input_module, "paddown?", mrb_narya_input_pad_down, MRB_ARGS_REQ(1));

  //struct RClass *image_module = mrb_define_module_under(mrb, narya_module, "Image");

  // Sprite
  struct RClass *sprite_class = mrb_define_class_under(mrb, narya_module, "Sprite", mrb->object_class);
  MRB_SET_INSTANCE_TT(sprite_class, MRB_TT_DATA);
  mrb_define_method(mrb, sprite_class, "initialize", mrb_narya_sprite_initialize, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, sprite_class, "move_to", mrb_narya_sprite_move_to, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, sprite_class, "move", mrb_narya_sprite_move, MRB_ARGS_REQ(2));
  
  // Bitmap
  struct RClass *bitmap_class = mrb_define_class_under(mrb, narya_module, "Bitmap", mrb->object_class);
  MRB_SET_INSTANCE_TT(bitmap_class, MRB_TT_DATA);
  mrb_define_method(mrb, bitmap_class, "initialize", mrb_narya_bitmap_initialize, MRB_ARGS_NONE());
  mrb_define_method(mrb, bitmap_class, "load", mrb_narya_bitmap_load, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, bitmap_class, "draw", mrb_narya_bitmap_draw, MRB_ARGS_REQ(2));

  // Config
  struct RClass *config_module = mrb_define_module_under(mrb, narya_module, "Config");
  mrb_define_module_function(mrb, config_module, "firmware_ver", mrb_narya_config_firmware_ver, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, config_module, "narya_ver", mrb_narya_config_narya_ver, MRB_ARGS_NONE());

  // Sound
  struct RClass *sound_module = mrb_define_module_under(mrb, narya_module, "Sound");
  mrb_define_module_function(mrb, sound_module, "load_mml", mrb_narya_sound_load, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, sound_module, "play", mrb_narya_sound_play, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, sound_module, "stop", mrb_narya_sound_stop, MRB_ARGS_NONE());



  /** To be implemented...
  * Display module
  *  Draw Ellipse
  *  Copy Rect
  *  Draw Draw Path(fill)
  *  double_buffer?
  * Storage module
  *  open
  *  read
  *  write
  *  close
  * Sprite class
  *  add_image
  *  set_config
  **/

  DONE;
}

void mrb_mruby_esp32_narya_gem_final(mrb_state *mrb)
{
  mrb_narya_finalize_resouce(mrb);
}
