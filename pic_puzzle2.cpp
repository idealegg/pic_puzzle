#include<iostream>
#include<vector>
#include <bits/stdc++.h>
#include<math.h>
#include<cstdio> 
#include<string>
#include<map>
#include<algorithm>

using namespace std;

#define MAX_WIDTH 100
#define MAX_HEIGHT 100
#define MIN_WIDTH 1
#define MIN_HEIGHT 1

#define BIG_NUM 127


typedef vector<string>  AdjMatrix;
typedef vector<string>  VertexVec;

typedef struct{
	VertexVec vexs; //vertex vector
	AdjMatrix arcs; //adjacency matrix
  int start;
	int goal; //vertex number of the Graph
  int width;
  int height;
  bool found_target;
  bool found_source;
  string target;
  string source;
} MGraph;

MGraph mg;

bool is_same_vector(string& v1, string& v2)
{
  string::iterator    iter1, iter2;
  for (iter1=v1.begin(), iter2=v2.begin();(iter1!=v1.end())&&(iter2!=v2.end());iter1++, iter2++){
    if (*iter1 != *iter2) return false;
  }
  return true;
}


void print_v(string& v){

  for(int i=0; i< v.length(); i++)
    cout<<int(v[i])<<" ";
  cout<<endl;
}

void print_vv(vector<string >& vv){
  for (int i=0;i<vv.size();i++){
    print_v(vv[i]);
  }
  cout<<endl;
}


bool is_same_odd(string& v, int w, int h)
{
  string::iterator    iter1, iter2;
  int count = 0;
  int space_n = -1;
  char s_n = w*h-1;
  int tmp = 0;
  
  for (iter1=v.begin();iter1!=v.end();iter1++, ++tmp)
  {
    if (*iter1 == w*h-1) space_n = tmp/w + tmp%w;
    for (iter2=iter1+1;iter2!=v.end();iter2++)
    {
      if ((*iter1 != s_n)&&(*iter2 != s_n)&&(*iter1 > *iter2)){
        count++;
      }
    }
    
  }
  
  //cout<<"is_same_odd -- count: "<<count<<", space_n: "<<space_n<<endl;
  //print_v(v);
  
  return (((count + space_n) % 2) == ((w+h)%2));
}


bool is_adjacent(string& v1, string& v2, int w, int h)
{
  string::iterator    iter1, iter2;
  int tmp=0;
  char s_n = h*w-1;
  char another = -1;
  bool first = true;
  vector<int> diff;
  int c=0;
  
  //cout<<"is_adjacent -- s_n: "<<s_n<<endl;
  //print_v(v1);
  //print_v(v2);
  
  for (iter1=v1.begin(), iter2=v2.begin();(iter1!=v1.end())&&(iter2!=v2.end());iter1++, iter2++, c++)
  {
    if (*iter1 != *iter2){
      //cout<<"*iter1: "<<*iter1<<", *iter2: "<<*iter2<<endl;
      //cout<<"first: "<<first<<", tmp: "<<tmp<<", another: "<<another<<endl;
      if ((*iter1 != s_n)&&(*iter2 != s_n)) return false;
      if (!first && (*iter1 != another)&&(*iter2 != another)) return false;
      if (tmp >= 2) return false;
      if (*iter1 != s_n)
      {
        another = *iter1;
      }
      else 
      {
        another = *iter2;
      }
      diff.push_back(c);
      tmp += 1;
      first = false;
    }
  }
  
  bool result = (((abs(diff[0]/w - diff[1]/w) == 1)&&(diff[0]%w == diff[1]%w))||((abs(diff[0]%w - diff[1]%w) == 1)&&(diff[0]/w == diff[1]/w)));

  return result;

}

void print_position(string& v1, string& v2, int w, int h)
{
  string::iterator    iter1, iter2;
  char s_n = h*w-1;
  char another = -1;
  int c=0;
  
  for (iter1=v1.begin(), iter2=v2.begin();(iter1!=v1.end())&&(iter2!=v2.end());iter1++, iter2++, c++)
  {
    if (*iter1 != *iter2){
      if (*iter1 != s_n)
      {
        another = *iter1;
      }
      else 
      {
        another = *iter2;
      }
      break;
    }
  }
  
  cout<<"r: "<< c/w +1 <<", c: "<<c%w+1<<", val: "<< static_cast<int>(another)<<endl;

}

