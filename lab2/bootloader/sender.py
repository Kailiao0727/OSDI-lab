#!/usr/bin/env python3
# tools/sender.py
import serial, struct, zlib, sys

def send_kernel(port, kernel_path):
    with open(kernel_path, "rb") as f:
        kernel_data = f.read()
    
    header = struct.pack("<III",  # Removed unused entry field
        0x544F4F42,              # Magic
        len(kernel_data),        # Size
        zlib.crc32(kernel_data) & 0xFFFFFFFF # Checksum
    )
    
    with serial.Serial(port, 115200, timeout=5) as ser:  # Increased timeout
        # ack = ser.read(1)
        # print(ack)
        print("Sending header...")
        ser.write(header)
        
        ack = ser.read(1)
        if ack == b'\x15':
            print(f"Magic unmatched (ACK: {ack})")
            sys.exit(1)
        if ack != b'\x06':
            print(f"Header rejected (ACK: {ack})")
            sys.exit(1)
        
        print(f"Sending kernel with size: {len(kernel_data)}")
        ser.write(kernel_data)
        print("Kernel sent");
        ack = ser.read(1)
        if ack != b'\x06':
            print(f"Transfer failed (ACK: {ack})")
            sys.exit(1)
        
        # Read back the kernel for verification
        print("Reading back kernel for verification...")
        received = ser.read(len(kernel_data))
        if received != kernel_data:
            print("Verification failed: received data does not match sent data!")
            sys.exit(1)
        else:
            print("Verification successful: kernel received correctly by bootloader!")
        print("Transfer successful!")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <port> <kernel.img>")
        sys.exit(1)
    
    send_kernel(sys.argv[1], sys.argv[2])