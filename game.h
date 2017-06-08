#include"Head.h"
#define _CRT_SECURE_NO_WARNINGS 1

bool MoveAble(int rockIndex, RockLocation_t* currentLocatePtr, int f_direction);
void SetGameBoardFlag(int rockIdx, RockLocation_t* curRockLocation);
void UserHitKeyBoard(char userHit, int* RockIndex, RockLocation_t* curRockLocation);
void FullLine();
void UpdateSocres(int scores);
void DelCurLine(int rowIdx);
bool IsGameOver();


void PlayGame()
{
	char userHit = 0;//用户敲击键盘
	int curRockIndex = 0;//当前方块的rockArray下标
	int nextRockIndex = 0;//下次
	RockLocation_t curRockLocation;
	curRockLocation.left = initRockLocation.left;
	curRockLocation.top = initRockLocation.top;
	DWORD oldtime = 0;
	srand((unsigned int)time(NULL));
	curRockIndex = rand() % rockTypeNum;
	nextRockIndex = rand() % rockTypeNum;
	//画出预览区初始化方块
	//在初始位置和预览区显示方块形状
	DisplayRock(curRockIndex, &initRockLocation, 1);
	DisplayRock(nextRockIndex, &preRockLocation, 1);
	bool moveAbled = false;
	while (true)
	{
		//判断当前方块是否落地(判断能否再下移)：如果落地,判断是否满行,再判断是否结束游戏， 改变game_board ,画出下次初始化的方块，以及生成新的预览方块
		//
		moveAbled = MoveAble(curRockIndex, &curRockLocation, DIRECT_DOWN);
		if (!moveAbled) //判断是否落地，不能下移表示落地
		{
			//修改game_board的值
			SetGameBoardFlag(curRockIndex, &curRockLocation);
			FullLine(); 
			if (IsGameOver())
			{
				MessageBox(NULL, _T("游戏结束"), _T("GAME OVER"), MB_OK);
				exit(0);
			}		
			//为下次生成模块开始准备
			DisplayRock(nextRockIndex, &preRockLocation, false);//擦除旧的方块
			curRockIndex = nextRockIndex;
			nextRockIndex = rand() % rockTypeNum; //生成新的预览方块
			DisplayRock(curRockIndex, &initRockLocation, 1);
			DisplayRock(nextRockIndex, &preRockLocation, 1);
			FlushBatchDraw();
			//修改curRockLocation的值
			curRockLocation.left = initRockLocation.left;
			curRockLocation.top = initRockLocation.top; 
		}

		if (kbhit()) //如果敲击键盘了 就处理按键
		{
			userHit = getch();
			UserHitKeyBoard(userHit, &curRockIndex, &curRockLocation);
		}

	    //没有 就自动下移一个单位 :不能用else，因为可能按键不是上下左右
		DWORD newtime = GetTickCount();
		if (newtime - oldtime >= (unsigned int)(300) && moveAbled == TRUE)
		{
			oldtime = newtime;
			DisplayRock(curRockIndex, &curRockLocation, false);
			curRockLocation.top += ROCK_SQUARE_WIDTH; //下落一格  
		}
		//AutomaticDownMove(curRockIndex, &curRockLocation);
		//画出新方块
		DisplayRock(curRockIndex, &curRockLocation, 1);
		FlushBatchDraw();//刷新界面，防止出现闪屏
		Sleep(20);
	}
}


