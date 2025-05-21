#include "Menu.hpp"
#include "Combat.hpp"
#include "PokemonFeu.hpp"
#include "PokemonEau.hpp"
#include "PokemonPlante.hpp"
#include <iostream>
#include <limits>
#include <fstream>
#include <sstream>
#include <random>
#include <map>

Menu::Menu() {
    // Initialisation avec un joueur par défaut
    joueur = std::make_shared<Joueur>("Dresseur");
}

void Menu::chargerDonneesPokemon() {
    std::cout << "Chargement des Pokémon, Leaders et Maîtres..." << std::endl;
    
    // Charger les Pokémon disponibles
    std::map<std::string, std::shared_ptr<Pokemon>> pokemonDisponibles;
    std::ifstream fichierPokemon("data/pokemon.csv");
    
    if (fichierPokemon.is_open()) {
        std::string ligne;
        // Ignorer l'en-tête
        std::getline(fichierPokemon, ligne);
        
        while (std::getline(fichierPokemon, ligne)) {
            std::stringstream ss(ligne);
            std::string nom, type, attaque;
            int hp, puissance;
            
            // Format: nom,type,hp,attaque,puissance
            std::getline(ss, nom, ',');
            std::getline(ss, type, ',');
            
            std::string hpStr, puissanceStr;
            std::getline(ss, hpStr, ',');
            std::getline(ss, attaque, ',');
            std::getline(ss, puissanceStr, ',');
            
            hp = std::stoi(hpStr);
            puissance = std::stoi(puissanceStr);
            
            // Vérifier si c'est un Pokémon à double type
            std::shared_ptr<Pokemon> pokemon;
            size_t typeSeparator = type.find('/');
            
            if (typeSeparator != std::string::npos) {
                // C'est un Pokémon à double type
                std::string typePrimaire = type.substr(0, typeSeparator);
                std::string typeSecondaire = type.substr(typeSeparator + 1);
                
                // Créer le Pokémon avec son type secondaire
                if (typePrimaire == "Feu") {
                    pokemon = std::make_shared<PokemonFeu>(nom, hp, attaque, puissance, typeSecondaire);
                } else if (typePrimaire == "Eau") {
                    pokemon = std::make_shared<PokemonEau>(nom, hp, attaque, puissance, typeSecondaire);
                } else if (typePrimaire == "Plante") {
                    pokemon = std::make_shared<PokemonPlante>(nom, hp, attaque, puissance, typeSecondaire);
                } else {
                    std::cerr << "Type primaire non reconnu: " << typePrimaire << " pour " << nom << std::endl;
                    continue;
                }
            } else {
                // C'est un Pokémon à type simple
                if (type == "Feu") {
                    pokemon = std::make_shared<PokemonFeu>(nom, hp, attaque, puissance);
                } else if (type == "Eau") {
                    pokemon = std::make_shared<PokemonEau>(nom, hp, attaque, puissance);
                } else if (type == "Plante") {
                    pokemon = std::make_shared<PokemonPlante>(nom, hp, attaque, puissance);
                } else {
                    std::cerr << "Type non reconnu: " << type << " pour " << nom << ". Le Pokémon ne sera pas chargé." << std::endl;
                    continue;
                }
            }
            
            if (pokemon) {
                pokemonDisponibles[nom] = pokemon;
            }
        }
        
        fichierPokemon.close();
        std::cout << pokemonDisponibles.size() << " Pokémon chargés." << std::endl;
    } else {
        std::cerr << "Impossible d'ouvrir le fichier pokemon.csv" << std::endl;
        // Fallback: créer des Pokémon par défaut
        pokemonDisponibles["Salamèche"] = std::make_shared<PokemonFeu>("Salamèche", 39, "Flammèche", 70);
        pokemonDisponibles["Carapuce"] = std::make_shared<PokemonEau>("Carapuce", 44, "Pistolet à O", 65);
        pokemonDisponibles["Bulbizarre"] = std::make_shared<PokemonPlante>("Bulbizarre", 45, "Fouet Lianes", 60, "Poison");
    }

    // Si le joueur n'a pas de Pokémon, lui donner des Pokémon de départ
    if (joueur->getNombrePokemon() == 0) {
        joueur->ajouterPokemon(pokemonDisponibles["Salamèche"]);
        joueur->ajouterPokemon(pokemonDisponibles["Carapuce"]);
        joueur->ajouterPokemon(pokemonDisponibles["Bulbizarre"]);
    }
    
    // Charger les leaders de gym
    leaders.clear();
    std::ifstream fichierLeaders("data/leaders.csv");
    
    if (fichierLeaders.is_open()) {
        std::string ligne;
        // Ignorer l'en-tête
        std::getline(fichierLeaders, ligne);
        
        while (std::getline(fichierLeaders, ligne)) {
            std::stringstream ss(ligne);
            std::string nom, badge, gymnase, pokemon1, pokemon2;
            
            // Format: nom,badge,gymnase,pokemon1,pokemon2
            std::getline(ss, nom, ',');
            std::getline(ss, badge, ',');
            std::getline(ss, gymnase, ',');
            std::getline(ss, pokemon1, ',');
            std::getline(ss, pokemon2, ',');
            
            auto leader = std::make_shared<LeaderGym>(nom, badge, gymnase);
            
            // Ajouter les Pokémon du leader
            if (pokemonDisponibles.find(pokemon1) != pokemonDisponibles.end()) {
                leader->ajouterPokemon(pokemonDisponibles[pokemon1]);
            }
            
            if (pokemonDisponibles.find(pokemon2) != pokemonDisponibles.end()) {
                leader->ajouterPokemon(pokemonDisponibles[pokemon2]);
            }
            
            leaders.push_back(leader);
        }
        
        fichierLeaders.close();
        std::cout << leaders.size() << " leaders de gym chargés." << std::endl;
    } else {
        std::cerr << "Impossible d'ouvrir le fichier leaders.csv" << std::endl;
        // Fallback: créer des leaders par défaut
        auto leader1 = std::make_shared<LeaderGym>("Pierre", "Roche", "Argenta");
        leader1->ajouterPokemon(pokemonDisponibles["Racaillou"]);
        leader1->ajouterPokemon(pokemonDisponibles["Onix"]);
        leaders.push_back(leader1);
        
        auto leader2 = std::make_shared<LeaderGym>("Ondine", "Cascade", "Azuria");
        leader2->ajouterPokemon(pokemonDisponibles["Staross"]);
        leader2->ajouterPokemon(pokemonDisponibles["Leviator"]);
        leaders.push_back(leader2);
        
        auto leader3 = std::make_shared<LeaderGym>("Major Bob", "Foudre", "Carmin sur Mer");
        leader3->ajouterPokemon(pokemonDisponibles["Pikachu"]);
        leader3->ajouterPokemon(pokemonDisponibles["Raichu"]);
        leaders.push_back(leader3);
        
        auto leader4 = std::make_shared<LeaderGym>("Erika", "Prisme", "Céladopole");
        leader4->ajouterPokemon(pokemonDisponibles["Saquedeneu"]);
        leader4->ajouterPokemon(pokemonDisponibles["Empiflor"]);
        leaders.push_back(leader4);
    }
    
    // Charger les maîtres Pokémon
    maitres.clear();
    std::ifstream fichierMaitres("data/maitres.csv");
    
    if (fichierMaitres.is_open()) {
        std::string ligne;
        // Ignorer l'en-tête
        std::getline(fichierMaitres, ligne);
        
        while (std::getline(fichierMaitres, ligne)) {
            std::stringstream ss(ligne);
            std::string nom, pokemon1, pokemon2;
            
            // Format: nom,pokemon1,pokemon2
            std::getline(ss, nom, ',');
            std::getline(ss, pokemon1, ',');
            std::getline(ss, pokemon2, ',');
            
            auto maitre = std::make_shared<MaitrePokemon>(nom);
            
            // Ajouter les Pokémon du maître
            if (pokemonDisponibles.find(pokemon1) != pokemonDisponibles.end()) {
                maitre->ajouterPokemon(pokemonDisponibles[pokemon1]);
            }
            
            if (pokemonDisponibles.find(pokemon2) != pokemonDisponibles.end()) {
                maitre->ajouterPokemon(pokemonDisponibles[pokemon2]);
            }
            
            maitres.push_back(maitre);
        }
        
        fichierMaitres.close();
        std::cout << maitres.size() << " maîtres Pokémon chargés." << std::endl;
    } else {
        std::cerr << "Impossible d'ouvrir le fichier maitres.csv" << std::endl;
        // Fallback: créer des maîtres par défaut
        auto maitre1 = std::make_shared<MaitrePokemon>("Peter");
        maitre1->ajouterPokemon(pokemonDisponibles["Dracolosse"]);
        maitre1->ajouterPokemon(pokemonDisponibles["Leviator"]);
        maitres.push_back(maitre1);
        
        auto maitre2 = std::make_shared<MaitrePokemon>("Agatha");
        maitre2->ajouterPokemon(pokemonDisponibles["Ectoplasma"]);
        maitre2->ajouterPokemon(pokemonDisponibles["Spectrum"]);
        maitres.push_back(maitre2);
    }
}

