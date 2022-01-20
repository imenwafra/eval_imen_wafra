#include "arete.h"
#include <map>
#include <cmath>
#include <limits>
#include <iostream>
#include <stack>
#include <queue>


//je n'ai pas fait toutes les questions et je n'ai pas reussi a corriger toutes 
//mes erreurs, je n'ai pas pu faire mes test mais j'ai code 5 questions



std::map<std::string, std::vector<Arete>> Graphe_adj::get_som(){
    return som;
}
//fonction qui renvoie le dictionnaire contenant la liste des sommets et des aretes associees

std::string Arete::get_sd(){
    return som_debut;
}
//renvoie le sommet entrant de l'arete

std::string Arete::get_sf(){
    return som_fin;
}

double Arete::get_val(){
    return valeur;
}

bool vrai=true;
bool faux=false;

bool is_in_lst(std::string elem, std::vector<std::string> lst){
    for (auto c:lst){
        if(c==elem){
            return faux;
        }
    }
    return vrai;
}

//fonction pour tester si un élément est dans une liste

//QUESTION 1

Graphe_mat Graphe_mat::adj_to_mat(Graphe_adj graphe){
    std::map<std::string, std::vector<Arete>> s;
    s=graphe.get_som();  //dictionnaire de graphe
    int sz=s.size(); //taille du dictionnaire

    std::vector<std::string> sommets; //liste des sommets initialisée
    
    std::vector<double> sous_mat(sz, std::numeric_limits<double>::infinity());
    std::vector<std::vector<double>> matr(sz, sous_mat); //initialisation de la matrice d'adjacence
    

    std::map<std::string, int> dico; //dico qui au nom d'un sommet va associer son indice
    int i{0};
    for(auto c:s){
        sommets.push_back(c.first);
        dico[c.first]=i;  //à la clé nom du sommet on associe l'indice
        i++;
    }
    int k{0};
    for(auto c:s){
        std::vector<Arete> aretes=c.second; //liste d'aretes du sommet c
        for(auto ar:aretes){
            int j=dico[ar.get_sf()];   //on récupère l'indice du voisin correspondant à l'arete
            matr[k][j]=ar.get_val();  //m[i,j]= la valeur de l'arete
            k++;
        }
    }
    Graphe_mat gr_mat(matr,sommets);
    return gr_mat;

}

Graphe_adj Graphe_adj::mat_to_adj(Graphe_mat graphe){
    std::vector<std::string> sommets=graphe.get_sommets(); //on récupère les sommets
    std::vector<std::vector<double>> mat=graphe.get_mat(); //on récupère la matrice d'adjacence

    std::map<std::string, std::vector<Arete>> dico_som; //on initialise le dico des sommets
    
    for(int i=0; i<sommets.size(); i++){
        std::string som_debut = sommets[i];
        std::vector<Arete> aretes; //on initialise la liste d'aretes de sommet[i]
        for (int j=0; j<sommets.size(); j++){
            if(mat[i][j]!=std::numeric_limits<double>::infinity()){
                std::string som_fin = sommets[j];
                double valeur=mat[i][j];
                Arete ar(som_debut, som_fin, valeur);
                aretes.push_back(ar);
            }
        }
        dico_som[sommets[i]]=aretes; // au nom du sommet i on associe la liste des ses aretes
    
    }
    Graphe_adj graph_ad(dico_som);
    return graph_ad;
}

std::string Graphe_adj::print_graph(){   //afficher un graphe sous forme textuelle
    //std::map<std::string, std::vector<Arete>> som;
    //som=graphe.get_som();
    std::string graphe_ch="" ; //graphe sous forme textuelle, initialisation de la chaîne de caractères
    for(auto c: som){
        std::vector<Arete> aretes=c.second;
        for(Arete ar: aretes){
            std::string s_d=ar.get_sd();
            std::string s_f=ar.get_sf();
            std::string val=std::to_string(ar.get_val());
            graphe_ch  = graphe_ch + s_d + ' ' + s_f + ' ' + val + '\n'; 
            //on ajoute l'arete ar a la chaine de caracteres
        }
    }
    std::cout<<graphe_ch<<std::endl;
    return 0;
}

std::string Graphe_mat::print_gr_mat(){  //affiche la matrice d'adjacence
    std::vector<std::vector<double>> mat= graphe.get_mat();
    std::vector<std::string> sommets = graphe.get_sommets();
    for(int i{0}; i<sommets.size(); i++){
        for(int j{0}; j<sommets.size(); j++){
            std::cout<<mat[i][j];
        }
        std::cout<<'\n';
    }
    return 0;
}

//QUESTION 2

