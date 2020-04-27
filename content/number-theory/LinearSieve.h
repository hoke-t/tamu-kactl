/**
 * Author: Julia Graham
 * Date: 11-15-2018
 * License: CC0
 * Source: https://cp-algorithms.com/algebra/prime-sieve-linear.html
 * Description: Linear-time factorization sieve. $lp[x]$ is the smallest prime factor of $x$. For prime $x$, $lp[x] = x$. 
 * Status: Tested
 * Time: $O(n)$
 */
#pragma once

const int MAX_PR = 5000000;
int lp[MAX_PR + 1] = {0};
vi factorSieve() {
  vi pr;
  rep(i, 2, MAX_PR + 1) {
    if (lp[i] == 0) pr.pb(lp[i] = i);
    for (auto p : pr) {
      if (lp[i] < p or i*p > MAX_PR) break;
      lp[i*p] = p;
    }
  }
  return pr;
}
