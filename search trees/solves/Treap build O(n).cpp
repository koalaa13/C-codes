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

#define F first
#define S second
#define mp make_pair
#define NAME "bridge"
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

const int N = 3e5 + 11;
int par[N], l[N], r[N];
struct vert {
	int x, y, ind;
	bool operator<(const vert &a) {
		return x < a.x;
	}
};

struct Node {
	Node* left;
	Node* right;
	Node* parent;
	int x, y, ind;
};
Node* Empty = new Node({ NULL, NULL, NULL, 0, 0, -1 });

void calc(Node* v, Node* parent = Empty) {
	if (v == Empty) {
		return;
	}
	int ind = v->ind - 1;
	if (parent == Empty) {
		par[ind] = 0;
	} else {
		par[ind] = parent->ind;
	}
	if (v->left == Empty) {
		l[ind] = 0;
	} else {
		l[ind] = v->left->ind;
	}
	if (v->right == Empty) {
		r[ind] = 0;
	} else {
		r[ind] = v->right->ind;
	}
	calc(v->left, v);
	calc(v->right, v);
}

void print(Node* v) {
	if (v == Empty) {
		return;
	}
	print(v->left);
	cout << v->x << " " << v->y << " " << v->ind << "\n";
	print(v->right);
}

int main() {
#if _DEBUG
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
#else
	// freopen(NAME".in", "r", stdin);
	// freopen(NAME".out", "w", stdout);
#endif

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	srand((int)time(NULL));
	// cout.precision(20);
	// cout.setf(ios::fixed);
	int n;
	cin >> n;
	vector<vert> arr(n);
	for (int i = 0; i < n; ++i) {
		cin >> arr[i].x >> arr[i].y;
		arr[i].ind = i + 1;
		arr[i].y = -arr[i].y;
	}
	sort(arr.begin(), arr.end());
	Node* last = new Node({ Empty, Empty, Empty, arr[0].x, arr[0].y, arr[0].ind });
	for (int i = 1; i < n; ++i) {
		if (last->y > arr[i].y) {
			last->right = new Node({ Empty, Empty, last, arr[i].x, arr[i].y, arr[i].ind });
			last = last->right;
		} else {
			Node* cur = last;
			while (cur->parent != Empty && cur->y < arr[i].y) {
				cur = cur->parent;
			}
			if (cur->y < arr[i].y) {
				Node* v = new Node({ cur, Empty, Empty, arr[i].x, arr[i].y, arr[i].ind });
				cur->parent = v;
				last = v;
			} else {
				Node* v = new Node({ cur->right, Empty, cur, arr[i].x, arr[i].y, arr[i].ind });
				cur->right->parent = v;
				cur->right = v;
				last = v;
			}
		}
		/*Node* deb = last;
		while (deb->parent != Empty) {
			deb = deb->parent;
		}
		print(deb);
		cout << "-----------------------------\n";*/
	}
	while (last->parent != Empty) {
		last = last->parent;
	}
	calc(last);
	cout << "YES\n";
	for (int i = 0; i < n; ++i) {
		cout << par[i] << " " << l[i] << " " << r[i] << "\n";
	}

	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
