//Author: Jaswin S. Kohli

#include<fstream.h>		//for file handling
#include<conio.h>		//for clrscr() and getch()
#include<math.h>		//for power and trigonometric functions
#include<string.h>		//for strcpy
#include<graphics.h>
#include<stdlib.h>		//for random,randomize
#include<stdio.h>		//for gets,puts
#include<iomanip.h>		//for setw
#include<dos.h>			//for delay()
#define c (3.14/180)		//for converting angle into radians

struct tankdat{	int x,y,k,u,m,l,s;		//x,y:coordinates, k:angle of turret, u:power
		char name[20];			//m: no of moves, l:color of tank, s:score
		};

class hscore{	char name[20];
		int score;
		public:
		hscore()
		{       strcpy(name,"Player");
			score=100;
		}
		hscore(tankdat t)
		{	strcpy(name,t.name);
			score=t.s;
		}
		int getscore()
		{	return score;
		}
		void display()
		{	cout<<"\n\t"<<name;
			cout<<"\t\t"<<score;
		}
	}rank[7];

const int max=100;
tankdat t1={200,349,60,20,4,3,0,"Player1"};	//initialising values
tankdat t2={400,349,60,20,4,6,0,"Player2"};

int control=1,r=3;

void menu();
void tank(int x, int y, int k, int l);
void arrow(int x, int y);
void game();
void impact(int , int );
void score(int);
void winner();
void highscore(tankdat);
/***************************************************************************
menu(): Function to display Menu items.

tank(): Function to draw the tank.

arrow(): Function to display an arrow over the tank whose chance it is.

game(): Function which displays the setup of the game after each move.

impact(): Function which shows the impact after a missile has been launched.

score(): Function to calculate and increment the score according to point of impact.

winner(): Function to compare the scores of players and declare the winner.

highscore(): Function which checks to see if either of the players has created a new record.

*****************************************************************************/

void tank(int x,int y,int k,int l)
{
setcolor(l);
setfillstyle(4,l);
for(int i=0;i<4;i++)			//wheels of the tank
{	circle(x+2*r*i,y-r-1,r);
	floodfill(x+2*r*i,y-r-1,l);
}
line(x,y-2*r,x+r,y-4*r);
line(x+r,y-4*r,x+5*r,y-4*r);
line(x+5*r,y-4*r,x+6*r,y-2*r);
line(x+3*r,y-4*r,(x+3*r)+r*4*cos(k*c),(y-4*r)-r*4*sin(k*c));	//tank turret
setfillstyle(2,l);
floodfill(x+3*r,y-3*r,l);
setcolor(63);
return;
}

void arrow(int x, int y)
{       setcolor(57);
	line(x+r,y-75,x+r,y-50);
	line(x+3*r,y-75,x+3*r,y-50);
	line(x+r,y-75,x+3*r,y-75);
	line(x-r,y-50,x+r,y-50);
	line(x+3*r,y-50,x+5*r,y-50);
	line(x-r,y-50,x+2*r,y-35);
	line(x+5*r,y-50,x+2*r,y-35);
	setcolor(63);
	return;
}

void game()
{
cleardevice();
int x=getmaxx()/2;
int y=getmaxy()/2;
int xp=0,yp=y+170;
setcolor(58);
line(0,y+110,x*2,y+110);		//Ground over which tanks move
setcolor(63);
gotoxy(1,1);
puts(t1.name);
gotoxy(1,2);
cout.setf(ios::left);
cout<<setw(5)<<t1.s;		//Display Score
gotoxy(1,3);
cout<<"Moves Left";
gotoxy(1,4);
cout<<t1.m;
gotoxy(61,1);
cout.setf(ios::right);
cout<<setw(20)<<t2.name;
gotoxy(76,2);
cout.setf(ios::right);
cout<<setw(5)<<t2.s;		//Display Score
gotoxy(61,3);
cout.setf(ios::right);
cout<<setw(20)<<"Moves Left";
gotoxy(80,4);
cout<<t2.m;
gotoxy(1,4);
cout<<t1.m;
gotoxy(1,23);
cout<<"Angle ";
gotoxy(1,24);
cout<<t1.k;
gotoxy(76,23);
cout<<"Angle";
gotoxy(78,24);
cout<<setw(3)<<t2.k;
setfillstyle(1,4);
gotoxy(1,25);
cout<<"Power";
rectangle(xp,yp-2,xp+164,yp+10);	//Display Power
bar(xp,yp,xp+(2*t1.u),yp+8);
gotoxy(76,25);
cout<<"Power";
rectangle(x*2,yp-2,x*2-164,yp+10);	//Display Power
bar(x*2,yp,x*2-(2*t2.u),yp+8);
if(control==1)			//Switching control
arrow(t1.x,t1.y);
else if(control==2)
arrow(t2.x,t2.y);
tank(t1.x,t1.y,t1.k,t1.l);
tank(t2.x,t2.y,180-t2.k,t2.l);
return;
}

