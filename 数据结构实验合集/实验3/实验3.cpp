#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
using namespace std;
int cnt1 = 0;
int cnt2 = 0;
//二叉查找树的存储结构
typedef struct celltype
{
    int data;
    struct celltype *lchild,*rchild;
}BSTNode;

//对二叉查找树进行中序遍历，并输出
void Recur_InOrder(BSTNode *F)
{
	if(F)
    {
		Recur_InOrder(F->lchild);
        cout << F->data<<" ";
		Recur_InOrder(F->rchild);
	}
}
//计算树的高度
int Height(BSTNode *F)
{
	int n,m;
	if(F == NULL)
		return 0;
	else
    {
		m = Height(F->lchild);
		n = Height(F->rchild);
	}
	if(m>n)
	return m+1;
	else
	return n+1;
}

//二叉查找树的查找操作:在树F中查找关键值k，返回k所在的结点p
BSTNode *Search(int k,BSTNode *F)
{
	if(k%2 == 1)       //若k为奇数，则计数多少次会查找成功 
     cnt1++;
    if(k%2 == 0)  //若k为偶数，则计数多少次会查找失败 
	 cnt2++;
	BSTNode *p = F;
	if(p == NULL)
    {
        cout <<"查找失败"<<endl;
        return NULL;
    }
    if(k == p->data)      //终止条件：找到了目标
    {
        cout <<"查找成功"<<endl;
        return p;
    }
    else if(k < p->data)
        return Search(k,p->lchild); //k<当前结点的关键字值，去p的左子树中递归查找
    else if(k > p->data)
        return Search(k,p->rchild); //k>当前结点的关键字值，去p的右子树中递归查找
}

//二叉查找树的插入操作：在树F中插入记录key
void InsertBST(int key,BSTNode * &F)
{
    if(F == NULL)            //如果当前树F空，则新插入的结点为树的根结点
    {
        F = new BSTNode;
        F->data = key;
        F->lchild = NULL;
        F->rchild = NULL;
    }
    else if(key < F->data)   //如果待插入元素小于当前结点关键字值，则递归将其插入当前结点的左子树
        InsertBST(key,F->lchild);
    else if(key > F->data)   //如果待插入元素大于当前结点关键字值，则递归将其插入当前结点的右子树
        InsertBST(key,F->rchild);
}
//删除F的最小结点
int deletemin(BSTNode * &F)
{
    int tmp;
    BSTNode *p;
    //若F左子树为空，则F即为右子树的最小结点，递归结束
    if(F->lchild == NULL)
    {
        p = F;
        tmp = F->data;
        F = F->rchild;
        delete p;
        return tmp;    //最小结点的关键字值记为tmp
    }
    else          //左子树不空，最小结点在左子树上
        return deletemin(F->lchild);
}
//二叉查找树的删除操作：
void DeleteB(int k,BSTNode * &F)
{
    if(!F)
        cout <<"删除失败，未查找到该关键字值"<<endl;
    if(k < F->data)
        DeleteB(k,F->lchild);
    else if(k > F->data)
        DeleteB(k,F->rchild);
    else if(k ==  F->data)            //找到了待删除的结点F
    {
        if((F->rchild == NULL) && (F->lchild == NULL))  //1.被删除结点是叶子结点，直接删除
            F = NULL;
        else if((F->rchild == NULL)  && (F->lchild != NULL))   //2.1被删除结点只有左子树，则直接用左子树继承被删结点
            F = F->lchild;
        else if((F->lchild == NULL)  && (F->rchild != NULL))  //2.2被删除结点只有右子树，则直接用右子树继承被删结点
            F = F->rchild;
        /* 被删除的结点左右子树都有，用继承结点（被删节点右子树的最小结点）替代被删结点，
        对于继承结点（只可能有右结点或直接是叶子结点）再按照1,2处理 */
        else if((F->lchild != NULL) && (F->rchild != NULL))
            F->data = deletemin(F->rchild);
    }
}
//建立二叉查找树 
BSTNode* CreatBST()
{
    BSTNode *F =NULL;
    int key;                //关键字值
    for(key = 1; key < 2048; key += 2) //顺序读入 
    {
    	cout<<key<<" ";
        InsertBST(key,F);  //插入记录key
    }
    cout<<endl;
    return F;
}


//随机序列建立二叉查找树算法
BSTNode *CreatBSTrandom()
{
    BSTNode *F = NULL;
    int key,cnt = 0;
	int rep,i,j,k;
    int K[1024] = {0};
    srand((unsigned int)time(NULL));
    key = rand()%2048;
    while(1)              //得到第一个数
    {
        if((key%2) == 1) //key为奇数 
        {
            InsertBST(key,F);                //插入记录key
            cout<<key<<" ";
            K[cnt] = key;
            cnt++;
            break;
        }
        key = rand()%2048;
    }
    while(cnt<1024)
    {
        key = rand()%2048;
        if((key%2) == 1)  //若key为奇数 
        {
            rep = 0;
            for(i = 0; i <= cnt; i++)
            {
                if(key == K[i])               //将得到的每个随机数存放到K[]中，用于检查是否重复
                    rep = 1;
            }
            if(!rep)
            {
                 InsertBST(key,F);                //插入记录key
                 cout<<key<<" ";
                 K[cnt] = key;
                 cnt++;
            }
        }
    }
    cout<<endl;
    return F;
}

