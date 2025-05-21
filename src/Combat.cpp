#include "Combat.hpp"
#include "Entraineur.hpp"
#include "MaitrePokemon.hpp"
#include <iostream>

Combat::Combat(std::shared_ptr<Entraineur> entraineur1, std::shared_ptr<Entraineur> entraineur2)
    : entraineur1(entraineur1), entraineur2(entraineur2), indexPokemon1(0), indexPokemon2(0) {}

void Combat::demarrer() {
    std::cout << "\nCOMBAT : " << entraineur1->getNom() << " VS " << entraineur2->getNom() << std::endl;
    std::cout << "----------------------------------------------" << std::endl;

    bool victoire = false;
    bool defaite = false;

    // Continuer le combat tant qu'un entraîneur a des Pokémon valides
    while (!victoire && !defaite) {
        // Afficher l'état des Pokémon actuels
        auto pokemon1 = entraineur1->getPokemon(indexPokemon1);
        auto pokemon2 = entraineur2->getPokemon(indexPokemon2);

        std::cout << "\nPokémon actifs:" << std::endl;
        std::cout << entraineur1->getNom() << ": ";
        pokemon1->afficher();
        std::cout << std::endl;
        
        std::cout << entraineur2->getNom() << ": ";
        pokemon2->afficher();
        std::cout << std::endl;

        // Le joueur attaque toujours en premier
        bool tourSuivant = effectuerTour();
        
        if (!tourSuivant) {
            // Vérifier si un des entraîneurs n'a plus de Pokémon valides
            if (!entraineur1->aDesPokemonValides()) {
                defaite = true;
            } else if (!entraineur2->aDesPokemonValides()) {
                victoire = true;
            }
        }
    }

    // Afficher le résultat du combat
    afficherResultat(victoire);
}

bool Combat::effectuerTour() {
    auto pokemon1 = entraineur1->getPokemon(indexPokemon1);
    auto pokemon2 = entraineur2->getPokemon(indexPokemon2);
    bool continuerCombat = true;

    // Tour du joueur (entraineur1)
    std::cout << "\n" << entraineur1->getNom() << " attaque avec " << pokemon1->getNom() 
              << " utilisant " << pokemon1->getAttaque() << "!" << std::endl;
    
    int degats = calculerDegats(pokemon1, pokemon2);
    pokemon2->subirDegats(degats);
    
    std::cout << pokemon2->getNom() << " subit " << degats << " dégâts!" << std::endl;
    
    // Vérifier si le Pokémon adverse est K.O.
    if (pokemon2->getHP() <= 0) {
        std::cout << pokemon2->getNom() << " est K.O.!" << std::endl;
        
        // Passer au Pokémon suivant si disponible
        indexPokemon2++;
        if (indexPokemon2 >= static_cast<int>(entraineur2->getNombrePokemon())) {
            return false; // Plus de Pokémon disponibles, fin du combat
        }
        
        std::cout << entraineur2->getNom() << " envoie " 
                  << entraineur2->getPokemon(indexPokemon2)->getNom() << "!" << std::endl;
        return true;
    }
    
    // Tour de l'adversaire (entraineur2)
    std::cout << "\n" << entraineur2->getNom() << " attaque avec " << pokemon2->getNom() 
              << " utilisant " << pokemon2->getAttaque() << "!" << std::endl;
    
    degats = calculerDegats(pokemon2, pokemon1);
    pokemon1->subirDegats(degats);
    
    std::cout << pokemon1->getNom() << " subit " << degats << " dégâts!" << std::endl;
    
    // Vérifier si le Pokémon du joueur est K.O.
    if (pokemon1->getHP() <= 0) {
        std::cout << pokemon1->getNom() << " est K.O.!" << std::endl;
        
        // Passer au Pokémon suivant si disponible
        indexPokemon1++;
        if (indexPokemon1 >= static_cast<int>(entraineur1->getNombrePokemon())) {
            return false; // Plus de Pokémon disponibles, fin du combat
        }
        
        std::cout << entraineur1->getNom() << " envoie " 
                  << entraineur1->getPokemon(indexPokemon1)->getNom() << "!" << std::endl;
    }
    
    return continuerCombat;
}

int Combat::calculerDegats(std::shared_ptr<Pokemon> attaquant, std::shared_ptr<Pokemon> defenseur) {
    // Calcul de base des dégâts
    int degatsBase = attaquant->getPuissance();
    
    // Application du multiplicateur de type
    float multiplicateur = attaquant->getMultiplicateurContre(defenseur->getType());
    
    // Si l'attaquant est un Maître Pokémon, appliquer bonus de 25%
    auto maitre = dynamic_cast<MaitrePokemon*>(entraineur2.get());
    if (maitre && attaquant == entraineur2->getPokemon(indexPokemon2)) {
        multiplicateur *= maitre->getBonusDegats();
    }
    
    if (multiplicateur > 1.0f) {
        std::cout << "C'est super efficace!" << std::endl;
    } else if (multiplicateur < 1.0f) {
        std::cout << "Ce n'est pas très efficace..." << std::endl;
    }
    
    return static_cast<int>(degatsBase * multiplicateur);
}

void Combat::afficherResultat(bool victoire) {
    std::cout << "\n----------------------------------------------" << std::endl;
    if (victoire) {
        std::cout << "VICTOIRE pour " << entraineur1->getNom() << " !" << std::endl;
    } else {
        std::cout << "DÉFAITE pour " << entraineur1->getNom() << " !" << std::endl;
        std::cout << entraineur2->getNom() << " remporte le combat." << std::endl;
    }
} 