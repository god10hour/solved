# [Ruby IV] Lati@s - 18630 

[문제 링크](https://www.acmicpc.net/problem/18630) 

### 성능 요약

메모리: 3060 KB, 시간: 40 ms

### 분류

수학, 정수론, 게임 이론, 선형대수학, 가우스 소거법

### 제출 일자

2026년 1월 4일 00:11:20

### 문제 설명

<p>Latias and Latios are usually living together in peace, but recently they started arguing which of them is actually better. In order to resolve this issue, they agreed to play the following game.</p>

<p>The state of the game will contain a multiset of tuples. Each of them will contain exactly n non-negative integers. In one move a player must choose any of these tuples, as long as it doesn’t contain any zero. Let’s call this tuple A. The player now performs the following move:</p>

<p>Firstly, choose some other tuple B (the multiset doesn’t have to necessarily contain any copy of B), such that B also contains n non-negative integers and each element of B is strictly smaller than the corresponding element of A; that is, B<sub>i</sub> < A<sub>i</sub> for each i = 1, 2, . . . , n. Nextly, a single copy of A is removed from the multiset. Then, for each non-empty subset X of integers from 1 to n, we add C<sub>X</sub> to the multiset. C<sub>X</sub> is a tuple such that (C<sub>X</sub>)<sub>i</sub> = B<sub>i</sub> if i ∈ X, or (C<sub>X</sub>)<sub>i</sub> = A<sub>i</sub> otherwise. For example, if A = (3, 7) and B = (0, 2), then the tuples (0, 7), (3, 2) and (0, 2) will be added to the multiset. Notice that 2<sup>n</sup> − 1 distinct tuples are always added in this step.</p>

<p>The player which is unable to make a move loses.</p>

<p>It wasn’t easy for Latias and Latios to decide what multiset should be the starting one. As they happened to have an n × n matrix M consisting of integers, they agreed to create a multiset containing n! tuples. For each permutation σ of the integers from 1 to n, the tuple (M<sub>1,σ(1)</sub>, M<sub>2,σ(2)</sub>, . . . , M<sub>n,σ(n)</sub>) is added to the multiset.</p>

<p>Latias goes first and then the players keep moving alternately. We can prove that the described game is finite, so it’s always possible to determine the winner. Your task is to decide who will win assuming that both players play optimally.</p>

### 입력 

 <p>The first line contains one integer n (1 ≤ n ≤ 150).</p>

<p>Then come n lines, each consisting of n integers. The j-th integer in the i-th of these lines equals M<sub>i,j</sub> (0 ≤ M<sub>i,j</sub> < 2<sup>64</sup>).</p>

<p>Please note that the numbers may not fit in the standard 64-bit signed type.</p>

### 출력 

 <p>Output <code>Latias</code> or <code>First</code> if the first player (Latias) will win the game. Otherwise output <code>Latios</code> or <code>Second</code>. If you decide the winner correctly, both possible words will be accepted.</p>

