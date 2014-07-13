#include <windows.h>
#include <gl/gl.h>

#include "LDFS.h"

void LDFS_EnableOpenGL(HWND LDFS_hWnd, HDC *LDFS_hDC, HGLRC *LDFS_hRC) {
	PIXELFORMATDESCRIPTOR pfd;
	int format;
	
	*LDFS_hDC = GetDC(LDFS_hWnd);
	
	ZeroMemory(&pfd, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;
	format = ChoosePixelFormat(*LDFS_hDC, &pfd);
	SetPixelFormat(*LDFS_hDC, format, &pfd);
	
	*LDFS_hRC = wglCreateContext(*LDFS_hDC);
	wglMakeCurrent(*LDFS_hDC, *LDFS_hRC);
}

void LDFS_DisableOpenGL(HWND LDFS_hWnd, HDC LDFS_hDC, HGLRC LDFS_hRC) {
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(LDFS_hRC);
	ReleaseDC(LDFS_hWnd, LDFS_hDC);
}
