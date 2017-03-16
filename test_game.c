

#include"game.h"

void menu()
{
	printf("**********单机版 三子棋*************\n");
	printf("********** 1 开始游戏  *************\n");
	printf("********** 0 退出游戏   ************\n");
	printf("************************************\n");
}
enum op
{
	EXIT,
	PLAY
};
void start_game(char board[][ROWS])
{
	char result = 0;
	init(board);
	print_board(board);
	do
	{
		p_game(board);
		result = check_win(board);
		if (result != 'Q')
			break;
		npc_game(board);
		result = check_win(board);
	} while (result == 'Q');
	if (result == 'X')
		printf("玩家赢了\n");
	else if (result == 'O')
		printf("电脑赢了\n");
	else if (result == 'P')
		printf("平局\n");
}
int main()
{
	char board[LINE][ROWS];
	int input = 1;	
	do
	{
		menu();
		printf("请输入选择：");
		scanf("%d", &input);
		switch (input)
		{
		case PLAY:
			start_game(board);
			break;
		case EXIT:
			break;
		default:
			printf("输入错误!!!\n");
			break;
		}
	} while (input);

	system("pause");
	return 0;
}