#ifndef CODUPPERCASEVALIDATOR_H
#define CODUPPERCASEVALIDATOR_H

#include <QValidator>

class CodUpperCaseValidator : public QValidator
{
public:
    CodUpperCaseValidator();

    QValidator::State validate(QString &input, int &) const;
};

#endif // CODUPPERCASEVALIDATOR_H
