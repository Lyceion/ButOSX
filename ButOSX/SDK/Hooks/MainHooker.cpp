//
//  MainHooker.cpp
//  ButOSX
//
//  Created by Can on 29.10.2020.
//  Copyright © 2020 VersteckteKrone. All rights reserved.
//

#include "MainHooker.hpp"

void Hooker::Init() { //Load hooks.
    //Inserting GUI
    SDLHook::Init();
    GameHooker::Init();
}

void Hooker::Destroy(){ //Destroy hooks.
    //Destroying GUI
    SDLHook::Unhook();
}
