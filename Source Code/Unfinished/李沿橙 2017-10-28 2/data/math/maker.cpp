#include<bits/stdc++.h>
#include<string>
#define G(x) ((rand()*(1LL<<47)+ rand()*(1LL<<31)+rand()*(1LL<<15)+rand() )%(x)+1)
using namespace std;
int data_start=7,data_end=20;
string problem_name="math";
ofstream fout;
string cmd_text,out_name;
void make_data1(int n);
void make_data2(int n);
void make_data3(int n,int q);
void make_data4(int n,int q);
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
    for(int i=data_start;i<=data_end;i++){
    	out_name=problem_name;
    	out_name+=int_to_string(i);
    	out_name+=".in"; 
        fout.open(out_name.c_str(),ios::out);
        
        int n=30;
		int a=1e9;
		int T=1000;
		fout<<T<<endl;
		for(int i=1;i<=T;i++)
			make_data3(n,a);
        
        fout.close();
		cmd_text=problem_name;
        cmd_text+=".exe <";
        cmd_text+=out_name;
        cmd_text+=" >";
        cmd_text+=problem_name;
        cmd_text+=int_to_string(i);
        cmd_text+=".out";
        system(cmd_text.c_str());
        cout<<cmd_text<<endl;
    }
    system("pause");
    return 0;
}

void make_data1(int n){
}
void make_data2(int n){
}
void make_data3(int n,int q){
	fout<<G(q)<<" "<<n-G(n/2)<<" "<<endl;
}
void make_data4(int n,int q){
}
void make_data5(int n){
} 
void make_data6(int n){
}

