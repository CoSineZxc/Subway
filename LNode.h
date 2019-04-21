#pragma once
#include"top.h"
#include<qstring.h>
/***************************************************************************
类  名  称：LNode
功      能：带头节点的链表模板类
成员及描述：data:数据域
			next:指针域
说      明：
***************************************************************************/
template <class elemtype>
struct Node 
{
	elemtype data;
	Node *next;
};

template <class elemtype>
class LNode
{
public:
	Node<elemtype> * Head;
	LNode();
	~LNode();
	status Clear_linklist();
	QString print_linklist(QString(*printele)(elemtype));
	status Insert_linklist(int loc, elemtype e);
	status Delete_linklist(int loc, elemtype e);
	status Change_linklist(int loc, elemtype e);
	int length();
};