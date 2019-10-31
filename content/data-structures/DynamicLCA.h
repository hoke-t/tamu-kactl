/**
 * Author: Julia Graham
 * Date: 2019-08-03
 * License: CC0
 * Source: Myself
 * Status: Tested on Stogovi
 * Description: A tree structure that allows for adding leaves
 * and dynamically computing the LCA in between.
 * Usage:
 *  DynLCA lca; 
 *  lca.add(0); lca.add(1); lca.add(1);
 *  lca.lca(2, 3); // is 1
 * Time: $O(\log N)$ add and query
 */

#pragma once

struct DynLCA {
  vector<vi> anc;
  vi depth;
  int log_n;

  DynLCA(int log_n = 25) : anc(1), depth(1), log_n(log_n) {
    anc[0] = vi(log_n, -1);
  }

  size_t size() { return anc.size(); }
  
  void add(int par) {
    depth.pb(depth[par] + 1);
    vi a(log_n, -1);
    a[0] = par;
    for (int k = 1; k < log_n; ++k) {
      a[k] = anc[a[k-1]][k-1];
      if (a[k] == -1) break;
    }
    anc.pb(a);
  }

  int lca(int a, int b) {
    if (a == 0 or b == 0) return 0;
    if (depth[a] < depth[b]) swap(a, b);
    for (int k = log_n - 1; k >= 0; --k) {
      if (depth[a] == depth[b]) break; 
      if (depth[a] - (1<<k) >= depth[b]) 
        a = anc[a][k];
    }
    for (int k = log_n - 1; k >= 0; --k) {
      if (anc[a][k] != anc[b][k]) {
        a = anc[a][k];
        b = anc[b][k];
      }
    }
    return (a == b) ? a : anc[a][0];
  }
};
