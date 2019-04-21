#include<qdebug.h>
#include "SubwayDemo.h"
#include "input_info.h"
#include<qfile>
SubwayDemo::SubwayDemo(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	scene = new QGraphicsScene;
	ui.graphicsView->setScene(scene);
	connect(ui.actionadd,SIGNAL(triggered()),this,SLOT(get_act_add()));
	connect(ui.pbtn_rfs, SIGNAL(clicked(bool)), this, SLOT(get_pbtn_rfs()));
	connect(ui.pbtn_ok, SIGNAL(clicked(bool)), this, SLOT(get_pbtn_ok()));
	connect(ui.pbtn_clr, SIGNAL(clicked(bool)), this, SLOT(get_pbtn_clr()));
	disfile2vecline("displayline.txt", this->linelist);
	disline2bgG(this->linelist, "SHsubwaymap.txt");
	bgfile2bg("SHsubwaymap.txt", &this->G);
	dispfile2display();
}

void SubwayDemo::get_pbtn_rfs()
{
	ui.txb_rst->clear();
	ui.lin_end->clear();
	ui.lin_start->clear();
	disfile2vecline("displayline.txt", this->linelist);
	disline2bgG(this->linelist, "SHsubwaymap.txt");
	bgfile2bg("SHsubwaymap.txt", &this->G);
	dispfile2display();
}

void SubwayDemo::get_act_add()
{
	input_info*info=new input_info;
	this->a.ui.lin_Lname->clear();
	this->a.ui.sbx_addst_num->setValue(1);
	this->a.ui.lin_addst_name->clear();
	this->a.ui.sbx_addst_lon->setValue(0);
	this->a.ui.sbx_addst_lat->setValue(0);
	this->a.ui.sbx_chgst_num->setValue(1);
	this->a.ui.lin_chgst_name->clear();
	this->a.ui.sbx_chgst_lon->setValue(0);
	this->a.ui.sbx_chgst_lat->setValue(0);
	this->a.ui.sbx_delst_num->setValue(1);
	this->a.ui.txb_dsp->clear();
	this->a.set_info(info);
	this->a.show();
}

void SubwayDemo::get_pbtn_ok()
{
	int start = 0, end = 0;
	if (ui.lin_start->text() == ui.lin_end->text() || ui.lin_end->text() == "" || ui.lin_start->text() == "")
	{
		ui.txb_rst->setText("输入存在错误");
		return;
	}
	for (; start < G.vexnum; start++)
	{
		if (G.vertices[start].info->name == ui.lin_start->text())
			break;
	}
	if (start == G.vexnum)
	{
		ui.txb_rst->setText("未找到出发站");
		return;
	}
	for (; end < G.vexnum; end++)
	{
		if (G.vertices[end].info->name == ui.lin_end->text())
			break;
	}
	if (end == G.vexnum)
	{
		ui.txb_rst->setText("未找到到达站");
		return;
	}
	G.Dijkstra(end, start);
	QString rst = "";
	for (VNode*p = &G.vertices[start]; p != &G.vertices[end]; p = p->pre)
		rst += p->info->name + "\n";
	rst += G.vertices[end].info->name;
	ui.txb_rst->setText(rst);
}
void SubwayDemo::get_pbtn_clr()
{
	ui.txb_rst->clear();
	ui.lin_end->clear();
	ui.lin_start->clear();
}

void SubwayDemo::dispfile2display()
{
	QPen pen;
	QVector<QString> namelist;
	QFont font("Microsoft YaHei", 8, 50, false);
	for (int i = 0; i < this->linelist.size(); i++)
	{
		pen.setColor(linelist[i].color);
		scene->addText(this->linelist[i].name)->setPos(this->linelist[i].vlist[0].lon, this->linelist[i].vlist[0].lat);
		for (int j = 0; j < this->linelist[i].vlist.size(); j++)
		{
			scene->addEllipse(this->linelist[i].vlist[j].lon/20-bias_x, this->linelist[i].vlist[j].lat/20-bias_y, 1, 1, pen);
			int t = 0;
			for (; t < namelist.size(); t++)
			{
				if (this->linelist[i].vlist[j].name == namelist[t])
					break;
			}
			if (t == namelist.size())
			{
				namelist.insert(namelist.begin(), this->linelist[i].vlist[j].name);
				scene->addText(this->linelist[i].vlist[j].name,font)->setPos(this->linelist[i].vlist[j].lon / 20 - bias_x, this->linelist[i].vlist[j].lat / 20 - bias_y);
			}
		}
		for (int j = 0; j < this->linelist[i].s2slist.size(); j++)
			scene->addLine(this->linelist[i].vlist[this->linelist[i].s2slist[j].id1].lon / 20 - bias_x,
				this->linelist[i].vlist[this->linelist[i].s2slist[j].id1].lat / 20 - bias_y,
				this->linelist[i].vlist[this->linelist[i].s2slist[j].id2].lon / 20 - bias_x,
				this->linelist[i].vlist[this->linelist[i].s2slist[j].id2].lat / 20 - bias_y, pen);
	}
}