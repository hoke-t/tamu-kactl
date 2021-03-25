/**
 * Author: Tanner Hoke
 * Date: 2020-03-22
 * License: CC0
 * Source: inspired by https://sharmaeklavya2.github.io/blog/generalizing-segment-trees.html and https://github.com/bqi343/USACO/blob/master/Implementations/content/data-structures/1D%20Range%20Queries%20(9.2)/LazySegAlt.h
 * Description: Generic lazy segment tree. Modify D and M, add helper functions as needed.
 * Time: O(\log N).
 * Status: tested on https://cses.fi/problemset/task/1735/ and https://open.kattis.com/problems/fantasticproblem
 */
#pragma once

struct D { // default to id
  int f = 1;
  ll inc = 0;
  D() {}
  D(int f, ll inc) : f(f), inc(inc) {}
  D& operator*=(const D& a) { // compose
    ckmin(f, a.f);
    inc = a.f * inc + a.inc;
    return *this;
  }
};
struct M { // monoid
  ll len = 1, sum = 0; // default to e
  M() {}
  M(ll sum) : len(1), sum(sum) {}
  M(ll len, ll sum) : len(len), sum(sum) {}
  friend M operator+(const M& a, const M& b) { // combine nodes
    M res(a.len + b.len, a.sum + b.sum);
    return res;
  }
  M& operator*=(const D& a) {
    sum = a.f * sum + a.inc * len;
    return *this;
  }
};
struct LazySeg {
  int n;
  vector<M> val;
  vector<D> lazy;
  LazySeg(vi& v) : n(sz(v)), val(4*sz(v)), lazy(4*sz(v)) {
    build(v, 0, n, 1); 
  }
  void build(vi &v, int tl, int tr, int id) {
    if (tl + 1 < tr) {
      int tm = (tl + tr) / 2;
      build(v, tl, tm, id * 2); build(v, tm, tr, id * 2 + 1);
      pull(id);
    } else val[id] = M(v[tl]);
  }
  M query(int l, int r, int tl, int tr, int id) {
    push(tl, tr, id);
    if (r <= tl || l >= tr) return M();
    if (l <= tl && r >= tr) return val[id];
    int tm = (tl + tr) / 2;
    return query(l, r, tl, tm, id*2) + query(l, r, tm, tr, id*2 + 1);
  }
  void upd(int l, int r, D x, int tl, int tr, int id) {
    push(tl, tr, id);
    if (r <= tl || l >= tr) return;
    if (l <= tl && r >= tr) {
      lazy[id] *= x;
      push(tl, tr, id);
      return;
    }
    int tm = (tl + tr) / 2;
    upd(l, r, x, tl, tm, id*2); upd(l, r, x, tm, tr, id*2 + 1);
    pull(id);
  }
  void push(int tl, int tr, int id) {
    val[id] *= lazy[id];
    if (tl + 1 < tr) 
      rep(j,0,2) lazy[id*2 + j] *= lazy[id];
    lazy[id] = D();
  }
  void pull(int id) {
    val[id] = val[id*2] + val[id*2+1];
  }
  // helper functions
  ll sum(int l, int r) { return query(l, r, 0, n, 1).sum; }
  void repl(int l, int r, int x) { upd(l, r, D(0, x), 0, n, 1); }
  void add(int l, int r, int x) { upd(l, r, D(1, x), 0, n, 1); }
};
