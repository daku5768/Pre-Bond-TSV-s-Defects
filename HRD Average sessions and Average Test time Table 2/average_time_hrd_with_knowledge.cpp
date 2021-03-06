#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair

double tt[5]={0,0.80,0.53,0.42,0.38};
double worst_test_time=0;
int worst_test_sessions=0;
vector<int> call(string s)
{
    int n=s.length();
    vector<int>v;   
    for(int i=0;i<n;i++)
    {
        if(s[i]=='0')
        v.pb(0);
        else
        v.pb(1);
    }

    return v;
}
void print(vector<int> session_count,double curr_sess_time)
{
	for(int i=session_count.size()-1;i>=0 && session_count[i];i--)
	{
		cout<<"No of test sessions with size "<<i<<"are "<<session_count[i]<<endl;
	}
	cout<<"Test time for current session is "<<curr_sess_time<<endl;
}
void get(string s,vector<vector<int> >&ans)
{
     vector<int>v=call(s);
    ans.pb(v);
   
    bool val=next_permutation(s.begin(),s.end());
    
    while(val)
    {
     vector<int>v1=call(s);
     ans.pb(v1);

     val=next_permutation(s.begin(),s.end());
    }

    return ;
}

void computepequal3(int n,int r,vector<vector<int> >&ans)
{
    int m=ans.size();
    int sum=0;
    int p=3;
    double t_sum=0;
    for(int i1=0;i1<m;i1++)
    {

       vector<int> tsv;
       for(int j1=0;j1<n;j1++)
          tsv.pb(ans[i1][j1]);
       cout<<"Input pattern :"<<endl;
       for(int k1=0;k1<n;k1++)
          cout<<tsv[k1]<<" ";
       cout<<endl;

    vector<int> locations;
    vector<int> session_count(p+1,0);
    int count=0;
    int curr_defected=0;
    for(int i=0;i<n;i+=p)
    {
    	if(curr_defected==r)
                break;
        count++;
        int not_defected=1;
        for(int j=i;j<min(i+p,n);j++)
          not_defected=not_defected & tsv[j];  
        if(i+p<=n)
        	session_count[3]++;
        else
        	session_count[2]++; 
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
        if(end==start)
        {
            count++;
            session_count[2]++;
            locations.push_back(start);
            curr_defected++;
            break;
        }
        if(end-start==1)
        {
            int res=1;
            session_count[2]++;
            res=res^tsv[start];
            count++;
            if(res==1 && is_even)
            {
                locations.push_back(start);
                locations.push_back(end);
                curr_defected+=2;
                break;
            }
            if(res==0 && !is_even)
            {
                locations.push_back(end);
                curr_defected++;
                break;
            }
            if(res==1 && !is_even)
            {
                locations.push_back(start);
                curr_defected++;
                break;
            }
        }
        while(start <=end)
        {
        	if(curr_defected==r)
                break;
            int k=start;
            session_count[2]++;
            vis++;
            int res=1;
            res=res^tsv[start];
            if(res==0)
                temp++;
            count++;
            if(vis==1 )
            {
                if(res==0 && !is_even)
                {
                    locations.push_back(k+1);
                    locations.push_back(k+2);
                    curr_defected+=2;
                    break;
                }
                if(res==1){
                   locations.push_back(k);
                   curr_defected++;
				}
            }
            else if(vis==2)
            {
                if(res==1){
                	locations.push_back(k);
                	curr_defected++;
                }
                    
                if(res==0 && ( (temp==2 && is_even)|| (temp==1 && !is_even) ) )
                {
                    locations.push_back(k+1);
                    curr_defected++;
                    break;
                }
                if(res==0 && temp==1 && is_even)
                    break;
                if(res==1 && ((temp==0 && !is_even) || (temp==1 && is_even)))
                {
                    break;
                }
                locations.push_back(k+1);
                curr_defected++;
                break;
                
            }
            start++;
        }
    }
    double curr_sess_time=0;
    for(int i=1;i<session_count.size();i++)
			curr_sess_time+=(session_count[i]*tt[i]);
	t_sum+=curr_sess_time;
    cout<<"Defected positions are :";
    for(int i=0;i<locations.size();i++)
        cout<<locations[i]<<" ";
    cout<<endl;
    print(session_count,curr_sess_time);
    sum+=count;
    cout<<"No of test sessions are :"<<count<<endl<<endl;
	worst_test_sessions=max(worst_test_sessions,count);
	worst_test_time=max(curr_sess_time,worst_test_time);
    }
    

    //cout<<"------------------------"<<endl;

    //cout<<"Total no of patterns = "<<m<<endl;
    cout<<"average test session = "<<((float)(sum))/((float)(m))<<endl;
    cout<<"Worst test sessions case are :"<<worst_test_sessions<<endl;
	cout<<"Average test time = "<<((double)(t_sum))/((double)(m))<<endl;
    cout<<"Worst test time is :"<<worst_test_time<<endl;
} 


