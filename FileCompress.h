#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"Huffman.h"
using namespace std;
struct FileInfo
{
	FileInfo()
	: _count(0)
	{}
	/*FileInfo operator+(const FileInfo& FileInfoRight)//会改变原来的值
	{
	this->_count += FileInfoRight._count;
	return *this;
	}*/
	FileInfo operator+(const FileInfo& FileInfoRight)
	{
		FileInfo  temp(*this);
		temp._count += FileInfoRight._count;
		return temp;
	}
	bool operator <(const FileInfo& FileInfoRight)const
	{
		return _count < FileInfoRight._count;
	}
	bool operator >(const FileInfo& FileInfoRight)const
	{
		return _count > FileInfoRight._count;
	}
	bool operator != (const FileInfo& FileInfoRight)const
	{
		return _count != FileInfoRight._count;
	}
	std::string _strCode;//存放当前字符压缩后的编码
	unsigned char _ch;//当前字符
	size_t _count;//统计字符个数
};
class FileCompress
{
public:
	FileCompress() //构造函数
	{
		for (size_t idx = 0; idx < 256; ++idx)
		{
			_fileinfo[idx]._ch = idx;
			_fileinfo[idx]._count = 0;
		}
	}
	// 一 从文件中读取，统计字符个数
	// 二 获取编码信息: 构建哈夫曼树，从哈夫曼树种获取编码信息
	// 三 先把压缩的相关信息写入头部，文件后缀名，不同的字符个数（一个字符一行），字符的_count的值(为了还原哈弗曼树)
	// 四 把文件内容压缩后写入
	void Compress(const std::string& strFilePath);
	void UnCompress(const std::string& strFilePath);
private:
	//统计信息
	void CountFileInfo(FILE *fp);
	//构建哈夫曼树，填充编码
	void FillCode();
	//后序遍历获取编码，填充编码
	void _GenerateHuffmanCode(HuffmanTreeNode<FileInfo>*& pRoot);

	//写入头部
	void WriteHead(FILE* Fwrite, const std::string& strFilePath);
	//处理头部，用字符串char*
	void GetHead(FILE *fp, std::string &FilePostfixName);
	//读取一行信息,用字符串char*
	void ReadLine(FILE *fp, unsigned char *buf);
	//读取一行信息,用string
	std::string ReadLine1(FILE* fp);
	//处理头部，用string
	void GetHead1(FILE* fp, std::string& strPostFix);
	//获取文件名后缀
	void GetPostfixFileName(const std::string& strFilePath, std::string& PostfixFileName);
	//获取文件名字前缀
	void GetPrefixFileName(const std::string& strFilePath, std::string& PrefixFileName);

	//文件内容进行压缩写入
	void CompressCore(FILE* Fread, FILE* Fwrite);
	//把文件内容解压
	void UnCompressCore(FILE * Fread, FILE * FWrite);
private:
	FileInfo _fileinfo[256];
};