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

class DecryptPage : public QWidget {
    Q_OBJECT
public:
    DecryptPage(QWidget *parent = nullptr);

private slots:
    void onDecryptButtonClicked();
    void onSaveToFileButtonClicked();
    void onCopyDecryptedTextButtonClicked();

private:
    QTextEdit *inputField;
    QTextEdit *outputField;
    QPushButton *decryptButton;
    QPushButton *saveToFileButton;
    QPushButton *copyDecryptedTextButton;
    QComboBox *algorithmList;

    QString decryptAlgorithm1(const QString &input);
    QString decryptAlgorithm2(const QString &input);
    QString decryptAlgorithm3(const QString &input);
};

#endif // DECRYPTPAGE_H