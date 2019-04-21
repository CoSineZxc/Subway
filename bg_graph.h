#pragma once
#include"LNode.h"
#include<qstring.h>
#include<qvector.h>
/***************************************************************************
�ṹ�����ƣ�arc_info
��      �ܣ��ڽӱ�߽ڵ���Ϣ
��Ա��������adjvex����Ӧ��ͷ�ڶ�����е�λ�ã�0��ͷ��
power���߽ڵ�Ȩֵ
˵      ����
***************************************************************************/
struct arc_info
{
	double power;
	int adjvex;
};
/***************************************************************************
�ṹ�����ƣ�ver_info
��      �ܣ��ڽӱ�߽ڵ���Ϣ
��Ա��������color���ڵ����״�����ף��ң�
			dist�������ľ���
			lon��γ��
			lat������
˵      ����
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
�ṹ�����ƣ�Vnode�� *V_p
��      �ܣ�����ڵ�
��Ա��������infor�����������Ϣ
			first_arc��������һ���߽ڵ�ָ��
			pre�����������ǰ���ڵ�ָ��
˵      ����
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

