#include<iostream>
#include<conio.h>   
#include<stdio.h>
#include<fstream>
#include<string>
#include<ctype.h>

using namespace std;

const int width = 35;
const int height = 15;
bool gameover;
enum ed { stop = 0, UP, DOWN, LEFT, RIGHT }; //for moving head.
ed dir; 
int x, y; //head pos.
int fx, fy; //fruit pos.
int tx[100], ty[100];  //val of prev. segment.
int tl;      //length of tail.
int cnt, cnt1;          //player count
int flag=0;      //for gamemode 1  or 2

fstream f, f1;

char username[30], password[30];

class snakegame
{
private:

	char username1[30], password1[30];
	int score; //score val.

public:

	void draw();
	void logic();
	void input();
	
	void setscr()
	{

		score = 0;
	}

	int retscr()
	{
		return(score);
	}

	void getu1()
	{
		if (flag == 1)
		{
			if (flag == 3)
				;
			else
				cnt++;
		}
		else if (flag == 2)
		{
			if (flag == 3)
				;
			else
				cnt1++;
		}

		cout << "\n\t\t\t\t\tEnter Player UserName To Be Registered : ";
		cin >> username1;
	}

	void getp1()
	{
		cout << "\n\t\t\t\t\tEnter User Password : ";
		cin >> password1;
	}

	void getu()
	{
		strcpy_s(username, username1);   //for writing-signup
	}

	void getp()
	{
		strcpy_s(password, password1);   //for writing-signup
	}

	char* retu1()
	{
		return(username1);     //for comparing-login
	}

	char* retp1()
	{
		return(password1);      //for comparing-login
	}

	void disp2();
	void disp1();

}s;

void snakegame::disp1()
{
	f.open("disp1.dat", ios::in | ios::binary);
	while (!f.eof())
	{
		if (f.is_open())
			cout << f.rdbuf();        //function to display everthing in file.
		if(!f)
			cout << "\n\t\t\t\t\t\tNo Registered Users Found! ";
		break;
	}
	f.close();
}

void snakegame::disp2()
{
	f.open("disp2.dat", ios::in | ios::binary);
	while (!f.eof())
	{ 
		if(f.is_open())
			cout << f.rdbuf();        //function to display everthing in file.
		if (!f)
			cout << "\n\t\t\t\t\t\tNo Registered Users Found! ";
		break;
	}
	f.close();
}


void setup()                           //initializing values.
{
	tl = 0;
	dir = stop;
	x = width / 2;
	y = height / 2;
	fx = rand() % width; //zero to 39.
	fy = rand() % height; //zero to 19.
}

void snakegame::draw()
{
	system("cls");

	if (flag == 2)
	{
		cout << "(Press 0 to Exit to main Menu)\n\n";
		cout << "\t\t\t\t\t\t\tGAME MODE 2\n\n";
		cout << "\t\t\t\t\t\t      WIHTOUT BORDER!!\n\n";
	}
	else if (flag == 1)
	{
		cout << "(Press 0 to Exit to main Menu)\n\n";
		cout << "\n\n\t\t\t\t\t\t\tGAME MODE 1\n\n";
		cout << "\t\t\t\t\t\t       WITH BORDER!!\n\n";
	}

	for (int i = 0; i <= width+1; i++)    //top border.
		cout << "#";
	cout << "\n";

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)          //left border
				cout << "#";

			if (i == y && j == x)              //snake head
				cout << "O";

			else if (i == fy && j == fx)        //fruit cout
				cout << "B";
			else
			{
				bool print = false;

				for (int k = 0; k < tl; k++)       //print tail
				{ 
					if (tx[k] == j && ty[k] == i)    //checking to print tail behind head
					{
						cout << "o";
						print = true;

					}
				}
				if (print == false)
					cout << " ";
			}

			if (j == width - 1)         //right border
				cout << "#";

		}
		cout << "\n";

	}

	for (int i = 0; i <= width+1; i++)     //bottom border
	{
		cout << "#";

	}
	cout << "\n\n\n\n\t\t\t\t\t S C O R E : " << score << endl;



}

