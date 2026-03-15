# [Platinum I] Functional Programming Counts - 5112 

[문제 링크](https://www.acmicpc.net/problem/5112) 

### 성능 요약

메모리: 2052 KB, 시간: 564 ms

### 분류

구현, 파싱, 정렬, 문자열

### 제출 일자

2026년 3월 15일 23:25:32

### 문제 설명

<p>The formal methods team at your place of work has decided to experiment with very small functional language. They have, of course, specified it. The bad news is that you have to implement it. The good news is that you can do so in a programming language of your choice and a formal proof of the correctness of your implementation is not required. In the grand tradition of Lisp your implementation will take the form of an interpreter which accepts expressions, assignments and function definitions from the console. Function definitions are remembered and the functions may be used in subsequent expressions. Expressions are immediately evaluated, and the result is displayed at the console.</p>

### 입력 

 <p>The input consists of a series of input lines, each holding an input action. No line has more than 100 characters. Actions can be of the following kinds:</p>

<ol>
	<li><expression>
	<ul>
		<li>The expression should be evaluated (to give an integer result) and the result should be displayed.</li>
	</ul>
	</li>
	<li>set <identifier> = <expression>
	<ul>
		<li>An assignment statement: The identifier represents a variable. If it has not been seen before, create a new variable and give it the value of the expression, otherwise just update an existing variable.</li>
	</ul>
	</li>
	<li>def <identifier> ( <parameter> ) = <expression>
	<ul>
		<li>A function definition line, that wholly or partially defines a function with name <identifier> and one integer parameter. <parameter> can be a <number> or an <identifier>. If it is a <number> then it defines the function when the parameter takes that value. The order of definition lines is important. All definitions for a function are kept, and function calls check them in order of input for the first parameter match. (This makes it impossible to change the definition of a function.)</li>
	</ul>
	</li>
	<li>profile
	<ul>
		<li>The software should report the number of function calls made on each definition line for each defined function, since the last profile request (or the start of the program). See sample output.</li>
	</ul>
	</li>
	<li>exit
	<ul>
		<li>The end of input.</li>
	</ul>
	</li>
</ol>

<p>Input should be processed, one line at a time, performing the requested action immediately, until the line with ‘exit’ is reached. The only data type processed by the language is integer. Values lie in the range -1,000,000 to 1,000,000 at all times. (The range is inclusive). The syntax for expressions is as follows. Operator precedence applies in the normal manner – evaluate factors, then terms and finally expressions.</p>

<ul>
	<li><expression> is a sum(+) or difference(-) of <term>s to be evaluated from left to right (eg: a + b – 3 + 4 – c)</li>
	<li><term> is a product ‘*’, quotient ‘/’ or remainder ‘%’ of <factor>s, to be evaluated left to right. Remainder should never be used with negative numbers. Division is integer division. (eg: 3 * 4 / 5 % x).</li>
	<li><factor> can be a <number>; an <identifier> being a variable, or the parameter of the current function; a function call of the form <identifier>(<expression>); or an expression in parenthesis (<expression>).</li>
	<li><number> is a string of digits, being a decimal value in the range 0 to 1,000,000 (inclusive)</li>
	<li><identifier> is a string of upper and lower case letters – case is significant, eg: ‘A’ and ‘a’ are different variables. The following are reserved words and should not be used as identifiers: ‘def’, ‘set’, ‘profile’, ‘exit’.</li>
</ul>

<p>White space should be ignored on all input lines, except in so far as it separates words. You can assume that all input is syntactically correct, that all function calls return (terminate), and that all expressions produce results in the permitted range. The total number of calls profiled on any one function line will never exceed 1,000,000. </p>

### 출력 

 <p>Expression results should be reported on a line of their own, prefixed by ‘>> ‘ (two greater than signs and a single space).</p>

<p>Profile results should be reported with one line per function of the form ‘<identifier> calls: n1 n2 n3 … => nt ’ where ni is the number of calls for definition line i in order input, and nt is the total number of calls to the function (single spaced).</p>

