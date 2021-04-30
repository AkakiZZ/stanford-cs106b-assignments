/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gmath.h"
#include "gwindow.h"
#include "simpio.h"
#include "gobjects.h"
using namespace std;

void drawSierepinski(GWindow &gw, GPoint p1, GPoint p2, GPoint p3, double size, int n);
void recurse(GWindow &gw, GPoint p1, GPoint p2, GPoint p3, double size, int n);


int main() {
	double sideLength = getReal("Enter length: ");
	while (sideLength <= 0) {
		sideLength = getReal("Enter length number > 0: ");
	}
	int order = getInteger("Enter order: ");
	while (order < 0) {
		order = getInteger("Enter number >= 0: ");
	}
    GWindow gw;
	// points of first triangle
	double distanceFromCenter = sideLength * sinDegrees(60) / 2;
	GPoint p2(gw.getWidth() / 2, gw.getHeight() / 2 - distanceFromCenter);
	GPoint p3 = gw.drawPolarLine(p2, sideLength, -60);
	GPoint p1 = gw.drawPolarLine(p2, sideLength, -120);
	drawSierepinski(gw, p1, p2, p3, sideLength, order);
	return 0;
}

void drawSierepinski(GWindow &gw, GPoint p1, GPoint p2, GPoint p3, double size, int n) {
	//draw first triangle
	gw.add(new GLine(p1.getX(), p1.getY(), p2.getX(), p2.getY()));
	gw.add(new GLine(p2.getX(), p2.getY(), p3.getX(), p3.getY()));
	gw.add(new GLine(p1.getX(), p1.getY(), p3.getX(), p3.getY()));
	//recurse for others
	recurse(gw, p1, p2, p3, size, n);
}

void recurse(GWindow &gw, GPoint p1, GPoint p2, GPoint p3, double size, int n) {
	if (n == 0)
		return;
	//get midpoints
	GPoint x((p1.getX() + p2.getX()) / 2, (p1.getY() + p2.getY()) / 2);
	GPoint y = gw.drawPolarLine(x, size / 2, 0);
	GPoint z = gw.drawPolarLine(y, size / 2, -120);
	gw.add(new GLine(x.getX(), x.getY(), y.getX(), y.getY()));
	gw.add(new GLine(y.getX(), y.getY(), z.getX(), z.getY()));
	gw.add(new GLine(x.getX(), x.getY(), z.getX(), z.getY()));
	recurse(gw, p1, x, z, size / 2, n - 1);
	recurse(gw, x, p2, z, size / 2, n - 1);
	recurse(gw, z, y, p3, size / 2, n - 1);
}
