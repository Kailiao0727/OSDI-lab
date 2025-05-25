import serial, struct, zlib

def send_kernel(port, kernel_path):
  with open(kernel_path, "rb") as f:
    kernel_data = f.read()
  
  header = struct.pack("<IIII", 
    0x544F4F42,          # Magic
    len(kernel_data),    # Size
    zlib.crc32(kernel_data),  # Checksum
  )
  
  with serial.Serial(port, 115200, timeout=1) as ser:
    ser.write(header)
    if ser.read(1) != b'\x06':  # Wait for ACK
      raise Exception("Header rejected")
    
    ser.write(kernel_data)
    if ser.read(1) != b'\x06':  # Final ACK
      raise Exception("Transfer failed")