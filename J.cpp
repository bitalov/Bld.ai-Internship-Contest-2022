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
const int MAXN = 20 + 2;

typedef long double ld;
ll mem[22][(1 << (21)) + 5];
bool a[25][25];
int n;
ll solve(int i, int mask) {
  if (i == n) {
    return (mask == (1 << n) - 1);
  }

  ll &ret = mem[i][mask];
  if (ret != -1) return ret;
  ret = 0;

  for (int w = 0; w < n; w++) {
    int bit = (mask >> w) & 1;

    if (!bit and a[i][w]) {
      ret += solve(i + 1, mask | (1 << w));
      ret %= MOD;
    }
  }

  return ret;
}

int main() {
  cin >> n;

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) cin >> a[i][j];

  memset(mem, -1, sizeof(mem));

  cout << solve(0, 0);
}