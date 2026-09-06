#include <windows.h>
#include "Core/Logger.h"
#include "Graphics/Renderer.h"	

#include <algorithm>

#include "Math/Vector2.h"

// 메시지 처리 함수
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_DESTROY:
		// 프로그램 종료 signal
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	float a = 0.5f;
	float b = -0.6f;
	float c = 1.5f;
	Logger::Log(std::clamp(a, 0.0f, 1.0f));
	Logger::Log(std::clamp(b, 0.0f, 1.0f));
	Logger::Log(std::clamp(c, 0.0f, 1.0f));

	// 윈도우 클래스
	WCHAR WindowClass[] = L"SPSoftRenderer";

	// 윈도우 타이틀바
	WCHAR Title[] = L"SPSoftRenderer";

	// 메시지 처리 함수 WndProc의 함수 포인터를 WindowClass 구조체에 삽입
	WNDCLASSW wndclass = { 0, WndProc, 0, 0, 0, 0, 0, 0, 0, WindowClass };

	// 윈도우 클래스 등록
	if (RegisterClassW(&wndclass) == 0)
	{
		return -1;
	}

	int winWidth = 1024;
	int winHeight = 1024;

	// 정확하게 winWidth, winHeight 크기의 윈도우 생성
	RECT rect = {};
	rect.right = winWidth;
	rect.bottom = winHeight;

	AdjustWindowRect(
		&rect,
		WS_POPUP | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		FALSE
	);

	// 윈도우 생성
	HWND hWnd = CreateWindowExW(0, WindowClass, Title, WS_POPUP | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top,
		nullptr, nullptr, hInstance, nullptr);

	if (hWnd == nullptr)
	{
		return -1;
	}

	// 렌더러 생성
	Renderer renderer(winWidth, winHeight);		 

	bool bIsExit = false;
		
	// FPS 제한
	const int targetFPS = 60;
	const double targetFrameTime = 1000.0 / targetFPS; // 한 프레임의 목표 시간 (밀리초 단위)

	// 고성능 타이머 초기화
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	LARGE_INTEGER startTime, endTime;
	double elapsedTime = 0.0;	

	// Main Loop (Quit Message가 들어오기 전까지 아래 Loop를 무한히 실행하게 됨)
	while (bIsExit == false)
	{
		MSG msg;

		// 루프 시작 시간 기록
		QueryPerformanceCounter(&startTime);

		renderer.Render(hWnd);

		// 처리할 메시지가 더 이상 없을때 까지 수행
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			// 키 입력 메시지를 번역
			TranslateMessage(&msg);

			// 메시지를 적절한 윈도우 프로시저에 전달, 메시지가 위에서 등록한 WndProc 으로 전달됨
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				bIsExit = true;
				break;
			}
		}

		do
		{
			Sleep(0);

			// 루프 종료 시간 기록
			QueryPerformanceCounter(&endTime);

			// 한 프레임이 소요된 시간 계산 (밀리초 단위로 변환)
			elapsedTime = (endTime.QuadPart - startTime.QuadPart) * 1000.0 / frequency.QuadPart;

		} while (elapsedTime < targetFrameTime);
	}

	return 0;
}