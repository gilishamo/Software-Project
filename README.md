# README
This project implements an algorithm for detecting community structures (clusters) in a network. 
We represent a network by a Graph and we generate a division of the graph that maximizes the modularity.

This project implements two main mathematical algorithms:

- Dividing a network into modularity groups
- Power Iteration Algorithm

Definition: A given group of vertices in a network is considered a **community** if the number of edge within the group is significantly more than expected (by chance). 
Meaning the group of nodes in a community are more densely connected internally than with the rest of the network.

Definition: The **modularity** of a group is the number of edges within the group minus the expected number of edges in a random graph with the same degree.

Modularity measures the strength of division of a network into modules (clusters). Networks with high modularity have dense connections between the nodes within modules and sparse connections between nodes in different modules.

#### Dividing a network into modularity groups

A network is represented by a graph G=(V,E), and let A be the adjacency matrix of G s.t:


<img src="https://i.upmath.me/svg/%0AA%20%3D%20%5Cbegin%7Bcases%7D%201%20%26%20(i%2Cj)%20%5Cin%20E%20%5C%5C%200%20%26%20otherwise%20%5Cend%7Bcases%7D%20%2C%20%5Cquad%20and%5C%3B%5Cforall%20i%20%5C%3B%20A_%7Bii%7D%3D0%0A" alt="
A = \begin{cases} 1 &amp; (i,j) \in E \\ 0 &amp; otherwise \end{cases} , \quad and\;\forall i \; A_{ii}=0
" />
A given group of vertices in a network is considered a community if the number of edges within the group is significantly more than expected. We define the modularity of a group as the number of edges within the group minus the expected number of edges in a random graph with the same degree. 

Formally, let <img src="https://i.upmath.me/svg/k_i" alt="k_i" /> be the degree of vertex i and let M = <img src="https://i.upmath.me/svg/%5Csum_i%20k_i" alt="\sum_i k_i" />, then the expected number of edges between vertex i and vertex j is <img src="https://i.upmath.me/svg/%5Cfrac%20%7Bk_ik_j%7D%20%7BM%7D" alt="\frac {k_ik_j} {M}" /> .
Let <img src="https://i.upmath.me/svg/S%20%5Csubseteq%20V%20" alt="S \subseteq V " /> a sub group of vertices, we define the modularity of S as:
<img src="https://i.upmath.me/svg/%20Q_s%20%3D%20%5Csum_%7Bi%2Cj%20%5Cin%20S%7D%20(A_%7Bij%7D%20-%20%5Cfrac%20%7Bk_ik_j%7D%20%7BM%7D%20)" alt=" Q_s = \sum_{i,j \in S} (A_{ij} - \frac {k_ik_j} {M} )" />. 
Our goal is to find a division of the graph into sub groups such that the modularity of the graph (the sum of all group modularity) is close to maximal.

**Dividing Into Two**

Initially we will explain how to find a good division into just two communities.

Let G=(V, E) <img src="https://i.upmath.me/svg/%7CV%7C%3Dn" alt="|V|=n" />

Let D = {<img src="https://i.upmath.me/svg/A%2C%20B" alt="A, B" />} be a division of G into two groups and let s be a vector (<img src="https://i.upmath.me/svg/s_1%2C...%2Cs_n" alt="s_1,...,s_n" />) s.t for each vertex <img src="https://i.upmath.me/svg/%20i%20%5Cin%20V" alt=" i \in V" />
<img src="https://i.upmath.me/svg/s_i%20%3D%20%5Cbegin%7Bcases%7D%201%20%26%20i%20%5Cin%20A%20%5C%5C%20-1%20%26%20i%20%5Cin%20B%5Cend%7Bcases%7D" alt="s_i = \begin{cases} 1 &amp; i \in A \\ -1 &amp; i \in B\end{cases}" />

Observe that: 

