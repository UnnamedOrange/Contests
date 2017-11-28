#include<bits/stdc++.h>
#include<string>
#define G(x) ((rand()*(1LL<<47)+ rand()*(1LL<<31)+rand()*(1LL<<15)+rand() )%(x)+1)
using namespace std;
int data_start=15,data_end=20;
string problem_name="equal";
ofstream fout;
string cmd_text,out_name;
void make_data1(int n,int q);
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
        
        int n=100000;
        int q=100000;
		make_data1(n,q);
        
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

vector<pair<int,int> > v;
void make_data1(int n,int q){
	v.clear();
	fout<<n<<endl;
	int p=n/5;
	for(int i=2;i<=p*3;i++){
		if(i%p==0) v.push_back(make_pair(1,i));
		else v.push_back(make_pair(i-1,i));
	}
	for(int i=p*3+1;i<=p*4;i++)
		v.push_back(make_pair(1,i));
	for(int i=p*4+1;i<=n;i++)
		v.push_back(make_pair(G(i-1),i));
	random_shuffle(v.begin(),v.end());
	for(int i=0;i<n-1;i++) 
		fout<<v[i].first<<" "<<v[i].second<<endl;
	fout<<q<<endl;
	for(int i=1,x;i<=q;i++)
		fout<<G(n)<<" "<<G(n)<<endl;
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

