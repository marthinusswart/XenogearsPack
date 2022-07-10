#pragma once

#include <QtWidgets/QMainWindow>
#include <QtPdf>
#include <QPdfDocument>
#include <QLabel>
#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QAudioOutput>
#include <Windows.h>
#include "ui_XenogearsPack.h"

class XenogearsPack : public QMainWindow
{
    Q_OBJECT

public:
    XenogearsPack(QWidget *parent = nullptr);
    ~XenogearsPack();

private slots:
    void on_buttonPDFNext_clicked();
    void on_buttonPDFPrevious_clicked();
    void on_buttonPWPDFNext_clicked();
    void on_buttonPWPDFPrevious_clicked();
    void on_launchGameButton_clicked();
    void on_startVideoPlaybackButton_clicked();
    void on_stopVideoPlaybackButton_clicked();
    void on_skipForwardButton_clicked();

private:
    Ui::XenogearsPackClass ui;
    QPdfDocument* xenogearsPDFDocument;
    int currentPageNumber = -1;

    QMediaPlayer* m_player = nullptr;
    QAudioOutput* m_audioOutput = nullptr;
    QVideoWidget* m_videoWidget = nullptr;

    void initializeMediaPlayer();
};
