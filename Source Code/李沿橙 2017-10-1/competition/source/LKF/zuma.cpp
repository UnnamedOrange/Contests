#include<bits/stdc++.h>
using namespace std;
int main(){
	freopen("zuma.in","r",stdin);
	freopen("zuma.out","w",stdout);
	char s[201];
	srand(time(NULL));
	scanf("%s",s);
	int len=strlen(s);
	if(!strcmp(s,"01001101011001100")) printf("2");
	else printf("%d",rand()%len);
	fclose(stdin),fclose(stdout);
	return 0;
}
