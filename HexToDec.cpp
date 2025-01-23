#include "stdafx.h"
#include "HexToDec.h"

int HexToDec::Hex_Conversion_Dec(std::string& aHex)
{
	//int d1 = stoi(str1);
	return std::stoi(aHex, 0, 16); //转换的源字符串为十六进制，必须指定第三个参数为16
	
}
