#ifndef POSVIEW_H
#define POSVIEW_H

#include <QWidget>

namespace Ui {
class posview;
}

class posview : public QWidget
{
    Q_OBJECT

public:
    explicit posview(QWidget *parent = nullptr);
    ~posview();

private slots:
    void on_btnThanhToan_clicked();

private:
    Ui::posview *ui;
};

#endif // POSVIEW_H
