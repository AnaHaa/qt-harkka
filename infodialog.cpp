#include "infodialog.h"
#include "ui_infodialog.h"
#include "holiday.h"

InfoDialog::InfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoDialog)
{
    ui->setupUi(this);
}

InfoDialog::~InfoDialog() {
    delete ui;
}

// Get the holiday from mainwindow
// display the data with description
void InfoDialog::setHoliday(Holiday holiday) {
    ui->locationLabel->setText(holiday.location);
    ui->weatherLabel->setText(holiday.weather);
    ui->ratingLabel->setText(QString::number(holiday.rating));
    ui->descBrowser->setText(holiday.desc);
}

void InfoDialog::on_pushButton_clicked() {
    accept();
}
