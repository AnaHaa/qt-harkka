#include "closedialog.h"
#include "ui_closedialog.h"

CloseDialog::CloseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CloseDialog)
{
    ui->setupUi(this);
}

CloseDialog::~CloseDialog()
{
    delete ui;
}

void CloseDialog::on_buttonBox_accepted()
{
    accept();
}

void CloseDialog::on_buttonBox_rejected()
{
    reject();
}
