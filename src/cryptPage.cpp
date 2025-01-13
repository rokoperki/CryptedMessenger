#include "cryptPage.h"
#include <QCryptographicHash>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QDataStream>

CryptPage::CryptPage(QWidget *parent) : QWidget(parent)
{
    QLabel *inputLabel = new QLabel("Input:", this);
    inputField = new QTextEdit(this);
    inputField->setPlaceholderText("Enter text to encrypt");
    inputField->setFixedHeight(300);

    QLabel *outputLabel = new QLabel("Output:", this);
    outputField = new QTextEdit(this);
    outputField->setReadOnly(true);
    outputField->setFixedHeight(300);

    encryptButton = new QPushButton("Encrypt", this);
    connect(encryptButton, &QPushButton::clicked, this, &CryptPage::onEncryptButtonClicked);

    saveToFileButton = new QPushButton("Save to file", this);
    saveToFileButton->setFixedWidth(200);
    connect(saveToFileButton, &QPushButton::clicked, this, &CryptPage::onSaveToFileButtonClicked);

    copyEncryptedTextButton = new QPushButton("Copy encrypted text", this);
    copyEncryptedTextButton->setFixedWidth(200);
    connect(copyEncryptedTextButton, &QPushButton::clicked, this, &CryptPage::onCopyEncryptedTextButtonClicked);

    algorithmList = new QComboBox(this);
    for (const auto &algorithm : algorithms)
    {
        algorithmList->addItem(algorithm.name);
    }

    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *flexLayout = new QHBoxLayout();
    QVBoxLayout *inputLayout = new QVBoxLayout();
    QVBoxLayout *outputLayout = new QVBoxLayout();
    QVBoxLayout *buttonLayout = new QVBoxLayout();
    QHBoxLayout *saveButtonsLayout = new QHBoxLayout();

    inputLayout->addWidget(inputLabel);
    inputLayout->addWidget(inputField);
    inputLayout->addStretch();

    buttonLayout->addSpacing(150);
    buttonLayout->addWidget(algorithmList, 0, Qt::AlignCenter);
    buttonLayout->addSpacing(20);
    buttonLayout->addWidget(encryptButton, 0, Qt::AlignCenter);
    buttonLayout->setAlignment(Qt::AlignTop);

    outputLayout->addWidget(outputLabel);
    outputLayout->addWidget(outputField);
    outputLayout->addStretch();

    flexLayout->addLayout(inputLayout);
    flexLayout->addLayout(buttonLayout);
    flexLayout->addLayout(outputLayout);

    saveButtonsLayout->addStretch();
    saveButtonsLayout->addWidget(saveToFileButton);
    saveButtonsLayout->addWidget(copyEncryptedTextButton);
    saveButtonsLayout->addStretch();

    mainLayout->addLayout(flexLayout);
    mainLayout->addSpacing(90);
    mainLayout->addLayout(saveButtonsLayout);
    mainLayout->addStretch();

    setLayout(mainLayout);
}

void CryptPage::onEncryptButtonClicked()
{
    QString inputText = inputField->toPlainText();
    QString selectedAlgorithm = algorithmList->currentText();
    QString encryptedText;

    for (const auto &algorithm : algorithms)
    {
        if (algorithm.name == selectedAlgorithm)
        {
            encryptedText = algorithm.encryptFunction(inputText);
            break;
        }
    }

    outputField->setPlainText(encryptedText);
}

void CryptPage::onSaveToFileButtonClicked()
{
    QString outputText = outputField->toPlainText();
    QString hash = QCryptographicHash::hash(outputText.toUtf8(), QCryptographicHash::Md5).toHex();

    if (outputText.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "There is no text to save!");
        return;
    }
    

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Verify Save", "Do you want to save the file?",
    QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        QString fileName = QFileDialog::getSaveFileName(this, "Save file", "", "Binary files (*.bin)");

        if (!fileName.isEmpty())
        {
            QFile file(fileName);
            if (file.open(QIODevice::WriteOnly))
            {
                QDataStream stream(&file);
                stream << outputText;
                stream << hash;
                file.close();
            }
        }
    }
}

void CryptPage::onCopyEncryptedTextButtonClicked()
{
    QString encryptedText = outputField->toPlainText();
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(encryptedText);
}