#include "pic_puzzle.h"

void print_v(Vertex& v){

  cout << "i: "<<v.i<<", stat: [";
  int i;
  for(i=0; i< mg.num; i++)
    cout<<v.stat[i]<<" ";
  cout << "], s_n: " << v.s_n << ", ("<<v.s_n_w<<", "<<v.s_n_h<<"), ghf: ("<<v.g<<", "<<v.h<<", "<<v.f<<"), adj: [";
  for(i=0; i< 4; i++)
    cout<<v.adj[i]<<" ";
  cout<<"]"<<endl;
}

void print_vv(vector<Vertex >& vv){
  for (int i=0;i<vv.size();i++){
    print_v(vv[i]);
  }
  cout<<endl;
}


bool is_same_odd(Vertex& v)
{
  int count = 0;
  int space_n = -1;
  int s_n = mg.num-1;
  int tmp = 0;
  int * iter1, *iter2;
  
  for (iter1=v.stat;iter1-v.stat<mg.num;iter1++, ++tmp)
  {
    if (*iter1 == s_n)
    {
      space_n = tmp;
      continue;
    }

    for (iter2=iter1+1;iter2-v.stat<mg.num;iter2++)
    {
      if ((*iter2 != s_n)&&(*iter1 > *iter2)){
        count++;
      }
    }
    
  }
  
  //cout<<"is_same_odd -- count: "<<count<<", space_n: "<<space_n<<endl;
  //print_v(v);

  if(mg.w%2)
    return (count % 2 == 0);
  else
    return (((count + space_n/mg.w) % 2) == ((mg.h-1)%2));
}

int get_factor(int n)
{
  int r = 1;
  for (int i=2; i<=n;i++)
  {
    r*=i;
  }
  
  return r;
}


int compute_index(int* stat)
{
  int pos=0;
  int i,j;
  static int* factor = NULL;
  static int* stat2 = NULL;
  if(!factor)
  {
    factor = new int[mg.num];
    factor[0] = 1;
    for(int i=1;i<mg.num;i++)
    {
      factor[i] = factor[i-1] *i;
    }
  }  

  if(!stat2)
  {
    stat2 = new int[mg.num];
  }    
  
  memcpy(stat2, stat, mg.num * 4);
  
  for (i=0;i<mg.num;i++)
  {
    //cout << "i: " << int(s[i])<<", factor: "<<factor<<", pos: "<<pos<<endl;
    //cout << "s: " << s <<endl;
    pos += stat2[i] * factor[mg.num-i-1];
    
    for (j=i+1;j<mg.num;j++)
    {
      if (stat2[j] > stat2[i]){
        stat2[j] = stat2[j] - 1;
      }
    }
      
  }   

  return pos;  
  
}

void print_position(Vertex& v1, Vertex& v2)
{
  
  cout<<"(i: "<<v2.s_n<<", r: "<< v2.s_n_h <<", c: "<<v2.s_n_w<<"), val: "<< v1.stat[v2.s_n]<<endl;

}


//save the input file to a Graph
//initial other parameters of the Graph
//return -1 when the format of the input file is illegal
int GetInputAndInitGraph(int iw, int ih, int* input)
{
  // -- get input
	int i, j, k;
  Vertex tmp_start, v;
	
	if((iw<MIN_WIDTH)||(iw>MAX_WIDTH)||(ih<MIN_HEIGHT)||(ih>MAX_HEIGHT))
  {
    cout << "width or height is wrong!" <<endl;
    return -1 ;
  }

  mg.w = iw;
  mg.h = ih;
	mg.num = iw * ih;

  
  tmp_start.stat = new int[mg.num];
  memset(tmp_start.stat, 0, 4 * mg.num);
  v.stat = new int[mg.num];
  memset(v.stat, 0, 4 * mg.num);
  
  for(i=0; i< mg.num; i++){
    tmp_start.stat[i] = input[i];
    v.stat[i] = i;
  }
  
  //tmp_start.stat[mg.num-1] = mg.num-1;
  //v.stat[mg.num-1] = mg.num-1;
    
  cout<<"width: " << iw<<", height: "<<ih <<endl;
  
  // -- check if there is a solution
	if(!is_same_odd(tmp_start))
  {
    cout << "No solution!" <<endl;
    return -2 ;
  }

  // -- generate stat list
  k = 0;

  do  
  {   
    Vertex v1;
    
    v1.stat = new int[mg.num];
    v1.stat2 = new int[mg.num];
    v1.adj = new int[4];
        
    memcpy(v1.stat, v.stat, mg.num * 4);
    memcpy(v1.stat2, v.stat, mg.num * 4);

    v1.h = 0;
    v1.i = k++;

    for (i=0;i<mg.num;i++){
      
      if (v1.stat[i] == mg.num -1) v1.s_n = i;
      if(v1.stat[i] == i) v1.h++;

      for (int j=i+1;j<mg.num;j++)
      {
        if (v1.stat2[j] > v1.stat2[i])
        {
          v1.stat2[j] = v1.stat2[j] - 1;
        }
      }
    }
    
    v1.s_n_w = v1.s_n % mg.w;
    v1.s_n_h = v1.s_n / mg.w;
    v1.father = -1;

    mg.vexs.push_back(v1);
    
  }while(next_permutation(v.stat,v.stat + mg.num));
 
 
  mg.start = compute_index(tmp_start.stat);
  delete []tmp_start.stat;
  
  mg.goal = 0;

  print_v(mg.vexs[mg.start]);
  cout<<"start: " << mg.start <<endl;
  cout<<"goal: " << mg.goal <<endl;

  cout<<"vexs: " << mg.vexs.size() <<endl;
  //print_vv(mg.vexs);
  
  for(i=0;i<mg.vexs.size();i++)
  {
		//cout<<i<<" "<<compute_index(mg.vexs[i].stat)<<endl;
		if (i!= compute_index(mg.vexs[i].stat)) cout<<"not equal: "<<i<<endl;
		}
  
  delete []v.stat;
  
  cout<<"Get adj completed!"<<endl;
  
	return 0;
}







  
int main()
{
	int input[9] ={6, 4, 3, 1, 2, 8, 7, 5, 0};
	GetInputAndInitGraph(3, 3, input);

}