void impact(int x,int y)
{       for( int i=1;i<=10;i++)
	{       cleardevice();
		if(control==1)
		{	if(abs(t2.x-x)<100)
			tank(t2.x-random(20),t2.y-random(20),180-t2.k,t2.l);
		}
		else if(control==2)
		{	if(abs(t1.x-x)<100)
			tank(t1.x-random(20),t1.y-random(20),t1.k,t1.l);
		}
		delay(50);
		game();
		setcolor(i);
		circle(x,y,i*10);
		delay(100);
	}
	setcolor(63);
	return;
}

void score(int x)
{       int s;
	if(control==1)
	{       s=max-abs(t2.x-x);		//evaluating distance of tank from impact point
		if(s<0)
		t1.s+=0;			//updating score
		else t1.s+=pow(s,2)/10;
		s=max-abs(t1.x-x);
		if(s<0)
		t1.s-=0;
		else t1.s-=s;
		return;
	}
	else
	{	s=max-abs(t1.x-x);		//evaluating distance of tank from impact point
		if(s<0)
		t2.s+=0;			//updating score
		else t2.s+=pow(s,2)/10;
		s=max-abs(t2.x-x);
		if(s<0)
		t2.s-=0;
		else t2.s-=s;

		return;
	}
}

void winner()			//evaluation of winner and displaying it
{       int w;
	settextstyle(7,0,2);
	if(t1.s>t2.s)
	{	w=textwidth(t1.name);
		outtextxy(t1.x-w,t1.y-150,t1.name);
		outtextxy(t1.x,t1.y-150," Wins!!!");
	}
	else if(t1.s<t2.s)
	{	w=textwidth(t2.name);
		outtextxy(t2.x-w,t2.y-150,t2.name);
		outtextxy(t2.x,t2.y-150," Wins!!!");
	}
	else
	outtextxy(getmaxx()/2-30,getmaxy()/2,"DRAW!!!");
	return;
}

void highscore(tankdat t3)		//Function to update high score records
{       fstream fio;
	hscore temp;
	int i=0;
	fio.open("highscore.txt",ios::in|ios::out|ios::binary);
	for(i=0;i<7;i++)
	fio.read((char*)&rank[i],sizeof(rank[i]));		//retrieving current values
	for(i=0;i<7;i++)
	{	if(rank[i].getscore()<t3.s)		//inserting the new highscore
		{       hscore temp2(t3);
			for(int j=6;j>i;j--)
			rank[j]=rank[j-1];
			rank[i]=temp2;
			break;
		}
	}
	fio.seekp(0);
	for(i=0;i<7;i++)
	fio.write((char*)&rank[i],sizeof(rank[i]));		//Updating new values in record
	fio.close();
	return;
}

