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
  struct RClass *narya_module = mrb_define_module(mrb, "Narya");

  struct RClass *display_module = mrb_define_module_under(mrb, narya_module, "Display");

  mrb_define_module_function(mrb, display_module, "draw_circle", mrb_narya_display_draw_circle, MRB_ARGS_REQ(4));
  mrb_define_module_function(mrb, display_module, "draw_text", mrb_narya_display_draw_text, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, display_module, "clear", mrb_narya_display_clear, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, display_module, "swap", mrb_narya_display_swap, MRB_ARGS_NONE());

  struct RClass *input_module = mrb_define_module_under(mrb, narya_module, "Input");
  struct RClass *image_module = mrb_define_module_under(mrb, narya_module, "Image");

  struct RClass *sprite_class = mrb_define_class_under(mrb, narya_module, "Sprite", mrb->object_class);
  MRB_SET_INSTANCE_TT(sprite_class, MRB_TT_DATA);
  mrb_define_method(mrb, sprite_class, "initialize", mrb_narya_sprite_initialize, MRB_ARGS_NONE());
  mrb_define_method(mrb, sprite_class, "move_to", mrb_narya_sprite_move_to, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, sprite_class, "move", mrb_narya_sprite_move, MRB_ARGS_REQ(2));
  


  DONE;
}

void mrb_mruby_esp32_narya_gem_final(mrb_state *mrb)
{
}
