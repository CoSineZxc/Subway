#pragma once

#include <QtWidgets/QMainWindow>
#include <qgraphicsview.h>
#include <qstring.h>
#include<qvector.h>
#include<qgraphicsitem.h>
#include<qpen.h>
#include "ui_SubwayDemo.h"
#include "top.h"
#include "add_line.h"
#include "bg_graph.h"
#include"disp2bg.h"


class SubwayDemo : public QMainWindow
{
	Q_OBJECT

public:
	SubwayDemo(QWidget *parent = Q_NULLPTR);


private:
	Ui::SubwayDemoClass ui;
	add_line a;
	QGraphicsScene *scene;          //³¡¾°
	bg_graph G;
	QVector<line> linelist;

private slots:
	void get_act_add();
	void get_pbtn_rfs();
	void get_pbtn_ok();
	void get_pbtn_clr();
	void dispfile2display();
};
