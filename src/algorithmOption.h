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

// Declare the global algorithms array
extern std::vector<AlgorithmOption> algorithms;

#endif // ALGORITHMOPTION_H