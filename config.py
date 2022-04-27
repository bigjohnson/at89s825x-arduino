# Configuration options

# serialPort = '/dev/ttyACM0'
serialPort = 'COM31'

at89s8252_max_program = 0x2000
at89s8252_max_data = 0x800

at89s8253_max_program = 0x3000
at89s8253_max_data = 0x800
at89s8253_max_user_sgn = 0x40
at89s8253_max_atmel_sgn = 0x40

## Code Space
# file used for chip programming
code_targetFile = 'blink/blink.hex'
# file used for save chip read programming content
code_dumpFile   = 'blink/programdump.hex'

## Data Space
# file used for chip programming
data_targetFile = 'blink/lorem.hex'
# file used for save chip read data content
data_dumpFile = 'blink/datadump.hex'

## Atmel Sgn
atmel_sgn_dumpFile = 'blink/atmelsigndump.hex'

## User Sgn
user_sgn_File = 'blink/usersign.hex'
user_sgn_dumpFile = 'blink/usersigndump.hex'




