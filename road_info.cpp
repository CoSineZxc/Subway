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
�������ƣ�road_info::printroad()
��    �ܣ����ͨ·��Ϣ
���������
�� �� ֵ��
˵    ����
***************************************************************************/
QString printroad(road_info elem)
{
	if (elem.dir == DOUBLE)
		return QString::number(elem.start) + "<->" + QString::number(elem.end);
	else
		return QString::number(elem.start) + "-->" + QString::number(elem.end);
}