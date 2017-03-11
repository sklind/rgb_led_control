require 'serialport'
require 'byebug'

module Arduino
  SERIAL_PORT = "/dev/ttyUSB0"
  SERIAL_RATE = 115200
  PIXELS = 24

  def self.serial_port
    @port ||= SerialPort.new(SERIAL_PORT, baud: SERIAL_RATE)
  end
end

# Note: 255 is a control character, so don't try and set an led value to that
def set_pixel(pixel, red, green, blue)
  Arduino.serial_port.write("#{pixel.chr}#{red.chr}#{green.chr}#{blue.chr}#{255.chr}")    
end

while(true)
  (0..Arduino::PIXELS).each do |pixel|
    set_pixel(pixel, 0,0,50)
    sleep(0.1)
    set_pixel(pixel, 0,0,0)
    sleep(0.01)
  end
end
