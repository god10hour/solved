# [Ruby III] The Cartesian Job - 27769 

[문제 링크](https://www.acmicpc.net/problem/27769) 

### 성능 요약

메모리: 3956 KB, 시간: 180 ms

### 분류

수학, 그래프 이론, 기하학, 누적 합, 확률론, 값 / 좌표 압축

### 제출 일자

2026년 4월 25일 21:49:47

### 문제 설명

<p>You may have heard of the platinum-iridium cylinder that serves as the standard for the kilogram, but did you know that there is a special line segment used as the standard for the kilometer? It runs from (0, 0) to (0, 1000) in a 2D plane in a confidential and very flat location.</p>

<p>Naturally, this segment is extremely valuable, so it is protected by <b>N</b> rotating surveillance lasers, which are rays in the 2D plane. Each laser has a fixed endpoint, and it rotates around that endpoint at a constant speed of 1 revolution per second. Whether each laser rotates clockwise or counterclockwise is chosen uniformly and independently at random by the security system.</p>

<p>Lasers are not blocked by other lasers or their endpoints, or the segment itself. No laser has an endpoint on the segment.</p>

<p>You have been hired to audit the security system, but all you have to work with is a single snapshot from an instant in time, which shows the endpoint and orientation (at that instant) of each laser. Since the image is just a snapshot, you have no way of inferring the rotation directions of the lasers.</p>

<p>You have determined that the segment could be stolen in a heist if there is ever a non-empty open interval of time during which no laser is touching the segment. What is the probability of this happening?</p>

### 입력 

 <p>The first line of the input gives the number of test cases, <b>T</b>. <b>T</b> test cases follow. Each case begins with one line containing one integer <b>N</b>: the number of lasers. Then, <b>N</b> more lines follow. The i-th of these lines represents the ray that is the i-th laser, and contains four integers <b>X<sub>i</sub></b>, <b>Y<sub>i</sub></b>, <b>X<sub>i</sub>'</b>, and <b>Y<sub>i</sub>'</b>, representing the 2D coordinates of the endpoint of the ray, followed by the 2D coordinates of some other point on the ray.</p>

### 출력 

 <p>For each test case, output one line containing <code>Case #x: y</code>, where <code>x</code> is the test case number (starting from 1) and <code>y</code> is the probability described above. <code>y</code> will be considered correct if it is within an absolute or relative error of 10<sup>-6</sup> of the correct answer.</p>

