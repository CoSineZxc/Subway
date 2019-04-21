#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_add_line.h"
#include "top.h"
#include"input_info.h"
#include"add_line_next.h"

class add_line : public QDialog
{
	Q_OBJECT

public:
	add_line(QDialog *parent = Q_NULLPTR);
	void set_info(input_info*inp);

	Ui::add_line ui;
	input_info*info;
	add_line_next child;

protected:
	//void closeEvent(QCloseEvent*event);

private slots:
	void get_btn_add_ok();
	void get_btn_add_can();
	void get_btn_chg_ok();
	void get_btn_chg_can();
	void get_btn_del_ok();
	void get_btn_del_can();
	void get_btn_next();
	void get_btn_exit();
	void get_btn_clr();
};
