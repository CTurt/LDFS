#include <windows.h>
#include <gl/gl.h>

#include "LDFS.h"

WNDCLASS LDFS_wc;
HWND LDFS_hWnd;
HDC LDFS_hDC;
HGLRC LDFS_hRC;
MSG LDFS_msg;

int LDFS_CREATE_WINDOW(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow, char *title, unsigned char fullScreen, int width, int height) {
	LDFS_wc.style = CS_OWNDC;
	//LDFS_wc.lpfnWndProc = wndProc;
	LDFS_wc.cbClsExtra = 0;
	LDFS_wc.cbWndExtra = 0;
	LDFS_wc.hInstance = hInstance;
	LDFS_wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	LDFS_wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	LDFS_wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	LDFS_wc.lpszMenuName = NULL;
	LDFS_wc.lpszClassName = "LDFSClass";
	RegisterClass(&LDFS_wc);
	
	if(fullScreen) {
		LDFS_hWnd = CreateWindow("LDFSClass", title, WS_EX_TOPMOST | WS_POPUP, 0, 0, width == LDFS_AUTO ? GetSystemMetrics(SM_CXSCREEN) : width, height == LDFS_AUTO ? GetSystemMetrics(SM_CYSCREEN) : height, NULL, NULL, hInstance, NULL);
		ShowWindow(LDFS_hWnd, SW_MAXIMIZE);
	}
	else LDFS_hWnd = CreateWindow("LDFSClass", title, WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE, 0, 0, width == LDFS_AUTO ? 768 : width, height == LDFS_AUTO ? 576 : height, NULL, NULL, hInstance, NULL);
	
	LDFS_EnableOpenGL(LDFS_hWnd, &LDFS_hDC, &LDFS_hRC);
}

unsigned char LDFS_Update(void) {
	LDFS_MaintainFramerate();
	
	if(PeekMessage(&LDFS_msg, NULL, 0, 0, PM_REMOVE)) {
		if(LDFS_msg.message == WM_QUIT) {
			return 0;
		}
		else {
			TranslateMessage(&LDFS_msg);
			DispatchMessage(&LDFS_msg);
		}
	}
	return 1;
}

inline void LDFS_SwapBuffers(void) {
	SwapBuffers(LDFS_hDC);
}

void LDFS_DestroyWindow(void) {
	LDFS_DisableOpenGL(LDFS_hWnd, LDFS_hDC, LDFS_hRC);
	DestroyWindow(LDFS_hWnd);
}

LRESULT CALLBACK LDFS_DefaultWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch(message) {
		case WM_CREATE:
			return 0;
			
		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;
			
		case WM_DESTROY:
			return 0;
			
		case WM_KEYDOWN:
			switch(wParam) {
				case VK_ESCAPE:
					PostQuitMessage(0);
					return 0;
			}
			return 0;
		
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
