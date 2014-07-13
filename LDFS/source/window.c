#include <windows.h>
#include <gl/gl.h>

#include "LDFS.h"

static HWND LDFS_hWnd;
static HDC LDFS_hDC;
static HGLRC LDFS_hRC;
static MSG LDFS_msg;

int LDFS_CREATE_WINDOW(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow, WNDPROC wndProc, char *title) {
	WNDCLASS wc;
	BOOL quit = 0;
	
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = wndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
	wc.hCursor = LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "LDFSClass";
	RegisterClass(&wc);
	
	LDFS_hWnd = CreateWindow("LDFSClass", title, WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE, 0, 0, 256, 256, NULL, NULL, hInstance, NULL);
	
	LDFS_EnableOpenGL(LDFS_hWnd, &LDFS_hDC, &LDFS_hRC);
	
	LDFS_InitTimer();
}

unsigned char LDFS_Update(void) {
	LDFS_MaintainFramerate();
	LDFS_FrameStart = LDFS_GetTime();
	
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
