#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H
#include <QPushButton>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class loginscreen; }
QT_END_NAMESPACE

class loginscreen : public QWidget
{
    Q_OBJECT

public:
    explicit loginscreen(QWidget *parent = nullptr);
    ~loginscreen();

private slots:
    void on_btnLogin_clicked();


private:
    Ui::loginscreen *ui;
    QPushButton *nutDangNhapSieuCap;
};

#endif // LOGINSCREEN_H