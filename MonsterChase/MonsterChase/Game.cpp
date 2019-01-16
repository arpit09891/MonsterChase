#include"Game.h"
#include"Debug.h"
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>
#include"Engine.h"
#include <crtdbg.h>
#include"GameObject.h"
#include"Physics.h"
#include"Vector3.h"
#include"Point2D.h"
#include"Timer.h"
#include"SmartPtr.h"
#include"ProcessFile.h"
#include"Vector4.h"
#include"Matrix.h"
#include<string>

namespace Game {

	GLib::Sprites::Sprite * pGoodGuy;
	GLib::Sprites::Sprite * pBadGuy;
	GLib::Sprites::Sprite * pBullet;
	GLib::Sprites::Sprite * pTimer;
	Vector3 *Force;
	int PhysicsCounter = 0;
	int flag = 0;
	int BulletRespawn = 1;
	//Vector3 worldpBadGuy = Vector3(180.0f,-100.0f, 0.0f);
	
}

bool Game::StartUp(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow, SmartPtr<GameObject> Player, SmartPtr<GameObject> Bullet, std::vector<SmartPtr<GameObject>> & Enemies) {
	bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600);
	if (bSuccess)
	{
		// Set a callback for notification of key presses
		

		// Create a couple of sprites using our own helper routine CreateSprite
		
		pGoodGuy = CreateSprite("data\\PlayerShip.dds", Player);
		pBadGuy = CreateSprite("data\\EnemyShip.dds", Enemies[0]);
		pBullet = CreateSprite("data\\Bullet.dds",Bullet);
		Player->SetPosition(Vector3(0.0f, -300.0f, 0.0f));
		Player->SetAlive(1);
		//Bullet->SetPosition(Vector3(-350, 200, 0.0f));
		for (int i = 0; i < 8; i++)
		{
			Enemies[i]->SetBB(Enemies[0]->GetBB());
			Enemies[i]->SetPosition(Vector3((-350+ i*100), 200, 0.0f));
			Enemies[i]->SetVelocity(Vector3(0.0f, 0.0f, 0.0f));
			Enemies[i]->SetAlive(1);
		}
		for (int i = 8;i < 17;i++) {

		}
		return true;
	}
	
	else
		return false;
}

void Game::TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
{
	
	//Point2D temp;
	if (bWentDown == true) {
		switch (i_VKeyID)
		{
		case 87:
			//Up
			flag = 1;

			PhysicsCounter++;
			break;

		case 83:
			//Down
			flag = 2;
			
			PhysicsCounter++;
			break;

		case 68:
			//right
			flag = 3;
			
			PhysicsCounter++;
			break;

		case 65:
			//left
			flag = 4;
			
			PhysicsCounter++;
			break;

		default:
			printf_s("Invalid Input");
			break;
		}
	}
	else
		flag = 0;
	
}

GLib::Sprites::Sprite * Game::CreateSprite(const char * i_pFilename, SmartPtr<GameObject> Player) {
	assert(i_pFilename, "i_pFilename is null");

	size_t sizeTextureFile = 0;

	// Load the source file (texture data)
	void * pTextureFile = LoadFile(i_pFilename, sizeTextureFile);

	// Ask GLib to create a texture out of the data (assuming it was loaded successfully)
	assert(pTextureFile, "its null");

 	GLib::Texture * pTexture = pTextureFile ? GLib::CreateTexture(pTextureFile, sizeTextureFile) : nullptr;

	// exit if something didn't work
	// probably need some debug logging in here!!!!
	if (pTextureFile)
		delete[] pTextureFile;

	if (pTexture == nullptr)
		return NULL;

	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int depth = 0;

	// Get the dimensions of the texture. We'll use this to determine how big it is on screen
	bool result = GLib::GetDimensions(pTexture, width, height, depth);
	assert(result == true, "There are no dimension");
	assert((width > 0) && (height > 0), "Height and width are negative");

	// Define the sprite edges
	GLib::Sprites::SpriteEdges	Edges = { -float(width / 2.0f), float(height), float(width / 2.0f), 0.0f };
	GLib::Sprites::SpriteUVs	UVs = { { 0.0f, 0.0f },{ 1.0f, 0.0f },{ 0.0f, 1.0f },{ 1.0f, 1.0f } };
	GLib::RGBA							Color = { 255, 255, 255, 255 };
	BoundingBox tempBB = BoundingBox();
	tempBB.Center = Vector3(0.0f,height/2, 0.0f);
	tempBB.Extends = Vector3(width/2, height/2, 0.0f);

	Player->SetBB(tempBB);
	// Create the sprite
	GLib::Sprites::Sprite * pSprite = GLib::Sprites::CreateSprite(Edges, 0.1f, Color, UVs);
	if (pSprite == nullptr)
	{
		GLib::Release(pTexture);
		return nullptr;
	}

	// Bind the texture to sprite
	GLib::Sprites::SetTexture(*pSprite, *pTexture);

	return pSprite;
}

// loading file specifically sprites
void * Game::LoadFile(const char * i_pFilename, size_t & o_sizeFile) {
	assert(i_pFilename != NULL, "Filename is null");

	FILE * pFile = NULL;

	errno_t fopenError = fopen_s(&pFile, i_pFilename, "rb");
	if (fopenError != 0)
		return NULL;

	assert(pFile != NULL, "pFile is null");

	int FileIOError = fseek(pFile, 0, SEEK_END);
	assert(FileIOError == 0, "There is FileIOError");

	long FileSize = ftell(pFile);
	assert(FileSize >= 0, "FileSize is in negative");

	FileIOError = fseek(pFile, 0, SEEK_SET);
	assert(FileIOError == 0, "There is FileIOError");

	uint8_t * pBuffer = new uint8_t[FileSize];
	assert(pBuffer, "pBuffer has problem");

	size_t FileRead = fread(pBuffer, 1, FileSize, pFile);
	assert(FileRead == FileSize, "FileRead is not equal to FileSize");

	fclose(pFile);

	o_sizeFile = FileSize;

	return pBuffer;
}

