#include<iostream>
#include<vector>
#include <bits/stdc++.h>
#include<math.h>
#include<cstdio> 
#include<string>
#include<map>
#include<algorithm>
#include<memory.h>

using namespace std;

#define MAX_WIDTH 100
#define MAX_HEIGHT 100
#define MIN_WIDTH 1
#define MIN_HEIGHT 1

#define BIG_NUM 127


struct Vertex
{
  int * stat; //store the order
  int * stat2; // store the order to compute index
  int s_n; // pos of space
  int s_n_w; // pos w
  int s_n_h; //pos h
  int * adj; //store up/down/left/right stat index
};

typedef vector<Vertex> VertexVec;

typedef struct{
	VertexVec vexs; //vertex vector
  int start;
	int goal; //vertex number of the Graph
  int w;
  int h;
  int num;
  int target;
  int source;
} MGraph;


MGraph mg;

void print_v(Vertex& v){

  cout << "stat: [";
  int i;
  for(i=0; i< mg.num; i++)
    cout<<v.stat[i]<<" ";
  cout << "], s_n: " << v.s_n << ", ("<<v.s_n_w<<", "<<v.s_n_h<<"), adj: [";
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
    for (iter2=iter1+1;iter2-v.stat<mg.num;iter2++)
    {
      if ((*iter1 != s_n)&&(*iter2 != s_n)&&(*iter1 > *iter2)){
        count++;
      }
    }
    
  }
  
  //cout<<"is_same_odd -- count: "<<count<<", space_n: "<<space_n<<endl;
  //print_v(v);
  
  return (((count + v.s_n) % 2) == ((mg.w+mg.h)%2));
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
  
  cout<<"(r: "<< v2.s_n_h <<", c: "<<v2.s_n_w<<"), val: "<< v1.stat[v2.s_n]<<endl;

}