<img src="https://i.upmath.me/svg/%20%5Cfrac%20%7B1%7D%20%7B2%7D(s_is_j%20%2B%201)%20" alt=" \frac {1} {2}(s_is_j + 1) " /> = <img src="https://i.upmath.me/svg/%5Cbegin%20%7Bcases%7D%201%20%26%20s_i%2Cs_j%20%5Cin%20A%20%5C%3A%20OR%20%5C%3A%20s_i%2Cs_j%20%5Cin%20B%20%5C%5C%200%20%26%20otherwise%20%20%5Cend%7Bcases%7D%20" alt="\begin {cases} 1 &amp; s_i,s_j \in A \: OR \: s_i,s_j \in B \\ 0 &amp; otherwise  \end{cases} " />

We can express the modularity as:

Q = <img src="https://i.upmath.me/svg/%20%5Csum_%7Bi%2Cj%20%5Cin%20A%7D%20A_%7Bij%7D%20-%20%5Cfrac%20%7Bk_ik_j%7D%20%7BM%7D" alt=" \sum_{i,j \in A} A_{ij} - \frac {k_ik_j} {M}" /> + <img src="https://i.upmath.me/svg/%20%5Csum_%7Bi%2Cj%20%5Cin%20B%7D%20A_%7Bij%7D%20-%20%5Cfrac%20%7Bk_ik_j%7D%20%7BM%7D" alt=" \sum_{i,j \in B} A_{ij} - \frac {k_ik_j} {M}" />  =

 <img src="https://i.upmath.me/svg/%20%5Csum_%7Bi%2Cj%20%5Cin%20V%7D%20" alt=" \sum_{i,j \in V} " /> <img src="https://i.upmath.me/svg/%5Cfrac%20%7B1%7D%20%7B2%7D(s_is_j%20%2B%201)%20" alt="\frac {1} {2}(s_is_j + 1) " /> <img src="https://i.upmath.me/svg/%20(A_%7Bij%7D%20-%20%5Cfrac%20%7Bk_ik_j%7D%20%7BM%7D)" alt=" (A_{ij} - \frac {k_ik_j} {M})" /> =

 <img src="https://i.upmath.me/svg/%5Cfrac%20%7B1%7D%20%7B2%7D%20" alt="\frac {1} {2} " /> <img src="https://i.upmath.me/svg/%20%5Csum_%7Bi%2Cj%20%5Cin%20V%7D%20(A_%7Bij%7D%20-%20%5Cfrac%20%7Bk_ik_j%7D%20%7BM%7D)" alt=" \sum_{i,j \in V} (A_{ij} - \frac {k_ik_j} {M})" /> <img src="https://i.upmath.me/svg/%20(s_is_j%20%2B%201)%20" alt=" (s_is_j + 1) " />

Since <img src="https://i.upmath.me/svg/%20%5Csum_%7Bi%2Cj%20%5Cin%20V%7D%20A_%7Bij%7D%20%3D%20%5Csum_%7Bi%20%5Cin%20V%7D%20K_i%20%3D%20M" alt=" \sum_{i,j \in V} A_{ij} = \sum_{i \in V} K_i = M" />
We can express the modularity as:

