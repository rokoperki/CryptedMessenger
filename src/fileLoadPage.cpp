#include "fileLoadPage.h"

FileLoadPage::FileLoadPage(QWidget *parent) : QWidget(parent) {
    QLabel *label = new QLabel("Ucitaj iz datoteke", this);
    label->setAlignment(Qt::AlignCenter);
}