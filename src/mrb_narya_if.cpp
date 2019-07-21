#include "mruby.h"
#include "mruby/data.h"
#include "mrb_narya.h"

//#include "freertos/FreeRTOS.h"
//#include "freertos/task.h"

//#include "fabgl.h"

/* 
typedef struct {
  char *str;
  mrb_int len;
} mrb_narya_data;


static const struct mrb_data_type mrb_narya_data_type = {
  "mrb_narya_data", mrb_free,
};
*/

MRB_BEGIN_DECL

mrb_value mrb_narya_init(mrb_state *mrb, mrb_value self)
{
  /* 
  mrb_narya_data *data;
  char *str;
  mrb_int len;

  data = (mrb_narya_data *)DATA_PTR(self);
  if (data) {
    mrb_free(mrb, data);
  }
  DATA_TYPE(self) = &mrb_narya_data_type;
  DATA_PTR(self) = NULL;

  mrb_get_args(mrb, "s", &str, &len);
  data = (mrb_narya_data *)mrb_malloc(mrb, sizeof(mrb_narya_data));
  data->str = str;
  data->len = len;
  DATA_PTR(self) = data;
  */

  return self;
}

mrb_value mrb_narya_hello(mrb_state *mrb, mrb_value self)
{
  //mrb_narya_data *data = DATA_PTR(self);
  //return mrb_str_new(mrb, data->str, data->len);
  return self;
}

mrb_value mrb_narya_hi(mrb_state *mrb, mrb_value self)
{
  //return mrb_str_new_cstr(mrb, "hi!!");
  return self;
}

MRB_END_DECL
