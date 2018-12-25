#include <client/Client.hpp>

#include <chrono>
#include <thread>

#include <engine/core/graphics/Renderer2D.hpp>

using namespace phx::gfx;
using namespace phx;

using namespace client;

Sandbox::Sandbox() :
	m_appRequirements(new phx::ApplicationRequirements()),
	m_appData(new phx::ApplicationData)
{
	using namespace phx::gfx;
	using namespace phx;

	m_appRequirements->glProfile = GLProfile::CORE;
	m_appRequirements->glVersion = GLVersion(3, 3);

	m_appRequirements->windowWidth = 1280;
	m_appRequirements->windowHeight = 720;
	m_appRequirements->windowTitle = "Phoenix!";

	m_appRequirements->logFile = "PhoenixClient.log";
	m_appRequirements->logVerbosity = LogVerbosity::DEBUG;
}

Sandbox::~Sandbox()
{}

void Sandbox::run()
{
	PHX_REGISTER_CONFIG("Controls");

	using namespace phx::voxels;
	
	RegistryBlock block("core:grass", "Grass", 100, BlockType::SOLID);
	std::vector<std::string> texForGrass;
	texForGrass.push_back("assets/textures/grass_side.png");
	texForGrass.push_back("assets/textures/grass_side.png");
	texForGrass.push_back("assets/textures/grass_side.png");
	texForGrass.push_back("assets/textures/grass_side.png");
	texForGrass.push_back("assets/textures/dirt.png");
	texForGrass.push_back("assets/textures/grass_top.png");
	block.setBlockTextures(texForGrass);
	block.setBreakCallback([]() { LDEBUG("Broken a grass block!"); });

	RegistryBlock blockDirt("core:dirt", "dirt", 100, BlockType::SOLID);
	std::vector<std::string> texForDirt;
	texForDirt.push_back("assets/textures/dirt.png");
	texForDirt.push_back("assets/textures/dirt.png");
	texForDirt.push_back("assets/textures/dirt.png");
	texForDirt.push_back("assets/textures/dirt.png");
	texForDirt.push_back("assets/textures/dirt.png");
	texForDirt.push_back("assets/textures/dirt.png");
	blockDirt.setBlockTextures(texForDirt);
	blockDirt.setBreakCallback([]() { LDEBUG("Broken a dirt block!"); });

	RegistryBlock air("core:air", "Air", 100, BlockType::GAS);
	air.setBreakCallback([]() { LDEBUG("Broken an air block somehow"); });
	
	BlockLibrary::get()->init();

	BlockLibrary::get()->registerBlock(block);
	BlockLibrary::get()->registerBlock(blockDirt);
	BlockLibrary::get()->registerBlock(air);

	ChunkManager* world = new ChunkManager("core:air", time(nullptr));

	m_player = std::make_unique<Player>(m_appData->window, world);

	gl::ShaderPipeline* shaderProgram = new gl::ShaderPipeline();
	shaderProgram->addStage(gl::ShaderType::VERTEX_SHADER, File::readFile("assets/shaders/main.vert").c_str());
	shaderProgram->addStage(gl::ShaderType::FRAGMENT_SHADER, File::readFile("assets/shaders/main.frag").c_str());
	shaderProgram->build();
	
	Matrix4x4 model;

	phx::gfx::IWindow* window = m_appData->window;
	int ww, wh;
	window->getSize(ww, wh);

	bool fullscreen = false;
	window->addKeyCallback(events::KeyEventType::PRESSED, events::Keys::KEY_F11, [&window, &fullscreen]()
	{
		fullscreen = !fullscreen;
		window->setFullscreen(fullscreen);
	});

	window->addKeyCallback(events::KeyEventType::PRESSED, events::Keys::KEY_RETURN, [&window, &fullscreen]()
	{
		LDEBUG("ENTER!");
		window->pollEvents();
		bool isPressed = window->isKeyDown(events::Keys::KEY_LALT);
		if (window->isKeyDown(events::Keys::KEY_LALT))
		{
			fullscreen = !fullscreen;
			window->setFullscreen(fullscreen);
		}
	});

	window->addKeyCallback(events::KeyEventType::PRESSED, events::Keys::KEY_1, [&world]() {
		world->toggleWireframe();
	});

	int fps_lasttime = SDL_GetTicks(); //the last recorded time.
	int fps_current; //the current FPS.
	int fps_frames = 0; //frames passed since the last recorded fps.
	
	gfx::Renderer2D renderer(
		Matrix4x4::ortho(0.f, ww, 0.f, wh, 1.f, -1.f),
		"assets/shaders/ui.vert",
		"assets/shaders/ui.frag"
	);

	world->determineGeneration(m_player->getPosition());
	float last = SDL_GetTicks();
	while (m_appData->window->isRunning())
	{
		m_appData->window->pollEvents();
		float now = SDL_GetTicks();
		float dt = now - last;
		last = now;

		m_player->tick(dt);

		// ONLY HERE TEMPORARILY.
		fps_frames++;
		if (fps_lasttime < SDL_GetTicks() - 1000)
		{
			fps_lasttime = SDL_GetTicks();
			fps_current = fps_frames;
			LDEBUG("FPS: ", fps_current);
			fps_frames = 0;
		}
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.3f, 0.5f, 0.7f, 1.0f);
		
		shaderProgram->use();

		m_player->applyTo(shaderProgram);
		shaderProgram->setMat4("u_model", model);
		shaderProgram->setUniform1<int>("u_TexArray", 10);

		world->render(10);
		
		renderer.begin();
		renderer.fillCircle({ ww / 2.f, wh / 2.f }, 3, 7, { 1.f, 1.f, 1.f });
		renderer.end();
		renderer.draw();
		
		m_appData->window->swapBuffers();
	}
}

phx::Application* phx::createApplication()
{
	return new Sandbox();
}