Q =  <img src="https://i.upmath.me/svg/%5Cfrac%20%7B1%7D%20%7B2%7D%20" alt="\frac {1} {2} " /> <img src="https://i.upmath.me/svg/%20%5Csum_%7Bi%2Cj%20%5Cin%20V%7D%20(A_%7Bij%7D%20-%20%5Cfrac%20%7Bk_ik_j%7D%20%7BM%7D)" alt=" \sum_{i,j \in V} (A_{ij} - \frac {k_ik_j} {M})" /> <img src="https://i.upmath.me/svg/%20(s_is_j%20%2B%201)%20" alt=" (s_is_j + 1) " /> = <img src="https://i.upmath.me/svg/%20%5Cfrac%20%7B1%7D%20%7B2%7D%20%5Csum_%7Bi%2Cj%20%5Cin%20V%7D%20(A_%7Bij%7D%20-%20%20%5Cfrac%20%7Bk_ik_j%7D%20%7BM%7D)(s_is_j)%20%2B%20%5Cfrac%20%7B1%7D%7B2%7D%5Csum_%7Bi%2Cj%20%5Cin%20V%7D(A_%7Bij%7D-%5Cfrac%7Bk_ik_j%7D%7BM%7D)" alt=" \frac {1} {2} \sum_{i,j \in V} (A_{ij} -  \frac {k_ik_j} {M})(s_is_j) + \frac {1}{2}\sum_{i,j \in V}(A_{ij}-\frac{k_ik_j}{M})" />  = 
 <img src="https://i.upmath.me/svg/%20%5Cfrac%20%7B1%7D%20%7B2%7D%20%5Csum_%7Bi%2Cj%20%5Cin%20V%7D%20(A_%7Bij%7D%20-%20%20%5Cfrac%20%7Bk_ik_j%7D%20%7BM%7D)(s_is_j)%20%2B%20%5Cfrac%20%7B1%7D%7B2%7D%5Csum_%7Bi%2Cj%20%5Cin%20E%7DA_%7Bij%7D-%5Cfrac%20%7B1%7D%20%7B2%7D%20%5Csum_%7Bi%2Cj%20%5Cin%20V%7D%20%5Cfrac%7Bk_ik_j%7D%7BM%7D" alt=" \frac {1} {2} \sum_{i,j \in V} (A_{ij} -  \frac {k_ik_j} {M})(s_is_j) + \frac {1}{2}\sum_{i,j \in E}A_{ij}-\frac {1} {2} \sum_{i,j \in V} \frac{k_ik_j}{M}" /> = 
<img src="https://i.upmath.me/svg/%20%5Cfrac%20%7B1%7D%20%7B2%7D%20%5Csum_%7Bi%2Cj%20%5Cin%20V%7D%20(A_%7Bij%7D%20-%20%20%5Cfrac%20%7Bk_ik_j%7D%20%7BM%7D)(s_is_j)%20%2B%20%5Cfrac%20%7B1%7D%7B2%7D%5Csum_%7Bi%2Cj%20%5Cin%20V%7DA_%7Bij%7D-%5Cfrac%20%7B1%7D%20%7B2M%7D%20%5Csum_%7Bi%2Cj%20%5Cin%20V%7Dk_ik_j" alt=" \frac {1} {2} \sum_{i,j \in V} (A_{ij} -  \frac {k_ik_j} {M})(s_is_j) + \frac {1}{2}\sum_{i,j \in V}A_{ij}-\frac {1} {2M} \sum_{i,j \in V}k_ik_j" /> = 
 <img src="https://i.upmath.me/svg/%20%5Cfrac%20%7B1%7D%20%7B2%7D%20%5Csum_%7Bi%2Cj%20%5Cin%20V%7D%20(A_%7Bij%7D%20-%20%20%5Cfrac%20%7Bk_ik_j%7D%20%7BM%7D)(s_is_j)%20%2B%20%5Cfrac%20%7B1%7D%7B2%7DM-%5Cfrac%20%7B1%7D%20%7B2M%7D%20%5Csum_%7Bi%20%5Cin%20V%7Dk_i%20%5Csum_%7Bj%20%5Cin%20V%7D%20k_j" alt=" \frac {1} {2} \sum_{i,j \in V} (A_{ij} -  \frac {k_ik_j} {M})(s_is_j) + \frac {1}{2}M-\frac {1} {2M} \sum_{i \in V}k_i \sum_{j \in V} k_j" /> = 
