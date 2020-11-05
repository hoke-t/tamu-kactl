/**
 * Author: Simon Lindholm, Tanner Hoke
 * Date: 2019-12-31
 * License: CC0
 * Source: folklore
 * Description: Eulerian undirected/directed path/cycle algorithm.
 * Input should be a vector of (dest, global edge index), where
 * for undirected graphs, forward/backward edges have the same index.
 * Returns a list of nodes in the Eulerian path/cycle with src at both start and end, or
 * empty list if no cycle/path exists. The returned vector is of (node, global edge index to node).
 * The second element of the first pair is always $-1$.
 * Time: O(V + E)
 * Status: stress-tested
 */
#pragma once

vii eulerWalk(vector<vector<pii>>& gr, int nedges, int src=0) {
  int n = sz(gr);
  vi D(n), its(n), eu(nedges);
  vii ret, s = {make_pair(src, -1)};
  D[src]++; // comment this line to disallow Euler paths, only allow cycles
  while (!s.empty()) {
    int x = s.back().fst, y, e, &it = its[x], end = sz(gr[x]);
    if (it == end){ ret.emplace_back(x, s.back().snd); s.pop_back(); continue; }
    tie(y, e) = gr[x][it++];
    if (!eu[e]) {
      D[x]--, D[y]++;
      eu[e] = 1; s.emplace_back(y, e);
    }}
  for (int x : D) if (x < 0 || sz(ret) != nedges+1) return {};
  return {ret.rbegin(), ret.rend()};
}

