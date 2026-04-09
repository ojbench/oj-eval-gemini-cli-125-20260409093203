#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

struct Constraint {
    int i, j, e;
};

const int MAXN = 3000005;
int parent_node[MAXN * 2];

int find_set(int v) {
    if (v == parent_node[v])
        return v;
    return parent_node[v] = find_set(parent_node[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b)
        parent_node[b] = a;
}

char buf[1 << 21], *p1 = buf, *p2 = buf;
inline char getc() {
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++;
}

inline int read() {
    int x = 0, f = 1;
    char ch = getc();
    while (ch < '0' || ch > '9') {
        if (ch == EOF) return -1;
        if (ch == '-') f = -1;
        ch = getc();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getc();
    }
    return x * f;
}

void solve() {
    int n = read();
    if (n == -1) return;
    vector<Constraint> constraints(n);
    vector<int> vars;
    vars.reserve(n * 2);
    for (int k = 0; k < n; ++k) {
        constraints[k].i = read();
        constraints[k].j = read();
        constraints[k].e = read();
        vars.push_back(constraints[k].i);
        vars.push_back(constraints[k].j);
    }
    
    sort(vars.begin(), vars.end());
    vars.erase(unique(vars.begin(), vars.end()), vars.end());
    
    int num_vars = vars.size();
    for (int k = 0; k < num_vars; ++k) {
        parent_node[k] = k;
    }
    
    for (int k = 0; k < n; ++k) {
        if (constraints[k].e == 1) {
            int u = lower_bound(vars.begin(), vars.end(), constraints[k].i) - vars.begin();
            int v = lower_bound(vars.begin(), vars.end(), constraints[k].j) - vars.begin();
            union_sets(u, v);
        }
    }
    
    bool possible = true;
    for (int k = 0; k < n; ++k) {
        if (constraints[k].e == 0) {
            int u = lower_bound(vars.begin(), vars.end(), constraints[k].i) - vars.begin();
            int v = lower_bound(vars.begin(), vars.end(), constraints[k].j) - vars.begin();
            if (find_set(u) == find_set(v)) {
                possible = false;
                break;
            }
        }
    }
    
    if (possible) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
}

int main() {
    int t = read();
    if (t != -1) {
        while (t--) {
            solve();
        }
    }
    return 0;
}