# [Platinum I] Bad Hair Day와 기댓값 - 18194 

[문제 링크](https://www.acmicpc.net/problem/18194) 

### 성능 요약

메모리: 2808 KB, 시간: 64 ms

### 분류

수학, 정수론, 조합론, 확률론, 모듈로 곱셈 역원, 기댓값의 선형성

### 제출 일자

2026년 2월 24일 03:01:03

### 문제 설명

<p>농부 존에게는 <em>N</em>마리의 소가 있다. 소들의 키는 다양하며, 두 마리의 소의 키가 서로 같을 수 있다.</p>

<p>자신의 헤어스타일이 마음에 들지 않았던 소들은 일렬로 서서 서로의 헤어스타일을 확인해 주려고 한다.</p>

<p>각 소들은 자신의 오른쪽을 바라보면서 자신보다 키가 같거나 큰 소가 등장하기 전까지 나온 모든 소들의 헤어스타일을 확인할 수 있다. 더 정확하게는, 왼쪽에서 <em>i</em>번째에 서 있는 소의 키를 <em>H'</em><sub><em>i</em></sub>라 하면, <em>i</em>번째 소는 다음 조건을 만족할 때 (또한 그러할 때에만) <em>j</em>번째 소를 볼 수 있다.</p>

<ul>
	<li><em>i</em> < <em>j</em>고, <em>H'</em><sub><em>i</em></sub> > <em>H'</em><sub><em>j</em></sub>다.</li>
	<li><em>i</em> < <em>k</em> < <em>j</em>고, <em>H'</em><sub><em>i</em></sub> ≤ <em>H'</em><sub><em>k</em></sub>를 만족하는 <em>k</em>가 존재하지 않는다.</li>
</ul>

<p>소들이 <em>N</em>마리 있으므로, 그들이 일렬로 설 수 있는 방법은 총 <em>N</em>!가지다. 농부 존은 헤어스타일을 확인할 수 있는 소들 쌍의 수의 기댓값이 궁금해졌다. 농부 존을 도와, 이 기댓값을 출력하는 프로그램을 작성하시오.</p>

### 입력 

 <p>첫 번째 줄에 소의 수를 나타내는 자연수 <em>N</em>이 주어진다.</p>

<p>두번째 줄에 <em>N</em>마리의 소의 키를 나타내는 <em>N</em>개의 자연수 <em>H</em><sub>1</sub>, ···, <em>H<sub>N</sub></em>가 사이에 공백을 두고 주어진다.</p>

### 출력 

 <p>어떤 서로소이고 음이 아닌 두 정수 <mjx-container class="MathJax" jax="CHTML" style="font-size: 99.9%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D443 TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>P</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$P$</span></mjx-container>, <mjx-container class="MathJax" jax="CHTML" style="font-size: 99.9%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D444 TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>Q</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$Q$</span></mjx-container>가 존재하여, 헤어스타일을 확인할 수 있는 소들 쌍의 수의 기댓값이 <mjx-container class="MathJax" jax="CHTML" style="font-size: 99.9%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mstyle><mjx-mfrac><mjx-frac type="d"><mjx-num><mjx-nstrut type="d"></mjx-nstrut><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D443 TEX-I"></mjx-c></mjx-mi></mjx-num><mjx-dbox><mjx-dtable><mjx-line type="d"></mjx-line><mjx-row><mjx-den><mjx-dstrut type="d"></mjx-dstrut><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D444 TEX-I"></mjx-c></mjx-mi></mjx-den></mjx-row></mjx-dtable></mjx-dbox></mjx-frac></mjx-mfrac></mjx-mstyle></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mstyle displaystyle="true" scriptlevel="0"><mfrac><mi>P</mi><mi>Q</mi></mfrac></mstyle></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$\displaystyle \frac{P}{Q}$</span></mjx-container>와 같다고 하자. 이때, <mjx-container class="MathJax" jax="CHTML" style="font-size: 99.9%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D443 TEX-I"></mjx-c></mjx-mi><mjx-mo class="mjx-n" space="4"><mjx-c class="mjx-c2261"></mjx-c></mjx-mo><mjx-mi class="mjx-i" space="4"><mjx-c class="mjx-c1D444 TEX-I"></mjx-c></mjx-mi><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D44B TEX-I"></mjx-c></mjx-mi><mjx-mspace style="width: 0.444em;"></mjx-mspace><mjx-mo class="mjx-n"><mjx-c class="mjx-c28"></mjx-c></mjx-mo><mjx-mi class="mjx-n"><mjx-c class="mjx-c6D"></mjx-c><mjx-c class="mjx-c6F"></mjx-c><mjx-c class="mjx-c64"></mjx-c></mjx-mi><mjx-mspace style="width: 0.333em;"></mjx-mspace><mjx-msup space="2"><mjx-mn class="mjx-n"><mjx-c class="mjx-c31"></mjx-c><mjx-c class="mjx-c30"></mjx-c></mjx-mn><mjx-script style="vertical-align: 0.393em;"><mjx-texatom size="s" texclass="ORD"><mjx-mn class="mjx-n"><mjx-c class="mjx-c39"></mjx-c></mjx-mn></mjx-texatom></mjx-script></mjx-msup><mjx-mo class="mjx-n" space="3"><mjx-c class="mjx-c2B"></mjx-c></mjx-mo><mjx-mn class="mjx-n" space="3"><mjx-c class="mjx-c37"></mjx-c></mjx-mn><mjx-mo class="mjx-n"><mjx-c class="mjx-c29"></mjx-c></mjx-mo></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>P</mi><mo>≡</mo><mi>Q</mi><mi>X</mi><mspace width="0.444em"></mspace><mo stretchy="false">(</mo><mi>mod</mi><mspace width="0.333em"></mspace><msup><mn>10</mn><mrow data-mjx-texclass="ORD"><mn>9</mn></mrow></msup><mo>+</mo><mn>7</mn><mo stretchy="false">)</mo></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$P \equiv QX \pmod{10^{9} + 7}$</span></mjx-container>를 만족하는 0 이상 (10<sup>9</sup> + 7) 미만의 정수 <mjx-container class="MathJax" jax="CHTML" style="font-size: 99.9%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D44B TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>X</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$X$</span></mjx-container>를 구하여 첫 번째 줄에 출력한다.</p>

<p>조건을 만족하는 <mjx-container class="MathJax" jax="CHTML" style="font-size: 99.9%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D443 TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>P</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$P$</span></mjx-container>, <mjx-container class="MathJax" jax="CHTML" style="font-size: 99.9%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D444 TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>Q</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$Q$</span></mjx-container>, <mjx-container class="MathJax" jax="CHTML" style="font-size: 99.9%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D44B TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>X</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$X$</span></mjx-container>는 반드시 존재한다. 또한 <mjx-container class="MathJax" jax="CHTML" style="font-size: 99.9%; position: relative;"><mjx-math class="MJX-TEX" aria-hidden="true"><mjx-mi class="mjx-i"><mjx-c class="mjx-c1D44B TEX-I"></mjx-c></mjx-mi></mjx-math><mjx-assistive-mml unselectable="on" display="inline"><math xmlns="http://www.w3.org/1998/Math/MathML"><mi>X</mi></math></mjx-assistive-mml><span aria-hidden="true" class="no-mathjax mjx-copytext">$X$</span></mjx-container>는 유일하게 존재함이 보장된다.</p>

