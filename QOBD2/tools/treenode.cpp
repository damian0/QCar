#include "treenode.h"

TreeNode::TreeNode(QString value, bool deleteSubnodesOnDeletion)
{
    this->setValue(value);
    this->setDeleteSubnodesOnDeletion(deleteSubnodesOnDeletion);
    this->setLeftChild(0);
    this->setRightChild(0);
    this->setFree(true);
}

TreeNode::~TreeNode()
{
    if(this->deleteSubnodesOnDeletion)
    {
        delete leftChild;
        delete rightChild;
    }
}

QString TreeNode::getValue()
{
    return this->value;
}

TreeNode** TreeNode::getLeftChild()
{
    return &this->leftChild;
}

TreeNode** TreeNode::getRightChild()
{
    return &this->rightChild;
}

bool TreeNode::getDeleteSubnodesOnDeletion()
{
    return this->deleteSubnodesOnDeletion;
}

void TreeNode::setValue(QString value)
{
    this->value = value;
}

void TreeNode::setLeftChild(TreeNode* node)
{
    this->leftChild = node;
}

void TreeNode::setRightChild(TreeNode* node)
{
    this->rightChild = node;
}

void TreeNode::setDeleteSubnodesOnDeletion(bool value)
{
    this->deleteSubnodesOnDeletion = value;
}

bool TreeNode::getFree() const
{
    return free;
}

void TreeNode::setFree(bool value)
{
    free = value;
}
