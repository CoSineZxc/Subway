#include "add_line.h"
#include"add_line_next.h"
#include<qmessagebox.h>
#include<qstring.h>

add_line::add_line(QDialog *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect(this->ui.btn_add_ok, SIGNAL(clicked(bool)), this, SLOT(get_btn_add_ok()));
	connect(this->ui.btn_add_can, SIGNAL(clicked(bool)), this, SLOT(get_btn_add_can()));
	connect(this->ui.btn_chg_ok, SIGNAL(clicked(bool)), this, SLOT(get_btn_chg_ok()));
	connect(this->ui.btn_chg_can, SIGNAL(clicked(bool)), this, SLOT(get_btn_chg_can()));
	connect(this->ui.btn_del_ok, SIGNAL(clicked(bool)), this, SLOT(get_btn_del_ok()));
	connect(this->ui.btn_del_can, SIGNAL(clicked(bool)), this, SLOT(get_btn_del_can()));
	connect(this->ui.btn_next, SIGNAL(clicked(bool)), this, SLOT(get_btn_next()));
	connect(this->ui.btn_clr, SIGNAL(clicked(bool)), this, SLOT(get_btn_clr()));
	connect(this->ui.btn_exit, SIGNAL(clicked(bool)), this, SLOT(get_btn_exit()));
}

void add_line::set_info(input_info*inp)
{
	this->info = inp;
}

void add_line::get_btn_add_ok()
{
	if (ui.lin_addst_name->text() != "")
	{
		QString name;
		double lon, lat;
		name = ui.lin_addst_name->text();
		lon = ui.sbx_addst_lon->value();
		lat = ui.sbx_addst_lat->value();
		stat_info e(name, lat, lon);
		this->info->insert_sta(e, ui.sbx_addst_num->value());
		ui.sbx_addst_num->setValue(info->length_sta() + 1);
		ui.lin_addst_name->clear();
		ui.sbx_addst_lon->setValue(0);
		ui.sbx_addst_lat->setValue(0);
		ui.txb_dsp->setText(this->info->disp_sta());
	}
}
void add_line::get_btn_add_can()
{
	ui.lin_addst_name->clear();
	ui.sbx_addst_lon->setValue(0);
	ui.sbx_addst_lat->setValue(0);
}
void add_line::get_btn_chg_ok()
{
	if (ui.lin_chgst_name->text() != "")
	{
		QString name;
		double lon, lat;
		name = ui.lin_chgst_name->text();
		lon = ui.sbx_chgst_lon->value();
		lat = ui.sbx_chgst_lat->value();
		stat_info e(name, lon, lat);
		this->info->change_sta(e, ui.sbx_chgst_num->value());
		ui.sbx_chgst_num->setValue(1);
		ui.lin_chgst_name->clear();
		ui.sbx_chgst_lon->setValue(0);
		ui.sbx_chgst_lat->setValue(0);
		ui.txb_dsp->setText(this->info->disp_sta());
	}
}
void add_line::get_btn_chg_can()
{
	ui.sbx_chgst_num->setValue(1);
	ui.lin_chgst_name->clear();
	ui.sbx_chgst_lon->setValue(0);
	ui.sbx_chgst_lat->setValue(0);
}
void add_line::get_btn_del_ok()
{
	this->info->delete_sta(ui.sbx_delst_num->value());
	ui.sbx_delst_num->setValue(1);
	ui.txb_dsp->setText(this->info->disp_sta());
	ui.sbx_addst_num->setValue(info->length_sta() + 1);
}
void add_line::get_btn_del_can()
{
	ui.sbx_delst_num->setValue(1);
	ui.txb_dsp->setText(this->info->disp_sta());
}
void add_line::get_btn_next()
{
	info->set_name(ui.lin_Lname->text());
	child.set_info(info);
	child.init();
	child.ui.sbx_add_num1->setValue(1);
	child.ui.sbx_add_num2->setValue(1);
	child.ui.sbx_chg_rdnum->setValue(1);
	child.ui.sbx_chg_stnum1->setValue(1);
	child.ui.sbx_chg_stnum2->setValue(1);
	child.ui.sbx_del_num->setValue(1);
	child.ui.txb_rd->clear();
	child.show();
}
void add_line::get_btn_exit()
{
	this->reject();
}
void add_line::get_btn_clr()
{
	ui.sbx_addst_num->setValue(1);
	ui.lin_addst_name->clear();
	ui.sbx_addst_lon->setValue(0);
	ui.sbx_addst_lat->setValue(0);
	ui.sbx_chgst_num->setValue(1);
	ui.lin_chgst_name->clear();
	ui.sbx_chgst_lon->setValue(0);
	ui.sbx_chgst_lat->setValue(0);
	ui.sbx_delst_num->setValue(1);
	ui.txb_dsp->clear();
	this->info->clr_sta();
}
/*
void add_line::closeEvent(QCloseEvent*event)
{
	delete this->info;
}
*/