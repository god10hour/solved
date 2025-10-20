from statistics import mean

c=int(input())
for _ in range(c):
    a=[int(i) for i in input().split()][1:]
    m=mean(a)
    print("%.3f%%"%((1-(len([0 for i in a if i<=m])/len(a)))*100))