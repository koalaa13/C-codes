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
#define NAME "isheap"
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

const int N = 1e5 + 22;
const ll p = 1e6 + 3;
int par[N], sz[N], sum[N], cnt;
ll zerg = 0;

int get(int v) {
	cnt += sum[v];
	if (par[v] != v) {
		return get(par[v]);
	}
	return par[v];
}

int get_mess(int v) {
	cnt = 0;
	get(v);
	return cnt;
}

bool join(int v, int u) {
	v = get(v);
	u = get(u);
	if (v == u) {
		return 0;
	}
	if (sz[v] > sz[u]) {
		par[u] = v;
		sz[v] += sz[u];
		sum[u] -= sum[v];
	} else {
		par[v] = u;
		sz[u] += sz[v];
		sum[v] -= sum[u];
	}
	return 1;
}

int main() {
#if SOLVE
	freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
#else
	// freopen(NAME".in", "r", stdin);
	// freopen(NAME".out", "w", stdout);
#endif

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	// srand(time(NULL));
	// cout.precision(20);
	// cout.setf(ios::fixed);

	int n, m;
	cin >> n >> m;
	vector<int> readed(n);
	for (int i = 0; i < n; ++i) {
		par[i] = i;
		sz[i] = 1;
		sum[i] = 0;
	}
	for (int i = 0; i < m; ++i) {
		int type;
		cin >> type;
		if (type == 1) {
			int a;
			cin >> a;
			a = (int)((a + zerg) % n);
			sum[get(a)]++;
			zerg = (30ll * zerg + 239ll) % p;
		}
		if (type == 2) {
			int a, b;
			cin >> a >> b;
			a = (int)((a + zerg) % n);
			b = (int)((b + zerg) % n);
			if (join(a, b)) {
				zerg = (13ll * zerg + 11ll) % p;
			}
		}
		if (type == 3) {
			int a;
			cin >> a;
			a = (int)((a + zerg) % n);
			int ans = get_mess(a);
			cout << ans - readed[a] << "\n";
			zerg = (100500ll * zerg + (ll)(ans - readed[a])) % p;
			readed[a] = ans;
		}
	}

	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
