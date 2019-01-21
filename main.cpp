#include "gitgen.h"
#include "gitgen.cpp"

#define COLOR(a) SetConsoleTextAttribute(hConsole, a)
#define SPACE(a) for(int i=0;i<a;i++) { cout<<" "; }

using namespace std;
bool first=true;

void centerstring(string s){
	int pos=(int)((70-s.length())/2);
	for(int i=0;i<pos;i++)
	cout<<" ";
	cout<<s;
}

void rightstring(string s){
	int pos=(int)(70-s.length());
	for(int i=0;i<pos;i++)
	cout<<" ";
	cout<<s;
}

void remove_scrollbar(){
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(handle, &info);
    COORD new_size = 
    {
        info.srWindow.Right - info.srWindow.Left + 1,
        info.srWindow.Bottom - info.srWindow.Top + 1
    };
    SetConsoleScreenBufferSize(handle, new_size);
}

void DisableMinimizeButton(HWND hwnd) {
	SetWindowLong(hwnd, GWL_STYLE,
	GetWindowLong(hwnd, GWL_STYLE) & ~WS_MINIMIZEBOX);
}

void DisableMaximizeButton(HWND hwnd) {
	SetWindowLong(hwnd, GWL_STYLE,
	GetWindowLong(hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX);
}

void display(string s){
	system("CLS");
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	ifstream file(s.c_str());
	string t;
	COLOR(11);
	cout<<endl;
	centerstring(s.substr(4,10));
	cout<<endl<<endl<<endl;
	COLOR(7);
	while(getline(file,t)) cout<<t<<endl<<endl;
	cout<<"  ";
	cin.get();
	cin.get();
	system("CLS");
	return;
}

bool solved(){
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(pro[j][i]==0) return false;
		}
	}
	for(int i=0;i<9;i++){
		for(int k=1;k<=9;k++){
			for(int j=0;j<=9;j++){
				if(j==9) return false;
				if(pro[j][i]==k) break;
			}
		}	
	}
	for(int j=0;j<9;j++){
		for(int k=1;k<=9;k++){
			for(int i=0;i<=9;i++){
				if(i==9) return false;
				if(pro[j][i]==k) break;
			}
		}	
	}
	for(int b=0;b<9;b++){
		for(int s=1;s<=9;s++){
			for(int x=b%3*3;x<b%3*3;x++){
				for(int y=b/3*3;y<=b/3*3+3;y++){
					if(pro[x][y]==s) break;
					if(y==b/3*3) return false;
				}
			}
		}
	}
	return true;
}

void gohere(){
	thegreatfunction();
	
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++) pro[j][i]=ans[j][i];
	}
	
	bool invalid=false;
	while(true){
		system("CLS");
		COLOR(10);
		cout<<endl;
		centerstring("THE SUDOKU PUZZLE (Difficulty: "+to_string(diff)+")");
		cout<<endl<<endl;
		SPACE(12);
		COLOR(111);
		for(char i='A';i<'A'+9;i++) cout<<"  "<<i<<"  ";
		cout<<endl;
		COLOR(7);
		SPACE(8);
		COLOR(111);
		SPACE(3);
		COLOR(7);
		SPACE(1);
		cout<<endl;
		int c=1;
		for(int i=0;i<9;i++){
			COLOR(7);
			COLOR(7);
			SPACE(8);
			COLOR(111);
			cout<<" "<<i+1<<" ";
			COLOR(7);
			SPACE(1);
			for(int j=0;j<9;j++){
				if(ans[j][i]!=0) COLOR(11+(j/3+i/3*3)%2*16);
				else COLOR(15+(j/3+i/3*3)%2*16);
				cout<<"  "<<pro[j][i]<<"  ";
			}
			cout<<endl;
			COLOR(7);
			SPACE(8);
			COLOR(111);
			SPACE(3);
			COLOR(7);
			SPACE(1);
			if(c>=4&&c<=6){
				COLOR(23);
				SPACE(15);
				COLOR(7);
				SPACE(15);
				COLOR(23);
				SPACE(15);
				c++;
			}
			else{
				COLOR(7);
				SPACE(15);
				COLOR(23);
				SPACE(15);
				COLOR(7);
				SPACE(15);
				c++;
			}
			cout<<endl;
		}
		
		cout<<endl;
		if(solved()) break;
		
		if(invalid){
			COLOR(12);
			centerstring("ERROR: Please check your input and try again.");
		}
		COLOR(7);
		
		cout<<endl<<endl;
		
		char cn,rn,vn;
		centerstring("Enter Column Letter: ");
		cin>>cn;
		if(cn=='/'){
			centerstring("Give Up? (y/n): ");
			char coward;
			cin>>coward;
			if(coward=='y'){
				system("CLS");
				return;
			}
			else if(coward=='n') continue;
			else{
				invalid=true;
				continue;
			}
		}
		centerstring("Enter Row Number: ");
		cin>>rn;
		centerstring("Enter Value: ");
		cin>>vn;
		cn-='A';
		cn++;
		rn-='0';
		vn-='0';
		if(cn<1||cn>9||rn<1||rn>9||vn<0||vn>9||ans[cn-1][rn-1]!=0){
			invalid=true;
			continue;
		}
		else{
			pro[cn-1][rn-1]=vn;
			invalid=false;
		}
	}
	COLOR(14);
	centerstring("Congratulations! You have solved the puzzle.");
	cout<<endl;
	SPACE(7);
	cin.get();
	cin.get();
	system("CLS");
}

int main(){
	HWND hwnd = GetConsoleWindow();
	if(hwnd != NULL && first) MoveWindow(hwnd, 120, 100, 600, 525, TRUE);
	remove_scrollbar();
	DisableMinimizeButton(hwnd);
	DisableMaximizeButton(hwnd);
	
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	srand(time(NULL));
	
	cout << endl;
	COLOR(10);
	ifstream logo("txt/logo.txt");
	string t;
	while (getline(logo, t)){
		centerstring(t);
		cout << endl;
	}
	logo.close();
	COLOR(11);
	cout<<endl;
	centerstring("The Classic Game");
	cout<<endl<<endl;
	COLOR(7);
	rightstring("Copyright 2019 wlhcode");
	cout<<endl<<endl;
	if(!first) cout<<endl;
	first=false;
	COLOR(15);
	centerstring("1. START GAME");
	cout<<endl<<endl;
	centerstring("2. ABOUT GAME");
	cout<<endl<<endl;
	centerstring("3. LEARN MORE");
	cout<<endl<<endl<<endl;
	COLOR(7);
	centerstring("Type in the number to select the corresponding mode:  ");
	cout<<"\b";
	int a;
	cin>>a;
	if (a<1||a>3){
		cout<<endl;
		COLOR(12);
		centerstring("ERROR: INVALID INPUT. ABORTING PROGRAMME.");
		cout<<endl;
		centerstring("The input must be an integer between 1 and 3.");
		cout<<" ";
		COLOR(7);
		cin.get();
		cin.get();
		return 0;
	}
	else{
		if(a==1){
			cout<<endl;
			centerstring("Loading . . .");
			gohere();
		}
		else if(a==2) display("txt/ABOUT GAME.txt");
		else if(a==3) display("txt/LEARN MORE.txt");
		main();
	}
}
