#include<bits/stdc++.h>
using namespace std;
int n;
vector<int>parent;

int f_set(int x){
    if(x!=parent[x]){
        parent[x]=f_set(parent[x]);
    }
    else return x;
}

void u_set(int x,int y){
    int x_r=f_set(x),y_r=f_set(y);
    if(x_r==y_r) return;
    else parent[y_r]=x_r;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int k;
    cin >> k;
    cin.ignore();

    for(int j=0;j<k;++j){
        int s_num=0,f_num=0;
        parent.clear();

        cin >> n;
        parent.assign(n+1,-1);
        for(int i=1;i<=n;++i) parent[i]=i;
        //cout << j << " " << n << ":";

        string s;
        cin.ignore();

        while(getline(cin,s)){
            if(s=="") break;

            char c;
            int a,b;

            sscanf(s.c_str(),"%c %d %d",&c,&a,&b);
            if(c=='c'){
                u_set(a,b);
            }
            else{
                if(f_set(a)==f_set(b)) s_num+=1;
                else f_num+=1;
            }
        }

        cout << s_num << "," << f_num << "\n";
        if(j!=k-1) cout << "\n";

    }
}
