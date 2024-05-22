#ifndef FORM_GROUPS_H
#define FORM_GROUPS_H

#include <QWidget>

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
private:
    Ui::form_groups *ui;
};

#endif // FORM_GROUPS_H
