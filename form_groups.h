#ifndef FORM_GROUPS_H
#define FORM_GROUPS_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

struct group;

namespace Ui {
class form_groups;
}

class form_groups : public QWidget
{
    Q_OBJECT

public:
    explicit form_groups(QWidget *parent = nullptr);
    ~form_groups();
    void setDataGroup(QVector<group> &groups);

    QVector<QWidget*> widgetGroups;
    QVector<QLabel*> labels;
    QVector<QPushButton*> pushButtons;
private slots:
    void on_pushButton_4_clicked();

private:
    Ui::form_groups *ui;
};

#endif // FORM_GROUPS_H
