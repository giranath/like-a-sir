/*
 * FICHIER: levier.cpp
 * PROJET:  LikeASir_fonctionnel
 *
 * AUTHEUR: Nathan
 * DATE:    2013-05-11
 *
*/

#include "levier.h"
#include "personnage.h"
#include "joueur.h"
#include "GestionnaireNiveau.h"
#include "trap.h"
#include "TextureManager.h"
#include "BufferManager.h"

levier::levier()
:interaction(){
    this->setLargeur(8);
    this->setHauteur(16);
    _utilise = false;
    _typeInteraction = interaction::LEVIER;
    
    _sprite.setTexture(*TextureManager::getInstance()->getTexture("levier"));
    _son.setBuffer(*BufferManager::getInstance()->getBuffer("levier"));
}

levier::~levier() {
    
}

void levier::rafraichir(float delta) {
    _active = false;
    
    if(_utilise) {
        _sprite.setTextureRect(sf::IntRect(8,0,8,8));
    } else {
        _sprite.setTextureRect(sf::IntRect(0,0,8,8));
    }
}

void levier::enCollisionAvecActeur(acteur *autre) {
    if(autre->getType() == acteur::PERSONNAGE) {
        _active = true;
        
        personnage *person = dynamic_cast<personnage*>(autre);
        
        // Si le joueur entre en collision 
        if(person->getTypePersonnage() == personnage::JOUEUR) {
            joueur *j = dynamic_cast<joueur*>(person);
            
            if(j->getAction() && _uniqueUtilisation == false) {
                _son.play();
                _uniqueUtilisation = true;
                std::vector<interaction*> interactions = gestionnaireNiveau::getInstance()->getNiveauActuel()->getInteractions();
                
                for(int i = 0 ; i < interactions.size(); i++) {
                    if(interactions[i]->getTypeInterraction() == TRAP) {
                        trap *t = dynamic_cast<trap*>(interactions[i]);
                        
                        if(t->getLevierID() == this->_levierIdentifiant) {
                            t->toggleOuvert();
                        }
                    }
                }
                
                _utilise = !_utilise;
            } else if(j->getAction() == false && _uniqueUtilisation == true) {
                _uniqueUtilisation = false;
            }
        }
    }
}

void levier::subitUneCollision() {
    
}

int levier::getLevierID() {
    return _levierIdentifiant;
}

void levier::setLevierID(int ID) {
    _levierIdentifiant = ID;
}

void levier::setUtiliser(bool val) {
    _utilise = val;
    
    std::vector<interaction*> interactions = gestionnaireNiveau::getInstance()->getNiveauActuel()->getInteractions();
    
    for(int i = 0 ; i < interactions.size(); i++) {
        if(interactions[i]->getTypeInterraction() == TRAP) {
            trap *t = dynamic_cast<trap*>(interactions[i]);
            
            if(_utilise == false) {
                if(t->getOuvertureDefaut() == true)
                    t->ouvrir();
                else
                    t->fermer();
            }
            else { 
                if(t->getOuvertureDefaut() == true)
                    t->fermer();
                else
                    t->ouvrir();
            }
        }
    }

}