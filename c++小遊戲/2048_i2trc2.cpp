#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
//high:6144

void SetColor(int color = 7)
{
  HANDLE hConsole;
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, color);
}

int dirline[4]={1,0,-1,0}; //列的方向
int dircolumn[4]={0,1,0,-1};//行的方向 
int board[4][4]; //方陣大小 
int value=0;
bool is_add[4][4]={0};

pair<int,int> position(){	//隨機選行列生成 
	int occupied=1,line,column;
	while(occupied){
		line=rand()%4;
		column=rand()%4;
		if(board[line][column]==0) occupied=0;
	}
	return make_pair(line,column);
	
}

void add_price(){
	pair<int,int> pos=position();	//隨機行列 
	board[pos.first][pos.second]=2;
}

void newgame(){ //初始化方陣 
	for(int i=0;i<4;++i){
		for(int j=0;j<4;++j)
			board[i][j]=0;
	}
	add_price();
}

void menu(){	//初始化 
	system("cls");
	for(int i=0;i<4;++i){
		for(int j=0;j<4;++j){
			if(board[i][j]==0) cout << setw(4) << ".";
			else{
				cout << setw(4) << board[i][j];
			}
		}
		cout << "\n";
	}
	cout << "-------------------\n";
	cout << "n:new game,  q:quit\n";
	cout << "w:up,  s:down,  a: left,  d:right\n";
	cout << "score: " << value <<"\n";
}

bool can_move(int line,int column,int nextline,int nextcolumn){
	if(nextline<0 || nextcolumn<0 || nextline>=4 || nextcolumn>=4
		|| board[line][column]!=board[nextline][nextcolumn] && board[nextline][nextcolumn]!=0)
		return false; //i,j,nextI,nextJ在範圍外 || 不能合併 
	return true;
}

void is_add_zero(){
	for(int i=0;i<4;++i) for(int j=0;j<4;++j) is_add[i][j]=0;
}

bool have_move(int i,int j,int nextI,int nextJ){
	if(board[i][j]==board[nextI][nextJ]){
		if(is_add[i][j] || is_add[nextI][nextJ]) return false;
		else return true;
	} 
	else return true;
}

void applymove(int dir){
	int startline=0,startcolumn=0,stepline=1,stepcolumn=1;
	if(dir==0){
		startline=3;
		stepline=-1;
	}
	if(dir==1){
		startcolumn=3;
		stepcolumn=-1;
	}
	int movepossible,can_add_price=0;
	
	do{
		movepossible=0;
		for(int i=startline;i>=0 && i<4;i+=stepline){
			for(int j=startcolumn;j>=0 && j<4;j+=stepcolumn){
				int nextI=i+dirline[dir],nextJ=j+dircolumn[dir];
				if(board[i][j] && can_move(i,j,nextI,nextJ) && have_move(i,j,nextI,nextJ)){
					if(board[nextI][nextJ]){
						is_add[nextI][nextJ]=1;
						value+=board[i][j];
					}
					board[nextI][nextJ]+=board[i][j];
					board[i][j]=0;
					movepossible=can_add_price=1;
				}
			}
		}
	}while(movepossible);
	if(can_add_price) add_price();
	is_add_zero();
} 

void color(){
	SetColor(12);
	cout << " ___    ___             ___ \n";
	SetColor(14);
	cout << "    |  |   |   |   |   |   |\n";
	SetColor(2);
	cout << " ___|  |   |   |___|   |___|\n";
	SetColor(11);
	cout << "|      |   |       |   |   |\n";
	SetColor(9);
	cout << "|___   |___|       |   |___|\n";
	SetColor();
	cout << "\n-------------------------------\n";
}

int main() {
	srand(time(0));
	char cmd_to_dir[128]; //wsad
	cmd_to_dir['s']=0; 
	cmd_to_dir['d']=1;
	cmd_to_dir['w']=2;
	cmd_to_dir['a']=3;
	
	string t;
	color();
	while(true){
		cout << "輸入i2trc2開始遊戲: ";
		cin >> t;
		if(t=="i2trc2")  break;
		else cout << "輸入錯誤\n";
	}
	newgame();
	while(true){
		menu();
		char s;
		cin >> s;
		if(s=='n'){
			newgame();
			value=0;
		}
		else if(s=='q') break;
		else if(s=='w'|| s=='a'||s=='s'||s=='d'){
			int now_dir=cmd_to_dir[s];
			//cout << now_dir << "\n";
			applymove(now_dir);
		}
	}
	
	return 0;
}
