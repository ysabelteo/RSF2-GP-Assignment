
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "Mr. Cat by Lim Shu Ting and Teo Xiao Hui"
#define PI 3.14159

float speed;
float tx = 0, tz = 0, tSpeed = 1.0;
bool isOrtho = true;
float Ry = 0, Rx = 0, Rz = 0, rSpeed = 5.0;

float moveHand = 0;
float energyStore = 0;
int choice=1;
int control;
bool isFired = false;
bool isSword = false;
bool isAttack = false;
bool isNod = false;
bool isShakingHead = false;
bool isWalking;
float wSpeed = 1;
float UpperArmAngle = 0, LowerArmAngle = 0;
float UpperLegAngle = 0, LowerLegAngle = 0;

float fireSpeed = 1;
float walkingDistance=0;
bool frontMax=false;
bool backMax = false;
bool isRotateActivate = false;
bool isTranslateActivate = false;
bool isJumping = false;

//--lighting--
float posD[] = { 0, 6, 0 };
float lightSpeed = 0.1, light;
float diff[] = { 1.0, 0.0, 0.0 }; //red color diffuse light
float Ra = 0.5, lSpeed = 0.5;
float ambM[] = { 0.0, 1.0, 0.0 };
bool lightOn = false; //turn on lighting?

//--texture--

