#include "XenogearsPack.h"

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
    QPdfDocument::DocumentError error = xenogearsPDFDocument->load("./[FPPO] Xenogears Comic Anthology.pdf");
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
    QPdfDocument::DocumentError error = xenogearsPDFDocument->load("./[FPPO] Xenogears Comic Anthology.pdf");
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
