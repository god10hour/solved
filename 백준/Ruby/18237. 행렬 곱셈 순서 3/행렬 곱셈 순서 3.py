import sys
import heapq

input=sys.stdin.readline

class Harc:
    __slots__=("idx", "sta", "end", "low", "mul", "base", "num", "den")
    def __init__(self):
        self.idx=0
        self.sta=0;
        self.end=0
        self.low=0
        self.mul=0;
        self.base=0
        self.num=0;
        self.den=0
    def contains(self, b) -> bool:
        return self.sta<=b.sta and b.end<=self.end
    def S(self) -> int:
        return (self.num//self.den) if self.den!=0 else (1<<61)

def main():
    N=int(input().strip())
    w=[0]*(N+2)
    for i in range(1, N+1):
        r, c=map(int, input().split())
        w[i]=r
        w[i+1]=c
    n=N+1
    if N<2:
        print(0)
        return

    # rotate so that global minimum is at index 1
    V1=1
    for i in range(2, n+1):
        if w[i]<w[V1]:
            V1=i
    # rotate w[1..n]
    w[1:n+1]=w[V1:n+1]+w[1:V1]
    w.append(0)  # ensure space for index n+1
    w[n+1]=w[1]

    # collect candidate h-arcs (one-sweep)
    arcs=[]
    st=[]
    tmp=[]
    for i in range(1, n+1):
        while len(st)>=2 and w[st[-1]]>w[i]:
            tmp.append((st[-2], i))
            st.pop()
        st.append(i)
    for a, b in tmp:
        if a==1 or b==1:
            continue
        arcs.append((a, b))

    # CP: prefix of adjacent products
    CP=[0]*(n+2)
    for i in range(2, n+2):
        CP[i]=CP[i-1]+w[i-1]*w[i]

    # build arcs + containment tree
    Narcs=0
    K=1+1+len(arcs)  # rough cap; indices will be 1..Narcs
    h=[None]*(K)
    for i in range(K):
        h[i]=Harc()

    def newArc(sti, eni):
        nonlocal Narcs
        Narcs+=1
        x=h[Narcs]
        x.idx=Narcs
        x.sta=sti;
        x.end=eni
        x.low=sti if w[sti]<w[eni] else eni
        x.mul=w[sti]*w[eni];
        x.base=CP[eni]-CP[sti]-x.mul
        x.num=0;
        x.den=0

    tree=[[] for _ in range(len(arcs)+2)]
    st=[]
    newArc(1, n+1)  # super-root
    for (a, b) in arcs:
        newArc(a, b)
        while st and h[Narcs].contains(h[st[-1]]):
            tree[Narcs].append(st.pop())
        st.append(Narcs)
    while st:
        tree[1].append(st.pop())
    con=[[] for _ in range(n+2)]  # con stacks per vertex
    sub=[0]*(Narcs+2)
    qid=list(range(Narcs+2))  # give each node its own pq id initially
    pqs=[[] for _ in range(Narcs+2)]
    seq=0  # tie-break for heap

    def getM(node: int) -> int:
        if node==1:
            return w[1]*w[2]+w[1]*w[n]
        cur=h[node]
        if cur.sta==cur.low:
            if not con[cur.sta] or not cur.contains(con[cur.sta][-1]):
                return w[cur.sta]*w[cur.sta+1]
            return con[cur.sta][-1].mul
        else:
            if not con[cur.end] or not cur.contains(con[cur.end][-1]):
                return w[cur.end]*w[cur.end-1]
            return con[cur.end][-1].mul
    def add(node: int):
        nonlocal seq
        cur=h[node]
        sup=cur.S()
        heapq.heappush(pqs[qid[node]], (-sup, seq, cur))
        seq+=1
        con[cur.sta].append(cur)
        con[cur.end].append(cur)
    def remove(node: int):
        heap=pqs[qid[node]]
        _, _, top=heapq.heappop(heap)
        con[top.sta].pop()
        con[top.end].pop()
        return top
    def merge(node: int):
        # pick child with maximum subtree size
        Midx=-1
        for ch in tree[node]:
            if Midx==-1 or sub[Midx]<sub[ch]:
                Midx=ch
        if Midx==-1:
            return
        # adopt that child's pq id
        qid[node]=qid[Midx]
        curheap=pqs[qid[node]]
        # merge other children heaps into curheap
        for ch in tree[node]:
            if ch==Midx:
                continue
            childheap=pqs[qid[ch]]
            while childheap:
                heapq.heappush(curheap, heapq.heappop(childheap))
    # iterative DFS (post-order), wrapped in a lambda-like function
    def dfs(start: int):
        nonlocal seq
        stk=[(start, 0)]  # (node, state) 0=push children, 1=process
        while stk:
            node, state=stk[-1]
            if state==0:
                stk[-1]=(node, 1)
                sub[node]=1
                if tree[node]:
                    for ch in tree[node]:
                        stk.append((ch, 0))
                    continue
                # leaf
                cur=h[node]
                # qid[node] already unique
                cur.den=cur.base
                cur.num=w[cur.low]*(cur.den+cur.mul-getM(node))
                add(node)
                stk.pop()
            else:
                # process after children
                cur=h[node]
                if tree[node]:
                    cur.den=cur.base
                    for ch in tree[node]:
                        sub[node]+=sub[ch]
                        cur.den-=h[ch].base
                    cur.num=w[cur.low]*(cur.den+cur.mul-getM(node))
                    merge(node)
                    PQ=pqs[qid[node]]
                    # delete loop (fan better)
                    while PQ and (-PQ[0][0])>=w[cur.low]:
                        topArc=remove(node)
                        cur.den+=topArc.den
                        cur.num=w[cur.low]*(cur.den+cur.mul-getM(node))
                    # condense loop (child block better)
                    while PQ and (cur.S()<=(-PQ[0][0])):
                        topArc=remove(node)
                        cur.den+=topArc.den
                        cur.num+=topArc.num
                    add(node)
                stk.pop()

    dfs(1)
    # sum remaining nums in root pq
    r=0
    root=pqs[qid[1]]
    while root:
        _, _, arc=heapq.heappop(root)
        r+=arc.num
    print(r)

if __name__=="__main__":
    main()