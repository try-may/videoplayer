#include "infmation.h"
#include "ui_infmation.h"
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include<iostream>
#include<qdebug.h>
#include<QMap>
extern "C" {
#include <libavformat/avformat.h>
#include <libavutil/log.h>
#include <libavutil/dict.h>
}
QMap<QString,QString> transfor = {
    {"encoder","编码"},
    {"comment","注释"},
    {"album","专辑名称"},
    {"title","标题"},
    {"artist","艺术家"},
    {"disc","唱片"},
    {"track","音轨"},
    {"major_brand","主要品牌"},
    {"minor_version","次要版本"},
    {"compatible_brands","兼容品牌"},
    {"description","描述"},
    {"creation_time","创建时间"},
    {"album_artist","专辑艺术家"},
    {"composer","作曲人"},
    {"software","软件"}
};
struct AVDictionary {
    int count;
    AVDictionaryEntry *elems;
};
infmation::infmation(QWidget *parent,QString nowpath) :
    QDialog(parent),
    ui(new Ui::infmation)
{
    this->setWindowTitle("文件信息");
    ui->setupUi(this);
    ui->label->setVisible(false);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"名称"<<"信息");
    this->setWindowTitle("文件信息");
    const char* path = nowpath.toStdString().c_str();
    //初始化封装库
    //初始化网络库（可以打开rtsp，rtmp，http协议的流媒体视频）
    avformat_network_init();

    //解封装上下文
    AVFormatContext* ic = nullptr;//将其地址做为输入，会申请一块空间，将这块空间的地址赋给ic
    //解封装上下文AVFormatContext，是存储音视频封装格式中包含信息的结构体。

    //对视频文件进行解封装操作
    int re = avformat_open_input(&ic, path, 0, nullptr);//0表示自动选择解封装器,设置一个返回值知道有无错误
    if (re != 0)//如果返回值不是0，说明打开出现错误
    {
        char buf[1024] = { 0 };
        av_strerror(re, buf, sizeof(buf) - 1);//记录错误

        ui->label->setVisible(true);
//                std::cout << "open" << path << "failed!:" << buf ;//提示错误
        return;
    }
    re = avformat_find_stream_info(ic, 0);
    //获取视频流的详细信息，包括视频流与音频流
    // url
    int i = 0;
    i =  ic->metadata->count;
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(i+2);
    ui->tableWidget->setItem(0,0,new QTableWidgetItem("文件路径"));
    ui->tableWidget->setItem(0,1,new QTableWidgetItem(ic->url));
    ui->tableWidget->setItem(1,0,new QTableWidgetItem("码率"));
    ui->tableWidget->setItem(1,1,new QTableWidgetItem((QString::number(ic->bit_rate ,'f',2))));
    //使用循环读出
    //(需要读取的数据，字段名称，前一条字段（循环时使用），参数)
    for (i = 0; i < ic->metadata->count; i++){
        ui->tableWidget->setItem(i+2,0,new QTableWidgetItem(transfor[QString::fromUtf8(ic->metadata->elems[i].key).toLower()]));
        ui->tableWidget->setItem(i+2,1,new QTableWidgetItem(ic->metadata->elems[i].value));
        qDebug()<<ic->metadata->elems[i].key;
    }
    if (ic) {//如果封装上下文仍存在
        avformat_close_input(&ic);//释放资源，指针置零
        ic = nullptr;
    }
}
void infmation::initLayout()
{
    m_layout = new QGridLayout(this);

}
infmation::~infmation()
{
    delete ui;
}
