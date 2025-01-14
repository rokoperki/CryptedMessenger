#include "safeMessagesPage.h"

SafeMessagesPage::SafeMessagesPage(QWidget *parent) : QWidget(parent) {
    QLabel *label = new QLabel("Safe Messaging", this);
    label->setAlignment(Qt::AlignCenter);
}