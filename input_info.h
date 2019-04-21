#pragma once
#include<qstring.h>
#include<qcolor.h>
#include<qvector.h>
#include"top.h"
#include"stat_info.h"
#include"road_info.h"
class input_info
{
public:
	input_info();
	~input_info();
	void set_name(QString nam);
	void insert_sta(stat_info elem, int loc);
	void insert_rad(road_info elem, int loc);
	void change_sta(stat_info elem, int loc);
	void change_rad(road_info elem, int loc);
	void delete_sta(int loc);
	void delete_rad(int loc);
	QString disp_sta();
	QString disp_rad();
	int length_sta();
	int length_rad();
	void clr_sta();
	void clr_rad();
	void set_color(QString color);
	QString name;
	QColor line_color;
	QVector<stat_info> stat_list;
	QVector<road_info> road_list;
};

