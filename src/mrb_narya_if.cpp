#include "mruby.h"
#include "mruby/data.h"
#include "mrb_narya.h"

#include "fabgl.h"
#include "fabutils.h"
MRB_BEGIN_DECL
/*
static void local_free(mrb_state *mrb, void* value)
{
  mrb_free(mrb,value);
}

static struct mrb_data_type mrb_cdata_type = { "CData", mrb_free };


mrb_value mrb_narya_cdata_initialize(mrb_state *mrb, mrb_value self)
{
  DATA_TYPE(self) = &mrb_cdata_type;
  DATA_PTR(self) = NULL;
}

*/
MRB_END_DECL
