#include "algorithmOption.h"
#include <algorithm>

std::vector<AlgorithmOption> algorithms = {
    {"Caesar cipher", AlgorithmOption::encryptCaesar, AlgorithmOption::decryptCaesar},
    {"XOR cipher", AlgorithmOption::encryptXOR, AlgorithmOption::decryptXOR},
    {"Reverse cipher", AlgorithmOption::encryptReverse, AlgorithmOption::decryptReverse}
};

std::vector<SafeMessagesOption> safeMessagesAlgorithms = {
    {"Safe Messages", SafeMessagesOption::encryptSafeMessages, SafeMessagesOption::decryptSafeMessages}
};

QString AlgorithmOption::encryptCaesar(const QString &input) {
    QString result;
    for (QChar c : input) {
        result.append(QChar(c.unicode() + 1));
    }
    return result;
}

QString AlgorithmOption::encryptXOR(const QString &input) {
    QString result;
    for (QChar c : input) {
        result.append(QChar(c.unicode() ^ 0x55));
    }
    return result;
}

QString AlgorithmOption::encryptReverse(const QString &input) {
    QString result;
    for (QChar c : input) {
        result.append(QChar(c.unicode() + 3));
    }
    std::reverse(result.begin(), result.end());
    return result;
}

QString AlgorithmOption::decryptCaesar(const QString &input) {
    QString result;
    for (QChar c : input) {
        result.append(QChar(c.unicode() - 1));
    }
    return result;
}

QString AlgorithmOption::decryptXOR(const QString &input) {
    QString result;
    for (QChar c : input) {
        result.append(QChar(c.unicode() ^ 0x55));
    }
    return result;
}

QString AlgorithmOption::decryptReverse(const QString &input) {
    QString result = input;
    std::reverse(result.begin(), result.end());
    for (int i = 0; i < result.size(); ++i) {
        result[i] = QChar(result[i].unicode() - 3);
    }
    return result;
}

QString SafeMessagesOption::encryptSafeMessages(const QString &input, const QString &key) {
    QString result;
    for (int i = 0; i < input.size(); ++i) {
        result.append(QChar(input[i].unicode() ^ key[i % key.size()].unicode()));
    }
    return result;
}

QString SafeMessagesOption::decryptSafeMessages(const QString &input, const QString &key) {
    return encryptSafeMessages(input, key);
}