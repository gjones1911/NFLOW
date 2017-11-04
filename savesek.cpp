#include <string>
#include <vector>
#include <list>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

int FindFLOW( vector <int> node, vector<int> path, int N, vector<vector<int> >&G, int nnm, int min)
{

	if(nnm == N+1) 
	{
		printf("I hit the sink \n");

		int last = nnm;

		for(int i = path.size()-1; i >= 0; i--)
		{
			int next = path.at(i);
			printf("Node: %d from %d",next,last);

			printf("dist at first %d min is %d\n",G.at(next).at(last),min);
			G.at(next).at(last) -= min;
			printf("dist is now %d\n",G.at(next).at(last));
			last = next;;
		}


		return nnm;
	}


	int max = -100;

	vector<int> n = node;

	//find biggest path with flow
	for(int i = 0; i < node.size();i++)
	{
		if(node.at(i) > max)
		{
			max = node.at(i);
		}
	}

	printf("max is %d\n",max);
}

int FLOW( vector<vector<int> >&G, vector<vector<int> >&R, vector<int> &path,int next, int N)
{	
	int found = 1;

	vector<int> A = G.at(0);
	vector<int> B = G.at(N+1);
	vector<int> node;


	while(!found)
	{

		found = 0;
		for(int i = 0; i < A.size();i++)
		{
			if( A.at(i) != 0)
			{
				found = 1;
				path.push_back(i);				//go to that node and find flow
				node = G.at(i);

				//FindFLOW(node,path);

			}
		}

	}

	return 0;

}

			//rpath = findflow(G,N,i,min);
vector<int> findflow(vector< vector<int> > G, int &N, int n,int &min)
{
	int i, j, k, nm, found = 1, nd, ans = 0;;


	min = 256; 
	int max = -256;

	//vector< vector<int> orig = G;	
	vector<int> node = G.at(n);
	vector<int> path;
	path.clear();

	path.push_back(n);

	int c = n;
	while(found)
	{
		found = 0;

		printf("checking node %d\n",c);

		//check if this node can hit the sink
		if(G[N=1][c] > 0);
		
		//node = G.at(c);

		//go through nodes looking for max flow
		for(i = 1; i < G[c].size() ;i++)
		{

			if( G[c][i] > 0)printf("checking %d with dist %d\n",i, G[c][i]);
			//if the node has flow check for max
			if(G[c][i] >0)
			{
				found = 1;
				if(max  < G[c][i])
				{
					max = G[c][i];
					nd = i;
					printf("mas is now %d at %d\n", max,nd);
				}
			}

		}

	
		printf("Max is now %d\n\n\n\n\n");


		//now if found a max use that path
		if(found)
		{
			path.push_back(nd);

			if(max < min)
			{
				min = max;
				printf("min is now %d\n\n\n\n", min);
			}

			//check for sink
			if( nd == N+1)
			{
				printf("hit the sink at node %d\n",nd);

				//exit(0);

				return path;
			}
			else
			{
				G[c][nd] *= -1; 
				c = nd;
				printf("going to node %d\n",nd);
			}
		}

		max = -256;
	

		printf("end of stuff\n\n\n\n\n\n\n");
	}

	printf("no flow found from %d\n\n",n);

	G[0][n] *= -1;

	path.clear();

	return path;

}
class Singing 
{
	public:
		int solve(int N, int low, int high, vector <int> pitch);
};


