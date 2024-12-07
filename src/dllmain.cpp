#include <Windows.h>
#include <../zGothicAPI.h>

#ifdef __G1
namespace Gothic_I_Classic
{
    extern void Game_EntryPoint();
}
#endif

#ifdef __G1A
namespace Gothic_I_Addon
{
    extern void Game_EntryPoint();
}
#endif

#ifdef __G2
namespace Gothic_II_Classic
{
    extern void Game_EntryPoint();
}
#endif

#ifdef __G2A
namespace Gothic_II_Addon
{
    extern void Game_EntryPoint();
}
#endif

BOOL WINAPI DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // Initialize once for each new process.
            // Return FALSE to fail DLL load.

            switch (GetGameVersion())
            {
#ifdef __G1
                case Engine_G1:
                    Gothic_I_Classic::Game_EntryPoint();
                    break;
#endif

#ifdef __G1A
                case Engine_G1A:
                    Gothic_I_Addon::Game_EntryPoint();
                    break;
#endif

#ifdef __G2
                case Engine_G2:
                    Gothic_II_Classic::Game_EntryPoint();
                    break;
#endif

#ifdef __G2A
                case Engine_G2A:
                    Gothic_II_Addon::Game_EntryPoint();
                    break;
#endif
            }
            break;

        case DLL_PROCESS_DETACH:
            if (lpvReserved != nullptr)
                break; // do not do cleanup if process termination scenario

            // Perform any necessary cleanup.
            break;

        case DLL_THREAD_ATTACH:
            // Do thread-specific initialization.
            break;

        case DLL_THREAD_DETACH:
            // Do thread-specific cleanup.
            break;
    }

	return TRUE;
}