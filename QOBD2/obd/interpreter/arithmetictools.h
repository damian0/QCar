#ifndef ARITHMETICTOOLS_H
#define ARITHMETICTOOLS_H

class QString;
class QStringList;

class ArithmeticTools
{
public:
    static QStringList toPrefix(QString infix);
    static bool isOperand(QString expression);
    static bool isOperator(QString expression);
    static bool isLeftBracket(QString expression);
    static bool isRightBracket(QString expression);
    static int precedence(QString expression);
};

#endif // ARITHMETICTOOLS_H