//cette fonction ne fonctionne pas, je n'ai pas reussi a corriger les erreurs
Graphe_adj read_graph_adj(){
   std::string graph;
   std::cout<<"entrez le nom du fichier graphe"<<std::endl; //on entre le graphe sous la forme d'une chaine de caracteres
   std::cin>>graph;   //le fichier n'est pas pris en argument mais demandé à l'utilisateur

   int sz=graph.size(); //taille de la chaine de caractère
   //détecter les espaces
   std::map<std::string, std::vector<Arete>> dico_som;
   std::vector<std::string> lst;
   std::vector<std::string> sommets;
   std::vector<Arete> aretes;
   int i{0};
   int n{0};

   while(i<sz){

       int n{0}; //nombre de "mots"
       std::string mot= "";
       while((graph[i]!=" ") && (graph[i]!='\n')){   //on détecte les espaces et changements de lignes qui séparent les caractères
       //je ne sais pas pourquoi cette comparaison n'est pas valide
           mot= mot + graph[i];
           i++;
       }
       n++;
       lst.push_back(mot); 
       }
    int size=lst.size();
     
    for(int k{0}; k<sz; k++){
        if((k%3==0) && (is_in_lst(lst[k],sommets)==false)){ //on vérifie si l'élément n'est pas déjà dans la liste
            sommets.push_back(lst[k]);  //on remplit la liste des sommets
            std::string sd = lst[k];
            std::string sf = lst[k+1];
            double val= std::stod(lst[k+2]);
            Arete ar(sd,sf,val);
            aretes.push_back(ar); //on remplit la liste des aretes
        }
        if((k%3==1) && (is_in_lst(lst[k],sommets)==false)){  //cas où un sommet n'a aucune arête sortante
            sommets.push_back(lst[k]);  //il faut quand même qu'il soit dans la liste des sommets
        }
    }

    for(auto s:sommets){
        std::vector<Arete> aretes_som; //liste des aretes du sommet s
        for(Arete ar:aretes){
            std::string sf=ar.get_sf();
            if(sf==s){
                aretes_som.push_back(ar);
            }
        }
        dico_som[s]=aretes_som;  //on remplit le dico : à la clé s on associe la liste d'aretes de s
    }
    return Graphe_adj(dico_som);
}


Graphe_mat read_graph_mat(){
   std::string graph;
   std::cout<<"entrez le fichier graphe"<<std::endl;
   std::cin>>graph;   //le fichier n'est pas pris en argument mais demandé à l'utilisateur

    Graphe_adj graph_adj = read_graph_adj();  //on utilise la fonction précédente qui convertit le fichier teste en Graphe_adj

    Graphe_mat graph_mat = graph_mat.adj_to_mat(graph_adj); //on utilise la fonction qui convertit le Graph_adj en Graph_adj

    return graph_mat;

    
}

//QUESTION 3


int ind_elem(std::string elem, std::vector<std::string> lst){ //fonction qui renvoie l'indice dans une liste lst d'un élément elem
    int sz=lst.size();
    for(int i{0}; i<sz; i++){
        if(lst[i]==elem){
            return i;
        }
    }
}
//fonction qui retourne l'indice d'un element dans une liste

void parcourt_som(std::string som, std::vector<std::string> visiter, std::map<std::string, std::vector<Arete>> dico){
    //fonction recursive
    //prend en argument un sommet a parcourir, une liste de sommets a visiter et la liste d'adjacence
    //l'agorithme se termine tout seul lorsque la liste des sommets a visiter est vide

    std::vector<Arete> aretes = dico[som]; //on récupère la liste des aretes de som
    for(Arete ar:aretes){
        std::string sf=ar.get_sf();
        double val = ar.get_val();
        visiter.erase(visiter.begin()+ind_elem(som,visiter));
        std::cout<<som<<sf<<val<<std::endl;
        //recursion
        parcourt_som(sf,visiter,dico); //récursion : on applique l'algorithme aux sommets voisins

    }
}

void parcourt_graphe(Graphe_adj graph){
    //fonction qui va utiliser la fonction recursive precedente pour parcourir tous les sommets du graphe
    std::map<std::string, std::vector<Arete>> dico_som = graph.get_som();

    
    std::vector<std::string> a_visiter; //sommets à visiter
    for(auto c:dico_som){
        a_visiter.push_back(c.first);  //initialisée avec la liste complète des sommets
    }
    while(a_visiter.size()>0){ //tant qu'il y a des sommets a visiter
        std::string som=a_visiter[0];
        parcourt_som(som, a_visiter, dico_som); //on applique l'algorithme de parcourt tant que la liste des sommets à visiter n'est pas vide
    }

}


//QUESTION 4