<img src="https://i.upmath.me/svg/%20%5Cfrac%20%7B1%7D%20%7B2%7D%20%5Csum_%7Bi%2Cj%20%5Cin%20V%7D%20(A_%7Bij%7D%20-%20%20%5Cfrac%20%7Bk_ik_j%7D%20%7BM%7D)(s_is_j)%20%2B%20%5Cfrac%20%7B1%7D%7B2%7DM-%5Cfrac%20%7B1%7D%20%7B2M%7D%20M%5E2%20" alt=" \frac {1} {2} \sum_{i,j \in V} (A_{ij} -  \frac {k_ik_j} {M})(s_is_j) + \frac {1}{2}M-\frac {1} {2M} M^2 " /> =
 <img src="https://i.upmath.me/svg/%20%5Cfrac%20%7B1%7D%20%7B2%7D%20%5Csum_%7Bi%2Cj%20%5Cin%20V%7D%20(A_%7Bij%7D%20-%20%20%5Cfrac%20%7Bk_ik_j%7D%20%7BM%7D)(s_is_j)%20%2B%20%5Cfrac%20%7B1%7D%7B2%7DM-%5Cfrac%20%7B1%7D%20%7B2%7DM" alt=" \frac {1} {2} \sum_{i,j \in V} (A_{ij} -  \frac {k_ik_j} {M})(s_is_j) + \frac {1}{2}M-\frac {1} {2}M" /> = 
<img src="https://i.upmath.me/svg/%20%5Cfrac%20%7B1%7D%20%7B2%7D%20%5Csum_%7Bi%2Cj%20%5Cin%20V%7D%20(A_%7Bij%7D%20-%20%20%5Cfrac%20%7Bk_ik_j%7D%20%7BM%7D)(s_is_j)%20" alt=" \frac {1} {2} \sum_{i,j \in V} (A_{ij} -  \frac {k_ik_j} {M})(s_is_j) " />

Let B be the modularity matrix, <img src="https://i.upmath.me/svg/B_%7Bij%7D%20%3D%20A_%7Bij%7D%20-%5Cfrac%20%7Bk_ik_j%7D%20%7BM%7D%20" alt="B_{ij} = A_{ij} -\frac {k_ik_j} {M} " />, hence we can write the modularity as:

Q = <img src="https://i.upmath.me/svg/%20%5Cfrac%20%7B1%7D%20%7B2%7D%20%5Csum_%7Bi%2Cj%20%5Cin%20V%7D%20(A_%7Bij%7D%20-%20%20%5Cfrac%20%7Bk_ik_j%7D%20%7BM%7D)(s_is_j)%20" alt=" \frac {1} {2} \sum_{i,j \in V} (A_{ij} -  \frac {k_ik_j} {M})(s_is_j) " /> =
<img src="https://i.upmath.me/svg/%20%5Cfrac%7B1%7D%7B2%7D%20s%5ETBs" alt=" \frac{1}{2} s^TBs" />

Now our goal is to find the vertex s that maximizes the modularity Q.

Note that B is a symmetric matrix, thus it is diagonalizable with n eigenvalues. In each
row and column its elements sum to zero, thus B has the eigenvector (1, . . . , 1) with a
corresponding eigenvalue 0.

Let (<img src="https://i.upmath.me/svg/%5Cbeta_1%2C%20.%20.%20.%20%2C%20%5Cbeta_n" alt="\beta_1, . . . , \beta_n" />) be the eigenvalues of B such that (<img src="https://i.upmath.me/svg/%5Cbeta_1%20%E2%89%A5...%20%E2%89%A5%20%5Cbeta_n" alt="\beta_1 ≥... ≥ \beta_n" />), and let (<img src="https://i.upmath.me/svg/u_1%2C%20.%20.%20.%20%2C%20u_n" alt="u_1, . . . , u_n" />) be the
corresponding normalized eigenvectors. For all vectors with a fixed norm c, the vector <img src="https://i.upmath.me/svg/c%5Ccdot%20u_1" alt="c\cdot u_1" />
achieves the maximum value for Q (which is <img src="https://i.upmath.me/svg/c%5E2%5Cbeta_1" alt="c^2\beta_1" />). However, recall we look for a vector s
whose elements are ±1. Thus, we need to make s as close to being parallel to <img src="https://i.upmath.me/svg/u_1" alt="u_1" /> as possible,
which is equivalent to maximizing the dot product <img src="https://i.upmath.me/svg/u_i%5ETs" alt="u_i^Ts" />.
The maximum is achieve by setting:
<img src="https://i.upmath.me/svg/s_i%20%3D%20%5Cbegin%7Bcases%7D%20%2B1%20%26%20u_1%5Bi%5D%20%3E%200%20%5C%5C%20-1%20%26%20otherwise%20%5Cend%7Bcases%7D" alt="s_i = \begin{cases} +1 &amp; u_1[i] &gt; 0 \\ -1 &amp; otherwise \end{cases}" />

