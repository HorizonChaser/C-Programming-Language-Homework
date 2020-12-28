from decimal import *
import random

#计算二项分布
def binomialDist(n, p):
    ret = 0
    for a in range(0, n):
        if (random.random() <= p):
            ret += 1
    return ret

a = 0.8
p = 0.005
n = 15000
cnt = 10000000
ms80 = 82
ms90 = 86
ms95 = 89
#ansX为满足概率为X时的次数
ans80 = 0
ans90 = 0
ans95 = 0

for i in range(1, 100000):
    t = binomialDist(n, p)
    if (t <= ms80):
        ans80 += 1
    if (t <= ms90):
        ans90 += 1
    if (t <= ms95):
        ans95 += 1

print(ans80)
print(str(ans80 / 1000) + "%")
print(ans90)
print(str(ans90 / 1000) + "%")
print(ans95)
print(str(ans95 / 1000) + "%")
