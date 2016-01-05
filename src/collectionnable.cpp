/*
 * FICHIER: collectionnable.cpp
 * PROJET:  LikeASir
 *
 * AUTHEUR: Nathan
 * DATE:    2013-04-23
 *
*/

#include "collectionnable.h"

collectionnable::collectionnable()
:acteur()
{
    _type = COLLECTIONNABLE;
    _typeCollectionnable = NON_DEFINI;
}

collectionnable::collectionnable(collectionnable const& copy) {
    _largeur = copy._largeur;
    _hauteur = copy._hauteur;
    _id = copy._id;
    
    _vivant = copy._vivant;
    _visible = copy._visible;
    
    _type = copy._type;
    
    _typeCollectionnable = copy._typeCollectionnable;
}

collectionnable::~collectionnable() {
    
}

collectionnable::typeCollectionnable collectionnable::getTypeCollectionnable() {
    return _typeCollectionnable;
}

