#pragma once
#include"top.h"
template <class elemtype>
class priqueue
{
public:
	priqueue();
	~priqueue();
	status En_priority_queue(elemtype e, int(*compare)(elemtype, elemtype));
	status De_priority_queue(elemtype&e, int(*compare)(elemtype, elemtype));
	int efflength();
private:
	int all_length;
	int eff_length;
	elemtype*head;
	status Addspace_list();
	status Clear_list();
	status Insert_list_tail(elemtype e);
	status Delete_list_head(elemtype&e);
	status sift_up(int(*compare)(elemtype, elemtype));
	status exchange_node(int&parent, int lorr, int&Lchild, int&Rchild);
	status sift_down(int(*compare)(elemtype, elemtype));
	int Parent(int loc);
	int Leftchild(int loc);
	int Rightchild(int loc);
};

