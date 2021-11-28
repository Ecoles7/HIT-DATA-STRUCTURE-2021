#include <iostream>
#include <cstdio>
#include<stack>
#include<queue>
#include<fstream>
using namespace std;
#define Maxnum 100     //定义最大顶点数为100 
int visited[Maxnum];   //用于标记是否访问过 

void visitedto0()              //标记访问清空函数 
{
	int i=Maxnum;
	for(i=0;i<Maxnum;i++)
	{
		visited[i]=0;
	}
}


//邻接表的建立
typedef struct node    //边表结点建立 
{
	int adjvex;       //结点下标（编号） 
	struct node* next;
}Edgenode;            

typedef struct {      //顶点表结点建立 
	char element;
	Edgenode *firstedge;
}VertexNode;

typedef struct{                    //邻接表建立 
	VertexNode vexlist[Maxnum];   //顶点表 
	int n,e;                     //图的顶点数与边数 
}AdjGraph;

void creatAdj(AdjGraph *p)  //读入并显示邻接表 
{
	int i,j,k;
    ifstream in("file.txt");
    in>>p->n>>p->e;
	for (k=0; k<p->n; k++)      //邻接表的初始化
    {
        in>>p->vexlist[k].element;
        p->vexlist[k].firstedge=NULL; 
    }
    for(k=0; k<p->e; k++)
    {
        in>>j>>i;
        Edgenode* q=new Edgenode;
        q->adjvex=i;
        q->next=p->vexlist[j].firstedge;
        p->vexlist[j].firstedge=q;//头插法 
       /* q=new Edgenode;//建立无向图，所以还要反过来链接
        q->adjvex=j;
        q->next=p->vexlist[i].firstedge;
        p->vexlist[i].firstedge=q;*/
    }
    in.close();
    cout<<"邻接表生成如下"<<endl; 
    for(i=0;i<p->n;i++)    //打印建立好的邻接表 
    {
        cout<<i<<" "<<p->vexlist[i].element;
        Edgenode *m=p->vexlist[i].firstedge;
        while(m!=NULL)
        {
            cout<<"->"<<m->adjvex;
            m=m->next;
        }
        cout<<"->NULL"<<endl;
    }
}

//邻接矩阵的建立 
typedef struct {
	int mat[Maxnum][Maxnum];    //邻接矩阵一边表 
	char element[Maxnum];       //顶点表 
	int n,e;                    //结点数，边数 
}MTGraph;

void creatMTG(MTGraph *p)     //读入并输入建立矩阵 
{
	int i,j,x,y;
    ifstream in("file.txt");
    in>>p->n>>p->e;
	for(i=0; i<p->n; i++)        //读入顶点表 
    {
	  in>>p->element[i];
    }
    for(i=0; i<p->n; i++)       //将邻接矩阵初始为0 
    {
	   for(j=0; j<p->n; j++)
            p->mat[i][j]=0;
    }
    for(i=0; i<p->e; i++)    //编写邻接矩阵 
    {
        in>>x>>y;
        p->mat[x][y]=1;
    }
    cout<<"建立邻接矩阵如下:"<<endl;   //打印建立好的邻接矩阵 
    for(i=0; i<p->n; i++)
    {
    	cout<<p->element[i]<<" ";
      for(j=0; j<p->n; j++)
        cout << p->mat[i][j] << " ";
        cout << endl;
    }
}

//邻接矩阵转邻接表
void MTGtoAdjG(AdjGraph *G,MTGraph M) 
{               
    G->n=M.n;    //将邻接矩阵中的顶点数传输给邻接表
    G->e=M.e;     //将邻接矩阵中的边数传输给邻接表
    int i,j,k;
    for(k=0;k<G->n;k++)  //初始化
   {   
      G->vexlist[k].element=M.element[k];
      G->vexlist[k].firstedge=NULL;
   }

    for(i=0;i<M.n;i++)  //遍历矩阵
{   	
        for(j=0;j<=M.n-1;j++)
        {
           if(M.mat[i][j]==1)
           {   	
              Edgenode *p=new Edgenode;
              p->adjvex=j;                      //记录邻接点序号
              p->next=G->vexlist[i].firstedge;    //头插法建立i的链表
              G->vexlist[i].firstedge=p;        
           }
        }
    }
}

//邻接表转邻接矩阵
void AdjGtoMTG(AdjGraph G,MTGraph *M) 
{
	M->n=G.n;    //将邻接矩阵中的顶点数传输给邻接表
    M->e=G.e;     //将邻接矩阵中的边数传输给邻接表
    int i,j;
    for(i=0;i<M->n;i++)  //顶点表初始化
   {   
      M->element[i]=G.vexlist[i].element;
   }
   for(i=0;i<M->n;i++)  //邻接矩阵初始化 
   {
   	 for(j=0;j<M->n;j++)
   	 {
   	 	M->mat[i][j]=0;
	 }
   }
   for(i=0;i<M->n;i++)  //将邻接信息从邻接表转入到邻接矩阵 
   {
   	   Edgenode *p=G.vexlist[i].firstedge;
   	   p=p->next;
       while(p != NULL)
   	  {
   		int x=p->adjvex;
   		M->mat[x][i]=1;
   		M->mat[i][x]=1;
   		p=p->next;
	  }
	}
}

