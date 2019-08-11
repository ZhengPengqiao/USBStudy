#!/usr/bin/python3

import time
import Adafruit_GPIO as GPIO
import Adafruit_GPIO.FT232H as FT232H

class NeoPixel_FT232H(object):
    def __init__(self, n):
        # Create an FT232H object.
        self.ft232h = FT232H.FT232H()
        # Create a SPI interface for the FT232H object. Set the SPI bus to 6mhz.
        self.spi = FT232H.SPI(self.ft232h, max_speed_hz=6000000)
        # Create a pixel data buffer and lookup table.
        self.buffer = bytearray(n*24)
        self.lookup = self.build_byte_lookup()
    def build_byte_lookup(self):
        # Create a lookup table to map all byte values to 8 byte values which
        # represent the 6mhz SPI data to generate the NeoPixel signal for the
        # specified byte.
        lookup = {}
        for i in range(256):
            value = bytearray()

        for j in range(7, -1, -1):
            if ((i >> j) & 1) == 0:
                value.append(0b11100000)
            else:
                value.append(0b11111000)
        lookup[i] = value
        return lookup
    def set_pixel_color(self, n, r, g, b):
        # Set the pixel RGB color for the pixel at position n.
        # Assumes GRB NeoPixel color ordering, but it's easy to change below.
        index = n*24
        self.buffer[index:index+8] = self.lookup[int(g)]
        self.buffer[index+8:index+16] = self.lookup[int(r)]
        self.buffer[index+16:index+24] = self.lookup[int(b)]
    def show(self):
        # Send the pixel buffer out the SPI data output pin (D1) as a NeoPixel
        # signal.
        self.spi.write(self.buffer)
        # Run this code when the script is called at the command line:
if __name__ == '__main__':
    # Define the number of pixels in the NeoPixel strip.
    # Only up to ~340 pixels can be written using the FT232H.
    pixel_count = 16
    # Create a NeoPixel_FT232H object.
    pixels = NeoPixel_FT232H(pixel_count)
    # Animate each pixel turning red.
    # Loop through each pixel.
    for i in range(pixel_count):
        # Set the pixel color to pure red.
        pixels.set_pixel_color(i, 255, 0, 0)
    # Show the pixel buffer by sending it to the LEDs.
    pixels.show()
    # Delay for a short period of time.
    time.sleep(0.25)
    # Animate each pixel turning pure green.
    for i in range(pixel_count):
        pixels.set_pixel_color(i, 0, 255, 0)
    pixels.show()
    time.sleep(0.25)
    # Animate each pixel turning pure blue.
    for i in range(pixel_count):
        pixels.set_pixel_color(i, 0, 0, 255)
    pixels.show()
    time.sleep(0.25)
    # Animate a pattern of colors marching around the pixels.

    # Create a pattern of colors to display.
    colors = [ (255, 0, 0), (255, 255, 0), (0, 255, 0), (0, 255, 255),
    (0, 0, 255), (255, 0, 255) ]
    offset = 0
    print('Press Ctrl-C to quit.')
    while True:
        # Loop through all the pixels and set their color based on the pattern.
        for i in range(pixel_count):
            color = colors[(i+offset)%len(colors)]
            pixels.set_pixel_color(i, color[0], color[1], color[2])
        pixels.show()
        # Increase the offset to make the colors change position.
        offset += 1
        time.sleep(0.25)
