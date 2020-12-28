from decimal import *

#循环法计算阶乘
def fact(n):
    if (n == 0):
        return 1
    ans = 1
    for i in range(1, n+1):
        ans *= i
    return ans

#计算组合数
def combination(n, k):
    if (k == 0):
        return 1
    return fact(n) // (fact(k) * fact(n - k))


p = 0.005
res = Decimal('0.0') #A1~Ak概率之和
delta = Decimal('0.0') #每一项的概率
n = 15000
a = 0.95
k = 1

# 累加计算概率
for k in range(1, 1000000):
    delta = combination(n, k) * Decimal(p)**k * Decimal(1-p)**(n-k)
    res += delta
    print("res = " + str(res) + " k = " + str(k) + " delta = " + str(delta))
    if (res >= a):
        break

print(k)
print(res)
