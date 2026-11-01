#include "windows.h"
#include "Graphics/Renderer.h"

Renderer::Renderer(int width, int height)
	:width(width), height(height),
    frameBuffer(width, height), rasterizer() 
{
    bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmapInfo.bmiHeader.biWidth = width;
    bitmapInfo.bmiHeader.biHeight = -height;
    bitmapInfo.bmiHeader.biPlanes = 1;
    bitmapInfo.bmiHeader.biBitCount = 32;
    bitmapInfo.bmiHeader.biCompression = BI_RGB;
}

void Renderer::Render(HWND hWnd, std::vector<GameObject*>& gameObjects)
{
    renderQueue.Clear();
    frameBuffer.Clear(Color::White);

    // 게임오브젝트 순회
    for (std::vector<GameObject*>::iterator gameObjectIter = gameObjects.begin();
        gameObjectIter != gameObjects.end(); ++gameObjectIter)
    {
        if ((*gameObjectIter) == nullptr)
            continue;

        RendererComponent* rendererComponent =
            (*gameObjectIter)->GetComponent<RendererComponent>();

        if (rendererComponent == nullptr)
            continue;

        rendererComponent->Submit(renderQueue);

    }

    // 오브젝트별 렌더링
    for (std::vector<DrawCommand>::const_iterator command = renderQueue.GetCommands().begin();
        command != renderQueue.GetCommands().end(); ++command)
    {
        for (size_t i = 0; i + 2 < command->mesh->GetIndices().size(); i += 3)
        {
            int a = command->mesh->GetIndices()[i];
            int b = command->mesh->GetIndices()[i + 1];
            int c = command->mesh->GetIndices()[i + 2];

            Vertex v1 = command->mesh->GetVertex(a);
            Vertex v2 = command->mesh->GetVertex(b);
            Vertex v3 = command->mesh->GetVertex(c);

            Vector4 v1_position = Vector4((command->worldMatrix) * Matrix4x1(v1.position));
            Vector4 v2_position = Vector4((command->worldMatrix) * Matrix4x1(v2.position));
            Vector4 v3_position = Vector4((command->worldMatrix) * Matrix4x1(v3.position));

            rasterizer.DrawTriangle(
                v1_position.y, v1_position.z, v1.color,
                v2_position.y, v2_position.z, v2.color,
                v3_position.y, v3_position.z, v3.color,
                frameBuffer
            );
        }
    }

    Present(hWnd);
}

void Renderer::Present(HWND hWnd)
{
    HDC hdc = GetDC(hWnd);

    StretchDIBits(
        hdc,
        0, 0,
        frameBuffer.GetWidth(),
        frameBuffer.GetHeight(),
        0, 0,
        frameBuffer.GetWidth(),
        frameBuffer.GetHeight(),
        frameBuffer.GetPixelsByUInt32(),
        &bitmapInfo,
        DIB_RGB_COLORS,
        SRCCOPY
    );

    ReleaseDC(hWnd, hdc);
}