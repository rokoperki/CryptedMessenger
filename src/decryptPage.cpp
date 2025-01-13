#include "decryptPage.h"

DecryptPage::DecryptPage(QWidget *parent) : QWidget(parent) {
    QLabel *inputLabel = new QLabel("Input:", this);
    inputField = new QTextEdit(this);
    inputField->setPlaceholderText("Enter text to decrypt");
    inputField->setFixedHeight(100); // Set a fixed height for the input field

    QLabel *outputLabel = new QLabel("Output:", this);
    outputField = new QTextEdit(this);
    outputField->setReadOnly(true);
    outputField->setFixedHeight(100); // Set a fixed height for the output field

    decryptButton = new QPushButton("Decrypt", this);
    connect(decryptButton, &QPushButton::clicked, this, &DecryptPage::onDecryptButtonClicked);

    saveToFileButton = new QPushButton("Save to file", this);
    connect(saveToFileButton, &QPushButton::clicked, this, &DecryptPage::onSaveToFileButtonClicked);

    copyDecryptedTextButton = new QPushButton("Copy decrypted text", this);
    copyDecryptedTextButton->setFixedWidth(200);
    connect(copyDecryptedTextButton, &QPushButton::clicked, this, &DecryptPage::onCopyDecryptedTextButtonClicked);

    algorithmList = new QComboBox(this);
    algorithmList->addItem("Algorithm 1");
    algorithmList->addItem("Algorithm 2");
    algorithmList->addItem("Algorithm 3");

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    QVBoxLayout *inputLayout = new QVBoxLayout();
    QVBoxLayout *outputLayout = new QVBoxLayout();
    QVBoxLayout *buttonLayout = new QVBoxLayout();

    inputLayout->addWidget(inputLabel);
    inputLayout->addWidget(inputField);
    inputLayout->addStretch();

    buttonLayout->addSpacing(150);
    buttonLayout->addWidget(algorithmList, 0, Qt::AlignCenter);
    buttonLayout->addSpacing(20);
    buttonLayout->addWidget(decryptButton, 0, Qt::AlignCenter);
    buttonLayout->addWidget(saveToFileButton, 0, Qt::AlignCenter);
    buttonLayout->addWidget(copyDecryptedTextButton, 0, Qt::AlignCenter);
    buttonLayout->setAlignment(Qt::AlignTop);

    outputLayout->addWidget(outputLabel);
    outputLayout->addWidget(outputField);
    outputLayout->addStretch();

    mainLayout->addLayout(inputLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addLayout(outputLayout);

    setLayout(mainLayout);
}

void DecryptPage::onDecryptButtonClicked() {
    QString inputText = inputField->toPlainText();
    QString selectedAlgorithm = algorithmList->currentText();
    QString decryptedText;

    if (selectedAlgorithm == "Algorithm 1") {
        decryptedText = decryptAlgorithm1(inputText);
    } else if (selectedAlgorithm == "Algorithm 2") {
        decryptedText = decryptAlgorithm2(inputText);
    } else if (selectedAlgorithm == "Algorithm 3") {
        decryptedText = decryptAlgorithm3(inputText);
    }

    outputField->setPlainText(decryptedText);
}

void DecryptPage::onSaveToFileButtonClicked() {
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

void DecryptPage::onCopyDecryptedTextButtonClicked() {
    QString decryptedText = outputField->toPlainText();
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(decryptedText);
}

QString DecryptPage::decryptAlgorithm1(const QString &input) {
    QString result;
    for (QChar c : input) {
        result.append(QChar(c.unicode() - 1));
    }
    return result;
}

QString DecryptPage::decryptAlgorithm2(const QString &input) {
    QString result;
    for (QChar c : input) {
        result.append(QChar(c.unicode() ^ 0x55));
    }
    return result;
}

QString DecryptPage::decryptAlgorithm3(const QString &input) {
    // Reverse transposition cipher combined with substitution cipher
    QString result = input;

    // Step 1: Transposition cipher (reverse the string)
    std::reverse(result.begin(), result.end());

    // Step 2: Substitution cipher (simple shift)
    for (int i = 0; i < result.size(); ++i) {
        result[i] = QChar(result[i].unicode() - 3);
    }

    return result;
}