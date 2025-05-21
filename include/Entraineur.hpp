#ifndef ENTRAINEUR_HPP
#define ENTRAINEUR_HPP

#include <string>
#include <vector>
#include <memory>
#include "Pokemon.hpp"
#include "Interagir.hpp"

class Entraineur : public Interagir {
protected:
    std::string nom;
    std::vector<std::shared_ptr<Pokemon>> equipe;

public:
    Entraineur(const std::string& nom);
    virtual ~Entraineur() = default;

    // Méthodes pour gérer l'équipe de Pokémon
    void ajouterPokemon(std::shared_ptr<Pokemon> pokemon);
    std::shared_ptr<Pokemon> getPokemon(int index) const;
    size_t getNombrePokemon() const;
    bool aDesPokemonValides() const;
    
    // Implémentation de la méthode de l'interface Interagir
    void interagir() const override;
    
    // Méthodes d'accès
    std::string getNom() const;
    void afficherEquipe() const;
};

#endif 