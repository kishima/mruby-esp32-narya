/*
** mrb_narya_input.cpp - Narya Input class
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
mrb_value mrb_narya_input_available(mrb_state *mrb, mrb_value self)
{
  bool ret = Keyboard.isKeyboardAvailable();
  return ret ? mrb_true_value() : mrb_false_value();
}

mrb_value mrb_narya_input_keydown(mrb_state *mrb, mrb_value self)
{
  if(Keyboard.isKeyboardAvailable()){
    mrb_int vkey;
    mrb_get_args(mrb, "i", &vkey);
    bool ret = Keyboard.isVKDown((fabgl::VirtualKey)vkey);
    return ret ? mrb_true_value() : mrb_false_value();
  }
  return mrb_false_value();
}

MRB_END_DECL
