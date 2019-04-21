#pragma once

#include <QtWidgets/QMainWindow>
#include <QCloseEvent>
#include "top.h"
#include "ui_add_line_next.h"
#include"input_info.h"

class add_line_next : public QDialog
{
	Q_OBJECT

public:
	add_line_next(QDialog *parent = Q_NULLPTR);
	void set_info(input_info* inf);
	void init();


	Ui::add_line_next ui;
	input_info*info;
	
private slots:
	void get_pbtn_add_ok();
	void get_pbtn_add_can();
	void get_pbtn_chg_ok();
	void get_pbtn_chg_can();
	void get_pbtn_del_ok();
	void get_pbtn_del_can();
	void get_pbtn_back();
	void get_pbtn_clr();
	void get_pbtn_ok();
};