In other words, we need to obtain the leading eigenvector of B, i.e. the eigenvector of B
with the largest eigenvalue. Then, vertices whose corresponding elements are positive go in
one group, and the rest of the vertices go in the other group.

It is possible for there to be no positive eigenvalues of B. In this case, the leading eigenvector
is the vector (1, . . . , 1), corresponding to all vertices in a single group together. in this case, there is no division of the network
that results in a positive modularity. The modularity of an undivided network is zero, which
is the best that can be achieved.

Additionally, it could happen that although the leading eigenvalue is positive, <img src="https://i.upmath.me/svg/s%5ETBs" alt="s^TBs" /> is
non-positive, i.e. the division represented by s has a worse modularity than a trivial division
into one group.

**Dividing Into Modularity Groups**

Until now we described a division of a network into two groups, however Many networks contain more than two communities, thus we would like to find
good divisions of networks into a larger number of groups. Our approach is to divide each group into two until there is no division of the group.

To divide a group, we cannot use the same method since it must take into consideration
the entire graph, instead we need to look at the additional change <img src="https://i.upmath.me/svg/%5CDelta%20Q" alt="\Delta Q" /> to the modularity.

Suppose we divide a group g of size <img src="https://i.upmath.me/svg/n_g" alt="n_g" /> in two, the change depends on pairs of elements in g.
Prior to the division, the contribution of pairs in g to Q was <img src="https://i.upmath.me/svg/%20%5Csum_%7Bi%2Cj%20%5Cin%20g%7D%20B_%7Bij%7D%20" alt=" \sum_{i,j \in g} B_{ij} " />. Let s be a vector of size <img src="https://i.upmath.me/svg/%20n_g" alt=" n_g" /> with +1, -1 elements representing a division of g into two groups, and define <img src="https://i.upmath.me/svg/%20%5Cdelta_%7Bij%7D%20" alt=" \delta_{ij} " /> as:

<img src="https://i.upmath.me/svg/%20%5Cdelta_%7Bij%7D%3D%5Cbegin%7Bcases%7D%201%20%26%20if%5C%3Bi%20%3D%20j%20%5C%5C%200%20%26%20otherwise%20%5Cend%7Bcases%7D" alt=" \delta_{ij}=\begin{cases} 1 &amp; if\;i = j \\ 0 &amp; otherwise \end{cases}" />

