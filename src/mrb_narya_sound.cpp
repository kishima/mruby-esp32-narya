/*
** mrb_narya_sound.cpp - Narya Display class
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

mrb_value mrb_narya_sound_load(mrb_state *mrb, mrb_value self)
{
  FMRB_DEBUG(FMRB_LOG::DEBUG,"sound load\n");
  char * mml = NULL;
  mrb_get_args(mrb, "z", &mml);
  if(mml) gNaryaRef.fmrb_sound_engine->load_mml(mml);
  return self;
}

mrb_value mrb_narya_sound_play(mrb_state *mrb, mrb_value self)
{
  FMRB_DEBUG(FMRB_LOG::DEBUG,"sound play\n");
  gNaryaRef.fmrb_sound_engine->play_mml();
  return self;
}

mrb_value mrb_narya_sound_stop(mrb_state *mrb, mrb_value self)
{
  FMRB_DEBUG(FMRB_LOG::DEBUG,"sound stop\n");
  gNaryaRef.fmrb_sound_engine->stop();
  return self;
}

//MRB_END_DECL
