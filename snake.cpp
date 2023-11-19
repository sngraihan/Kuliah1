#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ncurses/ncurses.h>
using namespace std;

int maxY, maxX;
bool game = true;
char arah = 'w';
int x, y;
int score=0;
int fruitx, fruity;
int ekor = 1;
int ekorx[100], ekory[100];


void draw(){
	WINDOW * win = newwin(maxY, maxX, 0, 0);
	refresh();
	
	box(win, 0, 0);
	wrefresh(win);
	mvprintw(y, x, "0");
	mvprintw(fruity, fruitx, "Q");
	for(int i=0;i<ekor;i++){
		mvprintw(ekory[i], ekorx[i], "o");
	}
	refresh();
	if(arah == 'a')Sleep(35);
	if(arah == 'd')Sleep(35);
	if(arah == 'w' || arah == 's')Sleep(100);
}

void console(){
	if(kbhit()){
	switch(getch()){
		case 'a' : if(arah!='d')arah = 'a'; break;
		case 'w' : if(arah!='s')arah = 'w'; break;
		case 's' : if(arah!='w')arah = 's'; break;
		case 'd' : if(arah!='a')arah = 'd'; break;
		case 'q' : game=false; break;
	}
}
}

void algorithm(){
	int prevx = ekorx[0];
	int prevy = ekory[0];
	int prevx2, prevy2;
	ekorx[0] = x;
	ekory[0] = y;
	
	for(int i=1; i<ekor; i++){
		prevx2 = ekorx[i];
		prevy2 = ekory[i];
		ekorx[i] = prevx;
		ekory[i] = prevy;
		prevx = prevx2;
		prevy = prevy2;
	}
	
	if(arah=='a')x--;
	if(arah=='d')x++;
	if(arah=='s')y++;
	if(arah=='w')y--;
	if(fruitx==x && fruity==y){
	fruitx = rand()%maxX;
	fruity = rand()%maxY;
	score++;
	ekor++;
	}
	for(int i = 0; i<ekor; i++){
		if(ekorx[i] == x && ekory[i] == y){
			game = false;
		}	
	}
	
	if(x <= 0 || x >=maxX || y<=0 || y>= maxY){
		game = false;
	}
	
}

int main(){

	initscr();
	noecho();
	curs_set(0);
	
	getmaxyx(stdscr,maxY,maxX);
	x=maxX/2, y=maxY/2;
	fruitx = rand()%maxX;
	fruity = rand()%maxY;
	
	do{
		draw();
		console();
		algorithm();
	}while(game);
	
	clear();
	mvprintw(9, 50, "GAME OVER ANDA CUPU");
	mvprintw(10, 50, "score anda adalah %d", score);
	refresh();
	getch();
	endwin();
	
	return 0;
}
