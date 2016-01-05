/*
 * FICHIER: TextureManager.cpp
 * PROJET:  Amanita
 *
 * AUTHEUR: Nathan
 * DATE:    2013-04-28
 *
*/

#include "TextureManager.h"
 
TextureManager::TextureManager() {
    
}

TextureManager::~TextureManager() {
    for(std::map<std::string, sf::Texture*>::iterator it = _textures.begin(); it != _textures.end(); ++it) {
        delete it->second;
    }
}

bool TextureManager::addTexture(std::string name) {
    std::map<std::string, sf::Texture*>::iterator it = _textures.find(name);
    
    if(it == _textures.end())
        _textures[name] = new sf::Texture;
    else
        return false;
    
    return true;
}

bool TextureManager::removeTexture(std::string name) {
    std::map<std::string, sf::Texture*>::iterator it = _textures.find(name);
    
    if(it != _textures.end())
        delete _textures[name];
    else 
        return false;
    
    return true;
}

bool TextureManager::loadTexture(std::string name, std::string path) {
    std::map<std::string, sf::Texture*>::iterator it = _textures.find(name);
    
    if(it != _textures.end()) {
        return _textures[name]->loadFromFile(path);        
    } 
    
    return false;
}

sf::Texture* TextureManager::getTexture(std::string name) {
    return _textures[name];
}