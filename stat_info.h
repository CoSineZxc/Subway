#pragma once
#include<qstring.h>
class stat_info
{
public:
	stat_info();
	~stat_info();
	stat_info(QString n, double lo, double la);
	friend QString print_sta(stat_info elem);
	QString name;
	double lon;
	double lat;
};
