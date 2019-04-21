#include"bg_graph.h"
#include"priqueue.h"
#include"priqueue.cpp"
#include<qfile.h>
#include<qmessagebox.h>
#include<qtextstream.h>
#include<cmath>
#include<qdebug.h>
bg_graph::~bg_graph()
{
}

void millierconv(double&lony, double&latx)//30,120
{
	double L = 6381372 * PI * 2;//�����ܳ�  
	double W = L;// ƽ��չ����x������ܳ�  
	double H = L / 2;// y��Լ�����ܳ�һ��  
	double mill = 2.3;// ����ͶӰ�е�һ����������Χ��Լ������2.3֮��  
	double x = lony * PI / 180;// �����ȴӶ���ת��Ϊ����  
	double y = latx * PI / 180;// ��γ�ȴӶ���ת��Ϊ����  
	y = 1.25 * log(tan(0.25 * PI + 0.4 * y));// ����ͶӰ��ת��  
											   // ����תΪʵ�ʾ���  
	x = (W / 2) + (W / (2 * PI)) * x;
	y = (H / 2) - (H / (2 * mill)) * y;
	latx = x;
	lony = y;
}

double power_xy(double x1, double y1, double x2, double y2)
{
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

bg_graph::bg_graph()
{
	QFile file("SHsubwaymap.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	QTextStream in(&file);
	for (int i = 0; !in.atEnd(); i++)
	{
		QString line = in.readLine();
		if (i == 0)
		{
			this->vexnum = line.toInt();
			this->vertices = new VNode[this->vexnum];
		}
		else if (i == 1)
			this->arcnum = line.toInt();
		else if (i >= 2 && i <= this->vexnum * 3 + 1)
		{
			if (i % 3 == 0)
			{
				this->vertices[i / 3 - 1].info->XY[0] = line.toDouble();
			}
			else if (i % 3 == 1)
			{
				this->vertices[i / 3 - 1].info->XY[1] = line.toDouble();
				//millierconv(vertices[i / 3 - 1].info->XY[0], vertices[i / 3 - 1].info->XY[1]);
			}
			else
			{
				this->vertices[i / 3].info = new ver_info;
				this->vertices[i / 3].info->name = line;
				//�����ѯ��·id�Ĳ���
			}
		}
		else if (i > this->vexnum * 3 + 1 && i <= this->vexnum * 3 + 1 + this->arcnum)
		{
			QString line2= in.readLine();
			ANode* arc = new ANode;
			ANode*arc2 = new ANode;
			arc->data.adjvex = line2.toInt();
			arc->data.power = power_xy(vertices[line.toInt()].info->XY[0],
				vertices[line.toInt()].info->XY[1],
				vertices[line2.toInt()].info->XY[0],
				vertices[line2.toInt()].info->XY[1]);
			ANode*p = this->vertices[line.toInt()].firstarc;
			this->vertices[line.toInt()].firstarc = arc;
			arc->next = p;

			arc2->data.adjvex = line.toInt();
			arc2->data.power = arc->data.power;
			p = this->vertices[line2.toInt()].firstarc;
			this->vertices[line2.toInt()].firstarc = arc2;
			arc2->next = p;
		}
	}
}

int compare_arc_info(arc_info a, arc_info b)
{
	if (a.adjvex == b.adjvex)
		return EQUAL;
	else
		return INEQUAL;
}
/***************************************************************************
�������ƣ�Relax_Dij
��    �ܣ��ɳڲ�����������·����
���������Ŀ�ĵأ�;����
�� �� ֵ��
˵    ����
***************************************************************************/
status bg_graph::Relax_Dij(VNode&dest, VNode&path)
{
	double path_power;
	int p = &path - this->vertices;
	ANode*path_p = this->vertices[p].firstarc;
	for (; path_p != NULL; path_p = path_p->next)
	{
		if (path_p->data.adjvex == &dest - vertices)
		{
			path_power = path_p->data.power;
			break;
		}
	}
	if (path_p == NULL)
		path_power = DOUBLE_INFINITY;
	if (dest.info->dist > path.info->dist + path_power)
	{
		dest.info->dist = path.info->dist + path_power;
		dest.pre = &path;
	}
	return OK;
}
int compare_ver_dist(VNode*a, VNode*b)
{
	if (a->info->dist > b->info->dist)
		return MORE;
	else if (a->info->dist < b->info->dist)
		return LESS;
	else
		return EQUAL;
}
/***************************************************************************
�������ƣ�Dijkstra
��    �ܣ����·���㷨
���������ͼ��Ȩֵ���࣬���
�� �� ֵ��
˵    ����
***************************************************************************/
status bg_graph::Dijkstra(int start,int end)
{
	priqueue<VNode*> Q;
	for (int i = 0; i < vexnum; i++)//��ʼ��
	{
		vertices[i].info->color = WHITE;
		if (i != start)
			vertices[i].info->dist = DOUBLE_INFINITY;
		else
			vertices[i].info->dist = 0;
		Q.En_priority_queue(&vertices[i], compare_ver_dist);
	}
	for (; Q.efflength() != 0;)
	{
		VNode* e;
		Q.De_priority_queue(e, compare_ver_dist);
		for (; e->info->color == GRAY;)
			Q.De_priority_queue(e, compare_ver_dist);
		for (ANode*p = e->firstarc; p != NULL; p = p->next)
		{
			double before = vertices[p->data.adjvex].info->dist;
			Relax_Dij(vertices[p->data.adjvex], *e);
			if (vertices[p->data.adjvex].info->dist < before)
				Q.En_priority_queue(&vertices[p->data.adjvex], compare_ver_dist);
		}
		e->info->color = GRAY;
		if (e - vertices == end)
			break;
	}
	return OK;
}