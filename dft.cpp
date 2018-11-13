#include<bits/stdc++.h>
using namespace std;

void dft(vector< complex<double> > &a,bool invert)
{
	int n=a.size();
	if(n==1)
		return;
	n/=2;
	vector< complex<double> > a0,a1;
	for(int i=0;i<n;i++)
	{
		a0.push_back(a[2*i]);
		a1.push_back(a[2*i+1]);
	}
	dft(a0,invert);
	dft(a1,invert);
	double ang=acos(-1)/n;
	if(invert)
		ang*=-1;
	complex<double> w(1),wn(cos(ang),sin(ang));
	for(int i=0;i<n;i++)
	{
		a[i]=a0[i]+w*a1[i];
		a[i+n]=a0[i]-w*a1[i];
		w*=wn;
	}
} 
int main()
{
	vector< complex<double> > a,b;
	int n,m;
	cout<<"Enter the degree of polynomial A"<<endl;
	cin>>n;
	n++;
	cout<<"Enter the coeffecients of polynomial A"<<endl;
	for(int i=0;i<n;i++)
	{
		int x;
		cin>>x;
		complex<double> s(x);
		a.push_back(s);
	}
	
	cout<<"Enter the degree of polynomial B"<<endl;
	cin>>m;
	m++;
	cout<<"Enter the coeffecients of polynomial B"<<endl;
	for(int i=0;i<m;i++)
	{
		int x;
		cin>>x;
		complex<double> s(x);
		b.push_back(s);
	}
	
	int sz=1;
	while(sz<n+m)
		sz<<=1;
	a.resize(sz);
	b.resize(sz);
	dft(a,false);
	dft(b,false);
	for(int i=0;i<sz;i++)
		a[i]*=b[i];
	dft(a,true);
	
	for(int i=0;i<sz;i++)
	{
		a[i]/=sz;		
	}
		
	while((a.size()>1)&&a[a.size()-1].real()==0)
		a.pop_back();
	
	cout<<"Result of multiplication is"<<endl;
	for(int i=0;i<a.size();i++)
	{
		cout<<((int)round(a[i].real()))<<" ";
	}	
	cout<<endl;
}
