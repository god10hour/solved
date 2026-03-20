n=int(input())
L=[input() for _ in range(n)]
k=int(input())

digit='0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ'

PD={}
for s in L:
    for i in range(1, len(s)+1):
        if PD.get(s[-i]) is None:
            PD[s[-i]]=0
        PD[s[-i]]+=(35-int(s[-i], 36))*(36**(i-1))

tmp=list(PD.items())
tmp.sort(key=lambda x: x[1])

for i in range(k):
    if not tmp: break
    cur=tmp.pop()
    for j in range(n):
        L[j]=L[j].replace(cur[0], 'Z')

buffer=0
for e in L:
    for i in range(1, len(e)+1):
        buffer+=int(e[-i], 36)*(36**(i-1))
result=""
while buffer>0:
    result=digit[buffer%36]+result
    buffer//=36

if not result:
    print(0)
    exit()
print(result)