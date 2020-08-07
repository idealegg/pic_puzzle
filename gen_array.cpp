#include<iostream>
#include<cstdio> 
#include<string>
#include<vector>
#include<algorithm>
#include<memory.h>
using namespace std;


int get_factor(int n)
{
  int r = 1;
  for (int i=2; i<=n;i++)
  {
    r*=i;
  }
  
  return r;
}

int compute_index(string s, int num)
{
  int pos=0;
  static int* factor = NULL;
  if(!factor)
  {
    factor = new int[num];
    factor[0] = 1;
    for(int i=1;i<num;i++)
    {
      factor[i] = factor[i-1] *i;
    }
  }    
  
  for (int i=0;i<num;i++)
  {
    //cout << "i: " << int(s[i])<<", factor: "<<factor<<", pos: "<<pos<<endl;
    //cout << "s: " << s <<endl;
    pos += (s[i]-'0') * factor[num-i-1];
    
    for (int j=i+1;j<num;j++)
    {
      if (s[j] > s[i]){
        s[j] = s[j] - 1;
      }
    }
    
  }   

  return pos;  
  
}

int main()
{
      string v("0123");
      string v3("0123");
      string v4("01234");
      vector<int> v1(4, 1);
      vector<int> v2(5,1);
      int v5[4]= {0, 1, 2, 3};
      
      /*if(v==v3){ cout<<"v, v3 equal!"<<endl;}
      if(v==v4){ cout<<"v, v4 equal!"<<endl;}
      if(v1==v2){ cout<<"v1, v2 equal!"<<endl;}*/
      
      int i =0;
      
      do  
      {   
        //cout <<i++<<": "<< v5[0] <<" "<< v5[1]<<" "<< v5[2] <<" "<< v5[3]<<endl;
      
      // }while(next_permutation(v5,v5+4));
      
        cout <<i++<<": "<<  v <<endl;
} while(next_permutation(v.begin(), v.end()));
      
      /*vector<int*> abc;
      int i1[4] = {1,2,3,4};
      abc.push_back(i1);*/
      cout << "hd"<<endl;
      cout << compute_index(string("0321"), 4) <<": 0321"<<endl;
      
      int * a = new int[4];
      memset(a, 0, 4 * 4);
      cout << "a[3]: "<<a[3]<<endl;
      return 0;
}