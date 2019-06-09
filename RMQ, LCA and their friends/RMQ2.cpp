#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <cstdio>

using namespace std;

typedef long long ll;

const ll INF = 2e18;
struct Node {
	Node* left;
	Node* right;
	int to_do;
	ll add, set, mn;
};
Node* Empty = new Node({ NULL, NULL, 0, 0, INF, INF });

Node* build(int lb, int rb, vector<ll> const &arr) {
	if (lb + 1 == rb) {
		return new Node{ Empty, Empty, 0, 0, INF, arr[lb]};
	}
	int mid = (lb + rb) / 2;
	Node* lch = build(lb, mid, arr);
	Node* rch = build(mid, rb, arr);
	return new Node({ lch, rch, 0, 0, INF, min(lch->mn, rch->mn) });
}

void push(Node* v) {
	if (v == Empty || v->to_do == 0) {
		return;
	}
	if (v->to_do == 1) {
		v->mn = (v->set == INF ? v->mn : v->set) + v->add;
	} else {
		v->add = 0;
		v->mn = v->set;
	}
	v->left->to_do = v->right->to_do = v->to_do;
	v->to_do = 0;
	if (v->set != INF) {
		v->left->add = v->right->add = 0;
		v->left->set = v->right->set = v->set;
		v->set = INF;
	}
	v->left->add += v->add;
	v->right->add += v->add;
	v->add = 0;
}

void set(Node* v, int l, int r, ll x, int lb, int rb) {
	push(v);
	if (lb >= r || rb <= l) {
		return;
	}
	if (l <= lb && rb <= r) {
		v->set = x;
		v->to_do = 2;
		push(v);
		return;
	}
	int mid = (lb + rb) / 2;
	set(v->left, l, r, x, lb, mid);
	set(v->right, l, r, x, mid, rb);
	v->mn = min(v->left->mn, v->right->mn);
}

void add(Node* v, int l, int r, ll x, int lb, int rb) {
	push(v);
	if (lb >= r || rb <= l) {
		return;
	}
	if (l <= lb && rb <= r) {
		v->add += x;
		v->to_do = 1;
		push(v);
		return;
	}
	int mid = (lb + rb) / 2;
	add(v->left, l, r, x, lb, mid);
	add(v->right, l, r, x, mid, rb);
	v->mn = min(v->left->mn, v->right->mn);
}

ll get_min(Node* v, int l, int r, int lb, int rb) {
	push(v);
	if (lb >= r || rb <= l) {
		return INF;
	}
	if (l <= lb && rb <= r) {
		return v->mn;
	}
	int mid = (lb + rb) / 2;
	return min(get_min(v->left, l, r, lb, mid), get_min(v->right, l, r, mid, rb));
}

int main() {
	// freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	cin >> n;
	vector<ll> arr(n);
	for (int i = 0; i < n; ++i) {
		cin >> arr[i];
	}
	Node* root = build(0, n, arr);
	string type;
	while (cin >> type) {
		if (type == "min") {
			int l, r;
			cin >> l >> r;
			// printf("%I64d\n", get_min(root, l - 1, r, 0, n));
			cout << get_min(root, l - 1, r, 0, n) << "\n";
		} else {
			int l, r;
			ll x;
			cin >> l >> r >> x;
			if (type == "set") {
				set(root, l - 1, r, x, 0, n);
			} else {
				add(root, l - 1, r, x, 0, n);
			}
		}
	}
	/*string type;
	while (cin >> type) {
		int l, r;
		cin >> l >> r;
		if (type == "min") {
			ll res = arr[l - 1];
			for (int i = l; i < r; ++i) {
				res = min(res, arr[i]);
			}
			printf("%I64d\n", res);
		} else {
			ll x;
			cin >> x;
			if (type == "set") {
				for (int i = l - 1; i < r; ++i) {
					arr[i] = x;
				}
			} else {
				for (int i = l - 1; i < r; ++i) {
					arr[i] += x;
				}
			}
		}
	}*/

	return 0;
}
