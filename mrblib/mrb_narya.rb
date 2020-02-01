module Narya
  class Color
    attr_accessor :r,:g,:b
    def initialize(r,g,b)
      @r=r
      @g=g
      @b=b
    end
    def to_s
      "#{r},#{g},#{b}"
    end
  end

  module Display
  end

  module Input
  end

  module Image
  end

  module Sound
  end

  class Bitmap
    attr_reader :width,:height
  end

  class Sprite
  end

  module Key
    K_NONE   = 0
    K_SPACE  = 1
    K_0      = 2
    K_1      = 3
    K_2      = 4
    K_3      = 5
    K_4      = 6
    K_5      = 7
    K_6      = 8
    K_7      = 9
    K_8      = 10
    K_9      = 11
    K_a      = 22
    K_b      = 23
    K_c      = 24
    K_d      = 25
    K_e      = 26
    K_f      = 27
    K_g      = 28
    K_h      = 29
    K_i      = 30
    K_j      = 31
    K_k      = 32
    K_l      = 33
    K_m      = 34
    K_n      = 35
    K_o      = 36
    K_p      = 37
    K_q      = 38
    K_r      = 39
    K_s      = 40
    K_t      = 41
    K_u      = 42
    K_v      = 43
    K_w      = 44
    K_x      = 45
    K_y      = 46
    K_z      = 47
    K_A      = 48
    K_B      = 49
    K_C      = 50
    K_D      = 51
    K_E      = 52
    K_F      = 53
    K_G      = 54
    K_H      = 55
    K_I      = 56
    K_J      = 57
    K_K      = 58
    K_L      = 59
    K_M      = 60
    K_N      = 61
    K_O      = 62
    K_P      = 63
    K_Q      = 64
    K_R      = 65
    K_S      = 66
    K_T      = 67
    K_U      = 68
    K_V      = 69
    K_W      = 70
    K_X      = 71
    K_Y      = 72
    K_Z      = 73
    K_ESCAPE         = 125
    K_RETURN         = 144
    K_UP             = 151
    K_DOWN           = 153
    K_LEFT           = 155
    K_RIGHT          = 157
  end
end
