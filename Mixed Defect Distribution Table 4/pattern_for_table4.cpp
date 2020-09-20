#include<bits/stdc++.h>
using namespace std;
int rm,clus;
vector<vector<int> >v;
void get(int n)
{
    int cases=10;
    while(cases--)
    {
     int r=n/4,c=4;
     v.clear();
     v.resize(r,vector<int>(c,1));
   
    
    int u=rand()%n;
    int x=u/4,y=u%4;
    v[x][y]=0;
    
    
    deque<pair<int,int> >q;
    q.push_front({x,y});    
    int i=0; 
    while(i<clus-1)
    {
        pair<int,int>zz=q.front();
        q.pop_front();
        q.push_back(zz);

        x=zz.first;
        y=zz.second;
       


        int dx[4]={1,-1,0,0};
        int dy[4]={0,0,1,-1};

        int d1=rand()%4;
        
        
        int i1=x+dx[d1];
        int j1=y+dy[d1];

        if(i1>=0&&j1>=0&&i1<r&&j1<c&&v[i1][j1]==1)
        {
            
            v[i1][j1]=0;
            bool l=true,r=true,u=true,d=true;
            if(j1-1<0)
            l=false;
            else if(v[i1][j1-1]==0)
            l=false;

            if(j1+1>=c)
            r=false;
            else if(v[i1][j1+1]==0)
            r=false;

            if(i1-1<0)
            u=false;
            else if(v[i1-1][j1]==0)
            u=false;

            if(i1+1>=r)
            d=false;
            else if(v[i1+1][j1]==0)
            d=false;

            if(l||r||u||d)
            q.push_back({i1,j1});
            
            
            i+=1;
           
            
            
        }
    }
    i=0;
    
    while(i<rm)
    {
        int f=rand()%n;
        
        int i1=f/4;
        int j1=f%4;
    
        if(v[i1][j1]==0)
        continue; 
        bool up=true,down=true,left=true,right=true;
        if(i1-1>=0&&v[i1-1][j1]==0)
        up=false;
        if(i1+1<r&&v[i1+1][j1]==0)
        down=false;
        if(j1-1>=0&&v[i1][j1-1]==0)
        left=false;
        if(j1+1<c&&v[i1][j1+1]==0)
        right=false;

        if(up&&down&&left&&right)
        {
       
            v[i1][j1]=0;
            i+=1;
        }
    }
    for(i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        cout<<v[i][j]<<" ";
        cout<<endl;
    }
    cout<<"----------------------"<<endl;

    v.clear();
    }
}
    
    

int main()
{
    int n;
    cout<<"Enter total no of tsv's"<<endl; 
    cin>>n;
    cout<<"Enter no of tsv in random defects"<<endl;
    cin>>rm;
    cout<<"Enter no of tsvs in clutered defects"<<endl;
    cin>>clus;

    srand(time(NULL));
    get(n);
}
