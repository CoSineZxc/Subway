#include "priqueue.h"
#include<qdebug.h>
/***************************************************************************
�������ƣ�
��    �ܣ�˳����ʼ��
���������
�� �� ֵ��
˵    ����
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
�������ƣ�
��    �ܣ�˳�������
���������
�� �� ֵ��
˵    ����
***************************************************************************/
template <class elemtype>
priqueue<elemtype>::~priqueue()
{
	delete head;
	head = NULL;
}
/***************************************************************************
�������ƣ�Addspace_list
��    �ܣ�˳������ӳ���
���������
�� �� ֵ�����״̬����ֵ
˵    ����
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
�������ƣ�
��    �ܣ�˳�������
���������˳�������
�� �� ֵ��
˵    ����
***************************************************************************/
template <class elemtype>
status priqueue<elemtype>::Clear_list()
{
	eff_length = 0;
	return OK;
}
/***************************************************************************
�������ƣ�Insert_list_tail
��    �ܣ�˳����β������Ԫ��
������������Ա�����ã�����Ԫ��
�� �� ֵ�����״̬����ֵ
˵    ����
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
�������ƣ�Delete_list_head
��    �ܣ�˳����ͷ��ɾ��Ԫ��,��β��Ԫ�ط���ͷ��
���������˳������ã�ɾ��Ԫ�����ݣ�������ʽ��
�� �� ֵ�����״̬����ֵ
˵    ����
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
�������ƣ�Parent��Leftchild��Rightchild
��    �ܣ��ҵ��ڵ��������ж�Ӧ��˫�׽ڵ㼰���Һ��ӽڵ�
�������������λ��
�� �� ֵ����Ӧ˫�׻��ӵ�λ��
˵    ����
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
�������ƣ�sift_up
��    �ܣ��ѵ�Ԫ���ϸ�����
��������������У��ȽϺ���
�� �� ֵ��
˵    ����
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
�������ƣ�exchange_node
��    �ܣ���˫�׽���뺢�ӽ�㽻��
����������������У�˫�����ã������жϣ����Һ�������
�� �� ֵ��
˵    ����
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
�������ƣ�sift_down
��    �ܣ��ѵ�Ԫ���³�����
��������������У��ȽϺ���
�� �� ֵ��
˵    ����
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
�������ƣ�En_priority_queue
��    �ܣ����ȶ������
����������������У����Ԫ��
�� �� ֵ��
˵    ����
***************************************************************************/
template <class elemtype>
status priqueue<elemtype>::En_priority_queue(elemtype e, int(*compare)(elemtype, elemtype))
{
	Insert_list_tail(e);
	sift_up(compare);
	return OK;
}
/***************************************************************************
�������ƣ�De_priority_queue
��    �ܣ����ȶ��г���
����������������У�����Ԫ������
�� �� ֵ��
˵    ����
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