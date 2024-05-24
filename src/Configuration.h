#pragma once

class Configuration
{
public:
	Configuration();
	~Configuration();

	inline int FpsRender() { return fpsRender; }

	inline int ResRenderX() { return resRenderX; }
	inline int ResRenderY() { return resRenderY; }

	inline int ResWindowX() { return resRenderX * 2; }
	inline int ResWindowY() { return resRenderY; }


	inline const float& Left(const int & eye) { return left[eye]; }
	inline const float& Right(const int& eye) { return right[eye]; }
	inline const float& Top(const int& eye) { return top[eye]; }
	inline const float& Bottom(const int& eye) { return bottom[eye]; }


private:
	int fpsRender;
	int resRenderX;
	int resRenderY;

	float left[2];
	float right[2];
	float top[2];
	float bottom[2];

};

extern Configuration gConfiguration;