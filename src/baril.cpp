/*
 * FICHIER: baril.cpp
 * PROJET:  LikeASir_fonctionnel
 *
 * AUTHEUR: Nathan
 * DATE:    2013-05-09
 *
*/

#include "baril.h"
#include "TextureManager.h"
#include "joueur.h"

baril::baril() {
    this->setTexture(*TextureManager::getInstance()->getTexture("baril"));
    this->setLargeur(8);
    this->setHauteur(16);
}

baril::~baril() {
    
}

void baril::rafraichir(float delta) {
    _active = false;
}

void baril::enCollisionAvecActeur(acteur *autre) {
    if(autre->getType() == acteur::PERSONNAGE) {
        personnage *person = dynamic_cast<personnage*>(autre);
        
        // Si la clef entre en collision 
        if(person->getTypePersonnage() == personnage::JOUEUR) {
            joueur *j = dynamic_cast<joueur*>(person);
            _active = true;
            
            if(j->getAction() && j->getCache() == false && _uniqueAction == false) {
                j->nonDetecte();
                j->setCache(true);
                j->cacher();
                _uniqueAction = true;
                
                j->setPosition(_position);
            } 
            
            else if(j->getAction() && j->getCache() == true && _uniqueAction == false) {
                j->setCache(false);
                j->devoiler();
                _uniqueAction = true;
            }
            
            else if(j->getAction() == false && _uniqueAction == true) {
                _uniqueAction = false;
            }
        }
    }
}

void baril::subitUneCollision() {
    
}