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
#define NAME "supermarket"
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

struct cash {
	ll a, b, t;
};

inline bool cmp(const ll &mid, const cash &a, const cash &b) {
	if (a.a != 0 && b.a != 0) {
		return b.a * (mid - a.t - a.b) > a.a * (mid - b.b - b.t);
	}
	if (a.a == 0 && b.a == 0) {
		return mid - a.t - a.b < mid - b.t - b.b;
	}
	if (a.a == 0) {
		return 0;
	}
	return 1;
}

vector<cash> merge_sort(const ll &mid, const int &l, const int &r, const vector<cash> &arr) {
	if (l + 1 == r) {
		return{ arr[l] };
	}
	int m = (l + r) / 2;
	vector<cash> res_l = merge_sort(mid, l, m, arr);
	vector<cash> res_r = merge_sort(mid, m, r, arr);
	size_t nl = res_l.size(), nr = res_r.size();
	vector<cash> res(nl + nr);
	for (size_t it = 0, i = 0, j = 0; it < res.size(); ++it) {
		if (i < nl && j < nr) {
			if (cmp(mid, res_l[i], res_r[j])) {
				res[it] = res_l[i++];
			} else {
				res[it] = res_r[j++];
			}
		} else {
			if (i < nl) {
				res[it] = res_l[i++];
			} else {
				res[it] = res_r[j++];
			}
		}
	}
	return res;
}

int m, n;
ll p;
inline bool check(const ll &mid, vector<cash> &cs) {
	ll can = 0;
	for (int i = 0; i < m; ++i) {
		if (mid - cs[i].t - cs[i].b >= 0 && cs[i].a == 0) {
			return 1;
		}
	}
	cs = merge_sort(mid, 0, (int)cs.size(), cs);
	for (int i = 0, cnt = 0; i < m && cnt < n; ++i) {
		if (mid - cs[i].t - cs[i].b >= 0) {
			if (cs[i].a > 0) {
				cnt++;
				can += (mid - cs[i].t - cs[i].b) / cs[i].a;
			}
		}
	}
	return can >= p;
}

int main() {
#if SOLVE
	freopen("input.txt", "r", stdin);
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

	cin >> m;
	vector<cash> cs(m);
	for (int i = 0; i < m; ++i) {
		cin >> cs[i].a >> cs[i].b >> cs[i].t;
	}
	cin >> n >> p;
	ll l = 0, r = (ll)20000000000;
	while (r - l > 1) {
		ll mid = (l + r) / 2;
		if (check(mid, cs)) {
			r = mid;
		} else {
			l = mid;
		}
	}
	if (check(l, cs)) {
		cout << l;
	} else {
		cout << r;
	}

	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
