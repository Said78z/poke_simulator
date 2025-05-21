#include "Pokemon.hpp"
#include <map>
#include <iostream>

Pokemon::Pokemon(const std::string& nom, int hp, const std::string& attaque, int puissance,
                 const std::string& type, const std::string& typeSecondaire)
    : nom(nom), hp(hp), attaque(attaque), puissance(puissance), 
      type(type), typeSecondaire(typeSecondaire) {}

std::string Pokemon::getType() const {
    if (typeSecondaire.empty()) {
        return type;
    } else {
        return type + "/" + typeSecondaire;
    }
}

std::string Pokemon::getTypePrimaire() const {
    return type;
}

std::string Pokemon::getTypeSecondaire() const {
    return typeSecondaire;
}

bool Pokemon::estDoubleType() const {
    return !typeSecondaire.empty();
}

float Pokemon::getMultiplicateurContre(const std::string& typeAdverse) const {
    // Définir les multiplicateurs de dégâts pour chaque type
    // Cette implémentation est simplifiée et basée sur le tableau du sujet
    static std::map<std::string, std::map<std::string, float>> multiplicateurs = {
        // Format: {type attaquant, {type défenseur, multiplicateur}}
        {"Feu", {
            {"Feu", 0.5f}, {"Eau", 0.5f}, {"Plante", 2.0f}, {"Glace", 2.0f}, 
            {"Insecte", 2.0f}, {"Acier", 2.0f}, {"Fée", 1.0f}, {"Roche", 0.5f},
            {"Sol", 0.5f}, {"Poison", 1.0f}, {"Vol", 1.0f}
        }},
        {"Eau", {
            {"Feu", 2.0f}, {"Eau", 0.5f}, {"Plante", 0.5f}, {"Glace", 1.0f},
            {"Acier", 1.0f}, {"Roche", 2.0f}, {"Sol", 2.0f}, {"Vol", 1.0f},
            {"Électrik", 1.0f}, {"Poison", 1.0f}
        }},
        {"Plante", {
            {"Feu", 0.5f}, {"Eau", 2.0f}, {"Plante", 0.5f}, {"Glace", 1.0f},
            {"Poison", 0.5f}, {"Vol", 0.5f}, {"Insecte", 0.5f}, {"Roche", 2.0f},
            {"Sol", 2.0f}, {"Acier", 0.5f}, {"Électrik", 1.0f}
        }},
        {"Poison", {
            {"Plante", 2.0f}, {"Fée", 2.0f}, {"Combat", 1.0f}, {"Poison", 0.5f}, 
            {"Sol", 0.5f}, {"Roche", 0.5f}, {"Acier", 0.0f}
        }},
        {"Vol", {
            {"Électrik", 0.5f}, {"Glace", 0.5f}, {"Roche", 0.5f}, {"Combat", 2.0f},
            {"Insecte", 2.0f}, {"Plante", 2.0f}, {"Sol", 2.0f}
        }},
        {"Électrik", {
            {"Eau", 2.0f}, {"Vol", 2.0f}, {"Sol", 0.0f}, {"Électrik", 0.5f},
            {"Acier", 1.0f}
        }},
        {"Dragon", {
            {"Dragon", 2.0f}, {"Glace", 0.5f}, {"Fée", 0.0f}
        }},
        {"Spectre", {
            {"Spectre", 2.0f}, {"Psy", 2.0f}, {"Normal", 0.0f}, {"Combat", 0.0f}
        }},
        {"Roche", {
            {"Feu", 2.0f}, {"Vol", 2.0f}, {"Insecte", 2.0f}, {"Combat", 0.5f},
            {"Sol", 0.5f}, {"Acier", 0.5f}
        }},
        {"Sol", {
            {"Électrik", 2.0f}, {"Roche", 2.0f}, {"Acier", 2.0f}, {"Poison", 2.0f},
            {"Vol", 0.0f}, {"Plante", 0.5f}, {"Insecte", 0.5f}
        }}
    };

    // Calculer le multiplicateur pour le type primaire
    float multiplicateurPrimaire = 1.0f;
    if (multiplicateurs.find(type) != multiplicateurs.end() && 
        multiplicateurs[type].find(typeAdverse) != multiplicateurs[type].end()) {
        multiplicateurPrimaire = multiplicateurs[type][typeAdverse];
    }

    // Si pas de type secondaire, retourner directement le multiplicateur primaire
    if (typeSecondaire.empty()) {
        return multiplicateurPrimaire;
    }

    // Calculer le multiplicateur pour le type secondaire
    float multiplicateurSecondaire = 1.0f;
    if (multiplicateurs.find(typeSecondaire) != multiplicateurs.end() && 
        multiplicateurs[typeSecondaire].find(typeAdverse) != multiplicateurs[typeSecondaire].end()) {
        multiplicateurSecondaire = multiplicateurs[typeSecondaire][typeAdverse];
    }

    // Pour un Pokémon à double type, on multiplie les deux multiplicateurs
    return multiplicateurPrimaire * multiplicateurSecondaire;
}

void Pokemon::subirDegats(int degats) {
    hp -= degats;
    if (hp < 0) hp = 0;
}

void Pokemon::restaurerHP(int nouveauxHP) {
    hp = nouveauxHP;
}

void Pokemon::afficher() const {
    if (typeSecondaire.empty()) {
        std::cout << nom << " (" << type << ") - HP: " << hp
                  << ", Attaque: " << attaque << " (" << puissance << ")";
    } else {
        std::cout << nom << " (" << type << "/" << typeSecondaire << ") - HP: " << hp
                  << ", Attaque: " << attaque << " (" << puissance << ")";
    }
}

void Pokemon::interagir() const {
    if (typeSecondaire.empty()) {
        std::cout << "Le Pokémon " << nom << " de type " << type << " fait un bruit caractéristique !" << std::endl;
    } else {
        std::cout << "Le Pokémon " << nom << " de type " << type << "/" << typeSecondaire 
                  << " vous fait une démonstration de ses pouvoirs combinés !" << std::endl;
        
        if (type == "Plante" && typeSecondaire == "Poison") {
            std::cout << "Il libère un doux parfum toxique qui provient de ses feuilles !" << std::endl;
        } else if (type == "Eau" && typeSecondaire == "Vol") {
            std::cout << "Il s'élève dans les airs et fait tomber quelques gouttes d'eau !" << std::endl;
        } else if (type == "Dragon" && typeSecondaire == "Vol") {
            std::cout << "Il rugit puissamment en déployant ses ailes majestueuses !" << std::endl;
        }
    }
}

std::string Pokemon::getNom() const { return nom; }
int Pokemon::getHP() const { return hp; }
std::string Pokemon::getAttaque() const { return attaque; }
int Pokemon::getPuissance() const { return puissance; }
