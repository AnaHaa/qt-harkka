#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "holiday.h"

#include <QMainWindow>
#include <QTableWidget>
#include <QGraphicsView>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void writeSettings();
    void readSettings();
    void setWidget(QTableWidget* tableWidget, Holiday holidays[]);
    void resizeEvent(QResizeEvent* event);
    void setGraphics(QGraphicsView* graphicsview);
    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event);

private slots:
    void on_pushButton_help_clicked();
    void on_pushButton__info_clicked();
    void on_pushButton_search_clicked();
    void on_pushButton_clear_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
