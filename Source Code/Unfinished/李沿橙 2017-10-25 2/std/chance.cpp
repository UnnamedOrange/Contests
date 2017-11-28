#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

const double eps = 1e-9;
using namespace std;
const int N = 2111;
int n;
double prob[N];
double f[N][N];
long long getsum(long long num) {
    long long now = 1;
    if (!num) return 0;
    long long sum = 1;
    for (int i = 2; i <= 19; i++) {
        now *= 10;
        if (now > num) {
       		return sum;
        }
        if (now * 2 > num) {
            return sum + num - now + 1;
        }
        sum += now;
    }
}
int fix(double x) {
    if (fabs(x - (int)x) < eps) return (int)x;
    else return (int)(x + 1 - eps);
}

int main() {
	freopen("chance.in", "r", stdin);
	freopen("chance.out", "w", stdout);
	
	double k;
    scanf("%d", &n);
    scanf("%lf", &k);
    for (int i = 1; i <= n; i++) {
        long long l, r;
        scanf("%lld%lld", &l, &r);
        prob[i] = 1. * (getsum(r) - getsum(l - 1)) / ((r - l + 1) * 1.);
    }
    k /= 100;
    int need = fix(n * k);
    f[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            f[i][j] += f[i - 1][j] * (1 - prob[i]);
            if (j) {
                f[i][j] += f[i - 1][j - 1] * prob[i];
            }
        }
    }
    double ans = 0;
    for (int i = need; i <= n; i++) {
        ans += f[n][i];
    }
    printf("%.7f\n", ans);
    return 0;
}
