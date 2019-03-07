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
	int pr, k, sz;
};

typedef pair<Node*, Node*> pn;

Node* Empty = new Node({ NULL, NULL, 0, 0, 0 });
Node* root = Empty;

void upd(Node* v) {
	if (v == Empty) {
		return;
	}
	v->sz = v->left->sz + v->right->sz + 1;
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
	if (v->k >= k) {
		pn fsplit = split(v->left, k);
		v->left = fsplit.second;
		upd(v);
		upd(fsplit.first);
		return{ fsplit.first, v };
	}
	pn fsplit = split(v->right, k);
	v->right = fsplit.first;
	upd(fsplit.second);
	upd(v);
	return{ v, fsplit.second };
}

pn split_sz(Node* v, int k) {
	if (v == Empty) {
		return{ Empty, Empty };
	}
	if (v->left->sz >= k) {
		pn fsplit = split_sz(v->left, k);
		v->left = fsplit.second;
		upd(fsplit.first);
		upd(v);
		return{ fsplit.first, v };
	}
	pn fsplit = split_sz(v->right, k - v->left->sz - 1);
	v->right = fsplit.first;
	upd(fsplit.second);
	upd(v);
	return{ v, fsplit.second };
}

void insert(int key) {
	key = -key;
	pn fsplit = split(root, key);
	Node* v = new Node({ Empty, Empty, rand(), key, 1 });
	root = merge(fsplit.first, merge(v, fsplit.second));
}

void erase(int key) {
	key = -key;
	pn fsplit = split(root, key);
	pn ssplit = split_sz(fsplit.second, 1);
	root = merge(fsplit.first, ssplit.second);
}

int kth(int k) {
	pn fsplit = split_sz(root, k - 1);
	pn ssplit = split_sz(fsplit.second, 1);
	int res = ssplit.first->k;
	root = merge(fsplit.first, merge(ssplit.first, ssplit.second));
	return res;
}

void print(Node* v) {
	if (v == Empty) {
		return;
	}
	print(v->left);
	cout << v->k << " ";
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
	for (int i = 0; i < n; ++i) {
		string type;
		int k;
		cin >> type >> k;
		if (type == "1" || type == "+1") {
			insert(k);
		}
		if (type == "0") {
			cout << -kth(k) << "\n";
		}
		if (type == "-1") {
			erase(k);
		}
		// print(root);
		// cout << "\n";
	}

	// cerr << clock() * 1. / CLOCKS_PER_SEC << "\n";
	return 0;
}
