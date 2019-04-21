#include"disp2bg.h"
status disline2bgG(QVector<line> line_list,QString bgfile)
{
	QFile fileout(bgfile);
	if (!fileout.open(QIODevice::WriteOnly | QIODevice::Text))
		return ERROR;
	QTextStream out(&fileout);
	QVector<sta> staline;
	QVector<sta2sta> rdline;
	for (int i = 0; i < line_list.size(); i++)
	{
		for (int j = 0; j < line_list[i].vlist.size(); j++)
		{
			int t = 0;
			for (; t < staline.size(); t++)
				if (line_list[i].vlist[j].name == staline[t].name)
					break;
			if (t == staline.size())
				staline.insert(staline.end(), line_list[i].vlist[j]);
		}
	}
	for (int i = 0; i < line_list.size(); i++)
	{
		for (int j = 0; j < line_list[i].s2slist.size(); j++)
		{
			int m = 0;
			sta2sta node;
			for (int t = 0; t < staline.size(); t++)
			{
				if (m == 2)
					break;
				if (staline[t].name == line_list[i].vlist[line_list[i].s2slist[j].id1].name)
				{
					node.id1 = t;
					m++;
				}
				else if (staline[t].name == line_list[i].vlist[line_list[i].s2slist[j].id2].name)
				{
					node.id2 = t;
					m++;
				}
			}
			rdline.insert(rdline.end(), node);
		}
	}
	out << staline.size() << endl;
	out << rdline.size() << endl;
	for (int i = 0; i < staline.size(); i++)
	{
		out << staline[i].name << endl;
		out << staline[i].lon << endl;
		out << staline[i].lat << endl;
	}
	for (int i = 0; i < rdline.size(); i++)
	{
		out << rdline[i].id1 << endl;
		out << rdline[i].id2 << endl;
	}
	return OK;
}

void millierconv1(double&lonx, double&laty)
{
	double L = 6381372 * PI * 2;//地球周长  
	double W = L;// 平面展开后，x轴等于周长  
	double H = L / 2;// y轴约等于周长一半  
	double mill = 2.3;// 米勒投影中的一个常数，范围大约在正负2.3之间  
	double x = lonx * PI / 180;// 将经度从度数转换为弧度  
	double y = laty * PI / 180;// 将纬度从度数转换为弧度  
	y = 1.25 * log(tan(0.25 * PI + 0.4 * y));// 米勒投影的转换  
											 // 弧度转为实际距离  
	x = (W / 2) + (W / (2 * PI)) * x;
	y = (H / 2) - (H / (2 * mill)) * y;
	lonx = x;
	laty = y;
}

double power_xy1(double x1, double y1, double x2, double y2)
{
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

status disfile2vecline(QString disfile,QVector<line>&linelist)
{
	linelist.clear();
	QFile file(disfile);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return ERROR;
	QTextStream in(&file);
	while (!in.atEnd())
	{
		line linenode;
		QString line = in.readLine();
		linenode.name = line;
		line = in.readLine();
		linenode.color.setNamedColor(line);
		for (;;)
		{
			line = in.readLine();
			bool ok;
			line.toInt(&ok);
			if (ok == false)
			{
				sta stnode;
				stnode.name = line;
				line = in.readLine();
				stnode.lon = line.toDouble();
				line = in.readLine();
				stnode.lat = line.toDouble();
				millierconv1(stnode.lon, stnode.lat);
				linenode.vlist.insert(linenode.vlist.end(), stnode);
			}
			else
				break;
		}
		for (;;)
		{
			sta2sta rdnode;
			rdnode.id1 = line.toInt();
			line = in.readLine();
			rdnode.id2 = line.toInt();
			linenode.s2slist.insert(linenode.s2slist.end(), rdnode);
			line = in.readLine();
			if (line == "")
				break;
		}
		linelist.insert(linelist.end(), linenode);
	}
	return OK;
}

status bgfile2bg(QString file_name,bg_graph*G)
{
	delete G->vertices;
	QFile file(file_name);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return ERROR;
	QTextStream in(&file);
	for (int i = 0; !in.atEnd(); i++)
	{
		QString line = in.readLine();
		if (i == 0)
		{
			G->vexnum = line.toInt();
			G->vertices = new VNode[G->vexnum];
		}
		else if (i == 1)
			G->arcnum = line.toInt();
		else if (i >= 2 && i <= G->vexnum * 3 + 1)
		{
			if (i % 3 == 0)
			{
				G->vertices[i / 3 - 1].info->XY[0] = line.toDouble();
			}
			else if (i % 3 == 1)
			{
				G->vertices[i / 3 - 1].info->XY[1] = line.toDouble();
				//millierconv1(G->vertices[i / 3 - 1].info->XY[0], G->vertices[i / 3 - 1].info->XY[1]);
			}
			else
			{
				G->vertices[i / 3].info = new ver_info;
				G->vertices[i / 3].info->name = line;
				//加入查询线路id的操作
			}
		}
		else if (i > G->vexnum * 3 + 1 && i <= G->vexnum * 3 + 1 + G->arcnum)
		{
			QString line2 = in.readLine();
			ANode* arc = new ANode;
			ANode*arc2 = new ANode;
			arc->data.adjvex = line2.toInt();
			arc->data.power = power_xy1(G->vertices[line.toInt()].info->XY[0],
				G->vertices[line.toInt()].info->XY[1],
				G->vertices[line2.toInt()].info->XY[0],
				G->vertices[line2.toInt()].info->XY[1]);
			ANode*p = G->vertices[line.toInt()].firstarc;
			G->vertices[line.toInt()].firstarc = arc;
			arc->next = p;

			arc2->data.adjvex = line.toInt();
			arc2->data.power = arc->data.power;
			p = G->vertices[line2.toInt()].firstarc;
			G->vertices[line2.toInt()].firstarc = arc2;
			arc2->next = p;
		}
	}
	return OK;
}