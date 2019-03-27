/*
Maximum Post Reachability in a social network

Concepts:
Multiple Structures
BFS
Spanning Forest
Sorting on basis of edges of spanning tree

*/

#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

using namespace std;

struct node
{
   char city[20];
   int ind;
   node *next;
};

struct Main_node
{
    char city[20];
    int visited;
    int noe;
    node *next;
};

int total=0;
char ans[50][20];

void CalcNOE(Main_node Adj[],int non);                         //Calculates number of Edges of each spanning tree of each vertex
int traversalNOE(Main_node Adj[],node *ptr,int &key);          //Traversal to each edge for calculating number of edges
void Findind(Main_node Adj[],int non);                         //Finds index of each vertex and store in child node of adjacency list
void readG(Main_node adj[],int non);                           //Reads the data set from user
void displayG(Main_node adj[],int non);
void sortG(Main_node Adj[],int non);
int traversalG(Main_node Adj[],node *ptr);
void EvaluateG(Main_node Adj[],int non);

int main()
{
    Main_node Adj[50];
    int i,non;
    cout<<"Enter the number of total cities having military bases: ";
    cin>>non;
    for(i=0;i<non;i++)
    {
        cout<<"Enter city name:";
        scanf("%s",Adj[i].city);
        Adj[i].next=NULL;
        Adj[i].visited=0;
    }
    readG(Adj,non);
    cout<<"\n---------------------------------------\n";
    cout<<"\n The Military Base network is: ";
    displayG(Adj,non);
    EvaluateG(Adj,non);
    printf("\nThe weapons must be distributed to:\n");
    for(int h=0;h<=total;h++)
        {
            printf("%s",ans[h]);
            printf("\n");
        }
    return 0;
}

void Findind(Main_node Adj[],int non)
{
    for(int i=0;i<non;i++)
    {
        node *ptr;
        ptr=Adj[i].next;
        while(ptr!=NULL)
        {
            for(int j=0;j<non;j++)
            {
                if(strcmpi(Adj[j].city,ptr->city)==0)
                {
                    ptr->ind=j;
                }
            }
            ptr=ptr->next;
        }
    }
}

void CalcNOE(Main_node Adj[],int non)
{
    for(int i=0;i<non;i++)
    {
        int key=0;
        node *ptr;
        ptr=Adj[i].next;
        Adj[i].visited=1;
        while(ptr!=NULL)
        {
            key++;
            traversalNOE(Adj,ptr,key);
            ptr=ptr->next;
        }
        Adj[i].noe=key;
        for(int j=0;j<non;j++)
            {
                Adj[j].visited=0;
            }
    }
}

int traversalNOE(Main_node Adj[],node *ptr,int &key)
{
    if(ptr==NULL || Adj[ptr->ind].visited==1)
    {
        return 0;
    }
    else
    {
        Adj[ptr->ind].visited=1;
        node *Ptr;
        Ptr=Adj[ptr->ind].next;
        while(Ptr!=NULL)
        {
            key++;
            traversalNOE(Adj,Ptr,key);
            Ptr=Ptr->next;
        }
    }
    return 0;
}

void readG(Main_node Adj[],int non)
{
    node *new_node,*last;
    int i,j,n;
    char val[20];
    total+=non;
    for(i=0;i<non;i++)
    {
        last=NULL;
        cout<<"\nEnter the number of cities "<< Adj[i].city<<" is connected to: ";
        cin>>n;
        for(j=0;j<n;j++)
        {
            cout<<"\nEnter the city connected to "<<Adj[i].city<<" : ";
            scanf("%s",val);
            new_node=new node;
            strcpy(new_node->city,val);
            new_node->next=NULL;
            if(Adj[i].next==NULL)
            {
                Adj[i].next=new_node;
            }
            else
            {
                last->next=new_node;
            }
            last=new_node;
        }
    }
    Findind(Adj,non);
    CalcNOE(Adj,non);
    for(i=0;i<non;i++)
    {
        Adj[i].visited=0;
    }
}

void displayG(Main_node Adj[], int non)
{
    node *ptr;
    int i;
    for(i=0;i<non;i++)
    {
        ptr=Adj[i].next;
        cout<<"\n The Base "<<Adj[i].city<<" is connected to : ";
        while(ptr!=NULL)
        {
            cout<<"\t"<<ptr->city;
            ptr=ptr->next;
        }
    }
}

void sortG(Main_node Adj[],int non)
{
    int i, j;
    Main_node key;
    for (i = 1; i < non; i++)
    {
        key = Adj[i];
        j = i - 1;
        while (j >= 0 && Adj[j].noe < key.noe)
        {
            Adj[j + 1] = Adj[j];
            j = j - 1;
        }
        Adj[j + 1] = key;
    }
}

int traversalG(Main_node Adj[],node *ptr)
{
    if(ptr==NULL || Adj[ptr->ind].visited==1)
    {
        return 0;
    }
    else
    {
        Adj[ptr->ind].visited=1;
        node *Ptr;
        Ptr=Adj[ptr->ind].next;
        while(Ptr!=NULL)
        {
            traversalG(Adj,Ptr);
            Ptr=Ptr->next;
        }
    }
    return 0;
}

void EvaluateG(Main_node Adj[],int non)
{
    sortG(Adj,non);
    for(int i=0;i<non;i++)
    {
        if(Adj[i].visited==0)
        {
           strcpy(ans[total++],Adj[i].city);
           node *ptr;
           ptr=Adj[i].next;
           Adj[i].visited=1;
           while(ptr!=NULL)
            {
                traversalG(Adj,ptr);
                ptr=ptr->next;
            }
        }
    }
}
