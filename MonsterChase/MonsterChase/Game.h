#pragma once
#include"GLib.h"
#include"SmartPtr.h"
#include"Collision.h"
#include"Vector3.h"

class GameObject;
//class Vector3;
class Physics;

namespace Game {

	bool StartUp(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow, SmartPtr<GameObject> Player, SmartPtr<GameObject> Player2, std::vector<SmartPtr<GameObject>> & Enemies);
	void Run(Vector3 &Force, SmartPtr<GameObject> Player, Physics & physics, SmartPtr<GameObject> Player2, Collision & collision, std::vector<SmartPtr<GameObject>> & Enemies);
	void CreateBullet(SmartPtr<GameObject> Player);
	void ShutDown();
	void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown);
	GLib::Sprites::Sprite * CreateSprite(const char * i_pFilename, SmartPtr<GameObject> Player);
	void * LoadFile(const char * i_pFilename, size_t & o_sizeFile);

};