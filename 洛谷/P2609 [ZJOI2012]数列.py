T = int(input())
for i in range(0, T):
    x = int(input())
    l = 1
    r = 0
    while x:
        if x & 1:
            r += l
        else:
            l += r
        x //= 2
    print(r)