void DFSAdj(AdjGraph* G,int v)  //递归实现邻接表的深度优先搜索 ,从下标为v的结点开始 
{
    Edgenode *p; 
    cout << G->vexlist[v].element << " ";
    visited[v]=1;
    p=G->vexlist[v].firstedge;
    while(p!=NULL)
    {
        if(!visited[p->adjvex])   //访问未被搜索过的结点 
		DFSAdj(G,p->adjvex);
        p=p->next;
    }
}

void DFSAdjfei(AdjGraph* G,int v)  //邻接表深度优先搜索的非递归实现 
{
    int STACK[Maxnum],top=Maxnum;
    Edgenode *p=NULL;
    STACK[--top]=v;//第一个压栈
    while(top!=Maxnum)
    {
        int w=STACK[top++];
        if(!visited[w])
        {
            cout <<  G->vexlist[w].element << " ";
            visited[w]=1;
        }
        for(p=G->vexlist[w].firstedge; p!=NULL; p=p->next)
        {
		    if(!visited[p->adjvex])
            STACK[--top]=p->adjvex;//遇到一个没有访问的，压栈,向下搜索
        }
    }
}

void DFSMTG(MTGraph *G,int v)//邻接矩阵深度优先（递归）
{
    int j;
    cout << G->element[v] << " ";
    visited[v]=1;
    for(j=G->n-1; j>=0; j--)
	{
	  if(G->mat[v][j]==1&&!visited[j])  
	  DFSMTG(G,j);
    }
}

void DFSMTGfei(MTGraph *G,int v)//邻接矩阵深度优先（非递归）
{
    int STACK[Maxnum];
    int top=Maxnum;
    STACK[--top]=v;//第一个压栈
    while(top!=Maxnum)
    {
        int w=STACK[top++];
        if(!visited[w])
        {
            cout <<  G->element[w] <<  " ";
            visited[w]=1;
        }//取栈顶判断
        for(int i=0; i<G->n; i++)
		{ 
		   if(!visited[i]&&G->mat[w][i])
           STACK[--top]=i;//遇到一个没有访问的，压栈,向下搜索
        }
    }
}

void BFSMTG(MTGraph *G,int v)//邻接矩阵的广度优先
{
    int Queue[Maxnum],front=0,rear=0,w;
    visited[v]=1;
    Queue[rear++]=v;
    cout << G->element[v] << " ";
    while(front!=rear)
    {
        v=Queue[front++];
        for(w=0; w<G->n; w++)
        {
            if(!visited[w]&&G->mat[v][w])
            {
                cout <<G->element[w] << " ";
                visited[w]=1;
                Queue[rear++]=w;
            }
        }
    }
}

void BFSAdj(AdjGraph* G,int v)    //邻接矩阵的广度优先遍历 
{
    int Queue[Maxnum],front=0,rear=0;
    Edgenode *p=NULL;
    visited[v]=1;
    Queue[rear++]=v;
    cout << G->vexlist[v].element << " ";
    while(front!=rear)
    {
        v=Queue[front++];
        p=G->vexlist[v].firstedge;
        while(p!=NULL)
        {
        	if(!visited[p->adjvex]) 
            {
			   cout <<G->vexlist[p->adjvex].element << " ";
               visited[p->adjvex]=1;
               Queue[rear++]=p->adjvex;
            }
            p=p->next;
        }
    }
}