//响应键盘命令时间
void UserHitKeyBoard(char userHit, int* RockIndex, RockLocation_t* curRockLocation)
{
	switch (userHit)
	{
	case 'W':
	case 'w'://↑
		if (MoveAble(RockArray[*RockIndex].nextRockIndex, curRockLocation, DIRECT_UP))
		{
			DisplayRock(*RockIndex, curRockLocation, false);
			*RockIndex = RockArray[*RockIndex].nextRockIndex;
		}
		break;
	case 'S':
	case 's'://↓
		if (MoveAble(*RockIndex, curRockLocation, DIRECT_DOWN))
		{
			DisplayRock(*RockIndex, curRockLocation, false);
			curRockLocation->top += 2 * (ROCK_SQUARE_WIDTH);
			if (!MoveAble(*RockIndex, curRockLocation, DIRECT_DOWN))
			{
				curRockLocation->top -= ROCK_SQUARE_WIDTH;
			}
		}
		break;
	case 'A':
	case 'a': //←
		if (MoveAble(*RockIndex, curRockLocation, DIRECT_LEFT))
		{
			DisplayRock(*RockIndex, curRockLocation, false);
			curRockLocation->left -= ROCK_SQUARE_WIDTH;
		}
		break;
	case 'D':
	case 'd': //→
		if (MoveAble(*RockIndex, curRockLocation, DIRECT_RIGHT))
		{
			DisplayRock(*RockIndex, curRockLocation, FALSE);
			curRockLocation->left += ROCK_SQUARE_WIDTH;
		}
		break;
	case ' ': //暂停
		while (1)
		{
			userHit = getch();
			if (userHit == ' ')
				break;
		}
		break;
	default:
		break;
	}
}

//判断是否满行，满行消除，然后计算得分
void FullLine()
{
	bool linefull = true;
	int idx = yROCK_SQUARE_NUM;//从最后一行往上查找 22
	int count = 0;
	while (count != xROCK_SQUARE_NUM ) //遇到空行 14
	{
		linefull = true;
		count = 0;
		for (int i = 1; i <= xROCK_SQUARE_NUM; ++i)
		{
			if (game_board[idx][i] == 0)
			{
				linefull = false;
				count++;
			}
		}
		if (linefull) //满行，消除当前行，更新分数
		{
			DelCurLine(idx);
			game_socres += 3;
			UpdateSocres(game_socres);
			idx++;//因为下面要减1
		}
		idx--;
	}

}
void UpdateSocres(int scores)
{
	setcolor(RED);
	TCHAR s[10];
	_stprintf(s, _T("%d"), scores);
	outtextxy(GAME_WALL_WIDTH + 90, 200, s);
}
//消除当前行
void DelCurLine(int rowIdx)
{
	//擦除当前行
	setcolor(BLACK);
	setfillcolor(BLACK);
	for (int i = 1; i < xROCK_SQUARE_NUM; ++i)
	{
		fillrectangle(WALL_SQUARE_WIDTH + (i - 1)*ROCK_SQUARE_WIDTH, (rowIdx - 1)*ROCK_SQUARE_WIDTH + WALL_SQUARE_WIDTH,
				  WALL_SQUARE_WIDTH + i*ROCK_SQUARE_WIDTH, rowIdx*ROCK_SQUARE_WIDTH + WALL_SQUARE_WIDTH);
	}
	//把上面的向下移
	int cnt = 0;
	while (cnt != xROCK_SQUARE_NUM) //直到遇到是空行的为止  
	{
		cnt = 0;
		for (int i = 1; i <= xROCK_SQUARE_NUM; i++)
		{
			game_board[rowIdx][i] = game_board[rowIdx - 1][i];

			//擦除上面的一行  
			setcolor(BLACK);
			setfillcolor(BLACK);
			fillrectangle(WALL_SQUARE_WIDTH + ROCK_SQUARE_WIDTH*i - ROCK_SQUARE_WIDTH ,
				WALL_SQUARE_WIDTH + ROCK_SQUARE_WIDTH*(rowIdx - 1) - ROCK_SQUARE_WIDTH ,
				WALL_SQUARE_WIDTH + ROCK_SQUARE_WIDTH*i,
				WALL_SQUARE_WIDTH + ROCK_SQUARE_WIDTH*(rowIdx - 1));

			//显示下面的一行  
			if (game_board[rowIdx][i] == 1)
			{
				setcolor(WHITE);
				setfillcolor(RED);
				fillrectangle(WALL_SQUARE_WIDTH + ROCK_SQUARE_WIDTH*i - ROCK_SQUARE_WIDTH ,
					WALL_SQUARE_WIDTH + ROCK_SQUARE_WIDTH*rowIdx - ROCK_SQUARE_WIDTH ,
					WALL_SQUARE_WIDTH + ROCK_SQUARE_WIDTH*i,
					WALL_SQUARE_WIDTH + ROCK_SQUARE_WIDTH*rowIdx);
			}

			if (game_board[rowIdx][i] == 0)
				cnt++;            //统计一行是不是 都是空格  
		}//for  
		rowIdx--;
	}
}

