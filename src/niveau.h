/*
 * FICHIER: Niveau.h
 * PROJET:  ProtoNinja
 *
 * AUTHEUR: Nathan
 * DATE:    2013-04-22
 *
 * Classe gérant un niveau. C'est à dire une matrice de tuiles et une liste d'acteur
 */

#ifndef __ProtoNinja__Niveau__
#define __ProtoNinja__Niveau__

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "acteur.h"

#include "personnage.h"
#include "interaction.h"
#include "joueur.h"

using namespace std;

// Une tuile
struct tuile {
    int identifiant;        // Identifiant de la tuile
    sf::Sprite _sprite;     // Image de la tuile
    bool mur;               // Peut-on passer à travers?
};

// Un niveau
class niveau {
private:
    int _largeur, _hauteur; // En nombre de bloc
    vector<vector<tuile> > _tuiles; // Un matrice de tuile
    std::list<acteur*> _acteurs;
    
    sf::Vector2i _entree, _sortie;
    sf::Color _backColor;
    
public:
    niveau();
    niveau(niveau const&copy);
    ~niveau();
    
    bool init(int largeur, int hauteur);
    
    tuile* getTuile(int x, int y);
    bool setTuile(int x, int y, tuile tuile);
    
    void ajouterActeur(acteur *acteur);
    
    void rafraichir(float delta);
    
    int getLargeur() const;
    int getHauteur() const;
    
    void setEntree(int x, int y);
    void setEntree(sf::Vector2i pos);

    void setSortie(int x, int y);
    void setSortie(sf::Vector2i pos);

    sf::Vector2i getEntree();
    sf::Vector2i getSortie();
    
    void setBackColor(int r, int g, int b);
    sf::Color getBackColor();
    
    void recharger();

    void afficherActeur(sf::RenderTarget &target);
    
    std::vector<interaction*> getInteractions();
};

#endif /* defined(__ProtoNinja__Niveau__) */
