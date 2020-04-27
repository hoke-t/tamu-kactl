/**
 * Author: Julia Graham
 * Date: 2018-11-13
 * License: CC0
 * Source: Chen Xing
 * Description: Flow algorithm with complexity $O((V+E) E log V)$. To get edge flow values, compare
 * capacities before and after, and take the positive values only. Runs in 0.4s on $V = 500$, $E = 10000$.
 * Status: Tested on kattis maxflow
 */
#pragma once

typedef ll T; // or whatever
const T INF = 1e18;
typedef vector<unordered_map<int, T>> graph;

T max_flow(graph& g, int s, int t) {
  assert(s != t);
  T flow = 0;
  vi par(sz(g));
  for (;;) {
    fill(all(par), -1);

    int u, v; T inc, cap;
    priority_queue<tuple<T, int, int>> pq; 
    pq.push({INF, s, s});
    while (!pq.empty()) {
      int p; tie(inc, u, p) = pq.top(); pq.pop();
      if (par[u] != -1) continue; par[u] = p;
      if (u == t) break; 
      for (auto e : g[u]) {
        tie(v, cap) = e;
        if (par[v] != -1 or cap == 0) continue;
        pq.push({min(inc, cap), v, u}); 
      } 
      if (par[t] != -1) break; 
    }
    if (par[t] == -1) return flow;

    if (inc == INF) return INF; 
    flow += inc;
    for (int y = t; y != s; y = par[y]) {
      g[par[y]][y] -= inc;
      g[y][par[y]] += inc;
    }
  } 
}
