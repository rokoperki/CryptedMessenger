#ifndef CRYPTPAGE_H
#define CRYPTPAGE_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QComboBox>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QCryptographicHash>
#include <QClipboard>
#include <QGuiApplication>
#include "algorithmOption.h"

class CryptPage : public QWidget {
    Q_OBJECT
public:
    CryptPage(QWidget *parent = nullptr);

private slots:
    void onEncryptButtonClicked();
    void onSaveToFileButtonClicked();
    void onCopyEncryptedTextButtonClicked();

private:
    QTextEdit *inputField;
    QTextEdit *outputField;
    QPushButton *encryptButton;
    QPushButton *saveToFileButton;
    QPushButton *copyEncryptedTextButton;
    QComboBox *algorithmList;
};

#endif // CRYPTPAGE_H