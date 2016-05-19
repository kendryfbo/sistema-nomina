#include "uppercasevalidator.h"

UpperCaseValidator::UpperCaseValidator(){}

QValidator::State UpperCaseValidator::validate(QString &input, int &) const{
    input = input.toUpper();
    if (input.length()<=50) return QValidator::Acceptable;
    else return QValidator::Invalid;
}
