#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <bitset>

#define MAXN 25
using namespace std;

bool DP[(1<<MAXN)+1],P[MAXN];
int A[MAXN],B[MAXN];
int a,b,ans=MAXN;

string n;

string matriz;
void mb(int mask){
  for (int i=0;i<mask;i++){
    bitset<25> bs(i);
    string st=bs.to_string<char,string::traits_type,string::allocator_type>();
    reverse(st.begin(),st.end());
    memset(A,0,sizeof(A));
    memset(B,0,sizeof(B));
    for (int i=0;i<a*b;i++){
      if (st[i]=='1'){
        B[i%b]++;
        A[i/b]++;
      }
    }
    bool paso=1;
    for (int i=1;i<a;i++){
      if (A[i]!=A[i-1])
        paso=0;
    }
    for (int i=1;i<b;i++){
      if (B[i]!=B[i-1])
        paso=0;
    }
    if (paso){
      int aux=0;
      for (int i=0;i<n.size();i++){
        if (n[i]!=st[i]){
          aux++;
        }
      }
      if (aux<ans){
        matriz=st;
      }
      ans=min(ans,aux);
    }
  }
}

int main (){
  cin >> a >> b;
  for (int i=0;i<a;i++){
    for (int j=0;j<b;j++){
      char aux;
      cin >> aux;
      n.push_back(aux);
    }
  }
  mb((1<<(a*b)));
  cout << ans << endl;
  cout << matriz << endl;
  return 0;
}
