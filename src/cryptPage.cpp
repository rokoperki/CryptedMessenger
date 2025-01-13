#include "cryptPage.h"
#include <QCryptographicHash>

CryptPage::CryptPage(QWidget *parent) : QWidget(parent) {
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
    algorithmList->addItem("Cezarova sifra");
    algorithmList->addItem("XOR sifra");
    algorithmList->addItem("Obrnuta sifra");

    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *flexLayout = new QHBoxLayout();
    QVBoxLayout *inputLayout = new QVBoxLayout();
    QVBoxLayout *outputLayout = new QVBoxLayout();
    QVBoxLayout *buttonLayout = new QVBoxLayout();

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

    mainLayout->addLayout(flexLayout);
    mainLayout->addSpacing(90);
    mainLayout->addWidget(saveToFileButton);
    mainLayout->addWidget(copyEncryptedTextButton);
    mainLayout->addStretch();

    setLayout(mainLayout);
}

void CryptPage::onEncryptButtonClicked() {
    QString inputText = inputField->toPlainText();
    QString selectedAlgorithm = algorithmList->currentText();
    QString encryptedText;

    if (selectedAlgorithm == "Cezarova sifra") {
        encryptedText = encryptAlgorithm1(inputText);
    } else if (selectedAlgorithm == "XOR sifra") {
        encryptedText = encryptAlgorithm2(inputText);
    } else if (selectedAlgorithm == "Obrnuta sifra") {
        encryptedText = encryptAlgorithm3(inputText);
    }

    outputField->setPlainText(encryptedText);
}


void CryptPage::onSaveToFileButtonClicked() {
    QString outputText = outputField->toPlainText();
    QString hash = QCryptographicHash::hash(outputText.toUtf8(), QCryptographicHash::Md5).toHex();
    QString fileName = QFileDialog::getSaveFileName(this, "Save file", "", "Binary files (*.bin)");

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly)) {
            QDataStream stream(&file);
            stream << outputText;
            stream << hash;
            file.close();
        }
    }
}

void CryptPage::onCopyEncryptedTextButtonClicked() {
    QString encryptedText = outputField->toPlainText();
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(encryptedText);
}

QString CryptPage::encryptAlgorithm1(const QString &input) {
    QString result;
    for (QChar c : input) {
        result.append(QChar(c.unicode() + 1));
    }
    return result;
}

QString CryptPage::encryptAlgorithm2(const QString &input) {
    QString result;
    for (QChar c : input) {
        result.append(QChar(c.unicode() ^ 0x55));
    }
    return result;
}

QString CryptPage::encryptAlgorithm3(const QString &input) {
    
    QString result;

    for (QChar c : input) {
        result.append(QChar(c.unicode() + 3));
    }

    std::reverse(result.begin(), result.end());

    return result;
}