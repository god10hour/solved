# [Diamond II] Good Game - 25224 

[문제 링크](https://www.acmicpc.net/problem/25224) 

### 성능 요약

메모리: 22024 KB, 시간: 84 ms

### 분류

애드 혹, 다이나믹 프로그래밍

### 제출 일자

2026년 4월 27일 12:30:52

### 문제 설명

<p>Finn is playing a game of Twos and Threes. Twos and Threes is a one-player game played on a one-dimensional board. In the starting position, there are $N$ blocks arranged in a row, with each block labelled either $A$ or $B$. Blocks are numbered from $1$ to $N$ from left to right. Finn is allowed to make moves of the following form:</p>

<ul>
	<li>Select $2$ or $3$ consecutive blocks that share the same label. Remove them from the board. Connect any remaining blocks together. Re-index the blocks from left to right, starting with index $1$.</li>
</ul>

<p>Finn wins the game if all blocks are removed from the board. Your task is to help Finn determine a winning sequence of moves, or determine if the game cannot be won.</p>

### 입력 

 <p>The first line of input will contain the integer $N$.</p>

<p>The second line of input will contain the string $S$, which is the starting position of the game.</p>

<p>There are $N$ characters in $S$, and each of these characters in $S$ is either <code>A</code> or <code>B</code>.</p>

### 출력 

 <p>If there is a winning sequence of moves, output $K$, the number of moves in the winning sequence. On each of the next $K$ lines, print an index $i$, followed by one space, followed by a number $j$, denoting a move that will remove the blocks currently at indices $i$ to $i + j - 1$, inclusive.</p>

<p>If there is no winning sequence of moves, output <code>-1</code>.</p>

<p>If there are multiple winning sequences, then any winning sequence will be accepted. There is no need to minimize or maximize $K$.</p>

