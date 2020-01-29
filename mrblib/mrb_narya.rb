module Narya
  class Color
    attr_accessor :r,:g,:b
    def initialize(r,g,b)
      @r=r
      @g=g
      @b=b
    end
  end

  RED = Color.new(3,0,0).freeze
  GREEN = Color.new(0,3,0).freeze
  BLUE = Color.new(0,0,3).freeze
  WHITE = Color.new(3,3,3).freeze
  BLACK = Color.new(0,0,0).freeze

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
    K_ESCAPE         = 125
    K_RETURN         = 144
    K_UP             = 151
    K_DOWN           = 153
    K_LEFT           = 155
    K_RIGHT          = 157
  end
end
