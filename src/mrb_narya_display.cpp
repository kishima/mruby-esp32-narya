#include "mruby.h"
#include "mruby/data.h"
#include "mrb_narya.h"

#include "fabgl.h"
#include "fabutils.h"

MRB_BEGIN_DECL

mrb_value mrb_narya_display_draw_circle(mrb_state *mrb, mrb_value self)
{
  mrb_int x;
  mrb_int y;
  mrb_int r;
  mrb_int col;
  mrb_get_args(mrb, "iiii", &x,&y,&r,&col);

  Color color;
  switch(col){
    case 0:
      color = Color::Black;
      break;
    case 1:
      color = Color::Red;
      break;
    case 2:
      color = Color::Green;
      break;
    case 3:
      color = Color::Yellow;
      break;
    case 4:
      color = Color::Blue;
      break;
    case 5:
      color = Color::Magenta;
      break;
    case 6:
      color = Color::Cyan;
      break;
    case 7:
      color = Color::White;
      break;
    default:
      color = Color::Black;
      break;
  }

  Canvas.setBrushColor(color);
  Canvas.fillEllipse(x, y, r, r);
  return self;
}

mrb_value mrb_narya_display_draw_text(mrb_state *mrb, mrb_value self)
{
  return self;
}

mrb_value mrb_narya_display_clear(mrb_state *mrb, mrb_value self)
{
  Canvas.setBrushColor(Color::Black);
  Canvas.clear();
  return self;
}

mrb_value mrb_narya_display_swap(mrb_state *mrb, mrb_value self)
{
  Canvas.swapBuffers();
  return self;
}

MRB_END_DECL
