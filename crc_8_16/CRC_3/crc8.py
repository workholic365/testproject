class CRC8(object):
    # Precompute the table
    def __init__(self, poly, init):
        self.crctab = []
        self.init = init

        current_residue = poly
        for i in range(0, 8):
            self.crctab.append(current_residue)
            current_residue <<= 1
            if (current_residue & 0x100):
                current_residue = (current_residue & 0xff) ^ poly

    # Single iteration
    def single(self, left, right):
        mask = 1
        for residue in self.crctab:
            if right & mask:
                left ^= residue
            mask <<= 1
        return left

    # Check if the packet's CRC8 is valid
    def check(self, bytelist):
        crc = self.compute(bytelist)
        if crc:
            return False
        return True

    # Compute the CRC8 of a list of bytes
    def compute(self, bytelist):
        current_crc = self.init
        for byte in bytelist:
            current_crc = self.single(byte, current_crc)
        return current_crc


