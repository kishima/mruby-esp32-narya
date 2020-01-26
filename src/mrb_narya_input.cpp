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

#include "fmruby.h"

extern fabgl::PS2Controller PS2Controller;

MRB_BEGIN_DECL
mrb_value mrb_narya_input_available(mrb_state *mrb, mrb_value self)
{
  auto keyboard = PS2Controller.keyboard();
  bool ret = keyboard->virtualKeyAvailable();
  return ret ? mrb_true_value() : mrb_false_value();
}

mrb_value mrb_narya_input_keydown(mrb_state *mrb, mrb_value self)
{
  auto keyboard = PS2Controller.keyboard();

  if(keyboard->virtualKeyAvailable()){
    mrb_int vkey;
    mrb_get_args(mrb, "i", &vkey);

    bool ret = keyboard->isVKDown((fabgl::VirtualKey)vkey);
    if(ret){
      keyboard->emptyVirtualKeyQueue();
    }
    //FMRB_DEBUG(FMRB_LOG::DEBUG,"kdwn:%d:%d\n",vkey,ret);
    return ret ? mrb_true_value() : mrb_false_value();
  }
  return mrb_false_value();
}

MRB_END_DECL
