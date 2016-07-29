#ifndef LEVEL_H
#define LEVEL_H

#include "string.h"

class CLevel {
public:
	static CLevel& Instance();
	void ReadLevel(int32 level); //read the level and save tha data in the member variables
	int32 GetNumberLevel() const { return m_numberLevel; }
	String GetNameLevel() const { return m_nameLevel; }
	double GetNumberGoal() const { return m_numberGoal; }
	void SetNumberGoal(double numberGoal) { m_numberGoal = numberGoal; }
protected:
	CLevel(){};
	virtual ~CLevel(){};
private:
	static CLevel* level;
	int32 m_numberLevel;
	String m_nameLevel;
	double m_numberGoal;
};


#endif