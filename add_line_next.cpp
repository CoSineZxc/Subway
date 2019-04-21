#include "add_line_next.h"
#include <qmessagebox.h>
#include <qfile.h>
#include<qtextstream.h>

add_line_next::add_line_next(QDialog *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	
	connect(this->ui.pbtn_add_ok, SIGNAL(clicked(bool)), this, SLOT(get_pbtn_add_ok()));
	connect(this->ui.pbtn_add_can, SIGNAL(clicked(bool)), this, SLOT(get_pbtn_add_can()));
	connect(this->ui.pbtn_chg_ok, SIGNAL(clicked(bool)), this, SLOT(get_pbtn_chg_ok()));
	connect(this->ui.pbtn_chg_can, SIGNAL(clicked(bool)), this, SLOT(get_pbtn_chg_can()));
	connect(this->ui.pbtn_del_ok, SIGNAL(clicked(bool)), this, SLOT(get_pbtn_del_ok()));
	connect(this->ui.pbtn_del_can, SIGNAL(clicked(bool)), this, SLOT(get_pbtn_del_can()));
	connect(this->ui.pbtn_back, SIGNAL(clicked(bool)), this, SLOT(get_pbtn_back()));
	connect(this->ui.pbtn_clr, SIGNAL(clicked(bool)), this, SLOT(get_pbtn_clr()));
	connect(this->ui.pbtn_ok, SIGNAL(clicked(bool)), this, SLOT(get_pbtn_ok()));
}

void add_line_next::set_info(input_info* inf)
{
	this->info = inf;
}

void add_line_next::init()
{
	ui.txb_st->setText(info->disp_sta());
}

void add_line_next::get_pbtn_add_ok()
{
	int start = ui.sbx_add_num1->value();
	int end = ui.sbx_add_num2->value();
	int stnum = this->info->length_sta();
	bool dir;
	if (ui.rbtn_add_dbl->isChecked() == true)
		dir = DOUBLE;
	else
		dir = SINGLE;
	if (start != end &&start <= stnum&&end <= stnum)
	{
		road_info rd_in(start, end, dir);
		this->info->insert_rad(rd_in, this->info->length_rad() + 1);
		ui.txb_rd->setText(info->disp_rad());
	}
	ui.sbx_add_num1->setValue(1);
	ui.sbx_add_num2->setValue(1);
	ui.rbtn_add_dbl->setChecked(true);
}
void add_line_next::get_pbtn_add_can()
{
	ui.sbx_add_num1->setValue(1);
	ui.sbx_add_num2->setValue(1);
	ui.rbtn_add_dbl->setChecked(true);
}
void add_line_next::get_pbtn_chg_ok()
{
	int start = ui.sbx_chg_stnum1->value();
	int end = ui.sbx_chg_stnum2->value();
	int rdnum = ui.sbx_chg_rdnum->value();
	int stnum = this->info->length_sta();
	bool dir;
	if (ui.rbtn_chg_dbl->isChecked() == true)
		dir = DOUBLE;
	else
		dir = SINGLE;
	if (start != end &&start <= stnum&&end <= stnum)
	{
		road_info rd_in(start, end, dir);
		this->info->change_rad(rd_in, rdnum);
		ui.txb_rd->setText(info->disp_rad());
	}
	ui.sbx_chg_rdnum->setValue(1);
	ui.sbx_chg_stnum1->setValue(1);
	ui.sbx_chg_stnum2->setValue(1);
	ui.rbtn_chg_dbl->setChecked(true);
}
void add_line_next::get_pbtn_chg_can()
{
	ui.sbx_chg_rdnum->setValue(1);
	ui.sbx_chg_stnum1->setValue(1);
	ui.sbx_chg_stnum2->setValue(1);
	ui.rbtn_chg_dbl->setChecked(true);
}
void add_line_next::get_pbtn_del_ok()
{
	int delloc = ui.sbx_del_num->value();
	int rdnum = this->info->length_rad();
	if (delloc <= rdnum)
	{
		this->info->delete_rad(delloc);
		ui.txb_rd->setText(info->disp_rad());
	}
	ui.sbx_del_num->setValue(1);
}
void add_line_next::get_pbtn_del_can()
{
	ui.sbx_del_num->setValue(1);
}
void add_line_next::get_pbtn_back()
{
	this->reject();
}
void add_line_next::get_pbtn_clr()
{
	ui.sbx_add_num1->setValue(1);
	ui.sbx_add_num2->setValue(1);
	ui.rbtn_add_dbl->setChecked(true);
	ui.sbx_chg_rdnum->setValue(1);
	ui.sbx_chg_stnum1->setValue(1);
	ui.sbx_chg_stnum2->setValue(1);
	ui.rbtn_chg_dbl->setChecked(true);
	ui.sbx_del_num->setValue(1);
	this->info->clr_rad();
	ui.txb_rd->setText(info->disp_rad());
}
void add_line_next::get_pbtn_ok()
{
	int ret = QMessageBox::information(this, "确认添加线路", "确认保存新添加的线路", "确认", "取消");
	if (ret == 0)
	{
		this->close();
		QFile file("displayline.txt");
		if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
			return;
		QTextStream outfile(&file);
		outfile << this->info->name << endl;
		outfile << this->info->line_color.name() << endl;
		for (int i = 0; i < this->info->stat_list.size(); i++)
		{
			outfile << this->info->stat_list[i].name << endl;
			outfile << this->info->stat_list[i].lat << endl;
			outfile << this->info->stat_list[i].lon << endl;
		}
		for (int i = 0; i < this->info->road_list.size(); i++)
		{
			outfile << this->info->road_list[i].start - 1 << endl;
			outfile << this->info->road_list[i].end - 1 << endl;
		}
		delete info;
	}
}

