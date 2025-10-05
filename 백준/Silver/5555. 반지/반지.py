s=input()
r=0
for i in range(int(input())):
    t=input()
    t+=t
    if s in t:
        r+=1
print(r)