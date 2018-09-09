#include "test.h"
#include "ui_test.h"

test::test(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::test)
{
    ui->setupUi(this);
    tsf.connect(&tsf,SIGNAL(readyreadp2psignal(QString)),this,SLOT(readyread(QString)));
}

test::~test()
{
    delete ui;
}

void test::on_pushButton_2_clicked()
{
    tsf.connectp2p(ui->lineEdit->text());
}
void test::readyread(QString data) {
    ui->textBrowser->append(data);
}

void test::on_pushButton_clicked()
{
    tsf.send(ui->lineEdit_2->text());
}
