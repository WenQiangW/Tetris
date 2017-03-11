//普通版
class String
{
public:
	//构造函数
	String(char *pStr = "")
	{
		if(pStr == NULL)
		{
			_pStr = new char[1];
			_pStr = '\0';
		}
		else
		{
			_pStr = new char[strlen(pStr) + 1];
			strcpy(_pStr ,pStr);
		}
	}
	//拷贝构造函数
	String(const String& str) //引用防止无限递归调用
		:_pStr(new char[strlen(str._pStr) +1])
	{
		strcpy(_pStr,str._pStr);
	}
	//赋值重载函数
	String& operator=(const String& str)
	// 返回值为引用，可以实现连续赋值
	// 参数为引用，为了不调用拷贝构造函数，减少开销
	{
		//判断是否为自我赋值 ,
		//不判断的话，可能把自己的空间释放掉，
		if(*this != str)
		{
			delete[] _pStr;
			_pStr = NULL;
			_pStr = new char[strlen(str._pStr) +1];
			strcpy(_pStr ,str._pStr);
		}
		return *this;
	}
	~String()
	{
		if(_pStr != NULL)
		{
			delete[] _pStr;
			_pStr = NULL;
		}
	}
private:
	char *_pStr;
};
