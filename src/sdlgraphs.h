#ifndef _SDL_GRAPHS_H_
#define _SDL_GRAPHS_H_

#include <SDL2/SDL.h>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <string>

#define RGB(r, g, b) ((Uint8)r << 16 | (Uint8)g << 8 | (Uint8)b)

class Graph
{
public:

	Graph(float xMin, float xMax, float xScale, yMin, yMax, yScale, int width, int height, Uint32 color);

	~Graph();

	SDL_Surface* getSurface() const;

	void drawGrid(int thickness, int length);

	void update();

	void clear();

	int writeBMP(const std::string& filename);

	inline void setColor(int r, int g, int b) { m_color = RGB(r, g, b); }

	inline Uint32* getColor() { return &m_color; }

	inline void setXMin(float xMin) { m_xMin = xMin; }

	inline float getXMin() const { return m_xMin; }

	inline void setXMax(float xMax) { m_xMax = xMax; }

	inline float getXMax() const { return m_xMax; }

	inline void setXScale(float xScale) { m_xScale = xScale; }

	inline float getXScale() const { return m_xScale; }

	inline void setYMin(float yMin) { m_yMin = yMin; }

	inline float getYMin() const { return m_yMin; }

	inline void setYMax(float yMax) { m_yMax = yMax; }

	inline float getYMax() const { return m_yMax; }

	inline void setYScale(float yScale) { m_yScale = yScale; }

	inline float getYScale() const { m_yScale = yScale; }

	inline void setSize(int width, int height) { m_width = width; m_height = height; }

	inline void setWith(int width) { m_width = width; }

	inline int getWidth() const { return m_width; }

	inline void setHeight(int height) { m_height = height; }

	inline int getHeight() const { return m_height; }

private:

	int _getWidthFromCoordinate(float x);

	int _getHeightFromCoordinate(float y);

	Uint32* _getPixelFromCoordinates(float x, float y);

	Uint32* _getPixelFromWindow(int x, int y);

	int _writeBMPHeader(FILE *file, int width, int height);

	int _writeBMPDate(FILE *file);

private:

	float m_xMin;
	float m_xMax;
	float m_xScale;
	float m_yMin;
	float m_yMax;
	float m_yScale;

	int m_width;
	int m_height;

	Uint32 m_color;

	SDL_Surface *m_workingSurface;

};
