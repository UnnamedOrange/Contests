#include<cstdio>
#include<cstring>
#include<cctype>
#include<cstdlib>
#include<set>
//#include<tr1/unordered_set>
using namespace std;
int n,m,tot,len[21000];
char s[11000][1001];
inline int get_pos(char c){
    return c-'a';
}
struct Trie{
//    unordered_set<int> exist;
	bool exist[21000];
    Trie *son[26];
}*root;
inline Trie* init(){
    Trie *ret;
    if(!(ret=(Trie*)malloc(sizeof(Trie)))) return NULL;
    for(int i=0;i<26;i++) ret->son[i]=NULL;
    memset(ret->exist,false,sizeof(ret->exist));
    return ret;
}
inline char get_char(){
    static char buf[10000001],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000000,stdin))?EOF:*p1++;
}
inline int read(){
    int num=0;
    char c;
    while(isspace(c=getchar()));
    while(num=num*10+c-48,isdigit(c=getchar()));
    return num;
}
void build(int tar,int len){
    Trie *now=root;
    for(int i=len-1;i>=0;i--){
        int pos=get_pos(s[tar][i]);
        if(!now->son[pos])
			now->son[pos]=init();
        now->son[pos]->exist[tar]=true;
        now=now->son[pos];
    }
}
int query(int t){
    int que[11],ans=0;
    for(int i=1;i<=t;i++) que[i]=read();
    Trie *now=root;
    while(now){
        int pos=get_pos(s[que[1]][len[que[1]]-ans-1]);
        now=now->son[pos];
        if(!now) return ans;
        for(int i=2;i<=t;i++)
			if(!now->exist[que[i]]) return ans;
        ans++;
    }
}
int main(){
	freopen("biology.in","r",stdin),freopen("biology.out","w",stdout);
    n=read(),m=read();
    root=init();
    for(int i=1,j;i<=n;i++){
    	j=0;
        while(isspace(s[i][0]=getchar()));
        while(isalpha(s[i][++j]=getchar()));
        s[i][len[i]=j]=0;
        build(i,j);
    }
    tot=n;
    for(int i=1;i<=m;i++){
        int con=read();
        if(con==1){
            tot++;
            int j=0;
            while(isspace(s[tot][0]=getchar()));
            while(isalpha(s[tot][++j]=getchar()));
            s[tot][len[tot]=j]=0;
            build(tot,j);
        } else {
            int t=read();
            printf("%d\n",query(t));
        }
    }
    fclose(stdin),fclose(stdout);
    return 0;
}
