#include"Head.h"

static void ShapeStrToBit(unsigned char *rockShapeStr, unsigned short& rockShapeBit);
static void ReadRcok();


void InitGame()
{
	//把全局游戏游戏版初始化，边界初始化为1
	for (int i = 0; i < xROCK_SQUARE_NUM + 2; i++)
	{
		game_board[0][i] = 1;  //上边界
		game_board[yROCK_SQUARE_NUM + 1][i] = 1; //下边界
	}
	for (int i = 0; i < yROCK_SQUARE_NUM + 2; i++)
	{
		game_board[i][0] = 1 ; //左边界
		game_board[i][xROCK_SQUARE_NUM + 1] = 1; //右边界
	}
	//读取俄罗斯方块 
	ReadRcok();

}

//从文件中读取方块的形状存储到rockArray中
void ReadRcok()
{
	FILE* fp = fopen("RockShape.ini","r");
	if (NULL == fp)
	{
		printf("打开文件失败\n");
		return;
	}
	unsigned char readBuf[1024]; //fp读取到字符串readbuf中
	unsigned short rockShapeBit = 0;//存放方块形状，占16比特位
	unsigned char rockShapeStr[16];//存放方块字符串
	int ShapeStrIdx = 0;
	int rockNum = 0;//统计方块的个数以及存放方块数组RockArray的下标
	int rocknext = 0;//方块数组中下一个形状
	int rockShapeStart = 0;//同一类型的形状
	
	while (true)
	{
		size_t readSize = fread(readBuf, 1, 1024, fp);
		if (readSize == 0)
			break;
		//处理readbuf
		for (size_t idx = 0; idx < readSize; ++idx)
		{
			//将字符存放到rockShapeStr中
			while (ShapeStrIdx < 16 && idx < readSize)
			{
				if (readBuf[idx] == '@' || readBuf[idx] == '#')
				{
					rockShapeStr[ShapeStrIdx] = (unsigned char)readBuf[idx];
					++ShapeStrIdx;
				}
				++idx; //可能idx == readSize了 ,这里不可能等于的，配置文件小于1024
				if (readBuf[idx] == '*')//修改上一次方块的next值
				{
					idx += 5;
					RockArray[--rockNum].nextRockIndex = rockShapeStart;
					rockNum++;
					rockShapeStart = rockNum;
					rocknext = rockShapeStart ;
				}
			}
			//可能没有填满,
			if (ShapeStrIdx < 16)
			{
				break;
			}
			else //填满shapestr
			{
				ShapeStrIdx = 0;//置0
				//将rockShapeStr 转为rockShapeBit
				ShapeStrToBit(rockShapeStr, rockShapeBit);
				rocknext++;
				RockArray[rockNum].rockShapeBits = rockShapeBit;
				RockArray[rockNum].nextRockIndex = rocknext;
				rockNum++;
			}
		}
	}
	fclose(fp);
}

//将从文件中读取的字符串(长度默认为16)转换成 unsigned short
void ShapeStrToBit(unsigned char *rockShapeStr, unsigned short& rockShapeBit)
{
	rockShapeBit = 0;
	for (size_t idx = 0; idx < 16; ++idx)
	{
		if (rockShapeStr[idx] == '@') //1
		{
			rockShapeBit |= (1 << (16 - idx - 1));
		}
		// #为0 不需要处理
	}
}


