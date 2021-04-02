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
 * Description:     ��ʼ��ʱ����ģ���
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
 * Description:     ��ȡ���ñ����Config�ļ�
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
 * Description:     �����ñ��浽json�ļ�
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
 * Description:     ��ȡ���Ϳ��е�body
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
 * Description:     ����HTTP����
 * Access Level:    private
 * Input:           N/A
 * Output:          N/A
 * Return:          N/A
 ************************************/
void MainWindow::SendRequest(void)
{
    ui->textBrowser_receive->clear();
    QNetworkAccessManager *p_HttpMgr = new QNetworkAccessManager();
    //����¼�ѭ�����ƣ����غ������к����
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
    //������
    if (reply->error() == QNetworkReply::NoError)
    {
        qDebug() << "request protobufHttp NoError";
    }
    else
    {
        qDebug()<<"request protobufHttp handle errors here";
        QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        //statusCodeV��HTTP����������Ӧ�룬reply->error()��Qt����Ĵ����룬���Բο�QT���ĵ�
        qDebug( "request protobufHttp found error ....code: %d %d\n", statusCodeV.toInt(), (int)reply->error());
        qDebug(qPrintable(reply->errorString()));
    }
    //���󷵻صĽ��
    ui->textBrowser_receive->append(reply->readAll());
    delete reply;
    delete p_HttpMgr;
}

/************************************
 * Function:        TextEditSendEnable
 * Description:     ����TextEditSend�����޸�
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
 * Description:     ������TextEditSend�����޸�
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
 * Description:     ���Get��ѡ��
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
 * Description:     ���Get����ĵ�ѡ��
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
 * Description:     ��Э��仯д��send��
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
 * Description:     pushButton��click�ۺ���
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