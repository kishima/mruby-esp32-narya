/*
** mrb_narya.hpp - Narya header
**
** Copyright (c) KAGEYAMA Katsuhiko 2019
**
** See Copyright Notice in LICENSE
*/

#pragma once

#include "fmruby.h"
#include "fmruby_app.h"

struct NaryaRef{
  fabgl::VGAController *fmrb_vga_controller;
  fabgl::Canvas        *fmrb_canvas;
  FmrbFileService      *fmrb_storage;
  FmrbSystemApp        *fmrb_system_app;
  FmrbAudio            *fmrb_sound_engine;
};