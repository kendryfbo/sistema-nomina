#ifndef UPPERCASEVALIDATOR_H
#define UPPERCASEVALIDATOR_H

#include <QValidator>

class UpperCaseValidator : public QValidator
{
public:

    UpperCaseValidator();

    QValidator::State validate(QString &input, int &) const;
};

#endif // UPPERCASEVALIDATOR_H
