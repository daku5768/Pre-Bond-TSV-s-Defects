#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair

int count_p=0;
vector<double>prob;
double expected_sessions=0;
vector<double>avg_sessions;
double expected_time=0;
vector<double>avg_time;
int worst_test_sessions=0;
double tt[5]={0,0.80,0.53,0.42,0.38};
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

void cal_expected_time(int r)
{
    expected_time=(prob[0]*avg_time[0])+(prob[1]*avg_time[1])+(avg_time[2]*prob[2]);
    if(r==1)
        return;
    double sum_prob=0;
    for(int i=3;i<=r+1;i++)
    {
        sum_prob+=prob[i];
    }
    expected_time+=(sum_prob*prob[r+1]);
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
void get(string s,vector<vector<int> >&ans)
{
  //  cout<<s<<endl;
     vector<int>v=call(s);
    ans.pb(v);
   
    bool val=next_permutation(s.begin(),s.end());
    
    while(val)
    {
     vector<int>v1=call(s);
     ans.pb(v1);

   //  cout<<s<<endl;
     val=next_permutation(s.begin(),s.end());
    }

    return ;
}
double computepequal2(int n,vector<vector<int> >&ans,int r)
{
	int m=ans.size();
    int sum=0;
    int p=2;
    double t_sum=0;
    for(int i1=0;i1<m;i1++)
    {

       vector<int> tsv;
       for(int j1=0;j1<n;j1++)
          tsv.pb(ans[i1][j1]);
          //cout<<"Input pattern :"<<endl;
          //for(int k1=0;k1<n;k1++)
          	//cout<<tsv[k1]<<" ";
          //cout<<endl;

		// for(int i=0;i<n;i++)
		//     cin>>tsv[i];
		vector<int> locations;
		int count=0;
		int curr_defected=0;
		vector<int> session_count(p+1,0);
		for(int i=0;i<n;i+=p)
		{
			if(i+p<=n)
				session_count[2]++;
			else
				session_count[1]++;
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
		    if(end==start)
		    {
		    	session_count[1]++;
		        locations.push_back(start);
		    }
		    else if(end-start==1)
		    {
		        int res=1;
		        res=res^tsv[start];
		        count++;
		        session_count[1]++;
		        if(res==1 && is_even)
		        {
		            locations.push_back(start);
		            locations.push_back(end);
		            continue;
		        }
		        if(res==0 && !is_even)
		        {
		            locations.push_back(end);
		            continue;
		        }
		        if(res==1 && !is_even)
		        {
		            locations.push_back(start);
		            continue;
		        }
		    }
		}
		for(int i=1;i<session_count.size();i++)
			t_sum+=(session_count[i]*tt[i]);
	    //cout<<"Defected positions are :";
	    //for(int i=0;i<locations.size();i++)
	      //  cout<<locations[i]<<" ";
	    //cout<<endl;
	    sum+=count;
	    //cout<<"No of test sessions are :"<<count<<endl<<endl;
		worst_test_sessions=max(worst_test_sessions,count);

    }
    
	avg_time[r]=(double)(t_sum)/(double)(m);
    cout<<"------------------------"<<endl;

    cout<<"Total no of patterns = "<<m<<endl;
    cout<<"average test session = "<<((double)(sum))/((double)(m))<<endl;
    //cout<<"Worst test sessions case are :"<<worst_test_sessions<<endl;
    return ((double)(sum)/(double)(m));
}
double computepequal3(int n,vector<vector<int> >&ans,int r)
{
    int m=ans.size();
    double t_sum=0;
    int sum=0;
    int p=3;
    for(int i1=0;i1<m;i1++)
    {

       vector<int> tsv;
       for(int j1=0;j1<n;j1++)
          tsv.pb(ans[i1][j1]);
          //cout<<"Input pattern :"<<endl;
          //for(int k1=0;k1<n;k1++)
          //cout<<tsv[k1]<<" ";
          //cout<<endl;

    // for(int i=0;i<n;i++)
    //     cin>>tsv[i];
    vector<int> locations;
    vector<int> session_count(p+1,0);
    int count=0;
    int curr_defected=0;
    for(int i=0;i<n;i+=p)
    {
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
            break;
        }
        if(end-start==1)
        {
            int res=1;
            res=res^tsv[start];
            count++;
            session_count[2]++;
            if(res==1 && is_even)
            {
                locations.push_back(start);
                locations.push_back(end);
                break;
            }
            if(res==0 && !is_even)
            {
                locations.push_back(end);
                break;
            }
            if(res==1 && !is_even)
            {
                locations.push_back(start);
                break;
            }
        }
        while(start <=end)
        {
            int k=start;
            vis++;
            int res=1;
            res=res^tsv[start];
            session_count[2]++;
            if(res==0)
                temp++;
            count++;
            if(vis==1 )
            {
                if(res==0 && !is_even)
                {
                    locations.push_back(k+1);
                    locations.push_back(k+2);
                    break;
                }
                if(res==1)
                   locations.push_back(k); 
            }
            else if(vis==2)
            {
                if(res==1)
                    locations.push_back(k);
                if(res==0 && ( (temp==2 && is_even)|| (temp==1 && !is_even) ) )
                {
                    locations.push_back(k+1);
                    break;
                }
                if(res==0 && temp==1 && is_even)
                    break;
                if(res==1 && ((temp==0 && !is_even) || (temp==1 && is_even)))
                {
                    break;
                }
                locations.push_back(k+1);
                break;
                
            }
            start++;
        }
    }
    for(int i=1;i<session_count.size();i++)
			t_sum+=(session_count[i]*tt[i]);
    //cout<<"Defected positions are :";
    //for(int i=0;i<locations.size();i++)
      //  cout<<locations[i]<<" ";
    //cout<<endl;
    sum+=count;
    cout<<"No of test sessions are :"<<count<<endl<<endl;
	worst_test_sessions=max(worst_test_sessions,count);

    }
    
	avg_time[r]=(double)(t_sum)/(double)(m);
    cout<<"------------------------"<<endl;

    cout<<"Total no of patterns = "<<m<<endl;
    cout<<"average test session = "<<((double)(sum))/((double)(m))<<endl;
    //cout<<"Worst test sessions case are :"<<worst_test_sessions<<endl;
    return ((double)(sum)/(double)(m));

} 


