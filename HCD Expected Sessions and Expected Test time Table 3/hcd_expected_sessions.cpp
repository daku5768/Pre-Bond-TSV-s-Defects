#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair

int count_p;
vector<string>res;
vector<double>prob;
double expected_sessions=0;
vector<double>avg_sessions;

void cal_expected_sessions(int r)
{
    expected_sessions=(prob[0]*avg_sessions[0])+(prob[1]*avg_sessions[1])+(avg_sessions[2]*prob[2]);
    if(r==1)
        return;
    double sum_prob=0;
    for(int i=3;i<=r+1;i++)
    {
        sum_prob+=prob[i];
    }
    expected_sessions+=(sum_prob*prob[r+1]);
}

int NcR(int n, int r) 
{
    long long p = 1, k = 1; 
    if (n - r < r) 
        r = n - r; 
    if (r != 0) { 
        while (r) { 
            p *= n; 
            k *= r; 
            long long m = __gcd(p, k); 
            p /= m; 
            k /= m; 
            n--; 
            r--; 
        } 
    } 
    else
        p = 1; 
      return p;
}

void cal_prob(double yield,int n,int f)
{
    for(int r=0;r<=f;r++)
    {
       int comp=NcR(n+r,r);
       double f1=pow((1-yield),r);
       double f2=pow(yield,n-r);
       prob.push_back((double)(comp)*f1*f2);
    }
}

bool check(int i,int j,int r,int c,vector<vector<bool> >&vis)
{
    if(i>=0&&j>=0&&i<r&&j<c)
    {
        if(!vis[i][j])
          return true;
    } 
    return false;

}

void dfs(vector<vector<bool> >&vis,vector<vector<char> >&v1,int r,int c,int i ,int j)
{
    if(vis[i][j])
      return ;
      vis[i][j]=true;

      if(v1[i][j]=='1'||v1[i][j]=='x')
        return ;


     
     v1[i][j]='1';

     int dx[4]={1,-1,0,0};
     int dy[4]={0,0,1,-1};

     for(int k=0;k<4;k++)
     {
         int i1=i+dx[k];
         int j1=j+dy[k];

         if(check(i1,j1,r,c,vis))
         {
             dfs(vis,v1,r,c,i1,j1);
         }
     }
}

void print_matrix(string s,int n,int m)
{
     int r,c;
      c=m;

    int n1=(n%m)?(((n/m)+1)*m):n;
    r=n1/m;

     vector<vector<char> >v(r,vector<char>(c));
        for(int i=0;i<s.length();i++)
          v[i/c][i%c]=s[i];
       for(int i=0;i<r;i++)
        {
           for(int j=0;j<c;j++)
           {
               cout<<v[i][j]<<" ";
           }
           cout<<endl;
        }

        
       

}
void print(string s,int n,int r,int c)
{
   vector<vector<char> >v(r,vector<char>(c));
   vector<vector<char> >v1(r,vector<char>(c));
 
   for(int i=0;i<s.length();i++)
        v[i/c][i%c]=s[i];
   
   v1=v;
   vector<vector<bool> >vis(r,vector<bool>(c,false));

   bool flag=false;
   int idx=-1,idy=-1;
   for(int i=0;i<r;i++)
   {
       for(int j=0;j<c;j++)
       {
           if(v1[i][j]=='0')
           {
               idx=i;
               idy=j;
               flag=true;
           }
           if(flag)
            break;
       }
       if(flag)
         break;
   }
    
   dfs(vis,v1,r,c,idx,idy);
   flag=false;
   for(int i=0;i<r;i++)
   {
       for(int j=0;j<c;j++)
       {
           if(v1[i][j]=='0')
           {
               flag=true;
           }
           if(flag)
            break;
       }
       if(flag)
         break;
   }
   if(flag==false)
   {
       count_p+=1;
       res.pb(s);
   }
}

void to_matrix(string s,int n,int m)
{
    int r,c;
    c=m;
    int n1=(n%m)?(((n/m)+1)*m):n;
    r=n1/m;
    for(int i=0;i<n1-n;i++)
        s.pb('x');
    print(s,n1,r,c);
}
void get(string s,int n,int m)
{
    to_matrix(s,n,m);
    bool val=next_permutation(s.begin(),s.end());
    while(val)
    {
        to_matrix(s,n,m);
        val=next_permutation(s.begin(),s.end());
    }
    return ;
}

