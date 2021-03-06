#include "../include/screen.h"
#include "../include/glinclude.h"

Screen* Screen::screen = NULL;

int GLFWCALL Screen::CloseCallback() {
	Screen::Instance().opened = false;
	return GL_TRUE;
}

Screen::Screen() {
	glfwInit();
	opened = false;
}

Screen::~Screen() {
	glfwTerminate();
}

Screen& Screen::Instance() {
	if ( !screen )
		screen = new Screen();
	return *screen;
}

void Screen::Open(uint16 width, uint16 height, bool fullscreen) {
	// Abrimos la ventana
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	glfwOpenWindow(int(width), int(height), 8, 8, 8, 8, 0, 0, fullscreen ? GLFW_FULLSCREEN : GLFW_WINDOW );
	if ( !fullscreen )
		glfwSetWindowPos((GetDesktopWidth()-width)/2, (GetDesktopHeight()-height)/2);
	glfwSetWindowCloseCallback(GLFWwindowclosefun(CloseCallback));
	glfwSwapInterval(1);
	SetTitle("");
	opened = true;

	// Inicializamos OpenGL
	glEnableClientState(GL_VERTEX_ARRAY); //Lectura del array de v�rtices.
	glEnableClientState(GL_TEXTURE_COORD_ARRAY); //Lectura del array de coordenadas de textura.
	glEnable(GL_BLEND); //Mezclado.
	glEnable(GL_TEXTURE_2D); //Renderizado de texturas.

	this->width = width;
	this->height = height;

	// Configuramos viewport
	glViewport(0,0,width,height);

	// Configuramos matriz de proyeccion
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity;
	glOrtho(0,width,height,0,0,1000);

	// Configuramos matriz de modelado
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity;

	//Configuramos la matrix de texturas
	/*glMatrixMode(GL_TEXTURE);
	glLoadIdentity;*/

	// Inicializamos temporizador
	lastTime = glfwGetTime();
	elapsed = 0;
}

void Screen::Close() {
	glfwCloseWindow();
}

void Screen::SetTitle(const String &title) {
    glfwSetWindowTitle(title.ToCString());
}

void Screen::Refresh() {
	glfwSwapBuffers();
	glfwGetMousePos(&mousex, &mousey);
	elapsed = glfwGetTime() - lastTime;
	lastTime = glfwGetTime();
}

uint16 Screen::GetDesktopWidth() const {
	GLFWvidmode mode;
	glfwGetDesktopMode(&mode);
	return uint16(mode.Width);
}

uint16 Screen::GetDesktopHeight() const {
	GLFWvidmode mode;
	glfwGetDesktopMode(&mode);
	return uint16(mode.Height);
}

bool Screen::MouseButtonPressed(int button) const {
	return glfwGetMouseButton(button) == GLFW_PRESS;
}

bool Screen::KeyPressed(int key) const {
	return glfwGetKey(key) == GLFW_PRESS;
}
