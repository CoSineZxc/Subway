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
�������ƣ�stat_info::print_sta()
��    �ܣ����վ����Ϣ
�����������Ϣ�ַ���
�� �� ֵ��
˵    ����
***************************************************************************/
QString print_sta(stat_info elem)
{
	return elem.name + "(" + QString::number(elem.lon) + "," + QString::number(elem.lat) + ")";
}