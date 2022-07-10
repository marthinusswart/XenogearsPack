#include "XenogearsPack.h"
#include "videowidget.h"
#include <QFileDialog>

XenogearsPack::XenogearsPack(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    xenogearsPDFDocument = new QPdfDocument(this);  

}

XenogearsPack::~XenogearsPack()
{}

void XenogearsPack::on_buttonPDFNext_clicked()
{
    QLabel* lbl = ui.labelPDFComicView;
    QPdfDocument::DocumentError error = xenogearsPDFDocument->load("./XenogearsMedia/[FPPO] Xenogears Comic Anthology.pdf");
    if (!error)
    {        
        currentPageNumber++;
        QSize pageSize = xenogearsPDFDocument->pageSize(currentPageNumber).toSize();
        QSize lblSize = lbl->size();

        if (pageSize.height() < lblSize.height())
        {
            int differenceHeight = lblSize.height() - pageSize.height();
            float scale = (float) differenceHeight / (float) pageSize.height();
            scale += 1;
            pageSize.setHeight(lblSize.height());
            pageSize.setWidth(pageSize.width() * scale);            
        }

        QImage newImage = xenogearsPDFDocument->render(currentPageNumber, pageSize);
        lbl->setPixmap(QPixmap::fromImage(newImage));
        lbl->size().setWidth(pageSize.width());
        lbl->setMinimumWidth(pageSize.width());
    }
    else
    {
        lbl->setText("error; " + QDir::currentPath());
    }
}

void XenogearsPack::on_buttonPDFPrevious_clicked()
{
    QLabel* lbl = ui.labelPDFComicView;
    QPdfDocument::DocumentError error = xenogearsPDFDocument->load("./XenogearsMedia/[FPPO] Xenogears Comic Anthology.pdf");
    if (!error)
    {
        if (currentPageNumber > 0)
        {
            currentPageNumber--;
            QSize pageSize = xenogearsPDFDocument->pageSize(currentPageNumber).toSize();
            QSize lblSize = lbl->size();

            if (pageSize.height() < lblSize.height())
            {
                int differenceHeight = lblSize.height() - pageSize.height();
                float scale = (float)differenceHeight / (float)pageSize.height();
                scale += 1;
                pageSize.setHeight(lblSize.height());
                pageSize.setWidth(pageSize.width() * scale);
            }

            QImage newImage = xenogearsPDFDocument->render(currentPageNumber, pageSize);
            lbl->setPixmap(QPixmap::fromImage(newImage));
            lbl->size().setWidth(pageSize.width());
            lbl->setMinimumWidth(pageSize.width());
        }
    }
    else
    {
        lbl->setText("error; " + QDir::currentPath());
    }
}

void XenogearsPack::on_buttonPWPDFNext_clicked()
{
    QLabel* lbl = ui.labelPDFPerfectWorksView;
    QPdfDocument::DocumentError error = xenogearsPDFDocument->load("./XenogearsMedia/Xenogears Perfect Works.pdf");
    if (!error)
    {
        currentPageNumber++;
        QSize pageSize = xenogearsPDFDocument->pageSize(currentPageNumber).toSize();
        QSize lblSize = lbl->size();

        if (pageSize.height() > lblSize.height())
        {
            int differenceHeight = lblSize.height() - pageSize.height();
            float scale = (float)differenceHeight / (float)pageSize.height();
            scale += 1;
            pageSize.setHeight(lblSize.height());
            pageSize.setWidth(pageSize.width() * scale);
        }

        QImage newImage = xenogearsPDFDocument->render(currentPageNumber, pageSize);
        lbl->setPixmap(QPixmap::fromImage(newImage));
        lbl->size().setWidth(pageSize.width());
        lbl->setMinimumWidth(pageSize.width());
    }
    else
    {
        lbl->setText("error; " + QDir::currentPath());
    }
}

void XenogearsPack::on_buttonPWPDFPrevious_clicked()
{
    QLabel* lbl = ui.labelPDFPerfectWorksView;
    QPdfDocument::DocumentError error = xenogearsPDFDocument->load("./XenogearsMedia/Xenogears Perfect Works.pdf");
    if (!error)
    {
        if (currentPageNumber > 0)
        {
            currentPageNumber--;
            QSize pageSize = xenogearsPDFDocument->pageSize(currentPageNumber).toSize();
            QSize lblSize = lbl->size();

            if (pageSize.height() < lblSize.height())
            {
                int differenceHeight = lblSize.height() - pageSize.height();
                float scale = (float)differenceHeight / (float)pageSize.height();
                scale += 1;
                pageSize.setHeight(lblSize.height());
                pageSize.setWidth(pageSize.width() * scale);
            }

            QImage newImage = xenogearsPDFDocument->render(currentPageNumber, pageSize);
            lbl->setPixmap(QPixmap::fromImage(newImage));
            lbl->size().setWidth(pageSize.width());
            lbl->setMinimumWidth(pageSize.width());
        }
    }
    else
    {
        lbl->setText("error; " + QDir::currentPath());
    }
}

void XenogearsPack::on_launchGameButton_clicked()
{       
    QProcess* process = new QProcess(this);
    QString file = "\"" + QDir::currentPath() + "/ePSXe205/ePSXe.exe\" -nogui -loadbin \"" + 
        QDir::currentPath() + "/Xenogears/Xenogears (USA) (Disc 1).bin\" " + "-bios \"" + QDir::currentPath() + "/ePSXe205/bios/SCPH1000.BIN\"";
    process->start(file);
}

void XenogearsPack::on_startVideoPlaybackButton_clicked()
{
    initializeMediaPlayer();
    m_player->play();
}

void XenogearsPack::on_stopVideoPlaybackButton_clicked()
{
    m_player->stop();

    ui.embeddedVideoLayout->removeWidget(m_videoWidget);
    ui.embeddedVideoLayout->addWidget(ui.videoImagePlaceholderWidget);

    m_videoWidget->hide();
}

void XenogearsPack::initializeMediaPlayer()
{
    m_player = new QMediaPlayer(this);
    m_audioOutput = new QAudioOutput(this);
    m_player->setAudioOutput(m_audioOutput);

    m_videoWidget = new VideoWidget(this);
    m_videoWidget->resize(1280, 720);
    m_player->setVideoOutput(m_videoWidget);
    QUrl videoUrl = QUrl::fromLocalFile("./XenogearsMedia/Xenogears - All CGI Cutscenes 1080p.mp4");
    m_player->setSource(videoUrl);

    ui.embeddedVideoLayout->removeWidget(ui.videoImagePlaceholderWidget);
    ui.embeddedVideoLayout->addWidget(m_videoWidget);
}

void XenogearsPack::on_skipForwardButton_clicked()
{
    qint64 currentPosition = m_player->position();
    m_player->setPosition(currentPosition + 10000);
}