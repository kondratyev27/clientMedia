#include "MainWindow.h"

#include <QApplication>
#include <QScreen>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    auto pixmap = QApplication::primaryScreen()->grabWindow(0);
    qDebug()<<"format ="<<pixmap.toImage().format();
}

MainWindow::~MainWindow()
{

}
