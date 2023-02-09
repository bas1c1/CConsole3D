unsigned long RGBA2DWORD(int iR, int iG, int iB, int iA)
{
    return ((iA * 256 + iR) * 256 + iG) * 256 + iB;
}

typedef struct RGBACOLOR {
    int r;
    int g;
    int b;
    int a;
} RGBACOLOR;

RGBACOLOR color_new(int iR, int iG, int iB, int iA) {
    RGBACOLOR col;
    col.r = iR;
    col.g = iG;
    col.b = iB;
    col.a = iA;
    return col;
}

int draw(int height, int width, int pixels[][4])
{
    BITMAPINFOHEADER    bih;
    PDWORD              pBmp;
    HBITMAP             hBmp;
    HDC                 hBmpDC;

    memset(&bih, 0, sizeof bih);
    bih.biSize = sizeof bih;
    bih.biPlanes = 1;
    bih.biBitCount = 8 << 2;
    bih.biCompression = BI_RGB;
    bih.biWidth = width;
    bih.biHeight = height;
    bih.biSizeImage = bih.biWidth * bih.biHeight * (1 << 2);
    hBmp = CreateDIBSection(NULL, (PBITMAPINFO)&bih, DIB_RGB_COLORS, (PVOID*)&pBmp, NULL, NULL);
    hBmpDC = CreateCompatibleDC(NULL);
    SelectObject(hBmpDC, hBmp);
    for (int i = 0; i < (height * width); i++)
    {
        pBmp[i] = RGBA2DWORD(pixels[i][0], pixels[i][0], pixels[i][0], pixels[i][0]);
    }
    BitBlt(GetDC(GetConsoleWindow()), 0, 0, width, height, hBmpDC, 0, 0, SRCCOPY);
    DeleteDC(hBmpDC);
    DeleteObject(hBmp);
    return 0;
}