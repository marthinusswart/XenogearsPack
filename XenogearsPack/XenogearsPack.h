#pragma once

#include <QtWidgets/QMainWindow>
#include <QtPdf>
#include <QPdfDocument>
#include <QLabel>
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

private:
    Ui::XenogearsPackClass ui;
    QPdfDocument* xenogearsPDFDocument;
    int currentPageNumber = -1;
};
