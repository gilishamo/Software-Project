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


$$
A = \begin{cases} 1 & (i,j) \in E \\ 0 & otherwise \end{cases} , \quad and\;\forall i \; A_{ii}=0
$$
A given group of vertices in a network is considered a community if the number of edges within the group is significantly more than expected. We define the modularity of a group as the number of edges within the group minus the expected number of edges in a random graph with the same degree. 
Formally, let $$k_i$$ be the degree of vertex i and let M = $\sum_i k_i$, then the expected number of edges between vertex i and vertex j is $\frac {k_ik_j} {M}$ .
Let $$S \subseteq V $$ a sub group of vertices, we define the modularity of S as:
$$ Q_s = \sum_{i,j \in S} (A_{ij} - \frac {k_ik_j} {M} )$$. 
Our goal is to find a division of the graph into sub groups such that the modularity of the graph (the sum of all group modularity) is close to maximal.

**Dividing Into Two**

Initially we will explain how to find a good division into just two communities.

Let G=(V, E) $$|V|=n$$

Let D = {$$A, B$$} be a division of G into two groups and let s be a vector ($$s_1,...,s_n$$) s.t for each vertex $$ i \in E$$
$$s_i = \begin{cases} 1 & i \in A \\ -1 & i \in B\end{cases}$$

Observe that: 

$$ \frac {1} {2}(s_is_j + 1) $$ = $$\begin {cases} 1 & s_i = s_j   \\ 0 & otherwise  \end{cases} $$

We can express the modularity as:

Q = $$ \sum_{i,j \in A} A_{ij} - \frac {k_ik_j} {M}$$ + $$ \sum_{i,j \in B} A_{ij} - \frac {k_ik_j} {M}$$  =

 $$ \sum_{i,j \in V} $$ $$\frac {1} {2}(s_is_j + 1) $$ $$ (A_{ij} - \frac {k_ik_j} {M})$$ =

 $$\frac {1} {2} $$ $$ \sum_{i,j \in V} (A_{ij} - \frac {k_ik_j} {M})$$ $$ (s_is_j + 1) $$

Since $$ \sum_{i,j \in V} A_{ij} = \sum_{i \in V} K_i = M$$
We can express the modularity as:

Q =  $$\frac {1} {2} $$ $$ \sum_{i,j \in V} (A_{ij} - \frac {k_ik_j} {M})$$ $$ (s_is_j + 1) $$ = $$ \frac {1} {2} \sum_{i,j \in V} (A_{ij} -  \frac {k_ik_j} {M})(s_is_j) + \frac {1}{2}\sum_{i,j \in V}(A_{ij}-\frac{k_ik_j}{M})$$  = 
 $$ \frac {1} {2} \sum_{i,j \in V} (A_{ij} -  \frac {k_ik_j} {M})(s_is_j) + \frac {1}{2}\sum_{i,j \in E}A_{ij}-\frac {1} {2} \sum_{i,j \in V} \frac{k_ik_j}{M}$$ = 
$$ \frac {1} {2} \sum_{i,j \in V} (A_{ij} -  \frac {k_ik_j} {M})(s_is_j) + \frac {1}{2}\sum_{i,j \in V}A_{ij}-\frac {1} {2M} \sum_{i,j \in V}k_ik_j$$ = 
 $$ \frac {1} {2} \sum_{i,j \in V} (A_{ij} -  \frac {k_ik_j} {M})(s_is_j) + \frac {1}{2}M-\frac {1} {2M} \sum_{i \in V}k_i \sum_{j \in V} k_j$$ = 
$$ \frac {1} {2} \sum_{i,j \in V} (A_{ij} -  \frac {k_ik_j} {M})(s_is_j) + \frac {1}{2}M-\frac {1} {2M} M^2 $$ =
 $$ \frac {1} {2} \sum_{i,j \in V} (A_{ij} -  \frac {k_ik_j} {M})(s_is_j) + \frac {1}{2}M-\frac {1} {2}M$$ = 
$$ \frac {1} {2} \sum_{i,j \in V} (A_{ij} -  \frac {k_ik_j} {M})(s_is_j) $$

Let B be the modularity matrix, $$B_{ij} = A_{ij} -\frac {k_ik_j} {M} $$, hence we can write the modularity as:

Q = $$ \frac {1} {2} \sum_{i,j \in V} (A_{ij} -  \frac {k_ik_j} {M})(s_is_j) $$ =
$$ \frac{1}{2} s^TBs$$

Now our goal is to find the vertex s that maximizes the modularity Q.

Note that B is a symmetric matrix, thus it is diagonalizable with n eigenvalues. In each
row and column its elements sum to zero, thus B has the eigenvector (1, . . . , 1) with a
corresponding eigenvalue 0.

Let ($\beta_1, . . . , \beta_n$) be the eigenvalues of B such that ($\beta_1 ≥... ≥ \beta_n$), and let ($u_1, . . . , u_n$) be the
corresponding normalized eigenvectors. For all vectors with a fixed norm c, the vector $c\cdot u_1$
achieves the maximum value for Q (which is $c^2\beta_1$). However, recall we look for a vector s
whose elements are ±1. Thus, we need to make s as close to being parallel to $u_1$ as possible,
which is equivalent to maximizing the dot product $$u_i^Ts$$.
The maximum is achieve by setting:
$$s_i = \begin{cases} +1 & u_1[i] > 0 \\ -1 & otherwise \end{cases}$$

