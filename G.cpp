#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
/* #pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")*/
typedef long long ll;
const ll MAXN = 1e5 + 4;
const ll MAXK = 1e3 + 5;
const ll MOD = 1e9 + 7;
const ll MODH = 1e9 + 9;
const int MAXLG = 20;
const long double PI = acos(-1);
const ll p = 41;
const long double EPS = 1e-4;
#define x first
#define y second
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
inline ll rand(ll a, ll b) {
  ll c = rng();
  return a + ((ll)abs(c)) % (b - a + 1);
}
ll binpow(ll a, ll b, ll m) {
  a %= m;
  ll res = 1;
  while (b > 0) {
    if (b & 1) {
      res = res * a % m;
    }
    a = a * a % m;
    b >>= 1;
  }
  return res;
}
vector<pair<int, int> > g[MAXN];
int par[MAXN][MAXLG], minpar[MAXN][MAXLG];
int depth[MAXN], out[MAXN], in[MAXN];
int tt = 0, n, comp;
vector<int> gc[MAXN];
int id[MAXN];
int parent[MAXN];
typedef pair<int, pair<int, int> > ppp;
vector<ppp> edges;
void dfs(int u, int p) {
  par[u][0] = p;
  in[u] = (++tt);
  gc[comp].push_back(u);
  id[u] = comp;
  for (auto &k : g[u]) {
    if (k.first == p) continue;
    depth[k.first] = depth[u] + 1;
    minpar[k.first][0] = k.second;
    dfs(k.first, u);
  }
  out[u] = (tt);
}

void preprocess() {
  for (int j = 1; j < MAXLG; j++)
    for (int i = 1; i < MAXN; i++) minpar[i][j] = 1e9;
  for (int i = 1; i <= n; i++) {
    if (depth[i]) continue;
    comp++;
    dfs(i, i);
  }

  for (int i = 1; i <= comp; i++) {
    int MMXLG = ceil(log2((int)gc[comp].size())) + 1;
    for (int j = 1; j < MMXLG; j++)
      for (auto i : gc[comp]) {
        minpar[i][j] = min(minpar[i][j - 1], minpar[par[i][j - 1]][j - 1]);
        par[i][j] = par[par[i][j - 1]][j - 1];
      }
  }
}

bool ansc(int u, int v) { return (in[u] <= in[v] and out[v] <= out[u]); }
int lca(int u, int v) {
  if (u == v) return u;
  if (depth[u] < depth[v]) swap(u, v);

  for (int j = MAXLG - 1; j >= 0; j--)
    if (!ansc(par[u][j], v)) u = par[u][j];

  return par[u][0];
}

int getMin(int u, int v) {
  assert(u != v);
  if (depth[u] < depth[v]) swap(u, v);

  int d = depth[u] - depth[v];
  int ret = 1e9;
  for (int i = 30; i >= 0; i--)
    if ((d >> i) & 1) {
      ret = min(ret, minpar[u][i]);
      u = par[u][i];
    }
  if (u == v) {
    return ret;
  }
  for (int j = MAXLG - 1; j >= 0; j--) {
    if (par[u][j] != par[v][j]) {
      ret = min(ret, minpar[u][j]);
      ret = min(ret, minpar[v][j]);
      u = par[u][j];
      v = par[v][j];
    }
  }

  if (u != v) {
    ret = min(ret, minpar[u][0]);
    ret = min(ret, minpar[v][0]);
  }
  return ret;
}

int getDist(int u, int v) { return depth[u] + depth[v] - 2 * depth[lca(u, v)]; }

int find_set(int v) {
  if (v == parent[v]) return v;
  return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
  a = find_set(a);
  b = find_set(b);
  if (a != b) parent[b] = a;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int m;
  cin >> n >> m;

  for (int i = 1; i <= n; i++) parent[i] = i;
  for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    edges.push_back({w, {u, v}});
  }
  sort(edges.rbegin(), edges.rend());

  for (int i = 0; i < m; i++) {
    int a = edges[i].second.first;
    int b = edges[i].second.second;
    int w = edges[i].first;
    int x = find_set(a);
    int y = find_set(b);
    if (x != y) {
      parent[y] = x;
      g[a].push_back({b, w});
      g[b].push_back({a, w});
    }
  }

  preprocess();
  int q;
  cin >> q;
  while (q--) {
    int u, v;
    cin >> u >> v;
    cout << getMin(u, v) << '\n';
  }
}