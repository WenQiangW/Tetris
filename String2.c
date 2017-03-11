//简洁版

class String()
{
public:
	String(char* pStr = "")
	{
	  if(pStr == NULL)
	  {
		_pStr = new char[1];
		_pStr = '\0';
	  }
	  else
	  {
		_pStr = new char[strlen(pStr) +1];
		strcpy(_pStr,pStr);
	  }
	}
	//拷贝构造函数
	String(const String* str)
	:_pStr(NULL) //防止临时变量_pStr指向其他地方，造成内存泄漏
	{
		//char *temp = str._pStr; //防止交换后str 为空
		String strTemp(str._pStr);
		std::swap(strTemp._pStr,_pStr);
	}
	//赋值运算符重载函数
	String& operator=(const String& str)
	{
		if(this != &str)
		{
			_pStr = NULL;
			String strTemp(str._pStr);
			std::swap(_pStr,strTemp._pStr);
		}
		return *this;
	}
private:
	char* _pStr;
}