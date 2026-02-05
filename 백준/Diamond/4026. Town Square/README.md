# [Diamond V] Town Square - 4026 

[문제 링크](https://www.acmicpc.net/problem/4026) 

### 성능 요약

메모리: 2052 KB, 시간: 684 ms

### 분류

기하학

### 제출 일자

2026년 2월 5일 23:53:35

### 문제 설명

<p>Felix J. Humble, a nerdy but rich resident of a small Midwest town, has erected 4 statues in his honor in a public park (which he happens to own). Felix is very proud of these statues, but is now worried about vandals, small children with bubble gum, and the occasional dog with a urinary tract infection. To solve this problem, he has decided to build a fence around the statues (Felix owns the local fencing company as well). For various aesthetic reasons he would like the following conditions met:</p>

<ol>
	<li>The enclosed area must be a square.</li>
	<li>The distance between each statue and its nearest fence side should be 5 feet.</li>
	<li>No two statues should have the same nearest fence side.</li>
</ol>

<p>After working for a grand total of 12 seconds, Felix has realized that he has no idea of the length of fence needed, or even if the above conditions can be met. Since he is planning similar tributes in other parks he owns, he would like someone to write a program to solve this problem (which Felix will later take credit for, of course).</p>

### 입력 

 <p>The first line of the input file will contain an integer n indicating the number of test cases. The test cases will follow, one per line, each consisting of eight integer values giving the x and y coordinates for the first, second, third and then fourth statue. All values will be in units of feet, and will lie between -100 and 100. No two statues will be at the same location.</p>

### 출력 

 <p>For each test case, output the case number followed by one of two answers: 1) If there is a solution, output the side length of the enclosing square. If there are multiple solutions, output the side length of the solution of maximum size; 2) If it is not possible to build a square fence which meets Felix’s conditions, output no solution. All numerical output should be rounded to the nearest hundredth of a foot. Follow the format in the examples below.</p>

