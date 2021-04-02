#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QtNetwork>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum HTTP
    {
        POST,
        GET,
        PUT,
        DELETE
    };

    enum ENCRYPTION_WORK
    {
        BASIC,
        DIGEST,
    };

private:
    QByteArray GetBodyInSend(QString text);
    void Registration(void);
    void GetConfig(void);
    void SetConfig(void);
    void SendRequest(void);
    void TextEditSendDisable(void);
    void TextEditSendEnable(void);
    Ui::MainWindow *ui;
    QButtonGroup *mp_groupButton_http;
    QButtonGroup *mp_groupButton_encrypt;
    QNetworkRequest* mp_requestInfo;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void ClickSelectGet(void);
    void ClickSelectPost(void);
    void HostChange(void);
    void PushButton_Click(void);
};
#endif // MAINWINDOW_H
