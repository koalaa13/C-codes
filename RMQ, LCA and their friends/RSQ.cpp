#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef long long ll;

struct Node {
	Node* left;
	Node* right;
	ll sum;
};
Node* Empty = new Node({ NULL, NULL, 0 });

Node* build(int lb, int rb, vector<ll> const &arr) {
	if (lb + 1 == rb) {
		return new Node({ Empty, Empty, arr[lb] });
	}
	int mid = (lb + rb) / 2;
	Node* lch = build(lb, mid, arr);
	Node* rch = build(mid, rb, arr);
	return new Node({ lch, rch, lch->sum + rch->sum });
}

void change(Node* v, int ind, ll x, int lb, int rb) {
	if (lb + 1 == rb) {
		v->sum = x;
		return;
	}
	int mid = (lb + rb) / 2;
	if (ind < mid) {
		change(v->left, ind, x, lb, mid);
	} else {
		change(v->right, ind, x, mid, rb);
	}
	v->sum = v->left->sum + v->right->sum;
}

ll get_sum(Node* v, int l, int r, int lb, int rb) {
	if (l >= rb || r <= lb) {
		return 0;
	}
	if (l <= lb && rb <= r) {
		return v->sum;
	}
	int mid = (lb + rb) / 2;
	return get_sum(v->left, l, r, lb, mid) + get_sum(v->right, l, r, mid, rb);
}

int main() {
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
		if (type == "sum") {
			int l, r;
			cin >> l >> r;
			cout << get_sum(root, l - 1, r, 0, n) << "\n";
		} else {
			int ind;
			ll x;
			cin >> ind >> x;
			change(root, ind - 1, x, 0, n);
		}
	}

	return 0;
}
