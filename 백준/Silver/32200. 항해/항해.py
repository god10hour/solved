n, x, y=map(int, input().split())
sws=list(map(int, input().split()))

c=0
least=0
for i in sws:
    if i<x:
        least+=i
    else:
        a=i//x
        b=i%x
        c+=a
        if b>a*(y-x):
            least+=(b-a*(y-x))
print(c)
print(least)