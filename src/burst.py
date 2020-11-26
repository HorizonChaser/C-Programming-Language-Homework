table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz01234{}789+/="

# c = "9A879C B5FE58 D14AFE 0BED6C FAFDEB CBE834 A3438E A3477A"

c="9E9B9C B5FE70 D30FB2 D14F9C 027FAB DE5965 63E740 9DCDFA"

c = c.split()
for i in range(len(c)):
    c[i] = eval("0x"+c[i])

print(c)
for x in c:
    t = 0
    for i in range(len(table)):
        for j in range(len(table)):
            for k in range(len(table)):
                for l in range(len(table)):
                    t = (0 << 6) | i
                    t = (t << 6) | j
                    t = (t << 6) | k
                    t = (t << 6) | l
                    if(t == x):
                        print(table[i]+table[j]+table[k]+table[l])
