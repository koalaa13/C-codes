#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

const int INF = 2e9;

vector<int> arr;
struct Node {
	Node* left;
	Node* right;
	int mn;
};

Node* Empty = new Node({ NULL, NULL, INF });

Node* build(int l, int r) {
	if (l + 1 == r) {
		return new Node({ Empty, Empty, arr[l] });
	}
	int mid = (l + r) / 2;
	Node* left_ch = build(l, mid);
	Node* right_ch = build(mid, r);
	return new Node({ left_ch, right_ch, min(left_ch->mn, right_ch->mn) });
}
Node* root;

void set(Node* v, int pos, int val, int lb, int rb) {
	if (lb + 1 == rb) {
		v->mn = val;
		return;
	}
	int mid = (lb + rb) / 2;
	if (pos < mid) {
		set(v->left, pos, val, lb, mid);
	} else {
		set(v->right, pos, val, mid, rb);
	}
	v->mn = min(v->left->mn, v->right->mn);
}

int get_min(Node* v, int l, int r, int lb, int rb) {
	if (lb >= r || rb <= l) {
		return INF;
	}
	if (l <= lb && r >= rb) {
		return v->mn;
	}
	int mid = (lb + rb) / 2;
	return min(get_min(v->left, l, r, lb, mid), get_min(v->right, l, r, mid, rb));
}

int main() {
	int n;
	cin >> n;
	arr.resize(n);
	for (int i = 0; i < n; ++i) {
		cin >> arr[i];
	}
	root = build(0, n);
	string s;
	while (cin >> s) {
		int a, b;
		cin >> a >> b;
		if (s == "min") {
			cout << get_min(root, a - 1, b, 0, n) << "\n";
		} else {
			set(root, a - 1, b, 0, n);
		}
	}

	return 0;
}
