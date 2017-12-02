#include<bits/stdc++.h>
#include<string>
#define G(x) ((rand()*(1LL<<47)+ rand()*(1LL<<31)+rand()*(1LL<<15)+rand() )%(x)+1)
using namespace std;
int data_start=20,data_end=20;
string problem_name="graph";
ofstream fout;
string cmd_text,out_name;
void make_data1(int n,int m);
void make_data2(int n);
void make_data3(int n);
void make_data4(int n);
void make_data5(int n);
void make_data6(int n);
string int_to_string(int k){
	stringstream ss;
	ss<<k;
	string ret=ss.str();
	return ret; 
}
int main(){
    srand(time(0));
    for(int id=data_start;id<=data_end;id++){
    	out_name=problem_name;
    	out_name+=int_to_string(id);
    	out_name+=".in"; 
        fout.open(out_name.c_str(),ios::out);
        
        int n=1e5;
		make_data1(n,n+n);
        
        fout.close();
		cmd_text=problem_name;
        cmd_text+=".exe <";
        cmd_text+=out_name;
        cmd_text+=" >";
        cmd_text+=problem_name;
        cmd_text+=int_to_string(id);
        cmd_text+=".out";
        system(cmd_text.c_str());
        cout<<cmd_text<<endl;
    }
    system("pause");
    return 0;
}

set<pair<int,int> > st;
void add(int l,int r){
	if(l>r) swap(l,r);
	assert(st.insert(make_pair(l,r)).second);
	fout<<l<<" "<<r<<endl;
}
bool check(int l,int r){
	if(l>r) swap(l,r);
	return st.find(make_pair(l,r))!=st.end();
}

void make_data1(int n,int m){
	st.clear();
	fout<<n<<" "<<m<<endl;
	int left=m-(n-1);
	for(int i=2;i<=n-2;i++){
		if(G(2)==1&&i+2<=n-2&&left>1){
			add(i,i-1);
			add(i+1,i-1);
			add(i,i+1);
			left--;
			i++;
		}else{
			int l=G(i-1),r=i;
			add(l,r);
		}
	}
	add(n-1,n-2);
	add(n,n-2);
	if(left>0) add(n,n-1),left--;
	for(int i=1;i<=left;i++){
		int l=G(n),r=G(n);
		while(l==r||check(l,r)) l=G(n),r=G(n);
		add(l,r);
	}
}
void make_data2(int n){
}
void make_data3(int n){
}
void make_data4(int n){
}
void make_data5(int n){
} 
void make_data6(int n){
}

