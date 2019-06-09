#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cstdio>

using namespace std;

const int INF = 2e9;
struct Node {
	Node* left;
	Node* right;
	int cnt_z;
};
Node* Empty = new Node({ NULL, NULL, 0 });

Node* build(int lb, int rb) {
	if (lb + 1 == rb) {
		return new Node({ Empty, Empty, 1 });
	}
	int mid = (lb + rb) / 2;
	Node* lch = build(lb, mid);
	Node* rch = build(mid, rb);
	return new Node({ lch, rch, lch->cnt_z + rch->cnt_z });
}

void change(Node* v, int ind, int x, int lb, int rb) {
	if (lb + 1 == rb) {
		v->cnt_z = 1 - x;
		return;
	}
	int mid = (lb + rb) / 2;
	if (ind < mid) {
		change(v->left, ind, x, lb, mid);
	} else {
		change(v->right, ind, x, mid, rb);
	}
	v->cnt_z = v->left->cnt_z + v->right->cnt_z;
}

int get(Node* v, int l, int r, int lb, int rb) {
	if (lb >= r || rb <= l || v->cnt_z == 0) {
		return INF;
	}
	if (lb + 1 == rb) {
		return v->cnt_z == 1 ? lb : INF;
	}
	int mid = (lb + rb) / 2;
	int res = get(v->left, l, r, lb, mid);
	return res == INF ? get(v->right, l, r, mid, rb) : res;
}

int main() {
	// freopen("input.txt", "r", stdin);
	// ios_base::sync_with_stdio(false);
	// cin.tie(NULL);
	int n, m;
	cin >> n >> m;
	Node* root = build(0, n);
	for (int i = 0; i < m; ++i) {
		int id;
		string s;
		cin >> s >> id;
		if (s == "exit") {
			change(root, id - 1, 0, 0, n);
		} else {
			int cur = get(root, id - 1, n, 0, n);
			if (cur == INF) {
				cur = get(root, 0, id, 0, n);
			}
			// printf("%d\n", cur + 1);
			cout << cur + 1 << "\n";
			change(root, cur, 1, 0, n);
		}
	}

	return 0;
}
