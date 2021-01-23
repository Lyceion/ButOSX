//
//  Interfaces.hpp
//  ButOSX
//
//  Created by Can Destan on 23.01.2021.
//  Copyright © 2021 VersteckteKrone. All rights reserved.
//

#ifndef Interfaces_hpp
#define Interfaces_hpp

#include <stdio.h>
extern ISurface* pSurface;
extern IPanel* pPanel;
extern ICvar* pCvar;
extern IBaseClientDLL* pClient;
extern IClientEntityList* pEntList;
extern IVDebugOverlay* pOverlay;
extern IEngineClient* pEngine;
extern IVModelInfo* pModelInfo;
extern IEngineTrace* pEngineTrace;
extern IClientMode* pClientMode;

extern VMT* paintVMT;
#endif /* Interfaces_hpp */
