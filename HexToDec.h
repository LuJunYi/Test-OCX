#pragma once
#include <string>

class HexToDec
{
public:
	/*首先对十六进制数0xA2C除16取余，即每次取一个数，并存入数组*/
	/*这里不需要我们去处理A-F因为我们输入的就是十六进制数，计算机已经整数存储。*/
	//十六进制转十进制
	static int Hex_Conversion_Dec(std::string &aHex);
};