//save the input file to a Graph
//initial other parameters of the Graph
//return -1 when the format of the input file is illegal
int GetInputAndInitGraph()
{
  // -- get input
	int width, height, i, j;
  Vertex tmp_target, v;

	cin>>width;
	cin>>height;
	
	if((width<MIN_WIDTH)||(width>MAX_WIDTH)||(height<MIN_HEIGHT)||(height>MAX_HEIGHT))
  {
    cout << "width or height is wrong!" <<endl;
    return -1 ;
  }

  mg.w = width;
  mg.h = height;
	mg.num = width * height;

  
  tmp_target.stat = new int[mg.num];
  memset(tmp_target.stat, 0, 4 * mg.num);
  v.stat = new int[mg.num];
  memset(v.stat, 0, 4 * mg.num);
  
  for(i=0; i< mg.num; i++){
    cin>>tmp_target.stat[i];
    v.stat[i] = i;
  }
  
  //tmp_target.stat[mg.num-1] = mg.num-1;
  //v.stat[mg.num-1] = mg.num-1;
    
  cout<<"width: " << width<<", height: "<<height <<endl;
  
  // -- check if there is a solution
	if(!is_same_odd(tmp_target))
  {
    cout << "No solution!" <<endl;
    return -2 ;
  }

  // -- generate stat list
  do  
  {   
    Vertex v1;
    
    v1.stat = new int[mg.num];
    v1.stat2 = new int[mg.num];
    v1.adj = new int[4];
        
    memcpy(v1.stat, v.stat, mg.num * 4);
    memcpy(v1.stat2, v.stat, mg.num * 4);
    
    for (i=0;i<mg.num;i++){
      
      if (v1.stat[i] == mg.num -1) v1.s_n = i;
      
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
    
    mg.vexs.push_back(v1);
    
  }while(next_permutation(v.stat,v.stat + mg.num));
 
 
  mg.start = 0;
  mg.goal = compute_index(tmp_target.stat);

  print_v(mg.vexs[mg.goal]);
  cout<<"start: " << mg.start <<endl;
  cout<<"goal: " << mg.goal <<endl;

  cout<<"vexs: " << mg.vexs.size() <<endl;
  //print_vv(mg.vexs);
  
  for(i=0;i<mg.vexs.size();i++)
  {
    // adj up
    if (mg.vexs[i].s_n_h > 0)
    {
      j = (mg.vexs[i].s_n_h - 1) * mg.w + mg.vexs[i].s_n_w;
      memcpy(v.stat, mg.vexs[i].stat, mg.num * 4); 
      v.stat[mg.vexs[i].s_n] = v.stat[j];
      v.stat[j] = mg.num - 1;
      mg.vexs[i].adj[0] = compute_index(v.stat);
    }
    else
    {
      mg.vexs[i].adj[0] = -1;
    }
    
    // adj down
    if (mg.vexs[i].s_n_h < mg.h -1)
    {
      j = (mg.vexs[i].s_n_h + 1) * mg.w + mg.vexs[i].s_n_w;
      memcpy(v.stat, mg.vexs[i].stat, mg.num * 4); 
      v.stat[mg.vexs[i].s_n] = v.stat[j];
      v.stat[j] = mg.num - 1; 
      mg.vexs[i].adj[1] = compute_index(v.stat);
    }
    else
    {
      mg.vexs[i].adj[1] = -1;
    }
    
    // adj left
    if (mg.vexs[i].s_n_w > 0)
    {
      j = mg.vexs[i].s_n_h * mg.w + mg.vexs[i].s_n_w - 1;
      memcpy(v.stat, mg.vexs[i].stat, mg.num * 4); 
      v.stat[mg.vexs[i].s_n] = v.stat[j];
      v.stat[j] = mg.num - 1;
      mg.vexs[i].adj[2] = compute_index(v.stat);
    }
    else
    {
      mg.vexs[i].adj[2] = -1;
    }
    
    // adj right
    if (mg.vexs[i].s_n_w < mg.w - 1)
    {
      j = mg.vexs[i].s_n_h * mg.w + mg.vexs[i].s_n_w + 1;
      memcpy(v.stat, mg.vexs[i].stat, mg.num * 4); 
      v.stat[mg.vexs[i].s_n] = v.stat[j];
      v.stat[j] = mg.num - 1;
      mg.vexs[i].adj[3] = compute_index(v.stat);
    }
    else
    {
      mg.vexs[i].adj[3] = -1;
    }
        
  }
  
  cout<<"Get adj completed!"<<endl;
  
	return 0;
}


int get_arc_dis(int v, int w)
{
  if ((mg.vexs[v].adj[0] == w)
    || (mg.vexs[v].adj[1] == w)
    || (mg.vexs[v].adj[2] == w)
    || (mg.vexs[v].adj[3] == w))
    {
      return 1;
    }
    
    return BIG_NUM;
}

//to save the shortest path length between any 2 vertex


bool ShortestPath_DIJ(vector<int> &D, vector<vector<int> >& paths)
{
	//using Dijkstra algorithm to calculate the shortest path D[v] between v0 and v in the network named mg 
	//if final_short[v] is true, there is a shortest path between v0 and v.
	int v0 = mg.start;
	if((v0<0)||(v0>=mg.vexs.size())){
    cout<<"mg szie wrong!"<<endl;
    return false;
  }

	D.clear();

	vector<bool> final_short;

	for(int v = 0; v < mg.vexs.size(); ++v)
	{
		final_short.push_back(false); 
		//D[v] = mg.arcs[v0][v];
    
		D.push_back(get_arc_dis(v0, v));
    vector<int> apath;
    apath.push_back(v0);
    apath.push_back(v);
    paths.push_back(apath);
	}//for 

  final_short[v0] = true; // initial 

  cout<<"ShortestPath_DIJ:"<<endl;
	//main loop, to calculate the shortest path between v0 and v each time
	for(int i = 0; i< mg.vexs.size(); ++i)
	{
    //cout<<"i: "<<i<<", "<< float(i)/float(mg.vexs.size())*100<<"%"<<endl;
    //print_v(D);
		if(i==v0) continue;

		int min = BIG_NUM;
		int v = v0;

		for(int w = 0; w < mg.vexs.size(); ++w)
		{
			if(!final_short[w])
			{
				if(D[w] < min)
				{
					v =w;
					min = D[w];
				}
			}
		}

		if(v==v0)
    {
      cout<<"no path between v and v0";
      return true; //no path between v and v0;
    }

		final_short[v] = true;

		//update current distance of shortest path
		for(int w = 0; w < mg.vexs.size(); ++w)
		{
      int dis = get_arc_dis(v, w);
			if(!final_short[w] && (min + dis < D[w]))
      {
        D[w] = min + dis;
        paths[w].assign(paths[v].begin(), paths[v].end());
        paths[w].push_back(w);
      }
      
		}//for
	}

	return true;
}//ShortestPath_DIJ


class Orienteering {
public:
	void main();
};

void Orienteering::main() {
	// TODO: Implement this function

	int checknum = 0;

	//save input file to a Graph
	if(GetInputAndInitGraph()) return;

  vector<int> D;
  vector<vector<int> > P;
	ShortestPath_DIJ(D, P);
  
  cout << "v: "<< mg.goal<<endl;
  cout << "D[v]: "<<D[mg.goal]<<endl;  
  cout <<"path: ";
  
  int i;
  for(i=0;i<P[mg.goal].size();i++)
    cout<<P[mg.goal][i]<<" ";
  cout<<endl;

  for(i=P[mg.goal].size()-1;i>=0;i--)
  {
     print_v(mg.vexs[P[mg.goal][i]]);
  }
  
  for(i=P[mg.goal].size()-2;i>=0;i--)
  {
     print_position(mg.vexs[P[mg.goal][i+1]], mg.vexs[P[mg.goal][i]]);
  }
  

}


int main(int argc, char* argv[]) {
	Orienteering o;
	o.main();
	return 0;
}
