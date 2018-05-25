#pragma once
#include <sstream>
#include <fstream>
#include <iostream>

class FileUtil
{
public:
	static std::string getFileContent(const std::string& fileName)
	{
		std::ifstream fileStream(fileName);
		if (!fileStream.is_open())
		{
			std::cout << "输入的文件" << fileName << "不存在" << std::endl;
			return "";
		}

		std::ostringstream ss;
		ss << fileStream.rdbuf();

		return ss.str();
	}
};