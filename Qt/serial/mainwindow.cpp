#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initPort();
//    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::search);
    ui->sendButton->setEnabled(false);
    ui->baudrateBox->setCurrentIndex(3);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::search()
{
    qDebug()<<serial.portName();
    //从接收缓冲区中读取数据
    QByteArray buffer = serial.readAll();
    if(!buffer.isEmpty()){
        qDebug()<<"buffer"<<buffer;
        //从界面中读取以前收到的数据
        QString recv = ui->recvTextEdit->toPlainText();
        recv += QString(buffer);
        //清空以前的显示
        ui->recvTextEdit->clear();
        //重新显示
        ui->recvTextEdit->append(recv);
    }
    buffer.clear();

}


void MainWindow::initPort(){
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()){


        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite)){
            ui->portNameBox->addItem(info.portName());
            serial.close();
        }
    }

    QStringList baudList; //波特率
    QStringList parityList; //校验位
    QStringList dataBitsList; //数据位
    QStringList stopBitsList; //停止位

    baudList<<"50"<<"75"<<"100"<<"134"<<"150"<<"200"<<"300"
           <<"600"<<"1200"<<"1800"<<"2400"<<"4800"<<"9600"
          <<"14400"<<"19200"<<"38400"<<"56000"<<"57600"
         <<"76800"<<"115200"<<"128000"<<"256000";
    ui->baudrateBox->addItems(baudList);
    ui->baudrateBox->setCurrentIndex(12);

    parityList<<"无"<<"奇"<<"偶";
    parityList<<"标志";
    parityList<<"空格";
    ui->ParityBox->addItems(parityList);
    ui->ParityBox->setCurrentIndex(0);

    dataBitsList<<"5"<<"6"<<"7"<<"8";
    ui->dataBitsBox->addItems(dataBitsList);
    ui->dataBitsBox->setCurrentIndex(3);

    stopBitsList<<"1";
    stopBitsList<<"1.5";
    stopBitsList<<"2";
    ui->stopBitsBox->addItems(stopBitsList);
    ui->stopBitsBox->setCurrentIndex(0);

    ui->sendButton->setEnabled(true);
}

void MainWindow::on_openButton_clicked()
{
    if(ui->openButton->text()==QString("打开串口"))
    {
        //设置串口名
        serial.setPortName(ui->portNameBox->currentText());
        //设置波特率
        serial.setBaudRate(ui->baudrateBox->currentText().toInt());
        //设置数据位数
        switch(ui->dataBitsBox->currentIndex())
        {
        case 8: serial.setDataBits(QSerialPort::Data8); break;
        default: break;
        }
        //设置奇偶校验
        switch(ui->ParityBox->currentIndex())
        {
        case 0: serial.setParity(QSerialPort::NoParity); break;
        default: break;
        }
        //设置停止位
        switch(ui->stopBitsBox->currentIndex())
        {
        case 1: serial.setStopBits(QSerialPort::OneStop); break;
        case 2: serial.setStopBits(QSerialPort::TwoStop); break;
        default: break;
        }
        //设置流控制
        serial.setFlowControl(QSerialPort::NoFlowControl);

        //打开串口
        if(!serial.open(QIODevice::ReadWrite))
        {
            QMessageBox::about(NULL, "提示", "无法打开串口！");
            return;
        }
        QObject::connect(&serial, &QSerialPort::readyRead, this, &MainWindow::search);
        qDebug()<<"开";

        //下拉菜单控件失能
        ui->portNameBox->setEnabled(false);
        ui->baudrateBox->setEnabled(false);
        ui->dataBitsBox->setEnabled(false);
        ui->ParityBox->setEnabled(false);
        ui->stopBitsBox->setEnabled(false);

        ui->openButton->setText(QString("关闭串口"));
        //发送按键使能
        ui->sendButton->setEnabled(true);
    }
    else
    {
        //关闭串口
        serial.close();

        //下拉菜单控件使能
        ui->portNameBox->setEnabled(true);
        ui->baudrateBox->setEnabled(true);
        ui->dataBitsBox->setEnabled(true);
        ui->ParityBox->setEnabled(true);
        ui->stopBitsBox->setEnabled(true);

        ui->openButton->setText(QString("打开串口"));
        //发送按键失能
        ui->sendButton->setEnabled(false);
//        QObject::disconnect(&serial, &QSerialPort::readyRead, this, &MainWindow::serialPort_readyRead);
    }
}


void MainWindow::on_sendButton_clicked()
{
    qDebug()<<"发";
    //获取界面上的数据并转换成utf8格式的字节流
    QByteArray data = ui->sendTextEdit->toPlainText().toUtf8();

    qint64 byte = serial.write(data);
    qDebug()<<data<< byte;
}

void MainWindow::on_clearButton_clicked()
{
    qDebug()<<"1111";
    ui->recvTextEdit->clear();
}