void Menu::chargerDonneesJoueur() {
    std::ifstream fichierJoueur("data/joueur.csv");
    
    if (fichierJoueur.is_open()) {
        std::string ligne;
        // Ignorer l'en-tête
        std::getline(fichierJoueur, ligne);
        
        if (std::getline(fichierJoueur, ligne)) {
            std::stringstream ss(ligne);
            std::string nom, badgesStr, gagnesStr, perdusStr;
            
            // Format: nom,badges,combatsGagnes,combatsPerdus
            std::getline(ss, nom, ',');
            std::getline(ss, badgesStr, ',');
            std::getline(ss, gagnesStr, ',');
            std::getline(ss, perdusStr, ',');
            
            int badges = std::stoi(badgesStr);
            int gagnes = std::stoi(gagnesStr);
            int perdus = std::stoi(perdusStr);
            
            // Créer le joueur avec le nom chargé
            joueur = std::make_shared<Joueur>(nom);
            
            // Mettre à jour les statistiques
            for (int i = 0; i < badges; ++i) {
                joueur->ajouterBadge();
            }
            
            for (int i = 0; i < gagnes; ++i) {
                joueur->incrementerCombatsGagnes();
            }
            
            for (int i = 0; i < perdus; ++i) {
                joueur->incrementerCombatsPerdus();
            }
            
            std::cout << "Données du joueur " << nom << " chargées." << std::endl;
        }
        
        fichierJoueur.close();
    } else {
        std::cerr << "Impossible d'ouvrir le fichier joueur.csv" << std::endl;
        // Si aucun fichier de sauvegarde n'existe, on garde le joueur par défaut
        if (!joueur) {
            joueur = std::make_shared<Joueur>("Dresseur");
        }
    }
}

