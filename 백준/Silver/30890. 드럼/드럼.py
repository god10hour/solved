import sys

a, b=map(int, sys.stdin.read().split())
i=j=1
r=[]
inf=float('inf')

while i<=a or j<=b:
    L=i*b if i<=a else inf
    R=j*a if j<=b else inf
    if L<R: r.append('1'); i+=1
    elif L>R: r.append('2'); j+=1
    else: r.append('3'); i+=1; j+=1

print(''.join(r))
