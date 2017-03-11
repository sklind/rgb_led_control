Control an RGB led strip from a computer over the serial port (using an ardunio as the middle man).


* Connect to the serial port using whatever library or tool you prefer
* send 8 bit bytes, terminated by a byte with value 255 to signal the end of the command 


| byte 0        | byte 1 | byte 2 | byte 3 | byte 5                 |
| ------------- | ------ | ------ | ------ | ---------------------- |
| pixel number  | red    | blue   |  green | stop byte (always 255) |
