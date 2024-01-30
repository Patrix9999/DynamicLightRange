// Exports of event handlers

extern "C" {
	__declspec(dllexport) void Game_Entry() {}

	__declspec(dllexport) void Game_Init() {}

	__declspec(dllexport) void Game_Exit() {}

	__declspec(dllexport) void Game_PreLoop() {}

	__declspec(dllexport) void Game_Loop() {}

	__declspec(dllexport) void Game_PostLoop() {}

	__declspec(dllexport) void Game_MenuLoop() {}

	__declspec(dllexport) void Game_SaveBegin() {}

	__declspec(dllexport) void Game_SaveEnd() {}

	__declspec(dllexport) void Game_LoadBegin_NewGame() {}

	__declspec(dllexport) void Game_LoadEnd_NewGame() {}

	__declspec(dllexport) void Game_LoadBegin_SaveGame() {}

	__declspec(dllexport) void Game_LoadEnd_SaveGame() {}

	__declspec(dllexport) void Game_LoadBegin_ChangeLevel() {}

	__declspec(dllexport) void Game_LoadEnd_ChangeLevel() {}

	__declspec(dllexport) void Game_LoadBegin_Trigger() {}

	__declspec(dllexport) void Game_LoadEnd_Trigger() {}

	__declspec(dllexport) void Game_Pause() {}

	__declspec(dllexport) void Game_Unpause() {}

	__declspec(dllexport) void Game_DefineExternals() {}

	__declspec(dllexport) void Game_ApplyOptions() {}
}