//save the input file to a Graph
//initial other parameters of the Graph
//return -1 when the format of the input file is illegal
int GetInputAndInitGraph(MGraph &mg)
{
	int width, height;

	cin>>width;
	cin>>height;
	
	if((width<MIN_WIDTH)||(width>MAX_WIDTH)||(height<MIN_HEIGHT)||(height>MAX_HEIGHT))
  {
    cout << "width or height is wrong!" <<endl;
    return -1 ;
  }

	int num = width * height;
	int tmp=0;

  int i;
  
  for(i=0; i< num-1; i++){
    cin>>tmp;
    mg.source.append(1, static_cast<char>(i));
    mg.target.append(1, static_cast<char>(tmp));
  }
  
  mg.source.append(1, static_cast<char>(num-1));
  mg.target.append(1, static_cast<char>(num-1));
  
  mg.found_source = false;
  mg.found_target = false;
    
  cout<<"width: " << width<<", height: "<<height <<endl;
  
	if(!is_same_odd(mg.target, width, height))
  {
    cout << "No solution!" <<endl;
    return -2 ;
  }
  
  mg.width = width;
  mg.height = height;
  
  i=num;
  string v;
  //while(i--)
  {   
      v = mg.source;
      
      do  
      {   
        mg.vexs.push_back(v);
      
        if (!mg.found_target)
        {
          if (is_same_vector(v, mg.target))
          {
            mg.found_target = true;
            mg.goal = mg.vexs.size() -1;
          }
        }
        
        if (!mg.found_source)
        {
          if (is_same_vector(v, mg.source))
          {
            mg.found_source = true;
            mg.start = mg.vexs.size() -1;
          }
        }
      }while(next_permutation(v.begin(),v.end()));
  
  }   
    
  for(i = 0; i < mg.vexs.size(); ++i)
  {
    string aRow;
    int j;
    //for(j = 0; j < i; ++j)
    //  aRow.append(1, static_cast<char>(mg.arcs[j][i]));
    
    //aRow.append(1, static_cast<char>(0));
    //aRow.push_back(BIG_NUM);
    
    for(int j = i+1; j < mg.vexs.size(); ++j)
    {
      if(is_adjacent(mg.vexs[i], mg.vexs[j], width, height))
      {
        //if adjacent
        //mg.arcs[i][j] = 1;
        aRow.append(1, static_cast<char>(j));
        
        //cout<<"i: "<<i<<", j:"<<j<<endl;
      }
      //else
      //{
        //itself or not adjacent
      //  aRow.append(1, static_cast<char>(BIG_NUM));				
      //}
    }

    mg.arcs.push_back(aRow);
	}

  cout<<"source: " << mg.source.length() <<endl;
  print_v(mg.source);
  cout<<"target: " << mg.target.length() <<endl;
  print_v(mg.target);
  cout<<"start: " << mg.start <<endl;
  cout<<"goal: " << mg.goal <<endl;
  cout<<"vexs: " << mg.vexs.size() <<endl;
  //print_vv(mg.vexs);
  cout<<"arcs: " << mg.arcs.size() <<endl;
  //print_vv(mg.arcs);
  
	return 0;
}


int get_arc_dis(const MGraph& G, int v, int w)
{
  if (v==w) return BIG_NUM;
  int v0 = v;
  if(v>w){
    v0=w;
    w=v;
  }

  if (G.arcs[v0].find(static_cast<char>(w)) != string::npos) return 1;
  return BIG_NUM;
}

//to save the shortest path length between any 2 vertex


bool ShortestPath_DIJ(const MGraph& G, string &D, vector<string >& paths)
{
	//using Dijkstra algorithm to calculate the shortest path D[v] between v0 and v in the network named G 
	//if final_short[v] is true, there is a shortest path between v0 and v.
	int v0 = G.start;
	if((v0<0)||(v0>=G.vexs.size())){
    cout<<"G szie wrong!"<<endl;
    return false;
  }

	D.clear();

	vector<bool> final_short;

	for(int v = 0; v < G.vexs.size(); ++v)
	{
		final_short.push_back(false); 
		//D[v] = G.arcs[v0][v];
    
		D.append(1, static_cast<char>(get_arc_dis(G, v0, v)));
    string apath;
    apath.append(1, static_cast<char>(v0));
    apath.append(1, static_cast<char>(v));
    paths.push_back(apath);
	}//for 

  final_short[v0] = true; // initial 

  //cout<<"ShortestPath_DIJ:"<<endl;
	//main loop, to calculate the shortest path between v0 and v each time
	for(int i = 0; i< G.vexs.size(); ++i)
	{
    //cout<<"D:";
    //print_v(D);
		if(i==v0) continue;

		int min = BIG_NUM;
		int v = v0;

		for(int w = 0; w < G.vexs.size(); ++w)
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
      return true; //no path between v and v0;
    }

		final_short[v] = true;

		//update current distance of shortest path
		for(int w = 0; w < G.vexs.size(); ++w)
		{
      int dis = get_arc_dis(G, v, w);
			if(!final_short[w] && (min + dis < D[w]))
      {
        D[w] = min + dis;
        paths[w].assign(paths[v]);
        paths[w].append(1, static_cast<char>(w));
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
	if(GetInputAndInitGraph(mg)) return;

  string D;
  vector<string > P;
	ShortestPath_DIJ(mg, D, P);
  
  cout << "v: "<< mg.goal<<endl;
  cout << "D[v]: "<<D[mg.goal]<<endl;  
  cout <<"path: ";
  print_v(P[mg.goal]);

  for(int i=P[mg.goal].length()-1;i>=0;i--)
  {
     print_v(mg.vexs[P[mg.goal][i]]);
  }
  
  for(int i=P[mg.goal].length()-2;i>=0;i--)
  {
     print_position(mg.vexs[P[mg.goal][i+1]], mg.vexs[P[mg.goal][i]], mg.width, mg.height);
  }
  

}


int main(int argc, char* argv[]) {
	Orienteering o;
	o.main();
	return 0;
}
