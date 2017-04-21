#include"Head.h"
#include"Draw.h"
#include"Init.h"
#include"game.h"

int main()
{
	initgraph(WINDOW_WIDTH,WINDOW_HIGH);

	DrawGameWindow();
	//使用 API 函数修改窗口名称  
	HWND hWnd = GetHWnd();
	SetWindowText(hWnd, _T("俄罗斯方块"));
	InitGame();
	PlayGame();
	getchar();
	closegraph();
	system("pause");
	return	0;
}
