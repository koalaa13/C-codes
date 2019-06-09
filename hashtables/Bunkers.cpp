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
#include <list>
#include <unordered_map>
// #pragma comment(linker, "/STACK:256000000")
using namespace std;

#define F first
#define S second
#define mp make_pair
#define NAME "map"
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

const int N = 1e5 + 11;
ll p1, mod1, p2, mod2;
vector<ll> mods = { 778523, 779879, 779927, 889481, 891487, 891679 };
vector<ll> ps = { 556799, 558209, 667673, 666667, 445187, 447179 };

vector<vector<int>> g(N);
int subtree[N];
void dfs(int v, int par = -1) {
	for (int to : g[v]) {
		if (to != par) {
			dfs(to, v);
		}
	}
	subtree[v] = 1;
	for (int to : g[v]) {
		if (to != par) {
			subtree[v] += subtree[to];
		}
	}
}

ll get_hash(const vector<ll> &arr, const ll &p, const ll &mod) {
	if (arr.empty()) {
		return 1;
	}
	ll hash = 0, pp = 1;
	for (size_t i = 0; i < arr.size(); ++i, pp = (pp * p) % mod) {
		hash = (hash + (arr[i] * pp) % mod) % mod;
	}
	return hash;
}

pair<ll, ll> get_hash(int v, int par) {
	vector<ll> hashes1, hashes2;
	for (int to : g[v]) {
		if (to != par) {
			pair<ll, ll> res = get_hash(to, v);
			hashes1.push_back(res.first);
			hashes2.push_back(res.second);
		}
	}
	sort(hashes1.begin(), hashes1.end());
	sort(hashes2.begin(), hashes2.end());
	return{ get_hash(hashes1, p1, mod1), get_hash(hashes2, p2, mod2) };
}

int rnd(int n) {
	return rand() % n;
}

pair<int, int> get2(int n) {
	int i = rnd(n), j = rnd(n);
	if (i == j) {
		j = (j + 1) % n;
	}
	return{ i, j };
}

int main() {
#if SOLVE
	// freopen("input.txt", "r", stdin);
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

	pair<int, int> inds = get2(6);
	p1 = ps[inds.first];
	p2 = ps[inds.second];
	inds = get2(6);
	mod1 = mods[inds.first];
	mod2 = mods[inds.second];
	int n;
	cin >> n;
	for (int i = 0; i < n - 1; ++i) {
		int v, u;
		cin >> v >> u;
		v--;
		u--;
		g[v].push_back(u);
		g[u].push_back(v);
	}
	dfs(0);
	vector<int> starts;
	if (g[0].size() == 2 && subtree[g[0][0]] == subtree[g[0][1]]) {
		starts.push_back(0);
	}
	for (int i = 1; i < n; ++i) {
		if (g[i].size() == 2 && n - subtree[i] == subtree[i] - 1) {
			starts.push_back(i);
		}
	}
	if (starts.empty()) {
		cout << "NO";
		return 0;
	}
	for (int v : starts) {
		pair<ll, ll> hash1 = get_hash(g[v][0], v), hash2 = get_hash(g[v][1], v);
		if (hash1 == hash2) {
			cout << "YES";
			return 0;
		}
	}
	cout << "NO";

	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
