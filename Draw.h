#include"Head.h"

1

//画出游戏界面
void DrawGameWindow()
{
	//先画出围墙
	setcolor(BLUE);
	setlinestyle(PS_SOLID,NULL,0);
	setfillcolor(BLUE);
	//画出上下围墙
	for (int x = WALL_SQUARE_WIDTH; x <= GAME_WALL_WIDTH; x += WALL_SQUARE_WIDTH)
	{
		fillrectangle(x - WALL_SQUARE_WIDTH, 0, x, WALL_SQUARE_WIDTH); //上
		fillrectangle(x - WALL_SQUARE_WIDTH, GAME_WALL_HTGH - WALL_SQUARE_WIDTH, x, GAME_WALL_HTGH);//下
	}
	//画出左右围墙
	for (int y = WALL_SQUARE_WIDTH; y <= GAME_WALL_HTGH; y += WALL_SQUARE_WIDTH)
	{
		fillrectangle(0, y, WALL_SQUARE_WIDTH, y + WALL_SQUARE_WIDTH);//左
		fillrectangle(GAME_WALL_WIDTH - WALL_SQUARE_WIDTH, y, GAME_WALL_WIDTH, y + WALL_SQUARE_WIDTH);//右
	}

	//画出右边统计分数及相关东西

	//画出分割线
	setcolor(WHITE);
	setlinestyle(PS_DASH,2);
	line(GAME_WALL_WIDTH + 20, 0, GAME_WALL_WIDTH + 20, GAME_WALL_HTGH);

	//设置字体
	LOGFONT font;
	gettextstyle(&font);
	settextstyle(18, 0, _T("宋体"));
	font.lfQuality = ANTIALIASED_QUALITY;//设置输出效果为抗锯齿 
	//1显示预览形状
	outtextxy(GAME_WALL_WIDTH + 80, 30, _T("预览"));

	outtextxy(GAME_WALL_WIDTH + 80, 170, _T("分数"));
	
	outtextxy(GAME_WALL_WIDTH + 65, 250, _T("操作说明"));
	outtextxy(GAME_WALL_WIDTH + 40, 290, _T("w a s d控制方向"));
	outtextxy(GAME_WALL_WIDTH + 40, 335, _T("空格 暂停"));
	
	//显示分数
	setcolor(RED);
	outtextxy(GAME_WALL_WIDTH + 90, 200, '0');
}

//在游戏区显示编号为rockIdx的方块
void DisplayRock(int rockIdx,  RockLocation_t*  LocatePtr, bool displayed)
{
	int color;//方块的填充颜色
	int lineColor = WHITE;//线的颜色
	int boardFalg = 0;
	int xRock = 0;
	int yRock = 0;
	unsigned short rockCode = RockArray[rockIdx].rockShapeBits;
	//如果displayed为true的话，将方块块颜色设置为white，game_board对应的位置设置为1；
	//如果displayed为false的话，将方块块颜色设置为black，game_board对应的位置设置为0；
	displayed ? (color = RED, boardFalg = 1) : (color = BLACK,lineColor = BLACK, boardFalg = 0);
	
	setcolor(lineColor);
	setfillcolor(color);
	
	setlinestyle(PS_SOLID);//设置为实线，
	xRock = LocatePtr->left;
	yRock = LocatePtr->top;

	int count = 0;//每4个换行，记录坐标偏移量
	unsigned short mask = 1;
	for (int i = 1; i <= 16; ++i)
	{
		
		mask = 1 << (16 - i);
		if ((rockCode & mask) != 0) //如果不为0的话，就画出小方块
		{		
			fillrectangle(xRock , yRock, xRock + ROCK_SQUARE_WIDTH, yRock + ROCK_SQUARE_WIDTH);
		}
		if (i % 4 == 0) //换行
		{
			yRock = yRock + ROCK_SQUARE_WIDTH;	
			xRock = xRock = LocatePtr->left;
		}
		else
		{
			xRock += ROCK_SQUARE_WIDTH;
		}
	}
}

