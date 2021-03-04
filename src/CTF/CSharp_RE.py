xored = "63143B6F8007B98C53CA2149822777B3566F9241"
dec = ""

for c in xored:
    for i in range(128):
        if i ^ ord(c) == 0:
            dec = dec + chr(i)

print(dec)