void snakegame::input()
{
	if (_kbhit())             //returns: pressed- +ve ; not pressed- zero
	{
		switch (_getch())             //returns ascii value of what key is pressed
		{
		case 'a':
			dir = LEFT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case '0':            //exits to main menu
			gameover = true;
			break;

		}
	}
}

void snakegame::logic()                   //without border death.
{
	int px = tx[0];  //prev.
	int py = ty[0];  //prev.
	int pnx, pny;
	tx[0] = x;
	ty[0] = y;

	for (int i = 1; i < tl; i++)    //tracking and printing tail.
	{
		pnx = tx[i];
		pny = ty[i];
		tx[i] = px;
		ty[i] = py;
		px = pnx;
		py = pny;

	}

	switch (dir)        //moving head.
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
			   
	}

	if (flag == 2)                         //without border
	{
		if (x > width)
		{
			x = 0;
		}

		if (x < 0)
		{
			x = width - 1;
		}

		if (y < 0)
		{
			y = height - 1;
		}

		if (y > height)
		{
			y = 0;
		}

		for (int i = 1; i < tl; i++)
		{
			if (x == tx[i] && y == ty[i])
			{
				gameover = true;
				system("PAUSE");
				system("cls");
				cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\tG A M E   O V E R!!!\n\n";
				cout << "\n\t\t\t\t\t\t    S C O R E : " << score << "\n\n";
				system("PAUSE");
			}
		}

		if (x == fx && y == fy)         //eating fruit.
		{
			score += 1;
			fx = rand() % width;
			fy = rand() % height;
			tl++;                      // increasing tail length.
		}
	}
	else if (flag == 1)              //with border   
	{
		if (x > width || x < 0 || y<0 || y>height) 
		{
			gameover = true;

			system("cls");
			cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\tG A M E   O V E R !!!\n\n";
			cout << "\n\t\t\t\t\t\t    S C O R E : " << score << "\n\n";
			system("PAUSE");
		}

		for (int i = 1; i < tl; i++)
		{
			if (x == tx[i] && y == ty[i])
			{
				gameover = true;
				system("PAUSE");
				system("cls");
				cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\tGAME OVER!!!\n";
				cout << "\n\t\t\t\t\t\t    S C O R E : " << score << "\n\n";
				system("PAUSE");
			}
		}

		if (x == fx && y == fy)         //eating fruit.
		{
			score += 1;
			fx = rand() % width;
			fy = rand() % height;
			tl++;                      // increasing tail length.
		}
	}

}

