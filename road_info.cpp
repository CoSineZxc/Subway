#include "road_info.h"
road_info::road_info()
{
}


road_info::~road_info()
{
}

road_info::road_info(int s, int e, bool d)
{
	this->start = s;
	this->end = e;
	this->dir = d;
}
/***************************************************************************
函数名称：road_info::printroad()
功    能：输出通路信息
输入参数：
返 回 值：
说    明：
***************************************************************************/
QString printroad(road_info elem)
{
	if (elem.dir == DOUBLE)
		return QString::number(elem.start) + "<->" + QString::number(elem.end);
	else
		return QString::number(elem.start) + "-->" + QString::number(elem.end);
}