#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<fstream>
#include<string>
#include<stack>
using namespace std;
struct Seat // 坐标
{
	Seat(int x = 0, int y = 0)
	: _x(x)
	, _y(y)
	{}
	int _x;
	int _y;
};
//1、地图的数据保存在文件中，加载是从文件中读取
//2、保存迷宫地图的空间使用动态开辟的二维数组
//3、程序运行结束后在地图上标出具体的走法
class Maze
{
public:
	Maze(const string& filename)
	{
		string strBuff;
		string strData;
		fstream fin(filename);

		getline(fin,strBuff);//读取第一行

		strData = strBuff.substr(0, strBuff.find_first_of(','));//获取row
		_row = atoi(strData.c_str()); 

		strData = strBuff.substr(strBuff.find_first_of(',')+1);//获取col
		_col= atoi(strData.c_str());

		//动态开辟数组
		_map = new int*[_row];
		for (int i = 0; i < _row; ++i)
		{
			_map[i] = new int[_col];
		}

		// 读取数据放在动态数组中
		int RowIdx = 0, ColIdx = 0;
		while (!fin.eof())
		{
			getline(fin,strData);
			char* start = (char*)strData.c_str();
			while (*start)
			{
				if (*start >= '0' && *start <= '3')
					_map[RowIdx][ColIdx++] = *start - '0';
				start++;
			}
			RowIdx += 1;//换行
			ColIdx = 0;
		}
		fin.close();
	}
	bool IsPass(const Seat& s)   // 判断当前路口是否是通路
	{
		if (s._x < 0 || s._y < 0 || s._y >= _col|| s._x >= _row) //表示到达终点
			return true;
		if (_map[s._x][s._y] == 1)
			return true;
		else
			return false;
	}
	bool PassMaze(const Seat& Entry) // 递归走迷宫
	{
		//当前坐标在二维数组外面 递归结束条件
		if (Entry._x < 0 || Entry._x >= _row ||
			Entry._y < 0 || Entry._y >= _col)
			return true;

		if (IsPass(Entry)) //判断当前的坐标是否通
		{
			_map[Entry._x][Entry._y] = 2; //通路置成2

			//超前
			Seat front(Entry._x -1,Entry._y);
			if (PassMaze(front))
				return true;
			//超左
			Seat left(Entry._x, Entry._y -1);
			if (PassMaze(left))
				return true;
			//超右
			Seat right(Entry._x, Entry._y + 1);
			if (PassMaze(right))
				return true;

			_map[Entry._x][Entry._y] = 3; // 标记表示走不通
		}
			return false;
	}
	bool PazzMaze2(std::stack<Seat>&s, const Seat& Entry)// 用栈循环实现
	// 通路放在栈中
	{
		
		if (IsPass(Entry))
		{
			s.push(Entry);
			while (!s.empty())
			{
				Seat Cur = s.top();
				//函数结束条件
				if (Cur._x < 0 || Cur._x >= _row ||
					Cur._y < 0 || Cur._y >= _col)
				{
					s.pop();
					return true;
				}
					
				_map[Cur._x][Cur._y] = 2;
				//前
				Seat Front(Cur._x-1, Cur._y);
				if (IsPass(Front))
				{
					s.push(Front);
					continue;
				}
				//左
				Seat Left(Cur._x, Cur._y-1);
				if (IsPass(Left))
				{
					s.push(Left);
					continue;
				}
				//右
				Seat Right(Cur._x, Cur._y+1);
				if (IsPass(Right))
				{
					s.push(Right);
					continue;
				}
				_map[Entry._x][Entry._y] = 3;//表示不通路，然后pop
				s.pop();
			}
		}
			
	}
	void PrintMap()   // 打印地图
	{
		for (int i = 0; i < _row; ++i)
		{
			for (int j = 0; j < _col; j++)
			{
				cout << _map[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	~Maze()
	{
		for (int idx = 0; idx < _row; ++idx)
		{
			delete[] _map[idx];
		}
		delete[] _map;
	}

private:
	int **_map;
	int _row;
	int _col;
};

void Test()
{
	Maze maze("map.txt");
	maze.PrintMap();
	Seat seat(9,6);
	stack<Seat> s;
	maze.PassMaze(seat);
	maze.PrintMap();
	maze.PazzMaze2(s,seat);
	maze.PrintMap();
}
int main()
{
	Test();
	system("pause");
	return 0;
}