double to_func(int n,int p,int m)
{
    int tot_sum=0;
    for(int yy=0;yy<res.size();yy++)
    {
        string f=res[yy];
        print_matrix(f,n,p);
        int id=0;
        vector<vector<int> >  tsv((n-1)/p +1,vector<int>());
        vector<int> locations;
        int count=0;
        for(int i=0;i<n;i+=p)
        {
            int j=i;
            while(j<n && j<i+p){
                int a;
                  if(f[id]=='0')
                   a=0;
                else if(f[id]=='1')
                   a=1;
               
                id+=1;  
                tsv[count].push_back(a);
                j++;
            }
            count++;
        }
        count=0;
        int test_sessions=0;
    	for(int i=0;i<tsv.size();i++)
    	{
        	vector<int> x(tsv[i].size(),1);
        	//parallel xoring
        	for(int j=0;j<x.size();j++)
        	{
        	    x[j]^=tsv[i][j];
        	}
        	test_sessions++;
        	int row_faults=0;
        	for(int j=0;j<x.size();j++)
        	{
        	    if(x[j]==1)
        	    {
        	        row_faults++;
        	        locations.push_back((i*p)+j+1);
        	    }
        	}
        	count+=row_faults;
        	if(count==m-1 && row_faults==1){
        	    locations.push_back(locations.back()+p);
        	    count++;
        	}
        	if(count==m)
        	    break;
        	if(i+1==tsv.size()-1 && count+tsv[i+1].size()==m)
        	{
        	    for(int j=0;j<tsv[i+1].size();j++)
        	        locations.push_back((i+1)*p +j+1);
        	    break;
        	}
    	}
    	cout<<"Faulty locations are :";
    	for(int i=0;i<locations.size();i++)
    	    cout<<locations[i]<<" ";
    
        tot_sum+=test_sessions;
    	cout<<endl<<"Test sessions are: "<<test_sessions<<endl;
         cout<<"---------------------------"<<endl;  
    }
    cout<<"average test session = "<<(double)(tot_sum)/(double)(res.size())<<endl;
    return (double)(tot_sum)/(double)(res.size());
}
int main()
{
    int n,r,p;
    double yield;
    cout<<"Total number of tsv's: "<<endl;
    cin>>n;
    cout<<"Number of faulty tsv's:"<<endl;
    cin>>r;
    cout<<"enter session size: "<<endl;
    cin>>p;
    cout<<"Enter yield in range bw 0 and 1"<<endl;
    cin>>yield;
    int r_dup=r;
    r++;
    cal_prob(yield,n,r);
    avg_sessions.resize(r+1);
    while(r>=0){
        cout<<"PATTERNS FOR r="<<r<<endl;
        count_p=0;
        res.clear();
        if(r==0)
        {
            count_p=1;
            int val=1;
            int rows=((n-1)/p)+1;
            for(int i=0;i<rows && val<=n;i++)
            {
                for(int j=0;j<p && val++<=n;j++)
                    cout<<"1"<<" ";
                cout<<endl;
            }
            avg_sessions[r]=(double)(min(p,rows));
            cout<<endl<<"Average Test sessions are: "<<avg_sessions[r]<<endl;
            
            
        }
        else
        {
            string s="";
            for(int i=0;i<n;i++)
            {
                if(i<r)
                    s=s+'0';
                else
                    s=s+'1';
            }
            get(s,n,p);
            
            avg_sessions[r]=to_func(n,p,r);
        }
        cout<<"total no of pattern = "<<count_p<<endl;
        r--;
        cout<<"#####################################"<<endl;
        cout<<endl;
        cout<<endl;
    }
    cal_expected_sessions(r_dup);
    for(int i=0;i<avg_sessions.size();i++)
        cout<<"Avg sessions for "<<i<<" faults are: "<<avg_sessions[i]<<endl;
    cout<<endl;
    for(int i=0;i<prob.size();i++)
        cout<<"Probability for "<<i<<" faults are: "<<prob[i]<<endl;
    cout<<endl;
    cout<<"Expected sessions for r="<<r_dup<<" are: "<<expected_sessions<<endl;
}

/*Input format
  //no of tsvs(n),no of faults(r),session_size(p),yield(between 0 and 1) 
  8 1 2 0.995
*/
