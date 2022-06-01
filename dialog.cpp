#include "dialog.h"
#include "ui_dialog.h"
#include "qfiledialog.h"
#include "QDir"
#include "QDirIterator"
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{

    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,[=]{
        path = QFileDialog::getExistingDirectory(this,"选择目录", "./", QFileDialog::ShowDirsOnly);
        ui->pathtext->setText(path);

    });

}

Dialog::~Dialog()
{
    delete ui;
}
