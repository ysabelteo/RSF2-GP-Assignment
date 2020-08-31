
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "Mr. Cat by Lim Shu Ting and Teo Xiao Hui"

float speed;
float tz = 0, tSpeed = 1.0;
bool isOrtho = true;
float Ry = 0, rSpeed = 1.0;

float moveHand = 0;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			PostQuitMessage(0);
		else if (wParam == VK_UP) {
			if (isOrtho) {
				if (tz < 5.0)
					tz += tSpeed;
			}
			else {
				if (tz < 8) {
					tz += tSpeed;
				}
			}
		}
		else if (wParam == VK_DOWN) {
			if (isOrtho) {
				if (tz > -5)
					tz -= tSpeed;
			}

			else {
				if (tz > 1)
					tz -= tSpeed;
			}
		}

		else if (wParam == 'O') {
			isOrtho = true;
			tz = 0;
		}
		else if (wParam == 'P') {
			isOrtho = false;
			tz = 4.0;
		}
		else if (wParam == VK_LEFT) {
			Ry += rSpeed;
		}
		else if (wParam == VK_RIGHT) {
			Ry -= rSpeed;
		}

		else if (wParam == 0x57) {
			if (moveHand < 90) {
				moveHand += 1;
			}
		}
		else if (wParam == 0x53) {
			if (moveHand > 0) {
				moveHand -= 1;
			}
		}

		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void drawCube(float size) {
	glBegin(GL_QUADS);

	//Face1 : Bottom
	//glColor3f(1, 1, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(size, 0, 0);
	glVertex3f(size, 0, size);
	glVertex3f(0, 0, size);
	//Face2 : Back

	//glColor3f(1, 0, 0);
	glVertex3f(0, 0, size);
	glVertex3f(size, 0, size);
	glVertex3f(size, size, size);
	glVertex3f(0, size, size);
	//Face3 : Left
	//glColor3f(0, 0, 1);
	glVertex3f(0, size, size);
	glVertex3f(0, 0, size);
	glVertex3f(0, 0, 0);
	glVertex3f(0, size, 0);
	//Face4 : Top
	//glColor3f(0, 1, 0);
	glVertex3f(0, size, 0);
	glVertex3f(0, size, size);
	glVertex3f(size, size, size);
	glVertex3f(size, size, 0);
	//Face5 : Right
	//glColor3f(1, 1, 0);
	glVertex3f(size, size, 0);
	glVertex3f(size, size, size);
	glVertex3f(size, 0, size);
	glVertex3f(size, 0, 0);
	//Face6 : Front
	//glColor3f(0, 1, 1);
	glVertex3f(size, 0, 0);
	glVertex3f(size, size, 0);
	glVertex3f(0, size, 0);
	glVertex3f(0, 0, 0);
	glEnd();
}
void drawCuboid(float size) {
	glBegin(GL_QUADS);

	//Face1 : Bottom
	//glColor3f(1, 1, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(2 * size, 0, 0);
	glVertex3f(2 * size, 0, size);
	glVertex3f(0, 0, size);
	//Face2 : Back

	//glColor3f(1, 0, 0);
	glVertex3f(0, 0, size);
	glVertex3f(2 * size, 0, size);
	glVertex3f(2 * size, size, size);
	glVertex3f(0, size, size);
	//Face3 : Left
	//glColor3f(0, 0, 1);
	glVertex3f(0, size, size);
	glVertex3f(0, 0, size);
	glVertex3f(0, 0, 0);
	glVertex3f(0, size, 0);
	//Face4 : Top
	//glColor3f(0, 1, 0);
	glVertex3f(0, size, 0);
	glVertex3f(0, size, size);
	glVertex3f(2 * size, size, size);
	glVertex3f(2 * size, size, 0);
	//Face5 : Right
	//glColor3f(1, 1, 0);
	glVertex3f(2 * size, size, 0);
	glVertex3f(2 * size, size, size);
	glVertex3f(2 * size, 0, size);
	glVertex3f(2 * size, 0, 0);
	//Face6 : Front
	//glColor3f(0, 1, 1);
	glVertex3f(2 * size, 0, 0);
	glVertex3f(2 * size, size, 0);
	glVertex3f(0, size, 0);
	glVertex3f(0, 0, 0);
	glEnd();
}
void drawCuboid3f(float size, float scale) {

	glBegin(GL_QUADS);

	//Face1 : Bottom
	//glColor3f(1, 1, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(scale * size, 0, 0);
	glVertex3f(scale * size, 0, size);
	glVertex3f(0, 0, size);
	//Face2 : Back

	//glColor3f(1, 0, 0);
	glVertex3f(0, 0, size);
	glVertex3f(scale * size, 0, size);
	glVertex3f(scale * size, size, size);
	glVertex3f(0, size, size);
	//Face3 : Left
	//glColor3f(0, 0, 1);
	glVertex3f(0, size, size);
	glVertex3f(0, 0, size);
	glVertex3f(0, 0, 0);
	glVertex3f(0, size, 0);
	//Face4 : Top
	//glColor3f(0, 1, 0);
	glVertex3f(0, size, 0);
	glVertex3f(0, size, size);
	glVertex3f(scale * size, size, size);
	glVertex3f(scale * size, size, 0);
	//Face5 : Right
	//glColor3f(1, 1, 0);
	glVertex3f(scale * size, size, 0);
	glVertex3f(scale * size, size, size);
	glVertex3f(scale * size, 0, size);
	glVertex3f(scale * size, 0, 0);
	//Face6 : Front
	//glColor3f(0, 1, 1);
	glVertex3f(scale * size, 0, 0);
	glVertex3f(scale * size, size, 0);
	glVertex3f(0, size, 0);
	glVertex3f(0, 0, 0);
	glEnd();

}
void drawCuboid2f(float size, float length,float width) {

	glBegin(GL_QUADS);

	//Face1 : Bottom
	//glColor3f(1, 1, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(length * size, 0, 0);
	glVertex3f(length * size, 0, width * size);
	glVertex3f(0, 0, width * size);
	
	//Face2 : Back
	//glColor3f(1, 0, 0);
	glVertex3f(0, 0, width * size);
	glVertex3f(length * size, 0, width * size);
	glVertex3f(length * size, size, width * size);
	glVertex3f(0, size, width * size);

	//Face3 : Left
	//glColor3f(0, 0, 1);
	glVertex3f(0, size, width * size);
	glVertex3f(0, 0, width * size);
	glVertex3f(0, 0, 0);
	glVertex3f(0, size, 0);

	//Face4 : Top
	//glColor3f(0, 1, 0);
	glVertex3f(0, size, 0);
	glVertex3f(0, size, width * size);
	glVertex3f(length * size, size, width * size);
	glVertex3f(length * size, size, 0);
	//Face5 : Right
	//glColor3f(1, 1, 0);
	glVertex3f(length * size, size, 0);
	glVertex3f(length * size, size, width * size);
	glVertex3f(length * size, 0, width * size);
	glVertex3f(length * size, 0, 0);

	//Face6 : Front
	//glColor3f(0, 1, 1);
	glVertex3f(length * size, 0, 0);
	glVertex3f(length * size, size, 0);
	glVertex3f(0, size, 0);
	glVertex3f(0, 0, 0);
	glEnd();

}
void drawSphere(float size) {
	//glColor3f(1.0, 0.75, 0.8);

	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_LINE);
	gluSphere(sphere, size, 50, 50);
	gluDeleteQuadric(sphere);
}
void drawSphereWithoutGlu(float size) {
	const float PI = 3.141592f;
	GLfloat x, y, z, sliceA, stackA;
	GLfloat radius = size;
	int sliceNo = 30, stackNo = 30;

	for (sliceA = 0.0; sliceA < 2 * PI; sliceA += PI / sliceNo) {
		glBegin(GL_LINE_LOOP);
		for (stackA = 0; stackA < 2 * PI; stackA += PI / stackNo) {
			x = radius * cos(stackA) * sin(sliceA);
			y = radius * sin(stackA) * sin(sliceA);
			z = radius * cos(sliceA);
			glVertex3f(x, y, z);
			x = radius * cos(stackA) * sin(sliceA + PI / stackNo);
			y = radius * sin(stackA) * sin(sliceA + PI / sliceNo);
			z = radius * cos(sliceA + PI / sliceNo);
			glVertex3f(x, y, z);
		}
		glEnd();
	}
}
void drawCone(float baseRadius, float height) {
	//glColor3f(0.6, 0.48, 0.3);

	GLUquadricObj* cone = NULL;
	cone = gluNewQuadric();
	gluQuadricDrawStyle(cone, GLU_FILL);
	gluCylinder(cone, 0.00001, baseRadius, height, 10, 9);
	gluDeleteQuadric(cone);
}
void drawCylinder(float size, float height) {
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, size, size, height, 10, 9);
	gluDeleteQuadric(cylinder);
}
void drawPyramid(float size) {
	glBegin(GL_QUADS);
	//Face1 : Bottom
	glColor3f(1, 1, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(size, 0, 0);
	glVertex3f(size, 0, size);
	glVertex3f(0, 0, size);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(0, 0, 0);
	glVertex3f(size, 0, 0);
	glVertex3f(size, size, size);

	glVertex3f(size, 0, size);
	glVertex3f(size, 0, 0);
	glVertex3f(size, size, size);

	glVertex3f(size, 0, size);
	glVertex3f(0, 0, size);
	glVertex3f(size, size, size);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, size);
	glVertex3f(size, size, size);
	glEnd();
}
void drawLowerArm(float size) {
	glBegin(GL_QUADS);

	//Face1 : Bottom
	//glColor3f(1, 1, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(2 * size, 0, 0);
	glVertex3f(2 * size, 0, size);
	glVertex3f(0, 0, size / 2);
	//Face2 : Back

	//glColor3f(1, 0, 0);
	glVertex3f(0, 0, size / 2);
	glVertex3f(2 * size, 0, size);
	glVertex3f(2 * size, size, size);
	glVertex3f(0, size / 2, size / 2);
	//Face3 : Left
	//glColor3f(0, 0, 1);
	glVertex3f(0, size / 2, size / 2);
	glVertex3f(0, 0, size / 2);
	glVertex3f(0, 0, 0);
	glVertex3f(0, size / 2, 0);
	//Face4 : Top
	//glColor3f(0, 1, 0);
	glVertex3f(0, size / 2, 0);
	glVertex3f(0, size / 2, size / 2);
	glVertex3f(2 * size, size, size);
	glVertex3f(2 * size, size, 0);
	//Face5 : Right
	//glColor3f(1, 1, 0);
	glVertex3f(2 * size, size, 0);
	glVertex3f(2 * size, size, size);
	glVertex3f(2 * size, 0, size);
	glVertex3f(2 * size, 0, 0);
	//Face6 : Front
	//glColor3f(0, 1, 1);
	glVertex3f(2 * size, 0, 0);
	glVertex3f(2 * size, size, 0);
	glVertex3f(0, size / 2, 0);
	glVertex3f(0, 0, 0);
	glEnd();
}
void drawHand() {
	//Upper Arm
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	drawCuboid3f(0.5, 3);
	glPopMatrix();

	//Lower Arm
	glPushMatrix();
	glRotatef(moveHand, 0, 0, 1);
	glTranslatef(0, -1.5, 0);
	glRotatef(90, 0, 0, 1);
	drawCuboid3f(0.5, 3);
	glPopMatrix();
}
void drawTetrahedrom(float size) {
	glBegin(GL_LINE_LOOP);

	glVertex3f(0, 0, 0);
	glVertex3f(0, size, 0);
	glVertex3f(0, size / 2, size);

	glVertex3f(0, size / 2, size);
	glVertex3f(0, size, 0);
	glVertex3f(size, size, 0);

	glVertex3f(size, size, 0);
	glVertex3f(0, size / 2, size);
	glVertex3f(0, 0, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(size, size, 0);
	glVertex3f(0, size, 0);

	glEnd();

}
void drawHead() {
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	drawSphereWithoutGlu(0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.2, 0.0);
	glScalef(1.0, 0.7, 1.0);
	drawSphereWithoutGlu(0.5);
	glPopMatrix();

	//left ear
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glTranslatef(-0.40, 0.15, 0.0);
	glRotatef(45, 0.0, 0.0, 1.0);
	drawPyramid(0.3);
	glPopMatrix();

	//right ear
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glTranslatef(0.40, 0.15, 0.2);
	glRotatef(180, 0.0, 1.0, 0.0);
	glRotatef(45, 0.0, 0.0, 1.0);
	drawPyramid(0.3);
	glPopMatrix();

	//neck
	glPushMatrix();
	glTranslatef(-0.13, -0.8, -0.2);
	drawCuboid3f(0.5, 0.5);
	glPopMatrix();

	//left eyes
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(-0.25, 0.0, 0.5);
	glScalef(0.2, 0.1, 0.0);
	drawSphere(0.7);
	glPopMatrix();

	//right eyes
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(0.2, 0.0, 0.5);
	glScalef(0.25, 0.1, 0.0);
	drawSphere(0.7);
	glPopMatrix();
}
void drawBody() {
	//body
	glPushMatrix();

	glPushMatrix();
	glTranslatef(-1.5, 1.125, 0);
	drawCube(1.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 1.125, 0);
	drawCube(1.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.125, 0.75, 0);
	drawCube(1.125);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.75, 0);
	drawCube(1.125);
	glPopMatrix();

	glPushMatrix();
	drawCube(0.75);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.75, 0, 0);
	drawCube(0.75);
	glPopMatrix();


	//drawCuboid2f(3, 0.75, 0.15);
	glPopMatrix();
}
void drawLeg() {

	//upper
	glLoadIdentity();
	glPushMatrix();
	glScalef(1.0, 1.0, 0.2);
	glTranslatef(0.0, 1.0, 0.0);
	glRotatef(180, 1.0, 1.0, 0.0);
	drawCuboid(1.0);
	glPopMatrix();

	//joint
	glPushMatrix();
	glScalef(1.0, 1.0, 0.2);
	glTranslatef(0.5, 0.5, 0.0);
	drawSphereWithoutGlu(0.5);
	glPopMatrix();

	//lower
	glPushMatrix();
	glLoadIdentity();
	glScalef(1.0, 1.0, 0.2);
	glTranslatef(0.0, -2.0, 0.0);
	glRotatef(180, 1.0, 1.0, 0.0);
	drawCuboid(1.0);
	glPopMatrix();

	//jiao ban
	glPushMatrix();
	glScalef(1.5, 0.5, 0.2);
	glTranslatef(-0.18, -4.0, -1.0);
	drawCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -3.0, 2.0);
	drawCube(1.0);
	glPopMatrix();

}
void projection() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glRotatef(Ry, 0.0, 1.0, 0.0);

	if (isOrtho) {
		glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
	}
	else {
		gluPerspective(60.0, 1.0, -1.0, 1.0);
		glFrustum(-5.0, 5.0, -5.0, 5.0, 1.0, 8.0);
	}
}

void display()
{

	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5, 0.5, 0.5, 0);
	projection();

	glMatrixMode(GL_MODELVIEW);

	glRotatef(0.1, 1, 1, 1);

	//glLoadIdentity();
	//glTranslatef(0.0, 0.0, tz);

	glPushMatrix();
	glTranslatef(2, 1, 0.0);
	
	glColor3f(1, 0, 1);
	drawHand();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, 1, 0.0);
	glColor3f(1, 0, 0);
	drawHand();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0);
	glColor3f(1, 1, 0);
	drawBody();
	glPopMatrix();

	//drawLeg();
}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 700, 700,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------