void Menu::chargerDonnees() {
    chargerDonneesJoueur();
    chargerDonneesPokemon();
    std::cout << "Toutes les données ont été chargées avec succès !" << std::endl;
}

void Menu::afficherMenuPrincipal() const {
    std::cout << "\n====== MENU PRINCIPAL ======" << std::endl;
    std::cout << "1. Afficher mes Pokémon" << std::endl;
    std::cout << "2. Récupérer les points de vie de mes Pokémon" << std::endl;
    std::cout << "3. Changer l'ordre de mes Pokémon" << std::endl;
    std::cout << "4. Afficher mes statistiques" << std::endl;
    std::cout << "5. Affronter un leader de gym" << std::endl;
    std::cout << "6. Affronter un Maître Pokémon" << std::endl;
    std::cout << "7. Interagir avec un Pokémon ou un entraîneur" << std::endl;
    std::cout << "8. Quitter" << std::endl;
    std::cout << "Votre choix : ";
}

void Menu::executerOption(int choix) {
    switch (choix) {
        case 1:
            afficherPokemon();
            break;
        case 2:
            recupererPointsDeVie();
            break;
        case 3:
            changerOrdrePokemon();
            break;
        case 4:
            afficherStatistiques();
            break;
        case 5:
            affronterGymnase();
            break;
        case 6:
            affronterMaitrePokemon();
            break;
        case 7:
            interagirAvecEntite();
            break;
        case 8:
            // La gestion de la sortie est maintenant dans demarrer()
            // Ne rien faire ici
            break;
        default:
            std::cout << "Option invalide. Veuillez réessayer." << std::endl;
            break;
    }
}

