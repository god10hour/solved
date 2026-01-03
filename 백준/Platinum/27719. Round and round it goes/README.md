# [Platinum V] Round and round it goes - 27719 

[문제 링크](https://www.acmicpc.net/problem/27719) 

### 성능 요약

메모리: 4528 KB, 시간: 0 ms

### 분류

애드 혹, 해 구성하기, 수학, 정수론, 런타임 전의 전처리, 소수 판정

### 제출 일자

2026년 1월 3일 23:45:14

### 문제 설명

<p>Last month, Dexter created the best infinite loop ever. However, his sister DeeDee used his computer to check her Facebook page and meanwhile she managed to erase two numbers from Dexter’s program.</p>

<p>Here is the damaged program in Java. (Check the input file for the same code in other languages.)</p>

<pre>public class R {  
 
  static boolean magic(int x) {  
    int foo = 0;  
    while (x > 1)  
      for (int y=2; ; ++y) {  
        if (y==x) return foo≤0;  
        if (magic(y) && x%y==0) { x/=y; ++foo; break; }  
      }  
    return true;  
  }  
 
  public static void main(String[] argv) {  
    int where = ??????;  
    int step = ??????;  
    int best = where;  
    while (step != 0) {  
      where += step;  
      if (where < best) { best=where; System.out.println("*"); }  
      if (!magic(where)) break;  
    }  
  }  
}
</pre>

<p>In both data sets your task is to replace the two “??????” strings by a pair of integers W and S. Note that these integers must be in a valid range for a signed 32-bit integer variable (e.g., int in Java). That is, your values must satisfy −2<sup>31</sup> ≤ W,S ≤ 2<sup>31</sup> − 1.</p>

<p>As the solution to the easy data set R1, submit any two integers W and S such that the program will run in an infinite loop if where is initialized to W and step to S.</p>

<p>As the solution to the hard data set R2, submit two integers W and S such that the program will run in an infinite loop if where is initialized to W and step to S. Additionally, out of all pairs (W,S) that satisfy the first condition, your values W and S must be such that the number of stars printed by the program is maximized. (Any such pair will be accepted.)</p>

### 입력 

 <p>For your convenience, the input file contains the program in multiple languages. All these programs are equivalent.</p>

<ul>
	<li><a href="https://upload.acmicpc.net/14be1c58-3734-4981-990f-08a35dd4e5b0/">r.java</a> <a href="https://upload.acmicpc.net/15dc067e-f807-4f18-b209-6aebd70c2978/">r.py</a> <a href="https://upload.acmicpc.net/0d5fec68-1e5a-4b45-ad9f-d690595e0e54/">r.cpp</a></li>
</ul>

### 출력 

 <p>Output a single line with two space-separated integers W and S.</p>

