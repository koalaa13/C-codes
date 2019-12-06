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
#define NAME "buckets"
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
typedef unsigned int ui;

vector<pair<int, int>> net;

inline bool is_sorted(const int &l, const int &r, const vector<int> &arr) {
	for (size_t i = (size_t)l; i + 1 < (size_t)r; ++i) {
		if (arr[i + 1] < arr[i]) {
			return 0;
		}
	}
	return 1;
}

void build(const int &l, const int &r, const vector<int> &arr) {
	if (r - l < 2) {
		return;
	}
	if (!is_sorted(l, r, arr)) {
		build(l, r - 1, arr);
		if (arr[r]) {
			for (int i = l; i < r; ++i) {
				net.push_back({ i, r });
			}
		} else {
			for (int i = r; i > l; --i) {
				net.push_back({ i - 1, i });
			}
		}
	} else {
		build(l + 1, r, arr);
		if (arr[l]) {
			for (int i = l; i < r; ++i) {
				net.push_back({ i, i + 1 });
			}
		} else {
			for (int i = r; i > l; --i) {
				net.push_back({ l, i });
			}
		}
	}
}

vector<int> gen_arr(int n) {
	vector<int> res(n);
	do {
		for (int i = 0; i < n; ++i) {
			res[i] = rand() % 2;
		}
	} while (is_sorted(0, n, res));
	return res;
}

vector<vector<int>> find_not_sorted(int n) {
	vector<vector<int>> not_sorted;
	for (int mask = 0; mask < (1 << n); ++mask) {
		vector<int> cur(n), copy;
		for (int i = 0; i < n; ++i) {
			cur[i] = (mask & (1 << i)) > 0;
		}
		copy = cur;
		for (pair<int, int> i : net) {
			if (cur[i.first] > cur[i.second]) {
				swap(cur[i.first], cur[i.second]);
			}
		}
		if (!is_sorted(0, n, cur)) {
			not_sorted.push_back(copy);
		}
	}
	return not_sorted;
}

vector<int> get_arr(int mask, int n) {
	vector<int> arr(n);
	for (int i = 0; i < n; ++i) {
		arr[i] = (mask & (1 << i)) > 0;
	}
	return arr;
}

int main() {
#if SOLVE
	// freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
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

	/*for (int n = 2; n < 11; ++n) {
		for (int i = 0; i < (1 << n); ++i) {
			vector<int> arr = get_arr(i, n);
			if (is_sorted(0, n, arr)) {
				continue;
			}
			net.clear();
			build(0, (int)arr.size() - 1, arr);
			vector<vector<int>> not_sorted = find_not_sorted(n);
			if (not_sorted.size() != 1) {
				cout << "array is:\n";
				for (int i : arr) {
					cout << i << " ";
				}
				cout << "\nnot sorted with my network arrays:\n";
				for (size_t i = 0; i < not_sorted.size(); ++i) {
					for (int j : not_sorted[i]) {
						cout << j << " ";
					}
					cout << "\n";
				}
				return 0;
			} else {
				for (int i : arr) {
					cout << i << " ";
				}
				cout << "OK\n";
			}
		}
	}*/
	/*for (int t = 0;; ++t) {
		vector<int> arr = gen_arr(N);
		net.clear();
		build(0, (int)arr.size() - 1, arr);
		vector<vector<int>> not_sorted = find_not_sorted();
		if (not_sorted.size() != 1) {
			cout << "array is:\n";
			for (int i : arr) {
				cout << i << " ";
			}
			cout << "\nnot sorted with my network arrays:\n";
			for (size_t i = 0; i < not_sorted.size(); ++i) {
				for (int j : not_sorted[i]) {
					cout << j << " ";
				}
				cout << "\n";
			}
			return 0;
		} else {
			cout << "test# " << t << " ACCEPTED\n";
		}
	}*/
	for (;;) {
		int n;
		cin >> n;
		if (!n) {
			return 0;
		}
		vector<int> arr(n);
		for (int i = 0; i < n; ++i) {
			cin >> arr[i];
		}
		if (is_sorted(0, n, arr)) {
			cout << "-1\n";
		} else {
			net.clear();
			build(0, n - 1, arr);
			cout << net.size() << "\n";
			for (auto i : net) {
				cout << min(i.first, i.second) + 1 << " " << max(i.first, i.second) + 1 << "\n";
			}
		}
	}


	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
