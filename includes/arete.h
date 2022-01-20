#pragma once
#include <map>
#include <iostream>
#include <vector>

class Arete{
    private :
        std::string som_debut;
        std::string som_fin;
        double valeur;
    public:
        Arete(std::string sd, std::string sf, double val) :
            som_debut(sd),
            som_fin(sf),
            valeur(val) {}

        std::string get_sd(); // renvoie le sommet du début

        std::string get_sf(); //renvoie le sommet de la fin

        double get_val(); //renvoie la valeur de l'arete

        std::string print_arete(); //afficher une arete sous forme textuelle
        
};

class Graphe_mat;

class Graphe_adj{
    private :
        std::map<std::string, std::vector<Arete>> som;
    //dictionnaire qui au nom d'un sommet associe la liste des aretes partant de ce sommet
    
    public:
        Graphe_adj(std::map<std::string, std::vector<Arete>> sm):
            som{sm} {}

        std::string print_graph();
        Graphe_adj read_graph_adj(std::string graph); //lecture d'un fichier graphe sous graphe adj

        void add (std::string A, std::vector<Arete> B) {
            som[A] = B;
        }
        std::map<std::string, std::vector<Arete>> get_som();
        std::vector<std::string> get_noms_som();
        Graphe_adj mat_to_adj(Graphe_mat graph);

};

class Graphe_mat{
    std::vector<std::vector<double>> mat; //matrice d'adjacence
    std::vector<std::string> sommets; //liste des sommets
    public:
        Graphe_mat(std::vector<std::vector<double>> m, std::vector<std::string> soms):
            sommets{soms},
            mat{m} {}
        Graphe_mat adj_to_mat(Graphe_adj graph);
        std::vector<std::vector<double>> get_mat(){
            return mat;
        }
        std::vector<std::string> get_sommets(){
            return sommets;
        }
        Graphe_mat read_graphe_mat(std::string graphe);
        std::string print_gr_mat();
}; 
