#include "searchdialog.h"
#include "ui_searchdialog.h"

SearchDialog::SearchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchDialog)
{
    ui->setupUi(this);
}

SearchDialog::~SearchDialog() {
    delete ui;
}

// Setup the criteria from the input
void SearchDialog::on_buttonBox_accepted() {
    criteria[0] = ui->locationBox->currentText();
    criteria[1] = ui->weatherBox->currentText();
    criteria[2] = QString::number(ui->ratingBox->value());
    accept();
}

// Return the input criteria
const QString* SearchDialog::get_criteria() {
    return criteria;
}

// Return to mainwindow without modifying data
void SearchDialog::on_buttonBox_rejected() {
    rejected();
}
