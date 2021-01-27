#!/usb/bin/python
#

from crc8 import CRC8

CRC_POLY = 0x1d
CRC_INIT = 0xb0
sample = [ 0x20, 0x00, 0x20, 0x0c, 0x04, 0xff, 0x00, 0x00 ]

crc8 = CRC8(CRC_POLY, CRC_INIT)

# Compute the CRC of the zero-padded packet
sample[-1] = crc8.compute(sample)
print("Computed crc: 0x%02x" % sample[-1])

# Check that the packet is valid
if crc8.check(sample):
    print("CRC8 valid")
else:
    print("CRC8 invalid")




