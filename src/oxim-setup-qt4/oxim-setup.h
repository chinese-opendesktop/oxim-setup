/*
*/
#ifndef OXIM_SETUP_H
#define OXIM_SETUP_H

#include <QStandardItemModel>
#include "ui_oxim-setup.h"


class mainDialog : public QDialog
{
	Q_OBJECT
	
public:
    mainDialog(QDialog *parent =0 );
    void main_init();
    void IMList_Init();
    void UpdateFont();
    void setmodelitem();

public slots:
    void AddIM_clicked();
    void DelIM_clicked();
    void DialogOK();
    void findindex(QModelIndex);
    void Default_clicked();
    void Enable_clicked();
    void Common_clicked();
    void Attribute_clicked();

private:
    Ui::mainDialog ui;
    int idx;
    QStandardItem *item[20];
    QStandardItemModel *model;

};
	
#endif 

