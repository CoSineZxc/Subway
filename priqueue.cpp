#include "priqueue.h"
#include<qdebug.h>
/***************************************************************************
函数名称：
功    能：顺序表初始化
输入参数：
返 回 值：
说    明：
***************************************************************************/
template <class elemtype>
priqueue<elemtype>::priqueue()
{
	head = new elemtype[LISTSIZE];
	if (head == NULL)
	{
		qDebug() << "Space Overflow" << endl;
		exit(SPACE_OVERFLOW);
	}
	all_length = LISTSIZE;
	eff_length = 0;
}
/***************************************************************************
函数名称：
功    能：顺序表销毁
输入参数：
返 回 值：
说    明：
***************************************************************************/
template <class elemtype>
priqueue<elemtype>::~priqueue()
{
	delete head;
	head = NULL;
}
/***************************************************************************
函数名称：Addspace_list
功    能：顺序表增加长度
输入参数：
返 回 值：完成状态返回值
说    明：
***************************************************************************/
template <class elemtype>
status priqueue<elemtype>::Addspace_list()
{
	elemtype*p = new elemtype[all_length + ADDSIZE];
	if (p == NULL)
	{
		qDebug() << "Space Overflow" << endl;
		exit(SPACE_OVERFLOW);
	}
	for (int i = 0; i < all_length; i++)
		p[i] = head[i];
	delete head;
	head = p;
	all_length += ADDSIZE;
	return OK;
}
/***************************************************************************
函数名称：
功    能：顺序表的清空
输入参数：顺序表引用
返 回 值：
说    明：
***************************************************************************/
template <class elemtype>
status priqueue<elemtype>::Clear_list()
{
	eff_length = 0;
	return OK;
}
/***************************************************************************
函数名称：Insert_list_tail
功    能：顺序表从尾部插入元素
输入参数：线性表的引用，插入元素
返 回 值：完成状态返回值
说    明：
***************************************************************************/
template <class elemtype>
status priqueue<elemtype>::Insert_list_tail(elemtype e)
{
	if (eff_length >= all_length)
		this->Addspace_list();
	*(head + eff_length) = e;
	eff_length++;
	return OK;
}
/***************************************************************************
函数名称：Delete_list_head
功    能：顺序表从头部删除元素,将尾部元素放在头部
输入参数：顺序表引用，删除元素数据（引用形式）
返 回 值：完成状态返回值
说    明：
***************************************************************************/
template <class elemtype>
status priqueue<elemtype>::Delete_list_head(elemtype&e)
{
	e = head[0];
	head[0] = head[eff_length - 1];
	eff_length--;
	return OK;
}
/***************************************************************************
函数名称：Parent，Leftchild，Rightchild
功    能：找到节点在序列中对应的双亲节点及左右孩子节点
输入参数：搜索位置
返 回 值：对应双亲或孩子的位置
说    明：
***************************************************************************/
template <class elemtype>
int priqueue<elemtype>::Parent(int loc)
{
	if (loc % 2 == 0)
		return loc / 2 - 1;
	else
		return loc / 2;
}
template <class elemtype>
int priqueue<elemtype>::Leftchild(int loc)
{
	return 2 * loc + 1;
}
template <class elemtype>
int priqueue<elemtype>::Rightchild(int loc)
{
	return 2 * loc + 2;
}
/***************************************************************************
函数名称：sift_up
功    能：堆底元素上浮操作
输入参数：堆序列，比较函数
返 回 值：
说    明：
***************************************************************************/
template <class elemtype>
status priqueue<elemtype>::sift_up(int(*compare)(elemtype, elemtype))
{
	elemtype*p = &head[eff_length - 1];
	int parent = Parent(eff_length - 1), child = eff_length - 1;
	for (;;)
	{
		if (child == 0)
			break;
		if (compare(head[parent], head[child]) == MORE)
		{
			elemtype swap = head[parent];
			head[parent] = head[child];
			head[child] = swap;
			child = parent;
			parent = Parent(parent);
		}
		else
			break;
	}
	return OK;
}
/***************************************************************************
函数名称：exchange_node
功    能：将双亲结点与孩子结点交换
输入参数：队列序列，双亲引用，左右判断，左右孩子引用
返 回 值：
说    明：
***************************************************************************/
template <class elemtype>
status priqueue<elemtype>::exchange_node(int&parent, int lorr, int&Lchild, int&Rchild)
{
	int child;
	if (lorr == LEFT)
	{
		child = Leftchild(parent);
		elemtype swap = head[parent];
		head[parent] = head[child];
		head[child] = swap;
		parent = Lchild;
		Lchild = Leftchild(parent);
		Rchild = Rightchild(parent);
	}
	else
	{
		child = Rightchild(parent);
		elemtype swap = head[parent];
		head[parent] = head[child];
		head[child] = swap;
		parent = Rchild;
		Lchild = Leftchild(parent);
		Rchild = Rightchild(parent);
	}
	return OK;
}
/***************************************************************************
函数名称：sift_down
功    能：堆底元素下沉操作
输入参数：堆序列，比较函数
返 回 值：
说    明：
***************************************************************************/
template <class elemtype>
status priqueue<elemtype>::sift_down(int(*compare)(elemtype, elemtype))
{
	elemtype*p = head;
	int parent = 0, Lchild = Leftchild(0), Rchild = Rightchild(0);
	for (;;)
	{
		if (parent == eff_length - 1)
			break;
		if (Lchild >= eff_length)
			break;
		if (Rchild >= eff_length)
		{
			if (compare(head[parent], head[Lchild]) == MORE)
				exchange_node(parent, LEFT, Lchild, Rchild);
			break;
		}
		if (compare(head[parent], head[Lchild]) == MORE&& compare(head[parent], head[Rchild]) == MORE)
		{
			if (compare(head[Lchild], head[Rchild]) == MORE)
				exchange_node(parent, RIGHT, Lchild, Rchild);
			else
				exchange_node(parent, LEFT, Lchild, Rchild);
		}
		else if (compare(head[parent], head[Lchild]) == MORE)
			exchange_node(parent, LEFT, Lchild, Rchild);
		else if (compare(head[parent], head[Rchild]) == MORE)
			exchange_node(parent, RIGHT, Lchild, Rchild);
		else
			break;
	}
	return OK;
}
/***************************************************************************
函数名称：En_priority_queue
功    能：优先队列入队
输入参数：队列序列，入队元素
返 回 值：
说    明：
***************************************************************************/
template <class elemtype>
status priqueue<elemtype>::En_priority_queue(elemtype e, int(*compare)(elemtype, elemtype))
{
	Insert_list_tail(e);
	sift_up(compare);
	return OK;
}
/***************************************************************************
函数名称：De_priority_queue
功    能：优先队列出队
输入参数：队列序列，弹出元素引用
返 回 值：
说    明：
***************************************************************************/
template <class elemtype>
status priqueue<elemtype>::De_priority_queue(elemtype&e, int(*compare)(elemtype, elemtype))
{
	Delete_list_head(e);
	sift_down(compare);
	return OK;
}

template <class elemtype>
int priqueue<elemtype>::efflength()
{
	return this->eff_length;
}