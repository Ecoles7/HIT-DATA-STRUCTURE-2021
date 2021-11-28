#include <iostream> 
#include <stdlib.h>
#include <stdio.h>
#include <stack>
#include <queue>
using namespace std;

struct node        //定义树的二叉链表 
{
    node *lchild;
    char data;
    node *rchild;
};
typedef node *BTREE;
BTREE CreatBT()   //任务一：二叉树的创建 
{
    BTREE T;
    char ch;
    scanf(" %c",&ch);
    if(ch=='#')   //若输入#则令该结点为空 
        T = NULL;
    else
    {
        T = (BTREE)malloc(sizeof(node));
        T->data = ch;
        T->lchild = CreatBT();   //利用递归，使用先序顺序进行创建 
        T->rchild = CreatBT();
    }
    return T;
}
void PreOrder(BTREE BT)  //先序遍历的递归实现 
{
    if(BT!=NULL)
    {
        printf("%c ",BT->data);  //先访问根节点 
        PreOrder(BT->lchild);    //再访问左子树 
        PreOrder(BT->rchild);    //再访问右子树 
    }
}
void InOrder(BTREE BT)   //中序遍历的递归实现 
{
    if(BT!=NULL)
    {
        InOrder(BT->lchild);    //先访问左子树 
        printf("%c ",BT->data); //再访问根节点 
        InOrder(BT->rchild);    //再访问右子树 
    }
}
void PostOrder(BTREE BT)
{
    if(BT!=NULL)
    {
        PostOrder(BT->lchild);   //先访问左子树 
        PostOrder(BT->rchild);   //再访问右子树 
        printf("%c ",BT->data);  //再访问根节点 
    }
}
void PreOrderfei(BTREE T)   //先序遍历非递归实现 
{
    stack <BTREE> S;
    BTREE p = T;
    while(p!=NULL||!S.empty())
    {                          //按照先序遍历 根节点，左子树，右子树 的顺序安排结点进栈及输出
        while(p!=NULL)    
        {
            printf("%c ",p->data);
            S.push(p);
            p = p->lchild;
        }

        if(!S.empty())  
        {
            p = S.top();
            S.pop();
            p = p->rchild;
        }
    }

}
void InOrderfei(BTREE T)  //中序遍历的非递归实现 
{
    stack <BTREE> S;
    BTREE root = T;
    while(root!=NULL||!S.empty())
    {                            //按照中序遍历 左子树，根节点，右子树 的顺序安排结点进栈及输出
        while(root!=NULL)   
        {
            S.push(root);
            root = root->lchild;
        }
        if(!S.empty())   
        {
            root = S.top();
            S.pop();
            printf("%c ",root->data);
            root = root->rchild;
        }
    }
}
void PostOrderfei(BTREE T)  //后序遍历的非递归实现 
{
    BTREE p,pr;
    stack <BTREE> S;
    p = T;
    while(p!=NULL||!S.empty())
    {                           //按照后序遍历 左子树，右子树，根结点 的顺序安排结点进栈及输出
        while(p!=NULL)  
        {
            S.push(p);
            pr = p->rchild;
            p = p->lchild;
            if(p==NULL)
                p = pr;
        }
        p = S.top();  //p指向栈首 
        S.pop();      //出栈操作 
        printf("%c ",p->data);  //输出结点数据 
        if(!S.empty()&&S.top()->lchild==p)  //若栈非空且栈的左孩子结点为p 
            p = S.top()->rchild;    //p指向其兄弟结点 
        else
            p = NULL;
    }
}
void LevelOrder(BTREE root)  //层序遍历 
{
    queue <BTREE> Q;  
    if(root==NULL)
        return;
    Q.push(root);
    while(!Q.empty())
    {
        BTREE q = Q.front();     //p指向队首 
        Q.pop();
        printf("%c ",q->data);   //输出结点的数据值 
        if(q->lchild!=NULL)
            Q.push(q->lchild);   //先让左子树进队 
        if(q->rchild!=NULL)
            Q.push(q->rchild);   //后让右子树进队 
    }

}
bool IsComleteTree(BTREE root)  //判断是否为完全二叉树 
{
    if(root == NULL)
    {
        return false;
    }
    queue<BTREE>q;
    q.push(root);
    BTREE p = q.front();
    while(p != NULL)   //按照层序遍历的次序进队直到访问到空结点 
    {
        q.pop();
        q.push(p->lchild);
        q.push(p->rchild);
        p = q.front();
    }
    q.pop();  //队首的空结点出队 
    while(!q.empty())   //若此时队内全为空结点说明为完全二叉树，反之则不是 
    {
        if(q.front()!=NULL)
            return false;
        q.pop();
    }
    return true;
}
int main()
{
    BTREE T;
    T = CreatBT();
    printf("先序递归：");
    PreOrder(T);
    printf("\n");
    printf("中序递归：");
    InOrder(T);
    printf("\n");
    printf("后序递归：");
    PostOrder(T);
    printf("\n");
    printf("先序非递归：");
    PreOrderfei(T);
    printf("\n");
    printf("中序非递归：");
    InOrderfei(T);
    printf("\n");
    printf("后序非递归：");
    PostOrderfei(T);
    printf("\n");
    printf("层序遍历：");
    LevelOrder(T);
    printf("\n");
    printf("是否为完全二叉树：");
    if(IsComleteTree(T)==false)
        printf("FALSE\n");
    else
        printf("TRUE\n");
    return 0;
}
