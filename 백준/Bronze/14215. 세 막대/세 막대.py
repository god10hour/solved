a, b, c=map(int, input().split())
r=0
for i in range(1, a+1):
    for j in range(1, b+1):
        for k in range(1, c+1):
            ls=[i, j, k]
            ls.sort()
            if ls[0]+ls[1]>ls[2]:
                r=max(r, i+j+k)      
print(r)