BITMAP BMP;			 //bitmap structure
HBITMAP hBMP = NULL; //bitmap handle
LPCSTR backgroundChoice = "galaxy.bmp";
LPCSTR mainTexture = "metalTexture.bmp";
LPCSTR subTexture = "blue2.bmp";

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
			if (isTranslateActivate) {
				if (isOrtho) {
					if (tz < 5.0)
						tz += tSpeed;
				}
				else {
					if (tz < 28) {
						tz += tSpeed;
					}
				}
			}
				
			if (isRotateActivate) {
				Rx += rSpeed;
			}
		}
		else if (wParam == VK_DOWN) {
			if (isTranslateActivate) {
				if (isOrtho) {
					if (tz > -5)
						tz -= tSpeed;
				}

				else {
					if (tz > 16)
						tz -= tSpeed;
				}
			}
			
			if (isRotateActivate) {
				Rx -= rSpeed;
			}
		}

		else if (wParam == 'O') {
			isOrtho = true;
			tz = 0;
		}
		else if (wParam == 'P') {
			isOrtho = false;
			tz = 16.0;
		}
		else if (wParam == VK_LEFT) {
			if (isTranslateActivate) {
				if (isOrtho) {
					if (tx > -5)
						tx -= tSpeed;
				}

				else {
					if (tx > -5)
						tx -= tSpeed;
				}
			}

			if (isRotateActivate) {
				Ry += rSpeed;
			}
			
		}
		else if (wParam == VK_RIGHT) {
			if (isTranslateActivate) {
				if (isOrtho) {
					if (tx < 5)
						tx += tSpeed;
				}

				else {
					if (tx < 5)
						tx += tSpeed;
				}
			}

			if (isRotateActivate) {
				Ry -= rSpeed;
			}
			
		}

		else if (wParam == 0x57) {
			if (moveHand < 90) {
				moveHand += 10;
			}
		}
		else if (wParam == 0x53) {
			if (moveHand > 0) {
				moveHand -= 10;
			}
		}
		else if (wParam == 0x46) {
			isFired = true;
			fireSpeed = 0;
			energyStore = 0;
		}
		else if (wParam == 0x48) {
			choice = 1;
		}
		else if (wParam == 0x4A) {
			choice = 2;
		}
		else if (wParam == 0x5A) {
			isWalking = true;
			isJumping = false;
			if (!frontMax) {
				UpperArmAngle += 5;
				LowerArmAngle += 10;
				
				UpperLegAngle -= 10;
				LowerLegAngle -= 5;
			}
			else {
				UpperArmAngle -= 5;
				if(LowerArmAngle>0)
					LowerArmAngle -= 10;

				UpperLegAngle += 10;
				LowerLegAngle += 5;
			}
				

			if (isOrtho)
				if(walkingDistance<7)
					walkingDistance += 0.5;
			else
				walkingDistance -= 0.1;
			
		}
		else if (wParam == VK_SPACE) {
			walkingDistance = 0;
			Rx = 0;
			Ry = 0;
			tx = 0;
			LowerArmAngle = 0;
			LowerLegAngle = 0;
			UpperArmAngle = 0;
			UpperLegAngle = 0;
			if (isOrtho)
				tz = 0;
			else
				tz = 16;
		}
		else if (wParam == 0x4C) {
			lightOn = !lightOn;
		}
		else if (wParam == 0x4D) {
			posD[0] = 0;
			posD[1] = 0;
			posD[2] = 0;
		}
		else if (wParam == 0x30) {
			isRotateActivate = !isRotateActivate;
			isTranslateActivate = false;
		}
		else if (wParam == 0x31) {
			backgroundChoice = "sky2.bmp";
		}
		else if (wParam == 0x32) {
		backgroundChoice = "galaxy.bmp";
		}
		else if (wParam == 0x33) {
		backgroundChoice = "sky3.bmp";
		}
		else if (wParam == 0x34) {
		mainTexture = "metalTexture.bmp";
		subTexture = "blue2.bmp";
		}
		else if (wParam == 0x35) {
		mainTexture = "purple.bmp";
		subTexture = "black2.bmp";
		}
		else if (wParam == 0x36) {
		mainTexture = "light_green.bmp";
		subTexture = "green.bmp";
		}
		else if (wParam == 0x39) {
			isTranslateActivate = !isTranslateActivate;
			isRotateActivate = false;
		}
		else if (wParam == 0x38) {
			isJumping = !isJumping;
			
		}
		else if (wParam == 0x45) { //e
			isSword = !isSword;

		}
		else if (wParam == 0x51) { //q
			isAttack = !isAttack;

		}
		else if (wParam == 0x59) { //y
		isNod = !isNod;

		}
		else if (wParam == 0x4E) { //n
		isShakingHead = !isShakingHead;

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
GLuint loadTexture(LPCSTR filename) {

	//take from step 1
	GLuint texture = 0;  //texture name

	//step 3: initialize texture info
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	//step 4: Assign texture to polygon
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture); //generate texture
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	glTexCoord2f(0.0f, 0.0f);

	//take from step 5
	DeleteObject(hBMP);
	return texture;
}
void drawCube(float size) {
	glBegin(GL_QUADS);

	//Face1 : Bottom
	////glColor3f(1, 1, 1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(size, 0, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(size, 0, size);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, size);

	//Face2 : Back
	////glColor3f(1, 0, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 0, size);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(size, 0, size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(size, size, size);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, size, size);

	//Face3 : Left
	////glColor3f(0, 0, 1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, size, size);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, 0, size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, size, 0);

	//Face4 : Top
	////glColor3f(0, 1, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, size, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, size, size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(size, size, size);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(size, size, 0);

	//Face5 : Right
	////glColor3f(1, 1, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(size, size, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(size, size, size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(size, 0, size);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(size, 0, 0);

	//Face6 : Front
	////glColor3f(0, 1, 1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(size, 0, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(size, size, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, size, 0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glEnd();
}
void drawCuboid(float size) {
	glBegin(GL_QUADS);

	//Face1 : Bottom
	////glColor3f(1, 1, 1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2 * size, 0, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2 * size, 0, size);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, size);
	//Face2 : Back

	////glColor3f(1, 0, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 0, size);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2 * size, 0, size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2 * size, size, size);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, size, size);
	//Face3 : Left
	////glColor3f(0, 0, 1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, size, size);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, 0, size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, size, 0);
	//Face4 : Top
	////glColor3f(0, 1, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, size, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, size, size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2 * size, size, size);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(2 * size, size, 0);
	//Face5 : Right
	////glColor3f(1, 1, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(2 * size, size, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2 * size, size, size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2 * size, 0, size);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(2 * size, 0, 0);
	//Face6 : Front
	////glColor3f(0, 1, 1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(2 * size, 0, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2 * size, size, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, size, 0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glEnd();
}
void drawCuboid3f(float size, float scale) {

	glBegin(GL_QUADS);

	//Face1 : Bottom
	////glColor3f(1, 1, 1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(scale * size, 0, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(scale * size, 0, size);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, size);
	//Face2 : Back

	////glColor3f(1, 0, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 0, size);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(scale * size, 0, size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(scale * size, size, size);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, size, size);
	//Face3 : Left
	////glColor3f(0, 0, 1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, size, size);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, 0, size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, size, 0);
	//Face4 : Top
	////glColor3f(0, 1, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, size, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, size, size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(scale * size, size, size);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(scale * size, size, 0);
	//Face5 : Right
	////glColor3f(1, 1, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(scale * size, size, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(scale * size, size, size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(scale * size, 0, size);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(scale * size, 0, 0);
	//Face6 : Front
	////glColor3f(0, 1, 1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(scale * size, 0, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(scale * size, size, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, size, 0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glEnd();

}
void drawCuboid2f(float size, float length,float width) {

	glBegin(GL_QUADS);

	//Face1 : Bottom
	////glColor3f(1, 1, 1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(length * size, 0, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(length * size, 0, width * size);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, width * size);
	
	//Face2 : Back
	////glColor3f(1, 0, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 0, width * size);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(length * size, 0, width * size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(length * size, size, width * size);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, size, width * size);

	//Face3 : Left
	////glColor3f(0, 0, 1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, size, width * size);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, 0, width * size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, size, 0);

	//Face4 : Top
	////glColor3f(0, 1, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, size, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, size, width * size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(length * size, size, width * size);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(length * size, size, 0);
	//Face5 : Right
	////glColor3f(1, 1, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(length * size, size, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(length * size, size, width * size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(length * size, 0, width * size);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(length * size, 0, 0);

	//Face6 : Front
	////glColor3f(0, 1, 1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(length * size, 0, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(length * size, size, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, size, 0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glEnd();

}
void drawSphere(float size) {
	////glColor3f(1.0, 0.75, 0.8);
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, true);
	gluSphere(sphere, size, 50, 50);
	gluDeleteQuadric(sphere);
}
void drawSphereWithoutGlu(float size) {
	//const float PI = 3.141592f;
	GLfloat x, y, z, sliceA, stackA;
	GLfloat radius = size;
	int sliceNo = 30, stackNo = 30;

	for (sliceA = 0.0; sliceA < 2 * PI; sliceA += PI / sliceNo) {
		glBegin(GL_TRIANGLE_FAN);
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
	////glColor3f(0.6, 0.48, 0.3);
	GLUquadricObj* cone = NULL;
	cone = gluNewQuadric();
	gluQuadricDrawStyle(cone, GLU_FILL);
	gluQuadricTexture(cone, true);
	gluCylinder(cone, 0.00001, baseRadius, height, 10, 9);
	gluDeleteQuadric(cone);
}
void drawCylinder(float size, float height) {
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluQuadricTexture(cylinder, true);
	gluCylinder(cylinder, size, size, height, 10, 9);
	gluDeleteQuadric(cylinder);
}
void drawPyramid(float size) {
	glBegin(GL_QUADS);
	//Face1 : Bottom
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(size, 0, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(size, 0, size);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, size);
	glEnd();

	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(size, 0, 0);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(size, size, size);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(size, 0, size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(size, 0, 0);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(size, size, size);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(size, 0, size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, 0, size);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(size, size, size);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, 0, size);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(size, size, size);

	glEnd();
}
void drawShoulder() {
	GLuint textures[3];

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.5);
	textures[0] = loadTexture("grey.bmp");
	//Buttom
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0, 0.0, -1.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0, 0.0, -1.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0, 0.0, 0.0);
	glEnd();

	//font
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0, 0.0, 0.0);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0.0, 1.0, 0.0);

	//left
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0, 1.0, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0, 0.0, 0.0);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(-1.0, 0.0, -1.0);

	//back
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0, 0.0, -1.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0, 1.0, 0.0);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(1.0, 0.0, -1.0);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0, 0.0, -1.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0, 1.0, 0.0);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(1.0, 0.0, 0.0);
	glEnd();
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0, -0.2, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	textures[0] = loadTexture("grey.bmp");
	drawCylinder(0.5, 2.0);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();
}
void drawSword() {

	GLuint textures[3];

	glPushMatrix();
	////glColor3f(0.478, 0.070, 0.035);
	glTranslatef(0.0, 3, 0.0);
	textures[0] = loadTexture("sword1.bmp");
	drawSphereWithoutGlu(0.15);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 2.9, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	textures[1] = loadTexture("black1.bmp");
	drawCylinder(0.125, 0.3);
	glDeleteTextures(1, &textures[1]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 2.6, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	////glColor3f(1, 0, 0);
	textures[0] = loadTexture("metalTexture.bmp");
	drawCylinder(0.15, 0.1);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 2, 0);
	glRotatef(-90, 1, 0, 0);
	////glColor3f(1, 1, 1);
	textures[2] = loadTexture("black2.bmp");
	drawCylinder(0.125, 0.5);
	glDeleteTextures(1, &textures[2]);
	glPopMatrix();

}
void drawSword2() {

	GLuint textures[3];

	glPushMatrix();
	textures[0] = loadTexture("metalTexture.bmp");
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.5, 1.9, 0.14);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5, 1.9, -0.14);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5, 1.9, -0.14);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5, 1.9, 0.14);
	glEnd();
	glDeleteTextures(1, &textures[0]);

	textures[0] = loadTexture("metalTexture.bmp");
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.4, 1.9, 0.14);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.4, 1.9, -0.14);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.4, 2, -0.14);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.4, 2, 0.14);
	glEnd();
	glDeleteTextures(1, &textures[0]);

	textures[0] = loadTexture("metalTexture.bmp");
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.5, 1.9, 0.14);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5, 1.9, -0.14);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5, 2, -0.14);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5, 2, 0.14);
	glEnd();
	glDeleteTextures(1, &textures[0]);

	textures[0] = loadTexture("metalTexture.bmp");
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.5, 1.9, 0.14);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5, 1.9, 0.14);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5, 2, 0.14);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5, 2, 0.14);
	glEnd();
	glDeleteTextures(1, &textures[0]);

	textures[0] = loadTexture("metalTexture.bmp");
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.5, 1.9, -0.14);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5, 2, -0.14);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5, 2, -0.14);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5, 1.9, -0.14);
	glEnd();
	glDeleteTextures(1, &textures[0]);

	textures[0] = loadTexture("metalTexture.bmp");
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.5, 2, 0.14);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5, 2, -0.14);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5, 2, -0.14);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5, 2, 0.14);
	glEnd();
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	textures[1] = loadTexture("diamond.bmp");
	glBegin(GL_POLYGON);
	glTexCoord2f(-0.9, 1.0);
	glVertex3f(-0.3, 2.0, 0.15);
	glTexCoord2f(0.9, 1.0);
	glVertex3f(0.3, 2.0, 0.15);
	glTexCoord2f(1.0, 0.9);
	glVertex3f(0.35, 1.9, 0.15);
	glTexCoord2f(0.5, 0.0);
	glVertex3f(0.00, 1.5, 0.15);
	glTexCoord2f(-1.0, 0.9);
	glVertex3f(-0.35, 1.9, 0.15);
	glEnd();
	glDeleteTextures(1, &textures[1]);
	glPopMatrix();

	glPushMatrix();
	//glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.3, 2.0, 0.15);
	glVertex3f(0.3, 2.0, 0.15);
	glVertex3f(0.35, 1.9, 0.15);
	glVertex3f(0.00, 1.5, 0.15);
	glVertex3f(-0.35, 1.9, 0.15);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	//glColor3f(1,1,1);
	textures[1] = loadTexture("diamond.bmp");
	glBegin(GL_POLYGON);
	glTexCoord2f(-0.9, 1.0);
	glVertex3f(-0.3, 2.0, -0.15);
	glTexCoord2f(0.9, 1.0);
	glVertex3f(0.3, 2.0, -0.15);
	glTexCoord2f(1.0, 0.9);
	glVertex3f(0.35, 1.9, -0.15);
	glTexCoord2f(0.5, 0.0);
	glVertex3f(0.00, 1.5, -0.15);
	glTexCoord2f(-1.0, 0.9);
	glVertex3f(-0.35, 1.9, -0.15);
	glEnd();
	glDeleteTextures(1, &textures[1]);
	glPopMatrix();

	glPushMatrix();
	//glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.3, 2.0, -0.15);
	glVertex3f(0.3, 2.0, -0.15);
	glVertex3f(0.35, 1.9, -0.15);
	glVertex3f(0.00, 1.5, -0.15);
	glVertex3f(-0.35, 1.9, -0.15);
	glEnd();
	glPopMatrix();

	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix();
	//textures[0] = loadTexture("metalTexture.bmp");
	glBegin(GL_QUADS);
	////glColor3f(0.75, 0.75, 0.75);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, -1, 0.125);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.25, -1, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.25, 2, 0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 2, 0.125);

	////glColor3f(1, 1, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 2, 0.125);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, -1, 0.125);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.25, -1, 0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.25, 2, 0);

	////glColor3f(0, 1, 1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.25, 2, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.25, -1, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, -1, -0.125);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 2, -0.125);

	////glColor3f(1, 0, 1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 2, -0.125);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.25, 2, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.25, -1, 0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, -1, -0.125);
	//glDeleteTextures(1, &textures[0]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	//textures[2] = loadTexture("metalTexture.bmp");
	glBegin(GL_TRIANGLES);
	////glColor3f(1, 0, 0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0, -1.25, 0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0, -1, 0.125);
	glTexCoord2f(0.5, 1.0);
	glVertex3f(-0.25, 0, 0);

	////glColor3f(0, 0, 1);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.25, -1, 0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0, -1, -0.125);
	glTexCoord2f(0.5, 1.0);
	glVertex3f(0, -1.25, 0);

	////glColor3f(0, 1, 0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0, -1.25, 0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0, -1, 0.125);
	glTexCoord2f(0.5, 1.0);
	glVertex3f(0.25, -1, 0);

	////glColor3f(1, 1, 1);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.25, -1, 0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0, -1, -0.125);
	glTexCoord2f(0.5, 1.0);
	glVertex3f(0, -1.25, 0);
	//glDeleteTextures(1, &textures[2]);
	glEnd();

	glPopMatrix();
}
void drawLeftHand() {
	GLuint textures[3];
	
	glPushMatrix(); {
		//Upper Arm
		glPushMatrix(); {
			if (isJumping) {
				glRotatef(-20, 1, 0, 0);
			}
			if (isWalking) {
				if (UpperArmAngle > 5) {
					frontMax = true;
				}
				if (UpperArmAngle < 0) {
					frontMax = false;
				}
				glRotatef(UpperArmAngle, 1, 0, 0);
			}
			glRotatef(90, 0, 0, 1);
			textures[1] = loadTexture(mainTexture);
			drawCuboid3f(0.5, 2.5);
			glDeleteTextures(1, &textures[1]);
		}
		glPopMatrix();
		
		//Lower Arm
		glPushMatrix(); {
			if (isJumping) {
				glRotatef(-45, 1, 0, 0);
			}
			if (isWalking) {
				glRotatef(-LowerArmAngle, 1, 0, 0);
			}
			if (isAttack) {
				glRotatef(-90, 1, 0, 0);
			}
			glRotatef(-moveHand, 1, 0, 0);

			glPushMatrix(); {
				glTranslatef(0, -2.0, 0);
				glRotatef(90, 0, 0, 1);
				textures[1] = loadTexture(mainTexture);
				drawCuboid3f(0.5, 4);
				glDeleteTextures(1, &textures[1]);
			}
			glPopMatrix();

			//Hand
			if (choice == 1) {
				glPushMatrix(); {
					glTranslatef(-0.5, 0, 0);
					glRotatef(90, 0, 1, 0);

					glPushMatrix(); {
						glTranslatef(-0.65, -2.5, -0.005);
						textures[1] = loadTexture(subTexture);
						drawCuboid2f(1.0, 0.81, 0.51);
						glDeleteTextures(1, &textures[1]);
					}
					glPopMatrix();

					if (!isSword) {
						// 1 finger
						glPushMatrix();
						glTranslatef(-0.65, -2.8, 0.0);
						textures[1] = loadTexture(mainTexture);
						drawCuboid3f(0.3, 0.4);
						glDeleteTextures(1, &textures[1]);
						glPopMatrix();

						glPushMatrix();
						glTranslatef(-0.57, -2.8, 0.15);
						glRotatef(90, 1.0, 0.0, 0.0);
						textures[0] = loadTexture(subTexture);
						drawCylinder(0.08, 0.1);
						glDeleteTextures(1, &textures[0]);
						glPopMatrix();

						glPushMatrix();
						glTranslatef(-0.65, -3.2, 0.0);
						textures[1] = loadTexture(mainTexture);
						drawCuboid3f(0.3, 0.4);
						glDeleteTextures(1, &textures[1]);
						glPopMatrix();

						glPushMatrix();
						glTranslatef(-0.57, -3.2, 0.15);
						glRotatef(90, 1.0, 0.0, 0.0);
						textures[0] = loadTexture(subTexture);
						drawCylinder(0.08, 0.1);
						glDeleteTextures(1, &textures[0]);
						glPopMatrix();

						glPushMatrix();
						glTranslatef(-0.65, -3.6, 0.0);
						textures[1] = loadTexture(mainTexture);
						drawCuboid3f(0.3, 0.4);
						glDeleteTextures(1, &textures[1]);
						glPopMatrix();
						// end of hand

						// 1 finger
						glPushMatrix();
						glTranslatef(-0.45, -2.8, 0.0);
						textures[1] = loadTexture(mainTexture);
						drawCuboid3f(0.3, 0.4);
						glDeleteTextures(1, &textures[1]);
						glPopMatrix();

						glPushMatrix();
						glTranslatef(-0.37, -2.8, 0.15);
						glRotatef(90, 1.0, 0.0, 0.0);
						textures[0] = loadTexture(subTexture);
						drawCylinder(0.08, 0.1);
						glDeleteTextures(1, &textures[0]);
						glPopMatrix();

						glPushMatrix();
						glTranslatef(-0.45, -3.2, 0.0);
						textures[1] = loadTexture(mainTexture);
						drawCuboid3f(0.3, 0.4);
						glDeleteTextures(1, &textures[1]);
						glPopMatrix();

						glPushMatrix();
						glTranslatef(-0.37, -3.2, 0.15);
						glRotatef(90, 1.0, 0.0, 0.0);
						textures[0] = loadTexture(subTexture);
						drawCylinder(0.08, 0.1);
						glDeleteTextures(1, &textures[0]);
						glPopMatrix();

						glPushMatrix();
						glTranslatef(-0.45, -3.6, 0.0);
						textures[1] = loadTexture(mainTexture);
						drawCuboid3f(0.3, 0.4);
						glDeleteTextures(1, &textures[1]);
						glPopMatrix();
						// end of hand

						// 1 finger
						glPushMatrix();
						glTranslatef(-0.25, -2.8, 0.0);
						textures[1] = loadTexture(mainTexture);
						drawCuboid3f(0.3, 0.4);
						glDeleteTextures(1, &textures[1]);
						glPopMatrix();

						glPushMatrix();
						glTranslatef(-0.17, -2.8, 0.15);
						glRotatef(90, 1.0, 0.0, 0.0);
						textures[0] = loadTexture(subTexture);
						drawCylinder(0.08, 0.1);
						glDeleteTextures(1, &textures[0]);
						glPopMatrix();

						glPushMatrix();
						glTranslatef(-0.25, -3.2, 0.0);
						textures[1] = loadTexture(mainTexture);
						drawCuboid3f(0.3, 0.4);
						glDeleteTextures(1, &textures[1]);
						glPopMatrix();

						glPushMatrix();
						glTranslatef(-0.17, -3.2, 0.15);
						glRotatef(90, 1.0, 0.0, 0.0);
						textures[0] = loadTexture(subTexture);
						drawCylinder(0.08, 0.1);
						glDeleteTextures(1, &textures[0]);
						glPopMatrix();

						glPushMatrix();
						glTranslatef(-0.25, -3.6, 0.0);
						textures[1] = loadTexture(mainTexture);
						drawCuboid3f(0.3, 0.4);
						glDeleteTextures(1, &textures[1]);
						glPopMatrix();
						// end of hand

						// 1 finger
						glPushMatrix();
						glTranslatef(-0.05, -2.8, 0.0);
						textures[1] = loadTexture(mainTexture);
						drawCuboid3f(0.3, 0.4);
						glDeleteTextures(1, &textures[1]);
						glPopMatrix();

						glPushMatrix();
						glTranslatef(0.03, -2.8, 0.15);
						glRotatef(90, 1.0, 0.0, 0.0);
						textures[0] = loadTexture(subTexture);
						drawCylinder(0.08, 0.1);
						glDeleteTextures(1, &textures[0]);
						glPopMatrix();

						glPushMatrix();
						glTranslatef(-0.05, -3.2, 0.0);
						textures[1] = loadTexture(mainTexture);
						drawCuboid3f(0.3, 0.4);
						glDeleteTextures(1, &textures[1]);
						glPopMatrix();

						glPushMatrix();
						glTranslatef(0.03, -3.2, 0.15);
						glRotatef(90, 1.0, 0.0, 0.0);
						textures[0] = loadTexture(subTexture);
						drawCylinder(0.08, 0.1);
						glDeleteTextures(1, &textures[0]);
						glPopMatrix();

						glPushMatrix();
						glTranslatef(-0.05, -3.6, 0.0);
						textures[1] = loadTexture(mainTexture);
						drawCuboid3f(0.3, 0.4);
						glDeleteTextures(1, &textures[1]);
						glPopMatrix();
						// end of hand

						//thumb
						glPushMatrix();
						glTranslatef(-0.8, -2.2, 0.3);
						glRotatef(-90, 1.0, 1.0, 0.0);
						textures[1] = loadTexture(mainTexture);
						drawCuboid3f(0.3, 0.4);
						glDeleteTextures(1, &textures[1]);
						glPopMatrix();

						glPushMatrix();
						glTranslatef(-1.0, -2.3, 0.5);
						glRotatef(-90, 1.0, 1.0, 0.0);
						textures[1] = loadTexture(mainTexture);
						drawCuboid3f(0.3, 0.4);
						glDeleteTextures(1, &textures[1]);
						glPopMatrix();
					}
					if (isSword) {
						glPushMatrix(); {
							if (isAttack) {
								glTranslatef(0.5, -0.5, 1.5);
								glRotatef(45, 1, 1, 0);
							}
							glTranslatef(-3, -2.5, 0);
							glRotatef(-90, 0, 0, 1);
							drawSword();
							glPushMatrix();
							textures[0] = loadTexture("diamond.bmp");
							drawSword2();
							glDeleteTextures(1, &textures[0]);
							glPopMatrix();
						}
						glPopMatrix();
					}
				}
				glPopMatrix();
			}
			else if (choice == 2) {
				glTranslatef(-0.25, -0.50, 0.25);
				glRotatef(90, 1, 0, 0);
				textures[0] = loadTexture(subTexture);
				drawCylinder(0.5, 2.1);
				glDeleteTextures(1, &textures[0]);

				glPushMatrix(); {
					textures[0] = loadTexture("red4.bmp");
					glBegin(GL_TRIANGLE_FAN);

					float y3 = 0.0, x3 = 0.0;
					float x2, y2;
					float radius = 0.5;

					for (float i = 0; i <= 360; i++) {
						x2 = x3 + radius * (cos(i * PI / 180));
						y2 = y3 + radius * (sin(i * PI / 180));
						glVertex3f(x2, y2, 2.1);
					}
					glEnd();
					glDeleteTextures(1, &textures[0]);
				}
				glPopMatrix();

				glPushMatrix(); {
					glTranslatef(0, 0, -2.0);
					textures[0] = loadTexture("red4.bmp");
					glBegin(GL_TRIANGLE_FAN);

					float y3 = 0.0, x3 = 0.0;
					float x2, y2;
					float radius = 0.5;

					for (float i = 0; i <= 360; i++) {
						x2 = x3 + radius * (cos(i * PI / 180));
						y2 = y3 + radius * (sin(i * PI / 180));
						glVertex3f(x2, y2, 2);
					}
					glEnd();
					glDeleteTextures(1, &textures[0]);
				}
				glPopMatrix();

				glPushMatrix(); {
					glTranslatef(-0.5, -0.25, 0.25);
					textures[0] = loadTexture(mainTexture);
					drawCylinder(0.25, 1);
					glDeleteTextures(1, &textures[0]);
				}
				glPopMatrix();

				glPushMatrix(); {
					glTranslatef(-0.5, -0.25, -0.75);
					textures[0] = loadTexture("red4.bmp");
					glBegin(GL_TRIANGLE_FAN);

					float y3 = 0.0, x3 = 0.0;
					float x2, y2;
					float radius = 0.25;

					for (float i = 0; i <= 360; i++) {
						x2 = x3 + radius * (cos(i * PI / 180));
						y2 = y3 + radius * (sin(i * PI / 180));
						glVertex3f(x2, y2, 2);
					}
					glEnd();
					glDeleteTextures(1, &textures[0]);
				}
				glPopMatrix();

				glPushMatrix(); {
					glTranslatef(-0.5, -0.25, -1.75);
					textures[0] = loadTexture("red4.bmp");
					glBegin(GL_TRIANGLE_FAN);

					float y3 = 0.0, x3 = 0.0;
					float x2, y2;
					float radius = 0.25;

					for (float i = 0; i <= 360; i++) {
						x2 = x3 + radius * (cos(i * PI / 180));
						y2 = y3 + radius * (sin(i * PI / 180));
						glVertex3f(x2, y2, 2);
					}
					glEnd();
					glDeleteTextures(1, &textures[0]);
				}
				glPopMatrix();
				

				if (isFired && !isJumping && moveHand > 70) {
					glPushMatrix(); {
						
						if (energyStore < 2) {
							glScalef(energyStore += 0.1, energyStore += 0.1, energyStore += 0.1);
						}
						else {
							glTranslatef(0, 0, fireSpeed += 0.1);
						}

						glTranslatef(0, 0, 1.5);
						textures[2] = loadTexture("power.bmp");
						drawSphere(0.25);
						glDeleteTextures(1, &textures[2]);
					}
					glPopMatrix();
				}
			}

		}
		glPopMatrix();
	}
	glPopMatrix();
	
}
void drawRightHand() {
	GLuint textures[3];

	glPushMatrix(); {
		//Upper Arm
		glPushMatrix(); {
			if (isJumping) {
				glRotatef(-15, 1, 0, 0);
			}
			if (isWalking) {
				if (UpperArmAngle > 5) {
					frontMax = true;
				}
				if (UpperArmAngle < 0) {
					frontMax = false;
				}
				glRotatef(UpperArmAngle, 1, 0, 0);
			}
			glRotatef(90, 0, 0, 1);
			textures[1] = loadTexture(mainTexture);
			drawCuboid3f(0.5, 2.5);
			glDeleteTextures(1, &textures[1]);
		}
		glPopMatrix();

		//Lower Arm
		glPushMatrix(); {
			if (isJumping) {
				glRotatef(-50, 1, 0, 0);
			}
			if (isWalking) {
				glRotatef(-LowerArmAngle, 1, 0, 0);
			}
			if (isAttack) {
				glRotatef(-90, 1, 0, 0);
			}
			glRotatef(-moveHand, 1, 0, 0);

			glPushMatrix(); {
				glTranslatef(0, -2.0, 0);
				glRotatef(90, 0, 0, 1);
				textures[1] = loadTexture(mainTexture);
				drawCuboid3f(0.5, 4);
				glDeleteTextures(1, &textures[1]);
			}
			glPopMatrix();

			//Hand
			if (choice == 1) {
				glPushMatrix(); {
					glTranslatef(-0.5, 0, 0);
					glRotatef(90, 0, 1, 0);

					glPushMatrix(); {
						glTranslatef(-0.65, -2.5, -0.005);
						textures[1] = loadTexture(subTexture);
						drawCuboid2f(1.0, 0.81, 0.51);
						glDeleteTextures(1, &textures[1]);
					}
					glPopMatrix();

					
					// 1 finger
					glPushMatrix();
					glTranslatef(-0.65, -2.8, 0.0);
					textures[1] = loadTexture(mainTexture);
					drawCuboid3f(0.3, 0.4);
					glDeleteTextures(1, &textures[1]);
					glPopMatrix();

					glPushMatrix();
					glTranslatef(-0.57, -2.8, 0.15);
					glRotatef(90, 1.0, 0.0, 0.0);
					textures[0] = loadTexture(subTexture);
					drawCylinder(0.08, 0.1);
					glDeleteTextures(1, &textures[0]);
					glPopMatrix();

					glPushMatrix();
					glTranslatef(-0.65, -3.2, 0.0);
					textures[1] = loadTexture(mainTexture);
					drawCuboid3f(0.3, 0.4);
					glDeleteTextures(1, &textures[1]);
					glPopMatrix();

					glPushMatrix();
					glTranslatef(-0.57, -3.2, 0.15);
					glRotatef(90, 1.0, 0.0, 0.0);
					textures[0] = loadTexture(subTexture);
					drawCylinder(0.08, 0.1);
					glDeleteTextures(1, &textures[0]);
					glPopMatrix();

					glPushMatrix();
					glTranslatef(-0.65, -3.6, 0.0);
					textures[1] = loadTexture(mainTexture);
					drawCuboid3f(0.3, 0.4);
					glDeleteTextures(1, &textures[1]);
					glPopMatrix();
					// end of hand

					// 1 finger
					glPushMatrix();
					glTranslatef(-0.45, -2.8, 0.0);
					textures[1] = loadTexture(mainTexture);
					drawCuboid3f(0.3, 0.4);
					glDeleteTextures(1, &textures[1]);
					glPopMatrix();

					glPushMatrix();
					glTranslatef(-0.37, -2.8, 0.15);
					glRotatef(90, 1.0, 0.0, 0.0);
					textures[0] = loadTexture(subTexture);
					drawCylinder(0.08, 0.1);
					glDeleteTextures(1, &textures[0]);
					glPopMatrix();

					glPushMatrix();
					glTranslatef(-0.45, -3.2, 0.0);
					textures[1] = loadTexture(mainTexture);
					drawCuboid3f(0.3, 0.4);
					glDeleteTextures(1, &textures[1]);
					glPopMatrix();

					glPushMatrix();
					glTranslatef(-0.37, -3.2, 0.15);
					glRotatef(90, 1.0, 0.0, 0.0);
					textures[0] = loadTexture(subTexture);
					drawCylinder(0.08, 0.1);
					glDeleteTextures(1, &textures[0]);
					glPopMatrix();

					glPushMatrix();
					glTranslatef(-0.45, -3.6, 0.0);
					textures[1] = loadTexture(mainTexture);
					drawCuboid3f(0.3, 0.4);
					glDeleteTextures(1, &textures[1]);
					glPopMatrix();
					// end of hand

					// 1 finger
					glPushMatrix();
					glTranslatef(-0.25, -2.8, 0.0);
					textures[1] = loadTexture(mainTexture);
					drawCuboid3f(0.3, 0.4);
					glDeleteTextures(1, &textures[1]);
					glPopMatrix();

					glPushMatrix();
					glTranslatef(-0.17, -2.8, 0.15);
					glRotatef(90, 1.0, 0.0, 0.0);
					textures[0] = loadTexture(subTexture);
					drawCylinder(0.08, 0.1);
					glDeleteTextures(1, &textures[0]);
					glPopMatrix();

					glPushMatrix();
					glTranslatef(-0.25, -3.2, 0.0);
					textures[1] = loadTexture(mainTexture);
					drawCuboid3f(0.3, 0.4);
					glDeleteTextures(1, &textures[1]);
					glPopMatrix();

					glPushMatrix();
					glTranslatef(-0.17, -3.2, 0.15);
					glRotatef(90, 1.0, 0.0, 0.0);
					textures[0] = loadTexture(subTexture);
					drawCylinder(0.08, 0.1);
					glDeleteTextures(1, &textures[0]);
					glPopMatrix();

					glPushMatrix();
					glTranslatef(-0.25, -3.6, 0.0);
					textures[1] = loadTexture(mainTexture);
					drawCuboid3f(0.3, 0.4);
					glDeleteTextures(1, &textures[1]);
					glPopMatrix();
					// end of hand

					// 1 finger
					glPushMatrix();
					glTranslatef(-0.05, -2.8, 0.0);
					textures[1] = loadTexture(mainTexture);
					drawCuboid3f(0.3, 0.4);
					glDeleteTextures(1, &textures[1]);
					glPopMatrix();

					glPushMatrix();
					glTranslatef(0.03, -2.8, 0.15);
					glRotatef(90, 1.0, 0.0, 0.0);
					textures[0] = loadTexture(subTexture);
					drawCylinder(0.08, 0.1);
					glDeleteTextures(1, &textures[0]);
					glPopMatrix();

					glPushMatrix();
					glTranslatef(-0.05, -3.2, 0.0);
					textures[1] = loadTexture(mainTexture);
					drawCuboid3f(0.3, 0.4);
					glDeleteTextures(1, &textures[1]);
					glPopMatrix();

					glPushMatrix();
					glTranslatef(0.03, -3.2, 0.15);
					glRotatef(90, 1.0, 0.0, 0.0);
					textures[0] = loadTexture(subTexture);
					drawCylinder(0.08, 0.1);
					glDeleteTextures(1, &textures[0]);
					glPopMatrix();

					glPushMatrix();
					glTranslatef(-0.05, -3.6, 0.0);
					textures[1] = loadTexture(mainTexture);
					drawCuboid3f(0.3, 0.4);
					glDeleteTextures(1, &textures[1]);
					glPopMatrix();
					// end of hand

					//thumb
					glPushMatrix();
					glTranslatef(-1.1, -2.0, 0.0);
					glRotatef(90, 1.0, 1.0, 0.0);
					textures[0] = loadTexture(mainTexture);
					drawCuboid3f(0.3, 0.4);
					glDeleteTextures(1, &textures[0]);
					glPopMatrix();

					glPushMatrix();
					glTranslatef(-1.2, -2.2, -0.2);
					glRotatef(90, 1.0, 1.0, 0.0);
					textures[0] = loadTexture(mainTexture);
					drawCuboid3f(0.3, 0.4);
					glDeleteTextures(1, &textures[0]);
					glPopMatrix();
					
					
				}
				glPopMatrix();
			}
			else if (choice == 2) {
				glTranslatef(-0.25, -0.50, 0.25);
				glRotatef(90, 1, 0, 0);
				textures[0] = loadTexture(mainTexture);
				drawCylinder(0.5, 2.1);
				glDeleteTextures(1, &textures[0]);

				glPushMatrix(); {
					textures[0] = loadTexture("red4.bmp");
					glBegin(GL_TRIANGLE_FAN);

					float y3 = 0.0, x3 = 0.0;
					float x2, y2;
					float radius = 0.5;

					for (float i = 0; i <= 360; i++) {
						x2 = x3 + radius * (cos(i * PI / 180));
						y2 = y3 + radius * (sin(i * PI / 180));
						glVertex3f(x2, y2, 2.1);
					}
					glEnd();
					glDeleteTextures(1, &textures[0]);
				}
				glPopMatrix();

				glPushMatrix(); {
					glTranslatef(0, 0, -2.0);
					textures[0] = loadTexture("red4.bmp");
					glBegin(GL_TRIANGLE_FAN);

					float y3 = 0.0, x3 = 0.0;
					float x2, y2;
					float radius = 0.5;

					for (float i = 0; i <= 360; i++) {
						x2 = x3 + radius * (cos(i * PI / 180));
						y2 = y3 + radius * (sin(i * PI / 180));
						glVertex3f(x2, y2, 2);
					}
					glEnd();
					glDeleteTextures(1, &textures[0]);
				}
				glPopMatrix();

				glPushMatrix(); {
					glTranslatef(0.5, -0.25, 0.25);
					textures[0] = loadTexture(mainTexture);
					drawCylinder(0.25, 1);
					glDeleteTextures(1, &textures[0]);
				}
				glPopMatrix();

				glPushMatrix(); {
					glTranslatef(0.5, -0.25, -0.75);
					textures[0] = loadTexture("red4.bmp");
					glBegin(GL_TRIANGLE_FAN);

					float y3 = 0.0, x3 = 0.0;
					float x2, y2;
					float radius = 0.25;

					for (float i = 0; i <= 360; i++) {
						x2 = x3 + radius * (cos(i * PI / 180));
						y2 = y3 + radius * (sin(i * PI / 180));
						glVertex3f(x2, y2, 2);
					}
					glEnd();
					glDeleteTextures(1, &textures[0]);
				}
				glPopMatrix();

				glPushMatrix(); {
					glTranslatef(0.5, -0.25, -1.75);
					textures[0] = loadTexture("red4.bmp");
					glBegin(GL_TRIANGLE_FAN);

					float y3 = 0.0, x3 = 0.0;
					float x2, y2;
					float radius = 0.25;

					for (float i = 0; i <= 360; i++) {
						x2 = x3 + radius * (cos(i * PI / 180));
						y2 = y3 + radius * (sin(i * PI / 180));
						glVertex3f(x2, y2, 2);
					}
					glEnd();
					glDeleteTextures(1, &textures[0]);
				}
				glPopMatrix();


				if (isFired && !isJumping && moveHand > 70) {
					glPushMatrix(); {
						if (energyStore < 2) {
							energyStore += 0.01;
							glScalef(energyStore, energyStore, energyStore);
						}
						else {
							glTranslatef(0, 0, fireSpeed += 1);
							isFired=false;
						}

						glTranslatef(0, 0, 1.5);
						textures[2] = loadTexture("power.bmp");
						drawSphere(0.25);
						glDeleteTextures(1, &textures[2]);
					}
					glPopMatrix();
				}
			}

		}
		glPopMatrix();
	}
	glPopMatrix();

}
void drawHead() {

	GLuint textures[3];

	//head
	glPushMatrix();
	//glColor3f(1.0, 1.0, 1.0);
	textures[0] = loadTexture("metalTexture.bmp");
	drawSphere(0.75);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.8, -0.6);
	//left ear
	glPushMatrix();
	glTranslatef(-0.2, -0.15, 0.3);
	glRotatef(30, 0, 0, 1);
	glRotatef(180, 1, 0, 0);
	//drawPyramid(-0.5);
	
	//textures[0] = loadTexture(mainTexture);
	glBegin(GL_QUADS);
	//Face1 : Bottom
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5, 0, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5, 0, -0.5);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, -0.5);
	//glDeleteTextures(1, &textures[0]);
	glEnd();

	textures[0] = loadTexture("metalTexture.bmp");
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5, 0, 0);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(-0.5, -0.5, -0.5);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5, 0, -0.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5, 0, 0);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(-0.5, -0.5, -0.5);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5, 0, -0.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, 0, -0.5);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(-0.5, -0.5, -0.5);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, 0, -0.5);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	//right ear
	glPushMatrix();
	glTranslatef(0.2, -0.15, 0.3);
	glRotatef(-30, 0, 0, 1);
	textures[0] = loadTexture("metalTexture.bmp");
	drawPyramid(0.5);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPopMatrix();

	//neck
	glPushMatrix();
	glTranslatef(0.0, -0.65, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	textures[0] = loadTexture(mainTexture);
	drawCylinder(0.2, 0.3);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	//eyes
	glPushMatrix();
	glTranslatef(-0.75, 0, 0.25);

	textures[0] = loadTexture("mint.bmp");
	glBegin(GL_TRIANGLE_FAN);
	//glColor3f(0, 0, 0);
	glTexCoord2f(-0.8, 1.0);
	glVertex3f(0.75, -0.1, 0.0);
	glTexCoord2f(0.8, 1.0);
	glVertex3f(0, -0.1, 0);
	glTexCoord2f(1.0, 0.8);
	glVertex3f(0.15, -0.1, 0.5);
	glTexCoord2f(0.8, 0.0);
	glVertex3f(0.75, -0.1, 0.65);
	glTexCoord2f(-0.8, 0.0);
	glVertex3f(1.35, -0.1, 0.5);
	glTexCoord2f(-1.0, 0.8);
	glVertex3f(1.5, -0.1, 0);
	glEnd();
	glDeleteTextures(1, &textures[0]);

	textures[0] = loadTexture("mint.bmp");
	glBegin(GL_QUADS);
	//glColor3f(0, 0, 0.80);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, -0.1, 0.0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, 0.2, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.15, 0.2, 0.5);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.15, -0.1, 0.5);

	//glColor3f(0, 1, 0.80);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.15, -0.1, 0.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.15, 0.2, 0.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.75, 0.2, 0.65);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.75, -0.1, 0.65);

	//glColor3f(0, 1, 0.80);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.75, -0.1, 0.65);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.75, 0.2, 0.65);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.35, 0.2, 0.5);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.35, -0.1, 0.5);

	//glColor3f(0, 0, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.35, -0.1, 0.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.35, 0.2, 0.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.5, 0.2, 0.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.5, -0.1, 0.0);
	glEnd();
	glDeleteTextures(1, &textures[0]);

	//textures[0] = loadTexture("black1.bmp");
	glBegin(GL_TRIANGLE_FAN);
	//glColor3f(0, 0, 0);
	glVertex3f(0.75, 0.2, 0.0);
	glVertex3f(0, 0.2, 0);
	glVertex3f(0.15, 0.2, 0.5);
	glVertex3f(0.75, 0.2, 0.65);
	glVertex3f(1.35, 0.2, 0.5);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.5, 0.2, 0);
	glEnd();
	//glDeleteTextures(1, &textures[0]);

	glEnd();

	glPopMatrix();
}
void drawBody() {
	GLuint textures[3];
	//body
	glPushMatrix();

	glPushMatrix();
	glTranslatef(-1.3, 1.3, 0);
	textures[0] = loadTexture(mainTexture);
	drawCube(0.9);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.4, 1.3, 0);
	textures[1] = loadTexture(mainTexture);
	drawCube(0.9);
	glDeleteTextures(1, &textures[1]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, 1.125, 0);
	textures[2] = loadTexture(subTexture);
	drawCube(1.0);
	glDeleteTextures(1, &textures[2]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5, 1.125, 0);
	textures[2] = loadTexture(subTexture);
	drawCube(1.0);
	glDeleteTextures(1, &textures[2]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 1.125, 0);
	textures[2] = loadTexture(subTexture);
	drawCube(1.0);
	glDeleteTextures(1, &textures[2]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.125, 0.75, 0);
	textures[2] = loadTexture(mainTexture);
	drawCube(1.125);
	glDeleteTextures(1, &textures[2]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.75, 0);
	textures[2] = loadTexture(mainTexture);
	drawCube(1.125);
	glDeleteTextures(1, &textures[2]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 1.3125, 0.75);
	////glColor3f(1, 0, 1);
	textures[2] = loadTexture(subTexture);
	drawCylinder(0.55, 0.5);
	glDeleteTextures(1, &textures[2]);

	textures[2] = loadTexture(subTexture);
	glBegin(GL_TRIANGLE_FAN);
	////glColor3f(1.0, 0.0, 0.0);
	float y3 = 0.0, x3 = 0.0;
	float x2, y2;
	float radius = 0.55;

	for (float i = 0; i <= 360; i++) {
		x2 = x3 + radius * (cos(i * PI / 180));
		y2 = y3 + radius * (sin(i * PI / 180));
		glVertex3f(x2, y2, 0.5);
	}
	glEnd();
	glDeleteTextures(1, &textures[2]);

	glPushMatrix();
	glTranslatef(0, 0, 0.45);
	////glColor3f(0, 1, 1);
	textures[2] = loadTexture("yellow.bmp");
	drawSphere(0.25);
	glDeleteTextures(1, &textures[2]);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	textures[2] = loadTexture(subTexture);
	drawCube(0.75);
	glDeleteTextures(1, &textures[2]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.75, 0, 0);
	textures[2] = loadTexture(subTexture);
	drawCube(0.75);
	glDeleteTextures(1, &textures[2]);
	glPopMatrix();

	glPopMatrix();
}
void drawBodyBack() {
	GLuint textures[4];

	//--left--
	glPushMatrix();
	//glColor3f(1, 0, 0);
	glTranslatef(-1.0, 0.0, 0.0);
	textures[0] = loadTexture("rocket.bmp");
	drawCuboid2f(2.0, 0.5, 0.4);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	//glColor3f(1, 1, 1);
	glTranslatef(-0.3, 2.0, 0.5);
	textures[1] = loadTexture(subTexture);
	drawCube(0.3);
	glDeleteTextures(1, &textures[1]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0, 2.0, 0.5);
	//glColor3f(1, 1, 1);
	textures[1] = loadTexture(subTexture);
	drawCube(0.3);
	glDeleteTextures(1, &textures[1]);
	glPopMatrix();

	glPushMatrix();
	//glColor3f(0, 0, 1);
	glTranslatef(-0.75, 0.5, 0.7);
	textures[2] = loadTexture("blue2.bmp");
	drawCuboid2f(1.0, 0.1, 0.2);
	glDeleteTextures(1, &textures[2]);
	glPopMatrix();

	glPushMatrix();
	//glColor3f(0, 0, 1);
	glTranslatef(-0.55, 0.5, 0.7);
	textures[2] = loadTexture("blue2.bmp");
	drawCuboid2f(1.0, 0.1, 0.2);
	glDeleteTextures(1, &textures[2]);
	glPopMatrix();

	glPushMatrix();
	//glColor3f(0, 0, 1);
	glTranslatef(-0.35, 0.5, 0.7);
	textures[2] = loadTexture("blue2.bmp");
	drawCuboid2f(1.0, 0.1, 0.2);
	glDeleteTextures(1, &textures[2]);
	glPopMatrix();

	glPushMatrix();
	//glColor3f(1, 1, 1);
	glTranslatef(-0.3, -0.3, 0.5);
	textures[1] = loadTexture(subTexture);
	drawCube(0.3);
	glDeleteTextures(1, &textures[1]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0, -0.3, 0.5);
	//glColor3f(1, 1, 1);
	textures[1] = loadTexture(subTexture);
	drawCube(0.3);
	glDeleteTextures(1, &textures[1]);
	glPopMatrix();

	//cylinder
	glPushMatrix();
	//glColor3f(1, 1, 0);
	glTranslatef(-0.5, 3.5, 0.5);
	glRotatef(90, 1.0, 0.0, 0.0);
	textures[1] = loadTexture(subTexture);
	drawCylinder(0.3, 1.5);
	glDeleteTextures(1, &textures[1]);
	glPopMatrix();

	//cone
	glPushMatrix();
	//glColor3f(0, 0, 0);
	glTranslatef(2.1, 4.0, 0.5);
	glRotatef(90, 1.0, 0.0, 0.0);
	textures[0] = loadTexture("rocket.bmp");
	drawCone(0.3, 0.5);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();
	//--end of left--

	//--center--
	glPushMatrix();
	//glColor3f(0, 1, 1);
	glScalef(1.0, 1.0, 0.5);
	glTranslatef(0.0, -0.3, 0.0);
	textures[0] = loadTexture("rocket.bmp");
	drawCuboid3f(2.0, 0.8);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();
	//--end of center

	//--right--
	glPushMatrix();
	//glColor3f(1, 0, 0);
	glTranslatef(1.6, 0.0, 0.0);
	textures[0] = loadTexture("rocket.bmp");
	drawCuboid2f(2.0, 0.5, 0.4);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	//glColor3f(1, 1, 1);
	glTranslatef(2.3, 2.0, 0.5);
	textures[1] = loadTexture(subTexture);
	drawCube(0.3);
	glDeleteTextures(1, &textures[1]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.6, 2.0, 0.5);
	//glColor3f(1, 1, 1);
	textures[1] = loadTexture(subTexture);
	drawCube(0.3);
	glDeleteTextures(1, &textures[1]);
	glPopMatrix();

	glPushMatrix();
	//glColor3f(0, 0, 1);
	glTranslatef(1.80, 0.5, 0.7);
	textures[2] = loadTexture("blue2.bmp");
	drawCuboid2f(1.0, 0.1, 0.2);
	glDeleteTextures(1, &textures[2]);
	glPopMatrix();

	glPushMatrix();
	//glColor3f(0, 0, 1);
	glTranslatef(2.0, 0.5, 0.7);
	textures[2] = loadTexture("blue2.bmp");
	drawCuboid2f(1.0, 0.1, 0.2);
	glDeleteTextures(1, &textures[2]);
	glPopMatrix();

	glPushMatrix();
	//glColor3f(0, 0, 1);
	glTranslatef(2.20, 0.5, 0.7);
	textures[2] = loadTexture("blue2.bmp");
	drawCuboid2f(1.0, 0.1, 0.2);
	glDeleteTextures(1, &textures[2]);
	glPopMatrix();

	glPushMatrix();
	//glColor3f(1, 1, 1);
	glTranslatef(1.6, -0.3, 0.5);
	textures[1] = loadTexture(subTexture);
	drawCube(0.3);
	glDeleteTextures(1, &textures[1]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.3, -0.3, 0.5);
	//glColor3f(1, 1, 1);
	textures[1] = loadTexture(subTexture);
	drawCube(0.3);
	glDeleteTextures(1, &textures[1]);
	glPopMatrix();

	//cylinder
	glPushMatrix();
	//glColor3f(1, 1, 0);
	glTranslatef(2.1, 3.5, 0.5);
	glRotatef(90, 1.0, 0.0, 0.0);
	textures[1] = loadTexture(subTexture);
	drawCylinder(0.3, 1.5);
	glDeleteTextures(1, &textures[1]);
	glPopMatrix();

	//cone
	glPushMatrix();
	//glColor3f(0, 0, 0);
	glTranslatef(-0.5, 4.0, 0.5);
	glRotatef(90, 1.0, 0.0, 0.0);
	textures[0] = loadTexture("rocket.bmp");
	drawCone(0.3, 0.5);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();
	//--end of right--
}
void drawBodyBack2() {
	//--center--
	//trapezium
	glPushMatrix();
	//glColor3f(1, 0, 1);
	glTranslatef(0.8, 1.7, 0.0);
	glScalef(8, 8, 8);
	
	glBegin(GL_POLYGON);
	//bottom
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.1, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.1, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.1, 0.0, 0.1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.1, 0.0, 0.1);

	//left
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.1, 0.0, 0.1);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.1, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.05, 0.1, 0.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.05, 0.1, 0.1);

	//top
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.05, 0.1, 0.1);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.05, 0.1, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.05, 0.1, 0.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.05, 0.1, 0.1);

	//back
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.05, 0.1, 0.1);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.05, 0.1, 0.1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.10, 0.0, 0.1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.10, 0.0, 0.1);

	//right
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.10, 0.0, 0.1);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.05, 0.1, 0.1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.05, 0.1, 0.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.1, 0.0, 0.0);

	//front
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.1, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.05, 0.1, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.05, 0.1, 0.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.05, 0.0, 0.0);
	glEnd();
	

	glPopMatrix();
}
void drawLowerBody() {
	GLuint textures[3];

	glPushMatrix();
	glTranslatef(0.0, 1.0, -0.3);
	glRotatef(90, 1.0, 0.0, 0.0);
	textures[0] = loadTexture(subTexture);
	drawCylinder(0.2, 1.0);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.875, -0.25, -0.5);
	glRotatef(90, 0, 1, 0);
	textures[0] = loadTexture(subTexture);
	drawCylinder(0.5, 1.75);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.875, -0.25, -0.5);
	glRotatef(90, 0, 1, 0);
	textures[0] = loadTexture(subTexture);
	glBegin(GL_TRIANGLE_FAN);
	//glColor3f(1.0, 0.0, 0.0);
	float y3 = 0.0, x3 = 0.0;
	float x2, y2;
	float radius = 0.5;

	for (float i = 0; i <= 360; i++) {
		x2 = x3 + radius * (cos(i * PI / 180));
		y2 = y3 + radius * (sin(i * PI / 180));
		glVertex3f(x2, y2, 1.75);
	}
	glEnd();
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.875, -0.25, 1.25);
	glRotatef(90, 0, 1, 0);
	glTranslatef(1.75, 0, 0);
	textures[0] = loadTexture(subTexture);
	glBegin(GL_TRIANGLE_FAN);
	//glColor3f(1.0, 0.0, 0.0);
	radius = 0.5;

	for (float i = 0; i <= 360; i++) {
		x2 = x3 + radius * (cos(i * PI / 180));
		y2 = y3 + radius * (sin(i * PI / 180));
		glVertex3f(x2, y2, 0);
	}
	glEnd();
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();
	
}
void drawLeftLeg() {
	GLuint textures[3];

	//upper
	glPushMatrix();
	if (isJumping) {
		glRotatef(-20, 1, 0, 0);
	}
	if (isWalking) {
		glRotatef(UpperLegAngle, 1, 0, 0);
	}
	//glScalef(1.0, 1.0, 0.2);
	glTranslatef(0.0, 0.5, 0.0);
	glRotatef(180, 1.0, 1.0, 0.0);
	textures[0] = loadTexture(subTexture);
	drawCuboid3f(0.5, 2.5);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	//joint
	glPushMatrix();
	//glScalef(1.0, 1.0, 0.2);
	glTranslatef(0.25, 0.15, -0.25);
	textures[0] = loadTexture(mainTexture);
	drawSphere(0.3);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	//lower
	glPushMatrix();
	//glScalef(1.0, 1.0, 0.2);
	if (isJumping) {
		glRotatef(30, 1, 0, 0);
	}
	if (isWalking) {
		glRotatef(LowerLegAngle, 1, 0, 0);
	}
	glTranslatef(0.0, -1.7, 0.0);
	glRotatef(180, 1.0, 1.0, 0.0);
	textures[0] = loadTexture(subTexture);
	drawCuboid3f(0.5, 3);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	//sole
	glPushMatrix();
	if (isJumping) {
		glRotatef(30, 1, 0, 0);
	}if (isWalking) {
		glRotatef(LowerLegAngle, 1, 0, 0);
	}
	//glScalef(1.5, 0.5, 0.2);
	glTranslatef(-0.1, -2.0, -0.58);
	textures[0] = loadTexture(mainTexture);
	drawCube(0.7);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	if (isJumping) {
		glRotatef(30, 1, 0, 0);
	}
	if (isWalking) {
		glRotatef(LowerLegAngle, 1, 0, 0);
	}
	glTranslatef(0.7, -2.3, 0.15);
	glRotatef(90, 0.0, 0.0, 1.0);
	textures[0] = loadTexture(subTexture);
	drawCuboid2f(0.8, 0.5, 1.0);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	if (isJumping) {
		glRotatef(30, 1, 0, 0);
	}
	if (isWalking) {
		glRotatef(LowerLegAngle, 1, 0, 0);
	}
	glTranslatef(0.7, -2.3, -1.2);
	glRotatef(90, 0.0, 0.0, 1.0);
	textures[0] = loadTexture(subTexture);
	drawCuboid2f(0.8, 0.5, 0.8);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

}
void drawRightLeg() {
	GLuint textures[3];

	//upper
	glPushMatrix();
	if (isJumping) {
		glRotatef(-20, 1, 0, 0);
	}
	if (isWalking) {
		glRotatef(-UpperLegAngle, 1, 0, 0);
	}
	//glScalef(1.0, 1.0, 0.2);
	glTranslatef(0.0, 0.5, 0.0);
	glRotatef(180, 1.0, 1.0, 0.0);
	textures[0] = loadTexture(subTexture);
	drawCuboid3f(0.5, 2.5);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	//joint
	glPushMatrix();
	//glScalef(1.0, 1.0, 0.2);
	glTranslatef(0.25, 0.15, -0.25);
	textures[0] = loadTexture(mainTexture);
	drawSphere(0.3);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	//lower
	glPushMatrix();
	//glScalef(1.0, 1.0, 0.2);
	if (isJumping) {
		glRotatef(30, 1, 0, 0);
	}
	if (isWalking) {
		glRotatef(-LowerLegAngle, 1, 0, 0);
	}
	glTranslatef(0.0, -1.7, 0.0);
	glRotatef(180, 1.0, 1.0, 0.0);
	textures[0] = loadTexture(subTexture);
	drawCuboid3f(0.5, 3);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	//sole
	glPushMatrix();
	if (isJumping) {
		glRotatef(30, 1, 0, 0);
	}
	if (isWalking) {
		glRotatef(-LowerLegAngle, 1, 0, 0);
	}
	//glScalef(1.5, 0.5, 0.2);
	glTranslatef(-0.1, -2.0, -0.58);
	textures[0] = loadTexture(mainTexture);
	drawCube(0.7);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	if (isJumping) {
		glRotatef(30, 1, 0, 0);
	}
	if (isWalking) {
		glRotatef(-LowerLegAngle, 1, 0, 0);
	}
	glTranslatef(0.7, -2.3, 0.15);
	glRotatef(90, 0.0, 0.0, 1.0);
	textures[0] = loadTexture(subTexture);
	drawCuboid2f(0.8, 0.5, 1.0);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	if (isJumping) {
		glRotatef(30, 1, 0, 0);
	}
	if (isWalking) {
		glRotatef(-LowerLegAngle, 1, 0, 0);
	}
	glTranslatef(0.7, -2.3, -1.2);
	glRotatef(90, 0.0, 0.0, 1.0);
	textures[0] = loadTexture(subTexture);
	drawCuboid2f(0.8, 0.5, 0.8);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

}
void drawTail() {
	GLuint textures[3];
	
	glPushMatrix();
	textures[0] = loadTexture(mainTexture);
	drawSphere(0.2);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1, -0.2, 0.0);
	textures[0] = loadTexture(mainTexture);
	drawSphere(0.2);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.2, -0.4, 0.0);
	textures[0] = loadTexture(mainTexture);
	drawSphere(0.2);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3, -0.6, 0.0);
	textures[0] = loadTexture(mainTexture);
	drawSphere(0.2);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.4, -0.8, 0.0);
	textures[0] = loadTexture(mainTexture);
	drawSphere(0.2);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, -0.9, 0.0);
	textures[0] = loadTexture(mainTexture);
	drawSphere(0.2);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.6, -1.0, 0.0);
	textures[0] = loadTexture(mainTexture);
	drawSphere(0.2);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.7, -1.1, 0.0);
	textures[0] = loadTexture(mainTexture);
	drawSphere(0.2);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.8, -1.2, 0.0);
	textures[0] = loadTexture(mainTexture);
	drawSphere(0.2);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.85, -1.25, 0.0);
	textures[0] = loadTexture(mainTexture);
	drawSphere(0.2);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.90, -1.25, 0.0);
	textures[0] = loadTexture(mainTexture);
	drawSphere(0.2);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.95, -1.25, 0.0);
	textures[0] = loadTexture(mainTexture);
	drawSphere(0.2);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.00, -1.25, 0.0);
	textures[0] = loadTexture(mainTexture);
	drawSphere(0.2);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.1, -1.25, 0.0);
	textures[0] = loadTexture(mainTexture);
	drawSphere(0.2);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.2, -1.25, 0.0);
	textures[0] = loadTexture(mainTexture);
	drawSphere(0.2);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.3, -1.25, 0.0);
	textures[0] = loadTexture(mainTexture);
	drawSphere(0.2);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.4, -1.25, 0.0);
	textures[0] = loadTexture(mainTexture);
	drawSphere(0.2);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.45, -1.2, 0.0);
	textures[0] = loadTexture(mainTexture);
	drawSphere(0.2);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, -1.15, 0.0);
	textures[0] = loadTexture(mainTexture);
	drawSphere(0.2);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.55, -1.1, 0.0);
	textures[0] = loadTexture(mainTexture);
	drawSphere(0.2);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.6, -1.05, 0.0);
	textures[0] = loadTexture(mainTexture);
	drawSphere(0.2);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.65, -1.00, 0.0);
	textures[0] = loadTexture(mainTexture);
	drawSphere(0.2);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.70, -0.95, 0.0);
	textures[0] = loadTexture(mainTexture);
	drawSphere(0.2);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.75, -0.90, 0.0);
	textures[0] = loadTexture(mainTexture);
	drawSphere(0.2);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.4, -0.1, 0.0);
	glRotatef(50, 0.0, 0.0, 1.0);
	glRotatef(-90, 0.0, 1.0, 0.0);
	textures[0] = loadTexture(mainTexture);
	drawCone(0.2, 1.0);
	glDeleteTextures(1, &textures[0]);
	glPopMatrix();
}

