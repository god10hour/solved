# [Diamond V] Identity Function - 16808 

[문제 링크](https://www.acmicpc.net/problem/16808) 

### 성능 요약

메모리: 2024 KB, 시간: 0 ms

### 분류

수학, 정수론, 소수 판정, 페르마의 소정리, 오일러 피 함수

### 제출 일자

2026년 4월 6일 22:24:55

### 문제 설명

<p>You are given an integer $N$, which is greater than $1$.</p>

<p>Consider the following functions:</p>

<ul>
	<li>$f(a) = a^N \bmod N$</li>
	<li>$F_1(a) = f(a)$</li>
	<li>$F_{k+1}(a) = F_k(f(a))~~(k = 1,2,3,\ldots)$</li>
</ul>

<p>Note that we use $\mathrm{mod}$ to represent the integer modulo operation. For a non-negative integer $x$ and a positive integer $y$, $x \bmod y$ is the remainder of $x$ divided by $y$.</p>

<p>Output the minimum positive integer $k$ such that $F_k(a) = a$ for all positive integers $a$ less than $N$. If no such $k$ exists, output $-1$.</p>

### 입력 

 <p>The input consists of a single line that contains an integer $N$ ($2 \le N \le 10^9$), whose meaning is described in the problem statement.</p>

### 출력 

 <p>Output the minimum positive integer $k$ such that $F_k(a) = a$ for all positive integers $a$ less than $N$, or $-1$ if no such $k$ exists.</p>

