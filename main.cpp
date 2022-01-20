#include "arete.h"
#include <map>
#include <cmath>
#include <limits>
#include <iostream>


int main(){

//test

    Arete a("Paris","Lyon",1.1), b("Paris","Rennes",9.2), c("Paris","Tour",4.2);
    Arete d("Paris","Lille",0.2), e("Paris","Marseille",6.2);
    Arete f("Lyon","Lille",2.3), g("Lyon","Toulouse",1.3), h("Lyon","Mozère",2.9);
    Arete j("Toulouse","Marseille",90.0), k("Toulouse","Toulon",88.0);
    Arete l("Rennes","Brest",45.3), m("Toulon","Nice",98.2);

    std::map<std::string,std::vector<Arete>> som;

    som["Paris"]={a,b,c,d,e};
    som["Lyon"]={f,g,h};
    som["Toulouse"]={j,k};
    som["Rennes"]={l};
    som["Toulon"]={m};
 
    Graphe_adj graph(som);

    graph.print_graph();

    return 0;
    
}

//j'ai essayé de creer un graphe representant des villes pour tester 