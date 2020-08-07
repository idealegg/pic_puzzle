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
	
  cout<<"width: " << iw<<", height: "<<ih <<endl;
  
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
    cout<<"i: "<<i<<", val: " << input[i]<<endl;
    tmp_start.stat[i] = input[i];
    v.stat[i] = i;
  }
  
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
  
  delete []v.stat;
  
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

struct open_vertex {
  Vertex * v;
  bool operator <(const open_vertex & v1) const
  {
    if(v->f == v1.v->f)
    {
      if(v->g != v1.v->g)
        return v->g < v1.v->g;
      else
        return v->i < v1.v->i;
    }
    else {
      return v->f < v1.v->f;
    }

  }

  /*bool operator ==(const open_vertex & v1) const
  {
    return v->i == v1.v->i;
  }

  bool operator !=(const open_vertex & v1) const
  {
    return v->i != v1.v->i;
  }*/

};

class Astar
{
  int mean_steps;

  set<open_vertex> open_list;
  set<int> close_index;
  vector<open_vertex> close_list;
  vector<Vertex> result;
  
  int first;

  open_vertex cn; // current node
  open_vertex gn; // target node

  void c_h(Vertex& v){
      //v.h = (mg.num - v.h) * mean_steps;
    v.h = 0;
    for(int i=0;i<mg.num;i++)
    {
      v.h += (abs(v.stat[i]/mg.w - i/mg.w) + abs(v.stat[i]%mg.h - i%mg.h)) * 1;
    }
    //v.h = abs(v.i - mg.goal);
  }

  void insert2open_list(Vertex& v)
  {
    //cout<<"insert2open_list: ";
    //print_v(v);
    if(close_index.count(v.i)){
      //cout<<"There is a element in close list!"<<endl;
      return;
    }

    open_vertex tn = {&v};
    if (open_list.count(tn))
    {
      if(tn.v->g <= cn.v->g + 1)
      {
        //cout<<"There is a element in open list!"<<endl;
        return;
      }
      v.father = cn.v->i;
      v.g = cn.v->g + 1;
      v.f = tn.v->g + tn.v->h;
      //cout<<"Update open list!"<<endl;
      return;
    }

    tn.v->father = cn.v->i;
    tn.v->g = cn.v->g + 1;
    tn.v->f = tn.v->g + tn.v->h;
    open_list.insert(tn);
  }

  void get_next_cn()
  {
    /*print_open_list();
    print_close_list();
    print_close_index();*/

    if (open_list.size())
    {
      cn = *(open_list.begin());
      open_list.erase(open_list.begin());
      close_list.push_back(cn);
      close_index.insert(cn.v->i);
    }
  }

  void print_open_list()
  {
    set<open_vertex>::iterator iter;
    cout<<"open list:"<<endl;
    for(iter = open_list.begin(); iter!=open_list.end();iter++)
    {
      print_v(*(iter->v));
    }
  }

  void print_close_list()
  {
    vector<open_vertex>::iterator iter;
    cout<<"close list:"<<endl;
    for(iter = close_list.begin(); iter!=close_list.end();iter++)
    {
      print_v(*(iter->v));
    }
  }

  void print_close_index()
  {
    set<int>::iterator iter;
    cout<<"close index:"<<endl;
    for(iter = close_index.begin(); iter!=close_index.end();iter++)
    {
      cout<<*iter<<" ";
    }
    cout<<endl;
  }
  
  void release_v()
  {
    for(int i=0;i<mg.vexs.size();i++)
    {
      if(mg.vexs[i].stat)
      {
        delete []mg.vexs[i].stat;
        mg.vexs[i].stat = NULL;
      }
      
      if(mg.vexs[i].stat2)
      {
        delete []mg.vexs[i].stat2;
        mg.vexs[i].stat2 = NULL;
      }
      
      if(mg.vexs[i].adj)
      {
        delete []mg.vexs[i].adj;
        mg.vexs[i].adj = NULL;
      }
    }
  }
  

public:

  Astar(int ms):mean_steps(ms){}
  
  ~Astar()
  {
    release_v();
    //release_c_result;
  }
  
  void run()
  {
    for(int i=0;i<mg.vexs.size();i++)
    {
      c_h(mg.vexs[i]);
      mg.vexs[i].g = mg.num * mean_steps;
      mg.vexs[i].f = mg.vexs[i].g + mg.vexs[i].h;
      mg.vexs[i].father = -1;
    }

    cn.v = &mg.vexs[mg.start];
    gn.v = &mg.vexs[mg.goal];
    cn.v->g = 0;
    cn.v->f = cn.v->g + cn.v->h;
    close_list.push_back(cn);
    close_index.insert(cn.v->i);

    first = 1;
    while(!open_list.count(gn))
    {
      get_next_cn();
      for(int i=0; i<4;i++)
      {
        if(cn.v->adj[i] != -1) insert2open_list(mg.vexs[cn.v->adj[i]]);
      }
    }

    //close_list.push_back(gn);
    //close_index.insert(gn.v->i);

    Vertex v2 = *gn.v;
    result.push_back(v2);
    while(v2.father != -1)
    {
      v2 = mg.vexs[v2.father];
      result.push_back(v2);
    }

    cout << "v: "<< mg.start<<endl;
    cout << "dis: "<<result.size()-1<<endl;
    cout <<"path: "<<endl;

    for(int i=result.size()-1;i>=0;i--)
    {
      print_v(result[i]);
    }

    for(int i=result.size()-2;i>=0;i--)
    {
      print_position(result[i+1], result[i]);
    }

  }
  
  compute_result convert_result()
  {
    compute_result c_result;
    c_result.num = 0;
    
    c_result.data = new int[result.size()-1];
    
    for(int i=result.size()-2;i>=0;i--)
    {
      c_result.data[result.size()-2 - i] = result[i].s_n;
      c_result.num++;
    }
    
    return c_result;
  }
  
};


EXTERNFCT void release_c_result(compute_result c)
{
  if(c.data)
  {
    delete []c.data;
  }
  
  c.data = NULL;
}
  
EXTERNFCT compute_result compute_steps(int w, int h, int * input) {
  cout<<"call compute_steps"<<endl;

	GetInputAndInitGraph(w, h, input);

  Astar ast(mg.num);
  ast.run();
  
  return ast.convert_result();
}


/*int main(int argc, char* argv[])
{
	int* input = new int[argc-3];
	int w, h, j;
	
	sscanf(argv[1], "%d", &w);
	sscanf(argv[2], "%d", &h);
	
	for(j=3;j<argc;j++)
	{
		sscanf(argv[j], "%d", &input[j-3]);
	}
	
	compute_result cr = compute_steps(w, h, input);
	
	FILE * fd = fopen("compute_result", "w");
	string s;
	if(fd)
	{
		for(j=0;j<cr.num;j++)
		{
			fprintf(fd, "%d ", cr.data[j]);
		}
		
		fclose(fd);
	}
	else
	{
		return 1;
	}
	
	return 0;
}*/
