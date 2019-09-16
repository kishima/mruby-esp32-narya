module Narya
  class Color
    def initialize(r,g,b)
      @r=r
      @g=g
      @b=b
    end
    attr_accessor :r,:g,:b
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

  class Sprite
  end
  
end
