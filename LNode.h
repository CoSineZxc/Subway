#pragma once
#include"top.h"
#include<qstring.h>
/***************************************************************************
��  ��  �ƣ�LNode
��      �ܣ���ͷ�ڵ������ģ����
��Ա��������data:������
			next:ָ����
˵      ����
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