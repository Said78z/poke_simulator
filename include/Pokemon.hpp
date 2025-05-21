#ifndef POKEMON_HPP
#define POKEMON_HPP

#include <string>
#include <iostream>
#include "Interagir.hpp"

class Pokemon : public Interagir {
protected:
    std::string nom;
    int hp;
    std::string attaque;
    int puissance;
    std::string type;
    std::string typeSecondaire; // Type secondaire (optionnel)

public:
    Pokemon(const std::string& nom, int hp, const std::string& attaque, int puissance, 
            const std::string& type, const std::string& typeSecondaire = "");
    virtual ~Pokemon() = default;

    virtual std::string getType() const;
    virtual float getMultiplicateurContre(const std::string& typeAdverse) const;

    void subirDegats(int degats);
    void restaurerHP(int nouveauxHP);
    virtual void afficher() const;
    void interagir() const override;

    std::string getNom() const;
    int getHP() const;
    std::string getAttaque() const;
    int getPuissance() const;
    std::string getTypePrimaire() const;
    std::string getTypeSecondaire() const;
    bool estDoubleType() const;
};

#endif
