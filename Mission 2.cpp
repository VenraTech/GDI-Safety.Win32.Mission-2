// Mission 2.cpp : Este arquivo contém as funções "principais". É aqui que começa e termina a execução do programa.
//

#include <windows.h>
#pragma comment(lib, "winmm.lib")
typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE b;
		BYTE g;
		BYTE r;
		BYTE Reserved;
	};
}_RGBQUAD, * PRGBQUAD;
DWORD WINAPI shader(LPVOID lvshader)
{       int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
       _RGBQUAD* data = (_RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(_RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        for (int i = 0;; i++, i %= 3) {
        HDC desk = GetDC(NULL);
        HDC hdcdc = CreateCompatibleDC(desk);
        HBITMAP hbm = CreateBitmap(w, h, 1, 32, data);
        SelectObject(hdcdc, hbm);
        BitBlt(hdcdc, 0, 0, w, h, desk, 0, 0, SRCERASE);
        GetBitmapBits(hbm, w * h * 4, data);
        for (int i = 0; w * h > i; i++) {
            int x = i % w, y = i / h;
            data[i].rgb -= x*y ^ x+y + x+i;
        }
        SetBitmapBits(hbm, w * h * 4, data);
        BitBlt(desk, 0, 0, w, h, hdcdc, 0, 0, SRCCOPY);
        DeleteObject(hbm);
        DeleteObject(hdcdc);
        DeleteObject(desk);
    }
    return 0;
}
VOID WINAPI sound() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 40000, 40000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[40000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((t ^ t >> 5) * t >> 2);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
int CALLBACK WinMain(
	HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine, int       nCmdShow
)
{
	if (MessageBoxW(NULL, L"WARNING!\n\nYou're about to run a HARMLESS/SAFE malware called Mission 2.exe. In other words, Mission 2.exe will not be able to cause your system's death & data loss. However, this software will play loud sounds.\n\nBy the way, this was created for entertainment purposes. Do you proceed with running?", L"Mission 2.exe by Venra", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
	{
		ExitProcess(0);
	}
	else
	{
		if (MessageBoxW(NULL, L"FINAL WARNING!\n\nMake sure you are running the ORIGINAL Mission 2.exe from VENRA'S GITHUB!!! Downloading in other places may be unsafe and it can be modifed by any other malicious people.\n\nProceed at your own risk.", L"F?i?n?a?l? ?W?a?r?n?i?n?g? - Mission 2.exe", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
		{
			ExitProcess(0);
		}
		else
		{
			HANDLE thread = CreateThread(0, 0, shader, 0, 0, 0);
			sound();
			Sleep(30000);
			TerminateThread(thread, 0);
			CloseHandle(thread);
		}
	}
}			
