#include <windows.h>
#include <gl/gl.h>
#include <LDFS.h>

#include "main.h"

unsigned char holdingSpace = 0;
float angle = 0.0f;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow) {
	LDFS_Init(WndProc);
	LDFS_CreateWindow("test", 1, LDFS_AUTO, LDFS_AUTO);
	
	while(1) {
		if(LDFS_Update()) {
			
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			
			glPushMatrix();
			glRotatef(angle, 0.0f, 0.0f, 1.0f);
			glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(0.0f, 1.0f);
			glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.87f, -0.5f);
			glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(-0.87f, -0.5f);
			glEnd();
			glPopMatrix();
			
			if(holdingSpace) angle += 0.5f;
			
			LDFS_SwapBuffers();
			
		}
		else {
			LDFS_DestroyWindow();
			return 0;
		}
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
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
					break;
					
				case VK_SPACE:
					if(!(lParam & 0x40000000)) holdingSpace = 1;
					break;
			}
			return 0;
			
		case WM_KEYUP:
			switch(wParam) {
				case VK_SPACE:
					holdingSpace = 0;
			}
			
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
