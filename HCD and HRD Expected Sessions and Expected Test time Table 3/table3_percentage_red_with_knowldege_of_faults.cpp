#include<bits/stdc++.h>
using namespace std;
void fun(double a[],double b[])
{
	for(int i=0;i<20;i++)
		cout<<(b[i]-a[i])/b[i]*100<<endl;
}
int main()
{
	double a[]={2.03,2.96,2.07,2.97,2.18,3.01,3.89,3.89,3.91,3.91,2.12,2.86,2.29,2.91,2.65,3.05,3.62,3.62,3.70,3.70};
	double b[]={4,4,6,4.1,8.1,6.1,5.2,4.3,6.3,6.3,4.3,4.2,6.4,4.6,8.7,6.9,6.1,5.4,7.5,7.8};
	fun(a,b);
	return 0;
}
