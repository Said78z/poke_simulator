#ifndef MENU_HPP
#define MENU_HPP

#include <memory>
#include <vector>
#include "Joueur.hpp"
#include "LeaderGym.hpp"
#include "MaitrePokemon.hpp"

class Menu {
private:
    std::shared_ptr<Joueur> joueur;
    std::vector<std::shared_ptr<LeaderGym>> leaders;
    std::vector<std::shared_ptr<MaitrePokemon>> maitres;
    std::vector<std::shared_ptr<Entraineur>> entraineursVaincus;

public:
    Menu();
    
    // Initialisation du jeu
    void chargerDonnees();
    void chargerDonneesPokemon();
    void chargerDonneesJoueur();
    void sauvegarderDonneesJoueur();
    void nouvellePartie();
    void afficherMenuInitial();
    
    // Affichage et gestion du menu principal
    void afficherMenuPrincipal() const;
    void executerOption(int choix);
    
    // Options du menu
    void afficherPokemon() const;
    void recupererPointsDeVie();
    void changerOrdrePokemon();
    void afficherStatistiques() const;
    void affronterGymnase();
    void affronterMaitrePokemon();
    void interagirAvecEntite();
    
    // Boucle principale du jeu
    void demarrer();
};

#endif 