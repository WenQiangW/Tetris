#include"FileCompress.h"


void FileCompress::Compress(const std::string& strFilePath)
{
	FILE *Fread = fopen(strFilePath.c_str(), "rb");
	if (NULL == Fread)
	{
		std::cout << strFilePath << " Not Found !" << std::endl;
		return;
	}
	CountFileInfo(Fread);

	FillCode();

	std::string CompressFileName;
	GetPrefixFileName(strFilePath, CompressFileName);
	CompressFileName += ".hgz";

	FILE *FWrite = fopen(CompressFileName.c_str(), "wb");
	if (NULL == FWrite)
	{
		cout << "打开文件失败" << endl;
		return;
	}

	WriteHead(FWrite, strFilePath);
	CompressCore(Fread, FWrite);

	fclose(Fread);
	fclose(FWrite);

}
//解压缩
//1 验证 是否为.hzp
//2 读取文件首部：重新构建哈弗曼树
//3 读取压缩信息，利用哈弗曼树，重新写入
void FileCompress::UnCompress(const std::string& strFilePath)
{
	std::string strPost = strFilePath.substr(strFilePath.find_last_of('.'));
	if (strPost.compare(".hgz") != 0)
	{
		cout << "无法解压此类文件" << endl;
		return;
	}
	FILE* Fread = fopen(strFilePath.c_str(),"rb");
	if (NULL == Fread)
	{
		return;
	}
	std::string UnCompressFileName;
	GetPrefixFileName(strFilePath, UnCompressFileName);
	std::string postFixName;
	GetHead1(Fread, postFixName);
	//GetHead(Fread, postFixName);
	UnCompressFileName += postFixName;

	FILE* FWrite = fopen(UnCompressFileName.c_str(), "wb");
	if (NULL == FWrite)
	{
		return;
	}

	UnCompressCore(Fread,FWrite);

	fclose(FWrite);
	fclose(Fread);

}
void FileCompress::UnCompressCore(FILE * Fread,FILE * Fwrite) //
{
	HuffmanTree<FileInfo> ht(_fileinfo, sizeof(_fileinfo) / sizeof(_fileinfo[0]), FileInfo());
	HuffmanTreeNode<FileInfo>* pRoot = ht.GetRoot();
	HuffmanTreeNode<FileInfo>* pCur = pRoot;
	unsigned char ReadBuf[1024];
	unsigned char WriteBuf[1024];
	size_t WritePos = 0;
	if (pRoot == NULL)
		return;
	size_t FileLen = pRoot->_weight._count;//记录一共有多少个文件信息
	while (true)
	{
		size_t ReadSize = fread(ReadBuf, 1, 1024, Fread);
		if (ReadSize == 0)
			break;
		for (size_t idx = 0; idx < ReadSize && FileLen != 0; ++idx) //多加一个条件 
		{
			int BitPos = 8; //记录一个字节
			while (BitPos >0) //读取一个字节
			{
				--BitPos;
				if (ReadBuf[idx] & (1 << BitPos))
					pCur = pCur->_pRight;
				else
					pCur = pCur->_pLeft;
				if (NULL == pCur->_pLeft && NULL == pCur->_pRight)
				{
					WriteBuf[WritePos++] = pCur->_weight._ch;
					pCur = pRoot;
					if (1024 == WritePos)
					{
						fwrite(WriteBuf, 1, 1024, Fwrite);
						WritePos = 0;
					}
					--FileLen;
				}
				//可能存在已经读取完了，
				if (0 == FileLen && WritePos < 1024 && WritePos > 0)
				{
					fwrite(WriteBuf, 1, WritePos, Fwrite);
					break;
				}
			}
		}
	}
	if (FileLen != 0) //就是当个字符,比如"aaa" 没有构建哈弗曼树
	{
		while (FileLen--)
		{
			WriteBuf[WritePos++] = pRoot->_weight._ch;
			if (1024 == WritePos)
			{
				fwrite(WriteBuf, 1, 1024, Fwrite);
				WritePos = 0;
			}
		}
		fwrite(WriteBuf, 1, WritePos, Fwrite);
	}
}
//统计信息
void FileCompress::CountFileInfo(FILE *fp)
{
	assert(fp);
	unsigned char ReadBuf[1024];
	while (true)
	{
		size_t ReadSize = fread(ReadBuf, 1, 1024, fp);
		if (ReadSize == 0)
			break;
		for (size_t idx = 0; idx < ReadSize; ++idx)
		{
			_fileinfo[ReadBuf[idx]]._count++;
		}
	}
}
//构建哈夫曼树，填充编码
void FileCompress::FillCode()
{
	FileInfo invalid;
	HuffmanTree<FileInfo> hf(_fileinfo, sizeof(_fileinfo) / sizeof(_fileinfo[0]), invalid);
	HuffmanTreeNode<FileInfo>* proot = hf.GetRoot();
	_GenerateHuffmanCode(proot);
}
//后序遍历获取编码，填充编码
void FileCompress::_GenerateHuffmanCode(HuffmanTreeNode<FileInfo>*& pRoot)
{
	if (pRoot)
	{
		_GenerateHuffmanCode(pRoot->_pLeft);
		_GenerateHuffmanCode(pRoot->_pRight);


		HuffmanTreeNode<FileInfo>* pCur = pRoot;
		HuffmanTreeNode<FileInfo>* pParent = pCur->_pParent;
		std::string strCode;
		if (NULL == pCur->_pLeft && NULL == pCur->_pRight)
		{
			while (pParent)
			{
				if (pParent->_pLeft == pCur)
					strCode += '0';
				if (pParent->_pRight == pCur)
					strCode += '1';

				pParent = pParent->_pParent;
				pCur = pCur->_pParent;
			}
			std::reverse(strCode.begin(), strCode.end());
			_fileinfo[pRoot->_weight._ch]._strCode = strCode;
		}
	}
}

