#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int n, m, s, t;
vector <int> adj[1001];
int parent[1001];
bool visited[1001];
void dfs(int u){
	visited[u]=true;
	for(int i: adj[u])
	{
		if(!visited[i]){
			parent[i]=u;
			dfs(i);
		}
	}
}
void dbs(int u){
	queue <int> q;
	q.push(u);
	visited[u]=true;
	while(!q.empty()){
		int v =q.front(); q.pop();
		for(int x: adj[v]){
			if(!visited[x]){
				q.push(x);
				visited[x]=true;
			}
		}
	}
}
void path(int s, int t){
	memset(parent,0,sizeof(parent));
	memset(visited,0,sizeof(visited));
	cin>>s>>t;
	dfs(s);
	if(!visited[t]){
		cout<<"khong co duong di toi dinh: "<<t<<endl;
	}
	else{
		vector <int> path;
		while(t!=s){
			path.push_back(t);
			t=parent[t];
		}
		path.push_back(s);
		reverse(path.begin(),path.end());
		for(int x: path){
			cout<<x<<" ";
		}
	}
}
// 10 8
// 1 2
// 2 3
// 2 4
// 3 6
// 3 7
// 6 7
// 5 8
// 8 9
int main(){
	cin>>n>>m;
	for(int i=0;i<m;++i){
		int x, y; cin>>x>>y;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	cin>>s>>t;
	path(s,t);
}