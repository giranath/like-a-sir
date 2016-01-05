/*
 * FICHIER: BufferManager.cpp
 * PROJET:  LikeASir_fonctionnel
 *
 * AUTHEUR: Nathan
 * DATE:    2013-05-09
 *
*/

#include "BufferManager.h"

BufferManager::BufferManager() {
    
}

BufferManager::~BufferManager() {
    for(std::map<std::string, sf::SoundBuffer*>::iterator it = _buffer.begin(); it != _buffer.end(); ++it) {
        delete it->second;
    }
}

bool BufferManager::addBuffer(std::string name) {
    std::map<std::string, sf::SoundBuffer*>::iterator it = _buffer.find(name);
    
    if(it == _buffer.end())
        _buffer[name] = new sf::SoundBuffer;
    else
        return false;
    
    return true;
}

bool BufferManager::removeBuffer(std::string name) {
    std::map<std::string, sf::SoundBuffer*>::iterator it = _buffer.find(name);
    
    if(it != _buffer.end())
        delete _buffer[name];
    else 
        return false;
    
    return true;
}

bool BufferManager::loadBuffer(std::string name, std::string path) {
    std::map<std::string, sf::SoundBuffer*>::iterator it = _buffer.find(name);
    
    if(it != _buffer.end()) {
        return _buffer[name]->loadFromFile(path);        
    } 
    
    return false;
}

sf::SoundBuffer* BufferManager::getBuffer(std::string name) {
    return _buffer[name];
}