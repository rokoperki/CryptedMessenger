#ifndef SAFEMESSAGEPAGE_H
#define SAFEMESSAGEPAGE_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QCryptographicHash>
#include <QClipboard>
#include <QGuiApplication>
#include "algorithmOption.h"

class SafeMessagesPage : public QWidget {
    Q_OBJECT
public:
    SafeMessagesPage(QWidget *parent = nullptr);

private slots:
    void onEncryptButtonClicked();
    void onDecryptButtonClicked();
    void onSaveToFileButtonClicked();
    void onLoadFromFileButtonClicked();
    void onCopyTextButtonClicked();

private:
    QTextEdit *inputField;
    QTextEdit *outputField;
    QTextEdit *keyField;
    QPushButton *encryptButton;
    QPushButton *decryptButton;
    QPushButton *saveToFileButton;
    QPushButton *loadFromFileButton;
    QPushButton *copyTextButton;
};

#endif