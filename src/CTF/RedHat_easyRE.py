enc = "Iodl>Qnb(ocy\x7Fy.i\x7Fd`3w}wek9{iy=~yL@EC"
dec = ""

for i in range(0, len(enc)):
    dec += chr(ord(enc[i]) ^ i)

print(dec)