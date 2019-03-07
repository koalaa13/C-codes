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
//#pragma comment(linker, "/STACK:256000000")
using namespace std;

#define mp make_pair
#define NAME "stack1"
/*#define FAST_ALLOCATOR_MEMORY 2e8
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
#endif*/

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

int trash = numeric_limits<int>::min();

struct myvector {
	int sz, free_ind, *arr;
	myvector() {
		sz = 1;
		free_ind = 0;
		arr = new int[1];
	}
	bool empty() {
		return !sz;
	}
	int size() {
		return free_ind;
	}
	void push_back(int v) {
		if (free_ind == sz) {
			int *copy = new int[free_ind];
			for (int i = 0; i < free_ind; ++i) {
				copy[i] = arr[i];
			}
			delete[] arr;
			sz *= 2;
			arr = new int[sz];
			for (int i = 0; i < free_ind; ++i) {
				arr[i] = copy[i];
			}
		}
		arr[free_ind++] = v;
	}
	void pop_back() {
		if (!empty()) {
			free_ind--;
			if (free_ind * 4 <= sz && sz >= 4) {
				int *copy = new int[free_ind];
				for (int i = 0; i < free_ind; ++i) {
					copy[i] = arr[i];
				}
				sz = sz / 2;
				delete[] arr;
				arr = new int[sz];
				for (int i = 0; i < free_ind; ++i) {
					arr[i] = copy[i];
				}
			}
		}
	}
	int back() {
		if (!empty()) {
			return arr[free_ind - 1];
		}
		return trash;
	}
};

int main() {
#if SOLVE
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
#else
	freopen(NAME".in", "r", stdin);
	freopen(NAME".out", "w", stdout);
#endif

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	//srand(time(NULL));
	//cout.precision(20);
	//cout.setf(ios::fixed);

	myvector st;
	int m;
	cin >> m;
	for (int i = 0; i < m; ++i) {
		char t;
		cin >> t;
		if (t == '+') {
			int v;
			cin >> v;
			st.push_back(v);
		}
		if (t == '-') {
			cout << st.back() << "\n";
			st.pop_back();
		}
	}

	//cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}