# [Gold IV] A Puzzling Problem - 4694 

[문제 링크](https://www.acmicpc.net/problem/4694) 

### 성능 요약

메모리: 2040 KB, 시간: 0 ms

### 분류

백트래킹, 브루트포스 알고리즘, 구현

### 제출 일자

2026년 2월 13일 09:28:27

### 문제 설명

<p>The goal of this problem is to write a program which will take from 1 to 5 puzzle pieces such as those shown below and arrange them, if possible, to form a square. An example set of pieces is shown here.</p>

<p><img alt="" src="https://www.acmicpc.net/upload/images2/puzzle1.gif" style="height:179px; width:491px"></p>

<p>The pieces cannot be rotated or flipped from their original orientation in an attempt to form a square from the set. All of the pieces must be used to form the square. There may be more than one possible solution for a set of pieces, and not every arrangement will work even with a set for which a solution can be found. Examples using the above set of pieces are shown here.</p>

<p><img alt="" src="https://www.acmicpc.net/upload/images2/puzzle2.gif" style="height:179px; width:557px"></p>

### 입력 

 <p>The input file for this program contains several puzzles (i.e. sets of puzzle pieces) to be solved. The first line of the file is the number of pieces in the first puzzle. Each piece is then specified by listing a single line with two integers, the number of rows and columns in the piece, followed by one or more lines which specify the shape of the piece. The shape specification consists of '0' and '1' characters, with the '1' characters indicating the solid shape of the puzzle (the '0' characters are merely placeholders). For example, piece 'A' above would be specified as follows:</p>

<pre>2 3
111
101</pre>

<p>The pieces should be numbered by the order they are encountered in the puzzle. That is, the first piece in a puzzle is piece #1, the next is piece #2, etc. All pieces may be assumed to be valid and no larger than 4 rows by 4 columns.</p>

<p>The line following the final line of the last piece contains the number of pieces in the next puzzle, again followed by the puzzle pieces and so on. The end of the input file is indicated by a zero in place of the number of puzzle pieces.</p>

### 출력 

 <p>Your program should report a solution, if one is possible, in the format shown by the examples below. A 4-row by 4-column square should be created, with each piece occupying its location in the solution. The solid portions of piece #1 should be replaced with '1' characters, of piece #2 with '2' characters, etc. The solutions for each puzzle should be separated by a single blank line. For puzzles which have no possible solution simply report "No solution possible".</p>

