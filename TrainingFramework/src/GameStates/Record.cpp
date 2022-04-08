#include "Record.h"
#include "GSMenu.h"
#include "GSSelectStage.h"

void Record::ReadAll()
{
	std::string myText1;
	std::string myText2;
	file.open("../Data/Record.txt");
	if (!file.is_open())return;
	while (!file.eof()) {
		file >> myText1;
		file >> myText2;
		record.insert(record.begin(), std::pair < std::string, int>(myText1, std::stoi(myText2.c_str())));
	}
	GSMenu::difficulty = record["Difficulty"];
	GSSelectStage::currentLevel = record["CurrentLevel"];
	GSMenu::diamond = record["Diamond"];
	GSMenu::backgroundMusic = record["BackgroundMusic"];

	file.close();
}

void Record::WriteAll()
{
	file.open("../Data/Record.txt");
	record["Difficulty"] = GSMenu::difficulty;
	record["CurrentLevel"] = GSSelectStage::currentLevel;
	record["Diamond"] = GSMenu::diamond;
	record["BackgroundMusic"] = GSMenu::backgroundMusic;

	for (auto i = record.begin(); i != record.end(); i++)
	{
		std::cout << i->first << " "<< i->second << std::endl;
		file << i->first << " " << std::to_string(i->second) << std::endl;
	}
	file.close();  

}
