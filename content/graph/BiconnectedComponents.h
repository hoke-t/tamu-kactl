/**
 * Author: MIT
 * Description: Biconnected components, removing any vertex in component 
 * doesn't disconnect it. To get block-cut tree, create a bipartite graph
 * with the original vertices on the left and a vertex for each BCC on the right. 
 * Draw edge $u\leftrightarrow v$ if $u$ is contained within the BCC for $v.$
 * Time: O(N+M)
 * Source: GeeksForGeeks (corrected)
 */

struct BCC {
  vector<vii> adj;
  vii ed;
  vi disc;
  void ae(int u, int v) { 
    adj[u].pb(make_pair(v,sz(ed))), adj[v].pb(make_pair(u,sz(ed))), ed.pb(make_pair(u,v)); }
  int N;
  vi st; vector<vi> bccs; // edges for each bcc
  int bcc(int u, int p = -1) { // return lowest disc
    static int ti = 0; int low = disc[u] = ++ti, child = 0;
    trav(i,adj[u]) if (i.snd != p) {
      if (!disc[i.fst]) {
        child ++; st.pb(i.snd);
        int LOW = bcc(i.fst,i.snd); low = min(low, LOW);
        // if (disc[u] < LOW) -> bridge
        if (disc[u] <= LOW) { // get edges in bcc
          // if (p != -1 || child > 1) -> u is articulation pt
          bccs.emplace_back(); vi& tmp = bccs.back(); // new bcc
          for (bool done = 0; !done; tmp.pb(st.back()),
              st.pop_back()) done |= st.back() == i.snd;
        }
      } else if (disc[i.fst] < disc[u]) {
        low = min(low, (int)disc[i.fst]);
        st.pb(i.snd);
      }
    }
    return low;
  }
  void init(int _N) {
    N = _N; rep(i,0,N) disc[i] = 0;
    adj.resize(N);
    disc.resize(N);
    rep(i,0,N) if (!disc[i]) bcc(i); 
    /// st should be empty after each iteration
  }
};
