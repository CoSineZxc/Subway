#pragma once
#include"top.h"
#include<qstring.h>
class road_info
{
public:
	road_info();
	~road_info();
	road_info(int s, int e, bool d = DOUBLE);
	friend QString printroad(road_info elem);
	int start;
	int end;
	bool dir;
};

