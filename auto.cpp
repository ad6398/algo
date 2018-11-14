#include<bits/stdc++.h>
using namespace std;

#define f(i,x,y) for(int i=x;i<y;i++)


int main()
{

string s,t;
cin>>s>>t;

int m= t.size();
int n= s.size();

int i=1;
int lps[m];
lps[0]=0;
int l=0;
while(i<m)
{

	if(t[i]==t[l])
	{
		l++;
		lps[i]=l;
		i++;
	
	}
	else
	{
		if(l==0)
		{
			lps[i]=0;
			i++;
		
		}
		else
		l= lps[l-1];
		
	
	}

}

int tf[m+1][26];
f(i,0,26) tf[0][i]=0;
tf[0][t[0]-'a']=1;
int lp=0;
f(i,1,m+1)
{
	f(j,0,26) tf[i][j]= tf[lp][j];
	
	tf[i][t[i]-'a'] =i+1;
	if(i<m)
	lp= tf[lp][t[i]-'a'];
	

}
/*f(i,0,m+1)
{
f(j,0,26) cout<<tf[i][j]<<" ";
cout<<endl;
}
*/
int p=0;
f(i,0,n)
{

p= tf[p][s[i]-'a'];
if(p==m){
cout<<" found AT "<<i-m+1<<endl;

}

}









return 0;
}
