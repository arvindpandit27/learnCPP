#include <windows.h>
#include <iostream>
#include <windowsx.h>

using namespace std;

using namespace std;
#define VK_LBUTTON 0x01 
#define VK_RBUTTON 0x02

void CheckMouseButtonStatus()
{
    static int left_click_counter = 0;
    static int right_click_counter = 0;
    int mouseX = 0;
    int mouseY = 0;
    POINT p;
    //Check the mouse left button is pressed or not
    if ((GetKeyState(VK_LBUTTON) & 0x80) != 0)
    {
        HWND hWnd = FindWindowA(0, ("File Explorer"));
        DWORD pid;
        ::GetWindowThreadProcessId(hWnd, &pid);
        if (hWnd) { cout << "Found" << endl; }
        GetCursorPos(&p);
        if (ScreenToClient(hWnd, &p))
        {
            cout << "Left button was clicked \n" << endl;
            int mouseX = p.x;
            int mouseY = p.y;
            cout << p.x << " " << p.y << endl;
        }
    }
    //Check the mouse right button is pressed or not
    if ((GetKeyState(VK_RBUTTON) & 0x80) != 0)
    {
        GetCursorPos(&p);
        right_click_counter++;
        //   AfxMessageBox(_T("RButton pressed"));
        if (right_click_counter == 1) 
        { 
            cout << "Right pressed\n"; 
            mouseX = p.x;
            mouseY = p.y;
            cout << p.x << " " << p.y << "\n" << endl;
        }
    }
}

int main()
{
    while (1)
    {
        CheckMouseButtonStatus();
    }
    return 0;
}