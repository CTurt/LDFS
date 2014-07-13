#pragma once

#define LDFS_CreateWindow(title, width, height) do { LDFS_CREATE_WINDOW(hInstance, hPrevInstance, lpCmdLine, iCmdShow, title, width, height); } while(0)

extern WNDCLASS LDFS_wc;
extern HWND LDFS_hWnd;
extern HDC LDFS_hDC;
extern HGLRC LDFS_hRC;
extern MSG LDFS_msg;

int LDFS_CREATE_WINDOW(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow, char *title, int width, int height);
unsigned char LDFS_Update(void);
inline void LDFS_SwapBuffers(void);
void LDFS_DestroyWindow(void);
LRESULT CALLBACK LDFS_DefaultWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
