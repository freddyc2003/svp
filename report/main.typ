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
I chose to use the Schnorr–Euchner Enumeration algorithm @Yasuda:2020 for my approach to solve the SVP problem as it provides an exact solution and is reasonably simple to implement. Enumeration is a polynomial-space algorithm using less memory than the other main approach sieving which is an exponential-space algorithm. However, enumeration has super-exponential run-time @Gama:2010 whereas sieving has single exponential run-time @Ajtai:2001. For this coursework our implementation will only be evaluated on inputs up to 10 dimensions so enumeration is a natural choice as in practise it typically has good performance on low dimensions.

The run-time of enumeration algorithms is greatly affected by the quality of the input basis. A better basis is shorter and more orthogonal @Kumar:2019. I therefore chose to implement the LLL basis reduction algorithm to preprocess the input basis before running the enumeration algorithm. I use the norm of the first vector in the reduced basis as the bound for the search space used by the enumeration algorithm.

= Implementation
I chose to implement my final solution in C. The primary components of the program are the Gram Schmidt, LLL and Enumeration functions. The Gram Schmidt algorithm is implemented using floating-point arithmetic but initally I considered implementing the algorithm using exact arithmetic, storing the values as fractions to remove the floating point errors. However, I decided against this decision as the lost precision due to using floating-point arithmetic was negligble in comparson to the increase in run-time.

All numerical values were stored as doubles as we are required to be able to handle at least 32-bit floating point precision as per the coursework. All vectors were stored as C arrays and matrices as 2D C arrays.

The classical Gram-Schmidt algorithm I implemented is numerically unstable which means errors are introduced to the orthogonalised vectors and Gram-Schmidt coefficients due to the finite-precision of float-point arithmetic. These errors are particularly prevalent when the vectors are almost colinear

= Run-time
To test my implementation I generated uniform and knapsack like matrices of dimension $1 times 1$ to $40 times 40$ containing numbers of size 8, 16 and 32 bits.

To record the run-time I used hyperfine a command-line benchmarking tool.

The tests were performed on a virtual machine with 4 cores and 32 GB RAM running an Ubuntu Linux image.

= Memory

= Accuracy
To determine the accuracy of my implementation I compared my solution to the solution generated by the fpylll library. Given that I am working with floating-point arithmetic it is likely that I encounter small differences between the my solution and the reference solution. Therefore, I decided to allow a small tolerance level of $0.00001$ that my solution must be within to pass.

// = Background
// #lorem(40)
