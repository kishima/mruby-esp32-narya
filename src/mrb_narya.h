/*
** mrb_narya.h - Narya class
**
** See Copyright Notice in LICENSE
*/

#ifndef MRB_NARYA_H
#define MRB_NARYA_H

MRB_BEGIN_DECL

extern struct RClass *narya_data_class;

void mrb_mruby_narya_gem_init(mrb_state *mrb);

//mrb_value mrb_narya_cdata_initialize(mrb_state *mrb, mrb_value self);

mrb_value mrb_narya_display_draw_circle(mrb_state *mrb, mrb_value self);
mrb_value mrb_narya_display_draw_text(mrb_state *mrb, mrb_value self);
mrb_value mrb_narya_display_clear(mrb_state *mrb, mrb_value self);
mrb_value mrb_narya_display_swap(mrb_state *mrb, mrb_value self);

mrb_value mrb_narya_sprite_initialize(mrb_state *mrb, mrb_value self);
mrb_value mrb_narya_sprite_move_to(mrb_state *mrb, mrb_value self);
mrb_value mrb_narya_sprite_move(mrb_state *mrb, mrb_value self);

MRB_END_DECL

#endif
