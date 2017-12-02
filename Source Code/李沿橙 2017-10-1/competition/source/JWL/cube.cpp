#include<cstdio>
const int maxn = 3e4 + 10;
int n;
int s[maxn], top[maxn], down[maxn];
void find(int k,int q) {
	if(k==top[k]) return;
	s[q]+=s[k];
	top[q]=top[k];
	find(top[k],q);
}
int main() {
	freopen("cube.in", "r", stdin);
	freopen("cube.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		top[i] = i;
		down[i] = i;
	}
	char ch[3];
	int a, b;
	for(int i = 1; i <= n; i++) {
		scanf("%s", ch);
		if(ch[0] == 'M') {
			scanf("%d%d",&a,&b);
			find(top[a],a);
			find(top[b],b);
			s[top[b]]+=s[top[a]]+1;
			top[top[a]]=top[top[b]];
		}
		if(ch[0] == 'C') {
			scanf("%d", &a);
			find(top[a],a);
			printf("%d\n",s[top[a]]-s[a]);
		}
	}
	return 0;
}