int main()
{
	int op, op1,op2,op3;
	char ch[30], pw[30];
	int lcheck; //for login
	int log;   //to check for login
	int score;  //to write score
	streampos oldpos[100],oldpos1[100];  //holds pos for updating score system
	int l = 0, k = 0;
	int j = 0;

		do
		{ 
		main:

			system("cls");
			cout << "\n\n\t\t\t\t\t\t      A PROJECT BY:\n\n";
			cout << "\t\t\t\t\t\t    S.P. PRAVEEN KUMAR\n\n";
			cout << "\t\t\t\t\t\t        SNAKE GAME\n";
			cout << "\n\n\n\t\t\t\t\t       Enter Preferred Game mode:\n\n";
			cout << "\t\t\t\t\t\t 1] GAME MODE 1 - With Border Game:\n\n";
			cout << "\t\t\t\t\t\t 2] GAME MODE 2 - Without Border Game:\n\n";
			cout << "\t\t\t\t\t\t 3] Display All Player Details:\n\n";
			cout << "\t\t\t\t\t\t 4] Exit Game!\n\n";
			cout << "\t\t\t\t\t\t   YOUR CHOICE : ";
			cin >> op;

			switch (op)
			{
			case 1:                                         //game mode 1

				system("cls");
			sgn1:

				cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t       Enter Option:\n\n";
				cout << "\t\t\t\t\t\t\t 1] Sign Up:\n\n";
				cout << "\t\t\t\t\t\t\t 2] Login:\n\n";
				cout << "\t\t\t\t\t\t\t 3] Exit to Main Menu\n\n";
				cout << "\t\t\t\t\t\t\tYOUR CHOICE : ";
				cin >> op1;

				switch (op1)
				{
				case 1:                                         //signing up

					system("cls");

				signup1:

					log = 0;

					f.open("gamemode1.dat", ios::out | ios::binary | ios::cur);

					cout << "\n\n\t\t\t\t\t\t    SIGNING UP ";
					cout << "\n\t\t\t\t\t\t    ~~~~~~~~~~\n\n";

					if(flag!=3)     //not to increment when non matching details entered for getu1.
						flag = 1;
					s.getu1();               //for copy
					s.getp1();               //for copy
					cout << "\n\t\t\t\t\tRe-Enter Player UserName : ";
					cin >> ch;                //for checking
					cout << "\n\t\t\t\t\tRe-Enter Password : ";
					cin >> pw;

					if (strcmp(s.retu1(), ch) != 0 || strcmp(s.retp1(), pw) != 0)      //to check if user name and passwords match
					{
						cout << "\n\t\t\t\tUserNames / Passwords Do Not MATCH! Try Again!\n\n\n";
						system("PAUSE");
						system("cls");
						flag = 3;
						f.close();
						goto signup1;
					}

					while (!f.eof())
					{
						f.read((char*)& ch, sizeof(s));
						if (strcmp(username,ch) == 0)
						{
							cout << "\n\t\t\t\tSorry, Entered UserName Already Exists! Try Again!!\n\n";
							system("PAUSE");
							system("cls");
							f.close();
							goto signup1;
						}
						j++;
						if (j >= cnt)
							break;
					}
					f.close();

					cout << "\n\t\t\t\tSuccessfully registered! You May Now proceed to playing!\n\n\n";

					f1.open("gamemode1.dat", ios::out | ios::binary | ios::app);       //store everything
					s.getu();
					s.getp();
					f1 << "\t\t\t\t" << cnt << "] USERNAME: " << username << "\t" << "PASSWORD: " << password; //writing in file.
					f1.close();

					f1.open("disp1.dat", ios::out | ios::binary | ios::app);      //for disp
					f1 << "\t\t\t\t" << cnt << "] USERNAME: " << username; //writing in file.
					f1.close();
					system("PAUSE");

					break;

				case 2:                                   //logging in

				login1:

					lcheck = 0;
					log = 1;
					system("cls");
					cout << "\n\n\t\t\t\t\t\t    LOGING IN ";
					cout << "\n\t\t\t\t\t\t    ~~~~~~~~~\n\n";

					f.open("gamemode1.dat", ios::in | ios::binary);

					if (f.tellg() != '\0')             //to check if there are no users present
					{
						cout << "\n\t\t\t\t\t\tNo Registered Users Found!\n\n ";
						system("PAUSE");
						system("cls");
						f.close();
						goto signup1;
						break;
					}

					cout << "\n\t\t\t\t\tEnter Player UserName : ";
					cin >> ch;
					cout << "\n\t\t\t\t\tEnter User Password : ";
					cin >> pw;

					while (!f.eof())
					{
						if (strcmp(ch, s.retu1()) == 0 && strcmp(pw, s.retp1()) == 0)
						{
							cout << "\n\n\t\t\t\tSuccessfully Logged In! You May Now Proceed To Playing!\n\n\n";
							system("PAUSE");
							break;
						}
						else
						{
							lcheck = 1;
							break;
						}
					}
					f.close();

					if (lcheck == 1)
					{
						cout << "\n\n\t\t\t\tEntered Details Does Not Match With Existing Details! Try Again!\n\n\n";
						system("PAUSE");
						system("cls");
						f.close();
						goto login1;
					}

					break;

				case 3:

					system("pause");
					goto main;
					break;

				default:
					cout << "\nYou Have Entered an Wrong Input! Try Again!!\n\n\n";
					system("PAUSE");
					system("cls");
					goto sgn1;
				}

				setup();
				system("cls");
				cout << "\n\n\t\t\t\t\t         RULES:\n\n";
				cout << "\t\t\t\t   1)Touch Head To Border --> DEATH!\n";
				cout << "\t\t\t\t   2)Go In Direct Reverse Direction -->> DEATH!\n";
				cout << "\t\t\t\t   3)Touch Head To Tail --> DEATH!\n";

				cout << "\n\n\t\t\t\t\t        CONTROLS:\n\n";
				cout << "\t\t\t\t    W --> Upwards\n";
				cout << "\t\t\t\t    A --> Left\n";
				cout << "\t\t\t\t    S --> Downwards\n";
				cout << "\t\t\t\t    D --> Right\n";

				cout << "\n\n\t\t\t\t\t        DIAGRAM:\n\n";
				cout << "\t\t\t\t    O o o o o o o o          B\n";
				cout << "\t\t\t\t    ^       ^                ^\n";
				cout << "\t\t\t\t    |       |                |\n";
				cout << "\t\t\t\t    |       |                |\n";
				cout << "\t\t\t\t   HEAD    TAIL            FRUIT\n\n";

				system("PAUSE");
				system("cls");

				s.setscr();
				gameover = false;
				flag = 1;
				while (!gameover)
				{
					s.draw();
					s.input();
					s.logic();
				}

				score = s.retscr();

				if (log != 1)   //if not logged-will app
				{
					f.open("gamemode1.dat", ios::out | ios::binary | ios::app);  //for viewing password in explorer
					f << "            " << "SCORE: " << score << "\n\n";

					do
					{
						oldpos1[l] = f.tellg();             //storing all pos for re-writing
						break;
					} while (1);   //just for running once

					f.close();

					f.open("disp1.dat", ios::out | ios::binary | ios::app);  //for displaying
					f << "        " << "SCORE: " << score << "\n\n";

					do
					{
						oldpos[l] = f.tellg();   //storing all pos for re-writing
						l++;
						break;
					} while (1);   //just for running once

					f.close();
				}
				if (log == 1)      //to update score after login
				{
					score = s.retscr();                                            

					f.open("disp1.dat", ios::out | ios::binary | ios::cur | ios::in);

					if (cnt1 > 1)
					{
						do 
						{
							f.seekp(oldpos[k]);     //to write at pos
							k++;
							break;
						} while (1);
					}
					else              
						f.seekp(0);

					f << "\t\t\t\t" << cnt1 << "] USERNAME: " << username;
					f << "        " << "SCORE: " << score << "\n\n";
					f.close();

					f.open("gamemode1.dat", ios::out | ios::binary | ios::cur | ios::in);

					if (cnt1 > 1)
					{
						do
						{
							f.seekp(oldpos1[k]);     //to write at pos
							k++;
							break;
						} while (1);
					}
					else
						f.seekp(0);

					f << "\t\t\t\t" << cnt1 << "] USERNAME: " << username << "        " << "PASSWORD: " << password;
					f << "        " << "SCORE: " << score << "\n\n";
					f.close();

					l++;
				}

				break;

			case 2:                                                  //game mode 2

				system("cls");

			sgn2:

				cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t       Enter Option:\n\n";
				cout << "\t\t\t\t\t\t\t 1] Sign Up:\n\n";
				cout << "\t\t\t\t\t\t\t 2] Login:\n\n";
				cout << "\t\t\t\t\t\t\t 3] Exit to Main Menu\n\n";
				cout << "\t\t\t\t\t\t\tYOUR CHOICE : ";
				cin >> op2;

				switch (op2)
				{
				case 1:                                         //signing up

					system("cls");

				signup2:

					log = 0;

					f.open("gamemode2.dat", ios::in | ios::binary | ios::ate);

					cout << "\n\n\t\t\t\t\t\t    SIGNING UP ";
					cout << "\n\t\t\t\t\t\t    ~~~~~~~~~~\n\n";

					if(flag!=3)
						flag = 2;
					s.getu1();               //for copy
					s.getp1();               //for copy
					cout << "\n\t\t\t\t\tRe-Enter Player UserName : ";
					cin >> ch;                //for checking
					cout << "\n\t\t\t\t\tRe-Enter Password : ";
					cin >> pw;

					if (strcmp(s.retu1(), ch) != 0 || strcmp(s.retp1(), pw) != 0)      //to check if user name and passwords match
					{
						cout << "\n\n\t\t\t\tUserNames / Passwords Do Not MATCH! Try Again!\n\n";
						system("PAUSE");
						system("cls");
						flag = 3;
						f.close();
						goto signup2;
					}

					f.seekg(0,ios::beg);

					while (!f.eof())
					{
						f.read((char*)& ch, sizeof(s));
						if (strcmp(username, ch) == 0)
						{
							cout << "\n\t\t\t\tSorry, Entered UserName Already Exists! Try Again!!\n\n";
							system("PAUSE");
							system("cls");
							f.close();
							goto signup2;
						}
						j++;
						if (j >= cnt1)
							break;
					}

					f.close();
					cout << "\n\n\t\t\t\tSuccessfully registered! You May Now proceed to playing!\n\n\n";
					s.getu();
					s.getp();

					f1.open("gamemode2.dat", ios::out | ios::binary | ios::app);    //store everything
					f1 << "\t\t\t\t" << cnt1 << "] USERNAME: " << username << "        " << "PASSWORD: " << password;
					f1.close();

					f1.open("disp2.dat", ios::out | ios::binary | ios::app);    //for disp
					f1 << "\t\t\t\t" << cnt1 << "] USERNAME: " << username;
					f1.close();
					system("PAUSE");

					break;

				case 2:                                   //logging in

				login2:

					lcheck = 0;
					log = 2;

					system("cls");
					
					cout << "\n\n\t\t\t\t\t\t    LOGING IN ";
					cout << "\n\t\t\t\t\t\t    ~~~~~~~~~\n\n";

					f.open("gamemode2.dat", ios::in | ios::binary | ios::beg);

					if (f.tellg() != '\0')             //to check if there are no users present
					{
						cout << "\n\t\t\t\t\t\tNo Registered Users Found!\n\n ";
						system("PAUSE");
						system("cls");
						f.close();
						goto signup2;
						break;
					}

					cout << "\n\t\t\t\t\tEnter Player UserName : ";
					cin >> ch;
					cout << "\n\t\t\t\t\tEnter User Password : ";
					cin >> pw;

					while (!f.eof())
					{
						if (strcmp(ch, s.retu1()) == 0 && strcmp(pw, s.retp1()) == 0)
						{
							cout << "\n\n\t\t\t\tSuccessfully Logged In! You May Now Proceed To Playing!\n\n\n";
							system("PAUSE");
							break;
						}
						else
						{
							lcheck = 2;
							break;
						}
					}

					if (lcheck == 2)
					{
						cout << "\n\n\t\t\t\tEntered Details Does Not Match With Existing Details! Try Again!\n\n";
						f.close();
						system("PAUSE");
						system("cls");
						goto login2;
					}

					f.close();

					break;

				case 3:

					system("pause");
					goto main;

				default:
					cout << "\nYou Have Entered an Wrong Input! Try Again!!\n\n\n";
					system("PAUSE");
					system("cls");
					goto sgn2;

				}

				setup();
				system("cls");
				cout << "\n\n\t\t\t\t\t         RULES:\n\n";
				cout << "\t\t\t\t   1)Go In Direct Reverse Direction -->> DEATH!\n";
				cout << "\t\t\t\t   2)Touch Head To Tail --> DEATH!\n";

				cout << "\n\n\t\t\t\t\t        CONTROLS:\n\n";
				cout << "\t\t\t\t     W --> Upwards\n";
				cout << "\t\t\t\t     A --> Left\n";
				cout << "\t\t\t\t     S --> Downwards\n";
				cout << "\t\t\t\t     D --> Right\n";

				cout << "\n\n\t\t\t\t\t        DIAGRAM:\n\n";
				cout << "\t\t\t\t    O o o o o o o o          B\n";
				cout << "\t\t\t\t    ^       ^                ^\n";
				cout << "\t\t\t\t    |       |                |\n";
				cout << "\t\t\t\t    |       |                |\n";
				cout << "\t\t\t\t   HEAD    TAIL            FRUIT\n\n";

				system("PAUSE");
				system("cls");

				s.setscr();
				gameover = false;
				flag = 2;
				while (!gameover)
				{
					s.draw();
					s.input();
					s.logic();
				}

				score = s.retscr();

				if (log != 2)   //if not logged-will app
				{
					f.open("gamemode2.dat", ios::out | ios::binary | ios::app);  //for viewing password in explorer
					f << "            " << "SCORE: " << score << "\n\n";

					do
					{
						oldpos1[l] = f.tellg();         //storing all pos for re-writing
						break;
					} while (1);   //just for running once

					f.close();

					f.open("disp2.dat", ios::out | ios::binary | ios::app);  //for displaying
					f << "        " << "SCORE: " << score << "\n\n";

					do
					{
					    oldpos[l] = f.tellg();             //storing all pos for re-writing
						l++;
						break;
					} while (1);   //just for running once

					f.close();
				}  

				if (log == 2)      //to update score after login
				{
					score = s.retscr();                                         

					f.open("disp2.dat", ios::out | ios::binary | ios::cur | ios::in);

					if (cnt1 > 1)
					{
						do
						{
							f.seekp(oldpos[k]);     //to write at pos
							k++; 
							break;
						} while (1);
					}
					else
						f.seekp(0);

					f << "\t\t\t\t" << cnt1 << "] USERNAME: " << username;
					f << "        " << "SCORE: " << score << "\n\n";
					f.close();

					f.open("gamemode2.dat", ios::out | ios::binary | ios::cur | ios::in);

					if (cnt1 > 1)
					{
						do
						{
							f.seekp(oldpos1[k]);     //to write at pos
							k++;
							break;
						} while (1);
					}
					else
						f.seekp(0);

					f << "\t\t\t\t" << cnt1 << "] USERNAME: " << username << "        " << "PASSWORD: " << password;
					f << "        " << "SCORE: " << score << "\n\n";
					f.close();

					l++;
				}

				break;

            case 3:

				system("cls");
					cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t         Enter Option:\n\n";
					cout << "\t\t\t\t\t\t\t 1] GAMEMODE 1\n\n";
					cout << "\t\t\t\t\t\t\t 2] GAMEMODE 2\n\n";
					cout << "\t\t\t\t\t\t\t 3] Exit to Main Menu\n\n";
					cout << "\t\t\t\t\t\t\t  YOUR CHOICE : ";
					cin >> op3;
					switch (op3)
					{
					case 1:

						system("cls");
						cout << "\n\n\t\t\t\t\t\t    DISPLAYING ";
						cout << "\n\t\t\t\t\t\t    ~~~~~~~~~~~\n\n";
						s.disp1();
						cout << "\n\n";
						system("PAUSE");
						system("cls");
						break;

					case 2:

						system("cls");
						cout << "\n\n\t\t\t\t\t\t    DISPLAYING ";
						cout << "\n\t\t\t\t\t\t    ~~~~~~~~~~~\n\n";
						s.disp2();
						cout << "\n\n";
						system("PAUSE");
						system("cls");
						break;

					case 3:
						system("pause");
						break;

					default:

						cout << "You Have Entered An Wrong Input! Please Try Again!!\n\n\n\n";
						system("PAUSE");
						break;
					}

				break;

			case 4:
				system("PAUSE");
				exit(0);
				break;

			default:
				cout << "You Have Entered An Wrong Input! Please Try Again!!\n\n\n\n";
				system("PAUSE");
				goto main;
			}
		} while (op == 1 || op == 2 || op == 3);
		return 0;
}