void parcourt_iteratif(Graphe_adj graph){
    std::stack<std::string> pile;  //pile où on met les sommets en cours de visite
    std::vector<std::string> a_visiter; //liste des sommets du graphe
    std::vector<std::string> visites; //sommets deja visites

    std::map<std::string, std::vector<Arete>> dico_som = graph.get_som();

    for(auto c:dico_som){
        a_visiter.push_back(c.first);
    }
    //on remplit la liste des sommets du graphe, qui doivent tous etre visites au debut

    pile.push(a_visiter[0]); //on remplit la pile avec un sommet a visiter
    while((pile.size()>0) || (a_visiter.size() > 0) ){ //tant qu'il reste des sommets dans la pile ou qu'il reste des sommets a visiter, on continue
        if((pile.size() == 0)&& (a_visiter.size()>0)){ //on a fini de parcourir un sommet mais il en reste d'autres a parcourir
            pile.push(a_visiter[a_visiter.size()-1]); //on remplit la pile avec un sommet a visiter
            a_visiter.pop_back(); //on ajoute l'élément à la pile et on l'enleve de la lsite des sommets a parcourir        
        }
        else{
            std::string s = pile.top(); //on prend le sommet au dessus de la pile
            pile.pop(); //on l'enleve da la liste des sommets a visiter
            visites.push_back(s); //on l'ajoute a la liste des sommets visites
            std::cout<< s <<std::endl; //on affiche le sommet s
            std::vector<Arete> aretes = dico_som[s]; //on recupere la liste des aretes de s
            for(Arete ar:aretes){ //on parcourt la liste des aretes
                std::string sf = ar.get_sf();
                double val = ar.get_val();
                std::cout<<s<<sf<<val<<std::endl; //on affiche les aretes du sommet s
                if(is_in_lst((ar.get_sf(), a_visiter))){//on verifie que le sommet voisin n'a pas deja ete visite
                    int j = ind_elem(a_visiter, ar.get_sf()); //on recupere l'indice du sommet voisin dans la liste des sommets a visiter
                    a_visiter.erase(a_visiter.begin()+j); //on l'enleve de la liste des sommets a visiter
                } 
                
            }
        }

    }

}


// la meme en graphe mat

void parcourt_iteratif(Graphe_mat graph){
    Graphe_adj graphadj = mat_to_adj(graph); //on convertit la matrice d'adjacence en graphe adj
    parcourt_iteratif(graphadj); //on applique la fonction précédente

}


//QUESTION 5

void parcourt_largeur_niveau(int niveau, std::string som, std::vector<std::string> a_visiter, Graphe_adj graph){
    std::map<std::string, std::vector<Arete>> dico_som = graph.get_som();
    std::vector<Arete> aretes = dico_som[som]; //on recupere la liste des aretes du sommet de depart


    if(niveau==1){ // on n'affiche que les aretes des sommets voulus
        for(Arete ar:aretes){
            if(is_in_lst(ar.get_sf(), a_visiter)){
                std::string sf = ar.get_sf();
                double val = ar.get_val();
                std::cout<<som<<sf<<val<<std::endl; //on affiche les aretes du sommet s
                int ind = ind_elem(sf, a_visiter);
                a_visiter.erase(a_visiter.begin()+ind);
            }
        }

    }
    else{
        std::vector<std::string> voisins; //voisins sortants
        for(Arete ar:aretes){
            if(is_in_lst(ar.get_sf(), a_visiter)){
                voisins.push_back(ar.get_sf());
                std::cout<<ar.get_sd()<<ar.get_sf()<<ar.get_val()<<std::endl; //on affiche l'arete
                std::cout<<ar.get_sf()<<std::endl;
                int ind = ind_elem(ar.get_sf(), a_visiter);
                a_visiter.erase(a_visiter.begin()+ind);


            }
        }
        for(std::string v:voisins){
            parcourt_largeur_niveau(niveau-1,v,a_visiter,graph); //on parcourt le niveau suivant
        }

    }
}


void parcourt_largeur(Graphe_adj graph,int niveau, std::string som){ 
    //on prend en parametres le niveau auquel on veut s'arreter et le sommet de depart
    std::queue<std::string> file;  //file où on met les sommets en cours de visite (on remplace la pile du programme précéent par cette file )
    std::vector<std::string> a_visiter; //liste des sommets a visiter, tous au debut
    std::vector<std::string> visites; //sommets deja visites

    std::map<std::string, std::vector<Arete>> dico_som;

    file.push(som);

    
    for(auto c:dico_som){
        a_visiter.push_back(c.first);
    }
    int j = ind_elem(som, a_visiter);
    a_visiter.erase(a_visiter.begin()+j);

    if(niveau==0){   //on parcourt tout le graphe, comme pour le parcourt en profondeur
        while((a_visiter.size()>0) || (file.size()>0)){
            if((file.size()==0)&&(a_visiter.size()!=0)){ //la file est vide donc on a fini de visiter le sommet, mais il en reste a visiter donc on doit mettre le sommet suivant dans la file pour le visiter
                std::string s = a_visiter[a_visiter.size()-1];
                file.push(a_visiter[a_visiter.size()-1]);
                a_visiter.pop_back(); //
                std::cout<<s<<std::endl;
            }
            else{
                std::string s = file.front(); //on recupere le premier sommet de la file
                file.pop();
                visites.push_back(s);
                std::vector<Arete> aretes = graph.get_som();
                for(Arete ar:aretes){
                    if(is_in_lst(ar.get_sf(), a_visiter)){
                        std::string sf = ar.get_sf();
                        double val = ar.get_val();
                        std::cout<<s<<sf<<val<<std::endl; //on affiche les aretes du sommet s
                        std::cout<<sf<<std::endl; //on affiche le sommet sortant qu'on va visiter ensuite
                        int ind = ind_elem(sf, a_visiter); 
                        a_visiter.erase(a_visiter.begin()+ind);
                    }
                }
            }

        }

    }
    else{
        parcourt_largeur_niveau(niveau, som, a_visiter, graph);
    }

    
}


