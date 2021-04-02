#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QIntValidator>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
#include <QFile>

/************************************
 * Function:        Registration
 * Description:     初始化时进行模块绑定
 * Access Level:    private
 * Input:           N/A
 * Output:          N/A
 * Return:          N/A
 ************************************/
void MainWindow::Registration()
{
    ui->lineEdit_port->setValidator(new QIntValidator(0, 65535, this));
    mp_groupButton_http = new QButtonGroup(this);
    mp_groupButton_http->addButton(ui->radioButton_get, GET);
    mp_groupButton_http->addButton(ui->radioButton_post, POST);
    mp_groupButton_http->addButton(ui->radioButton_put, PUT);
    mp_groupButton_http->addButton(ui->radioButton_delete, DELETE);
    mp_groupButton_encrypt = new QButtonGroup(this);
    mp_groupButton_encrypt->addButton(ui->radioButton_basic, BASIC);
    mp_groupButton_encrypt->addButton(ui->radioButton_digest, DIGEST);
    connect(ui->radioButton_get, SIGNAL(clicked(bool)), this, SLOT(ClickSelectGet()));
    connect(ui->radioButton_post, SIGNAL(clicked(bool)), this, SLOT(ClickSelectPost()));
    connect(ui->radioButton_put, SIGNAL(clicked(bool)), this, SLOT(ClickSelectPost()));
    connect(ui->radioButton_delete, SIGNAL(clicked(bool)), this, SLOT(ClickSelectPost()));
    connect(ui->radioButton_basic, SIGNAL(clicked(bool)), this, SLOT(HostChange()));
    connect(ui->radioButton_digest, SIGNAL(clicked(bool)), this, SLOT(HostChange()));
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(PushButton_Click()));
    connect(ui->lineEdit_ip, SIGNAL(textChanged(const QString &)), this, SLOT(HostChange()));
    connect(ui->lineEdit_router, SIGNAL(textChanged(const QString &)), this, SLOT(HostChange()));
    connect(ui->lineEdit_port, SIGNAL(textChanged(const QString&)), this, SLOT(HostChange()));
}

/************************************
 * Function:        GetConfig
 * Description:     获取设置保存的Config文件
 * Access Level:    private
 * Input:           N/A
 * Output:          N/A
 * Return:          N/A
 ************************************/
void MainWindow::GetConfig(void)
{
    QFile file("./config.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "File open error";
        return;
    }
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject())
    {
        qDebug() << "Json Error";
        return;
    }
    QJsonObject obj = doc.object();
    ui->lineEdit_ip->setText(obj.value("ip").toString());
    ui->lineEdit_port->setText(obj.value("port").toString());
    ui->lineEdit_router->setText(obj.value("router").toString());
    ui->lineEdit_userName->setText(obj.value("userName").toString());
    ui->lineEdit_passwd->setText(obj.value("passwd").toString());
}

/************************************
 * Function:        SetConfig
 * Description:     将设置保存到json文件
 * Access Level:    private
 * Input:           N/A
 * Output:          N/A
 * Return:          N/A
 ************************************/
void MainWindow::SetConfig(void)
{
    QJsonObject obj;
    obj.insert("ip", ui->lineEdit_ip->text());
    obj.insert("port", ui->lineEdit_port->text());
    obj.insert("router", ui->lineEdit_router->text());
    obj.insert("userName", ui->lineEdit_userName->text());
    obj.insert("passwd", ui->lineEdit_passwd->text());
    QJsonDocument doc(obj);
    QFile file("./config.json");
    file.open(QIODevice::WriteOnly);
    file.write(doc.toJson());
    file.close();
}

/************************************
 * Function:        GetBodyInSend
 * Description:     获取发送框中的body
 * Access Level:    private
 * Input:           N/A
 * Output:          N/A
 * Return:          N/A
 ************************************/
QByteArray MainWindow::GetBodyInSend(QString text)
{
    QByteArray data;
    text = text.trimmed();
    qDebug() << text.mid(text.indexOf("\n\n") + 2).toLocal8Bit();
    return text.mid(text.indexOf("\n\n")).toLocal8Bit();
}

/************************************
 * Function:        SendRequest
 * Description:     发送HTTP请求
 * Access Level:    private
 * Input:           N/A
 * Output:          N/A
 * Return:          N/A
 ************************************/
