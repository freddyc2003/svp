#import "template.typ": *
#show: ams-article.with(
  title: [Implementing and Optimizing the Shortest Vector Problem],
  authors: (
    (
      name: "Freddy Cunningham",
      department: [Department of Computer Science],
      organization: [Durham University],
      email: "freddy.t.cunningham@durham.ac.uk"
    ),
  ),
  // abstract: lorem(100),
  bibliography-file: "refs.bib",
)

// Call me Ishmael. Some years ago --- never mind how long precisely ---
// having little or no money in my purse, and nothing particular to
// interest me on shore, I thought I would sail about a little and see
// the watery part of the world. It is a way I have of driving off the
// spleen, and regulating the circulation.  Whenever I find myself
// growing grim about the mouth; whenever it is a damp, drizzly November
// in my soul; whenever I find myself involuntarily pausing before coffin
// warehouses, and bringing up the rear of every funeral I meet; and
// especially whenever my hypos get such an upper hand of me, that it
// requires a strong moral principle to prevent me from deliberately
// stepping into the street, and methodically knocking people's hats off
// --- then, I account it high time to get to sea as soon as I can. This
// is my substitute for pistol and ball. With a philosophical flourish
// Cato throws himself upon his sword; I quietly take to the ship. There
// is nothing surprising in this. If they but knew it, almost all men in
// their degree, some time or other, cherish very nearly the same
// feelings towards the ocean with me. @netwok2020

// There now is your insular city of the Manhattoes, belted round by
// wharves as Indian isles by coral reefs - commerce surrounds it with
// her surf. Right and left, the streets take you waterward. Its extreme
// down-town is the battery, where that noble mole is washed by waves,
// and cooled by breezes, which a few hours previous were out of sight of
// land. Look at the crowds of water-gazers there.

// Anyone caught using formulas such as $sqrt(x+y)=sqrt(x)+sqrt(y)$
// or $1/(x+y) = 1/x + 1/y$ will fail.

// The binomial theorem is
// $ (x+y)^n=sum_(k=0)^n binom(n, k) x^k y^(n-k). $

// A favorite sum of most mathematicians is
// $ sum_(n=1)^oo 1/n^2 = pi^2 / 6. $

// Likewise a popular integral is
// $ integral_(-oo)^oo e^(-x^2) dif x = sqrt(pi) $

// #theorem[
//   The square of any real number is non-negative.
// ]

// #proof[
//   Any real number $x$ satisfies $x > 0$, $x = 0$, or $x < 0$. If $x = 0$,
//   then $x^2 = 0 >= 0$. If $x > 0$ then as a positive time a positive is
//   positive we have $x^2 = x x > 0$. If $x < 0$ then $−x > 0$ and so by
//   what we have just done $x^2 = (−x)^2 > 0$. So in all cases $x^2 ≥ 0$.
// ]

// = Introduction
// This is a new section.
// You can use tables like @solids.

// #figure(
//   table(
//     columns: (1fr, auto, auto),
//     inset: 5pt,
//     align: horizon,
//     [], [*Area*], [*Parameters*],
//     [*Cylinder*],
//     $ pi h (D^2 - d^2) / 4 $,
//     [$h$: height \
//      $D$: outer radius \
//      $d$: inner radius],
//     [*Tetrahedron*],
//     $ sqrt(2) / 12 a^3 $,
//     [$a$: edge length]
//   ),
//   caption: "Solids",
// ) <solids>

= Approach
I chose to use a brute-force approach to solve the shortest vector problem (SVP) as it provides an exact solution and is reasonably simple to implement. The algorithm I implemented was the Schnorr-Euchner Enumeration @Yasuda:2020, which uses polynomial-space which is less memory than the other main approach sieving which is an exponential-space algorithm. However, enumeration has a super-exponential run-time @Gama:2010 but is a natural choice as in practice it typically has good performance on low dimensions.

The run-time of enumeration algorithms is greatly affected by the quality of the input basis. A better basis is shorter and more orthogonal @Kumar:2019. I, therefore, chose to implement the LLL reduction algorithm @Plantard_Susilo_Zhang_2013 to preprocess the lattice basis before running the enumeration algorithm.

I also make use of the Gaussian Heuristic @Yasuda:2020 to obtain an upper bound for the length of the shortest vector in the lattice. This is used to define the search space for the enumeration algorithm.

= Implementation
The primary issue I experienced whilst implementing my solution was working with floating-point values. I chose to implement the classical Gram-Schmidt orthogonalisation (GSO) with floating-point arithmetic (fpa). This is known to be numerically unstable and in the worst case when applied within the LLL algorithm the lattice basis will not necessarily be reduced at all because of inaccuracies in the GSO coefficients @Nguên_Stehlé_2005. I experienced these problems with my implementation on a number of different types of tests.

In practise a floating-point variant of the LLL algorithm, $L^2$ is usually implemented which is proven to output a reduced basis in polynomial time. However, I was unable to successfully implement this algorithm.

= Run-time
To test the run-time of my implementation I generated uniform and knapsack like matrices of dimension $1 times 1$ to $20 times 20$ containing numbers of size 8, 16 and 32 bits using the fplll library.

To measure the run-time of my implementation I used hyperfine a command-line benchmarking tool.

The tests were performed on a virtual machine with 4 cores and 8 GB RAM running an Ubuntu Linux image.

= Memory
To test the amount of memory my implementation used I measured the total bytes used throughout the entire execution of the program as well as the maximum number of bytes used at any point during the programs execution.

This test was repeated for lattices of dimensions 2, 5, 10 and 20 and the results are shown in Table x.

= Accuracy
To determine the accuracy of my implementation I compared my solution to the solution generated by the fplll library. Given the fplll module uses superior algorithms to deal with floating-point errors, for certain lattices my solution will be less accurate than that produced by fplll. Therefore, I decided to allow a small tolerance level of $0.00001$ that my solution must be within in order to pass.

I ran my implementation on the same tests used to measure run-time and recorded the absolute differece between my solution and that generated by fplll and whether it passed given my specified tolerance.

// = Background
// #lorem(40)
