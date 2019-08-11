#!/usr/bin/python3

import Adafruit_GPIO.FT232H as FT232H

# Temporarily disable FTDI serial drivers.
FT232H.use_FT232H()
# Find the first FT232H device.
ft232h = FT232H.FT232H()

print('Scanning all I2C bus addresses...')
# Enumerate all I2C addresses.

print('     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f')

for address1 in range(8):
    print('{0:01X}'.format(address1), end="0:")
    for address2 in range(16):

        address = address1*16+address2
        
        # Skip I2C addresses which are reserved.
        if address <= 2 or address >= 120:
            print('   ', end="")
            continue

        # Create I2C object.
        i2c = FT232H.I2CDevice(ft232h, address)
        # Check if a device responds to this address.
        if i2c.ping():
            print(' {0:02X}'.format(address), end="")
        else:
            print(' --', end="")
            
    print('')
    