void Menu::afficherPokemon() const {
    std::cout << "\n====== MES POKÉMON ======" << std::endl;
    joueur->afficherEquipe();
}

void Menu::recupererPointsDeVie() {
    std::cout << "\n====== RÉCUPÉRATION DES POINTS DE VIE ======" << std::endl;
    joueur->recupererPointsDeVie();
}

void Menu::changerOrdrePokemon() {
    std::cout << "\n====== CHANGER L'ORDRE DES POKÉMON ======" << std::endl;
    
    // Afficher l'équipe actuelle
    joueur->afficherEquipe();
    
    // Demander les indices des Pokémon à échanger
    int index1, index2;
    std::cout << "Entrez l'indice du premier Pokémon à échanger (1-" << joueur->getNombrePokemon() << ") : ";
    std::cin >> index1;
    
    std::cout << "Entrez l'indice du deuxième Pokémon à échanger (1-" << joueur->getNombrePokemon() << ") : ";
    std::cin >> index2;
    
    // Ajuster les indices pour le tableau (0-based)
    joueur->changerOrdrePokemon(index1 - 1, index2 - 1);
    
    // Afficher la nouvelle équipe
    std::cout << "Nouvelle composition de l'équipe :" << std::endl;
    joueur->afficherEquipe();
}

void Menu::afficherStatistiques() const {
    std::cout << "\n====== MES STATISTIQUES ======" << std::endl;
    joueur->afficherStatistiques();
}

void Menu::affronterGymnase() {
    std::cout << "\n====== AFFRONTER UN LEADER DE GYM ======" << std::endl;
    
    // Vérifier si le joueur a des Pokémon valides
    if (!joueur->aDesPokemonValides()) {
        std::cout << "Vous n'avez pas de Pokémon en état de combattre !" << std::endl;
        return;
    }
    
    // Afficher la liste des leaders disponibles
    std::cout << "Leaders disponibles :" << std::endl;
    for (size_t i = 0; i < leaders.size(); ++i) {
        std::cout << i + 1 << ". " << leaders[i]->getNom() << " (Arène de " 
                  << leaders[i]->getGymnase() << ", Badge " << leaders[i]->getBadge() << ")" << std::endl;
    }
    
    // Demander le choix du leader
    int choix;
    std::cout << "Choisissez un leader à affronter (1-" << leaders.size() << ") : ";
    std::cin >> choix;
    
    // Vérifier la validité du choix
    if (choix < 1 || choix > static_cast<int>(leaders.size())) {
        std::cout << "Choix invalide." << std::endl;
        return;
    }
    
    // Créer et démarrer le combat
    auto leaderChoisi = leaders[choix - 1];
    Combat combat(joueur, leaderChoisi);
    combat.demarrer();
    
    // Traiter le résultat du combat
    if (joueur->aDesPokemonValides() && !leaderChoisi->aDesPokemonValides()) {
        joueur->incrementerCombatsGagnes();
        joueur->ajouterBadge();
        // Ajouter le leader vaincu à la liste
        entraineursVaincus.push_back(leaderChoisi);
    } else {
        joueur->incrementerCombatsPerdus();
    }
}