void menu()
{int v;
int x=getmaxx()/2;
int y=getmaxy()/2;
r=10;
for(v=100;v<=x-25;v+=3)			//loop to show moving tank animation
{
cleardevice();
tank(x*2-v,t2.y/2,180-t2.k,60);
tank(v,t1.y/2,t1.k,57);
setlinestyle(0,0,3);
setcolor(60);
line(x*2-v+3*r,t2.y/2-4*r,(x*2-v+3*r)+r*4*cos((180-t2.k)*c),(t2.y/2-4*r)-r*4*sin((180-t2.k)*c));
setcolor(57);
line(v+3*r,t2.y/2-4*r,(v+3*r)+r*4*cos(t1.k*c),(t1.y/2-4*r)-r*4*sin(t1.k*c));
setcolor(63);
setlinestyle(0,0,0);
delay(40);
}
for(int i=3;i<=7;i++)
{
cleardevice();
tank(x+25,t2.y/2,180-t2.k,60);
tank(x-25,t1.y/2,t1.k,57);
setlinestyle(0,0,3);
setcolor(60);
line(x+25+3*r,t2.y/2-4*r,(x+25+3*r)+r*4*cos((180-t2.k)*c),(t2.y/2-4*r)-r*4*sin((180-t2.k)*c));
setcolor(57);
line(x-25+3*r,t2.y/2-4*r,(x-25+3*r)+r*4*cos(t1.k*c),(t1.y/2-4*r)-r*4*sin(t1.k*c));
setcolor(63);
setlinestyle(0,0,0); //setuserchar size
settextstyle(4,0,i);
v=textwidth("Pocket Tanks!!!");
outtextxy(x-v/2,y-50,"Pocket Tanks!!!");		//loop to zoom in "pocket tanks"
delay(300);
}
settextstyle(11,0,1);
outtextxy(x,y*2-40,"Developers: Jaswin S. Kohli");
outtextxy(x+100,y*2-25,"Niladri Sanyal");
settextstyle(0,0,0);
r=3;
getch();
int ch=-1;
menu:
gotoxy(40,18);
if(ch!=-1) gotoxy(1,1);
cout<<"\n\t\t\t\tMENU: ";		//Displaying Menu
cout<<"\n\t\t\t1.Play";
cout<<"\n\t\t\t2.High Scores";
cout<<"\n\t\t\t3.How to Play";
cout<<"\n\t\t\t4.Exit";
cout<<"\n\n\t\t\tEnter your choice: ";
cin>>ch;
switch(ch)
{	case 1: cleardevice();		//User input of player information
		gotoxy(1,1);
		cout<<"\n\tPlayer 1 ";
		cout<<"\n\tPlayer name: ";
		gets(t1.name);
		cout<<"\n\tTank colour: \n";
		int j;
		for(i=1,v=100,j=14;i<=5;v+=103,i++,j+=13)
		{	tank(v,y-120,t1.k,i+56);
			gotoxy(j,9);
			cout<<i;
		}
		gotoxy(22,5);
		cin>>t1.l;
		t1.l+=56;
		cout<<"\n\n\n\n\n\n\tPlayer 2 ";
		cout<<"\n\tPlayer name: ";
		gets(t2.name);
		cout<<"\n\tTank colour: ";
		for(i=1,v=100,j=14;i<=5;v+=103,i++,j+=13)
		{	tank(v,y+40,t1.k,i+56);
			gotoxy(j,19);
			cout<<i;
		}
		gotoxy(22,15);
		cin>>t2.l;
		t2.l+=56;
		break;
	case 2: cleardevice();		//Retrieving and displaying High Scores
		gotoxy(1,1);
		ifstream fin;
		fin.open("highscore.txt",ios::in|ios::binary);
		if(!fin)
		{       ofstream fout("highscore.txt");
			for(i=0;i<7;i++)
			fout.write((char*)&rank[i],sizeof(rank[i]));
			fout.close();
		}
		gotoxy(36,1);
		cout<<"HIGH SCORES"<<endl;
		for(i=0;i<7;i++)
		{	fin.read((char*)&rank[i],sizeof(rank[i]));
			rank[i].display();
		}
		fin.close();
		cout<<"\n\nPress any key to return to main menu!";
		getch();
		cleardevice();
		goto menu;
	case 3: cleardevice();
		gotoxy(1,1);
		cout<<"Objective\nThe Objective of the game is to score more than the enemy tank by targeting the missile closest to the enemy tank. As a tank\s weakest spot are its wheels, the maximum points are obtained by aiming the missile to the leftmost wheel of the enemy tank. However there is a catch: if you hit too near to your own tank, you lose points. The player who bags the maximum points, in 5 chances, with most accurate hits wins the game.";
		cout<<"\n\nStrategy\nYou need to hit the target by choosing the power with which the missile will be launched i.e. the range of the missile. Also, you need to specify the angle of elevation of turret such that the missile hits the enemy tank. In the end, you can alter position of the tank to your advantage. You may move it away from the enemy tank if it has locked in on your position. Or you may seek the enemy tank to cause more damage to it. However, you cannot move the tank after you have fired or the other person has fired the missile.";
		cout<<"\n\n\tCONTROLS:\n";
		cout<<"\n\tIncrease Angle: w";
		cout<<"\n\tDecrease Angle: s";
		cout<<"\n\tIncrease Power: d";
		cout<<"\n\tDecrease Power: a";
		cout<<"\n\tMove Left: z";
		cout<<"\n\tMove Right: x";
		cout<<"\n\tFire: space bar";
		cout<<"\n\tExit game: p";
		cout<<"\n\n\tCAUTION: CAPS LOCK MUST BE OFF!\n\t";
		cout<<"Press any key to return to main menu!";
		getch();
		cleardevice();
		goto menu;
	case 4: exit(0);
};
return;
}

