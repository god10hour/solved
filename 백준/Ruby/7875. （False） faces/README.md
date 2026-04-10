# [Ruby II] (False) faces - 7875 

[문제 링크](https://www.acmicpc.net/problem/7875) 

### 성능 요약

메모리: 2164 KB, 시간: 2840 ms

### 분류

수학, 선형대수학

### 제출 일자

2026년 4월 11일 03:33:09

### 문제 설명

<p>The Company is testing its brand new face recognition solution. The application is supposed to recognize people given their profiles. It is fed with a number of test cases to check if everything is working fine. Each test consists of 2n photos of n persons; there is a left profile and a right profile of each person in a single test case. The program matches left profiles with right profiles, but it is still far from perfect, so sometimes several right profiles are assigned to a single left profile (and vice versa). A consistent reconstruction is an assignment of different right profiles to all left profiles, such that all the pairs matched were proposed by the program.</p>

<p style="text-align: center;"><img alt="" src="https://upload.acmicpc.net/9a972738-a2f1-46ab-a10c-46854e546546/-/preview/" style="width: 472px; height: 116px;"></p>

<p style="text-align: center;">The program output (on the left) and four possible consistent reconstructions.</p>

<p>In order to test the program, it is necessary to verify every possible consistent reconstruction. The verification has to be done by humans and the Company has a team of four experts who devoted their lives to face recognition. They are willing to do the job under one condition: their shares of work have to be equal, i.e., the number of consistent reconstructions has to be divisible by four. Your task is to check if it is so.</p>

### 입력 

 <p>The input contains several test cases. The first line of the input contains a positive integer Z ≤ 100, denoting the number of test cases. Then Z test cases follow.</p>

<p>The first line contains the number n of persons in a test (1 ≤ n ≤ 300). Then n lines follows, each containing n characters, each of them being 0 or 1. The j-th character in the i-th line is 1 if and only if the program matches the i-th left profile with the j-th right profile.</p>

### 출력 

 <p>The output should consist of one line containing <code>YES</code> if the number of reconstructions consistent with the program assignment is divisible by 4 and <code>NO</code> otherwise.</p>

