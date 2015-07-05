//---------------------------------------------------------
//	catgl
//
//		©2015 Yuichiro Nakada
//---------------------------------------------------------

#define CATGL_NANOVG
#define CATGL_IMPLEMENTATION
#include "catgl.h"

struct NVGcontext* vg;
int width, height;
float pixelRatio;

/*float angle, rad, speed, x, y, diam;
int nbPts;
static int s_RADIUS = 30;
    for (int i = 0; i<nbPts; i++) {
        angle[i] = random(0.0,TWO_PI);
        rad[i] = random(1, 5) * s_RADIUS;
        speed[i] = random(-.01, .01);
        x[i] = width/2;
        y[i] = height/2;
        nbConnex[i] = 0;
        diam[i] = 0;
    }
void draw()
{
	// draw background
	nvgBeginPath(vg);
	nvgRect(vg, 0,0, width,height);
	nvgFillColor(vg, nvgRGBA(255,255,255,255));
	nvgFill(vg);

	nvgStrokeColor(vg, nvgRGBA(0,0,0,50));
	for (int i=0; i<nbPts-1; i++) {
		for (int j=i+1; j<nbPts; j++) {
			if (dist(x[i], y[i], x[j], y[j])<RADIUS+10) {
				nvgBeginPath(vg);
				nvgMoveTo(vg, x[i], y[i]);
				nvgLineTo(vg, x[j], y[j]);
				nvgStroke(vg);
				nbConnex[i]++;
				nbConnex[j]++;
			}
		}
	}

	for (int i=0; i<nbPts; i++) {
		angle[i] += speed[i];
		x[i] = ease(x[i], width/2 + cos(angle[i]) * rad[i], 0.1);
		y[i] = ease(y[i], height/2 + sin(angle[i]) * rad[i], 0.1);
		diam[i] = ease(diam[i], min(nbConnex[i], 7)*max(0.5,(rad[i]/RADIUS/5.0)), 0.1);

		nvgBeginPath(vg);
		nvgFillColor(vg, nvgRGBA(0,0,0,100));
		nvgEllipse(vg, x[i], y[i], diam[i] + 3, diam[i] + 3);
		nvgFill(vg);

		nvgBeginPath(vg);
		nvgFillColor(vg, nvgRGBA(0,0,0,255));
		nvgEllipse(vg, x[i], y[i], diam[i], diam[i]);
		nvgFill(vg);

		nbConnex[i] = 0;
	}

	nvgBeginPath(vg);
	nvgMoveTo(vg, 0,0);
	nvgLineTo(vg, 100, 40);
	nvgStrokeColor(vg, nvgRGB(255,255,255));
	nvgStrokeWidth(vg, 3);
	nvgStroke(vg);
}*/

// 表示の初期化
void caInit(int w, int h)
{
	width = w;
	height = h;

	// Calculate pixel ration for hi-dpi devices.
	pixelRatio = (float)width / (float)height;

	vg = nvgCreate(NVG_ANTIALIAS);

	nvgCreateFont(vg, "sans-bold", CATGL_ASSETS("Roboto-Bold.ttf"));
	nvgFontFace(vg, "sans-bold");
}

// 描画
void caRender()
{
	glViewport(0, 0, width, height);

	//glClearColor(0.3f, 0.3f, 0.32f, 1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	nvgBeginFrame(vg, width, height, pixelRatio);

/*	NVGpaint bg = nvgLinearGradient(vg, 0,0,0, height,nvgRGBA(0,0,255,255), nvgRGBA(255,0,0,255));
	nvgRect(vg, 0, 0, width, height);
	nvgFillPaint(vg, bg);
	nvgFill(vg);*/

	nvgBeginPath(vg);
	nvgRect(vg, 100,100, 120,30);
	nvgFillColor(vg, nvgRGBA(255,192,0,255));
	nvgFill(vg);

	nvgBeginPath(vg);
	nvgRect(vg, 200,200, 220,30);
	nvgCircle(vg, 220,220, 5);
	nvgPathWinding(vg, NVG_HOLE);   // Mark circle as a hole.
	//nvgPathWinding(vg, NVG_CW);
	nvgFillColor(vg, nvgRGBA(255,192,0,255));
	nvgFill(vg);

	/*nvgRect(vg, 0, 0, width, height);
	nvgFillColor(vg, nvgRGBA(110, 201, 235, 255));
	nvgStrokeColor(vg, nvgRGBA(110, 201, 235, 255));
	nvgStrokeWidth(vg, 10.0f);
	nvgFill(vg);
	nvgStroke(vg);*/

	nvgBeginPath(vg);
	/* y は中心位置なことに注意。実際ここの部分は nvgTextBounds や nvgTextMetrics などを使って計算して求める必要があるだろう */
	//int x = 0;
	//int y = 10;
	nvgText(vg, /*x, y,*/100,100, "Hello!", NULL);
	nvgFill(vg);

	// GUI
	// Widgets
	caDrawWindow(vg, "Title", 10, 100, 100, 100);
	caDrawSearchBox(vg, "Search", 20, 120, 280, 25);
/*	y += 40;
	drawDropDown(vg, "Effects", x,y,280,28);
	popy = y + 14;
	y += 45;*/

//	draw();

	nvgEndFrame(vg);
}

void caEnd()
{
	nvgDelete(vg);
}
