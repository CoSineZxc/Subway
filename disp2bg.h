#pragma once
#include"top.h"
#include"bg_graph.h"
#include<qstring.h>
#include<qvector.h>
#include<qcolor.h>
#include<qfile.h>
#include<qtextstream.h>
struct sta
{
	QString name;
	double lon, lat;
};
struct sta2sta
{
	int id1, id2;
};
struct line
{
	QString name;
	QColor color;
	QVector<sta>vlist;
	QVector<sta2sta>s2slist;
};
status disline2bgG(QVector<line> line_list, QString bgfile);
status disfile2vecline(QString disfile, QVector<line>&linelist);
status bgfile2bg(QString file_name, bg_graph*G);
