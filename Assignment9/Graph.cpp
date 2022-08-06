//CS1300 Fall 2019
//Author: Mark Davis
//Recitation:203 Divya
//Homework #9

#include <iostream>
#include <math.h>
#include <cmath>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <locale>
#include <vector>
#include <queue>
#include <stack>
#include "Graph.hpp"

using namespace std;

void Graph::addEdge(string v1, string v2,int n){//make connections b/n vertexes & add weight
  for(unsigned int i = 0; i < vertices.size(); i++){
      if(vertices[i]->name == v1){
          for(unsigned int j = 0; j < vertices.size(); j++){
              if(vertices[j]->name == v2 && i != j){
                  adjVertex av;
                  av.v = vertices[j];
                  av.weight = n;
                  vertices[i]->adj.push_back(av);
                  //another vertex for edge in other direction
                  adjVertex av2;
                  av2.v = vertices[i];
                  av2.weight = n;
                  vertices[j]->adj.push_back(av2);
              }
          }
      }
  }
}

void Graph::addVertex(string n){//add vertex node
  bool found = false;
  for(int i = 0; i < vertices.size(); i++){
      if(vertices[i]->name == n){
          found = true;
      }
  }
  if(!found){
      vertex * v = new vertex;
      v->name = n;
      vertices.push_back(v);
  }
}

void Graph::displayEdges(){//print edges

  for(unsigned int i = 0; i < vertices.size(); i++){
      cout << vertices[i]->name << " --> ";
      for(unsigned int j = 0; j < vertices[i]->adj.size(); j++){
          cout << vertices[i]->adj[j].v->name << " ";
      }
      cout << endl;
  }

  /* Formatting
  Boulder --> Denver
  Denver --> Boulder Las Vegas
  Las Vegas --> Denver */
}

void depthFirstHelper(vertex* n){
  if(n == NULL)
    return;

  n->visited = true;
  cout<< n->name << " --> " ;

  for(unsigned int x = 0; x < n->adj.size(); x++ ){
    if(!n->adj[x].v->visited){
      depthFirstHelper(n->adj[x].v); //need recursion to find all linked vertex
    }
  }
}

void Graph::depthFirstTraversal(string n){
  if(n == ""){
    cout << "empty string" << endl; return;
  }

  for(unsigned int i = 0; i < vertices.size(); i++){
      if(vertices[i]->name == n){
          depthFirstHelper(vertices[i]);
      }
  }
  cout << "Done";
}

vertex* Graph::DijkstraAlgorithm(string start, string end){
  vertex* vStart;//pointer to where to start
  vertex* vEnd;//pointer to where to end
  vector<vertex*> solvedset; //vector list of all the solved nodes

  for(unsigned int i = 0; i < vertices.size(); i++){
      if(vertices[i]->name == start){ //saviing start position
          vStart = vertices[i];
          solvedset.push_back(vStart);
          vStart->visited = true;
          vStart->distance = 0;
      }
      if(vertices[i]->name == end){ //saving end position
          vEnd = vertices[i];
      }
  }
  vertex* solvedV;//temp to store next solved
  vertex* parent;//temp to update parent to follow back to start

  while(!vEnd->visited){ //while end not visited from new solved list
    int minDist = 100000000;//set and reset arbitrary large
    solvedV = NULL;//set and reset pointer
    for(unsigned int i = 0; i < solvedset.size(); i++){//visiting all the list
      for(unsigned int j = 0; j < solvedset[i]->adj.size(); j++){//visiting the adj nodes
        if(!solvedset[i]->adj[j].v->visited){//if not solved(visited) check distance
          int dist = solvedset[i]->distance + solvedset[i]->adj[j].weight; //adding vertex distance and adjacent edge weight
          if(dist < minDist){ //updating mindist to lowest found
            solvedV = solvedset[i]->adj[j].v;//saving adj to get out of here
            parent = solvedset[i];//updating parent each time
            minDist = dist;//updating mindist when lower found
          }
        }
      }
    }
    //setting all the solvedV members needed then pushing to solved list
    solvedV->distance = minDist;
    solvedV->pred = parent;
    solvedV->visited = true;
    solvedset.push_back(solvedV);
  }
  return vEnd; //return end node when found and solved
}

void shortestpathHelper(string st, vertex* beg){ //recursive to print from start to end
  if(beg->name == st){//stop, print current if reached start then recurse
    cout << beg->name << " ";
    return;
  }
  shortestpathHelper(st,beg->pred); //passing each parent till reach start name
  cout << beg->name << " "; //print each name as each recursion ends(print in order)
}

void Graph::shortestpath(string start, string end){
  vertex* saved;
  for(unsigned int i = 0; i < vertices.size(); i++){
      if(vertices[i]->name == end){
        saved = vertices[i];//found vetex pointing to end
      }
  }
  shortestpathHelper(start,saved);//pass end pointer and start name for when to stop
}

// void Graph::shortestpath(string start, string end){
// //another way to do it non-recursion but with stack
//   vertex* saved;
//   for(unsigned int i = 0; i < vertices.size(); i++){
//       if(vertices[i]->name == end){
//         saved = vertices[i];
//       }
//   }
//   stack<string> s;
//   while(saved != NULL){
//     s.push(saved->name);
//     saved = saved->pred;
//   }
//   if(s.top() == start){
//     while(!s.empty()){
//       cout << s.top() << " ";
//       s.pop();
//     }
//   }else {cout << "path back to start was incorrect" << endl;}
// }

void Graph::setAllVerticesUnvisited(){
  for(int i=0; i<vertices.size(); i++) {
      vertices[i]->visited = false;
  }
}


// cout<<"Depth First Traversal " <<endl;
// cout<<endl;
// cout<<"Dikstra's Shortest distance from Aurora to Fruita: "<<vertex->distance<<endl;
// cout<<"Dikstra's Shortest path from Aurora to Fruita: "<<endl;
