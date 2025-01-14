#include "decryptPage.h"
#include "algorithmOption.h"
#include <QCryptographicHash>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QDataStream>

DecryptPage::DecryptPage(QWidget *parent) : QWidget(parent) {
    QLabel *inputLabel = new QLabel("Input:", this);
    inputField = new QTextEdit(this);
    inputField->setPlaceholderText("Enter text to decrypt");
    inputField->setFixedHeight(300); // Set a fixed height for the input field

    QLabel *outputLabel = new QLabel("Output:", this);
    outputField = new QTextEdit(this);
    outputField->setReadOnly(true);
    outputField->setFixedHeight(300); // Set a fixed height for the output field

    decryptButton = new QPushButton("Decrypt", this);
    connect(decryptButton, &QPushButton::clicked, this, &DecryptPage::onDecryptButtonClicked);

    LoadFromFileButton = new QPushButton("Load from file", this);
    LoadFromFileButton->setFixedWidth(200);
    connect(LoadFromFileButton, &QPushButton::clicked, this, &DecryptPage::onLoadFromFileButtonClicked);

    copyDecryptedTextButton = new QPushButton("Copy decrypted text", this);
    copyDecryptedTextButton->setFixedWidth(200);
    connect(copyDecryptedTextButton, &QPushButton::clicked, this, &DecryptPage::onCopyDecryptedTextButtonClicked);

    algorithmList = new QComboBox(this);
    for (const auto &algorithm : algorithms) {
        algorithmList->addItem(algorithm.name);
    }

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *flexLayout = new QHBoxLayout();
    QVBoxLayout *inputLayout = new QVBoxLayout();
    QVBoxLayout *outputLayout = new QVBoxLayout();
    QVBoxLayout *buttonLayout = new QVBoxLayout();
    QHBoxLayout *loadButtonsLayout = new QHBoxLayout();

    inputLayout->addWidget(inputLabel);
    inputLayout->addWidget(inputField);
    inputLayout->addStretch();

    buttonLayout->addSpacing(150);
    buttonLayout->addWidget(algorithmList, 0, Qt::AlignCenter);
    buttonLayout->addSpacing(20);
    buttonLayout->addWidget(decryptButton, 0, Qt::AlignCenter);
    buttonLayout->setAlignment(Qt::AlignTop);

    outputLayout->addWidget(outputLabel);
    outputLayout->addWidget(outputField);
    outputLayout->addStretch();

    flexLayout->addLayout(inputLayout);
    flexLayout->addLayout(buttonLayout);
    flexLayout->addLayout(outputLayout);

    loadButtonsLayout->addStretch();
    loadButtonsLayout->addWidget(LoadFromFileButton);
    loadButtonsLayout->addWidget(copyDecryptedTextButton);
    loadButtonsLayout->addStretch();
    
    mainLayout->addLayout(flexLayout);
    mainLayout->addSpacing(90);
    mainLayout->addLayout(loadButtonsLayout);
    mainLayout->addStretch();

    setLayout(mainLayout);
}

void DecryptPage::onDecryptButtonClicked() {
    QString inputText = inputField->toPlainText();
    QString selectedAlgorithm = algorithmList->currentText();
    QString decryptedText;

    for (const auto &algorithm : algorithms) {
        if (algorithm.name == selectedAlgorithm) {
            decryptedText = algorithm.decryptFunction(inputText);
            break;
        }
    }

    outputField->setPlainText(decryptedText);
}

void DecryptPage::onCopyDecryptedTextButtonClicked() {
    QString decryptedText = outputField->toPlainText();
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(decryptedText);
}

void DecryptPage::onLoadFromFileButtonClicked() {
    QString filePath = QFileDialog::getOpenFileName(this, "Open File", "", "Text files (*.txt);;Binary files (*.bin)");
    if (filePath.isEmpty()) {
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error", "Could not open file for reading");
        return;
    }

    QString text;
    if (filePath.endsWith(".txt")) {
        QTextStream in(&file);
        text = in.readAll();
    } else if (filePath.endsWith(".bin")) {
        QDataStream in(&file);
        in >> text;
    }

    inputField->setPlainText(text);
    file.close();
}