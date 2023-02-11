#include <X11/Xlib.h> //-lX11
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include<iostream>
#include<stdlib.h>
#include<string>
using namespace std;

#define EXIT_B 9
#define LEFT_B 113
#define RIGHT_B 114
#define UP_B 111
#define DOWN_B 116

Display *dis;
int scr;
Window win;
XFontStruct *fontInfo;


int sx = 300, sy = 300;

GC gc;
unsigned long black, white, red, blue, green;


unsigned long RGB(int r, int g, int b){
    return b + (g << 8) + (r << 16);
}

void draw(){
    XClearWindow(dis, win);
}

void create(){

    if((dis = XOpenDisplay(NULL)) == NULL){
        cout<<"Cannot open dispay\n";
        exit(0);
    }
    if ( (fontInfo =  XLoadQueryFont(dis, "*-courier-*" )) == NULL){
        printf("Font not found!\n");
        exit(1);

    }
    Font fnt =  XLoadFont(dis, "*-courier-*");

    black = RGB(0, 0, 0);
    white = RGB(255, 255, 255);
    red = RGB(255, 100, 100);
    blue = RGB(100, 100, 255);
    green = RGB(0, 200, 50);
    scr = DefaultScreen(dis);
    win = XCreateSimpleWindow(dis, DefaultRootWindow(dis), 0, 0, sx, sy, 5, green, blue);
    XSetStandardProperties(dis, win, "Nira", "Microsystem", None, NULL, 0, NULL);
    //XSelectInput(dis, win, Expose | ButtonPressMask | KeyPressMask);
    XSelectInput(dis, win, ButtonPressMask | KeyPressMask);

    gc = XCreateGC(dis, win, 0,0);
    XSetFont(dis, gc, fnt);
    XSetBackground(dis, gc, green);
    XSetForeground(dis, gc, blue);
    XClearWindow(dis, win);
    XMapRaised(dis, win);
}

void close(){
    XFreeGC(dis, gc);
    XDestroyWindow(dis, win);
    XCloseDisplay(dis);
    exit(0);
}

