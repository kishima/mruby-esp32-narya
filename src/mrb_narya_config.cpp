/*
** mrb_narya_condif.cpp - Narya Config module
**
** Copyright (c) KAGEYAMA Katsuhiko 2020
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

MRB_BEGIN_DECL


/**
 *  get Family mruby version
 **/
mrb_value mrb_narya_config_firmware_ver(mrb_state *mrb, mrb_value self)
{
  return mrb_str_new_lit_frozen(mrb,FMRB_VERSION);
}

/**
 *  get Narya mrbgem version
 **/
mrb_value mrb_narya_config_narya_ver(mrb_state *mrb, mrb_value self)
{
  return mrb_str_new_lit_frozen(mrb,ESP32_NARYA_VERSION);
}


MRB_END_DECL
