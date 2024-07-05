#include "LULE_Multiplatform.h"

#ifdef _WIN32

// BaseWindow ------------------------------------------------------------------

// Public ----------------------------------------------------------------------

// -----------------------------------------------------------------------------
void LULE::Application::BaseWindow::CreateAndRegister() {
    WNDCLASSEX wcex = { 0 };

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = BaseWindow::WindowProc;
    wcex.hInstance = HInstance();
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.lpszClassName = m_Props.Title;

    RegisterClassEx(&wcex);

    m_HWND = CreateWindow(
        m_Props.Title,
        m_Props.Title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        m_Props.Width,
        m_Props.Height,
        nullptr,
        nullptr,
        HInstance(),
        this);

    if (!m_HWND)
        throw;
}

// -----------------------------------------------------------------------------
void LULE::Application::BaseWindow::Show() {
    if (!m_HWND)
        throw "No window";

    if (!IsWindowVisible(m_HWND))
        ShowWindow(m_HWND, SW_SHOWNORMAL);
}

// -----------------------------------------------------------------------------
void LULE::Application::BaseWindow::Hide() {
    ShowWindow(m_HWND, SW_HIDE);
}

// -----------------------------------------------------------------------------
void LULE::Application::BaseWindow::Destroy() {
    DestroyWindow(m_HWND);
}


LRESULT LULE::Application::BaseWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    return DefWindowProc(m_HWND, uMsg, wParam, lParam);
}

// Private ---------------------------------------------------------------------

// -----------------------------------------------------------------------------
void LULE::Application::BaseWindow::UpdateDimensions() {
    using std::move;

    if (!m_HWND)
        throw;

    static LUINT32 leftNtop[2] = { 0, 0 };
    static LUINT32 widthNheight[2] = { 0, 0 };
    RECT now = {};
    if (!GetWindowRect(m_HWND, &now))
        throw;

    // m_Props was updated, set new postion or resize
    if (leftNtop[0] != m_Props.Left ||
        leftNtop[1] != m_Props.Top ||
        widthNheight[0] != m_Props.Width ||
        widthNheight[1] != m_Props.Height) {

        SetWindowPos(
            m_HWND,
            0,
            (leftNtop[0] == m_Props.Left ? now.left : m_Props.Left),
            (leftNtop[1] == m_Props.Top ? now.top : m_Props.Top),
            (widthNheight[0] == m_Props.Width ? now.right : m_Props.Width),
            (widthNheight[1] == m_Props.Height ? now.bottom : m_Props.Height),
            SWP_NOZORDER);
    }

    if (widthNheight[0] != m_Props.Width ||
        widthNheight[1] != m_Props.Height) {

        widthNheight[0] = m_Props.Width;
        widthNheight[1] = m_Props.Height;
    }
    else {
        widthNheight[0] = m_Props.Width = move(now.right);
        widthNheight[1] = m_Props.Height = move(now.bottom);
    }

    if (leftNtop[0] != m_Props.Left ||
        leftNtop[1] != m_Props.Top) {

        leftNtop[0] = m_Props.Left;
        leftNtop[1] = m_Props.Top;
    }
    else {
        leftNtop[0] = m_Props.Left = move(now.left);
        leftNtop[1] = m_Props.Top = move(now.top);
    }
}

// -----------------------------------------------------------------------------
LRESULT LULE::Application::BaseWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    BaseWindow* pThis = nullptr;

    if (uMsg == WM_NCCREATE) {
        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
        pThis = (BaseWindow*)pCreate->lpCreateParams;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

        pThis->m_HWND = hwnd;
    }
    else {
        pThis = (BaseWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }
    if (pThis) {
        if (uMsg == WM_SIZE ||
            uMsg == WM_MOVE)
            pThis->UpdateDimensions();

        return pThis->HandleMessage(uMsg, wParam, lParam);
    }
    else {
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

#elif __GNUC__
#endif // _WIN32