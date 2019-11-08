/**
 * Author: Julia Graham
 * Date: 11-15-2018
 * License: CC0
 * Source: me. using heuristic by user Noobgam on codeforces
 * Status: untested
 * Description: Structure for offline sqrt-decomposition of range queries. Currently tooled for distinct elements in a range, but can easily be modified to work on any static range query problem
 * Usage: Add queries in the form $[L, R)$ using add_query(). After all queries are added, call process().
 * Time: $O((N + Q) \sqrt N)$ worst-case, faster in practice
 */

#pragma once

struct query { int l, r, id, blk; };

template<class T>
struct Mo {
  vector<T> a;
  vector<query> qs;
  const int BLOCK_SIZE = sqrt(100'000);

  void add_query(int l, int r) { // [l, r)
    qs.pb({l, r, sz(qs), l/BLOCK_SIZE});
  }

  vector<T> answers() {
    vector<T> ans(sz(qs));
    sort(all(qs), [](query a, query b) {
      if (a.blk != b.blk) return a.l < b.l;
      return a.blk&1 ? (a.r < b.r) : (b.r < a.r);
    });

    int L = 0, R = 0;
    trav(q, qs) {
      while (L < q.l) del(L++); 
      while (L > q.l) add(--L); 
      while (R < q.r) add(R++); 
      while (R > q.r) del(--R); 
      ans[q.id] = calc();
    }
    return ans;
  }
  // CHange stuff starting here:
  unordered_map<T, int> ct; int tot; 
  Mo(vector<T> a) : a(a) {
    /* TODO: initialize metadata */
    tot = 0;
  };

  void add(int k) {
    /* TODO: update metadata for adding a[k] */
    if (++ct[a[k]] == 1) ++tot;
  }
  void del(int k) { 
    /* TODO: update metadata for removing a[k] */ 
    if (--ct[a[k]] == 0) --tot;
  }
  T calc() {
    /* TODO: use metadata to get current query */
    return tot;
  }
};
