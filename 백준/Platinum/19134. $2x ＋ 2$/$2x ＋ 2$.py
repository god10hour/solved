n=int(input())
n+=2
ans=-1
k=1
while n>0:
    ans+=n*k
    n//=2
    k*=-1
print(ans)