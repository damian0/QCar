#ifndef TREENODE_H
#define TREENODE_H

#include <QString>

class TreeNode
{
    public:
        TreeNode(QString value, bool deleteSubnodesOnDeletion=true);
        virtual ~TreeNode();

        QString getValue();
        TreeNode** getLeftChild();
        TreeNode** getRightChild();
        bool getDeleteSubnodesOnDeletion();
        bool getFree() const;

        void setValue(QString value);
        void setLeftChild(TreeNode* node);
        void setRightChild(TreeNode* node);
        void setDeleteSubnodesOnDeletion(bool value);        
        void setFree(bool value);

private:
        QString value;
        bool deleteSubnodesOnDeletion;
        bool free;
        TreeNode* leftChild;
        TreeNode* rightChild;
};

#endif // TREENODE_H
