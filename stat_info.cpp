#include "stat_info.h"
stat_info::stat_info()
{
}
stat_info::~stat_info()
{
}
stat_info::stat_info(QString n, double lo, double la)
{
	this->name = n;
	this->lon = lo;
	this->lat = la;
}
/***************************************************************************
函数名称：stat_info::print_sta()
功    能：输出站点信息
输入参数：信息字符串
返 回 值：
说    明：
***************************************************************************/
QString print_sta(stat_info elem)
{
	return elem.name + "(" + QString::number(elem.lon) + "," + QString::number(elem.lat) + ")";
}