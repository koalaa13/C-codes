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
#define NAME "meetings"
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

struct meet {
	int a, b, c;
};

int count(int n) {
	int res = 0;
	while (n > 0) {
		if (n % 2 == 1) {
			res++;
		}
		n /= 2;
	}
	return res;
}

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

	int n, k;
	cin >> n >> k;
	vector<meet> ms(n);
	for (int i = 0; i < n; ++i) {
		cin >> ms[i].a >> ms[i].b >> ms[i].c;
	}
	int nn = (1 << n);
	vector<set<pair<int, int>>> dp(nn);
	dp[0].insert({ k, -1 });
	for (int mask = 0; mask < nn; ++mask) {
		for (int i = 0; i < n; ++i) {
			if ((mask & (1 << i)) == 0) {
				int new_mask = mask | (1 << i);
				for (pair<int, int> j : dp[mask]) {
					if (j.first >= ms[i].a && j.first <= ms[i].b) {
						dp[new_mask].insert({ j.first + ms[i].c, mask });
					}
				}
			}
		}
	}
	vector<int> ans;
	int mask = 0, cnt_ans = 0;
	for (int i = nn - 1; i >= 0; --i) {
		int cnt = count(i);
		if (!dp[i].empty() && cnt_ans < cnt) {
			cnt_ans = cnt;
			mask = i;
		}
	}
	while (1) {
		pair<int, int> par = *dp[mask].begin();
		if (par.second == -1) {
			break;
		}
		int find = mask ^ par.second;
		int m = 0;
		while (find > 0) {
			m++;
			find /= 2;
		}
		ans.push_back(m);
		mask = par.second;
	}
	cout << ans.size() << "\n";
	reverse(ans.begin(), ans.end());
	for (int i : ans) {
		cout << i << " ";
	}

	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
