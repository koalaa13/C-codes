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

struct Node {
	Node* left;
	Node* right;
	int pr, key, mn, mx;
};

typedef pair<Node*, Node*> pn;

const int INF = 2e9;
Node* Empty = new Node({ NULL, NULL, 0, 0, INF, -INF });
Node* root = Empty;

void upd(Node* v) {
	if (v == Empty) {
		return;
	}
	v->mn = min(v->left->mn, min(v->right->mn, v->key));
	v->mx = max(v->left->mx, max(v->right->mx, v->key));
}

Node* merge(Node* l, Node* r) {
	if (l == Empty) {
		upd(r);
		return r;
	}
	if (r == Empty) {
		upd(l);
		return l;
	}
	if (l->pr > r->pr) {
		l->right = merge(l->right, r);
		upd(l);
		return l;
	}
	r->left = merge(l, r->left);
	upd(r);
	return r;
}

pn split(Node* v, int k) {
	if (v == Empty) {
		return{ Empty, Empty };
	}
	if (v->key >= k) {
		pn fsplit = split(v->left, k);
		v->left = fsplit.second;
		upd(fsplit.first);
		upd(v);
		return{ fsplit.first, v };
	}
	pn fsplit = split(v->right, k);
	v->right = fsplit.first;
	upd(v);
	upd(fsplit.second);
	return{ v, fsplit.second };
}

void print(Node* v) {
	if (v == Empty) {
		return;
	}
	print(v->left);
	cout << v->key << " ";
	print(v->right);
}

void insert(int key) {
	pn fsplit = split(root, key);
	Node* v = new Node({ Empty, Empty, rand(), key, key, key });
	root = merge(fsplit.first, merge(v, fsplit.second));
}

void erase(int key) {
	pn fsplit = split(root, key);
	pn ssplit = split(fsplit.second, key + 1);
	root = merge(fsplit.first, ssplit.second);
}

bool exists(int key) {
	pn fsplit = split(root, key);
	pn ssplit = split(fsplit.second, key + 1);
	bool res = ssplit.first != Empty;
	root = merge(fsplit.first, merge(ssplit.first, ssplit.second));
	return res;
}

int next(Node* v, int key) {
	if (v == Empty) {
		return -INF;
	}
	if (v->key <= key) {
		return next(v->right, key);
	}
	return next(v->left, key);
}

int prev(Node* v, int key) {
	if (v == Empty) {
		return INF;
	}
	if (v->key > key) {
		return max(v->key, prev(v->left, key));
	}
	return prev(v->right, key);
}

int next(int key) {
	pn fsplit = split(root, key + 1);
	int res = fsplit.second->mn;
	root = merge(fsplit.first, fsplit.second);
	return res;
}

int prev(int key) {
	pn fsplit = split(root, key);
	int res = fsplit.first->mx;
	root = merge(fsplit.first, fsplit.second);
	return res;
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
	// srand((int)time(NULL));
	// srand(172381);
	// cout.precision(20);
	// cout.setf(ios::fixed);
	string type;
	int x;
	while (cin >> type) {
		cin >> x;
		if (type == "insert") {
			insert(x);
		}
		if (type == "delete") {
			erase(x);
		}
		if (type == "exists") {
			if (exists(x)) {
				cout << "true\n";
			} else {
				cout << "false\n";
			}
		}
		if (type == "next") {
			int res = next(x);
			if (res == INF) {
				cout << "none\n";
			} else {
				cout << res << "\n";
			}
		}
		if (type == "prev") {
			int res = prev(x);
			if (res == -INF) {
				cout << "none\n";
			} else {
				cout << res << "\n";
			}
		}
	}

	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
