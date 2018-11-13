#include<bits/stdc++.h>
using namespace std;
class Point
{
	public:
	int x,y;
	Point()
	{
		x=y=0;
	}
	Point(int a,int b)
	{
		x=a;
		y=b;
	}
		
};
int direction(Point p0,Point p1,Point p2)
{
	return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}

class Line
{	
	public:
	Point a,b;
	Line(Point x,Point y)
	{
		a=x;
		b=y;
	}
	bool onsegment(Point p)
	{
		if(min(a.x,b.x)<=p.x&&p.x<=max(a.x,b.x)&&min(a.y,b.y)<=p.y&&p.y<=max(a.y,b.y))
			return true;
		return false;
	}
	bool intersects(Line l)
	{
		int d1=direction(l.a,l.b,a);
		int d2=direction(l.a,l.b,b);
		int d3=direction(a,b,l.a);
		int d4=direction(a,b,l.b);
		if((d3*d4<0)&&(d1*d2<0))
			return true;
		else if(d1==0&&l.onsegment(a))
			return true;
		else if(d2==0&&l.onsegment(b))
			return true;
		else if(d3==0&&onsegment(l.a))
			return true;
		else if(d4==0&&onsegment(l.b))
			return true;
	}	
};
class Event
{
	public:
	int x,y,type,line;
	Event(int a,int b,int t,int li)
	{
		x=a;y=b;type=t;line=li;
	}
	
};
bool operator <(Event d,Event e)
	{
		if(d.x<e.x)
			return true;
		if(d.x>e.x)
			return false;
		if(d.type==0&&e.type==1)
			return false;
		if(d.type==1&&e.type==0)
			return true;
		if(d.y<e.y)
			return true;
		return false;
	}
int main()
{
	vector<Line> l;
	vector<Event> e;
	int n;
	cout<<"Enter the number of line segments"<<endl;
	cin>>n;
	cout<<"Enter the starting and ending coordinates of segments"<<endl;
	for(int i=0;i<n;i++)
	{
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		l.push_back(Line(Point(a,b),Point(c,d)));
		e.push_back(Event(a,b,0,i));
		e.push_back(Event(c,b,1,i));		
	}
	sort(e.begin(),e.end());
	set< pair<int,int> > s;
	for(int i=0;i<e.size();i++)
	{
		if(e[i].type==0)
		{
			pair<int,int> p=make_pair(e[i].y,e[i].line);
			s.insert(p);
			auto it=s.find(p);
			if(it!=s.begin())
			{
				auto it1=--it;
				it++;
				if(l[e[i].line].intersects(l[(*it1).second]))
				{
					cout<<"Intersection exists"<<endl;
					return true;
				}
			}
			if(it!=s.end())
			{
				auto it2=++it;
				if(it2!=s.end())
				{
					if(l[e[i].line].intersects(l[(*it2).second]))
					{
						cout<<"Intersection exists"<<endl;
						return true;
					}
				}
			}				
		}
		else
		{
			pair<int,int> p=make_pair(e[i].y,e[i].line);
			auto it=s.find(p);
			if(it!=s.end()&&it!=s.begin())
			{
				auto it2=++it;
				--it;	
				auto it1=--it;
				if(it2!=s.end())
				{
					if(l[(*it2).second].intersects(l[(*it1).second]))
					{
						cout<<"Intersection exists"<<endl;
						return true;
					}
				}
			}
			
			
			
			s.erase(p);			
		}		
	}
	cout<<"No intersection"<<endl;
	return 0;
			
}
