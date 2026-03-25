#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QFileInfo>
#include <QFontDialog>
#include <QFont>
#include <QColorDialog>
#include <QColor>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>

QString currentFile;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_textEdit_cursorPositionChanged()
{
    QTextCursor cursor = ui->textEdit->textCursor();

    int line = cursor.blockNumber() + 1;
    int column = cursor.positionInBlock() + 1;
    int charCount = ui->textEdit->toPlainText().length();

    QString status = QString("Line: %1 | Column: %2 | %3 Characters")
                         .arg(line).arg(column).arg(charCount);

    ui->statusbar->showMessage(status);
}



void MainWindow::on_actionNew_triggered()
{
    currentFile = "";
    ui->textEdit->clear();
    setWindowTitle("Untitled - Notepad");
}



void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "",
                                                    "Text Files (*.txt);;All Files (*)");

    if(fileName.isEmpty())
        return;

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this, "Error", "Could not open file");
        return;
    }

    QTextStream in(&file);
    ui->textEdit->setPlainText(in.readAll());
    file.close();

    currentFile = fileName;
    setWindowTitle(QFileInfo(currentFile).fileName() + " - Notepad");
    ui->statusbar->showMessage("File Opened", 3000);
}



void MainWindow::on_actionSave_triggered()
{
    if(currentFile.isEmpty()){
        on_actionSave_all_triggered();   // Save As
        return;
    }

    QFile file(currentFile);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::warning(this, "Error", "Could not save file");
        return;
    }

    QTextStream out(&file);
    out << ui->textEdit->toPlainText();
    file.close();

    setWindowTitle(QFileInfo(currentFile).fileName() + " - Notepad");
    ui->statusbar->showMessage("File Saved", 3000);
}



void MainWindow::on_actionSave_all_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save File As", "",
                                                    "Text Files (*.txt);;All Files (*)");

    if(fileName.isEmpty())
        return;

    currentFile = fileName;
    on_actionSave_triggered();
}

void MainWindow::on_actionClose_triggered()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Close",
                                  "Do you want to save before closing?",
                                  QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

    if(reply == QMessageBox::Yes){
        on_actionSave_triggered();
        this->close();
    }
    else if(reply == QMessageBox::No){
        this->close();
    }
    else {
        return;
    }
}

void MainWindow::on_actioncopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actioncut_triggered()
{
   ui->textEdit->cut();
}


void MainWindow::on_actionpaste_triggered()
{
   ui->textEdit->paste();
}


void MainWindow::on_actionundo_triggered()
{
   ui->textEdit->undo();
}


void MainWindow::on_actionredo_triggered()
{
   ui->textEdit->redo();
}


void MainWindow::on_actionfont_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok,this);
    if(ok){
        ui->textEdit->setFont(font);

    }else {
        return;
    }
}


void MainWindow::on_actionfont_colour_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"choose color");
    if(color.isValid()){
        ui->textEdit->setTextColor((color));
    }
}


void MainWindow::on_actionBG_colour_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"choose color");
    if(color.isValid()){
        ui->textEdit->setTextBackgroundColor((color));
}
}


void MainWindow::on_actionAbout_triggered()
{
    QString about_txt;
    about_txt = "Author : code by Aditya\n";
    about_txt += "Date : 26/02/2026\n";
    about_txt += "(c) :Ntepad (R)";

    QMessageBox::about(this,"About Notepad",about_txt);


}


void MainWindow::on_actionprint_triggered()
{
    QPrinter printer;
    QPrintDialog dialog(&printer,this);
    if(dialog.exec() == QDialog::Rejected)return;
    ui->textEdit->print(&printer);

}


void MainWindow::on_actionExit_triggered()
{

}

