# mruby-esp32-narya   [![Build Status](https://travis-ci.org/kishima/mruby-esp32-narya.svg?branch=master)](https://travis-ci.org/kishima/mruby-esp32-narya)
Narya class
## install by mrbgems
- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

    # ... (snip) ...

    conf.gem :github => 'kishima/mruby-esp32-narya'
end
```
## example
```ruby
p Narya.hi
#=> "hi!!"
t = Narya.new "hello"
p t.hello
#=> "hello"
p t.bye
#=> "hello bye"
```

## License
under the GPLv3 License:
- see LICENSE file