void main()
{
clrscr();
char ch[2]={"n"};
int a=DETECT,b;
initgraph(&a,&b,"C:\\TC\\BGI");	//initialising graph
menu();				//function call to menu
int xf,yf;
start: game();			//Game begins
for(int j=1;j<=10;)
{int keys=getch();
if(control==1)
{
xf=(t1.x+3*r)+18*cos(t1.k*c);
yf=(t1.y-4*r)-18*sin(t1.k*c);
}
else
{
xf=(t2.x+3*r)-18*cos(t2.k*c);
yf=(t2.y-4*r)-18*sin(t2.k*c);
}
 switch(keys)
{       case 'z':if(control==1)				//to move the tank backwards and forwards
		 {	if(t1.m>0)
			{	for(int i=0;i<25;i++)
				{	t1.x-=1;
					game();
					delay(100);
				}
				t1.m--;				//Decrementing no. of moves
			}
		 xf=(t1.x+3*r)+20*cos(t1.k*c);
		 }
		 if(control==2)
		 {	if(t2.m>0)
			{	for(int i=0;i<25;i++)
				{	t2.x-=1;
					game();
					delay(100);
				}
				t2.m--;
			}
		 xf=(t2.x+3*r)-20*cos(t2.k*c);
		 }
		 game();
		 break;
	case 'x':if(control==1)
		 {	if(t1.m>0)
			{	for(int i=0;i<25;i++)
				{	t1.x+=1;
					game();
					delay(100);
				}
				t1.m--;
			}
		 xf=(t1.x+3*r)+20*cos(t1.k*c);
		 }
		 if(control==2)
		 {	if(t2.m>0)
			{	for(int i=0;i<25;i++)
				{	t2.x+=1;
					game();
					delay(100);
				}
				t2.m--;
			}
		 xf=(t2.x+3*r)-20*cos(t2.k*c);
		 }
		 game();
		 break;
	case 'w':if(control==1)			//increasing and decreasing angle
		 {      if(t1.k<89) ++t1.k;
			else continue;
		 }
		 else if(control==2)
		 {	if(t2.k<89) ++t2.k;
			else continue;
		 }
		 game();
		 break;
	case 's':if(control==1)
		 {      if(t1.k>0) --t1.k;
			else continue;
		 }
		 else if(control==2)
		 {	if(t2.k>0) --t2.k;
			else continue;
		 }
		 game();
		 break;
	case 'a':if(control==1)			//increasing and decreasing power
		 {      if(t1.u>2) --t1.u;
			else continue;
		 }
		 else if(control==2)
		 {	if(t2.u>2) --t2.u;
			else continue;
		 }
		 game();
		 break;
	case 'd':if(control==1)
		 {      if(t1.u<=80) ++t1.u;
			else continue;
		 }
		 else if(control==2)
		 {	if(t2.u<=80) ++t2.u;
			else continue;
		 }
		 game();
		 break;
	case ' ':int posy=yf;			//Firing missile
		 if(control==1)
		 {
		 for(int i=0,j;yf<350;i++,xf++)		//loop to calculate and display projectile path of missile
		 {
		 randomize();
		 j=57+random(5);
		 setfillstyle(7,j);
		 setcolor(j);
		 circle(xf,yf,1);
		 floodfill(xf,yf,j);
		 yf=(posy-(i*tan(t1.k*c)))+((5*pow(i,2))/(pow(t1.u,2)*pow(cos(t1.k*c),2)));
		 delay(10);
		 }
		 }
		 else
		 {
		 for(int i=0,j;yf<350;i++,xf--)
		 {
		 randomize();
		 j=57+random(5);
		 setfillstyle(7,j);
		 setcolor(j);
		 circle(xf,yf,1);
		 floodfill(xf,yf,j);
		 yf=(posy-(i*tan(t2.k*c)))+((5*pow(i,2))/(pow(t2.u,2)*pow(cos(t2.k*c),2)));
		 delay(10);
		 }
		 }
		 impact(xf,yf);		//function call to show impact
		 score(xf);			//function call to update scores
		 if(control==1)		//Switching control of players
		 {
		 control=2;
		 yf=(t2.y-4*r)-20*sin(t1.k*c);
		 game();
		 }
		 else
		 {
		 control=1;
		 yf=(t2.y-4*r)-20*sin(t1.k*c);
		 game();
		 }
		 j++;
		 break;
	case 'p':j=11;
		 break;

};
}
winner();
highscore(t1);		//function call to check for new highscore
highscore(t2);
outtextxy(getmaxx()/2-120,getmaxy()/4,"Want to play again??(y/n)!");
int w=textwidth("Want to play again??(y/n)!");
ch[0]=char(getch());
outtextxy(getmaxx()/2-120+w,getmaxy()/4,ch);
getch();
if(ch[0]=='y')			//reseting the game
{       t1.x=200,t1.y=349,t1.k=60,t1.u=20,t1.m=3,t1.s=0;
	t2.x=400,t2.y=349,t2.k=60,t2.u=20,t2.m=3,t2.s=0;
	goto start;
}
else;
//closegraph();
}