int Singing::solve(int N, int low, int high, vector <int> pitch)
{
	int i, p,j, found =1, Acnt = 0, Bcnt = 0;

    set<int> An;
    set<int>::iterator  sit;
	
	set<int> Bn;

	vector<int> A;
	vector<int> B;
	vector<int> l;
	vector<int> h;
	vector<int> left;
	vector<int> path;
	vector<int> graph;
	vector<vector<int> >G(N);
	vector<vector<int> >AG(N);
	vector<vector<int> >BG(N);
	vector<vector<int> >R(N);
	vector <vector<int> > orig;
	A.clear();
	B.clear();
	left.clear();
	graph.clear();
	path.clear();

	printf("Alice sings from %d to %d\n", low,N);
	printf("Bob sings from %d to %d\n", 1,high);
	printf("N is %d\n",N);
	printf("the pitches in the song are.......\n");

	G.resize(N+2);

	G.at(0).resize(N+2,0);
	G.at(N+1).resize(N+2,0);



	//go through pitch deciding who
	//can sing what
	for(i = 0; i < pitch.size();i++)
	{
		p = pitch.at(i);

		printf("Pitch:%d %d\n",i,p);

		//if( p >= high+1 && p <= N)
		//if the pitch is higher than high
		//it goes to alice
		if( p >= high+1 )
		{
			A.push_back(i);
			graph.push_back(N+1);
			//G.at(p).resize(0);
			G.at(p).resize(N+2,0);
			AG.at(p).resize(N+2,0);
			Acnt++;
		}
		//else if(p >= 1 && p < low)
		//if the pitch is lower than low it
		// goes to Bob
		else if( p < low)
		{
			B.push_back(i);
			graph.push_back(0);
			G.at(p).resize(N+2,0);
			BG.at(p).resize(N+2,0);
			//G.at(p).resize(0);
			Bcnt++;
		}
		//otherwise either or can sing it so put it
		//in the left over
		else
		{
			left.push_back(i);
			graph.push_back(p);
			G.at(p).resize(N+2,0);
		}

	}

	if(A.size() == 0 || B.size() == 0)
	{
		printf("Song can be sung by one person!!!!\n");
		return 0;
	}

	printf("Alice Sings pitches...\n");
	for(i = 0; i < A.size();i++)
	{
		printf("A %d\n",A.at(i));  
//		An.insert( pitch.at( A.at(i)) );
	}

	printf("Bob Sings pitches...\n");
	for(i = 0; i < B.size();i++)
	{
		printf("B %d\n",B.at(i));  
//		Bn.insert( pitch.at( B.at(i)) );
	}

	printf("leftofver pitches...\n");
	for(i = 0; i < left.size();i++)
	{
		printf("LEFT %d\n",left.at(i));  
	}

	printf("Graph...\n");

	for(i = 0; i < graph.size();i++)
	{
		int nm = graph.at(i);

		printf("%d ",nm); 

	}


	printf("graph size is %d\n",pitch.size());

	//for(i = 0; i < graph.size()-1;i++)
	for(i = 0; i < pitch.size()-1;i++)
	{
		int nm = graph.at(i);
		int ad = graph.at(i+1);
		
		int nm2 = pitch.at(i);
		int ad2 = pitch.at(i+1);

		printf("i:%d current %d ,next %d\n",i,nm,ad);  
		printf(" ");
		printf("i:%d Pcurrent %d ,Pnext %d\n",i,nm2,ad2);  
		printf(" ");

		if(nm == N+1) 
		{

			if(ad != 0 && ad != N+1) 
			{	
				An.insert(ad);
				AG.at(nm2).at(ad2)++;
				//AG.at(ad).at(nm)++;
			}
		}
		else if(nm == 0) 
		{
			if(ad != 0 && ad != N+1)  
			{
				Bn.insert(ad);
				BG.at(nm2).at(ad2)++;
			}

		}

		G.at(nm).at(ad)++;
		G.at(ad).at(nm)++;

	}


	printf("\n\n\n");

	printf("Alice is the only one that sings...\n");
	for( sit = An.begin() ; sit != An.end();sit++)
	{
		printf("A: %d\n",(*sit));
	}
		
	printf("Bob is the only one that sings...\n");
	for( sit = Bn.begin() ; sit != Bn.end();sit++)
	{
		printf("B: %d\n",(*sit));
	}

	printf("\n\n\n");




	R = G;

	printf(">>>>\n");

	for( i = 0; i < G.size(); i++)
	{
		if(G.at(i).size() > 0)
		{
			printf("NODE %d:\n",i);

			for(j = 0; j < G.at(i).size();j++)
			{
				if(G.at(i).at(j) > 0)
				{
					R.at(i).at(j) *= -1;
					printf("G:%d--(%d)-->%d\n",i, G.at(i).at(j), j);
					printf("R:%d--(%d)-->%d\n",i, R.at(i).at(j), j);
				}
			}
		}
	}

exit(0);
	orig = G;
/*

	for( i = 0; i < G.at(0).size();i++)
	{
		if(G.at(0).at(i) != 0)
		{
			printf("following node %d\n",i);

			for(j = 1; j < G.at(i).size();j++)
			{

				int nmb = G.at(i).at(j);

				if(G.at(i).at(j) != 0)
				{
					printf("Node %d can get to node %d by %d\n",i,j,G.at(i).at(j));
				}

				if( j == (N+1))
				{
					printf("Hit the sink from path....\n");
				}
			}

		}
	}
*/

	vector<int> rpath;

	int to, from, min, cut = 0;
	rpath.clear();

	found = 1;

	while(found)
	{
		found = 0;

		//go through a's nodes looking for flow
		for(i = 0; i < G[0].size() ;i++)
		{
			if(G[0][i] > 0)
			{
				printf("tryng to flow from node %d\n",i);

				//give it graph, N, node number i 
				rpath = findflow(G,N,i,min);
				//exit(0);

				if(rpath.size() > 0)
				{
					printf("found some flow\n\n");
					found = 1;

					while( rpath.size() > 0)
					{
						to = rpath.back();
						rpath.pop_back();
						
						from = rpath.back();
						rpath.pop_back();

						printf("the dist from %d to %d is %d\n",from, to , G[from][to]);

						G[from][to] -= min;
						
						printf("the dist from %d to %d is NOW %d\n",from, to , G[from][to]);

						if(G[from][to] == 0)
						{
							cut += orig[from][to];
						}
					}

				}
				else printf("no path found\n");
			}
		}
	}

	printf("MIN CUT %d\n",cut);

	printf("\n");
	exit(0);
}
