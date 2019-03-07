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
#define NAME "priorityqueue2"
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

vector<pair<int, int>> qs;
vector<bool> deleted;

struct heap {
	vector<pair<int, int>> arr;
	int sz;
	void super_swap(const int &a, const int &b) {
		swap(qs[arr[a].second].second, qs[arr[b].second].second);
		swap(arr[a], arr[b]);
	}
	heap() {
		arr.resize(1);
		sz = 1;
	}
	bool is_empty() {
		return sz == 1;
	}
	void sift_up(const int &ind) {
		for (int i = ind; i > 1;) {
			int par = i >> 1;
			if (arr[par] > arr[i]) {
				super_swap(par, i);
				i = par;
			} else {
				break;
			}
		}
	}
	void push(const int &x) {
		pair<int, int> elem = { x, qs.size() };
		arr.push_back(elem);
		qs.push_back({ x, sz });
		deleted.push_back(0);
		sift_up(sz++);
	}
	void sift_down(const int &ind) {
		for (int i = ind;;) {
			int l = 2 * i, r = l + 1, next = l;
			if (r < sz && arr[r] < arr[l]) {
				next = r;
			}
			if (next < sz && arr[i] > arr[next]) {
				super_swap(i, next);
				i = next;
			} else {
				break;
			}
		}
	}
	pair<int, int> extract_min() {
		qs.push_back({ 0, 0 });
		deleted.push_back(0);
		if (is_empty()) {
			return{ -1, -1 };
		}
		deleted[arr[1].second] = 1;
		pair<int, int> res = arr[1];
		super_swap(1, --sz);
		sift_down(1);
		arr.pop_back();
		return res;
	}
	void decrease_key(const int &ind_push, const int &x) {
		qs.push_back({ 0, 0 });
		deleted.push_back(0);
		int ind_in_heap = qs[ind_push].second;
		if (deleted[ind_push]) {
			return;
		}
		qs[ind_push].first = x;
		int old = arr[ind_in_heap].first;
		arr[ind_in_heap].first = x;
		if (old > x) {
			sift_up(ind_in_heap);
		} else {
			sift_down(ind_in_heap);
		}
	}
};

int main() {
#if _DEBUG
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

	heap h;
	string s;
	while (cin >> s) {
		if (s == "push") {
			int a;
			cin >> a;
			h.push(a);
		}
		if (s == "extract-min") {
			pair<int, int> res = h.extract_min();
			if (res.second == -1) {
				cout << "*\n";
			} else {
				cout << res.first << " " << res.second + 1 << "\n";
			}
		}
		if (s == "decrease-key") {
			int a, b;
			cin >> a >> b;
			h.decrease_key(a - 1, b);
		}
	}

	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