void Game::Run(Vector3 &Force, SmartPtr<GameObject> Player, Physics & physics, SmartPtr<GameObject> Bullet, Collision & collision, std::vector<SmartPtr<GameObject>> & Enemies) {
	
	char test[500];
	size_t	lenBuffer = 65;
	float dt = Timer::CalcLastFrameTime();
	/*sprintf_s(test, lenBuffer, "\n dt Value %f \n", dt);
	OutputDebugStringA(test);*/
	int flagBullet = 0;
	
	GLib::SetKeyStateChangeCallback(TestKeyCallback);
	switch (flag)
	{
		case 1:flagBullet =1;
		break;
		case 2://Force.SetY(-2.50f);
		break;
		case 3:Force.SetX(2.50f);
		break;
		case 4:Force.SetX(-2.50f);
		break;
		default:
			printf_s("Invalid Input");
			break;
	}
	flag = 0;
	//Vector4 pointShip = Vector4(Player->GetPosition().GetX(), Player->GetPosition().GetY(), 0, 1);
	if (flagBullet == 1 && Bullet->GetAlive() == 0)
	{
		Bullet->SetAlive(1);
		Bullet->SetVelocity(Vector3(0.0f, 0.05f, 0.0f));
		Bullet->SetPosition(Vector3(Player->GetPosition().GetX(),(Player->GetPosition().GetY()+100), 0.0f));
	}
	if (PhysicsCounter > 0) {
		
		physics.Update(Force, dt);		
		
		bool IsCollision = false;
		for (int i = 0;i < 8; i++) {
			IsCollision = collision.CheckCollision(Bullet, Enemies[i], dt);			
			if (IsCollision)
			{
				BulletRespawn = 1;
				Enemies[i]->SetAlive(0);
				Bullet->SetAlive(0);
				Engine::MessagingSystem * temp = Engine::MessagingSystem::GetInstance();
				temp->SendMessageHandler("PlayerHit");
			}
			else
			{
				
			}			
		}
	}

	BoundingBox tempBB = BoundingBox();
	tempBB.Center = Vector3(0.0f, 0.0f, 0.0f);
	tempBB.Extends = Vector3(0.0f, 0.0f, 0.0f);
	//pTimer = CreateSprite("data\\PlayerShip.dds", Enemies[16]);
			
	// Tell GLib that we want to start rendering
	GLib::BeginRendering();
	// Tell GLib that we want to render some sprites
	GLib::Sprites::BeginRendering();
	for (int i = 0; i < 8; i++) {
		if (pBadGuy && Enemies[i]->GetAlive() == 1)
		{
			static float			moveDist = .01f;
			static float			moveDir = moveDist;
			//float tempVel = moveDist / dt;
			
			GLib::Point2D	Offset = { Enemies[i]->GetPosition().GetX(), Enemies[i]->GetPosition().GetY() };

			GLib::Sprites::RenderSprite(*pBadGuy, Offset, 0.0f);
		}
		if (Enemies[i]->GetAlive()==0) {
			
			Enemies[i]->SetBB(tempBB);

		}
	}
	if (pGoodGuy)
	{		
		static GLib::Point2D	Offset;

		Vector3 temp = Player->GetPosition();

		Offset.x = temp.GetX();

		Offset.y = temp.GetY();
				
		if (Offset.x > 350) {
			Offset.x = -350;
			Player->SetPosition(Vector3(Offset.x,-300,0));
		}
		else if (Offset.x < -350) {
			Offset.x = 350;
			Player->SetPosition(Vector3(Offset.x, -300, 0));
		}		

		// Tell GLib to render this sprite at our calculated location
		GLib::Sprites::RenderSprite(*pGoodGuy, Offset, 0.0f);
	}	
	

	if (pBullet && Bullet->GetAlive()== 1)
	{
		static GLib::Point2D	Offset;
		Offset.x = Bullet->GetPosition().GetX();
		Offset.y = Bullet->GetPosition().GetY();
		Offset.y += 0.05f;
		Bullet->SetPosition(Vector3(Offset.x,Offset.y,0.0f));
		if (Offset.y >= 260)
		{
			Bullet->SetAlive(0);
		}	
		float tempVel = 0.05f/ dt;
		
		GLib::Sprites::RenderSprite(*pBullet, Offset, 0.0f);
	}

	//static GLib::Point2D Offset;

	//Offset.x = 0;
	//Offset.y = 0;
	//int timerString = 1;
	//std::string text = "data\\";
	//text = text + std::to_string(timerString);
	//text = text + ".dds";
	//if (!pTimer) {
	//	
	//	GLib::Sprites::RenderSprite(*pTimer, Offset, 0.0f);
	//}
	// Tell GLib we're done rendering sprites
	GLib::Sprites::EndRendering();
	// Tell GLib we're done rendering
	GLib::EndRendering();
}
	


void Game::ShutDown() {
	
	if (pGoodGuy)
		GLib::Sprites::Release(pGoodGuy);
	if (pBadGuy)
		GLib::Sprites::Release(pBadGuy);
	if (pBullet)
		GLib::Sprites::Release(pBullet);
	if (pTimer)
		GLib::Sprites::Release(pTimer);
	GLib::Shutdown();
}

