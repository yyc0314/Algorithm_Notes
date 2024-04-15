#include<bits/stdc++.h>
using namespace std;
int g[100][100];
int y,x,cnt;
int dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};

void dfs(int a,int b){
    if(g[a][b]==0){
        cnt++;
        g[a][b]=-1;
        int n_x,n_y;
        for(int i=0;i<4;i++){
            n_x=a+dir[i][0];
            n_y=b+dir[i][1];

            if(n_x>=0 && n_y>=0 && n_x<y && n_y<x){
                dfs(n_x,n_y);
            }
        }
    }
}



int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    cin.ignore();

    for(int k=0;k<n;++k){
        int a,b;
        cin >> a >> b;
        a--;
        b--;
        cnt=0;
        y=0;

        cin.ignore();

        string s;

        while(getline(cin,s)){
            if(s=="") break;
            x=s.size();
            for(int j=0;j<x;j++){
                g[y][j]=int(s[j])-48;
            }
            y++;
        }
        dfs(a,b);

        //uva a blank between dataset
        cout << cnt << "\n";
        if(k!=n-1)cout << "\n";

        //zj
        //cout << cnt;
        //if(k!=n-1)cout << "\n";
    }

    return 0;
}
