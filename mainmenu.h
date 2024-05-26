#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>

namespace Ui {
class MainMenu;
}

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();
    void setCountUsers(int count);
    void setConnections(bool state);
    void setNullGroup(bool state);
private slots:
    void on_bt_create_group_clicked();

    void on_bt_connect_group_clicked();

    void on_bt_exit_clicked();

    void on_bt_profile_clicked();

    void on_bt_mm_clicked();

    void on_bt_settings_clicked();

private:
    Ui::MainMenu *ui;


};

#endif // MAINMENU_H
