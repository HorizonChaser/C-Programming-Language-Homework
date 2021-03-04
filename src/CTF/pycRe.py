code = [
    '\x1f',
    '\x12',
    '\x1d',
    '(',
    '0',
    '4',
    '\x01',
    '\x06',
    '\x14',
    '4',
    ',',
    '\x1b',
    'U',
    '?',
    'o',
    '6',
    '*',
    ':',
    '\x01',
    'D',
    ';',
    '%',
    '\x13']

flag = ""
dec = "GWHT{Just_Re_1s_Ha66y!}"

for i in range(len(code) -2, -1, -1):
    code[i] = chr(ord(code[i]) ^ ord(code[i + 1]))
    
for i in range(0, len(code)):
    print(ord(code[i]), end=" ")
print("\n")

for c in dec:
    print(str(ord(c)), end = " ")

for i in range(0, len(code)):
    for c in range(0, 256):
        num = ((c + i) % 128 + 128) % 128
        ccc = ord(code[i])
        if (num == ccc):
            print(str(i) + " " + str(ccc) + " " + str(num))
            flag += chr(num)
            break

print(flag)

for i in range(0, len(code)):
    print(chr((ord(code[i]) - i) %128), end = "")
