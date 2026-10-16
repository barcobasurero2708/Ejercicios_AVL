#include<bits/stdc++.h>
using namespace::std;

const int N = 200000 + 5;

int root = 1;
int L[N];
int R[N];
int P[N];

void add_right_child(int x, int y) {
    R[x] = y;
    P[y] = x;
}

void add_left_child(int x, int y) {
    L[x] = y;
    P[y] = x;
}

void rotate_left(int x) {
    int p = P[x];
    int y = R[x];
    add_right_child(x, L[y]);
    if (p > 0) {
        if (L[p] == x) {
            add_left_child(p, y);
        }
        else {
            add_right_child(p, y);
        }
    }
    else {
        root = y;
        P[y] = 0;
    }
    add_left_child(y, x);
}

void rotate_right(int x) {
    int p = P[x];
    int y = L[x];
    add_left_child(x, R[y]);
    if (p > 0) {
        if (L[p] == x) {
            add_left_child(p, y);
        }
        else {
            add_right_child(p, y);
        }
    }
    else {
        root = y;
        P[y] = 0;
    }
    add_right_child(y, x);
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        cin >> L[i] >> R[i];
        if (L[i]) P[L[i]] = i;
        if (R[i]) P[R[i]] = i;
    }
    while (q--) {
        int x;
        char op;
        cin >> op >> x;
        if (op == 'I') rotate_left(x);
        else rotate_right(x);
    }
    cout << root << '\n';
    for (int i = 1; i <= n; ++i) {
        cout << L[i] << " " << R[i] << '\n';
    }
    return 0;
}