#include<bits/stdc++.h>
using namespace std;
int br(vector< complex<double> > &a,int n)
{
	int ln=0;
	int c=n;
	while(c!=1)
	{
		ln++;
		c>>=1;
	}
	for(int i=0;i<n;i++)
	{
		int rev=0;
		int cp=i;
		for(int j=0;j<ln;j++)
		{
			rev*=2;
			rev|=(cp&1);
			cp>>=1;
		}
		if(rev>i)
			swap(a[i],a[rev]);
	}
	return ln;
}
void dft(vector< complex<double> > &a,bool invert)
{
	
	int n=a.size();
	br(a,n);
	for(int gap=1;gap<n;gap=gap*2)
	{
		double ang=(2*acos(-1))/(gap*2);
		if(invert)
			ang*=-1;
		complex<double> wn(cos(ang),sin(ang));
		for(int i=0;i+gap<n;i+=2*gap)
		{
			complex<double> w(1);
			for(int j=i;j<i+gap;j++)
			{
				complex<double> u=a[j];
				complex<double> t=w*a[j+gap];
				a[j]=u+t;
				a[j+gap]=u-t;
				w*=wn;
			}	
		}
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
