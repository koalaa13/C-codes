#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int INF = 2e9;
const int N = 2e6 + 111;
const int SHIFT = N >> 1;

struct Node {
	Node* left;
	Node* right;
	int add, mx, mx_ind;
};
Node* Empty = new Node({ NULL, NULL, 0, -INF, -1 });

Node* build(int lb, int rb) {
	if (lb + 1 == rb) {
		return new Node({ Empty, Empty, 0, 0, lb });
	}
	int mid = (lb + rb) / 2;
	Node* lch = build(lb, mid);
	Node* rch = build(mid, rb);
	return new Node({ lch, rch, 0, 0, lb });
}

void push(Node* v) {
	if (v == Empty) {
		return;
	}
	v->mx += v->add;
	v->left->add += v->add;
	v->right->add += v->add;
	v->add = 0;
}

void add(Node* v, int l, int r, int x, int lb, int rb) {
	push(v);
	if (lb >= r || rb <= l) {
		return;
	}
	if (l <= lb && rb <= r) {
		v->add += x;
		push(v);
		return;
	}
	int mid = (lb + rb) / 2;
	add(v->left, l, r, x, lb, mid);
	add(v->right, l, r, x, mid, rb);
	if (v->left->mx > v->right->mx) {
		v->mx = v->left->mx;
		v->mx_ind = v->left->mx_ind;
	} else {
		v->mx = v->right->mx;
		v->mx_ind = v->right->mx_ind;
	}
}

pair<int, int> get_max(Node* v, int l, int r, int lb, int rb) {
	push(v);
	if (lb >= r || rb <= l) {
		return{ -INF, -1 };
	}
	if (l <= lb && rb <= r) {
		return{ v->mx, v->mx_ind };
	}
	int mid = (lb + rb) / 2;
	pair<int, int> left_res = get_max(v->left, l, r, lb, mid);
	pair<int, int> right_res = get_max(v->right, l, r, mid, rb);
	return left_res.first > right_res.first ? left_res : right_res;
}

struct ev {
	int type, x, l, r;
};

bool cmp(ev const &a, ev const &b) {
	if (a.x != b.x) {
		return a.x < b.x;
	}
	return a.type < b.type;
}

int main() {
	// freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	cin >> n;
	vector<ev> evs;
	for (int i = 0; i < n; ++i) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		evs.push_back({ 0, x1, y1 + SHIFT, y2 + SHIFT });
		evs.push_back({ 1, x2, y1 + SHIFT, y2 + SHIFT });
	}
	sort(evs.begin(), evs.end(), cmp);
	int ans = 0, x_ans = 0, y_ans = 0;
	Node* root = build(0, N);
	for (ev cur : evs) {
		if (cur.type == 0) {
			add(root, cur.l, cur.r + 1, 1, 0, N);
			pair<int, int> cur_ans = get_max(root, 0, N, 0, N);
			if (cur_ans.first > ans) {
				ans = cur_ans.first;
				x_ans = cur.x;
				y_ans = cur_ans.second - SHIFT;
			}
		} else {
			add(root, cur.l, cur.r + 1, -1, 0, N);
		}
	}
	cout << ans << "\n" << x_ans << " " << y_ans;

	return 0;
}