void MainWindow::SendRequest(void)
{
    ui->textBrowser_receive->clear();
    QNetworkAccessManager *p_HttpMgr = new QNetworkAccessManager();
    //添加事件循环机制，返回后再运行后面的
    QEventLoop eventLoop;
    QNetworkReply* reply;
    switch (mp_groupButton_http->checkedId())
    {
        case POST:
            reply = p_HttpMgr->post(*mp_requestInfo, GetBodyInSend(ui->textEdit_send->toPlainText()));
            break;
        case GET:
            reply = p_HttpMgr->get(*mp_requestInfo);
            break;
        case PUT:
            reply = p_HttpMgr->put(*mp_requestInfo, GetBodyInSend(ui->textEdit_send->toPlainText()));
            break;
        default:
            return;
            break;
    }
    connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();
    //错误处理
    if (reply->error() == QNetworkReply::NoError)
    {
        qDebug() << "request protobufHttp NoError";
    }
    else
    {
        qDebug()<<"request protobufHttp handle errors here";
        QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        //statusCodeV是HTTP服务器的相应码，reply->error()是Qt定义的错误码，可以参考QT的文档
        qDebug( "request protobufHttp found error ....code: %d %d\n", statusCodeV.toInt(), (int)reply->error());
        qDebug(qPrintable(reply->errorString()));
    }
    //请求返回的结果
    ui->textBrowser_receive->append(reply->readAll());
    delete reply;
    delete p_HttpMgr;
}

/************************************
 * Function:        TextEditSendEnable
 * Description:     允许TextEditSend进行修改
 * Access Level:    private
 * Input:           N/A
 * Output:          N/A
 * Return:          N/A
 ************************************/
void MainWindow::TextEditSendEnable(void)
{
    ui->textEdit_send->clear();
    ui->textEdit_send->setReadOnly(false);
}

/************************************
 * Function:        TextEditSendDisable
 * Description:     不允许TextEditSend进行修改
 * Access Level:    private
 * Input:           N/A
 * Output:          N/A
 * Return:          N/A
 ************************************/
void MainWindow::TextEditSendDisable(void)
{
    ui->textEdit_send->clear();
    ui->textEdit_send->setReadOnly(true);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GetConfig();
    Registration();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/************************************
 * Function:        ClickSelectGet
 * Description:     点击Get单选键
 * Access Level:    public slots
 * Input:           N/A
 * Output:          N/A
 * Return:          N/A
 ************************************/
void MainWindow::ClickSelectGet(void)
{
    TextEditSendDisable();
    HostChange();
}

/************************************
 * Function:        ClickSelectPost
 * Description:     点击Get以外的单选键
 * Access Level:    public slots
 * Input:           N/A
 * Output:          N/A
 * Return:          N/A
 ************************************/
void MainWindow::ClickSelectPost(void)
{
    TextEditSendEnable();
    HostChange();
}

/************************************
 * Function:        HostChange
 * Description:     将协议变化写入send块
 * Access Level:    public slots
 * Input:           N/A
 * Output:          N/A
 * Return:          N/A
 ************************************/
void MainWindow::HostChange(void)
{
    QString showText = "";
    QNetworkRequest* p_requestInfo = new QNetworkRequest;
    switch (mp_groupButton_http->checkedId())
    {
        case POST:
            showText += "POST ";
            break;
        case GET:
            showText += "GET ";
            break;
        case PUT:
            showText += "PUT ";
            break;
        case DELETE:
            showText += "DELETE ";
            break;
        default:
            break;
    }

    if (ui->lineEdit_router->text()[0] != '/')
    {
        showText += "/";
    }
    showText += ui->lineEdit_router->text();
    showText += " HTTP/1.1\r\n";
    if (!ui->lineEdit_ip->text().isEmpty())
    {
        showText += "Host: " + ui->lineEdit_ip->text();
        if (!ui->lineEdit_port->text().isEmpty())
        {
            showText += ":" + ui->lineEdit_port->text() + "\r\n";
        }
    }
    
    if (!ui->lineEdit_userName->text().isEmpty() && !ui->lineEdit_passwd->text().isEmpty())
    {
        if (mp_groupButton_encrypt->checkedId() == BASIC)
        {
            QByteArray text = (ui->lineEdit_userName->text() + ":" + ui->lineEdit_passwd->text()).toLocal8Bit();
            text = text.toBase64();
            showText += "Authorization: Basic " + text + "\r\n";
            p_requestInfo->setRawHeader("Authorization", "Basic " + text + "\r\n");
        }
        else if (mp_groupButton_encrypt->checkedId() == DIGEST)
        {

        }
    }
    ui->textEdit_send->setText(showText);
    ui->textEdit_send->append("");
    QUrl url;
    url.setScheme("http");
    url.setHost(ui->lineEdit_ip->text());
    url.setPath(ui->lineEdit_router->text());
    url.setPort(ui->lineEdit_port->text().toInt());
    p_requestInfo->setUrl(QUrl(url));
    delete mp_requestInfo;
    mp_requestInfo = p_requestInfo;
}

/************************************
 * Function:        PushButton_Click
 * Description:     pushButton的click槽函数
 * Access Level:    public slots
 * Input:           N/A
 * Output:          N/A
 * Return:          N/A
 ************************************/
void MainWindow::PushButton_Click(void)
{
    SetConfig();
    SendRequest();
}