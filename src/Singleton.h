//
//  Singleton.h
//  EngineShooter2D
//
//  Created by Nathan on 2012-12-22.
//  Copyright (c) 2012 Nathan. All rights reserved.
//

#ifndef __EngineShooter2D__Singleton__
#define __EngineShooter2D__Singleton__

#include <iostream>

template <typename T>

class Singleton{
protected:
    Singleton() {};
    ~Singleton() {};
    
public:
    static T *getInstance ()
    {
        if (NULL == _singleton)
        {
            _singleton = new T;
        }
    
        return (static_cast<T*> (_singleton));
    }
    
private:
     static T *_singleton;
};

template <typename T>
T *Singleton<T>::_singleton = NULL;

#endif /* defined(__EngineShooter2D__Singleton__) */
