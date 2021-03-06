#include <windows.h>
#include <gl/gl.h>
#include <LDFS.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow) {
	LDFS_Init(LDFS_DefaultWndProc);
	
	// window title, full screen, width, height
	// LDFS_AUTO gets the user's resolution for you so that the image isn't stretched
	LDFS_CreateWindow("test", 1, LDFS_AUTO, LDFS_AUTO);
	
	while(1) {
		if(LDFS_Update()) {
			
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			
			glPushMatrix();
			glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(0.0f, 1.0f);
			glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.87f, -0.5f);
			glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(-0.87f, -0.5f);
			glEnd();
			glPopMatrix();
			
			LDFS_SwapBuffers();
			
		}
		else {
			LDFS_DestroyWindow();
			return 0;
		}
	}
}