It follows that the change in the modularity is:
<img src="https://i.upmath.me/svg/%5CDelta%20Q" alt="\Delta Q" /> = <img src="https://i.upmath.me/svg/%5Cfrac%20%7B1%7D%20%7B2%7D%20%20%5Csum_%7Bi%2Cj%20%5Cin%20g%7D%20(A_%7Bij%7D%20-%20%5Cfrac%20%7Bk_ik_j%7D%20%7BM%7D)(s_is_j%20%2B%201)%20-%20%5Csum_%7Bi%2Cj%20%5Cin%20g%7D%20B_%7Bij%7D" alt="\frac {1} {2}  \sum_{i,j \in g} (A_{ij} - \frac {k_ik_j} {M})(s_is_j + 1) - \sum_{i,j \in g} B_{ij}" /> =
<img src="https://i.upmath.me/svg/%5Cfrac%20%7B1%7D%20%7B2%7D%5Csum_%7Bi%2Cj%20%5Cin%20g%7D%20B_%7Bij%7D%20(s_is_j%20%2B%201)%20-%20%5Csum_%7Bi%2Cj%20%5Cin%20g%7D%20B_%7Bij%7D" alt="\frac {1} {2}\sum_{i,j \in g} B_{ij} (s_is_j + 1) - \sum_{i,j \in g} B_{ij}" />=
<img src="https://i.upmath.me/svg/%5Cfrac%20%7B1%7D%20%7B2%7D%20%5Csum_%7Bi%2Cj%20%5Cin%20g%7D%20B_%7Bij%7D%20s_is_j%20%2B%20%5Cfrac%7B1%7D%7B2%7D%5Csum_%7Bi%2Cj%20%5Cin%20g%7DB_%7Bij%7D%20-%20%5Csum_%7Bi%2Cj%20%5Cin%20g%7D%20B_%7Bij%7D" alt="\frac {1} {2} \sum_{i,j \in g} B_{ij} s_is_j + \frac{1}{2}\sum_{i,j \in g}B_{ij} - \sum_{i,j \in g} B_{ij}" /> =
<img src="https://i.upmath.me/svg/%5Cfrac%20%7B1%7D%20%7B2%7D%20%5Csum_%7Bi%2Cj%20%5Cin%20g%7D%20(B_%7Bij%7D%20s_is_j%20-B_%7Bij%7D)%20" alt="\frac {1} {2} \sum_{i,j \in g} (B_{ij} s_is_j -B_{ij}) " />=
<img src="https://i.upmath.me/svg/%5Cfrac%20%7B1%7D%20%7B2%7D%20%5Csum_%7Bi%2Cj%20%5Cin%20g%7D%20(B_%7Bij%7D%20-%5Cdelta%20_%7Bij%7D%20%5Csum_%7Bk%20%5Cin%20g%7DB_%7Bik%7D)s_is_j" alt="\frac {1} {2} \sum_{i,j \in g} (B_{ij} -\delta _{ij} \sum_{k \in g}B_{ik})s_is_j" />

Let $B[g]$ be the symmetric <img src="https://i.upmath.me/svg/n_g" alt="n_g" /> x <img src="https://i.upmath.me/svg/n_g" alt="n_g" /> sub-matrix of B corresponding to the rows and columns of g. Let <img src="https://i.upmath.me/svg/f_i%5Eg%3D%5Csum_%7Bk%20%5Cin%20g%7D%20B%5Bg%5D_%7Bik%7D%20" alt="f_i^g=\sum_{k \in g} B[g]_{ik} " /> .
Let <img src="https://i.upmath.me/svg/%5Cbar%20B%5Bg%5D" alt="\bar B[g]" /> be a symmetric <img src="https://i.upmath.me/svg/n_g" alt="n_g" /> x <img src="https://i.upmath.me/svg/n_g" alt="n_g" /> matrix with elements:
<img src="https://i.upmath.me/svg/%5Cbar%20B%5Bg%5D_%7Bij%7D%20%3D%20B%5Bg%5D_%7Bij%7D%20-%20%5Cdelta%20_%7Bij%7D%20f_i%5Eg%20" alt="\bar B[g]_{ij} = B[g]_{ij} - \delta _{ij} f_i^g " />
Hence we can write <img src="https://i.upmath.me/svg/%5CDelta%20Q" alt="\Delta Q" /> as:
<img src="https://i.upmath.me/svg/%5CDelta%20Q%20%3D%20%5Cfrac%7B1%7D%7B2%7Ds%5ET%5Cbar%20B%5Bg%5Ds%20" alt="\Delta Q = \frac{1}{2}s^T\bar B[g]s " />

this equation has the same form as before (for computing the modularity of a network with two sub groups), hence we can apply the same algorithm to maximize <img src="https://i.upmath.me/svg/%5CDelta%20Q" alt="\Delta Q" />, according to the leading eigenpair of <img src="https://i.upmath.me/svg/%5Cbar%20B%5Bg%5D%20" alt="\bar B[g] " />

