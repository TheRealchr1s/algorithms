n, x = (int(num) for num in input().split())

res = 0

for i in range(n + 1):
    for j in range(n + 1):
        res += 1 if x == i * j else 0

print(res)
