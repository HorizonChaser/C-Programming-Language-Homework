enc1 = [0x40, 0x35, 0x20, 0x56]
dec1 = "flag"
key = ""
enc2 = [0x40, 0x35, 0x20, 0x56, 0x5D, 0x18, 0x22, 0x45, 0x17, 0x2F, 0x24, 0x6E, 0x62, 
  0x3C, 0x27, 0x54, 0x48, 0x6C, 0x24, 0x6E, 0x72, 0x3C, 0x32, 
  0x45, 0x5B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]
dec2 = ""

for i in range(0, len(dec1)):
    key += chr(enc1[i] ^ ord(dec1[i]))

print(key)

for i in range(len(enc2)):
    dec2 += chr(ord(key[i % len(key)]) ^ enc2[i])
    
print(dec2)