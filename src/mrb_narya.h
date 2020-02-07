/*
** mrb_narya.h - Narya class
**
** See Copyright Notice in LICENSE
*/

#ifndef MRB_NARYA_H
#define MRB_NARYA_H

MRB_BEGIN_DECL

#define ESP32_NARYA_VERSION "0.1.0"

extern struct RClass *narya_data_class;

void mrb_mruby_narya_gem_init(mrb_state *mrb);

void mrb_narya_init_resouce(void);

//Display module
mrb_value mrb_narya_display_draw_circle(mrb_state *mrb, mrb_value self);
mrb_value mrb_narya_display_draw_text(mrb_state *mrb, mrb_value self);
mrb_value mrb_narya_display_clear(mrb_state *mrb, mrb_value self);
mrb_value mrb_narya_display_load_bitmap(mrb_state *mrb, mrb_value self);
mrb_value mrb_narya_display_draw_picture(mrb_state *mrb, mrb_value self);
mrb_value mrb_narya_display_draw_line(mrb_state *mrb, mrb_value self);
mrb_value mrb_narya_display_draw_rect(mrb_state *mrb, mrb_value self);
mrb_value mrb_narya_display_draw_pixel(mrb_state *mrb, mrb_value self);

mrb_value mrb_narya_display_swap(mrb_state *mrb, mrb_value self);
mrb_value mrb_narya_display_scroll(mrb_state *mrb, mrb_value self);
mrb_value mrb_narya_display_width(mrb_state *mrb, mrb_value self);
mrb_value mrb_narya_display_height(mrb_state *mrb, mrb_value self);

//Input module
mrb_value mrb_narya_input_available(mrb_state *mrb, mrb_value self);
mrb_value mrb_narya_input_keydown(mrb_state *mrb, mrb_value self);
mrb_value mrb_narya_input_get_key(mrb_state *mrb, mrb_value self);
mrb_value mrb_narya_input_pad_down(mrb_state *mrb, mrb_value self);

//Bitmap class
mrb_value mrb_narya_bitmap_initialize(mrb_state *mrb, mrb_value self);
mrb_value mrb_narya_bitmap_draw(mrb_state *mrb, mrb_value self);
mrb_value mrb_narya_bitmap_load(mrb_state *mrb, mrb_value self);

//Sprite class
mrb_value mrb_narya_sprite_initialize(mrb_state *mrb, mrb_value self);
mrb_value mrb_narya_sprite_move_to(mrb_state *mrb, mrb_value self);
mrb_value mrb_narya_sprite_move(mrb_state *mrb, mrb_value self);

//Sound class


//Config module
mrb_value mrb_narya_config_firmware_ver(mrb_state *mrb, mrb_value self);
mrb_value mrb_narya_config_narya_ver(mrb_state *mrb, mrb_value self);


MRB_END_DECL

#endif
