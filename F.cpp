#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
// function to find the longest subarray
// with sum divisible by k
const int MAXN = 1e5 + 5;
int arr[MAXN];

int longestSubarrWthSumDivByK(int n, int k) {

  map < ll, int > um;

  ll max_len = 0;
  ll curr_sum = 0;

  for (int i = 0; i < n; i++) {
    curr_sum += arr[i];

    int mod = ((curr_sum % k) + k) % k;

    if (mod == 0)
      max_len = i + 1;

    else if (um.find(mod) == um.end())
      um[mod] = i;

    else
    if (max_len < (i - um[mod]))
      max_len = i - um[mod];
  }

  return max_len;
}

// Driver code
int main() {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; i++)
    cin >> arr[i];

  cout << longestSubarrWthSumDivByK(n, k);

  return 0;
}