void projection() {
	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();
		
	if (isOrtho) {
		glOrtho(-7.0, 7.0, -7.0, 7.0, -7.0, 7.0);
	}
	else {
		gluPerspective(10.0, 1.0, -1.0, 1.0);
		glFrustum(-7.0, 7.0, -7.0, 7.0, 1.0, 14.0);
	}
}
void lighting() {
	if (lightOn) {
		
		glEnable(GL_LIGHTING);
		
	}
	else
		glDisable(GL_LIGHTING);
	
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diff);
	glLightfv(GL_LIGHT1, GL_POSITION, posD);
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(posD[0], posD[1], posD[2]);
	drawSphere(0.1);
	glPopMatrix();
	glEnable(GL_LIGHT1);
}

void background(float size) {

	GLUquadricObj* sphere2 = NULL;
	sphere2 = gluNewQuadric();
	gluQuadricDrawStyle(sphere2, GLU_FILL);
	gluQuadricTexture(sphere2, true);
	gluSphere(sphere2, 10.0, 30, 30);
	gluDeleteQuadric(sphere2);

}

void display()
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5, 0.5, 0.5, 0);

	//--texture
	GLuint textures[3];
	GLuint swordTextures[3];

	glPushMatrix();
		glTranslatef(0, 0, 5.0);
		textures[0] = loadTexture(backgroundChoice);
		background(14.0);
		glDeleteTextures(1, &textures[0]);
	glPopMatrix();
	
	projection();
	lighting();
	
	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();
		
		if (isJumping) {
			glLoadIdentity();
			glTranslatef(0, 1, 0);
		}
		else
			glLoadIdentity();

		if (isWalking) {	
				glTranslatef(0, 0, walkingDistance);
		}
		if (isOrtho) {
			glRotatef(Rx, 1.0, 0.0, 0.0);
			glRotatef(Ry, 0.0, 1.0, 0.0);
			
		}
		glTranslatef(tx, 0, tz);

		glPushMatrix();{
			if (isNod) {
				if (control==1) {
					glRotatef(10, 1, 0, 0);
					control = 0;
				}
				else if (control == 0) {
					glRotatef(-10, 1, 0, 0);
					control = 1;
				}
				
					
			}
			if (isShakingHead) {
				if (control==1) {
					glRotatef(10, 0, 1, 0);
					control = 0;
				}
				else if (control==0) {
					glRotatef(-30, 0, 1, 0);
					control = 1;
				}
				
					
			}
			glTranslatef(0.0, 3.5, -0.2);
			drawHead();
		}
		glPopMatrix();

		glPushMatrix();{
			glTranslatef(0.0, 0.45, -0.7);

			glPushMatrix();{
				if (isWalking) {
					if (UpperArmAngle > 20) {
						frontMax = true;
					}
					if (UpperArmAngle < -20) {
						frontMax = false;
					}
					glRotatef(UpperArmAngle, 1, 0, 0);
				}
				glTranslatef(1.8, 1.7, 0.5);
				glRotatef(45, 0.0, 0.0, -1.0);
				glScalef(0.5, 0.5, 1.0);

				drawShoulder();
			}
			glPopMatrix();

			glPushMatrix();{
				if (isWalking) {
					if (UpperArmAngle > 20) {
						frontMax = true;
					}
					if (UpperArmAngle < -20) {
						frontMax = false;
					}
					glRotatef(UpperArmAngle, 1, 0, 0);
				}
				glTranslatef(-1.8, 1.7, 0.5);
				glRotatef(45, 0.0, 0.0, 1.0);
				glScalef(0.5, 0.5, 1.0);
				drawShoulder();
			}
			glPopMatrix();

			glPushMatrix();{
				if (isWalking) {
					if (UpperArmAngle > 20) {
						frontMax = true;
					}
					if (UpperArmAngle < -20) {
						frontMax = false;
					}
					glRotatef(-UpperArmAngle, 1, 0, 0);
				}
					glTranslatef(2.1, 0.5, 0.3);
					drawRightHand();
				}
			glPopMatrix();

			glPushMatrix();{
					glTranslatef(-1.6, 0.5, 0.3);
					drawLeftHand();
				}
			glPopMatrix();
		
			glPushMatrix();
				drawBody();
			glPopMatrix();

		}
		glPopMatrix();

		glPushMatrix(); {
			glTranslatef(0.8, 1.0, -0.8);
			glRotatef(180, 0.0, 1.0, 0.0);
			drawBodyBack();
			glPushMatrix();
			textures[0] = loadTexture("rocket.bmp");
			drawBodyBack2();
			glDeleteTextures(1, &textures[0]);
			glPopMatrix();
		}
		glPopMatrix();

		glPushMatrix();{
			drawLowerBody();
		}
		glPopMatrix();

		//left leg
		glPushMatrix();{
			//glColor3f(0, 1, 1);
			glTranslatef(-1.0, -2.5, 0.0);
			drawLeftLeg();
		}
		glPopMatrix();

		//right leg
		glPushMatrix();{
			//glColor3f(0, 0, 1);
			glTranslatef(0.5, -2.5, 0.0);
			drawRightLeg();
		}
		glPopMatrix();
	
		glPushMatrix();{
			if (!isSword) {
				glTranslatef(3, -1, 0);
				drawSword();
				drawSword2();
			}
		}
		glPopMatrix();

		glPushMatrix();{
		glTranslatef(0.0, -0.5, -1.0);
		glRotatef(90, 0.0, 1.0, 0.0);
		drawTail();
		}
		glPopMatrix();

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
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