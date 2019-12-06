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
#define NAME "rmq"
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

const int N = 3e5 + 228;
const int INF = 2147483647;
struct ev {
	int type, l, x, ind_ask;
};
vector<pair<int, int>> asks;
vector<ev> evs;

bool cmp(const ev &a, const ev &b) {
	if (a.l != b.l) {
		return a.l < b.l;
	}
	return a.type < b.type;
}

struct heap {
	pair<int, int> arr[N];
	int sz = 1;
	void super_swap(const int &a, const int &b) {
		swap(arr[a], arr[b]);
		swap(asks[arr[a].second].second, asks[arr[b].second].second);
	}
	bool is_empty() {
		return sz == 1;
	}
	void sift_up(const int &ind) {
		for (int i = ind; i > 1;) {
			int par = i >> 1;
			if (arr[par] < arr[i]) {
				super_swap(par, i);
				i = par;
			} else {
				break;
			}
		}
	}
	int get_max() {
		if (is_empty()) {
			return 228;
		}
		return arr[1].first;
	}
	void push(const int &x, const int &ind_ask) {
		arr[sz] = { x, ind_ask };
		asks[ind_ask].first = x;
		asks[ind_ask].second = sz;
		sift_up(sz++);
	}
	void sift_down(const int &ind) {
		for (int i = ind;;) {
			int l = 2 * i, r = l + 1, next = l;
			if (r < sz && arr[r] > arr[l]) {
				next = r;
			}
			if (next < sz && arr[i] < arr[next]) {
				super_swap(i, next);
				i = next;
			} else {
				break;
			}
		}
	}
	void erase(const int &ind_ask) {
		int ind_in_heap = asks[ind_ask].second;
		super_swap(ind_in_heap, --sz);
		sift_down(ind_in_heap);
		sift_up(ind_in_heap);
	}
};

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

	int n, m, j = 0;
	cin >> n >> m;
	heap h;
	for (int i = 0; i < m; ++i) {
		int l, r, x;
		cin >> l >> r >> x;
		evs.push_back({ 0, l - 1, x, i });
		evs.push_back({ 1, r - 1, x, i });
		asks.push_back({ x, -1 });
	}
	sort(evs.begin(), evs.end(), cmp);
	for (int i = 0; i < n; ++i) {
		int was = j;
		while (j < (int)evs.size() && evs[j].l <= i) {
			if (evs[j].type == 0) {
				h.push(evs[j].x, evs[j].ind_ask);
			}
			++j;
		}
		cout << h.get_max() << " ";
		for (; was < j; ++was) {
			if (evs[was].type == 1) {
				h.erase(evs[was].ind_ask);
			}
		}
	}

	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
