#include "coduppercasevalidator.h"

CodUpperCaseValidator::CodUpperCaseValidator(){}

QValidator::State CodUpperCaseValidator::validate(QString &input, int &) const{
    input = input.toUpper().trimmed();
    if (input.length()<=6) return QValidator::Acceptable;
    else return QValidator::Invalid;
}
