# [Diamond IV] Do It - 22678 

[문제 링크](https://www.acmicpc.net/problem/22678) 

### 성능 요약

메모리: 2376 KB, 시간: 120 ms

### 분류

수학, 미적분학

### 제출 일자

2026년 4월 17일 18:05:13

### 문제 설명

<p>There is sometimes difficulty giving nice backgrounds to contest problems. So let this problem kept this simple - write a program that calculates the value of the following formula where the parameters <i>N</i>, <i>R</i>, <i>A<sub>i</sub></i>, <i>ω<sub>i</sub></i>, and <i>φ<sub>i</sub></i> are all given:</p>

<p><mjx-container class="MathJax" jax="CHTML" display="true" style="font-size: 99.9%; position: relative;"> <mjx-math display="true" class="MJX-TEX" aria-hidden="true" style="margin-left: 0px; margin-right: 0px;"><mjx-msubsup><mjx-mo class="mjx-lop"><mjx-c class="mjx-c222B TEX-S2"></mjx-c></mjx-mo><mjx-script style="vertical-align: -0.896em; margin-left: -0.388em;"><mjx-texatom size="s" texclass="ORD" style="margin-left: 0.647em;"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D445 TEX-I"></mjx-c></mjx-mi></mjx-texatom><mjx-spacer style="margin-top: 1.499em;"></mjx-spacer><mjx-texatom size="s" texclass="ORD"><mjx-mn class="mjx-n"><mjx-c class="mjx-c30"></mjx-c></mjx-mn></mjx-texatom></mjx-script></mjx-msubsup><mjx-texatom space="2" texclass="ORD"><mjx-mrow><mjx-mo class="mjx-s4"><mjx-c class="mjx-c5B TEX-S4"></mjx-c></mjx-mo><mjx-munderover><mjx-over style="padding-bottom: 0.2em; padding-left: 0.325em;"><mjx-texatom size="s" texclass="ORD"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D441 TEX-I"></mjx-c></mjx-mi></mjx-texatom></mjx-over><mjx-box><mjx-munder><mjx-row><mjx-base><mjx-mo class="mjx-lop"><mjx-c class="mjx-c220F TEX-S2"></mjx-c></mjx-mo></mjx-base></mjx-row><mjx-row><mjx-under style="padding-top: 0.167em; padding-left: 0.065em;"><mjx-texatom size="s" texclass="ORD"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D456 TEX-I"></mjx-c></mjx-mi><mjx-mo class="mjx-n"><mjx-c class="mjx-c3D"></mjx-c></mjx-mo><mjx-mn class="mjx-n"><mjx-c class="mjx-c31"></mjx-c></mjx-mn></mjx-texatom></mjx-under></mjx-row></mjx-munder></mjx-box></mjx-munderover><mjx-texatom space="2" texclass="ORD"><mjx-msub><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D434 TEX-I"></mjx-c></mjx-mi><mjx-script style="vertical-align: -0.15em;"><mjx-mi class="mjx-i" size="s"><mjx-c class="mjx-c1D456 TEX-I"></mjx-c></mjx-mi></mjx-script></mjx-msub><mjx-mi class="mjx-n" space="2"><mjx-c class="mjx-c73"></mjx-c><mjx-c class="mjx-c69"></mjx-c><mjx-c class="mjx-c6E"></mjx-c></mjx-mi><mjx-mo class="mjx-n"><mjx-c class="mjx-c2061"></mjx-c></mjx-mo><mjx-texatom space="2" texclass="ORD"><mjx-mrow><mjx-mo class="mjx-lop"><mjx-c class="mjx-c28 TEX-S2"></mjx-c></mjx-mo><mjx-msub><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D714 TEX-I"></mjx-c></mjx-mi><mjx-script style="vertical-align: -0.15em;"><mjx-mi class="mjx-i" size="s"><mjx-c class="mjx-c1D456 TEX-I"></mjx-c></mjx-mi></mjx-script></mjx-msub><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D461 TEX-I"></mjx-c></mjx-mi><mjx-mo class="mjx-n" space="3"><mjx-c class="mjx-c2B"></mjx-c></mjx-mo><mjx-msub space="3"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D711 TEX-I"></mjx-c></mjx-mi><mjx-script style="vertical-align: -0.15em;"><mjx-mi class="mjx-i" size="s"><mjx-c class="mjx-c1D456 TEX-I"></mjx-c></mjx-mi></mjx-script></mjx-msub><mjx-mo class="mjx-n" space="3"><mjx-c class="mjx-c22C5"></mjx-c></mjx-mo><mjx-mfrac space="3"><mjx-frac type="d"><mjx-num><mjx-nstrut type="d"></mjx-nstrut><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D70B TEX-I"></mjx-c></mjx-mi></mjx-num><mjx-dbox><mjx-dtable><mjx-line type="d"></mjx-line><mjx-row><mjx-den><mjx-dstrut type="d"></mjx-dstrut><mjx-mn class="mjx-n"><mjx-c class="mjx-c31"></mjx-c><mjx-c class="mjx-c38"></mjx-c><mjx-c class="mjx-c30"></mjx-c></mjx-mn></mjx-den></mjx-row></mjx-dtable></mjx-dbox></mjx-frac></mjx-mfrac><mjx-mo class="mjx-lop"><mjx-c class="mjx-c29 TEX-S2"></mjx-c></mjx-mo></mjx-mrow></mjx-texatom></mjx-texatom><mjx-mo class="mjx-s4"><mjx-c class="mjx-c5D TEX-S4"></mjx-c></mjx-mo></mjx-mrow><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D451 TEX-I"></mjx-c></mjx-mi><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D461 TEX-I"></mjx-c></mjx-mi></mjx-texatom></mjx-math><mjx-assistive-mml unselectable="on" display="block"><math xmlns="http://www.w3.org/1998/Math/MathML" display="block"><msubsup><mo data-mjx-texclass="OP">∫</mo><mrow data-mjx-texclass="ORD"><mn>0</mn></mrow><mrow data-mjx-texclass="ORD"><mi>R</mi></mrow></msubsup><mrow data-mjx-texclass="ORD"><mrow data-mjx-texclass="INNER"><mo data-mjx-texclass="OPEN">[</mo><munderover><mo data-mjx-texclass="OP">∏</mo><mrow data-mjx-texclass="ORD"><mi>i</mi><mo>=</mo><mn>1</mn></mrow><mrow data-mjx-texclass="ORD"><mi>N</mi></mrow></munderover><mrow data-mjx-texclass="ORD"><msub><mi>A</mi><mi>i</mi></msub><mi>sin</mi><mo data-mjx-texclass="NONE">⁡</mo><mrow data-mjx-texclass="ORD"><mrow data-mjx-texclass="INNER"><mo data-mjx-texclass="OPEN">(</mo><msub><mi>ω</mi><mi>i</mi></msub><mi>t</mi><mo>+</mo><msub><mi>φ</mi><mi>i</mi></msub><mo>⋅</mo><mfrac><mi>π</mi><mn>180</mn></mfrac><mo data-mjx-texclass="CLOSE">)</mo></mrow></mrow></mrow><mo data-mjx-texclass="CLOSE">]</mo></mrow><mi>d</mi><mi>t</mi></mrow></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$$ \int_{0}^{R}{\left[\prod_{i=1}^{N}{A_i \sin{\left( ω_it + φ_i \cdot \frac{\pi}{180} \right)}}\right]dt} $$</span> </mjx-container></p>

### 입력 

 <p>The input consists of a series of datasets each of which has the following format:</p>

<pre><i>N R</i>
<i>A</i><sub>1</sub> <i>ω</i><sub>1</sub> <i>φ</i><sub>1</sub>
<i>A</i><sub>2</sub> <i>ω</i><sub>2</sub> <i>φ</i><sub>2</sub>
...
<i>A</i><sub><i>N</i></sub> <i>ω</i><sub><i>N</i></sub> <i>φ</i><sub><i>N</i></sub>
</pre>

<p>The numbers in the input are all integers and satisfy the following conditions: 1 ≤ <i>N</i> ≤ 16, 1 ≤ <i>R</i> ≤ 10<sup>4</sup>, 1 ≤ <i>A<sub>i</sub></i> ≤ 10, 0 ≤ <i>ω<sub>i</sub></i> ≤ 100 and 0 ≤ <i>φ<sub>i</sub></i> ≤ 360.</p>

<p>The end of input is indicated by <i>N</i> = <i>R</i> = 0. This is not part of any dataset and hence should not be processed.</p>

### 출력 

 <p>For each dataset, print the result of the integration in a line. The result may be printed with an arbitrary number of fractional digits, but should have a relative or absolute error not greater than 10<sup>-8</sup>.</p>

