#include "RootWindow.h"
#include "GUI.h"

#define ROOTWINDOW_BACK_COLOR 0x00FFFFFF     /* ������Ĭ�ϱ���ɫ */

void (*RootWinPaint_Cb)(WM_HWIN hWin) = NULL;
void (*RootWinTimer_Cb)(WM_HWIN hWin) = NULL;

static void __Paint(WM_HWIN hWin)
{
    GUI_RECT *r = WM_GetWindowRect(hWin);

    if (RootWinPaint_Cb) {
        RootWinPaint_Cb(hWin);
    } else {
        /* ���Ʊ��� */
        GUI_SetFGColor(ROOTWINDOW_BACK_COLOR);
        GUI_FillRect(r->x0, r->y0, r->x1 - r->x0 + 1,
            r->y1 - r->y0 +1);
    }
}

static void _RootWin_Callback(WM_MESSAGE *pMsg)
{
    switch (pMsg->MsgId) {
    case WM_PAINT:
        __Paint(pMsg->hWin);
        break;
    case WM_TIMER:
        /* �û����� */
        if (RootWinTimer_Cb) {
            RootWinTimer_Cb(pMsg->hWin);
        }
        break;
    case WM_SET_FOCUS: /* �������뽹�� */
        break;
    case WM_GET_FOCUS:
        break;
    case WM_TP_CHECKED:
        WM_SetActiveWindow(pMsg->hWin); /* ����Ϊ����� */
        break;
    }
}

void WM_RootWindowInit(WM_Obj *pObj)
{
    int xSize, ySize;
    
    GUI_ScreenSize(&xSize, &ySize);
    pObj->Rect.x0 = 0;
    pObj->Rect.y0 = 0;
    pObj->Rect.x1 = xSize - 1;
    pObj->Rect.y1 = ySize - 1;
    pObj->WinCb = _RootWin_Callback;
    pObj->hNext = NULL;
    pObj->hNextLine = NULL;
    pObj->hParent = NULL;
    pObj->hFirstChild = NULL;
    pObj->Status = 0x0000;
    pObj->Id = WM_ROOTWIN_ID;
    WM_Invalidate(pObj);  /* ��������Ч�� */
    GUI_ClipNewWindow(pObj); /* ���¼����� */
}

/* ���ø����ڵĶ�ʱ�� */
void GUI_SetRootWindowTimer(GUI_TIME timer)
{
    GUI_TimerCreate(_hRootWin, 0, timer, GUI_TMR_AUTO);
}