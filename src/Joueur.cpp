#include "Joueur.hpp"
#include <iostream>

Joueur::Joueur(const std::string& nom) 
    : Entraineur(nom), nombreBadges(0), combatsGagnes(0), combatsPerdus(0) {}

void Joueur::ajouterBadge() {
    nombreBadges++;
    std::cout << "Félicitations ! Vous avez obtenu un nouveau badge !" << std::endl;
    std::cout << "Nombre total de badges : " << nombreBadges << std::endl;
}

void Joueur::incrementerCombatsGagnes() {
    combatsGagnes++;
}

void Joueur::incrementerCombatsPerdus() {
    combatsPerdus++;
}

void Joueur::afficherStatistiques() const {
    std::cout << "Statistiques de " << nom << " :" << std::endl;
    std::cout << "Badges : " << nombreBadges << std::endl;
    std::cout << "Combats gagnés : " << combatsGagnes << std::endl;
    std::cout << "Combats perdus : " << combatsPerdus << std::endl;
    std::cout << "Ratio de victoires : ";
    
    int totalCombats = combatsGagnes + combatsPerdus;
    if (totalCombats > 0) {
        float ratio = static_cast<float>(combatsGagnes) / totalCombats * 100.0f;
        std::cout << ratio << "%" << std::endl;
    } else {
        std::cout << "N/A (aucun combat)" << std::endl;
    }
}

void Joueur::recupererPointsDeVie() {
    for (auto& pokemon : equipe) {
        // Valeurs typiques de HP pour un Pokémon
        int maxHP;
        if (pokemon->getType() == "Feu") {
            maxHP = 39; // Salamèche
        } else if (pokemon->getType() == "Eau") {
            maxHP = 44; // Carapuce
        } else if (pokemon->getType() == "Plante") {
            maxHP = 45; // Bulbizarre
        } else {
            maxHP = 50; // Valeur par défaut
        }
        
        // On réinitialise les HP à leur valeur maximale
        if (pokemon->getHP() < maxHP) {
            pokemon->restaurerHP(maxHP);
            std::cout << pokemon->getNom() << " a récupéré tous ses points de vie !" << std::endl;
        }
    }
    
    std::cout << "Tous vos Pokémon sont maintenant en pleine forme !" << std::endl;
}

void Joueur::changerOrdrePokemon(int index1, int index2) {
    if (index1 >= 0 && index1 < static_cast<int>(equipe.size()) &&
        index2 >= 0 && index2 < static_cast<int>(equipe.size())) {
        std::swap(equipe[index1], equipe[index2]);
        std::cout << "L'ordre de vos Pokémon a été modifié." << std::endl;
    } else {
        std::cout << "Indices invalides. Veuillez choisir des indices valides." << std::endl;
    }
}

int Joueur::getNombreBadges() const {
    return nombreBadges;
}

int Joueur::getCombatsGagnes() const {
    return combatsGagnes;
}

int Joueur::getCombatsPerdus() const {
    return combatsPerdus;
}

void Joueur::interagir() const {
    std::cout << "Bonjour, je m'appelle " << nom << " et je suis un dresseur Pokémon !" << std::endl;
    std::cout << "J'ai remporté " << nombreBadges << " badges jusqu'à présent." << std::endl;
} 