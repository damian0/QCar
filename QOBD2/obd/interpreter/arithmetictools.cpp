#include "arithmetictools.h"
#include <QStringList>
#include <QStringListIterator>
#include <QDebug>
#include <QStack>

QStringList ArithmeticTools::toPrefix(QString infix)
{
    QStringList prefix;
    QString str = "";

    QStringList expressions = infix.split(" ");
    QStack<QString> expressionsStack;

    QStringList::const_iterator it;
    for(it=expressions.cend()-1; it != expressions.cbegin()-1; --it)
    {
        str = (*it);

        if(isOperand(str))
        {
            prefix.prepend(str);
        }
        else if(isRightBracket(str))
        {
            expressionsStack.push(str);
        }
        else if(isLeftBracket(str))
        {
            QString tmp = "";
            while(!expressionsStack.isEmpty() && !isRightBracket(tmp = expressionsStack.pop()))
            {
                prefix.prepend(tmp);
            }
        }
        else if(isOperator(str))
        {
            if(expressionsStack.isEmpty())
            {
                expressionsStack.push(str);
            }
            else
            {
                while (!expressionsStack.isEmpty())
                {
                    QString onTop = expressionsStack.pop();
                    int precedenceOnTop = precedence(onTop);
                    int precedenceScanned = precedence(str);
                    if (precedenceOnTop > precedenceScanned)
                    {
                        prefix.prepend(onTop);
                    }
                    else
                    {
                        expressionsStack.push(onTop);
                        break;
                    }
                }
                expressionsStack.push(str);
            }
        }
    }
    while (!expressionsStack.isEmpty())
        prefix.prepend(expressionsStack.pop());

    return prefix;
}

bool ArithmeticTools::isOperand(QString expression)
{
    return !isOperator(expression) && !isLeftBracket(expression) && !isRightBracket(expression);
}

bool ArithmeticTools::isOperator(QString expression)
{
    if(expression.length() > 1) return false;
    switch(expression.at(0).toLatin1())
    {
        case '+' :
        case '-' :
        case '*' :
        case '/' :return true;
        default : return false;
    }
}

bool ArithmeticTools::isLeftBracket(QString expression)
{
    return expression == "(";
}

bool ArithmeticTools::isRightBracket(QString expression)
{
    return expression == ")";
}

int ArithmeticTools::precedence(QString expression)
{
    if(expression.length() > 1) return 0;
    switch(expression.at(0).toLatin1())
    {
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
        default : return 0;
    }
}

