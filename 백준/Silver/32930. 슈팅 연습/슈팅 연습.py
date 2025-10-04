import sys

n, m=map(int, sys.stdin.readline().split())
cur=[tuple(map(int, sys.stdin.readline().split())) for _ in range(n)]
nxt=[tuple(map(int, sys.stdin.readline().split())) for _ in range(m)]
cx=cy=0
score=0
p=0
for _ in range(m):
    k=d=-1
    for i, (x, y) in enumerate(cur):
        dx=x-cx
        dy=y-cy
        d2=dx*dx+dy*dy
        if d2>d:
            d=d2; k=i
    score+=d
    cx, cy=cur[k]
    last=cur.pop()
    if k<len(cur):
        cur[k]=last
    if p<m:
        cur.append(nxt[p])
        p+=1
print(score)