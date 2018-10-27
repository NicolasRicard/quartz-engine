#include "engine/graphics/IWindow.hpp"

#include "engine/SDL/SDLWindow.hpp"
#include "engine/GLFW/GLFWWindow.hpp"

using namespace phx::gfx;

IWindow* IWindow::createWindow(WindowingAPI windowingAPI, const char* title, int width, int height, GLVersion version, GLProfile profile)
{
	switch (windowingAPI)
	{
	case WindowingAPI::SDL:
		return new phx::sdl::SDLWindow(title, width, height, version, profile);
	case WindowingAPI::GLFW:
		return new phx::glfw::GLFWWindow(title, width, height, version, profile);
	}

	return nullptr;
}
