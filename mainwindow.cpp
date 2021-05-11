#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "holiday.h"
#include "searchdialog.h"
#include "infodialog.h"
#include "helpdialog.h"
#include "closedialog.h"

#include <QTableWidget>
#include <QSettings>
#include <QDebug>
#include <QKeyEvent>
#include <QTranslator>
#include <QCloseEvent>

// For the desc sample
QString sampleText = "enim facilisis gravida neque convallis a cras semper auctor neque";

// Use the class created for holidays to make an array
Holiday holidays[9] = { { "Italy", "Hot", 5, sampleText }, { "Turkey", "Hot", 4, sampleText },
                      { "Spain", "Hot", 4, sampleText }, { "Finland", "Cold", 5, sampleText },
                      { "Sweden", "Cold", 3, sampleText }, { "Norway", "Cold", 4, sampleText },
                      { "Denmark", "Normal", 2, sampleText }, { "Germany", "Normal", 3, sampleText },
                      { "England", "Normal", 4, sampleText } };

// For modifying the tablewidget search
QString criteriaString[3] = {"No data", "No data", "No data"};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Check and load translation
    // edit holiday variable
    if (QLocale::system().name() == "fi_FI") {
        holidays[0] = { "Italia", "Lämmin", 5, sampleText };
        holidays[1] = { "Turkki", "Lämmin", 4, sampleText };
        holidays[2] = { "Espanja", "Lämmin", 4, sampleText };
        holidays[3] = { "Suomi", "Kylmä", 5, sampleText };
        holidays[4] = { "Ruotsi", "Kylmä", 3, sampleText };
        holidays[5] = { "Norja", "Kylmä", 4, sampleText };
        holidays[6] = { "Tanska", "Normaali", 2, sampleText };
        holidays[7] = { "Saksa", "Normaali", 3, sampleText };
        holidays[8] = { "Englanti", "Normaali", 4, sampleText };
    }

    // Initialize the QGraphicsView component
    setGraphics(ui->graphicsView);

    // Read the size and position on startup
    readSettings();

    // Initialize the QTableWidget component
    setWidget(ui->tableWidget, holidays);
}



MainWindow::~MainWindow() {
    // Write the size and position on exit
    writeSettings();
    delete ui;
}

