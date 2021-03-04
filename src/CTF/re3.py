enc = "e3nifIH9b_C@n@dH"
dec = ""

for i in range(0, len(enc)):
    dec += chr(ord(enc[i]) - i)

print(dec)