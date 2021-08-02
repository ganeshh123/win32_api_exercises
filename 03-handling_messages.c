// http://www.winprog.org/tutorial/window_click.html

#include <windows.h>

/* Window Procedure */

// Handles messages dispatched to the window from the main method. Takes in the handle unique to each
// window, and the message in the form of an integer with other params
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    // Exectution based on the message
    switch (msg)
    {

    case WM_LBUTTONDOWN:          // Message handler for left mouse button clicked down
        {
            char szFileName[MAX_PATH];                          // Reserve a string (array of chars) to store the filename
                                                                // of the window. MAX_PATH variable is the maximum file path
                                                                // length that Windows supports.                                    
            HINSTANCE hInstance = GetModuleHandle(NULL);        // Get a handle to the calling process
            GetModuleFileName(hInstance, szFileName, MAX_PATH); // Fetch the filename for the calling process and store it into
                                                                // the szFileName string

            // Display a message box showing the filename string with a label and an OK function.
            MessageBox(hwnd, szFileName, "This program is:", MB_OK | MB_ICONINFORMATION);
        }
        break;
    case WM_CLOSE:
        DestroyWindow(hwnd); // If close button (Alt+F4) pressed, close the window and send a window destroy message
        break;
    case WM_DESTROY:
        PostQuitMessage(0); // If window destroy message received, send quit message to our application, with a value of 0
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc; // Struct to define Window properties
    HWND hwnd;     // Will store handler to the Window
    MSG Msg;       // Will store messages received by application

    /* Define Window Class */

    // Window Class Name
    const char g_szClassName[] = "myWindowClass";

    // Setting the Window's properties
    wc.cbSize = sizeof(WNDCLASSEX);                // Size of the structure
    wc.style = 0;                                  // Class Styles
    wc.lpfnWndProc = WndProc;                      // Pointer to Window procedure for this Window Class
    wc.cbClsExtra = 0;                             // Amount of extra data allocated for this class in memory. Usually 0.
    wc.cbWndExtra = 0;                             // Amount of extra data allocated in memory per window of this type. Usually 0.
    wc.hInstance = hInstance;                      // Handle to application instance (that we got in the first parameter of WinMain()).
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);    // Large (usually 32x32) icon shown when the user presses Alt+Tab.
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);      // Cursor that will be displayed over our window.
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // Background Brush to set the color of our window.
    wc.lpszMenuName = NULL;                        // Name of a menu resource to use for the windows with this class.
    wc.lpszClassName = g_szClassName;              // Name to identify the class with.
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);  // Small (usually 16x16) icon to show in the taskbar and in the top left corner of the window.

    // Validate the properties of the Window Class and abort if false returned (fail) with
    // an error message displayed in the message box
    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
                   MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    /* Create the Window */
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,                       // Extended Windows Style
        g_szClassName,                          // Window Class Name
        "My Application",                       // Window Title
        WS_OVERLAPPEDWINDOW,                    // Windows Style Parameter
        CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, // x-coordinate-top-left-corner, y-coordinate-top-right-corner, width, height
        NULL, NULL, hInstance, NULL);           // parent-window-handle, menu-handle, application-instance-handle, window-creation-data-pointer

    // Window handle returns null if there's an error in the properties. This checks for errors,
    // displayes any error message in a message box and then terminates if error
    if (hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
                   MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Show and update the Window on the Main Screen
    ShowWindow(hwnd, nCmdShow); //nCmdShow allows command line flags for window state - e.g minimized, maximized
    UpdateWindow(hwnd);

    /* Message Loop */

    // Obtains messages from application message queue. Messages are generated when user interacts with mouse,
    // keyboard etc. Quit message is zero so will exit loop once received.
    while (GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg); // Additional processing of messages
        DispatchMessage(&Msg);  // Pass Messages to the Window
    }

    // Return value from quit message as exit value
    return Msg.wParam;
}