Note that if g is the entire graph then <img src="https://i.upmath.me/svg/%20%5Cforall%20i%0A%3A%20f_i%5Eg%20%3D%200%20" alt=" \forall i
: f_i^g = 0 " /> and thus <img src="https://i.upmath.me/svg/%5Cbar%20B%5Bg%5D%20%3D%20B" alt="\bar B[g] = B" />, allowing us to use this algorithm in all cases.

**Modularity Maximization**

We can further maximize a division of groups into two. Suppose {<img src="https://i.upmath.me/svg/g_1%2C%20g_2" alt="g_1, g_2" />} is an initial division of g into two groups. In order to maximize the change in modularity we want to find a single vertex that when moved to the other group, gives the biggest increase in modularity or the smallest decrease if no increase is possible.
We will repeat this process with the constraint that each vertex may only be moved once, until all vertices have been moved. Once done, from all the states of division into two groups during the operation, find the state that has the maximal modularity, and start again from this state.
We repeat the entire process iteratively until no further improvement is found.

#### Power Iteration

Power iteration is an eigenvalue algorithm to find a dominant eigenpair: given a diagonalizable matrix A, the algorithm will produce a number <img src="https://i.upmath.me/svg/%5Clambda" alt="\lambda" />, which is the greatest in absolute value, eigenvalue of A, and  a non zero vector <img src="https://i.upmath.me/svg/v" alt="v" /> which is a corresponding eigenvector of <img src="https://i.upmath.me/svg/%5Clambda" alt="\lambda" />.

The algorithm starts with a random vector in our case - <img src="https://i.upmath.me/svg/b_0" alt="b_0" />. The method is described by the recurrence relation:

<img src="https://i.upmath.me/svg/b_%7Bk%2B1%7D%3D%5Cfrac%7BAb_k%7D%7B%5Cparallel%7BAb_k%7D%5Cparallel%7D" alt="b_{k+1}=\frac{Ab_k}{\parallel{Ab_k}\parallel}" />    .

**Matrix Shifting**

Although, since the division into two algorithm requires a leading eigenpair we use matrix shifting.

Let <img src="https://i.upmath.me/svg/C" alt="C" /> be a matrix with the eigenvalues {<img src="https://i.upmath.me/svg/%5Clambda_1%2C...%2C%5Clambda_n" alt="\lambda_1,...,\lambda_n" />}, and let the 1-norm of <img src="https://i.upmath.me/svg/C" alt="C" /> be the sum of its largest column: <img src="https://i.upmath.me/svg/%5Cparallel%20C%20%5Cparallel%20_1%3D%20max_j(%5Csum_i%7CC_%7Bij%7D%7C)%20" alt="\parallel C \parallel _1= max_j(\sum_i|C_{ij}|) " /> .

Let <img src="https://i.upmath.me/svg/C'%20%3D%20%5Cparallel%20C%5Cparallel%20_1%20%5Ccdot%20I%20%2B%20C" alt="C' = \parallel C\parallel _1 \cdot I + C" />, then <img src="https://i.upmath.me/svg/C'" alt="C'" /> has the same eigenvectors as <img src="https://i.upmath.me/svg/C" alt="C" /> and the eigenvalues of <img src="https://i.upmath.me/svg/C'" alt="C'" /> are: {<img src="https://i.upmath.me/svg/%5Clambda%20_1%20%2B%20%5Cparallel%20C%5Cparallel%20_1%2C...%2C%5Clambda_n%20%2B%20%5Cparallel%20C%5Cparallel_1" alt="\lambda _1 + \parallel C\parallel _1,...,\lambda_n + \parallel C\parallel_1" />}. Thus the dominant eigenpair of <img src="https://i.upmath.me/svg/C'" alt="C'" /> is (<img src="https://i.upmath.me/svg/%5Clambda_1%20%2B%5Cparallel%20C%5Cparallel_1%2C%20v_1" alt="\lambda_1 +\parallel C\parallel_1, v_1" />), and the leading eigenpair of <img src="https://i.upmath.me/svg/C" alt="C" /> is (<img src="https://i.upmath.me/svg/%5Clambda_1%2C%20v_1" alt="\lambda_1, v_1" />).