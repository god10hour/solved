# [Diamond II] 정수론과 응용: 레시테이션 - 16141 

[문제 링크](https://www.acmicpc.net/problem/16141) 

### 성능 요약

메모리: 15736 KB, 시간: 52 ms

### 분류

수학, 정수론, 뫼비우스 반전 공식

### 제출 일자

2026년 1월 8일 23:06:02

### 문제 설명

<p>정수론과 응용 조교를 맡게 된 청응이는 바뻐 레시테이션 문제를 준비할 여를이 없었다. 수강생들이 이번 주 수업 때 오일러 피 함수(Euler's totient function, $\varphi$)를 배운 것을 알고 어떤 $n$을 주면 $\varphi(n)$을 구하라는 문제를 많이 내는 것으로 넘어가려고 했다.</p>

<p>\begin{equation*}<br>
\varphi(n)=\left|\left\{k\in\mathbb{N}\::\:k\leq n,\:\gcd(k,n)=1\right\}\right|<br>
\end{equation*}</p>

<p>그러나 이 문제는 소인수분해만 하면 구하는 공식이 너무 잘 알려져 있어 레시테이션 시간을 전부 넘기지 못한다는 것을 깨달았다. 그래서 오일러 피 함수를 일반화한 요르단 함수(Jordan's totient function)를 구하라는 문제를 준비했다.</p>

<p>\begin{equation*}<br>
\varphi(n,v)=\left|\left\{(k_1,k_2,\cdots,k_v)\in\mathbb{N}^v\::\:\forall i,\:k_i\leq n,\:\gcd(k_1,k_2,\cdots,k_v,n)=1\right\}\right|<br>
\end{equation*}</p>

<p>그러나 이 문제도 너무 쉽게 풀릴 것이라는 고민에 빠졌다. 그래서 더 어려운 문제를 생각하던 도중 가우스와 관련된 유명한 일화가 생각났다.</p>

<p>"가우스가 어렸을 때, 가우스의 지도 교사였던 뷔트너 선생님이 $1$부터 $100$까지 수들의 합을 구하라고 했고, 가우스는 제일 빠르게 $5050$이라는 답을 냈다."</p>

<p>이에 영감을 받아 $\sum\limits_{i=1}^n\sum\limits_{u=1}^{v}\varphi(i,u)$를 구하라고 문제를 냈다. 이제 이 문제를 푸는 것은 여러분 몫이다. $n$과 $v$가 주어지면 $\sum\limits_{i=1}^n\sum\limits_{u=1}^{v}\varphi(i,u)$를 구하는 프로그램을 작성하시오.</p>

### 입력 

 <p>입력은 한 줄만 주어지며 두 자연수 $n$과 $v$가 주어진다. 입력은 $1\leq n\leq 10^9$와 $1\leq v\leq 10^2$을 만족한다.</p>

### 출력 

 <p>$\sum\limits_{i=1}^n\sum\limits_{u=1}^{v}\varphi(i,u)$를 출력한다. 답이 몹시 커질 수 있으니 $10^9+7$로 나눈 나머지를 출력하라.</p>

