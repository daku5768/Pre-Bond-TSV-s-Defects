#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair

int count_p;
int zero;
int rm,clustered;
vector<string> res;
bool check(int i,int j,int r,int c,vector<vector<bool>>&vis)
{
    if(i>=0&&j>=0&&i<r&&j<c)
    {
        if(!vis[i][j])
          return true;
    } 
    return false;

}

void dfs(vector<vector<bool>>&vis,vector<vector<char>>&v1,int r,int c,int i ,int j)
{
    if(vis[i][j])
      return ;
      vis[i][j]=true;

      if(v1[i][j]=='1'||v1[i][j]=='x')
        return ;

     zero+=1;
     
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

void print(string s,int n,int r,int c)
{
      vector<vector<char>>v(r,vector<char>(c));
       vector<vector<char>>v1(r,vector<char>(c));
     
      for(int i=0;i<s.length();i++)
          v[i/c][i%c]=s[i];
       
        v1=v;
        vector<vector<bool>>vis(r,vector<bool>(c,false));
       vector<int>can;
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
           zero=0;
           dfs(vis,v1,r,c,idx,idy);
                   can.pb(zero);
               }
               
           }
           
       }
    int clus=0,ones=0;    
  for(int i=0;i<can.size();i++)
  {
    if(can[i]==1)
    ones+=1;
    else if(can[i]==clustered)
    clus=1;
  }

  if(ones==rm&&clus==1)
  {
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
void print_matrix(string s,int n,int m)
{
     int r,c;
      c=m;

    int n1=(n%m)?(((n/m)+1)*m):n;
    r=n1/m;

     vector<vector<char>>v(r,vector<char>(c));
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
double compute_hrd(int n,int p,int r)
{
    int m=res.size();
    int sum=0;
    for(int i1=0;i1<m;i1++)
    {
        vector<int> tsv;
       for(int j1=0;j1<n;j1++)
          tsv.pb(res[i1][j1]-'0');
        //   for(int k1=0;k1<n;k1++)
        //     cout<<tsv[k1]<<" ";
        //   cout<<endl;

   
    vector<int> locations;
    int count=0;
    int curr_defected=0;
    for(int i=0;i<n;i+=p)
    {
        count++;
        int not_defected=1;
        for(int j=i;j<min(i+p,n);j++)
          not_defected=not_defected & tsv[j];  
        
        if(not_defected==1)
            continue;
        
        int cummulative_xor=tsv[i];
        bool is_even=false;
        for(int j=i+1;j<min(i+p,n);j++)
            cummulative_xor=cummulative_xor^tsv[j];
            
        if(cummulative_xor%2==0)
            is_even=true;
        int start=i,end=min(i+p-1,n-1);
        bool alter=true;
        int temp=0,vis=0;
        while(start <=end)
        {
            if(curr_defected==r)
                break;
            int k;
            vis++;
            int res=1;
            if(alter){
                res=res^tsv[start];
                k=start;
            }
            else{
                res=res^tsv[end];
                k=end;
            }
            if(res==0)
                temp++;
            count++;
            if(start==end)
            {
                if(res==1){
                    locations.push_back(k);
                    curr_defected++;
                }
                break;
            }
            if(vis==1 )
            {
                if(res==1)
                {
                    curr_defected++;
                    locations.push_back(k);
                }
            }
            else if(vis==2)
            {
                if(res==0 && temp==2 && is_even)
                {
                    curr_defected+=2;
                    locations.push_back(k-1);
                    locations.push_back(k-2);
                    break;
                }
                if(res==1){
                    locations.push_back(k);
                    curr_defected++;
                }
            }
            else if(vis==3)
            {
                if(is_even)
                {
                    if(temp==0){
                        locations.push_back(k);
                        locations.push_back(k+1);
                        curr_defected+=2;
                    }
                    else if(temp==1)
                    {
                        if(res==1){
                            locations.push_back(k);
                            curr_defected++;
                        }
                    }
                    else if(temp==2)
                    {
                        locations.push_back(k+1);
                        curr_defected++;
                    }
                }
                else
                {
                    if(temp==0){
                        locations.push_back(k);
                        curr_defected++;
                    }
                    else if(temp==1)
                    {
                        if(res==1)
                        {
                            locations.push_back(k);
                            locations.push_back(k+1);
                            curr_defected+=2;
                        }
                        else{
                            locations.push_back(k+1);
                            curr_defected++;
                        }
                    }
                    else if(temp==2)
                    {
                        if(res==1){
                            locations.push_back(k);
                            curr_defected++;
                        }
                    }
                    else if(temp==3)
                    {
                        locations.push_back(k+1);
                        curr_defected++;
                    }
                }
                break;
                
            }
            
            if(alter)
                start++;
            else
                end--;
            alter=!alter;
        }
    }
    // cout<<"Defected positions are :";
    // for(int i=0;i<locations.size();i++)
    //     cout<<locations[i]+1<<" ";

        sum+=count;
    // cout<<endl;
    // cout<<"No of test sessions are :"<<count<<endl;

    }
    

   // cout<<"------------------------"<<endl;

    return ((double)(sum))/((double)(res.size()));

}
double per_cal(double a,double b)
{
    return (b-a)/b*100;
}
double compute_hcd(int n,int p,int m)
{
    int tot_sum=0;
    for(int yy=0;yy<res.size();yy++)
    {
        string f=res[yy];
       // print_matrix(f,n,p);
        int id=0;
        vector<vector<int>>  tsv((n-1)/p +1,vector<int>());
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
          
          if(count==m)
              break;
          
      }
      //cout<<"Faulty locations are :";
      //for(int i=0;i<locations.size();i++)
       //   cout<<locations[i]<<" ";
    
        tot_sum+=test_sessions;
    //  cout<<"Test sessions are: "<<test_sessions<<endl;
    //  cout<<endl;
    }
    return (double)(tot_sum)/(double)(res.size()) ;
}

int main()
{
    int n,r,p=4;
    cout<<"Total number of tsv's: "<<endl;
    cin>>n;
    cout<<"No of fauly tsv as random defects"<<endl;
    cin>>rm;
    cout<<"No of faulty tsv as clustered defects"<<endl;
    cin>>clustered;
    cout<<endl;
    r=rm+clustered;
    string s="";
    count_p=0;
    for(int i=0;i<n;i++)
    {
        if(i<r)
        s=s+'0';
        else
        s=s+'1';
    }
    
    get(s,n,p);
    double hcd_test_sessions=compute_hcd(n,p,r);
    double hrd_test_sessions=compute_hrd(n,p,r);
    double percentage_change=per_cal(hcd_test_sessions,hrd_test_sessions);
    cout<<"average test sessions for hcd = "<<hcd_test_sessions<<endl;
    cout<<"average test sessions for hrd = "<<hrd_test_sessions<<endl;
    cout<<"Percentage reduction of hcd over hrd = "<<percentage_change<<"%"<<endl;
    cout<<"total no of patterns = "<<res.size()<<endl;

}

/*input format
Total number of tsv's ->
Number of TSV's in random state ->
Number of TSV's in clustered state ->

20
2
3

*/