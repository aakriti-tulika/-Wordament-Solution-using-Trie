#include<iostream>
#include<fstream>
#include<bits/stdc++.h>
#include<cstdlib>
using namespace std;

char arr[5][5];
bool vis[5][5];
vector<string>all_string;
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};


bool ispresent (string);
struct Node{
    bool isEnd;
    Node* child[26];

    Node()
    {
        isEnd=false;
        for(int i=0;i<26;i++)
        child[i]=NULL;
        
    }
    bool containsKey(char ch)
    {
        return(child[ch-'a']!=NULL);
    }
    void put(char ch,Node *node)
    {
        child[ch-'a']=node;
    }
    Node* getNode(char ch)
    {
        return child[ch-'a'];
    }
    void set()
    {
        isEnd=true;
    }
    
};

class Trie{
    private:
    Node *root;

    public:
    Trie()
    {
        root=new Node();
    }
    ~Trie()
    {
        //clear(root);
    }
    public:
    friend  bool ispresent(string);
    Node* getRoot()
    {
        return root;
    }
    void insert(string key)
    {
        Node *node=root;
        for(int i=0;i<key.size();i++)
        {
            if(node->containsKey(key[i])==false)
            {
                node->put(key[i],new Node());
            }
            node=node->getNode(key[i]);
        }
        node->set();
    }
    public:
    bool findstring(string key)
    {
        Node *node=root;
        for(int i=0;i<key.size();i++)
        {
            if(node->containsKey(key[i])==false)
            {
                return false;
            }
            node=node->getNode(key[i]);
        }
        bool ans= (node->isEnd);
        node->isEnd=false;
        return ans;
    }
};

Trie trie;
void preprocessing()
{
    cout<<Processing....<<"\n";
    ifstream indata;
    string str;
    indata.open("words.txt");
    if(!indata)
    {
        cerr<<"ERROR:500 srry for inconvience\n";
        exit(1);
    }
    cout<<"WELCOME\nStarting the server\n";
    indata>>str;
    while(!indata.eof())
    {
        trie.insert(str);
        indata>>str;
    }
    indata.close();
    
}
bool isvalid(int i,int j)
{
   return (i>=0 && j>=0 && i<5 && j<5 && vis[i][j]==false); 
}
void readdata()
{
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        cin>>arr[i][j];
    }
}

void reset()
{
   for(int i=0;i<5;i++)
   {
       for(int j=0;j<5;j++)
       vis[i][j]=false;
   }
}
bool ispresent(string s)
{
    return trie.findstring(s);
}

void dfs(int i,int j,string s)
{
    vis[i][j]=true;
    s.push_back(arr[i][j]);
    if(ispresent(s))
    {
        all_string.push_back(s);
    }
    for(int k=0;k<4;k++)
    {
        int x=i+dx[k];
        int y=j+dy[k];
        if(isvalid(x,y))
        dfs(x,y,s);
    }
    s.pop_back();
}
int main()
{
    preprocessing();
    cout<<"ENTER THE CHARCTERS (in lowercase)\n";
    readdata();
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            reset();
            dfs( i, j,"");
        }
    }
    
    int tot=all_string.size();
    cout<<"Total words found="<<tot<<"\n";
    for(int i=0;i<tot;i++)
    {
        cout<<all_string[i]<<"\n";
    }
}