In other words, we need to obtain the leading eigenvector of B, i.e. the eigenvector of B
with the largest eigenvalue. Then, vertices whose corresponding elements are positive go in
one group, and the rest of the vertices go in the other group.

It is possible for there to be no positive eigenvalues of B. In this case, the leading eigenvector
is the vector (1, . . . , 1), corresponding to all vertices in a single group together. in this case, there is no division of the network
that results in a positive modularity. The modularity of an undivided network is zero, which
is the best that can be achieved.

Additionally, it could happen that although the leading eigenvalue is positive, $s^TBs$ is
non-positive, i.e. the division represented by s has a worse modularity than a trivial division
into one group.

**Dividing Into Modularity Groups**

Until now we described a division of a network into two groups, however Many networks contain more than two communities, thus we would like to find
good divisions of networks into a larger number of groups. Our approach is to divide each group into two until there is no division of the group.

To divide a group, we cannot use the same method since it must take into consideration
the entire graph, instead we need to look at the additional change ∆Q to the modularity.

Suppose we divide a group g of size $$n_g$$ in two, the change depends on pairs of elements in g.
Prior to the division, the contribution of pairs in g to Q was $$ \sum_{i,j \in g} B_{ij} $$. Let s be a vector of size $$ n_g$$ with +1, -1 elements representing a division of g into two groups, and define $$ \delta_{ij} $$ as:

$$ \delta_{ij}=\begin{cases} 1 & if\;i = j \\ 0 & otherwise \end{cases}$$

It follows that the change in the modularity is:
$$\Delta Q$$ = $$\frac {1} {2}  \sum_{i,j \in g} (A_{ij} - \frac {k_ik_j} {M})(s_is_j + 1) - \sum_{i,j \in g} B_{ij}$$ =
$$\frac {1} {2}\sum_{i,j \in g} B_{ij} (s_is_j + 1) - \sum_{i,j \in g} B_{ij}$$=
$$\frac {1} {2} \sum_{i,j \in g} B_{ij} s_is_j + \frac{1}{2}\sum_{i,j \in g}B_{ij} - \sum_{i,j \in g} B_{ij}$$ =
$$\frac {1} {2} \sum_{i,j \in g} (B_{ij} s_is_j -B_{ij}) $$=
$$\frac {1} {2} \sum_{i,j \in g} (B_{ij} -\delta _{ij} \sum_{k \in g}B_{ik})s_is_j$$

Let $B[g]$ be the symmetric $$n_g$$ x $$n_g$$ sub-matrix of B corresponding to the rows and columns of g. Let $$f_i^g=\sum_{k \in g} B[g]_{ik} $$ .
Let $$\bar B[g]$$ be a symmetric $$n_g$$ x $$n_g$$ matrix with elements:
$$\bar B[g]_{ij} = B[g]_{ij} - \delta _{ij} f_i^g $$
Hence we can write $$\Delta Q$$ as:
$$\Delta Q = \frac{1}{2}s^T\bar B[g]s $$

this equation has the same form as before (for computing the modularity of a network with two sub groups), hence we can apply the same algorithm to maximize $$\Delta Q$$, according to the leading eigenpair of $$\bar B[g] $$

Note that if g is the entire graph then $$ \forall i
: f_i^g = 0 $$ and thus $$\bar B[g] = B$$, allowing us to use this algorithm in all cases.

**Modularity Maximization**

We can further maximize a division of groups into two. Suppose {$$g_1, g_2$$} is an initial division of g into two groups. In order to maximize the change in modularity we want to find a single vertex that when moved to the other group, gives the biggest increase in modularity or the smallest decrease if no increase is possible.
We will repeat this process with the constraint that each vertex may only be moved once, until all vertices have been moved. Once done, from all the states of division into two groups during the operation, find the state that has the maximal modularity, and start again from this state.
We repeat the entire process iteratively until no further improvement is found.

#### Power Iteration

Power iteration is an eigenvalue algorithm to find a dominant eigenpair: given a diagonalizable matrix A, the algorithm will produce a number $\lambda$, which is the greatest in absolute value, eigenvalue of A, and  a non zero vector $v$ which is a corresponding eigenvector of $\lambda$.

The algorithm starts with a random vector in our case - $b_0$. The method is described by the recurrence relation:

$b_{k+1}=\frac{Ab_k}{\parallel{Ab_k}\parallel}$    .

**Matrix Shifting**

Although, since the division into two algorithm requires a leading eigenpair we use matrix shifting.

Let $C$ be a matrix with the eigenvalues {$\lambda_1,...,\lambda_n$}, and let the 1-norm of $C$ be the sum of its largest column: $\parallel C \parallel _1= max_j(\sum_i|C_{ij}|) $ .

Let $C' = \parallel C\parallel _1 \cdot I + C$, then $C'$ has the same eigenvectors as $C$ and the eigenvalues of $C'$ are: {$\lambda _1 + \parallel C\parallel _1,...,\lambda_n + \parallel C\parallel_1$}. Thus the dominant eigenpair of $C'$ is ($\lambda_1 +\parallel C\parallel_1, v_1$), and the leading eigenpair of $C$ is ($\lambda_1, v_1$).