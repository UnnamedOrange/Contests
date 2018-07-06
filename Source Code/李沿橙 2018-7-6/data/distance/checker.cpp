#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int x[N], y[N], s[N], t[N], u[N], v[N];
int main(int argc, char *argv[]) {
    FILE *fin = fopen(argv[1], "r");
    FILE *fout = fopen(argv[2], "r");
    FILE *ans = fopen(argv[3], "r");
    //FILE *ftot = fopen(argv[4], "r");
    FILE *fscore = fopen(argv[5], "w");
    FILE *msg = fopen(argv[6], "w");
    int n, m, k, i, k1, k2, d, fmk, len = 0;
    fscanf(fin, "%d%d%d", &n, &m, &k);
    for (i = 1; i <= k; ++i) fscanf(fin, "%d%d", &x[i], &y[i]);
    fscanf(ans, "%d", &k1);
    for (i = 1; i <= k1; ++i) fscanf(ans, "%d", &u[i]);
    for (i = 2; i <= k1; ++i) {
        d = max(abs(x[u[i]] - x[u[i - 1]]), abs(y[u[i]] - y[u[i - 1]]));
        while (s[d]) s[d++] = 0;
        s[d] = 1; len = max(len, d);
    }
    fscanf(fout, "%d", &k2);
    for (i = 1; i <= k2; ++i) {
        fscanf(fout, "%d", &v[i]);
        if (v[i] < 1 || v[i] > k) {
            fprintf(fscore, "0\n");
            fprintf(msg, "invalid point received");
            return 0;
        }
    }
    if (v[1] != 1 || v[k2] != k) {
        fprintf(fscore, "0\n");
        fprintf(msg, "wrong starting point or ending point");
        return 0;
    }
    for (i = 2; i <= k2; ++i) {
        d = max(abs(x[v[i]] - x[v[i - 1]]), abs(y[v[i]] - y[v[i - 1]]));
        while (t[d]) t[d++] = 0;
        t[d] = 1; len = max(len, d);
    }
    for (i = 0; i <= len; ++i)
        if (s[i] != t[i]) {
            fprintf(fscore, "0\n");
            fprintf(msg, "not shortest");
            return 0;
        }
    fprintf(fscore, "%s\n", argv[4]);
    fprintf(msg, "U R soooooo strong!");
    return 0;
}