// If user key enter on table
// get current row from table
// send current row data to dialog
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (ui->tableWidget->hasFocus()) {
        if (event->key() == Qt::Key_Enter || event->key() == 16777220) {
            QItemSelectionModel *select = ui->tableWidget->selectionModel();

            // Check the current selected row
            // first column data and get
            // index from comparison
            if (select->hasSelection()) {
                InfoDialog *infodialog = new InfoDialog(this);
                for (int i = 0; i < 9; i++) {
                    if (select->selectedRows().first().data() == holidays[i].location) {
                        infodialog->setHoliday(holidays[i]);
                        infodialog->show();
                        break;
                    }
                }
            }
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    CloseDialog closedialog;
    if (closedialog.exec() == QDialog::Accepted) {
        event->accept();
    }
}

// Incase of a resize, adjust the tableWidget
void MainWindow::resizeEvent(QResizeEvent* event) {
    // Set the column width to almost maximum to prevent horizontal scroll
    ui->tableWidget->setColumnWidth(0, ui->tableWidget->width()/3);
    ui->tableWidget->setColumnWidth(1, ui->tableWidget->width()/3);
    ui->tableWidget->setColumnWidth(2, ui->tableWidget->width()/3);

    QMainWindow::resizeEvent(event);
}

// Called on program end
// Used to store current settings
// from the program
void MainWindow::writeSettings() {
    // Name of the company and project for data saving
    QSettings windowSetting("Haarala project", "Holidayclubber");
    windowSetting.beginGroup("mainwindow");
    windowSetting.setValue("geometry", saveGeometry());
    windowSetting.setValue("savestate", saveState());
    windowSetting.setValue( "maximized", isMaximized() );
    windowSetting.setValue("criteriaLocation", QVariant::fromValue(criteriaString[0]));
    windowSetting.setValue("criteriaWeather", QVariant::fromValue(criteriaString[1]));
    windowSetting.setValue("criteriaRating", QVariant::fromValue(criteriaString[2]));

    // Save position and size if not maximixed
    if (!isMaximized()) {
        windowSetting.setValue( "pos", pos() );
        windowSetting.setValue( "size", size() );
    }

    windowSetting.endGroup();
}

// Called on program start
// Used to read previous settings
// from the program
void MainWindow::readSettings() {
    // Name of the company and project for data saving
    QSettings windowSetting("Haarala project", "Holidayclubber");

    windowSetting.beginGroup("mainwindow");
    restoreGeometry(windowSetting.value("geometry", saveGeometry() ).toByteArray());
    restoreState(windowSetting.value("savestate", saveState() ).toByteArray());
    move(windowSetting.value("pos", pos() ).toPoint());
    resize(windowSetting.value("size", size() ).toSize());
    criteriaString[0] = windowSetting.value("criteriaLocation").value<QString>();
    criteriaString[1] = windowSetting.value("criteriaWeather").value<QString>();
    criteriaString[2] = windowSetting.value("criteriaRating").value<QString>();

    // Set maximixed if maximixed
    if (windowSetting.value("maximized", isMaximized() ).toBool()) {
        showMaximized();
    }

    windowSetting.endGroup();
}

// Called on program start
// Used to initialize QTableWidget component
// using made up data class
void MainWindow::setWidget(QTableWidget* tableWidget, Holiday holidays[]) {
    // Clear header and set up
    ui->tableWidget->setRowCount(0);
    // Check if the criteria contains data
    // Program will ignore location criteria, since the table contains
    // only 1 of each locations
    if (criteriaString[0] != "No data") {
        // Clear tablewidget -> removeRow is automatic
        tableWidget->setRowCount(0);

        // Use the array to create the QTableWidget
        // with if
        for (int i = 0; i < 9; i++) {
            if (holidays[i].weather == criteriaString[1] && QString::number(holidays[i].rating) == criteriaString[2]) {
                // Insert the location column 0 and create new row
                tableWidget->insertRow ( tableWidget->rowCount() );
                tableWidget->setItem   ( tableWidget->rowCount() - 1, 0,
                                         new QTableWidgetItem(holidays[i].location) );
                // Insert the weather column 1
                tableWidget->setItem   ( tableWidget->rowCount() - 1, 1,
                                         new QTableWidgetItem(holidays[i].weather) );
                // Insert the rating column 2
                tableWidget->setItem   ( tableWidget->rowCount() - 1, 2,
                                         new QTableWidgetItem(QString::number(holidays[i].rating)) );
            }
        }
    } else {
        // Use the array to create the QTableWidget
        for (int i = 0; i < 9; i++) {
            // Insert the location column 0 and create new row
            tableWidget->insertRow ( tableWidget->rowCount() );
            tableWidget->setItem   ( tableWidget->rowCount() - 1, 0,
                                     new QTableWidgetItem(holidays[i].location) );
            // Insert the weather column 1
            tableWidget->setItem   ( tableWidget->rowCount() - 1, 1,
                                     new QTableWidgetItem(holidays[i].weather) );
            // Insert the rating column 2
            tableWidget->setItem   ( tableWidget->rowCount() - 1, 2,
                                     new QTableWidgetItem(QString::number( holidays[i].rating) ) );
        }
    }
}

// Called on program start
// Used to initialize QGraphicsView component
// with sun and rays
void MainWindow::setGraphics(QGraphicsView* graphicsView) {
    QGraphicsScene *scene = new QGraphicsScene();
    QPen pen(Qt::darkYellow);
    QBrush brush(Qt::yellow);
    scene->addEllipse(10,10,100,100, pen, brush);
    scene->addLine(150,50,250,60, pen);
    scene->addLine(150,70,230,80, pen);
    graphicsView->setScene(scene);
}

// If user accepts dialog
// Get dialog search criteria
// Redo tableWidget with criteria
void MainWindow::on_pushButton_search_clicked() {
    SearchDialog searchdialog;
    if (searchdialog.exec() == QDialog::Accepted) {
        const QString* criteria = searchdialog.get_criteria();
        for (int i = 0; i < 3; i++) {
            criteriaString[i] = criteria[i];
            setWidget(ui->tableWidget, holidays);
        }
    } else {
        // Undo the criteria
        criteriaString[0] = "No data";
        criteriaString[1] = "No data";
        criteriaString[2] = "No data";
        setWidget(ui->tableWidget, holidays);
    }
}

// Pointer to prevent automatic deletion with memory
void MainWindow::on_pushButton_help_clicked() {
    HelpDialog *helpdialog = new HelpDialog(this);
    helpdialog->show();
}

// Get current row from table
// send current row data to dialog
void MainWindow::on_pushButton__info_clicked() {
    QItemSelectionModel *select = ui->tableWidget->selectionModel();

    // Check the current selected row
    // first column data and get
    // index from comparison
    if (select->hasSelection()) {
        InfoDialog *infodialog = new InfoDialog(this);
        for (int i = 0; i < 9; i++) {
            if (select->selectedRows().first().data() == holidays[i].location) {
                infodialog->setHoliday(holidays[i]);
                infodialog->show();
                break;
            }
        }
    }
}

// Clear search criteria
void MainWindow::on_pushButton_clear_clicked() {
    criteriaString[0] = "No data";
    criteriaString[1] = "No data";
    criteriaString[2] = "No data";
    ui->tableWidget->setRowCount(0);
    setWidget(ui->tableWidget, holidays);
}
