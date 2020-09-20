#include<bits/stdc++.h>
using namespace std;
void fun(double a[],double b[])
{
	for(int i=0;i<21;i++)
		cout<<(b[i]-a[i])/b[i]*100<<endl;
}
int main()
{
	double a[]={3,4.5,5.85,6.69,4,5.66,7.30,8.53,9.46,5,6.66,8.38,9.76,10.89,11.78,5,7.25,9.84,11.94,13.67,15.07};
	double b[]={5,5.3,6.4,7.5,7,7.5,8.7,10.3,11.8,8,9.6,11.1,12.6,14.3,15.8,9,10.8,12.3,13.9,15.1,18};
	fun(a,b);
	return 0;
}
