#include<Windows.h>
#include<stdio.h>
#include "res.h"

INT_PTR CALLBACK DialogProc(HWND hwndDig, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
  case WM_COMMAND:
    switch (HIWORD(wParam))
    {
    case BN_CLICKED:
      switch (LOWORD(wParam))
      {
      case IDC_BUTTON2:
        MessageBox(hwndDig, TEXT("Test"), TEXT("Klikniecie"), MB_OK);
        HWND hwndEditBox = GetDlgItem(hwndDig, IDC_EDIT1);
        int iTextLength = GetWindowTextLength(hwndEditBox);
        CHAR szText[500];
        GetWindowText(hwndEditBox, szText, iTextLength + 1);

        SetWindowText((HWND)lParam, szText);
        return TRUE;
      }
      return FALSE;
    case EN_CHANGE:
      switch (LOWORD(wParam))
      {
      case IDC_EDIT1:
        HWND hwndEditBox = GetDlgItem(hwndDig, IDC_EDIT1);
        int iTextLength = GetWindowTextLength(hwndEditBox);
        CHAR szText[500];
        GetWindowText(hwndEditBox, szText, iTextLength + 1);
        HWND hwndEditBox1 = GetDlgItem(hwndDig, IDC_BUTTON1);
        SetWindowText(hwndEditBox1, szText);
        return TRUE;
      }
      return FALSE;
    }
    return FALSE;
  case WM_LBUTTONDOWN:
    CHAR szText[200];
    wsprintf(szText, "Kliknales myszka x=%d, y=%d", LOWORD(lParam), HIWORD(lParam));
    MessageBox(hwndDig, szText, TEXT("Klikniecie"), MB_OK);
    return TRUE;
  case WM_CLOSE:
    DestroyWindow(hwndDig);//zniszczenie okienka
    PostQuitMessage(0);//umieszczenie w petli komunikatow polecenia zakonczenia aplikacji 
    return TRUE;
  }
  return FALSE;
}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevinstance, PSTR szCmdLIne, int iCmdShow)
{
  HWND hwndMainWindow = CreateDialog(hinstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
  ShowWindow(hwndMainWindow, iCmdShow);

  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}