#pragma once
#include <string>
#include <vector>
#include <list>
#include "Vector2.h"
#include "Rect.h"

class NumPad
{
public:
	NumPad(const Vector2& pos);
	~NumPad();
	bool UpDate(const Vector2& pos,bool flag);
	void Draw(void);
	const std::string GetInputStr(void);
	void init(void);
private:
	std::string inputStr_;
	std::list<int> inputNum_;
	std::vector<std::pair<std::string,int>> numPadStr_;
	Vector2 currentPos_;
	Rect rect_;
	int drawPadScreen_;
	int drawNumScreen_;
};

