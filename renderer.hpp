/*
Functions for drawing a bitmap (the map) and circles of
various colors (the players and the ball). The camera
will be static, so there is no need to clip anything from
the scene (although this doesn't allow for bigger maps).
This will also provide info such as when the window resizes
and when it closes, as it contains the whole WINAPI
implementation.
*/

#include <d2d1.h>
#include <dwrite.h>
#include <iostream>

#define WINDOW_NAME "hexball"
#define WINDOW_CLASS_NAME "HexBall cu a"
#define WINDOW_DEF_WIDTH 800
#define WINDOW_DEF_HEIGHT 600

LRESULT CALLBACK MainWindowProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) {
	switch(message) {
	case WM_DESTROY:
		exit(0);
		break;
	default:
		break;
	}
	return DefWindowProcA(window, message, wparam, lparam);
}

typedef ID2D1SolidColorBrush* RendererBrush;

class Renderer {
private:
	HWND m_window;
	ID2D1Factory *m_d2d1_factory;
	ID2D1HwndRenderTarget *m_render_target;
	IDWriteFactory *m_dwrite_factory;
public:
	void Init() {
		WNDCLASSA window_class = { 0 };
		window_class.lpfnWndProc = MainWindowProc;
		window_class.lpszClassName = WINDOW_CLASS_NAME;
		RegisterClassA(&window_class);
		m_window = CreateWindowA(
			WINDOW_CLASS_NAME, WINDOW_NAME,
			WS_VISIBLE | WS_OVERLAPPEDWINDOW,
			100, 100, WINDOW_DEF_WIDTH, WINDOW_DEF_HEIGHT,
			0, 0, 0, 0
		);
		UpdateWindow(m_window);

		D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_d2d1_factory);
		m_d2d1_factory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_window, D2D1::SizeU(WINDOW_DEF_WIDTH, WINDOW_DEF_HEIGHT)),
			&m_render_target
		);
	}
	void PullMessages() {
		MSG message;
		if(PeekMessageA(&message, m_window, 0, 0, PM_REMOVE)) {
			DispatchMessageA(&message);
			TranslateMessage(&message);
		}
	}
	void CreateBrush(RendererBrush *brush, float r, float g, float b, float a = 1.0f) {
		m_render_target->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), brush);
	}
	void Begin() { m_render_target->BeginDraw(); }
	void End() { m_render_target->EndDraw(); }
	void Clear() { m_render_target->Clear(); }
	void Ellipse(float x, float y, float r, RendererBrush brush) {
		m_render_target->FillEllipse(
			D2D1::Ellipse(D2D1::Point2F(x, y), r, r),
			brush
		);
	}
	void Rectangle(float x, float y, float w, float h, RendererBrush brush, bool fill = 0) {
		if (fill)
			m_render_target->FillRectangle(D2D1::RectF(x, y, x + w, y + h), brush);
		else
			m_render_target->DrawRectangle(D2D1::RectF(x, y, x + w, y + h), brush);
	}
};
