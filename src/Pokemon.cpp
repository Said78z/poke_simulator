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
    // Définir les multiplicateurs de dégâts pour chaque type selon le tableau fourni
    // Format: {type défenseur, {type attaquant, multiplicateur}}
    static std::map<std::string, std::map<std::string, float>> multiplicateurs = {
        {"Feu", {
            {"Eau", 2.0f}, {"Roche", 2.0f}, {"Sol", 2.0f},
            {"Plante", 0.5f}, {"Glace", 0.5f}, {"Insecte", 0.5f}, {"Acier", 0.5f}, {"Fée", 0.5f}
        }},
        {"Eau", {
            {"Plante", 2.0f}, {"Électrik", 2.0f},
            {"Feu", 0.5f}, {"Eau", 0.5f}, {"Glace", 0.5f}, {"Acier", 0.5f}
        }},
        {"Plante", {
            {"Feu", 2.0f}, {"Glace", 2.0f}, {"Poison", 2.0f}, {"Vol", 2.0f}, {"Insecte", 2.0f},
            {"Eau", 0.5f}, {"Sol", 0.5f}, {"Roche", 0.5f}
        }},
        {"Électrik", {
            {"Sol", 2.0f},
            {"Vol", 0.5f}, {"Acier", 0.5f}, {"Électrik", 0.5f}
        }},
        {"Glace", {
            {"Feu", 2.0f}, {"Combat", 2.0f}, {"Roche", 2.0f}, {"Acier", 2.0f},
            {"Glace", 0.5f}
        }},
        {"Combat", {
            {"Vol", 2.0f}, {"Psy", 2.0f}, {"Fée", 2.0f},
            {"Roche", 0.5f}, {"Insecte", 0.5f}, {"Ténèbres", 0.5f}
        }},
        {"Poison", {
            {"Sol", 2.0f}, {"Psy", 2.0f},
            {"Plante", 0.5f}, {"Fée", 0.5f}, {"Combat", 0.5f}, {"Poison", 0.5f}, {"Insecte", 0.5f}
        }},
        {"Sol", {
            {"Eau", 2.0f}, {"Plante", 2.0f}, {"Glace", 2.0f},
            {"Poison", 0.5f}, {"Roche", 0.5f}
        }},
        {"Vol", {
            {"Électrik", 2.0f}, {"Glace", 2.0f}, {"Roche", 2.0f},
            {"Plante", 0.5f}, {"Combat", 0.5f}, {"Insecte", 0.5f}
        }},
        {"Psy", {
            {"Insecte", 2.0f}, {"Spectre", 2.0f}, {"Ténèbres", 2.0f},
            {"Combat", 0.5f}, {"Psy", 0.5f}
        }},
        {"Insecte", {
            {"Feu", 2.0f}, {"Vol", 2.0f}, {"Roche", 2.0f},
            {"Plante", 0.5f}, {"Combat", 0.5f}, {"Sol", 0.5f}
        }},
        {"Roche", {
            {"Eau", 2.0f}, {"Plante", 2.0f}, {"Combat", 2.0f}, {"Sol", 2.0f}, {"Acier", 2.0f},
            {"Feu", 0.5f}, {"Vol", 0.5f}, {"Poison", 0.5f}, {"Normal", 0.5f}
        }},
        {"Spectre", {
            {"Spectre", 2.0f}, {"Ténèbres", 2.0f},
            {"Poison", 0.5f}, {"Insecte", 0.5f}
        }},
        {"Dragon", {
            {"Glace", 2.0f}, {"Dragon", 2.0f}, {"Fée", 2.0f},
            {"Feu", 0.5f}, {"Eau", 0.5f}, {"Électrik", 0.5f}, {"Plante", 0.5f}
        }},
        {"Ténèbres", {
            {"Combat", 2.0f}, {"Insecte", 2.0f}, {"Fée", 2.0f},
            {"Spectre", 0.5f}, {"Psy", 0.5f}, {"Ténèbres", 0.5f}
        }},
        {"Acier", {
            {"Feu", 2.0f}, {"Combat", 2.0f}, {"Sol", 2.0f},
            {"Normal", 0.5f}, {"Plante", 0.5f}, {"Glace", 0.5f}, {"Vol", 0.5f}, {"Psy", 0.5f},
            {"Insecte", 0.5f}, {"Roche", 0.5f}, {"Dragon", 0.5f}, {"Acier", 0.5f}, {"Fée", 0.5f}
        }},
        {"Fée", {
            {"Poison", 2.0f}, {"Acier", 2.0f},
            {"Combat", 0.5f}, {"Insecte", 0.5f}, {"Ténèbres", 0.5f}, {"Dragon", 0.5f}
        }},
        {"Normal", {
            {}, // Pas de faiblesses spécifiques
            {} // Pas de résistances spécifiques
        }}
    };

    // Ajout des immunités (multiplicateur 0)
    multiplicateurs["Vol"]["Sol"] = 0.0f;           // Vol est immunisé contre Sol
    multiplicateurs["Normal"]["Spectre"] = 0.0f;    // Normal est immunisé contre Spectre
    multiplicateurs["Spectre"]["Normal"] = 0.0f;    // Spectre est immunisé contre Normal
    multiplicateurs["Spectre"]["Combat"] = 0.0f;    // Spectre est immunisé contre Combat
    multiplicateurs["Électrik"]["Sol"] = 0.0f;      // Sol est immunisé contre Électrik
    multiplicateurs["Acier"]["Poison"] = 0.0f;      // Acier est immunisé contre Poison
    multiplicateurs["Fée"]["Dragon"] = 0.0f;        // Fée est immunisé contre Dragon

    // Analyser le type adverse pour vérifier s'il s'agit d'un type double
    std::string typePrimaireAdverse = typeAdverse;
    std::string typeSecondaireAdverse = "";
    
    size_t separatorPos = typeAdverse.find('/');
    if (separatorPos != std::string::npos) {
        typePrimaireAdverse = typeAdverse.substr(0, separatorPos);
        typeSecondaireAdverse = typeAdverse.substr(separatorPos + 1);
    }
    
    // Calculer le multiplicateur pour le type primaire adverse
    float multiplicateurPrimaire = 1.0f;
    if (multiplicateurs.find(typePrimaireAdverse) != multiplicateurs.end() && 
        multiplicateurs[typePrimaireAdverse].find(type) != multiplicateurs[typePrimaireAdverse].end()) {
        multiplicateurPrimaire = multiplicateurs[typePrimaireAdverse][type];
    }
    
    // S'il n'y a pas de type secondaire, retourner directement le multiplicateur primaire
    if (typeSecondaireAdverse.empty()) {
        return multiplicateurPrimaire;
    }
    
    // Calculer le multiplicateur pour le type secondaire adverse
    float multiplicateurSecondaire = 1.0f;
    if (multiplicateurs.find(typeSecondaireAdverse) != multiplicateurs.end() && 
        multiplicateurs[typeSecondaireAdverse].find(type) != multiplicateurs[typeSecondaireAdverse].end()) {
        multiplicateurSecondaire = multiplicateurs[typeSecondaireAdverse][type];
    }
    
    // Pour un Pokémon à double type défenseur, on multiplie les multiplicateurs
    // C'est la règle dans les jeux Pokémon (ex: type Eau contre Plante/Vol = 0.5 * 2 = 1.0)
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
