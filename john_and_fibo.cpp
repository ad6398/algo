#include<bits/stdc++.h>
using namespace std;
class node
{
	public:
	node *parent,*left,*right,*child;
	pair<int,int> data; 
	int	degree;
	bool mark;
	node(pair<int,int> d)
	{
		data=d;
		degree=0;
		parent=left=right=child=NULL;
		mark=false;
	}
	node* concatenate(node *h)
	{
		node *x=left;
		node *y=h->left;
		x->right=h;
		h->left=x;
		y->right=this;
		left=y;
		if(h->data<data)
			return h;
		return this;
	}
};
class FibonacciHeap
{
	public:
	node *head;
	FibonacciHeap()
	{
		head=NULL;
	}
	bool isEmpty()
	{
		return head==NULL;
	}
	void concatenate(node *h)
	{
		if(head==NULL)
		{
			head=h;
			return;
		}
		if(h==NULL)
			return ;
		head=head->concatenate(h);
	}
	void insert(pair<int,int> val)
	{
		node *x=new node(val);
		x->left=x;
		x->right=x;
		concatenate(x);		
	}
	pair<int,int> extractMin()
	{
		node *z=head;
		node *c=z->child;
		do
		{
			if(!c)
				break;
			c->parent=NULL;
			c=c->right;
		}while(c!=z->child);
		z->child=NULL;
		concatenate(c);
		if(head->left==head)
		{
			head=NULL;
			return z->data;
		}	
		z->left->right=z->right;
		z->right->left=z->left;
		head=z->left;
		consolidate();
		return z->data;
	}
	void consolidate()
	{
		int maxDegree=0;
		node *x=head;
		int cnt=1;
		do
		{
			cnt++;
			maxDegree=max(maxDegree,x->degree);
			x=x->right;
		}while(x!=head);
		//cerr<<"done"<<endl;
		maxDegree+=cnt;
		node* A[maxDegree];
		for(int i=0;i<maxDegree;i++)
			A[i]=0;
		int maxYet=0;
		head->left->right=NULL;
		while(head)
		{
			node *next=head->right;
			head->left=head;
			head->right=head;
			int d=head->degree;
			while(A[d]!=NULL)
			{
				node *y=A[d];
				if(head->data>y->data)
				{
					node *z=head;
					head=y;
					y=z;
				}
				A[d]=NULL;	
				head=link(head,y);
				d++;
			}
			A[d]=head;
			maxYet=max(maxYet,d);
			head=next;	
		}
		head=NULL;
		for(int i=0;i<=maxYet;i++)
			concatenate(A[i]);		
	}	
	node* link(node *a,node *b)
	{
		a->degree++;
		b->parent=a;
		if(a->child==NULL)
			a->child=b;
		else
			a->child=(a->child)->concatenate(b);
		return a;
	}
	node* find(node* nd,pair<int,int> v)
	{
		if(nd==NULL)
			return nd;
		if(nd->data==v)
			return nd;
		node *f=find(nd->child,v);
		if(f!=NULL)
			return f;
		node *cp=nd->right;
		while(cp!=nd)
		{
			f=find(cp,v);
			if(f!=NULL)
				return f;
			cp=cp->right;
		}
		return NULL;
	}
	bool decreaseKey(pair<int,int> ov,pair<int,int> nv)
	{
		if(nv>=ov)
			return false;
		node *f=find(head,ov);
		//cout<<"found"<<endl;
		if(f==NULL)
			return false;
		f->data=nv;
		if(f->parent!=NULL&&f->parent->data>f->data)
		{
			node *par=f->parent;
			cut(f);
			//cout<<"cut done"<<endl;
			cascadingCut(par);
		}
		if(f->data<head->data)
			head=f;
		return true;
	}	
	void cut(node *x)
	{
		node *p=x->parent;
		
		p->child=remove(p->child,x);
		//cout<<"remove done"<<endl;
		p->degree--;
		x->left=x;
		x->right=x;
		x->parent=NULL;
		x->mark=false;
		concatenate(x);
	}
	void cascadingCut(node *x)
	{
		node *p=x->parent;
		if(p!=NULL)
		{
			if(x->mark==false)
				x->mark=true;
			else
			{
				cut(x);
				cascadingCut(p);	
			}
					
		}
	}
	node* remove(node *l,node *x)
	{
		
		if(l->left==l)
			return NULL;
		x->left->right=x->right;
		x->right->left=x->left;
		if(l==x)
			l=l->left;
		node *cp1=l,*cp2=l;
		
		do
		{
			if(cp2->data<cp1->data)
				cp1=cp2;
			cp2=cp2->right;
			//cout<<"l="<<l<<endl;;
			//cout<<cp2<<endl;
		}while(cp2!=l);
		return cp1;
	}
	pair<int,int> getMin()
	{
		return head->data;
	}
	bool deleteKey(pair<int,int> v)
	{
		if(!decreaseKey(v,make_pair(INT_MIN,INT_MIN)))
			return false;
		extractMin();
		return true;
	}
	/*
	void print()
	{
		if(isEmpty())
		{
			cout<<"Empty heap"<<endl;
			return;
		}
		node *x=head;
		int i=1;
		do
		{
			cout<<"Tree "<<i<<endl;
			i++;
			print(x);
			x=x->left;
		}while(x!=head);
		cout<<endl;
	}
	void print(node *x)
	{
		queue<node *> q;
		cout<<"|";
		q.push(x);
		q.push(NULL);
		while(!q.empty())
		{
				x=q.front();
				q.pop();
				if(x==NULL)
				{
					cout<<"|"<<endl;
					if(!q.empty())
						cout<<"|";
					continue;
				}
				cout<<x->data<<" ";
				if(x->child==NULL)
					q.push(x->child);
				else
				{
					node *v=x->child;
					do
					{
						q.push(v);
						v=v->right;
					}while(v!=x->child);
					q.push(NULL);
				}	
		}
	}
	*/
	
};
int main()
{
	int n,m;
	cout<<"Enter the number of nodes and edges in the graph"<<endl;
	cin>>n>>m;	
	vector< pair<int,int> > g[n+1];
	cout<<"Enter the edges in the format u v w"<<endl;
	for(int i=0;i<m;i++)
	{
		int u,v,w;
		cin>>u>>v>>w;
		g[u].push_back(make_pair(v,w));
	}
	//cerr<<"Done"<<endl;
	int d1[n+1];
	for(int i=1;i<=n;i++)
		d1[i]=0;
	//cerr<<"done"<<endl;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			for(int k=0;k<g[j].size();k++)
			{
				d1[g[j][k].first]=min(d1[g[j][k].first],d1[j]+g[j][k].second);			
			}
		}	
	}
	//cerr<<"done"<<endl;
	//reweight;
	for(int i=1;i<=n;i++)
		for(int j=0;j<g[i].size();j++)
		{
			g[i][j].second=g[i][j].second+d1[i]-d1[g[i][j].first];
		}
	//cerr<<"done"<<endl;
	int d[n+1][n+1];
	int par[n+1][n+1];
	for(int s=1;s<=n;s++)
	{
		for(int i=1;i<=n;i++)
		{
			d[s][i]=INT_MAX;
			par[s][i]=-1;
		}	
		//cout<<"donse s="<<s<<endl;
		d[s][s]=0;
		par[s][s]=0;
		FibonacciHeap h;
		for(int i=n;i>=1;i--)
		{
			h.insert(make_pair(d[s][i],i));
		}	
		while(!h.isEmpty())
		{
			pair<int,int> p=h.extractMin();
			
			if(p.first==INT_MAX)
				continue;
			int dist=p.first;
			int nd=p.second;
			for(int i=0;i<g[nd].size();i++)
			{
				
				int nn=g[nd][i].first;
				int wt=dist+g[nd][i].second;
				if(wt<d[s][nn])
				{
					par[s][nn]=nd;
					h.decreaseKey(make_pair(d[s][nn],nn),make_pair(wt,nn));
					d[s][nn]=wt;	
				}
			}
		}
		//cout<<"done s="<<s<<endl;
	}
	//correct path lengths
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			d[i][j]+=(d1[j]-d1[i]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			if(i==j)
				continue;
			if(par[i][j]==-1)
			{
				cout<<j<<" is not reachable from "<<i<<endl;
			}
			else
			{
				cout<<"Minimum cost from "<<i<<" to "<<j<<" = "<<d[i][j]<<endl;
				cout<<"Minimum cost path is "<<endl;
				stack<int> stk;
				int nd=j;
				while(nd!=0)
				{
					stk.push(nd);
					nd=par[i][nd];
				}
				while(!stk.empty())
				{
					cout<<stk.top();
					stk.pop();
					if(!stk.empty())
						cout<<"-->";
				}	
				cout<<endl;
			}
		}
		
}
