#include<bits/stdc++.h>
#include<string>
#define G(x) ((rand()*(1LL<<47)+ rand()*(1LL<<31)+rand()*(1LL<<15)+rand() )%(x)+1)
using namespace std;
int data_start=14,data_end=14;
string problem_name="tree";
ofstream fout;
string cmd_text,out_name;
void make_data1(int n);
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
    for(int i=data_start;i<=data_end;i++){
    	out_name=problem_name;
    	out_name+=int_to_string(i);
    	out_name+=".in"; 
        fout.open(out_name.c_str(),ios::out);
        
        int n=2000;
		int T=10;
		fout<<T<<endl;
		for(int i=1;i<=T;i++){
			if(G(2)==1) make_data1(n-G(n/10));
			else make_data2(n-G(n/10));
		}
		
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
	int k=max(G(n),2LL);
	fout<<n<<" "<<k<<endl;
	for(int i=2;i<=n;i++)
		fout<<G(i-1)<<" ";
	fout<<endl;
}
void make_data2(int n){
	int k=max(G(n),2LL);
	fout<<n<<" "<<k<<endl;
	for(int i=2;i<=n;i++)
		fout<<(G(n/10)==1||i>n/2 ? G(i-1):i-1) <<" ";
	fout<<endl;
}
void make_data3(int n){
}
void make_data4(int n){
}
void make_data5(int n){
} 
void make_data6(int n){
}

