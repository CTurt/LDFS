#pragma once

#define LDFS_CreateWindow(wndProc, title) do { LDFS_CREATE_WINDOW(hInstance, hPrevInstance, lpCmdLine, iCmdShow, wndProc, title); } while(0)

int LDFS_CREATE_WINDOW(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow, WNDPROC wndProc, char *title);
unsigned char LDFS_Update(void);
inline void LDFS_SwapBuffers(void);
void LDFS_DestroyWindow(void);
LRESULT CALLBACK LDFS_DefaultWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