void Menu::affronterMaitrePokemon() {
    std::cout << "\n====== AFFRONTER UN MAÎTRE POKÉMON ======" << std::endl;
    
    // Vérifier si le joueur a tous les badges nécessaires
    if (joueur->getNombreBadges() < 4) { // On suppose 4 badges au total
        std::cout << "Vous devez obtenir tous les badges avant de pouvoir affronter un Maître Pokémon !" << std::endl;
        std::cout << "Badges actuels : " << joueur->getNombreBadges() << "/4" << std::endl;
        return;
    }
    
    // Vérifier si le joueur a des Pokémon valides
    if (!joueur->aDesPokemonValides()) {
        std::cout << "Vous n'avez pas de Pokémon en état de combattre !" << std::endl;
        return;
    }
    
    // Afficher la liste des Maîtres disponibles
    std::cout << "Maîtres Pokémon disponibles:" << std::endl;
    for (size_t i = 0; i < maitres.size(); ++i) {
        std::cout << i + 1 << ". " << maitres[i]->getNom() << std::endl;
    }
    
    // Demander le choix du Maître
    int choix;
    std::cout << "Choisissez un Maître à affronter (1-" << maitres.size() << ") : ";
    std::cin >> choix;
    
    // Vérifier la validité du choix
    if (choix < 1 || choix > static_cast<int>(maitres.size())) {
        std::cout << "Choix invalide." << std::endl;
        return;
    }
    
    // Récupérer le Maître choisi
    int indexMaitre = choix - 1;
    
    std::cout << "Vous allez affronter le Maître Pokémon " << maitres[indexMaitre]->getNom() << " !" << std::endl;
    
    // Créer et démarrer le combat
    Combat combat(joueur, maitres[indexMaitre]);
    combat.demarrer();
    
    // Traiter le résultat du combat
    if (joueur->aDesPokemonValides() && !maitres[indexMaitre]->aDesPokemonValides()) {
        joueur->incrementerCombatsGagnes();
        std::cout << "Félicitations ! Vous avez vaincu un Maître Pokémon !" << std::endl;
        // Ajouter le maître vaincu à la liste
        entraineursVaincus.push_back(maitres[indexMaitre]);
    } else {
        joueur->incrementerCombatsPerdus();
    }
}

void Menu::interagirAvecEntite() {
    std::cout << "\n====== INTERAGIR AVEC UNE ENTITÉ ======" << std::endl;
    std::cout << "Avec qui souhaitez-vous interagir ?" << std::endl;
    std::cout << "1. Avec un de mes Pokémon" << std::endl;
    std::cout << "2. Avec un entraîneur vaincu" << std::endl;
    std::cout << "Votre choix : ";
    
    int choix;
    std::cin >> choix;
    
    switch (choix) {
        case 1: {
            // Interagir avec un Pokémon du joueur
            if (joueur->getNombrePokemon() == 0) {
                std::cout << "Vous n'avez pas de Pokémon !" << std::endl;
                return;
            }
            
            // Afficher l'équipe du joueur
            joueur->afficherEquipe();
            
            // Demander quel Pokémon
            std::cout << "Avec quel Pokémon souhaitez-vous interagir ? (1-" << joueur->getNombrePokemon() << ") : ";
            int indexPokemon;
            std::cin >> indexPokemon;
            
            if (indexPokemon < 1 || indexPokemon > static_cast<int>(joueur->getNombrePokemon())) {
                std::cout << "Choix invalide." << std::endl;
                return;
            }
            
            auto pokemon = joueur->getPokemon(indexPokemon - 1);
            pokemon->interagir();
            break;
        }
        case 2: {
            // Interagir avec un entraîneur vaincu
            if (entraineursVaincus.empty()) {
                std::cout << "Vous n'avez vaincu aucun entraîneur pour le moment !" << std::endl;
                return;
            }
            
            // Afficher la liste des entraîneurs vaincus
            std::cout << "Entraîneurs vaincus :" << std::endl;
            for (size_t i = 0; i < entraineursVaincus.size(); ++i) {
                std::cout << i + 1 << ". " << entraineursVaincus[i]->getNom() << std::endl;
            }
            
            // Demander quel entraîneur
            std::cout << "Avec quel entraîneur souhaitez-vous interagir ? (1-" << entraineursVaincus.size() << ") : ";
            int indexEntraineur;
            std::cin >> indexEntraineur;
            
            if (indexEntraineur < 1 || indexEntraineur > static_cast<int>(entraineursVaincus.size())) {
                std::cout << "Choix invalide." << std::endl;
                return;
            }
            
            entraineursVaincus[indexEntraineur - 1]->interagir();
            break;
        }
        default:
            std::cout << "Option invalide." << std::endl;
            break;
    }
}

