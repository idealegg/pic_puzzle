/**************************
图片拼图
自礼空王
***************************/

#include<conio.h>
#include<stdio.h>
#include"graphics.h"
#include<time.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

#define N 3

void GameInit();
void draw();
void game();
int judge();
void menu();


IMAGE img[N*N+2];//3*3原拼图；1封面 ；1 空白
int p[N][N];
int gn= 0; 
HWND hWnd;

COORD coor;




int main()
{
	initgraph(546, 710);
	setbkcolor(WHITE);
	cleardevice();
	loadimage(&img[0], L"res\\0.jpg",182,200);
	loadimage(&img[1], L"res\\1.jpg",182,200);
	loadimage(&img[2], L"res\\2.jpg",182,200);
	loadimage(&img[3], L"res\\3.jpg",182,200);
	loadimage(&img[4], L"res\\4.jpg",182,200);
	loadimage(&img[5], L"res\\5.jpg",182,200);
	loadimage(&img[6], L"res\\6.jpg",182,200);
	loadimage(&img[7], L"res\\7.jpg",182,200);
	loadimage(&img[8], L"res\\8.jpg",182,200);
	loadimage(&img[9], L"res\\9.jpg",182,200);
	loadimage(&img[10], L"res\\10.jpg", 546, 600);

	mciSendString(L"open ./res/单身狗之歌.mp3 alias bgm", 0, 0, 0);
	mciSendString(L"play bgm repeat", 0, 0, 0);

	menu();

	GameInit();

	while (1)
	{
		draw();
		game();
		if (judge()==2)break;
	}
	hWnd=GetForegroundWindow();
	draw();
	Sleep(200);
	p[(gn - 1) / N][gn - ((gn - 1) / N)*N - 1] = gn;
    draw();

	MessageBoxA(hWnd, "恭喜通关,节日快乐！", "恭喜通关", MB_OK);
	return 0;
}

void GameInit()
{
	int i, j, x = 1;
	for (i = 0; i < N; i++)
	for (j = 0; j < N; j++)
	{
		p[i][j] = x++;
	}
	srand((unsigned)time(NULL));
	int temp;

	while (gn== 0)gn= rand() % 10;
	p[(gn- 1) / N][gn-((gn-1)/N)*N-1] = 0;
	while (judge()!=0)
	{for (int t = 0; t < 2; t++)
	{
		temp = p[t][t];
		 p[t][t] =p[t][t+1];
		 p[t][t + 1] = temp;
	}
	for (int t = 0; t < 2; t++)
	{
		temp = p[t][t];
		p[t][t] = p[t + 1][t ];
		p[t + 1][t] = temp;
	}
	}
}

void draw()
{
	cleardevice();
	int i, j;
	for (i = 0; i < N; i++)
	{for (j = 0; j < N; j++)
	{
		switch (p[i][j])
		{
		case 0:putimage(182 * j, 200* i, &img[0]); break;
		case 1:putimage(182 * j, 200 * i, &img[1]); break;
		case 2:putimage(182 * j, 200 * i, &img[2]); break;
		case 3:putimage(182 * j, 200 * i, &img[3]); break;
		case 4:putimage(182 * j, 200 * i, &img[4]); break;
		case 5:putimage(182 * j, 200 * i, &img[5]); break;
		case 6:putimage(182 * j, 200 * i, &img[6]); break;
		case 7:putimage(182 * j, 200 * i, &img[7]); break;
		case 8:putimage(182 * j, 200 * i, &img[8]); break;
		case 9:putimage(182 * j, 200 * i, &img[9]); break;
		}
	}printf("\n");
	}
}


void game()
{
	char ch;
	int m, n;
	int i, j;
	for (i = 0; i < N; i++)
	for (j = 0; j < N; j++)
	{
		if (p[i][j] == 0)
		{
			m = i; n = j;break;
		}
	}


	ch = getch();
	switch (ch)
	{
	case 'w':
	case 'W':
	case 72:if (m != 2){	
		p[m][n] = p[m + 1][n];
		p[m + 1][n] = 0;}
			break;
	case 's':
	case 'S':
	case 80:if (m != 0)
	{p[m][n] = p[m - 1][n];
		p[m -1][n] = 0; 
	}break;
	case 'a':
	case 'A':
	case 75:if (n != 2)
	{
		p[m][n] = p[m][n + 1];
		p[m][n + 1] = 0;
	}
 break;
	case 'd':
	case 'D':
	case 77:if (n != 0)
	{
	p[m][n] = p[m][n - 1];
		p[m][n - 1] = 0;
	}
	 break;
	case 27:
		if (IDYES==MessageBoxA(hWnd, "你确定要退出吗", "退出游戏", MB_YESNO))
			exit(0);
	}

}

int judge()
{
	int i, j,x=0;
	int s;
	s= 0;
	int manha=0;
	int b[N*N];

	for (i = 0; i < N; i++)
	for (j = 0; j < N; j++)
	{
		if (p[i][j])
			b[x++] = p[i][j];
		else b[x++] = gn;
	}

	for (i = 0; i < (N*N-1);i++)
	for (j = (N*N-1); j>i; j--)
	{
		if (b[i]>b[j])s++;
	}



	int m, n;
	for (i = 0; i < N; i++)
	for (j = 0; j < N; j++)
	{
		if (p[i][j] == 0)
		{
			m = i; n = j; break;
		}
	}
	manha = N-1 - m + N-1 - n;

	if (s==0)
	return 2;
	if ((s + manha) % 2 == (N * N - 1 + 2 - (gn - 1) / N
		+ 2 - gn + ((gn - 1) / N) * N + 1) % 2)
		return 0;
	return 1;

}

void menu()
{
	putimage(0, 0, &img[10]);
	settextcolor(BLACK);
	outtextxy(265, 610, L"WASD、方向键控制");
	outtextxy(265, 630, L"ESC键退出游戏");
	outtextxy(265, 650, L"BY 自礼空王");
	outtextxy(265, 670, L"交流QQ：1254110687");

	while (!kbhit ())
	{
		outtextxy(280, 690, L"按任意键继续");
	}
}