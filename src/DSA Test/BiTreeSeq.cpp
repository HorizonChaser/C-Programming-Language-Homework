#include <bits/stdc++.h>

using namespace std;

struct TreeNode {  //每一个节点的属性:左节点、右节点、数据
    int data;
    TreeNode* left;
    TreeNode* right;
};
void BinaryTreeFromOrderings_pre_in(int* inorder, int* preorder, int length) {
    //中序序列，先序序列，中序中需要寻找的字段长度
    if (length == 0)
        return;

    TreeNode* node = new TreeNode;  //新建一个节点，节点的数据为先序的首个元素
    node->data = *preorder;

    int rootIndex;  //根节点在中序数组中的下标
    for (rootIndex = 0; rootIndex < length; rootIndex++)
        if (inorder[rootIndex] == *preorder)
            break;

    //后序遍历输出结果
    BinaryTreeFromOrderings_pre_in(inorder, preorder + 1, rootIndex);                                             //中序的左边一半长度作为新的需要寻找的字段长度
    BinaryTreeFromOrderings_pre_in(inorder + rootIndex + 1, preorder + rootIndex + 1, length - (rootIndex + 1));  //中序的后面一段长度作为需要寻找的字段长度
    cout << node->data << " ";
}

void BinaryTreeFromOrderings_in_last(int* inorder, int* lastorder, int length) {
    if (length == 0)
        return;

    TreeNode* node = new TreeNode;
    node->data = *(lastorder + length - 1);

    int rootindex;
    for (rootindex = 0; rootindex < length; rootindex++)
        if (inorder[rootindex] == node->data)
            break;

    cout << node->data << " ";
    BinaryTreeFromOrderings_in_last(inorder, lastorder, rootindex);
    BinaryTreeFromOrderings_in_last(inorder + rootindex + 1, lastorder + rootindex, length - (rootindex + 1));
}

int main() {
    int xian[] = {1, 2, 3, 4, 5, 6}, zhong[] = {3, 2, 4, 1, 6, 5}, hou[] = {3, 4, 2, 6, 5, 1};
    BinaryTreeFromOrderings_pre_in(zhong, xian, 6);
    cout << endl;
    BinaryTreeFromOrderings_in_last(zhong, hou, 6);

    string a = "0000";
    if(a == "0000") {
        cout << a << endl;
    }
}