void Menu::nouvellePartie() {
    // Demander le nom du joueur
    std::string nom;
    std::cout << "Entrez votre nom de dresseur : ";
    std::cin.ignore(); // Pour vider le buffer
    std::getline(std::cin, nom);
    if (nom.empty()) nom = "Sacha"; // Nom par défaut
    
    // Créer un nouveau joueur (avec statistiques à zéro)
    joueur = std::make_shared<Joueur>(nom);
    
    // Charger seulement les Pokémon, leaders et maîtres (pas les statistiques joueur)
    chargerDonneesPokemon();
    
    std::cout << "Nouvelle partie créée pour " << nom << " !" << std::endl;
    
    // Sauvegarder cette nouvelle partie
    sauvegarderDonneesJoueur();
}

void Menu::afficherMenuInitial() {
    std::cout << "\n====== POKEMON SIMULATOR ======" << std::endl;
    std::cout << "1. Nouvelle partie" << std::endl;
    std::cout << "2. Charger une partie existante" << std::endl;
    std::cout << "3. Quitter" << std::endl;
    std::cout << "Votre choix : ";
    
    int choix;
    std::cin >> choix;
    
    switch (choix) {
        case 1:
            nouvellePartie();
            break;
        case 2:
            chargerDonnees();
            std::cout << "Partie chargée pour " << joueur->getNom() << " !" << std::endl;
            break;
        case 3:
            std::cout << "Au revoir !" << std::endl;
            exit(0);
            break;
        default:
            std::cout << "Option invalide. Chargement d'une partie par défaut..." << std::endl;
            chargerDonnees();
            break;
    }
}

void Menu::demarrer() {
    // Afficher le menu initial
    afficherMenuInitial();
    
    // Boucle principale du menu
    int choix = 0;
    bool continuer = true;
    
    while (continuer) {
        // Afficher le menu et récupérer le choix de l'utilisateur
        afficherMenuPrincipal();
        
        // Récupérer l'entrée de l'utilisateur
        if (!(std::cin >> choix)) {
            // En cas d'erreur de lecture, réinitialiser le flux d'entrée
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrée invalide. Veuillez entrer un nombre." << std::endl;
            continue; // Revenir au début de la boucle
        }
        
        // Vider le reste du buffer après avoir lu le choix
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        // Gérer le choix de quitter
        if (choix == 8) {
            sauvegarderDonneesJoueur();
            std::cout << "Au revoir !" << std::endl;
            continuer = false; // Terminer la boucle proprement
        } else {
            // Exécuter l'option choisie
            executerOption(choix);
            
            // Pause optionnelle après chaque action pour donner le temps à l'utilisateur de lire
            std::cout << "\nAppuyez sur Entrée pour continuer...";
            std::cin.get();
        }
    }
}

void Menu::sauvegarderDonneesJoueur() {
    std::cout << "Sauvegarde des statistiques du joueur..." << std::endl;
    
    std::ofstream fichierJoueur("data/joueur.csv");
    
    if (fichierJoueur.is_open()) {
        // Écrire l'en-tête
        fichierJoueur << "nom,badges,combatsGagnes,combatsPerdus" << std::endl;
        
        // Écrire les données du joueur
        fichierJoueur << joueur->getNom() << ","
                     << joueur->getNombreBadges() << ","
                     << joueur->getCombatsGagnes() << ","
                     << joueur->getCombatsPerdus() << std::endl;
        
        fichierJoueur.close();
        std::cout << "Données du joueur sauvegardées avec succès !" << std::endl;
    } else {
        std::cerr << "Impossible d'ouvrir le fichier joueur.csv pour l'écriture" << std::endl;
    }
} 