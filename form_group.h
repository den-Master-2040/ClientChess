#ifndef FORM_GROUP_H
#define FORM_GROUP_H

#include <QWidget>

namespace Ui {
class Form_group;
}

class Form_group : public QWidget
{
    Q_OBJECT

public:
    explicit Form_group(QWidget *parent = nullptr);
    ~Form_group();
    QString nameAnotherPlayer = "";


    void join();
    void createGroup ();
    void connectUser (QString name);
    void messageAnothetUser(QString msg);
    void disconnectAnother();
    void setCurrentIndex_(int i);
    void setNameGroup(QString name);
    void connectWithViewers(QString name1, QString name2);
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pb_create_group_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_radioButton_clicked();

private:
    Ui::Form_group *ui;
protected:
   virtual void keyPressEvent(QKeyEvent *event);
};

#endif // FORM_GROUP_H
