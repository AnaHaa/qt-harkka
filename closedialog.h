#ifndef CLOSEDIALOG_H
#define CLOSEDIALOG_H

#include <QDialog>

namespace Ui {
class CloseDialog;
}

class CloseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CloseDialog(QWidget *parent = nullptr);
    ~CloseDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::CloseDialog *ui;
};

#endif // CLOSEDIALOG_H
