require 'serialport'
require 'byebug'

PIXELS = 24
SERIAL_PORT = "/dev/ttyUSB0"
SERIAL_RATE = 115200

$s = SerialPort.new(SERIAL_PORT, baud: SERIAL_RATE)

def set_pixel(pixel, red, green, blue)
  red   = clamp_value(red)
  green = clamp_value(green)
  blue  = clamp_value(blue)

  string = control_string(pixel, red, green, blue)

  $s.write(string)    
end

def control_string(pixel, red, green, blue)
  "#{pixel.chr}#{red.chr}#{green.chr}#{blue.chr}#{255.chr}"
end

# 255 and 254 are control characters, so if someone tries to use that, just reduce the brightness
def clamp_value(value)
  [value, 253].min
end

while(true)
  sleep_time = 0.1

  (0..PIXELS).each do |pixel|
    set_pixel(pixel, 0,0,50)
    sleep(0.1)
    set_pixel(pixel, 0,0,0)
    sleep(0.01)
  end
end
