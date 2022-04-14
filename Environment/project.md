- 搬题人：- A：hehezhou
- B, C：p_b_p_b

- 组题人：FSYo, p_b_p_b
- 验题人：chenkuowen01, srf
- 题解：chenkuowen01, hehezhou, p_b_p_b

### 最小生成树

题目来源：
- 京都大学プログラミングProgrammingコンテストContest 2020
- Petrozavodsk Summer 2021 Day 1: Kyoto U Contest (KUPC 2020), Problem F
QOJ 链接：[https://qoj.ac/contest/691/problem/1809](https://qoj.ac/contest/691/problem/1809)
官方题解：[https://qoj.ac/download.php?type=attachments&id=691&r=1](https://qoj.ac/download.php?type=attachments&id=691&r=1)

#### 解法一

  将图建出来然后使用任意最小生成树算法求解。
  时间复杂度 $\Theta((H\times W)^{1+\epsilon})$，可以通过前6个测试点。

#### 解法二

**lemma 1**: 一定存在一组最小生成树使得对于每个点 $P_{i,j}(i\gt 1\land j\gt 1)$ 存在和 $(i-1,j)$ 或 $(i,j-1)$ 的连边。
**proof**:
假设该结论不成立，那么对于所有最小生成树使得每个点 $P_{i,j}(i\gt 1\land j\gt 1)$ 都不存在这样的连边。
取其中一个点 $P_{i,j}$。
若其度数为 $1$，不妨令该边为 $(P_{i,j},P_{i+1,j})$，则删去该边后 $P_{i+1,j}$ 与 $P_{i-1,j}$ 在同一个连通块内，将该边替换为 $(P_{i-1,j},P_{i,j})$ 不劣。
若其度数为 $2$，考虑删去这两条边的连通块情况。
- 若 $P_{i+1,j},P_{i-1,j}$ 或 $P_{i,j-1},P_{i,j+1}$ 在同一连通块内，不妨令这组为 $P_{i+1,j},P_{i-1,j}$，那么替换对应边为 $(P_{i-1,j},P_{i,j})$ 不劣。
- 否则，$P_{i+1,j}$与$P_{i,j-1}$在同一连通块内且$P_{i,j+1}$与$P_{i-1,j}$在同一连通块内，将这两条边一并替换为$(P_{i-1,j},P_{i,j}),(P_{i,j-1},P_{i,j})$。
按上述方法调整即可找出矛盾。故假设不成立。
证毕。
**lemma 2**: 一定存在一组最小生成树 $T$ 使得对于任意 $1\le x\le H,1\le y\le W$，$T$ 关于点集 $\lbrace P_{i,j} | 1\le i\le x,1\le j\le y\rbrace$ 的导出子图为连通图。
**proof**:
假设该结论不成立，那么对于所有最小生成树都存在对应的 $x,y$ 不符合该性质。
我们取一组符合 **lemma 1** 的最小生成树和 $(x,y)$ 字典序最小的不符合条件的矩阵。
- 该导出子图不连通，所以一定存在 $i$ 使得 $P_{1,i},P_{1,i+1}$ 不连通，或 $P_{i,1},P_{i+1,1}$ 不连通，不妨只考虑后者。
- 考虑 $P_{i,1}$ 到 $P_{i+1,1}$ 在原图 $T$ 中的路径一定存在某个 $j$ 使得存在边 $(P_{i,j},P_{i+1,j})$，那么将该边替换为 $(P_{i,1},P_{i+1,1})$ 不会破坏性质且不劣。
- 重复该方法可得到一个对于任意 $1\le x'\le x,1\le y'\le y$ 符合点集 $\lbrace P_{i,j} | 1\le i\le x',1\le j\le y'\rbrace$ 的导出子图为连通图的最小生成树。
重复该过程可发现矛盾，故假设不成立。
证毕。
根据 **lemma 2**，我们可以按 $i,j$ 从小到大枚举加入维护的生成树，因此答案的权值和为：
$$\displaystyle\sum_{i=1}^{H-1} (A_i+B_1)+ \displaystyle\sum_{j=1}^{W-1} (C_1+D_i)+\displaystyle\sum_{i=2}^{H-1} \displaystyle\sum_{j=2}^{W-1} \min(A_{i-1}+B_j,C_i+D_{j-1})$$
其中：
$$\min(A_{i-1}+B_j,C_i+D_{j-1})=A_{i-1}+B_j+\lbrack C_i-A_{i-1}+D_j-B_{j-1}< 0 \rbrack (C_i-A_{i-1}+D_j-B_{j-1})$$
将 $i,j$ 分离后可用二分+前缀和优化，时间复杂度 $\Theta((H+W)\log (H+W))$，空间复杂度 $\Theta(H+W)$
该算法可以通过所有测试点。

### 猜数

题目来源：Petrozavodsk Winter 2022 Day 6: ICPC Camp Day 1, PKU Contest, Problem E
QOJ 链接：[https://qoj.ac/contest/824/problem/2609](https://qoj.ac/contest/824/problem/2609)
官方题解：[https://qoj.ac/download.php?type=attachments&id=824&r=1](https://qoj.ac/download.php?type=attachments&id=824&r=1)
在获得足够的关于 `seed` 的信息之前，返回值与真实答案不怎么相关。因此我们应当考虑先求出 `seed` 。
生成一次随机数可以被拆成三步：
- `seed*=n;`
- `seed%=P;`
- `return seed%n;`
注意到，如果没有第二步，那么 `seed%n` 永远是 $0$ 。因此 `seed%n` 可以告诉我们在第二步中 `seed` 减掉了几个 `P` 。
由此可以获得一个暴力做法：先询问 $40$ 次 $0$ ，获得每一次的 `seed%n` 。然后在 $[0,P)$ 里枚举 `seed` ，判断结果是否符合。符合的那个 `seed` 就是真实的 `seed` 。接下来再用 $60$ 次询问来二分答案即可。
由于错误的 `seed` 只会期望符合前 $O(1)$ 个位置，因此这个做法的时间复杂度是 $O(P)$ 的。
（事实上，直接判断返回值是否正确即可，因此并不需要推导到这里就可以获得 $O(P)$ 的暴力做法。）
考虑如何优化。
倒着做，维护 $[l,r]$ 表示已知 `seed` 现在在区间 $[l,r]$ 内，每次回退一步。那么由于知道 `seed%P` 减掉了几个 `P` ，就可以知道在第二步之前的 `seed` 所在的区间。然后 `seed*=n` 反过来就可以把区间长度除掉 $n$ 。
由于 $n^{40}>P$ ，所以回退 $40$ 步足以确定起始的 `seed` 。然后仍然二分答案即可。

### 抽卡

题目来源：Petrozavodsk Winter 2022 Day 6: ICPC Camp Day 1, PKU Contest, Problem B
QOJ 链接：[https://qoj.ac/contest/824/problem/2606](https://qoj.ac/contest/824/problem/2606)
官方题解：[https://qoj.ac/download.php?type=attachments&id=824&r=1](https://qoj.ac/download.php?type=attachments&id=824&r=1)

#### 题解一

首先考虑计算一次合法抽卡的概率。
令 $f_{i,j}$ 表示一次 $i$ 级抽卡，合法且抽出的卡最大值**不超过** $j$ 的概率，那么有：
$$f_{i,j}=f_{i-1,j}^{b_i}-f_{i-1,i-1}^{b_i}$$
后一项即为减去不合法的概率。
我们把抽卡过程看成一棵树，因为各叶子是等价的，只考虑最左侧叶子的贡献，考虑对根到最左侧的路径进行 $\text{dp}$（另一种理解是将各级抽卡的第一次抽卡设为关键抽卡）。
接下来考虑倒过来 $\text{dp}$，设 $g_{i,j}$ 表示一次合法抽卡过程中，若最左侧的 $i$ 级抽卡最大值为 $j$ ，最终 $n$ 级抽卡合法的概率，那么有：
$$g_{i,j}=g_{i+1,j}\sum_{k=0}^j s_{i,k}+\sum_{k=j+1}s_{i,k}g_{i+1,k}$$
其中 $s_{i,j}=f_{i,j}^{b_{i+1}-1}-f_{i,j-1}^{b_{i+1}-1}$，即第 $i$ 层其他抽卡最大值为 $j$ 的概率。上述式子可以分两部分前缀和优化。
总复杂度为 $O(n^2\log B)$，瓶颈在计算快速幂。

#### 题解二

显然 $m>n$ 可以特判成 $m=n$ ，所以后面认为抽卡等级和卡等级的上限是相同的。另外，后面的 $a_i$ 也全都表示概率，即已经除掉了 $\sum_{i=0}^n a_i$ 。
使用自底向上的思考方式，把低等级抽卡逐步合并为高等级抽卡。
相应地，我们也在合并的过程中逐步确定每次抽出来的卡的等级。当我们在考虑所有 $k$ 级抽卡时，所有等级 $<k$ 的卡已经确定了，而等级 $\ge k$ 的卡的等级则未定。
那么可以设
$$
f_k(x)=\sum_{s\in S_k} p(s)x^{cnt_{\ge k}(s)}
$$
 其中 $S_k$ 表示当所有等级 $\ge k$ 的卡被视为同一类时，合法的 $k$ 级抽卡的集合；$p(s)$ 表示等级 $<k$ 的卡的出现概率的乘积；$cnt_{\ge k}(s)$ 表示等级 $\ge k$ 的卡的个数。
转移式非常简单：
$$
f_0(x)=x\\
f_k(x)=f_{k-1}^{b_k}(x+a_{k-1})-f_{k-1}^{b_k}(a_{k-1})
$$
并且容易发现 $f_n(a_n)$ 就是一个 $n$ 级抽卡合法的概率，$a_nf'_n(a_n)$ 就是 $p_n\cdot q$ 。
如何求出这两个点值呢？从转移式可以注意到，为了求出这两个点值，对于所有的 $f_k(x)$ ，$x$ 只可能是从 $k$ 开始的若干个 $a_i$ 之和！
因此，可以设 $dp1_{k,r}=f_k(\sum_{i=k}^r a_i),dp2_{k,r}=f_k'(\sum_{i=k}^r a_i)$ ，然后使用转移式转移即可。
接下来考虑求出所有的 $p_k\cdot q$ 。
受到 $a_nf'_n(a_n)$ 的启发，可以想到用第二个变量来记录等级为 $k$ 的卡的数量，然后同样用求导的方式求出 $p_k\cdot q$ 。于是可以引入二元生成函数 $g(x,y)$ ：
$$
g_0(x,y)=x\\
g_k(x,y)=\begin{cases}
g^{b_k}_{k-1}(x+y,y)-g^{b_k}_{k-1}(y,y)&k=T\\
g^{b_k}_{k-1}(x+a_{k-1},y)-g^{b_k}_{k-1}(a_{k-1},y)&k\ne T
\end{cases}
$$
其中 $T$ 表示现在要求 $p_T\cdot q$ 。
那么设 $h_k(x,y)=\frac{\partial}{\partial y}g_k(x,y)$ ，就有 $p_T\cdot q=a_T h_n(a_n,a_T)$ 。
容易发现 $g,h$ 也有与 $f$ 类似的性质，即 $x$ 只可能代入 $\sum_{i=k}^r a_i$ ，因此也可以用类似的 DP 求出所有点值。这样就获得了一个 $O(n^3\log b)$ 的做法。
为了优化，注意到我们总是有 $g_k(\sum_{i=k}^r a_i,a_T)=f_k(\sum_{i=k}^r a_i)$ ，只有 $h$ 不确定，而且在 $g$ 已知时 $h$ 的转移是线性关系。因此可以设 $dp3_{k,r}$ 表示 $h_k(\sum_{i=k}^r a_i,a_T)$ 的贡献系数，而这个贡献系数与 $T$ 无关。这样倒着把 $dp3$ 递推出来之后就可以直接得到答案了。
所以最终复杂度 $O(n^2\log b)$ 。
