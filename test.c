#include"contact.h"

void menu()
{
	printf("*************通讯录*****************\n");
	printf("******1.添加********2.删除**********\n");
	printf("******3.查找********4.修改**********\n");
	printf("******5.显示********6.清空**********\n");
	printf("******7.排序********0.退出**********\n");
}
enum OP
{
	EXIT,
	ADD,
	DEL,
	FIND,
	ALTER,
	SHOW,
	CLAER,
	SORT
};

int main()
{
	int input = 1;
	Contact con;
	init(&con);
	do
	{
		menu();
		printf("请选择：");
		scanf("%d", &input);
		switch (input)
		{
		case ADD:
			add_person(&con);
			break;
		case DEL:
			del_person(&con);
			break;
		case FIND:
			find_person(&con);
			break;
		case ALTER:
			alter_person(&con);
			break;
		case SHOW:
			show_person(&con);
			break;
		case CLAER:
			clear_person(&con);
			break;
		case SORT:
			sort_name(&con);
			break;
		case EXIT:
			save_data(&con);
			break;
		default:
			break;
		}
	} while (input);
	system("pause");
	return 0;
}