#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cout<<"Enter the number of equations"<<endl;
	cin>>n;
	
	vector<double> a[n];
	cout<<"Enter the coeffecient matrix"<<endl;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		{
			double x;
			cin>>x;
			a[i].push_back(x);
		}
	double b[n];
	cout<<"Enter the B values"<<endl;
	for(int i=0;i<n;i++)	
		cin>>b[i];
	int pi[n];
	for(int i=0;i<n;i++)
		pi[i]=i;
	//LUP decomposition
	for(int k=0;k<n;k++)
	{
		double p=0;
		int e=k;
		for(int i=k;i<n;i++)
			if(abs(a[i][k])>p)
			{	
				p=abs(a[i][k]);
				e=i;
			}
		if(p==0)
		{
			cout<<"System is not solvable"<<endl;
			return 0;
		}
		swap(pi[k],pi[e]);
		swap(a[k],a[e]);
		for(int i=k+1;i<n;i++)
		{
			a[i][k]/=a[k][k];
			for(int j=k+1;j<n;j++)
				a[i][j]-=a[i][k]*a[k][j];
		}
	}
	cout<<"Decomposition matrix"<<endl;
	for(int i=0;i<n;i++)	
	{
		for(int j=0;j<n;j++)
			cout<<a[i][j]<<"\t";
		cout<<endl;
	}
	cout<<"Permutation matrix"<<endl;
	for(int i=0;i<n;i++)	
		cout<<pi[i]<<"\t";
	cout<<endl;
	double y[n];
	for(int i=0;i<n;i++)
	{
		double sum=0;
		for(int j=0;j<i;j++)
			sum+=a[i][j]*y[j];
		y[i]=b[pi[i]]-sum;	
	}
	for(int i=0;i<n;i++)	
		cout<<y[i]<<"\t";
	cout<<endl;
	double x[n];		
	for(int i=n-1;i>=0;i--)
	{
		double sum=0;
		for(int j=i+1;j<n;j++)
			sum+=(a[i][j]*x[j]);
		x[i]=(y[i]-sum)/a[i][i];	
	}
	cout<<"Values of unknowns are"<<endl;
	for(int i=0;i<n;i++)
		cout<<x[i]<<"\t";
	cout<<endl;
}
