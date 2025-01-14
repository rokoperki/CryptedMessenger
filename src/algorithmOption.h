#ifndef ALGORITHMOPTION_H
#define ALGORITHMOPTION_H

#include <QString>
#include <functional>
#include <vector>

class AlgorithmOption {
public:
    QString name;
    std::function<QString(const QString &)> encryptFunction;
    std::function<QString(const QString &)> decryptFunction;

    static QString encryptCaesar(const QString &input);
    static QString encryptXOR(const QString &input);
    static QString encryptReverse(const QString &input);
    static QString decryptCaesar(const QString &input);
    static QString decryptXOR(const QString &input);
    static QString decryptReverse(const QString &input);
};

class SafeMessagesOption {
public:
    QString name;
    std::function<QString(const QString &, const QString &key)> encryptFunction;
    std::function<QString(const QString &, const QString &key)> decryptFunction;

    static QString encryptSafeMessages(const QString &input, const QString &key);
    static QString decryptSafeMessages(const QString &input, const QString &key);
};

extern std::vector<AlgorithmOption> algorithms;
extern std::vector<SafeMessagesOption> safeMessagesAlgorithms;

#endif 