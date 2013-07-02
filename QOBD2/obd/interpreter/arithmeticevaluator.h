#ifndef ARITHMETICEVALUATOR_H
#define ARITHMETICEVALUATOR_H

#include "treenode.h"
#include <QString>
#include <QHash>

class ArithmeticEvaluator
{
public:
    ArithmeticEvaluator(QString infix);
    virtual ~ArithmeticEvaluator();
    double evaluate();    
    void setVariable(QString var, double value);
    void resetVariable(QString var);
    void resetVariables();

private:
    void createExpressionsTree();
    void addTreeNode(TreeNode **tree, const QString expression);    
    double evaluateTree(TreeNode *tree);

    QHash<QString, double> variables;
    QString infix;
    TreeNode* expressionsTree;
};

#endif // ARITHMETICEVALUATOR_H
