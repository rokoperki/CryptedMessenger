#ifndef DECRYPTPAGE_H
#define DECRYPTPAGE_H

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

class DecryptPage : public QWidget {
    Q_OBJECT
public:
    DecryptPage(QWidget *parent = nullptr);

private slots:
    void onDecryptButtonClicked();
    void onCopyDecryptedTextButtonClicked();

private:
    QTextEdit *inputField;
    QTextEdit *outputField;
    QPushButton *decryptButton;
    QPushButton *copyDecryptedTextButton;
    QComboBox *algorithmList;
};

#endif // DECRYPTPAGE_H