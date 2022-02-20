#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"

//components are in gameObject.h

using namespace std;

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void dae::Minigin::Initialize()
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	
	auto go = std::make_shared<GameObject>();
	go->AddComponent<TextureComponent>();
	go->GetComponent<TextureComponent>()->SetTexture("background.jpg");
	go->AddComponent<RenderComponent>();
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent<TextureComponent>();
	go->GetComponent<TextureComponent>()->SetTexture("logo.png");
	go->GetComponent<TextureComponent>()->SetPosition(216, 180);
	go->AddComponent<RenderComponent>();
	scene.Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<GameObject>();
	go->AddComponent<TextComponent>("Programming 4 Assignment", font);
	go->GetComponent<TextComponent>()->SetPosition(80, 20);
	go->AddComponent<RenderComponent>();
	scene.Add(go);

	auto font2 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	go = std::make_shared<GameObject>();
	go->AddComponent<FpsComponent>();
	go->AddComponent<TextComponent>("60 FPS", font2);
	go->GetComponent<TextComponent>()->SetPosition(10, 10);
	go->GetComponent<TextComponent>()->SetColor(255, 255, 0);
	go->AddComponent<RenderComponent>();
	scene.Add(go);
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		auto lastTime = std::chrono::high_resolution_clock::now();
		while (doContinue)
		{
			const auto currentTime = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
			lastTime = currentTime;

			doContinue = input.ProcessInput();
			sceneManager.Update(deltaTime);
			renderer.Render();
		}
	}

	Cleanup();
}
