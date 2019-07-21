/*
** mrb_narya.c - Narya class
**
** Copyright (c) KAGEYAMA Katsuhiko 2019
**
** See Copyright Notice in LICENSE
*/

#include "mruby.h"
#include "mruby/data.h"
#include "mrb_narya.h"

#define DONE mrb_gc_arena_restore(mrb, 0);

void mrb_mruby_esp32_narya_gem_init(mrb_state *mrb)
{
  struct RClass *narya;
  narya = mrb_define_class(mrb, "Narya", mrb->object_class);
  mrb_define_method(mrb, narya, "initialize", mrb_narya_init, MRB_ARGS_REQ(1));
  //mrb_define_method(mrb, narya, "init_fabgl", mrb_narya_, MRB_ARGS_NONE());
  //mrb_define_method(mrb, narya, "demo", mrb_narya_hello, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, narya, "start", mrb_narya_start, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, narya, "demo", mrb_narya_demo, MRB_ARGS_NONE());
  DONE;
}

void mrb_mruby_esp32_narya_gem_final(mrb_state *mrb)
{
}

