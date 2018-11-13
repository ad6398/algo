#include<bits/stdc++.h>
using namespace std;
class node
{
	public:
	int data,degree;
	node *child,*next,*parent;
	node(int v)
	{
		data=v;
		degree=0;
		parent=child=next=NULL;
	}
};
class BinomialHeap
{
	public:
	node *head,*Min,*pmin;
	BinomialHeap()
	{
		head=new node(0);
		pmin=head;
		Min=NULL;
	}
	bool isEmpty()
	{
		return (head->next)==NULL;
	}
	void Union()
	{
		if(!(head->next))
			return;
		node *prev=head;
		node *cur=prev->next;
		while(cur&&(cur->next))
		{
			if(cur->degree!=cur->next->degree)
			{
				
				prev=cur;
				cur=cur->next;	
			}
			else if(cur->next->next&&cur->next->next->degree==cur->degree)
			{
				prev=cur;
				cur=cur->next;
			}
			else if(cur->data<=cur->next->data)
			{
				node* nn=cur->next->next;
				cur->next->next=cur->child;
				cur->child=cur->next;
				cur->child->parent=cur;
				cur->next=nn;
			}
			else if(cur->data>cur->next->data)
			{
				node * nn=cur->next;
				prev->next=nn;
				cur->next=nn->child;
				nn->child=cur;
				cur->parent=nn;
				cur=nn;
			}
		}
		updMin();
		
	}
	void updMin()
	{
		pmin=head;
		Min=head->next;
		node *x=Min;
		while(x&&x->next)
		{
			if(x->next->data<Min->data)
			{
				pmin=x;
				Min=x->next;
			}
			x=x->next;
		}
	}
	void insert(int x)
	{
		node *a=new node(x);
		a->next=head->next;
		head->next=a;
		Union();
	}
	void merge(node *x)
	{
		node *a=head->next;
		node *pa=head;
		while(a&&x)
		{
			if(a->degree<=x->degree)
			{
				pa=a;
				a=a->next;
			}
			else
			{
				node * c=x->next;
				pa->next=x;
				x->next=a;
				pa=x;
				x=c;
			}
		}
		if(x)
		pa->next=x;
		Union();
	}
	int extractMin()
	{
		int minimum=Min->data;
		pmin->next=Min->next;
		node *c=Min->child;
		while(c)
		{
			c->parent=NULL;
			c=c->next;
		}
		merge(Min->child);
		return minimum;
	}
	node* find(int val)
	{
		node *c=head->next;
		while(c)
		{
			node *f=find(c,val);
			if(f)
				return f;
			c=c->next;
		}
		return NULL;
		
	}
	node* find(node *n,int val)
	{
		if(n==NULL)
			return NULL;
		if(n->data==val)
			return n;
		node *c=n->child;
		while(c)
		{
			node *f=find(c,val);
			if(f)
				return f;
			f=f->next;
		}	
		return NULL;
	}
	bool decreaseKey(int val,int newval)
	{
		if(val<=newval)
			return false;
		node *x=find(val);
		if(x==NULL)
		{
			return false;
		}
		x->data=newval;
		while(x->parent&&x->data<x->parent->data)
		{
			int d=x->data;
			x->data=x->parent->data;
			x=x->parent;
			x->data=d;
		}
		return true;
		updMin();
	}
	bool deleteKey(int val)
	{
		if(!decreaseKey(val,INT_MIN))
			return false;
		extractMin();
		return true;
	}
};
int main()
{
	BinomialHeap h;
	cout<<"Commands\ni <element> : insert an element\nm : extract minimum\nr <element> :"<<
	"delete operation\nd <old value> <new value> : decrease key operation\ne : exit"<<endl;
	while(1)
	{
		char c;
		cin>>c;
		switch(c)
		{
			case 'i': 
				int x;
				cin>>x;
				h.insert(x);
				break;
			case 'm':
				if(h.isEmpty())
					cout<<"Heap is Empty"<<endl;
				else
					cout<<"Extracted Minimum="<<h.extractMin()<<endl;
				break;
			case 'r':
				int y;
				cin>>y;
				cout<<y<<(h.deleteKey(y)?" Deleted":" Not present in heap")<<endl;
				break;
			case 'd':
				int a,b;
				cin>>a>>b;
				if(b>=a)
				{
					cout<<"Invalid arguments. New value should be smaller"<<endl;
				}
				else if(h.decreaseKey(a,b))
					cout<<a<<" decreased to "<<b<<endl;
				else
					cout<<a<<" was not present in heap"<<endl;
				break;
			case 'e':
				return 0;
		}
	}
}