//查找成功与失败的平均查找长度
void ASLB(BSTNode *F)
{
    int i;
    int sum1 = 0,sum2 = 0;
    double ASLS,ASLF;
    int height = Height(F);
    cout<<"BST的高度为:"<<height<<endl;
    for(i = 0; i <= 2048; i++)
    {
        cnt1 = 0;
        cnt2 = 0;
        Search(i,F);
        sum1+= cnt1;
        sum2+= cnt2;
    }
    ASLS = sum1/1024.0;
    ASLF = sum2/1025.0;
    cout <<"BST查找成功的平均查找长度为"<<ASLS<<endl;
    cout <<"BST查找失败的平均查找长度为"<<ASLF<<endl;
}

//折半查找算法：
int cnt3 = 0;
int cnt4 = 0;
int BF[1024];
int BinSearch(int key)
{
    int i;
    int low,up,mid;
    low = 0;
    up = 1023;
    for(i = 1; i < 2048; i += 2)  //生成奇数列 
    {
        BF[i/2] = i;
    }
    while(low <= up)
    {
        if(key%2)   //k为奇数 
          cnt3++;
        else       //k为偶数 
		  cnt4++;
        mid = (low + up)/2;
        if(BF[mid] == key)
        {
            cout <<"查找成功"<<endl;
            return mid;
        }
        else if(BF[mid] > key)
              up = mid -1;
        else  low = mid +1;
    }
    cout <<"查找失败"<<endl;
    return 0;
}
//折半查找的查找成功和失败的平均查找长度
void BinASL()
{
    int i;
    int sum3 = 0,sum4 = 0;
    float  ASLBS,ASLBF;
    for(i = 0; i <= 2048; i++)
    {
        cnt3 = 0;
        cnt4 = 0;
        BinSearch(i);
        sum3 += cnt3;
        sum4 += cnt4;
    }
    ASLBS = sum3/1024.0;
    ASLBF = sum4/1025.0;
    cout <<"折半查找成功的平均查找长度为"<<ASLBS<<endl;
    cout <<"折半查找失败的平均查找长度为"<<ASLBF<<endl;
}

int main()
{
	BSTNode *p;
	BSTNode *find;
	int key;
	int cho;
	int yrc;
	while(1)
  { 
  	cout <<"请选择功能:"<<endl;
	cout <<"0.顺序输入建立BST"<<endl;
    cout <<"1.随机输入建立BST"<<endl;
    cout <<"2.BST查找一个元素"<<endl;
    cout <<"3.插入一个元素"<<endl;
    cout <<"4.删除一个元素"<<endl;
    cout <<"5.折半查找"<<endl;
    cout <<"6.BST查找成功与失败平均查找长度"<<endl;
    cout <<"7.折半查找成功与失败平均查找长度"<<endl;
    cout <<"8.结束退出"<<endl; 
    cin>>cho;
    switch(cho)
   {
	  case 0:
      	cout<<"输入序列如下："<<endl;
      	p = CreatBST();
      	cout<<"建立BST的中序遍历结果如下："<<endl; 
      	Recur_InOrder(p);
      	cout<<endl;
        break;
      case 1:
      	cout<<"输入序列如下："<<endl;
      	p = CreatBSTrandom();
      	cout<<"建立BST的中序遍历结果如下："<<endl; 
      	Recur_InOrder(p);
      	cout<<endl;
        break;
      case 2:
      	cout<<"请输入您要查找的关键字"<<endl;
		cin>>key;
	    cnt1=0; 
	    cnt2=0;
		find=Search(key,p);
		if(key%2 == 0)  
		cout<<"比较次数；"<<cnt2<<endl;
		else
		cout<<"比较次数；"<<cnt1<<endl; 
		break;
	  case 3:
	  	cout<<"请选择你要插入的关键字"<<endl;
		cin>>key; 
		InsertBST(key,p);
		cout<<"插入后的BST中序遍历结果为："<<endl;
		Recur_InOrder(p);
		break;
	  case 4:
	  	cout<<"请选择你要删除的关键字"<<endl;
		cin>>key;
		DeleteB(key,p);
		cout<<"删除后的BST中序遍历结果为："<<endl;
		Recur_InOrder(p);
		break;
	  case 5:
	  	cout <<"请输入要查找的关键字值：";
        cin >>key;
        cnt3=0; 
	    cnt4=0;
        yrc = BinSearch(key);
        if(yrc!=0 || key==1 ) 
        cout<<"下标为："<<yrc<<endl;
        if(key%2 == 0)  
		cout<<"比较次数；"<<cnt4<<endl;
		else
		cout<<"比较次数；"<<cnt3<<endl; 
        break;
      case 6:
      	ASLB(p);
      	break;
      case 7:
      	BinASL();
      	break;
      case 8:
        exit(0);
      default:
        cout <<"输入错误，请重新输入:";
        cin >> cho;
    }
  }	
 } 
