#include <iostream>
#include <windows.h>
#include "Menu.hpp"
#include "PokemonFeu.hpp"
#include "PokemonEau.hpp"
#include "PokemonPlante.hpp"

// Fonction de test pour les Pokémon à double type
void testerPokemonDoubleType() {
    std::cout << "\n====== TEST POKEMON DOUBLE TYPE ======" << std::endl;
    
    // Créer un Pokémon Plante/Poison (Bulbizarre)
    auto bulbizarre = std::make_shared<PokemonPlante>("Bulbizarre", 45, "Fouet Lianes", 60, "Poison");
    
    // Créer un Pokémon Eau/Vol (Leviator)
    auto leviator = std::make_shared<PokemonEau>("Leviator", 95, "Cascade", 100, "Vol");
    
    // Créer quelques Pokémon à type simple pour comparaison
    auto salameche = std::make_shared<PokemonFeu>("Salamèche", 39, "Flammèche", 70);
    auto carapuce = std::make_shared<PokemonEau>("Carapuce", 44, "Pistolet à O", 65);
    
    // Afficher les Pokémon
    std::cout << "------- Affichage des Pokémon -------" << std::endl;
    bulbizarre->afficher(); std::cout << std::endl;
    leviator->afficher(); std::cout << std::endl;
    salameche->afficher(); std::cout << std::endl;
    carapuce->afficher(); std::cout << std::endl;
    
    // Tester l'interaction
    std::cout << "\n------- Interaction avec les Pokémon -------" << std::endl;
    bulbizarre->interagir();
    std::cout << std::endl;
    leviator->interagir();
    std::cout << std::endl;
    
    // Tester les multiplicateurs de dégâts
    std::cout << "\n------- Test des multiplicateurs de dégâts -------" << std::endl;
    std::cout << "Salamèche vs Bulbizarre (Plante/Poison): " 
              << salameche->getMultiplicateurContre(bulbizarre->getType()) << "x" << std::endl;
    std::cout << "Carapuce vs Leviator (Eau/Vol): " 
              << carapuce->getMultiplicateurContre(leviator->getType()) << "x" << std::endl;
    
    std::cout << "====== FIN DU TEST ======\n" << std::endl;
}

int main() {
    // Configuration de la console pour l'affichage des accents
    SetConsoleOutputCP(CP_UTF8);
    
    // Test des Pokémon à double type
    testerPokemonDoubleType();
    
    std::cout << "Bienvenue dans le Simulateur de Combat Pokémon !" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    
    // Créer et démarrer le menu principal
    Menu menu;
    menu.demarrer();
    
    return 0;
}
