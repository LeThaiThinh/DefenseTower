#pragma once
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include "Singleton.h"

class Record :public CSingleton<Record>
{
public:
	Record() :file(),record() {}
	~Record(){};
	void ReadAll();
	void WriteAll();
	std::map<std::string, int> record;
	std::fstream file;
private:

};
