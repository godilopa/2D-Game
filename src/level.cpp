#include "../include/level.h"
#include "../include/Markup.h" //To read XML
#include <string>

CLevel* CLevel::level = nullptr;
CMarkup xml;

CLevel& CLevel::Instance() {
	if (!level)
		level = new CLevel();
	return *level;
}

void CLevel::ReadLevel(int32 level) {
	if (level <= 3) {
		xml.Load("data/levels.xml");
		//Find levels
		xml.FindElem();
		//Go into levels to find each one 
		xml.IntoElem();
		//Find the specific level
		std::string string = "level" + std::to_string(level);
		const char* levelData = string.c_str();
		xml.FindElem(levelData);
		//Read the data from the xml
		m_nameLevel = xml.GetAttrib("name").c_str();
		m_numberGoal = stod(xml.GetAttrib("numberGoal"));
		m_numberLevel = level;
	}
}