void less_than_three_fun(int start,int end,vector<int> &locations,bool is_even,int &count,vector<int> &tsv,vector<int> &session_count)
{
        bool alter=true;
        int temp=0,vis=0;
        if(end==start)
        {
            count++;
            session_count[3]++;
            locations.push_back(start);
            return;
        }
        if(end-start==1)
        {
        	session_count[3]++;
            int res=1;
            res=res^tsv[start];
            count++;
            if(res==1 && is_even)
            {
                locations.push_back(start);
                locations.push_back(end);
                return;
            }
            if(res==0 && !is_even)
            {
                locations.push_back(end);
                return;
            }
            if(res==1 && !is_even)
            {
                locations.push_back(start);
                return;
            }
        }
        while(start <=end)
        {
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
                    break;
                }
                if(res==1)
                   locations.push_back(k); 
            }
            else if(vis==2)
            {
                if(res==1)
                    locations.push_back(k);
                if(res==0 && ( (temp==2 && is_even)|| (temp==1 && !is_even) ) )
                {
                    locations.push_back(k+1);
                    break;
                }
                if(res==0 && temp==1 && is_even)
                    break;
                if(res==1 && ((temp==0 && !is_even) || (temp==1 && is_even)))
                {
                    break;
                }
                locations.push_back(k+1);
                break;
                
            }
            start++;
        }
}
double computepequal4(int n,vector<vector<int> >&ans,int r)
{
    int m=ans.size();
    int sum=0;
    int p=4;
    double t_sum=0;
    for(int i1=0;i1<m;i1++)
    {
       vector<int> tsv;
       for(int j1=0;j1<n;j1++)
          tsv.pb(ans[i1][j1]);
          //cout<<"Input pattern :"<<endl;
          //for(int k1=0;k1<n;k1++)
          //cout<<tsv[k1]<<" ";
          //cout<<endl;

    // for(int i=0;i<n;i++)
    //     cin>>tsv[i];
      vector<int> locations;
      vector<int> session_count(p+1,0);
    int count=0;
    for(int i=0;i<n;i+=p)
    {
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
        	less_than_three_fun(start,end,locations,is_even,count,tsv,session_count);
        	fg=false;
        }
        while(fg && start <=end)
        {
            int k;
            vis++;
            int res=1;
            session_count[3]++;
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
                if(res==1)
                    locations.push_back(k);
                break;
            }
            if(vis==1 )
            {
                if(res==1)
                {
                    locations.push_back(k);
                }
            }
            else if(vis==2)
            {
                if(res==0 && temp==2 && is_even)
                {
                    locations.push_back(k-1);
                    locations.push_back(k-2);
                    break;
                }
                if(res==1)
                    locations.push_back(k);
            }
            else if(vis==3)
            {
                if(is_even)
                {
                    if(temp==0){
                        locations.push_back(k);
                        locations.push_back(k+1);
                    }
                    else if(temp==1)
                    {
                        if(res==1)
                            locations.push_back(k);
                    }
                    else if(temp==2)
                    {
                        locations.push_back(k+1);
                    }
                }
                else
                {
                    if(temp==0)
                        locations.push_back(k);
                    else if(temp==1)
                    {
                        if(res==1)
                        {
                            locations.push_back(k);
                            locations.push_back(k+1);
                        }
                        else
                            locations.push_back(k+1);
                    }
                    else if(temp==2)
                    {
                        if(res==1)
                            locations.push_back(k);
                    }
                    else if(temp==3)
                    {
                        locations.push_back(k+1);
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
    for(int i=1;i<session_count.size();i++)
			t_sum+=(session_count[i]*tt[i]);
    //cout<<"Defected positions are :";
    //for(int i=0;i<locations.size();i++)
      //  cout<<locations[i]<<" ";
	//cout<<endl;
        sum+=count;
    //cout<<endl;
    //cout<<"No of test sessions are :"<<count<<endl<<endl;
	worst_test_sessions=max(worst_test_sessions,count);
    }
    
	avg_time[r]=(double)(t_sum)/(double)(m);
    //cout<<"------------------------"<<endl;

    //cout<<"Total no of patterns = "<<m<<endl;
    cout<<"average test session = "<<((double)(sum))/((double)(m))<<endl;
    //cout<<"Worst test sessions case are :"<<worst_test_sessions<<endl;
    return ((double)(sum)/(double)(m));

} 
int main() 
{
	int n,r,p;
	double yield;
    cout<<"Total number of tsv's: "<<endl;
    cin>>n;
    cout<<"Number of faulty tsv's:"<<endl;
    cin>>r;
    cout<<"Value of p:"<<endl;
    cin>>p;
    cout<<"Enter yield in range bw 0 and 1"<<endl;
    cin>>yield;
    int r_dup=r;
    r++;
    cal_prob(yield,n,r);
    avg_sessions.resize(r+2);
    avg_time.resize(r+2);
    while(r>=0){
        cout<<"PATTERNS FOR r="<<r<<endl;
        count_p=0;
        if(r==0)
        {
            count_p=1;
            for(int i=0;i<n;i++)
            {
                cout<<"1"<<" ";
            }
            int val=(n-1)/p +1;
            avg_sessions[r]=(double)(val);
            avg_time[r]=avg_sessions[r]*tt[p];
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
            vector<vector<int> >ans;
            get(s,ans);
            if(p==2)
		    	avg_sessions[r]=computepequal2(n,ans,r);
		    else if(p==3)
		    	avg_sessions[r]=computepequal3(n,ans,r);
		    else if(p==4)
		    	avg_sessions[r]=computepequal4(n,ans,r);
        }
        cout<<"total no of pattern = "<<count_p<<endl;
        r--;
        cout<<"#####################################"<<endl;
        cout<<endl;
        cout<<endl;
    }
    cal_expected_sessions(r_dup);
    cal_expected_time(r_dup);
    for(int i=0;i<avg_sessions.size();i++)
        cout<<"Avg sessions for "<<i<<" faults are: "<<avg_sessions[i]<<endl;
    cout<<endl;
    for(int i=0;i<prob.size();i++)
        cout<<"Probability for "<<i<<" faults are: "<<prob[i]<<endl;
    cout<<endl;
    cout<<"Expected sessions for r="<<r_dup<<" are: "<<expected_sessions<<endl;
    cout<<"Expected time for r="<<r_dup <<" are: "<<expected_time*10<<endl;
    

    
}	
/*Input format
  //no of tsvs(n),no of faults(r),session_size(p),yield(between 0 and 1) 
  8 1 2 0.995
*/
