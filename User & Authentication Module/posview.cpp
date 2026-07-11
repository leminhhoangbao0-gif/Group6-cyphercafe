#include "posview.h"
#include "ui_posview.h"
#include <QMessageBox>
posview::posview(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::posview)
{
    ui->setupUi(this);
}

posview::~posview()
{
    delete ui;
}

void posview::on_btnThanhToan_clicked()
{
QMessageBox::information(this, "Thông báo", "Bạn đã bấm nút Thanh toán thành công!");
}