void less_than_three_fun(int start,int end,vector<int> &locations,bool is_even,int &count,vector<int> &tsv,int &curr_defected,int &r,vector<int> &session_count)
{
     	bool alter=true;
        int temp=0,vis=0;
        if(end==start)
        {
            count++;
            session_count[3]++;
            locations.push_back(start);
            curr_defected++;
            return;
        }
        if(end-start==1)
        {
            int res=1;
            res=res^tsv[start];
            count++;
            session_count[3]++;
            if(res==1 && is_even)
            {
                locations.push_back(start);
                locations.push_back(end);
                curr_defected+=2;
                return;
            }
            if(res==0 && !is_even)
            {
                locations.push_back(end);
                curr_defected++;
                return;
            }
            if(res==1 && !is_even)
            {
                locations.push_back(start);
                curr_defected++;
                return;
            }
        }
        while(start <=end)
        {
        	if(curr_defected==r)
                break;
            session_count[3]++;
            int k=start;
            vis++;
            int res=1;
            res=res^tsv[start];
            if(res==0)
                temp++;
            count++;
            if(vis==1 )
            {
                if(res==0 && !is_even)
                {
                    locations.push_back(k+1);
                    locations.push_back(k+2);
                    curr_defected+=2;
                    break;
                }
                if(res==1){
                   locations.push_back(k);
                   curr_defected++;
				}
            }
            else if(vis==2)
            {
                if(res==1){
                	locations.push_back(k);
                	curr_defected++;
                }
                    
                if(res==0 && ( (temp==2 && is_even)|| (temp==1 && !is_even) ) )
                {
                    locations.push_back(k+1);
                    curr_defected++;
                    break;
                }
                if(res==0 && temp==1 && is_even)
                    break;
                if(res==1 && ((temp==0 && !is_even) || (temp==1 && is_even)))
                {
                    break;
                }
                locations.push_back(k+1);
                curr_defected++;
                break;
                
            }
            start++;
        }
	
}


void computepequal4(int n,int r,vector<vector<int> >&ans)
{
    int m=ans.size();
    int sum=0;
    double t_sum=0;
    int p=4;
    for(int i1=0;i1<m;i1++)
    {
        vector<int> tsv;
       for(int j1=0;j1<n;j1++)
          tsv.pb(ans[i1][j1]);
          cout<<"Input pattern :"<<endl;
          for(int k1=0;k1<n;k1++)
          	cout<<tsv[k1]<<" ";
          cout<<endl;

      vector<int> locations;
      vector<int> session_count(p+1,0);
    int count=0;
    int curr_defected=0;
    for(int i=0;i<n;i+=p)
    {
    	if(curr_defected==r)
                break;
        count++;
        int not_defected=1;
        for(int j=i;j<min(i+p,n);j++)
          not_defected=not_defected & tsv[j];  
        if(i+p<=n)
        	session_count[4]++;
        else
        	session_count[3]++;
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
        bool fg=true;
        if(end-start<=2)
        {
        	less_than_three_fun(start,end,locations,is_even,count,tsv,curr_defected,r,session_count);
        	fg=false;
        }
        while(fg && start <=end)
        {
            if(curr_defected==r)
                break;
            session_count[3]++;
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
    double curr_sess_time=0;
    for(int i=1;i<session_count.size();i++)
			curr_sess_time+=(session_count[i]*tt[i]);
	t_sum+=curr_sess_time;
	print(session_count,curr_sess_time);
    cout<<"Defected positions are :";
    for(int i=0;i<locations.size();i++)
        cout<<locations[i]<<" ";
	cout<<endl;
        sum+=count;
    //cout<<endl;
    cout<<"No of test sessions are :"<<count<<endl<<endl;
	worst_test_sessions=max(worst_test_sessions,count);
	worst_test_time=max(curr_sess_time,worst_test_time);
    }
    

    //cout<<"------------------------"<<endl;

    //cout<<"Total no of patterns = "<<m<<endl;
    cout<<"average test session = "<<((float)(sum))/((float)(m))<<endl;
    cout<<"Worst test sessions case are :"<<worst_test_sessions<<endl;
    cout<<"Average test time = "<<((double)(t_sum))/((double)(m))<<endl;
    cout<<"Worst test time is :"<<worst_test_time<<endl;

} 
int main() 
{
	int n,f,p;
    cout<<"Total number of tsv's: "<<endl;
    cin>>n;
    cout<<"Number of faulty tsv's:"<<endl;
    cin>>f;
    cout<<"Value of p:"<<endl;
    cin>>p;
    string s="";
    
    for(int i=0;i<n;i++)
    {
        if(i<f)
        s=s+'0';
        else
        s=s+'1';
    }
    vector<vector<int> >ans;

    get(s,ans);
    if(p==3)
    	computepequal3(n,f,ans);
    else if(p==4)
    	computepequal4(n,f,ans);
}	

