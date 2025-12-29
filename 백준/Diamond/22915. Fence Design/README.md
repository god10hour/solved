# [Diamond V] Fence Design - 22915 

[문제 링크](https://www.acmicpc.net/problem/22915) 

### 성능 요약

메모리: 35204 KB, 시간: 3180 ms

### 분류

볼록 껍질, 분할 정복, 오일러 지표 (χ=V-E+F), 기하학

### 제출 일자

2025년 12월 29일 21:19:04

### 문제 설명

<p>You are hired as a temporary employee of the Fence Construction Company and have been tasked with finishing the design of the fencing for a field. Each fence must run in a straight line between two poles. Each pole occupies a single point and the location of each pole is fixed. No three poles are collinear. Fences cannot intersect each other, except possibly at their endpoints (the poles).</p>

<p>The design was started by someone else, but they quit the project after adding exactly two fences. You need to finish their design. To impress your bosses and clients, you want the design to have as many fences as possible, regardless of their lengths.</p>

<p>Given the positions of the poles and the already-built fences, please find a way to add as many fences as possible such that no pair of fences (new or existing) intersect each other, except possibly at their endpoints (the poles).</p>

### 입력 

 <p>The first line of the input gives the number of test cases, T. T test cases follow. Each test case starts with a single line containing an integer N, indicating the number of poles. Then, N lines follow. The i-th of these lines contains two integers X<sub>i</sub> and Y<sub>i</sub>, representing the X and Y coordinates of the i-th pole's position. The last two lines for each test case represent the two existing fences. These two lines contain two integers each: P<sub>k</sub> and Qk, representing that the k-th existing fence runs between the P<sub>k</sub>-th and the Q<sub>k</sub>-th pole (poles are numbered starting from 1).</p>

### 출력 

 <p>For each test case, output one line containing <code>Case #x: y</code>, where x is the test case number (starting from 1) and y is the maximum number of fences that can be added to the design (not including the existing ones). Then, output y more lines. Each line must contain two distinct integers i and j (both between 1 and N, inclusive), representing a different fence that connects the i-th and j-th poles. No pair of the y+2 fences (the existing fences as well as the ones you have added) may overlap, except possibly at their endpoints.</p>

