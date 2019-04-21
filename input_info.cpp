#include "input_info.h"



input_info::input_info()
{
	this->line_color.setNamedColor("#3f9337");
}


input_info::~input_info()
{	
}

void input_info::set_name(QString nam)
{
	this->name = nam;
}
void input_info::insert_sta(stat_info elem, int loc)
{
	if (loc > 0 && loc <= stat_list.size() + 1)
		this->stat_list.insert(stat_list.begin() + loc - 1, elem);
}
void input_info::insert_rad(road_info elem, int loc)
{
	if (loc > 0 && loc <= road_list.size() + 1)
		this->road_list.insert(road_list.begin() + loc - 1, elem);
}
void input_info::change_sta(stat_info elem, int loc)
{
	if (loc>0 && loc <= stat_list.size())
		this->stat_list[loc - 1] = elem;
}
void input_info::change_rad(road_info elem, int loc)
{
	if (loc>0 && loc <= road_list.size())
		this->road_list[loc - 1] = elem;
}
void input_info::delete_sta(int loc)
{
	if (loc > 0 && loc <= stat_list.size())
		this->stat_list.remove(loc - 1);
}
void input_info::delete_rad(int loc)
{
	if (loc > 0 && loc <= road_list.size())
		this->road_list.remove(loc - 1);
}
QString input_info::disp_sta()
{
	QString rst;
	for (int i = 0; i < stat_list.size(); i++)
		rst += QString::number(i + 1) + ":" + print_sta(this->stat_list[i]) + "\n";
	return rst;
}
QString input_info::disp_rad()
{
	QString rst;
	for (int i = 0; i < road_list.size(); i++)
		rst += QString::number(i + 1) + ":" + printroad(this->road_list[i]) + "\n";
	return rst;
}
int input_info::length_sta()
{
	return this->stat_list.size();
}
int input_info::length_rad()
{
	return this->road_list.size();
}
void input_info::clr_sta()
{
	this->stat_list.clear();
}
void input_info::clr_rad()
{
	this->road_list.clear();
}

void input_info::set_color(QString color)
{
	this->line_color.setNamedColor(color);
}