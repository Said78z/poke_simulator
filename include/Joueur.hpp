#ifndef JOUEUR_HPP
#define JOUEUR_HPP

#include "Entraineur.hpp"

class Joueur : public Entraineur {
private:
    int nombreBadges;
    int combatsGagnes;
    int combatsPerdus;

public:
    Joueur(const std::string& nom);
    
    // Gestion des badges et statistiques
    void ajouterBadge();
    void incrementerCombatsGagnes();
    void incrementerCombatsPerdus();
    
    // Affichage des statistiques
    void afficherStatistiques() const;
    
    // Récupération des points de vie des Pokémon
    void recupererPointsDeVie();
    
    // Changement de l'ordre des Pokémon
    void changerOrdrePokemon(int index1, int index2);
    
    // Méthodes d'accès
    int getNombreBadges() const;
    int getCombatsGagnes() const;
    int getCombatsPerdus() const;
    
    // Surcharge de la méthode interagir
    void interagir() const override;
};

#endif 