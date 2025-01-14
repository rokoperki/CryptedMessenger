#include "safeMessagesPage.h"
#include <QMessageBox>

SafeMessagesPage::SafeMessagesPage(QWidget *parent) : QWidget(parent) {
    QLabel *label = new QLabel("Safe Messaging", this);
    label->setAlignment(Qt::AlignCenter);

    QLabel *inputLabel = new QLabel("Input:", this);
    inputField = new QTextEdit(this);
    inputField->setPlaceholderText("Enter text to encrypt/decrypt");
    inputField->setFixedHeight(100);

    QLabel *keyLabel = new QLabel("Key:", this);
    keyField = new QTextEdit(this);
    keyField->setPlaceholderText("Enter key");
    keyField->setFixedHeight(30);

    QLabel *outputLabel = new QLabel("Output:", this);
    outputField = new QTextEdit(this);
    outputField->setReadOnly(true);
    outputField->setFixedHeight(100);

    encryptButton = new QPushButton("Encrypt", this);
    connect(encryptButton, &QPushButton::clicked, this, &SafeMessagesPage::onEncryptButtonClicked);

    decryptButton = new QPushButton("Decrypt", this);
    connect(decryptButton, &QPushButton::clicked, this, &SafeMessagesPage::onDecryptButtonClicked);

    saveToFileButton = new QPushButton("Save to file", this);
    connect(saveToFileButton, &QPushButton::clicked, this, &SafeMessagesPage::onSaveToFileButtonClicked);

    loadFromFileButton = new QPushButton("Load from file", this);
    connect(loadFromFileButton, &QPushButton::clicked, this, &SafeMessagesPage::onLoadFromFileButtonClicked);

    copyTextButton = new QPushButton("Copy text", this);
    connect(copyTextButton, &QPushButton::clicked, this, &SafeMessagesPage::onCopyTextButtonClicked);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    mainLayout->addWidget(label);
    mainLayout->addWidget(inputLabel);
    mainLayout->addWidget(inputField);
    mainLayout->addWidget(keyLabel);
    mainLayout->addWidget(keyField);
    mainLayout->addWidget(outputLabel);
    mainLayout->addWidget(outputField);

    buttonLayout->addWidget(encryptButton);
    buttonLayout->addWidget(decryptButton);
    buttonLayout->addWidget(saveToFileButton);
    buttonLayout->addWidget(loadFromFileButton);
    buttonLayout->addWidget(copyTextButton);

    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
}

void SafeMessagesPage::onEncryptButtonClicked() {
    QString inputText = inputField->toPlainText();
    QString key = keyField->toPlainText();
    QString encryptedText = SafeMessagesOption::encryptSafeMessages(inputText, key);
    outputField->setPlainText(encryptedText);
}

void SafeMessagesPage::onDecryptButtonClicked() {
    QString inputText = inputField->toPlainText();
    QString key = keyField->toPlainText();
    QString decryptedText = SafeMessagesOption::decryptSafeMessages(inputText, key);
    outputField->setPlainText(decryptedText);
}

void SafeMessagesPage::onSaveToFileButtonClicked() {
    QString outputText = outputField->toPlainText();

    if (outputText.isEmpty()) {
        QMessageBox::warning(this, "Warning", "There is no text to save!");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Save", "Do you want to save the file?",
    QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QString fileName = QFileDialog::getSaveFileName(this, "Save file", "", "Text files (*.txt);;Binary files (*.bin)");

        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (file.open(QIODevice::WriteOnly)) {
                if (fileName.endsWith(".bin")) {
                    QDataStream stream(&file);
                    stream << outputText;
                } else if (fileName.endsWith(".txt")) {
                    QTextStream stream(&file);
                    stream << outputText;
                }
                file.close();
            }
        }
    }
}
void SafeMessagesPage::onLoadFromFileButtonClicked() {
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

void SafeMessagesPage::onCopyTextButtonClicked() {
    QString text = outputField->toPlainText();
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(text);
}