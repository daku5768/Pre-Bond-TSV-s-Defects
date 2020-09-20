#include<bits/stdc++.h>
using namespace std;
int n;
int rm_ratio;
int clus_ratio;
int rm,clus;
double fault_rate;
int sum_hrd=0;
int sum_hcd=0;
int total_cases=10000;
vector< vector<int> > v;
void initial_values()
{
	int sum_tsvs=fault_rate*n;
	double a=double(rm_ratio)/(rm_ratio+clus_ratio);
	rm=sum_tsvs *a;
	clus=sum_tsvs-rm;
	//cout<<sum_tsvs<<" "<<rm<<" "<<clus<<endl;
}
void compute_hrd(int n)
{
    int r=rm+clus;
    int p=4;
    vector<int> tsv;
    for(int i1=0;i1<v.size();i1++)
        for(int j1=0;j1<v[i1].size();j1++)
            tsv.push_back(v[i1][j1]);
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
    // cout<<"Defected positions in hrd are :";
    // for(int i=0;i<locations.size();i++)
    //     cout<<locations[i]+1<<" ";

        sum_hrd+=count;
    // cout<<endl;
    // cout<<"No of test sessions in hrd are :"<<count<<endl;

    



}

void compute_hcd(int n)
{
    int p=4;
    int m=rm+clus;
    vector<int> locations;
    int count=0;
    int test_sessions=0;
	for(int i=0;i<v.size();i++)
	{
    	vector<int> x(v[i].size(),1);
    	for(int j=0;j<x.size();j++)
    	{
    	    x[j]^=v[i][j];
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
// 	cout<<"Faulty locations in hcd are :";
// 	for(int i=0;i<locations.size();i++)
// 	    cout<<locations[i]<<" ";

    sum_hcd+=test_sessions;
    //	cout<<"Test sessions are: "<<test_sessions<<endl;
    //	cout<<endl;
   
}    
 double per_cal(double a,double b)
{
    return (b-a)/b*100;
}   
void get(int n)
{
    int dup=total_cases;
     while(dup--)
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
    // for(i=0;i<r;i++)
    // {
    //     for(int j=0;j<c;j++)
    //     cout<<v[i][j]<<" ";
    //     cout<<endl;
    // }
    compute_hcd(n);
    compute_hrd(n);
   // cout<<"----------------------"<<endl;

    v.clear();
    }
}
int main()
{
    cout<<"Enter no of tsv's"<<endl; 
    cin>>n;
    cout<<"Enter ratio of random and clustered:"<<endl;
    cin>>rm_ratio>>clus_ratio;
    cout<<"Enter fault rate:"<<endl;
    cin>>fault_rate;
    initial_values();
    srand(time(NULL));
    get(n);
    // cout<<sum_hcd<<" "<<sum_hrd<<" "<<total_cases<<endl;
    double hcd_test=(double)(sum_hcd)/(double)(total_cases);
    double hrd_test=(double)(sum_hrd)/(double)(total_cases);
    double percentage_change=per_cal(hcd_test,hrd_test);
    
    cout<<"Average test sessions for hcd = "<<hcd_test<<endl;
    cout<<"Average test sessions for hrd = "<<hrd_test<<endl;
    cout<<"Percentage reduction of hcd over hrd = "<<percentage_change<<"%"<<endl;
}

/*Input format
Total number of tsv's ->
Number of TSV's in random state ->
Number of TSV's in clustered state ->
Number of cases to generate ->

2000
9 1
0.02
*/


/*Output format
Average test sessions for hcd = 4.65767
Average test sessions for hrd = 14.836
Percentage reduction of hcd over hrd = 68.6056%
*/