//是否可以移动方块
bool MoveAble(int rockIndex, RockLocation_t* currentLocatePtr, int f_direction)
{
	int mask;
	int rockX;
	int rockY;

	rockX = currentLocatePtr->left;
	rockY = currentLocatePtr->top;

	mask = (unsigned short)1 << 15;
	for (int i = 1; i <= 16; i++)
	{
		//与掩码相与为1的 即为方块上的点  
		if ((RockArray[rockIndex].rockShapeBits & mask) != 0)
		{
			//判断能否移动(即扫描即将移动的位置 是否与设置的围墙有重叠)  
			//若是向上(即翻滚变形)  
			if (f_direction == DIRECT_UP)
			{
				//因为此情况下传入的是下一个方块的形状，故我们直接判断此方块的位置是否已经被占 
				//判断下一个方块
				if (game_board[(rockY - WALL_SQUARE_WIDTH) / ROCK_SQUARE_WIDTH + 1]
					[(rockX - WALL_SQUARE_WIDTH) / ROCK_SQUARE_WIDTH + 1] == 1)
					return false;
			}
			//如果是向下方向移动  
			else if (f_direction == DIRECT_DOWN)
			{
				if (game_board[(rockY - WALL_SQUARE_WIDTH) / ROCK_SQUARE_WIDTH + 2]
					[(rockX - WALL_SQUARE_WIDTH) / ROCK_SQUARE_WIDTH + 1] == 1)
					return false;
			}
			else //如果是左右方向移动  
			{   //f_direction的DIRECT_LEFT为-1，DIRECT_RIGHT为1，故直接加f_direction即可判断。  
				if (game_board[(rockY - WALL_SQUARE_WIDTH) / ROCK_SQUARE_WIDTH + 1]
					[(rockX - WALL_SQUARE_WIDTH) / ROCK_SQUARE_WIDTH + 1 + f_direction] == 1)
					return false;
			}
		}

		//每4次 换行 转到下一行继续  
		i % 4 == 0 ? (rockY += ROCK_SQUARE_WIDTH, rockX = currentLocatePtr->left)
			: rockX += ROCK_SQUARE_WIDTH;

		mask >>= 1;
	}

	return true;

}
//给游戏game_board设置标记表示已经占了
void SetGameBoardFlag(int rockIdx, RockLocation_t* curRockLocation)
{
	int mask;
	int rockX;
	int rockY;

	rockX = curRockLocation->left;
	rockY = curRockLocation->top;

	mask = (unsigned int)1 << 15;
	for (int i = 1; i <= 16; i++)
	{
		//与掩码相与为1的 即为方块上的点  
		if ((RockArray[rockIdx].rockShapeBits & mask) != 0)
		{
			game_board[(rockY - WALL_SQUARE_WIDTH) / ROCK_SQUARE_WIDTH + 1]
				[(rockX - WALL_SQUARE_WIDTH) / ROCK_SQUARE_WIDTH + 1] = 1;
		}

		//每4次 换行 转到下一行继续画  
		i % 4 == 0 ? (rockY += ROCK_SQUARE_WIDTH, rockX = curRockLocation->left)
			: rockX += ROCK_SQUARE_WIDTH;

		mask >>= 1;
	}
}
//判断游戏是否结束
bool IsGameOver()
{
	bool topLineHaveRock = false;//顶行是否有方块
	bool bottomLineHaveRock = false;

	for (int i = 1; i < xROCK_SQUARE_NUM; ++i)
	{
		if (game_board[1][i] == 1)
			topLineHaveRock = true;
		if (game_board[yROCK_SQUARE_NUM][i] == 1)
			bottomLineHaveRock = true;
	}
	if (bottomLineHaveRock && topLineHaveRock)
		return true;
	else 
		return false;
}
