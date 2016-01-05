/*
 * FICHIER: interaction.cpp
 * PROJET:  LikeASir
 *
 * AUTHEUR: Nathan
 * DATE:    2013-04-23
 *
*/

#include "interaction.h"
#include "TextureManager.h"

interaction::interaction()
:acteur()
{
    _type = INTERACTIONNABLE;
    _typeInteraction = NON_DEFINI;
}

interaction::interaction(interaction const& copy) {
    _largeur = copy._largeur;
    _hauteur = copy._hauteur;
    _id = copy._id;
    
    _vivant = copy._vivant;
    _visible = copy._visible;
    
    _type = copy._type;
    
    _typeInteraction = copy._typeInteraction;
}

interaction::~interaction() {

}

interaction::typeInteraction interaction::getTypeInterraction() {
    return _typeInteraction;
}

void interaction::afficher(sf::RenderTarget *destination) {
    acteur::afficher(destination);
    
    if(_active) {
        sf::Sprite iconSprite;
        iconSprite.setTexture(*TextureManager::getInstance()->getTexture("actionIcon"));
        
        iconSprite.setPosition(_position.x, _position.y - 8);
        destination->draw(iconSprite);
    }
}