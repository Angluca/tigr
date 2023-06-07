#include "tigr.h"

int main(int argc, char* argv[]) {
    Tigr* screen = tigrWindow(320, 240, "Hello", 0);
    Tigr* fontImage = tigrLoadImage("ch.png");
    TigrFont* font = tigrLoadFont(fontImage, TCP_UTF32);
    while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {
        tigrClear(screen, tigrRGB(0x80, 0x90, 0xa0));
        tigrPrint(screen, tfont, 120, 90, tigrRGB(0xff, 0xff, 0xff), "Hello, world.");
        tigrPrint(screen, font, 120, 110, tigrRGB(0xff, 0xff, 0xff), "你好让我试试 效果如何哈【】︻☲.?!");
        tigrUpdate(screen);
    }
    tigrFree(screen);
    return 0;
}
