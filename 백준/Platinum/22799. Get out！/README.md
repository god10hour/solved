# [Platinum II] Get out! - 22799 

[문제 링크](https://www.acmicpc.net/problem/22799) 

### 성능 요약

메모리: 2192 KB, 시간: 40 ms

### 분류

정렬, 기하학, 스위핑, 삼분 탐색, 각도 정렬

### 제출 일자

2026년 2월 9일 15:34:18

### 문제 설명

<p>Tom was captured by aliens and brought into a mysterious region.</p>

<p>Since the event was all of a sudden, he did not understand what happened to him until he found some circular objects in the region. They looked really ominous so he got much horrified. He seriously began to consider escaping there, evading the objects, as soon as possible.</p>

<p>The region can be considered on a two-dimensional field. Tom was told that he got caused so that he could do nothing but move straight just in one direction, before the aliens dissapeared. Needless to say, he will fail to escape if he crashes with the objects as his move is blocked, though he may touch them.</p>

<p>In addition to that, when he passes by the objects, he will be robbed of his energy at the closest point to each object. The amount of energy absorbed by the object i is represented by</p>

<p style="text-align: center;"><mjx-container class="MathJax" jax="CHTML" display="true" style="font-size: 99.9%; position: relative;"> <mjx-math display="true" class="MJX-TEX" aria-hidden="true" style="margin-left: 0px; margin-right: 0px;"><mjx-mrow><mjx-mo class="mjx-s3"><mjx-c class="mjx-c7B TEX-S3"></mjx-c></mjx-mo><mjx-mtable style="min-width: 12.214em;"><mjx-table><mjx-itable><mjx-mtr><mjx-mtd style="text-align: left; padding-right: 0.5em; padding-bottom: 0.1em;"><mjx-msub><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D443 TEX-I"></mjx-c></mjx-mi><mjx-script style="vertical-align: -0.15em; margin-left: -0.109em;"><mjx-mi class="mjx-i" size="s"><mjx-c class="mjx-c1D456 TEX-I"></mjx-c></mjx-mi></mjx-script></mjx-msub><mjx-mo class="mjx-n" space="3"><mjx-c class="mjx-cD7"></mjx-c></mjx-mo><mjx-mo class="mjx-n" space="3"><mjx-c class="mjx-c28"></mjx-c></mjx-mo><mjx-msub><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D45F TEX-I"></mjx-c></mjx-mi><mjx-script style="vertical-align: -0.15em;"><mjx-mi class="mjx-i" size="s"><mjx-c class="mjx-c1D456 TEX-I"></mjx-c></mjx-mi></mjx-script></mjx-msub><mjx-mo class="mjx-n" space="3"><mjx-c class="mjx-c2212"></mjx-c></mjx-mo><mjx-msub space="3"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D451 TEX-I"></mjx-c></mjx-mi><mjx-script style="vertical-align: -0.15em;"><mjx-mi class="mjx-i" size="s"><mjx-c class="mjx-c1D456 TEX-I"></mjx-c></mjx-mi></mjx-script></mjx-msub><mjx-mo class="mjx-n"><mjx-c class="mjx-c29"></mjx-c></mjx-mo><mjx-texatom texclass="ORD"><mjx-mo class="mjx-n"><mjx-c class="mjx-c2F"></mjx-c></mjx-mo></mjx-texatom><mjx-msub><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D45F TEX-I"></mjx-c></mjx-mi><mjx-script style="vertical-align: -0.15em;"><mjx-mi class="mjx-i" size="s"><mjx-c class="mjx-c1D456 TEX-I"></mjx-c></mjx-mi></mjx-script></mjx-msub><mjx-tstrut></mjx-tstrut></mjx-mtd><mjx-mtd style="text-align: left; padding-left: 0.5em; padding-bottom: 0.1em;"><mjx-mtext class="mjx-n"><mjx-c class="mjx-c69"></mjx-c><mjx-c class="mjx-c66"></mjx-c><mjx-c class="mjx-cA0"></mjx-c></mjx-mtext><mjx-msub><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D451 TEX-I"></mjx-c></mjx-mi><mjx-script style="vertical-align: -0.15em;"><mjx-mi class="mjx-i" size="s"><mjx-c class="mjx-c1D456 TEX-I"></mjx-c></mjx-mi></mjx-script></mjx-msub><mjx-mo class="mjx-n" space="4"><mjx-c class="mjx-c2264"></mjx-c></mjx-mo><mjx-msub space="4"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D45F TEX-I"></mjx-c></mjx-mi><mjx-script style="vertical-align: -0.15em;"><mjx-mi class="mjx-i" size="s"><mjx-c class="mjx-c1D456 TEX-I"></mjx-c></mjx-mi></mjx-script></mjx-msub><mjx-tstrut></mjx-tstrut></mjx-mtd></mjx-mtr><mjx-mtr><mjx-mtd style="text-align: left; padding-right: 0.5em; padding-top: 0.1em;"><mjx-mn class="mjx-n"><mjx-c class="mjx-c30"></mjx-c></mjx-mn><mjx-tstrut></mjx-tstrut></mjx-mtd><mjx-mtd style="text-align: left; padding-left: 0.5em; padding-top: 0.1em;"><mjx-mtext class="mjx-n"><mjx-c class="mjx-c6F"></mjx-c><mjx-c class="mjx-c74"></mjx-c><mjx-c class="mjx-c68"></mjx-c><mjx-c class="mjx-c65"></mjx-c><mjx-c class="mjx-c72"></mjx-c><mjx-c class="mjx-c77"></mjx-c><mjx-c class="mjx-c69"></mjx-c><mjx-c class="mjx-c73"></mjx-c><mjx-c class="mjx-c65"></mjx-c></mjx-mtext><mjx-tstrut></mjx-tstrut></mjx-mtd></mjx-mtr></mjx-itable></mjx-table></mjx-mtable><mjx-mo class="mjx-n" style="vertical-align: 0.25em;"></mjx-mo></mjx-mrow></mjx-math><mjx-assistive-mml unselectable="on" display="block"><math xmlns="http://www.w3.org/1998/Math/MathML" display="block"><mrow data-mjx-texclass="INNER"><mo data-mjx-texclass="OPEN">{</mo><mtable columnalign="left left" columnspacing="1em" rowspacing=".2em"><mtr><mtd><msub><mi>P</mi><mi>i</mi></msub><mo>×</mo><mo stretchy="false">(</mo><msub><mi>r</mi><mi>i</mi></msub><mo>−</mo><msub><mi>d</mi><mi>i</mi></msub><mo stretchy="false">)</mo><mrow data-mjx-texclass="ORD"><mo>/</mo></mrow><msub><mi>r</mi><mi>i</mi></msub></mtd><mtd><mtext>if </mtext><msub><mi>d</mi><mi>i</mi></msub><mo>≤</mo><msub><mi>r</mi><mi>i</mi></msub></mtd></mtr><mtr><mtd><mn>0</mn></mtd><mtd><mtext>otherwise</mtext></mtd></mtr></mtable><mo data-mjx-texclass="CLOSE" fence="true" stretchy="true" symmetric="true"></mo></mrow></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$$\begin{cases} P_i \times (r_i - d_i) / r_i & \text{if }d_i \le r_i \\ 0 & \text{otherwise} \end{cases}$$</span> </mjx-container></p>

<p>where P<sub>i</sub> is a positive number called the power of the object i, r<sub>i</sub> is the radius of the object i, and d<sub>i</sub> is the distance between Tom and the circumference of the object when he gets to the closest point.</p>

<p style="text-align: center;"><img alt="" src="https://upload.acmicpc.net/81e601f4-95f4-44dc-8021-e43ed00d19f1/-/preview/" style="width: 139px; height: 175px;"></p>

<p>Tom gets unable to move anymore if he loses all his energy.</p>

<p>Your task is to write a program that shows Tom’s remaining energy after his escape when he moves in such a direction that he remains his energy as much as possible.</p>

<p style="text-align: center;"><img alt="" src="https://upload.acmicpc.net/44478051-a831-4a8b-9cc3-446a88b10144/-/preview/" style="width: 408px; height: 288px;"></p>

### 입력 

 <p>The input consists of a series of data sets.</p>

<p>The first line of a data set contains an integer N (1 ≤ N ≤ 50) that indicates the number of the circular objects. The (i + 1)-st line contains four real numbers x<sub>i</sub> (−1000 ≤ x<sub>i</sub> ≤ 1000), y<sub>i</sub> (−1000 ≤ y<sub>i</sub> ≤ 1000), r<sub>i</sub> (0.1 ≤ r<sub>i</sub> ≤ 500), and P<sub>i</sub> (0.1 ≤ P<sub>i</sub> ≤ 500), which denote the x and y coordinates of the center, the radius, and the power of the object i respectively. The (N + 2)-nd line contains three real numbers x (−1000 ≤ x ≤ 1000), y (−1000 ≤ y ≤ 1000), and E (0.1 ≤ E ≤ 100), which denote the x and y coordinates of Tom’s initial position, and Tom’s initial energy respectively.</p>

<p>There is always difference of at least 10<sup>−5</sup> degrees between directions Tom can escape touching objects on his left-hand, and that Tom can escape touching objects on his right-hand.</p>

<p>An input line containing a single integer 0 indicates the end of input.</p>

### 출력 

 <p>For each data set, print a single line.</p>

<p>If Tom can escape from the region, print Tom’s remaining energy with three digits after the decimal point. The value should not contain an error greater than 0.001.</p>

<p>Otherwise, print “No way to escape”.</p>

<p>You may assume Tom remains his energy of at least 10<sup>−5</sup> as long as he moves in such a direction that he can escape. In other words, there is not such a path that Tom can escape remaining his energy less than 10<sup>−5</sup>.</p>

<p>Note that the output line may contain 0.000, though. No extra spaces or blank lines should be printed.</p>

