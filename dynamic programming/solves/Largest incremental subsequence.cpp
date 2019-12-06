#include <iostream>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <set>
#include <map>
#include <bitset>
#include <string>
#include <queue>
#include <algorithm>
#include <stack>
#include <ctime>
#include <cassert>
#include <complex>
#include <stdlib.h>
#include <limits>
// #pragma comment(linker, "/STACK:256000000")
using namespace std;

#define mp make_pair
#define NAME "lis"
/* #define FAST_ALLOCATOR_MEMORY 2e8
#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#ifdef FAST_ALLOCATOR_MEMORY
int allocator_pos = 0;
char allocator_memory[(int)FAST_ALLOCATOR_MEMORY];
inline void* operator new(size_t n) {
char* res = allocator_memory + allocator_pos;
allocator_pos += n;
assert(allocator_pos <= (int)FAST_ALLOCATOR_MEMORY);
return (void*)res;
}
inline void operator delete(void*)noexcept {}
// inline void * operator new [] ( size_t ) { assert(0); }
// inline void operator delete [] ( void * ) { assert(0); }
#endif */

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

const int INF = 2e9;

int main() {
#if SOLVE
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
#else
	freopen(NAME".in", "r", stdin);
	freopen(NAME".out", "w", stdout);
#endif

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	// srand(time(NULL));
	// cout.precision(20);
	// cout.setf(ios::fixed);

	int n, len = 0;
	cin >> n;
	vector<int> arr(n), dp(n + 22, INF), par(n, -1), pos(n + 22, -1);
	for (int i = 0; i < n; ++i) {
		cin >> arr[i];
	}
	dp[0] = -INF;
	for (int i = 0; i < n; ++i) {
		int j = (int)(upper_bound(dp.begin(), dp.end(), arr[i]) - dp.begin());
		if (dp[j - 1] < arr[i] && arr[i] < dp[j]) {
			dp[j] = arr[i];
			pos[j] = i;
			par[i] = pos[j - 1];
			len = max(len, j);
		}
	}
	cout << len << "\n";
	vector<int> ans;
	int p = pos[len];
	while (p != -1) {
		ans.push_back(arr[p]);
		p = par[p];
	}
	reverse(ans.begin(), ans.end());
	for (int i : ans) {
		cout << i << " ";
	}

	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
