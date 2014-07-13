#include <windows.h>

#include "LDFS.h"

void LDFS_Init(WNDPROC wndProc) {
	memset(&LDFS_wc, '\0', sizeof(WNDPROC));
	LDFS_wc.lpfnWndProc = wndProc;
	LDFS_InitTimer();
}
