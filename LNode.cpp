#include<qdebug.h>
#include"LNode.h"
template <class elemtype>
LNode<elemtype>::LNode()
{
	this->Head = new Node<elemtype>;
	if (this->Head == NULL)
	{
		qDebug() << "Space Overflow" << endl;
		exit(SPACE_OVERFLOW);
	}
	this->Head->next = NULL;
}
template <class elemtype>
LNode<elemtype>::~LNode()
{
	Node<elemtype>*p = this->Head, *q;
	for (; p != NULL; p = q)
	{
		q = p->next;
		delete p;
	}
}
/***************************************************************************
函数名称：
功    能：清空链表
输入参数：
返 回 值：
说    明：
***************************************************************************/
template <class elemtype>
status LNode<elemtype>::Clear_linklist()
{
	Node<elemtype>*p = this->Head->next, *q;
	for (; p != NULL; p = q)
	{
		q = p->next;
		delete p;
	}
	this->Head->next = NULL;
	return OK;
}
/***************************************************************************
函数名称：
功    能：链表顺序输出
输入参数：单个节点输出函数指针
返 回 值：总输出字符串
说    明：
***************************************************************************/
template <class elemtype>
QString LNode<elemtype>::print_linklist(QString(*printele)(elemtype))
{
	QString str = "";
	Node<elemtype>*p = this->Head->next;
	int i = 1;
	for (; p != NULL; p = p->next, i++)
		str += QString::number(i) + ":" + printele(p->data) + "\n";
	return str;
}
/***************************************************************************
函数名称：
功    能：链表插入元素
输入参数：插入位置（在第i元素前），插入元素
返 回 值：完成状态返回值
说    明：
***************************************************************************/
template <class elemtype>
status LNode<elemtype>::Insert_linklist(int loc, elemtype e)
{
	Node<elemtype>* p = this->Head;
	if (loc < 1)
	{
		qDebug() << "Insert Error" << endl;
		return ERROR;
	}
	for (int i = 1; p != NULL&&i <= loc - 1; i++, p = p->next)
		;
	if (p == NULL)
	{
		qDebug() << "Insert Error" << endl;
		return ERROR;
	}
	Node<elemtype>* q = new Node<elemtype>;
	if (q == NULL)
	{
		qDebug() << "Space Overflow" << endl;
		exit(SPACE_OVERFLOW);
	}
	q->data = e;
	q->next = p->next;
	p->next = q;
	return OK;
}
/***************************************************************************
函数名称：
功    能：链表删除元素
输入参数：删除位置，删除元素数据（引用形式）
返 回 值：完成状态返回值
说    明：
***************************************************************************/
template <class elemtype>
status LNode<elemtype>::Delete_linklist(int loc, elemtype e)
{
	Node<elemtype>* p = this->Head, *q;
	if (loc < 1)
	{
		qDebug() << "Delete Error" << endl;
		return ERROR;
	}
	for (int i = 1; i <= loc - 1 && p->next != NULL; i++, p = p->next)
		;
	if (p->next == NULL)
	{
		qDebug() << "Delete Error" << endl;
		return ERROR;
	}
	q = p->next;
	e = q->data;
	p->next = q->next;
	delete q;
	return OK;
}
/***************************************************************************
函数名称：
功    能：节点内容修改
输入参数：修改位置，修改内容
返 回 值：
说    明：
***************************************************************************/
template <class elemtype>
status LNode<elemtype>::Change_linklist(int loc, elemtype e)
{
	Node<elemtype>* p = this->Head, *q;
	if (loc < 1)
	{
		qDebug() << "Delete Error" << endl;
		return ERROR;
	}
	for (int i = 1; i <= loc && p != NULL; i++, p = p->next)
		;
	p->data = e;
	return OK;
}
template <class elemtype>
int LNode<elemtype>::length()
{
	int num = -1;
	Node<elemtype>* p = this->Head;
	for (; p != NULL; p = p->next, num++)
		;
	return num;
}