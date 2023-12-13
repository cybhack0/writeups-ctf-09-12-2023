def IsPrime(n):
    d = 2
    while n % d != 0:
        d += 1
    return d == n


arr = []
for i in range(2, 1000):
    if IsPrime(i):
        arr.append(i)

print(arr)

for i in arr:
    for j in arr:
        if (i*j)*3 % 16 == 15:
            print(str(i) + " " + str(j))
