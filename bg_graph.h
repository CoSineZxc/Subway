#pragma once
#include"LNode.h"
#include<qstring.h>
#include<qvector.h>
/***************************************************************************
结构体名称：arc_info
功      能：邻接表边节点信息
成员及描述：adjvex：对应弧头在顶点表中的位置（0开头）
power：边节点权值
说      明：
***************************************************************************/
struct arc_info
{
	double power;
	int adjvex;
};
/***************************************************************************
结构体名称：ver_info
功      能：邻接表边节点信息
成员及描述：color：节点访问状况（白，灰）
			dist：到起点的距离
			lon：纬度
			lat：经度
说      明：
***************************************************************************/
struct ver_info
{
	int color;
	double dist;
	double XY[2];
	QVector<QString>rd_id;
	QString name;
};
struct ANode
{
	arc_info data;
	ANode*next;
};
/***************************************************************************
结构体名称：Vnode， *V_p
功      能：顶点节点
成员及描述：infor：顶点相关信息
			first_arc：下属第一个边节点指针
			pre：依据需求的前驱节点指针
说      明：
***************************************************************************/
struct VNode
{
	ver_info* info;
	ANode* firstarc = NULL;
	VNode*pre;
};
class bg_graph
{
public:
	bg_graph();
	~bg_graph();
	int vexnum;
	int arcnum;
	VNode*vertices;
	status Relax_Dij(VNode&dest, VNode&path);
	status Dijkstra(int start, int end);
};

