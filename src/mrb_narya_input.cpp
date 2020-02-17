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
#include "mrb_narya.hpp"

//MRB_BEGIN_DECL

extern NaryaRef gNaryaRef;

mrb_value mrb_narya_input_available(mrb_state *mrb, mrb_value self)
{
  auto keyboard = gNaryaRef.fmrb_system_app->m_ps2->keyboard();
  int ret = keyboard->virtualKeyAvailable();
  return ret>0 ? mrb_true_value() : mrb_false_value();
}

mrb_value mrb_narya_input_keydown(mrb_state *mrb, mrb_value self)
{
  auto keyboard = gNaryaRef.fmrb_system_app->m_ps2->keyboard();

  int cnt = keyboard->virtualKeyAvailable(); 
  if(cnt>0){
    mrb_int vkey;
    mrb_get_args(mrb, "i", &vkey);

    bool ret = keyboard->isVKDown((fabgl::VirtualKey)vkey);
    if(ret){
      keyboard->getNextVirtualKey();
    }
    if(cnt>5){
      keyboard->getNextVirtualKey();
      //keyboard->emptyVirtualKeyQueue();
    }
    //FMRB_DEBUG(FMRB_LOG::DEBUG,"kdwn:%d:%d\n",vkey,ret);
    return ret ? mrb_true_value() : mrb_false_value();
  }
  return mrb_false_value();
}

mrb_value mrb_narya_input_get_key(mrb_state *mrb, mrb_value self)
{
  auto keyboard = gNaryaRef.fmrb_system_app->m_ps2->keyboard();
  mrb_int vkey = 0;
  int cnt = keyboard->virtualKeyAvailable(); 
  if(cnt==1){
    vkey = keyboard->getNextVirtualKey();
  }else if(cnt>1){
    vkey = keyboard->getNextVirtualKey();
    keyboard->emptyVirtualKeyQueue();
  }
  return mrb_fixnum_value(vkey);
}

mrb_value mrb_narya_input_pad_down(mrb_state *mrb, mrb_value self)
{
  FmrbMrubyEngine* engine = gNaryaRef.fmrb_system_app->m_mruby_engine;
  uint8_t *map = engine->get_joypad_map();

  mrb_int pad;
  mrb_get_args(mrb, "i", &pad);
  if(pad>=(FMRB_JOYPAD_MAP_LENGTH) || pad<1){
    return mrb_false_value();
  }
  if(map[pad])return mrb_true_value();

  return mrb_false_value();
}

//MRB_END_DECL
