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
vector<int> findflow(vector< vector<int> > G, int &N, int n,int &min, set<int> Bn)
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
		if(G[N+1][c] > 0);


		//node = G.at(c);

		//go through nodes looking for max flow
		//for(i = 1; i < G[c].size() ;i++)
		for(i = 0; i < G[c].size() ;i++)
		{

			//if the node has flow check for max
			if(G[c][i] >0)
			{

				//if have hit bob
				if( i == 0)
				{
					printf("Have can hit the sink!!!!!!!!!!!!!!!!!!!\n");


				}

				printf("checking %d with dist %d\n",i, G[c][i]);
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
	AG.resize(N+2);
	BG.resize(N+2);

	G.at(0).resize(N+2,0);
	G.at(N+1).resize(N+2,0);
	AG.at(0).resize(N+2,0);
	AG.at(N+1).resize(N+2,0);
	BG.at(0).resize(N+2,0);
	BG.at(N+1).resize(N+2,0);



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
			printf("adding to alices set p:%d i:%d\n",p,i);
			A.push_back(i);
			An.insert(p);
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
			printf("adding to bobs set p % d i % d\n",p,i);
			B.push_back(i);
			Bn.insert(p);
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
			printf("adding to neutral set\n");
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

	printf("\n\n");

	for(i = 0; i < pitch.size();i++)
	{
		int nm = pitch.at(i);
		printf("%d ",nm); 
	}

	printf("\n\n");
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
				//An.insert(ad);
				AG.at(nm2).at(ad2)++;
				//AG.at(ad).at(nm)++;
			}
		}
		else if(nm == 0) 
		{
			if(ad != 0 && ad != N+1)  
			{
				//Bn.insert(ad);
				BG.at(nm2).at(ad2)++;
			}

		}

		G.at(nm).at(ad)++;
//		G.at(nm2).at(ad)++;
		G.at(ad).at(nm)++;

	}


	printf("\n\n\n");

	//An.insert(N+1);
	//Bn.insert(0);

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

	set<int> aa, bb;

	for( i = 0; i < G.size(); i++)
	{
		if(G.at(i).size() > 0)
		{
			printf("NODE %d:\n",i);

			for(j = 0; j < G.at(i).size();j++)
			{
				if(G.at(i).at(j) > 0)
				{
					if(i == 0) bb.insert(j);
					else if(i == N+1) aa.insert(j);
					R.at(i).at(j) *= -1;
					printf("G:%d--(%d)-->%d\n",i, G.at(i).at(j), j);
					printf("R:%d--(%d)-->%d\n",i, R.at(i).at(j), j);
				}
			}
		}
	}

	orig = G;

	printf("Alice nodes ...\n");
	for( sit = aa.begin() ; sit != aa.end();sit++)
	{
		printf("------A: %d\n",(*sit));
	}
		
	printf("Bobs nodes ...\n");
	for( sit = bb.begin() ; sit != bb.end();sit++)
	{
		printf("B: %d\n",(*sit));
	}

	printf("\n\n\n");


	vector<int> rpath;

	int to, from, min = 256, cut = 0, max = -256, nxt = 0, nd;
	rpath.clear();

	found = 1;

	set<int> visited;

	int cnt = 0;

	printf("trying to find %d\n",N+1);
	sit = bb.find(N+1);

	if( sit != bb.end())
	{
		cut += G[0][N+1];

		printf("-------cutting sink from source adding %d to cut\n",G[0][N+1]);

		G[0][N+1] = 0;
		G[N+1][0] = 0;
		orig[0][N+1] = 0;
	}
	else printf("Not Found\n");

		//for(sit = bb.begin();sit != bb.end();sit++)
		//for(sit = Bn.begin();sit != Bn.end();sit++)
	for(int nde = 0; nde < G[0].size(); nde++)
	{
		//nxt = (*sit);


	
		
		if( G[0][nde]  > 0 && nde != 0)
		{
			printf("next is %d\n",nde);

			found = 1;

			nxt = nde;

			while(found)
			{
				found = 0;

				max = -256;

				visited.insert(nxt);

				printf("---------------NODE is %d\n\n",nxt);

				//find max flow
				for(i = 0; i < G[nxt].size(); i++)
				{
					//printf("Checking node %d's entry %d\n", nxt, i);

					if(visited.find(i) == visited.end() && i != nxt && G[nxt][i] > 0 && i != 0)
					{
						printf("found flow\n");
						found = 1;

						if( i == N+1)
						{
							max = G[nxt][i];
							nd = i;
							break;	
						}
						else if(G[nxt][i] > max)
						{
							max = G[nxt][i];
							nd = i;
						}
					}

				}


				if(found)
				{
					printf("Max flow %d found with node %d from %d\n",max,nd,nxt);

					if( min > max)
					{
						min = max;
					}

					rpath.push_back(nxt);
					rpath.push_back(nd);

					if(nd == N+1)
					{
						printf("HIT the sink alice from node %d\n", nxt);

						int set = 0;
						while(rpath.size() > 0)
						{
							to = rpath.back();
							rpath.pop_back();

							from = rpath.back();
							rpath.pop_back();

							printf("from node %d to node %d dist: %d\n", from, to, G[from][to]);

							G[from][to] -= min;

							if(set == 0 && G[from][to] == 0)
							{
								printf("i---------found a cut of %d setting set\n",orig[from][to]);

								cut += orig[from][to];
								set = 1;
							}

							printf("Dist. is NOW %d\n",G[from][to]);
						}

						//start over
						found = 0;
						min = 256;
						visited.clear();

					}
					else
					{
						nxt = nd;
					}

					printf("\n\n\n");

				}
				else printf("found no flow!!!!!!\n\n\n");

				cnt++;
				//		if(cnt > 3) exit(0);

			}
		}
	}

	/*
	//go through a's nodes looking for flow
	for(i = 0; i < G[0].size() ;i++)
	//for(sit = Bn.begin(); sit != Bn.end();sit++)
	{

	//	int nnm = (*sit);

	int nnm = G[0][i]	

	if(nnm > 0)
	{
	printf("tryng to flow from node %d\n",nnm);

	found = 1;

	//exit(0);
	while(found)
	{  
	found = 0;

	printf("Checking node %d\n",nnm);

	//check this node for flow
	for(i = 0; i < G[nnm].size();i++)
	{
	//if you find flow check for the max

	if(G[nnm][i] > 0 && i != 0)
	{
	found = 1;
	printf("flow to node %d at weight %d\n",i,G[nnm][i]);

	if( G[nnm][i] > max) 
	{
	max = G[nnm][i];
	nxt = i;
	printf("MAX is now %d\n",G[nnm][i]);
	}
	}
	}


	if(found == 1)
	{
	printf("the max flow out of node %d is %d to node %d\n",nnm, max,nxt);

	if(max < min)
	{
	min = max;
	}

	rpath.push_back(nnm);
	rpath.push_back(nxt);

	//if i am part of allices set
	//return;
	if(An.find(nxt) != An.end())
	{
	found = 0;

	while(rpath.size() > 0)
	{
	to = rpath.back();
	rpath.pop_back();

	from = rpath.back();
	rpath.pop_back();

	//sub min from path
	printf("G from %d to %d is %d\n", from , to, G[from][to]);
	G[from][to] -= min;
	printf("NOW G from %d to %d is %d\n", from , to, G[from][to]);

	if(G[from][to] == 0)
	{
		cut += orig[from][to];
	}
}
}
else 
{
	nnm = nxt;
}
}
else printf("no flow found\n");

}
}
}
*/
printf("MIN CUT %d\n",cut);

printf("\n");
exit(0);
}