main()
{
	int n;
	AdjGraph G;
	MTGraph  M;
	int p1=0;
	int i,j;
	int count;
	while(p1==0)
	{
	   int yrc1;
	   int p2=0;
	   int num1;
       int yrc2;
	   int p3=0;
	   int num2;
	   cout<<"请选择您要进行的操作："<<endl;
	   cout<<"1.建立邻接表                      2.建立邻接矩阵                  3.退出界面"<<endl; 
       cin>>n;
       switch(n)
      {
    	  case 1:
    	      creatAdj(&G);
			  while(p2==0)
			  {
			    cout<<"请选择您要进行的操作:\n1.深度优先搜索     2.深度优先搜索（非递归）   3.广度优先搜索  4.转为邻接矩阵    5.返回初始界面"<<endl;
			    cin>>yrc1;
			    switch(yrc1)
			   {
			  	  case 1:
			  	  	cout<<"请输入搜索的起始点"<<endl;
					cin>>num1;
					cout<<"搜索结果如下"<<endl;
					visitedto0();
					cout<<"生成树1:";
					DFSAdj(&G,num1);
					cout<<endl; 
					count=2;
					for(i=0;i<G.n;i++)
				   {
                        if(!visited[i])
						{
							cout<<"生成树"<<count++<<":"; 
                            DFSAdj(&G,i);
                            cout<<endl;
				        }
			       }
					cout<<endl;
					break;
				  case 2:
			  	  	cout<<"请输入搜索的起始点"<<endl;
					cin>>num1;
					cout<<"搜索结果如下"<<endl;
					visitedto0();
					cout<<"生成树1:";
					DFSAdjfei(&G,num1);
					cout<<endl;
					count=2;
					for(i=0;i<G.n;i++)
				   {
                        if(!visited[i])
						{
						  cout<<"生成树"<<count++<<":"; 
                          DFSAdjfei(&G,i);
                          cout<<endl; 
				        }
			       }
					cout<<endl;
			  	    break;
			  	  case 3:
			  	  	cout<<"请输入搜索的起始点"<<endl;
					cin>>num1;
					cout<<"搜索结果如下"<<endl;
					visitedto0();
					cout<<"生成树1:";
					BFSAdj(&G,num1);
					cout<<endl;
					count=2;
					for(i=0;i<G.n;i++)
				   {
                        if(!visited[i])
						{
						  cout<<"生成树"<<count++<<":"; 
                          BFSAdj(&G,i);
                          cout<<endl; 
				        }
			       }
					cout<<endl;
					break;
				  case 4:
				  	AdjGtoMTG(G,&M);
					cout<<"转换成功，生成邻接矩阵如下："<<endl; 
					for(i=0; i<M.n; i++)
                   {
                   	     cout<<M.element[i]<<" ";
                         for(j=0; j<M.n; j++)
                         cout <<M.mat[i][j] << " ";
                         cout << endl;
                   }
					break;
				  case 5:
				    p2=1;
					break; 
			   }
		      }
		      break;
    	  case 2:
    		  creatMTG(&M);
			  while(p3==0)
			  {
			    cout<<"请选择您要进行的操作：\n1.深度优先搜索     2.深度优先搜索（非递归）   3.广度优先搜索    4.转为邻接表     5.返回初始界面"<<endl;
			    cin>>yrc2;
			    switch(yrc2)
			   {
			  	  case 1:
			  	  	cout<<"请输入搜索的起始点"<<endl;
					cin>>num2;
					cout<<"搜索结果如下"<<endl;
					visitedto0();
					cout<<"生成树1:";
					DFSMTG(&M,num2);
					cout<<endl;
					count=2;
					for(i=0;i<G.n;i++)
				   {
                        if(!visited[i])
						{
						  cout<<"生成树"<<count++<<":"; 
                          DFSMTG(&M,i);
                          cout<<endl;
				        }
			       }
					cout<<endl;
					break;
				  case 2:
			  	  	cout<<"请输入搜索的起始点"<<endl;
					cin>>num2;
					cout<<"搜索结果如下"<<endl;
					visitedto0();
					cout<<"生成树1:";
					DFSMTGfei(&M,num2);
					cout<<endl;
					count=2;
					for(i=0;i<G.n;i++)
				   {
                        if(!visited[i])
						{
							cout<<"生成树"<<count++<<":"; 
                            DFSMTGfei(&M,i);
                            cout<<endl;
				        }
			       }
					cout<<endl;
			  	    break;
			  	  case 3:
			  	  	cout<<"请输入搜索的起始点"<<endl;
					cin>>num2;
					cout<<"搜索结果如下"<<endl;
					visitedto0();
					cout<<"生成树1:";
					BFSMTG(&M,num2);
					cout<<endl;
					count=2;
					for(i=0;i<G.n;i++)
				   {
                        if(!visited[i])
						{
							cout<<"生成树"<<count++<<":"; 
                            BFSMTG(&M,i);
                            cout<<endl;
				        }
			       }
					cout<<endl;
					break;
				  case 4:
				  	MTGtoAdjG(&G,M); 
					cout<<"转换成功，生成邻接表如下"<<endl; 
					for(i=0;i<G.n;i++)    //打印建立好的邻接表 
                   {
                       cout<<i<<" "<<G.vexlist[i].element;
                       Edgenode *m=G.vexlist[i].firstedge;
                       while(m!=NULL)
                     {
                         cout<<"->"<<m->adjvex;
                         m=m->next;
                     }
                         cout<<"->NULL"<<endl;
                    }
					break;
				  case 5:
				    p3=1;
					break; 
			   }
		      }
		      break;
    	  case 3:
    	  	p1=1;
    	    break;
	  }
    }
	
	
}
