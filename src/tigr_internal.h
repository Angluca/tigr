// can't use pragma once here because this file probably will endup in .c
#ifndef __TIGR_INTERNAL_H__
#define __TIGR_INTERNAL_H__

#define _CRT_SECURE_NO_WARNINGS NOPE

// Graphics configuration.
#define TIGR_GAPI_GL

// Creates a new bitmap, with extra payload bytes.
Tigr *tigrBitmap2(int w, int h, int extra);

// Resizes an existing bitmap.
void tigrResize(Tigr *bmp, int w, int h);

// Calculates the biggest scale that a bitmap can fit into an area at.
int tigrCalcScale(int bmpW, int bmpH, int areaW, int areaH);

// Calculates a new scale, taking minimum-scale flags into account.
int tigrEnforceScale(int scale, int flags);

// Calculates the correct position for a bitmap to fit into a window.
void tigrPosition(Tigr *bmp, int scale, int windowW, int windowH, int out[4]);

// ----------------------------------------------------------
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#ifdef __linux__
#include<X11/X.h>
#include<X11/Xlib.h>
#endif

#ifdef TIGR_GAPI_GL
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#endif
#ifdef _WIN32
#include <GL/gl.h>
#endif
#ifdef __linux__
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include<GL/glx.h>
#endif
typedef struct {
	#ifdef _WIN32
	HGLRC hglrc;
	HDC dc;
	#endif
	#ifdef __APPLE__
	void *glContext;
	#endif
	GLuint tex[2];
	GLuint vao;
	GLuint program;
	GLuint uniform_projection;
	GLuint uniform_model;
	GLuint uniform_parameters;
	int gl_legacy;
	int gl_user_opengl_rendering;
} GLStuff;
#endif

typedef struct {
	int shown, closed;
	#ifdef TIGR_GAPI_GL
	GLStuff gl;
	#endif

	#ifdef _WIN32
	wchar_t *wtitle;
	DWORD dwStyle;
	RECT oldPos;
	#endif
	#ifdef __linux__
	Display *dpy;
	Window win;
	GLXContext glc;
	XIC ic;
	#endif

	Tigr *widgets;
	int widgetsWanted;
	unsigned char widgetAlpha;
	float widgetsScale;

	int hblur, vblur;
	float scanlines, contrast;

	int flags;
	int scale;
	int pos[4];
	int lastChar;
	char keys[256], prev[256];
	#if defined(__APPLE__) || defined(__linux__)
	int mouseButtons;
	#endif
	#ifdef __linux__
	int mouseX;
	int mouseY;
	#endif
} TigrInternal;
// ----------------------------------------------------------

TigrInternal *tigrInternal(Tigr *bmp);

void tigrGAPICreate(Tigr *bmp);
void tigrGAPIDestroy(Tigr *bmp);
int  tigrGAPIBegin(Tigr *bmp);
int  tigrGAPIEnd(Tigr *bmp);
void tigrGAPIPresent(Tigr *bmp, int w, int h);

#endif

