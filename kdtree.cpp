#include<bits/stdc++.h>
using namespace std;
class node
{
	public:
	node *left,*right;
	int split,axis;
	bool leaf;
	pair<int,int> p;
	node(int axi,int spl)
	{
		left=right=NULL;
		leaf=false;
		split=spl;
		axis=axi;
	}
	node(pair<int,int> pt)
	{
		left=right=NULL;
		leaf=true;
		p=pt;
	}
};
class KdTree
{
	public:
	node *head;
	KdTree(vector< pair< int,int> > p)
	{
		head=build(p,0);
	}
	node* build(vector< pair<int,int> > &p,int ax)
	{
		if(p.empty())
			return NULL;
		if(p.size()==1)
			return new node(p[0]);
		vector<int> val;
		vector< pair<int,int> > pless,pmore;
		int med;
		node* ret;
		if(ax==0)
		{	
			for(int i=0;i<p.size();i++)
				val.push_back(p[i].first);
			
			nth_element(val.begin(),val.begin()+(val.size()-1)/2,val.end());
			med=val[(val.size()-1)/2];
			for(int i=0;i<p.size();i++)
			{
				if(p[i].first<=med)
					pless.push_back(p[i]);
				else
					pmore.push_back(p[i]);
					
			}		
		} 
		else
		{
			for(int i=0;i<p.size();i++)
				val.push_back(p[i].second);
			nth_element(val.begin(),val.begin()+(val.size()-1)/2,val.end());
			med=val[(val.size()-1)/2];
			for(int i=0;i<p.size();i++)
			{
				if(p[i].second<=med)
					pless.push_back(p[i]);
				else
					pmore.push_back(p[i]);
					
			}
		}
		ret=new node(ax,med);
		ret->left=build(pless,1-ax);
		ret->right=build(pmore,1-ax);
		return ret;
	}
	void print()
	{
		queue<node *> q,q1;
		
		q.push(head);
		while(!q.empty())
		{
			while(!q.empty())
			{
				node *n=q.front();
				q.pop();
				if(n==NULL)		
					cout<<"|NULL| ";
				else if(n->leaf)
				{
					cout<<"|Point x="<<(n->p.first)<<" y="<<(n->p.second)<<"| ";
				}
				else
				{
					cout<<"|Split at "<<(n->axis==0?"x":"y")<<"="<<(n->split)<<"| ";
					q1.push(n->left);
					q1.push(n->right);
				}
			}
			cout<<endl;
			swap(q,q1);
		}
	}
};
int main()
{
	int n;
	vector<pair <int,int > >p;
	cout<<"Enter the number of points"<<endl;
	cin>>n;
	cout<<"Enter te points"<<endl;
	for(int i=0;i<n;i++)
	{
		int x,y;
		cin>>x>>y;
		p.push_back(make_pair(x,y));
	}
	KdTree tr(p);
	cout<<"The tree is"<<endl;
	tr.print();	
}
