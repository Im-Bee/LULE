#ifndef LULE_ENTRY_H
#define LULE_ENTRY_H

#ifdef _WIN32
#include "LULE_Multiplatform.h"

INT CALLBACK wWinMain(
    _In_	 HINSTANCE hInst,
    _In_opt_ HINSTANCE hInstPrev,
    _In_	 LPWSTR cmdline,
    _In_	 INT cmdshow) {
    
    auto* app = LULE::EntryApplication();
    app->Initialize();

    MSG msg = { 0 };
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        app->Update();
    }

    app->Destroy();
}

#endif // _WIN32

#endif // !LULE_ENTRY_H