/**
 * Author: Tanner Hoke
 * Date: 2019-07-19
 * License: CC0
 * Source: https://en.wikipedia.org/wiki/Discrete_logarithm and https://cp-algorithms.com/algebra/discrete-log.html
 * Description: Solves the equation $a^x \equiv b \pmod{mod}$ for $x$ given that $\gcd(a, mod) = 1$.
 * Could be made 3x faster by swapping unordered\_map for HashTable.h
 * Time: $O(\sqrt{mod})$
 * Status: Tested with https://codeforces.com/contest/1106/problem/F
 */
#pragma once

#include "ModPow.h"

ll dlog(ll a, ll b) {
  ll sq = 1+(ll)sqrt(mod), A = modpow(a, sq), e = 1;
  unordered_map<ll, ll> m;

  rep(p, 0, 1+sq) {
    m[e] = p;
    e = e * A % mod;
  }

  e = 1;
  rep(q, 0, sq) {
    ll r = e * b % mod;
    if (m.count(r)) {
      return (mod - q + m[r] * sq) % mod;
    }
    e = e * a % mod;
  }

  return -1;
}
