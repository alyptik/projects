const char name[] = "the mandelbrot set";

short plot[640][480];

void mandelbrot(int a, int b)
{
	int Px;
	int Py;
	for(Px = a; Px < b; Px++) for(Py = 0; Py < 480; Py++) {
		float x0 = Px / 640. * 3.5 - 2.5;
		float y0 = Py / 480. * 2.0 - 1.0;
		float x = 0.;
		float y = 0.;

		int iterations;
		for(iterations = 0; x*x + y*y < 2.*2. && iterations < 999; iterations++) {
			float xtemp = x*x - y*y + x0;
			float ytemp = 2.*x*y + y0;
			x = xtemp;
			y = ytemp;
		}
		plot[Px][Py] = iterations;
	}
}

#include <pthread.h>

pthread_mutex_t mutex;

int shared_variable;

void *mandelbrot_thread(void *arg)
{
	for(;;) {
		pthread_mutex_lock(&mutex);
		int work_variable = shared_variable++;
		pthread_mutex_unlock(&mutex);

		int a = work_variable * 10;
		int b = a + 10;

		if(b > 640) break;

		mandelbrot(a, b);
	}
	return(arg);
}

pthread_t threadid[4];

void *mandelbrot_spawn(void *arg)
{
	shared_variable = 0;

	pthread_mutex_init(&mutex, 0);
	int a;
	for(a = 0; a < 4; a++) pthread_create(&threadid[a], 0, mandelbrot_thread, 0);
	int b;
	for(b = 0; b < 4; b++) pthread_join(threadid[b], 0);
	pthread_mutex_destroy(&mutex);

	return(arg);
}

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

Display *display;
Colormap colourmap;
Window window;
int npixels;
unsigned long pixels[8];
XFontStruct *font;
GC gc;
XImage *image;

int histogram[1000];
int palette[1000];

void render(void)
{
	int Hx;
	int Hy;
	for(Hx = 0; Hx < 640; Hx++) for(Hy = 0; Hy < 480; Hy++) {
		int a = plot[Hx][Hy];
		histogram[a]++;
	}
	int total = 0;
	int b;
	for(b = 0; b < 999; b++) {
		total += histogram[b];
	}
	int hue = 0;
	int c;
	for(c = 0; c < 999; c++) {
		palette[c] = (npixels - 1) * hue / total;
		hue += histogram[c];
	}
	palette[999] = (npixels - 1); /* special case */
	int Px;
	int Py;
	for(Px = 0; Px < 640; Px++) for(Py = 0; Py < 480; Py++) {
		int d = plot[Px][Py];
		int e = palette[d];
		XPutPixel(image, Px, Py, pixels[e]);
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fail(const char *text)
{
	perror(text);
	exit(0);
}

void quit(void);

int main(int argc, char **argv)
{
	mandelbrot_spawn(0);

	atexit(quit);
	if(display = XOpenDisplay(0), display == 0)
		fail("open display error");

	static XVisualInfo visualinfo;
	visualinfo.screen = DefaultScreen(display);
	visualinfo.visual = DefaultVisual(display, visualinfo.screen);
	visualinfo.depth = DefaultDepth(display, visualinfo.screen);
	colourmap = DefaultColormap(display, visualinfo.screen);

	static XSetWindowAttributes setwindowattributes;
	setwindowattributes.background_pixel = 0;
	setwindowattributes.border_pixel = 0;
	setwindowattributes.event_mask = ButtonPressMask | ExposureMask;
	setwindowattributes.colormap = colourmap;
	if(window = XCreateWindow(display, RootWindow(display, visualinfo.screen), 20, 20, 640, 480, 0, visualinfo.depth, InputOutput, visualinfo.visual, CWBackPixel | CWBorderPixel | CWEventMask | CWColormap, &setwindowattributes), window == 0)
		fail("create window error");
	XSetStandardProperties(display, window, name, name, None, argv, argc, 0);
	XMapRaised(display, window);

	for(npixels = 0; npixels < 8; npixels++) {
		int r = npixels / 4 % 2;
		int g = npixels / 2 % 2;
		int b = npixels / 1 % 2;
		static XColor colour;
		colour.red = r * 65535;
		colour.green = g * 65535;
		colour.blue = b * 65535;
		if(XAllocColor(display, colourmap, &colour) == 0)
			fail("allocate colour error");
		pixels[npixels] = colour.pixel;
	}

	if(font = XLoadQueryFont(display, "fixed"), font == 0)
		fail("load query font error");
	if(gc = XCreateGC(display, window, 0, 0), gc == 0)
		fail("create graphics context error");
	if(image = XCreateImage(display, visualinfo.visual, visualinfo.depth, ZPixmap, 0, 0, 640, 480, BitmapPad(display), 0), image == 0)
		fail("create image error");
	if(image->data = (char *)(calloc(image->height, image->bytes_per_line)), image->data == 0)
		fail("allocate image error");

	render();

	static XCharStruct charstruct;
	int unused;
	XTextExtents(font, name, strlen(name), &unused, &unused, &unused, &charstruct);

	int draw = 1;
	int ok = 1;
	while(ok) {
		if(draw) {
			draw = 0;
			XPutImage(display, window, gc, image, 0, 0, 0, 0, 640, 480);
			XSetForeground(display, gc, pixels[0]);
			XSetFont(display, gc, font->fid);
			XDrawString(display, window, gc, (640 + charstruct.lbearing - charstruct.rbearing) / 2, (480 + charstruct.ascent - charstruct.descent) / 2, name, strlen(name));
		}
		static XEvent event;
		XPeekEvent(display, &event);
		while(XPending(display) > 0) {
			XNextEvent(display, &event);
			switch(event.type) {
			case ButtonPress: ok = 0; break;
			case Expose: draw = 1; break;
			}
		}
	}
	return(0);
}

void quit(void)
{
	if(image != 0) XDestroyImage(image);
	if(gc != 0) XFreeGC(display, gc);
	if(font != 0) XFreeFont(display, font);
	if(npixels != 0) XFreeColors(display, colourmap, pixels, npixels, 0);
	if(window != 0) XDestroyWindow(display, window);
	if(display != 0) XCloseDisplay(display);
}
