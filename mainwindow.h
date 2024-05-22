#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stack"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setCurrentWidget_(QWidget* w);
private:
    Ui::MainWindow *ui;
    std::stack<QWidget *> formsStack;
};
#endif // MAINWINDOW_H
