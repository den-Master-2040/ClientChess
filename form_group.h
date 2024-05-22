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
    void join();
    void createGroup ();
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pb_create_group_clicked();

private:
    Ui::Form_group *ui;
};

#endif // FORM_GROUP_H
