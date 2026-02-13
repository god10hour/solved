# [Gold IV] Rebel Against The Empire (Small) - 14351 

[문제 링크](https://www.acmicpc.net/problem/14351) 

### 성능 요약

메모리: 17700 KB, 시간: 4084 ms

### 분류

자료 구조, 그래프 이론, 그래프 탐색, 정렬, 기하학, 최단 경로, 데이크스트라, 분리 집합, 피타고라스 정리

### 제출 일자

2026년 2월 13일 10:08:31

### 문제 설명

<p>You are a rebel against the evil Galactic Empire, and you are on the run!</p>

<p>You have sabotaged the Empire's Factory of Evil, and imperial security forces will be after you soon! The factory is located on asteroid 0 in a system of N numbered asteroids. Your getaway ship, the Century Quail, is located on asteroid 1, and if you can get there, you will be able to fly away safely.</p>

<p>Each asteroid is a single point in space with a velocity, and you move through space along with whichever asteroid you are currently on. Your Asteroid Jumper will allow you to instantaneously jump between any two asteroids in the system. Long jumps are scarier than short ones (and the vacuum of space is terrifying), so you want to minimize the maximum distance you need to jump. However, starting now, if you ever spend more than a continuous S seconds without jumping, the imperial security forces will catch you. That is, the interval from now until your first jump, and each interval between subsequent jumps, must be less than or equal to S. You may jump at any instant; it does not have to be after an integer number of seconds have elapsed. You escape the instant you jump to asteroid 1.</p>

<p>The i-th asteroid starts at position (x<sub>i</sub>, y<sub>i</sub>, z<sub>i</sub>) in space, and it will move a total distance of (V<sub>xi</sub>, V<sub>yi</sub>, V<sub>zi</sub>) each second. This movement is continuous throughout time; it does not update discretely each second. (It is also possible for an asteroid to be stationary.) Nothing happens if asteroids occupy the same point in space at the same time. You can only travel between two asteroids by jumping, even if they happen to occupy the same point at the instant of your jump.</p>

<p>In the escape plan that minimizes the maximum jump distance, what is that maximum jump distance?</p>

<ul>
</ul>

### 입력 

 <p>The first line of the input gives the number of test cases, T. T test cases follow. The first line of each test case contains two integers: N (the number of asteroids) and S (the limit on how long you can go without jumping). Next, there are N lines describing the asteroids. The i-th of these lines (counting starting from 0) contains six integers: the initial (x<sub>i</sub>, y<sub>i</sub>, z<sub>i</sub>) position of the i-th asteroid in space, and the distance (V<sub>xi</sub>, V<sub>yi</sub>, V<sub>zi</sub>) it moves in a single second.</p>

<h3>Limits</h3>

<ul>
	<li>1 ≤ T ≤ 20.</li>
	<li>2 ≤ N ≤ 1000.</li>
	<li>1 ≤ S ≤ 100.</li>
	<li>-500 ≤ x<sub>i</sub> ≤ 500.</li>
	<li>-500 ≤ y<sub>i</sub> ≤ 500.</li>
	<li>-500 ≤ z<sub>i</sub> ≤ 500.</li>
	<li>V<sub>xi</sub> = 0.</li>
	<li>V<sub>yi</sub> = 0.</li>
	<li>V<sub>zi</sub> = 0.</li>
</ul>

### 출력 

 <p>For each test case, output one line containing <code>Case #x: y</code>, where <code>x</code> is the test case number (starting from 1) and <code>y</code> is a floating-point number: the distance of the longest jump you will have to make in order to get away. <code>y</code> will be considered correct if it is within an absolute or relative error of 10<sup>-4</sup> of the correct answer. </p>

