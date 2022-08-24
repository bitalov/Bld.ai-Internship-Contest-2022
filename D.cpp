#include <bits/stdc++.h>
 //#include <ext/pb_ds/assoc_container.hpp>
//using namespace __gnu_pbds;
using namespace std;
/* #pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")*/
typedef long long ll;
const ll MAXK = 3e3 + 5;
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
  return a + ((ll) abs(c)) % (b - a + 1);
}
ll binpowmod(ll a, ll b, ll m) {
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
//typedef tree<ll, null_type, less_equal<ll>, rb_tree_tag,  //less_equal
//           tree_order_statistics_node_update> oset;
const int MAXN = 1e6 + 5;

vector < vector < int >> g, r, h;
vector < int > seen, t, color;
int n, m;

void dfs(int cur) {
  seen[cur]++;
  for (auto v: g[cur]) {
    if (!seen[v]) dfs(v);
  }
  t.push_back(cur);
}

void dfs2(int cur, int c) {
  color[cur] = c;
  h[c].push_back(cur);
  for (auto v: r[cur]) {
    if (color[v] == -1) dfs2(v, c);
  }
}

int neg(char c, int x) {
  if (c == '+') return x + m;
  return x;
}

int id(char c, int x) {
  if (c == '-') return x + m;
  return x;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> m;
  g.resize(2 * m + 1);
  r.resize(2 * m + 1);
  h.resize(2 * m + 1);
  seen.assign(2 * m + 1, 0);
  color.assign(2 * m + 1, -1);
  while (n--) {
    char sa, sb;
    int a, b;
    cin >> a >> b;
    if (a > 0)
      sa = '+';
    else
      sa = '-';
    if (b > 0)
      sb = '+';
    else
      sb = '-';

    a = abs(a);
    b = abs(b);
    g[neg(sa, a)].push_back(id(sb, b));
    r[id(sb, b)].push_back(neg(sa, a));
    g[neg(sb, b)].push_back(id(sa, a));
    r[id(sa, a)].push_back(neg(sb, b));
  }
  for (int i = 1; i <= 2 * m; i++) {
    if (!seen[i]) dfs(i);
  }
  int c = 0;
  vector < int > ans(2 * m + 1, 1);
  for (int i = t.size() - 1; i >= 0; i--) {
    if (color[t[i]] == -1) dfs2(t[i], c++);
    if (color[t[i]] == color[t[i] > m ? t[i] - m : t[i] + m]) {
      cout << "-1";
      return 0;
    }
  }
  for (int i = c - 1; i >= 0; i--) {
    int truth = 1;
    for (const auto & v: h[i]) {
      truth &= ans[v];
    }
    for (const auto & v: h[i]) {
      ans[v] = truth;
      ans[v > m ? v - m : v + m] = 1 - truth;
    }
  }
  for (int i = 1; i <= m; i++) {
    cout << (ans[i]) << ' ';
  }
  return 0;

}