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
#define NAME "cutting"
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

const int N = 5e4 + 111;
int par[N], sz[N];

int get(int v) {
	if (par[v] != v) {
		par[v] = get(par[v]);
	}
	return par[v];
}

void join(int v, int u) {
	v = get(v);
	u = get(u);
	if (v == u) {
		return;
	}
	if (sz[v] > sz[u]) {
		par[u] = v;
		sz[v] += sz[u];
	} else {
		par[v] = u;
		sz[u] += sz[v];
	}
}

struct q {
	string t;
	int v, u;
};

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

	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 0; i < n; ++i) {
		par[i] = i;
		sz[i] = 1;
	}
	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
	}
	stack<q> st;
	int cnt = 0;
	for (int i = 0; i < k; ++i) {
		string s;
		int v, u;
		cin >> s >> v >> u;
		v--;
		u--;
		cnt += s == "ask";
		st.push({ s, v, u });
	}
	vector<string> ans(cnt);
	while (!st.empty()) {
		q c = st.top();
		st.pop();
		if (c.t == "ask") {
			if (get(c.u) == get(c.v)) {
				ans[--cnt] = "YES";
			} else {
				ans[--cnt] = "NO";
			}
		} else {
			join(c.u, c.v);
		}
	}
	for (string s : ans) {
		cout << s << "\n";
	}

	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
