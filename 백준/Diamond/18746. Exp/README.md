# [Diamond I] Exp - 18746 

[문제 링크](https://www.acmicpc.net/problem/18746) 

### 성능 요약

메모리: 80152 KB, 시간: 476 ms

### 분류

수학, 다이나믹 프로그래밍, 미적분학, 생성 함수

### 제출 일자

2026년 4월 23일 14:49:17

### 문제 설명

<p>Find the expected amount of experience a hero will get for beating n monsters one by one, given that beating each monster gives the hero i units of experience (0 ≤ i ≤ k) with probability p<sub>i</sub> independently, but if the hero gets more than x units of experience in total, their experience is capped to exactly x units, and display it modulo 998 244 353.</p>

### 입력 

 <p>The first line contains three integers n, k, and x (1 ≤ n ≤ 10<sup>7</sup>; 1 ≤ k ≤ 100; 1 ≤ x ≤ min(10<sup>7</sup>, 5·10<sup>7</sup>/k)).</p>

<p>The second line contains k + 1 real numbers p<sub>0</sub>, p<sub>1</sub>, . . . , p<sub>k</sub> (0 < p<sub>i</sub> < 1), given with exactly 4 decimal digits. The sum of p<sub>i</sub> is equal to 1.</p>

### 출력 

 <p>Display the expected amount of experience the hero will get.</p>

<p>It can be shown that the sought number can be represented as an irreducible fraction p/q such that q ≢ 0 (mod 998 244 353). Then, there exists a unique integer r such that r · q ≡ p (mod 998 244 353) and 0 ≤ r < 998 244 353, so display this r.</p>

