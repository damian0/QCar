#include "arithmeticevaluator.h"
#include "arithmetictools.h"
#include <QStringList>
#include <QDebug>

ArithmeticEvaluator::ArithmeticEvaluator(QString infix)
{
    this->infix = infix;
    expressionsTree = 0;
    createExpressionsTree();
}

ArithmeticEvaluator::~ArithmeticEvaluator()
{
    delete expressionsTree;
}

double ArithmeticEvaluator::evaluate()
{
    return evaluateTree(expressionsTree);
}

void ArithmeticEvaluator::setVariable(QString var, double value)
{
    variables[var] = value;
}

void ArithmeticEvaluator::resetVariable(QString var)
{
    variables.remove(var);
}

void ArithmeticEvaluator::resetVariables()
{
    variables.clear();
}

void ArithmeticEvaluator::createExpressionsTree()
{
    QStringList prefix = ArithmeticTools::toPrefix(infix);       

    foreach(const QString expression, prefix)
    {
        addTreeNode(&expressionsTree, expression);
    }
}

void ArithmeticEvaluator::addTreeNode(TreeNode **tree, const QString expression)
{
    if(!(*tree))
    {        
        *tree = new TreeNode(expression);
        if( !ArithmeticTools::isOperator((*tree)->getValue()) )
            (*tree)->setFree(false);
    }
    else
    {
        //Should not happen
        if( !(*tree)->getFree() ) return;

        TreeNode** left = (*tree)->getLeftChild();
        TreeNode** right = (*tree)->getRightChild();

        if( !(*left) || ArithmeticTools::isOperator((*left)->getValue()) && (*left)->getFree() )
            addTreeNode(left, expression);
        else
            addTreeNode(right, expression);

        if( (*left) && !ArithmeticTools::isOperator((*left)->getValue()) &&
            (*right) && !ArithmeticTools::isOperator((*right)->getValue()) ||
            (*left) && !(*left)->getFree() && (*right) && !(*right)->getFree())
        {
            (*tree)->setFree(false);
        }

    }
}

double ArithmeticEvaluator::evaluateTree(TreeNode *tree)
{
    if(tree)
    {
        QString value = tree->getValue();

        //Number or variable
        if( !ArithmeticTools::isOperator(tree->getValue()) )
        {
            if( variables.contains(value) )
            {                
                return variables[value];
            }
            else
            {
                bool ok;
                //We try to convert string -> double
                double d = value.toDouble(&ok);

                return (ok) ? d : 0.0;
            }
        }
        //Operator
        else
        {
            switch(value.at(0).toLatin1())
            {
                case '+' : return evaluateTree(*tree->getLeftChild()) + evaluateTree(*tree->getRightChild());
                case '-' : return evaluateTree(*tree->getLeftChild()) - evaluateTree(*tree->getRightChild());
                case '*' : return evaluateTree(*tree->getLeftChild()) * evaluateTree(*tree->getRightChild());
                case '/' : return evaluateTree(*tree->getLeftChild()) / evaluateTree(*tree->getRightChild());
                default : return 0.0;
            }
        }
    }
    else
    {
        return 0.0;
    }
}
