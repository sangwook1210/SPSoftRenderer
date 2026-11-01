#include <windows.h>
#include "Core/Logger.h"
#include "Graphics/Renderer.h"	

#include <algorithm>
#include <vector>
#include <Component/Renderer/MeshRenderer.h>

#include "Math/Vector2.h"
#include "Math/Matrix.h"
#include "Core/GameObject.h"

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
	Vector2 a(1, 2);
	Vector2 b(3, 4);
	Vector3 c(6, 7, 8);
	Matrix2x2 m2(a, b);
	Matrix3x3 m3;
	Matrix3x1 m31(c);
	Matrix4x1 m41(c);
	float arr[3] = { 1.0,2.0,3.0 };
	Matrix<1, 3> left(arr, sizeof(arr) / sizeof(arr[0]));
	Matrix<1, 3> left2({ 2.0f, 3.0f, 4.0f });

	Logger::Log(m41);


	/* 테스트용 게임 오브젝트 */
	std::vector<GameObject*> gameObjects;
	GameObject g1;
	gameObjects.push_back(&g1);
	Logger::Log(g1.transform->GetPosition());
	Logger::Log("변경 전: ", g1.transform->GetWorldMatrix());
	g1.GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 512.0f));
	g1.GetComponent<Transform>()->SetRotation(Vector3(45.0f, 0.0f, 0.0f));
	g1.GetComponent<Transform>()->SetScale(Vector3(0.1f, 0.1f, 0.1f));
	Logger::Log(g1.transform->GetPosition());
	Logger::Log("변경 후: ", g1.transform->GetWorldMatrix());

	Mesh mesh;
	mesh.SetVertices({
		{Vector3(0.0f, -200.0f, -200.0f), Color::Red},
		{Vector3(0.0f, 200.0f, -200.0f), Color::Blue},
		{Vector3(0.0f, -200.0f, 200.0f), Color::Green},
		{Vector3(0.0f, 200.0f, 200.0f), Color::Pink}
		});
	mesh.SetIndices({ 0,1,2, 1,3,2 });

	g1.AddComponent<MeshRenderer>();
	g1.GetComponent<MeshRenderer>()->mesh = &mesh;

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

	float totTime =0.0f;
	int renderCount = 0;

	// Main Loop (Quit Message가 들어오기 전까지 아래 Loop를 무한히 실행하게 됨)
	while (bIsExit == false)
	{
		MSG msg;

		// 루프 시작 시간 기록
		QueryPerformanceCounter(&startTime);
		QueryPerformanceFrequency(&frequency);

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



		// 실제 동작
		float deltaTime = static_cast<float>(elapsedTime / 1000.0);
		totTime += deltaTime;
		g1.transform->AddPosition({ 0.0f, 512.0f * deltaTime, 0.0f });

		renderer.Render(hWnd, gameObjects);
		renderCount++;

		QueryPerformanceCounter(&endTime);

		elapsedTime = (endTime.QuadPart - startTime.QuadPart) * 1000.0 / frequency.QuadPart;

		while (elapsedTime < targetFrameTime)
		{
			Sleep(0);

			// 루프 종료 시간 기록
			QueryPerformanceCounter(&endTime);

			// 한 프레임이 소요된 시간 계산 (밀리초 단위로 변환)
			elapsedTime = (endTime.QuadPart - startTime.QuadPart) * 1000.0 / frequency.QuadPart;

		}

		Logger::Log("ElapsedTime: ", elapsedTime);
		Logger::Log("deltaTime: ", deltaTime);
		Logger::Log("FPS: ", 1.0f / deltaTime);
		Logger::Log("Y: ", g1.transform->GetPosition().y);
		Logger::Log("totTime: ", totTime);
		Logger::Log("renderCount: ", renderCount);
		Logger::Log("\n");
	}

	return 0;
}
