#include<bits/stdc++.h>
using namespace std;
void fun(double a[],double b[])
{
	for(int i=0;i<20;i++)
		cout<<(b[i]-a[i])/b[i]*100<<endl;
}
int main()
{
	double a[]={2.09,3.01,2.24,3.07,2.47,3.17,4.02,4.02,4.12,4.12,2.39,3.06,2.93,3.29,3.74,3.63,4.08,4.08,4.42,4.42};
	double b[]={4,4,6,4.1,8.1,6.1,5.2,4.3,6.3,6.3,4.3,4.2,6.4,4.6,8.7,6.9,6.1,5.4,7.5,7.8};
	fun(a,b);
	return 0;
}
