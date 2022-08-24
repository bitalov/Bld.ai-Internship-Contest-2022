#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
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
  return a + ((ll)abs(c)) % (b - a + 1);
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
// typedef tree<ll, null_type, less_equal<ll>, rb_tree_tag,  //less_equal
//           tree_order_statistics_node_update> oset;
const int MAXN = 1e6 + 5;

typedef long double ld;

ll pw[MAXN];

void preprocess() {
  for (ll i = 0; i < 64; i++) {
    pw[i] = (1LL << i);
  }
}

ll node_val(ll h, ll l, ll i) {
  ll ret = pw[(h - l)] * (2 * i - 1);
  return ret;
}
ll L, I;
ll h;
pair<ll, ll> get(ll X) {
  pair<ll, ll> ret;
  ret = {0, 0};
  for (ll l = 1; l <= h; ++l) {
    ll tmp_I = (X / (pw[(h - l)])) + 1;
    tmp_I /= 2LL;
    ll val = node_val(h, l, tmp_I);

    if (tmp_I and val == X) {
      I = tmp_I;
      L = l;
      ret = {L, tmp_I};
      break;
    }
  }

  return ret;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  preprocess();
  int q;
  cin >> q;

  while (q--) {
    ll a, b;
    cin >> h >> a >> b;

    pair<ll, ll> Y = get(b);
    pair<ll, ll> X = get(a);

    ll root = node_val(h, 1, 1);
    map<ll, ll> vis;
    ll curr = a;
    vis[curr] = 1;
    while (curr != root) {
      pair<ll, ll> info = get(curr);
      ll idx = info.second;
      ll lvl = info.first;
      if (idx & 1) {
        curr += pw[h - lvl];
      } else
        curr -= pw[h - lvl];

      vis[curr] = 1;
    }
    curr = b;
    ll ans = root;
    while (curr != root) {
      pair<ll, ll> info = get(curr);
      ll idx = info.second;
      ll lvl = info.first;
      if (vis[curr]) {
        ans = curr;
        break;
      }
      if (idx & 1) {
        curr += pw[h - lvl];
      } else
        curr -= pw[h - lvl];
    }

    cout << ans << '\n';
  }
}