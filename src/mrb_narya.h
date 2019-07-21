/*
** mrb_narya.h - Narya class
**
** See Copyright Notice in LICENSE
*/

#ifndef MRB_NARYA_H
#define MRB_NARYA_H

MRB_BEGIN_DECL
void mrb_mruby_narya_gem_init(mrb_state *mrb);

mrb_value mrb_narya_init(mrb_state *mrb, mrb_value self);
mrb_value mrb_narya_start(mrb_state *mrb, mrb_value self);
mrb_value mrb_narya_demo(mrb_state *mrb, mrb_value self);

MRB_END_DECL

#endif
