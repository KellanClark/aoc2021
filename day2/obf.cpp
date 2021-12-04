#include <iostream>
#include <fstream>
#include <string>
using namespace std;int main(){fstream i("../day2/input",ios_base::in);int h,d,e,n;h=d=e=n=0;string s;while(i>>s){i>>n;if(s[0]=='f'){h+=n;e+=d*n;}d+=s[0]=='d'?n:0;d-=s[0]=='u'?n:0;}cout<<h*d<<'\n'<<h*e<<'\n';}