//写入头部
void FileCompress::WriteHead(FILE* Fwrite, const std::string& strFilePath)
{
	// 压缩文件头格式:
	// 扩展名
	// 编码行数
	// 编码行 ...
	std::string strHead;
	GetPostfixFileName(strFilePath, strHead);
	strHead += '\n';

	size_t LineCount = 0;//计数 编码行数		
	std::string strCode; //记录字符编码信息
	unsigned char ItoaBuf[30];
	size_t idx = 0;
	while (idx < sizeof(_fileinfo) / sizeof(_fileinfo[0]))
	{
		if (_fileinfo[idx]._count)
		{
			strCode += _fileinfo[idx]._ch;
			strCode += ':';
			_itoa(_fileinfo[idx]._count, (char *)ItoaBuf, 10);
			//sprintf((char *)ItoaBuf, "%lld", _fileinfo[idx]._count);
			strCode += (char *)ItoaBuf;
			strCode += '\n';

			LineCount++;
		}
		idx++;
	}
	_itoa(LineCount, (char *)ItoaBuf, 10);
	//sprintf((char *)ItoaBuf, "%d", LineCount);
	strHead += (char *)ItoaBuf;
	strHead += '\n';

	strHead += strCode;

	fwrite(strHead.c_str(), 1, strHead.length(), Fwrite);
}

//处理头部信息,用字符串 unsigned char*
void FileCompress::GetHead(FILE *fp, std::string &FilePostfixName)
{
	assert(fp);
	unsigned char buf[1024];
	//获取后缀名
	ReadLine(fp,buf);
	FilePostfixName += (char *)buf;

	//获取行数
	ReadLine(fp, buf);
	size_t lineCount = atoi((char *)buf);
	while (lineCount--)
	{
		ReadLine(fp, buf);
		_fileinfo[*buf]._count = atoi((char *)(buf + 2));
	}
}
//读取一行信息,用字符串 unsigned char*
void FileCompress::ReadLine(FILE *fp, unsigned char *buf)
{
	assert(fp);
	size_t n = 0;
	int index = 0;
	while (fread(buf + index, 1, 1, fp) > 0)
	{
		if (index != 0 && buf[index] == '\n') // 多加一个条件index！=0 处理单行只有一个\n
			break;

		index++;
	}
	buf[index] = '\0';
}
std::string FileCompress::ReadLine1(FILE* fp)
{
	std::string strLine;
	if (feof(fp))
		return strLine;
	unsigned char c = getc(fp);
	while ('\n' != c || strLine.length() == 0) //多加一个条件，处理单行\n:继续读取信息
	{
		strLine += c;
		if (feof(fp))//看文件是否是结尾
			return strLine;
		c = getc(fp);
	}
	return strLine;
}
//处理头部，用string
void FileCompress::GetHead1(FILE* fp, std::string& strPostFix)
{
	strPostFix += ReadLine1(fp);
	int linCount = atoi(ReadLine1(fp).c_str());
	std::string strCode;
	unsigned char temp;
	while (linCount--)
	{
		strCode = ReadLine1(fp);
		temp = strCode[0];   //得转换成无符号的char
		_fileinfo[temp]._count = atoi(strCode.substr(2).c_str());

	}
}
//获取文件名后缀
void FileCompress::GetPostfixFileName(const std::string& strFilePath, std::string& PostfixFileName)
{
	PostfixFileName = strFilePath.substr(strFilePath.find_last_of('.'));
}
//获取文件名
void FileCompress::GetPrefixFileName(const std::string& strFilePath, std::string& PrefixFileName)
{
	// test.txt
	// f:\\ab\\c\\test.txt
	size_t begin = strFilePath.find_last_of("/\\");
	if (begin == std::string::npos)
	{
		begin = 0;
	}
	size_t end = strFilePath.find_last_of('.');
	PrefixFileName += strFilePath.substr(begin, end - begin);
}

void FileCompress::CompressCore(FILE* Fread, FILE* Fwrite)
{
	fseek(Fread, 0, SEEK_SET); // 把读文件指针指向开始
	unsigned char value = 0;
	unsigned char ReadBuf[1024];
	unsigned char WriteBuf[1024];
	size_t BitPos = 0;
	size_t WritePos = 0;
	while (true)
	{
		size_t ReadSize = fread(ReadBuf, 1, 1024, Fread);
		if (ReadSize == 0)
			break;
		for (size_t readidx = 0; readidx < ReadSize; ++readidx)
		{
			std::string &strCode = _fileinfo[ReadBuf[readidx]]._strCode;
			//把字符压缩编码写入文件
			if (strCode == "")
				return;
			for (size_t idx = 0; idx < strCode.length(); ++idx)
			{
				value <<= 1;//左移一位放到判断前面，因为左移一位相当于写入0
				if (strCode[idx] == '1')
					value |= 1;

				if (8 == ++BitPos)
				{
					WriteBuf[WritePos++] = value;

					if (WritePos == 1024)
					{
						fwrite(WriteBuf, 1, 1024, Fwrite);
						WritePos = 0;
					}
					BitPos = 0;
					value = 0;
				}
			}
		}
	}

	// 可能 BitPos 小于8 
	if ((BitPos > 0 && BitPos < 8) || WritePos < 1024)
	{
		value <<= (8 - BitPos);
		WriteBuf[WritePos++] = value;
		fwrite(WriteBuf, 1, WritePos, Fwrite);
	}
}

