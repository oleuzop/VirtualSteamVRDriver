#pragma once

enum HeadsetType
{
	UNDEFINED_HEADSET = 0,
	QUEST3,
	QUEST_PRO,
	PICO4,
	PIMAX_CRYSTAL,
	PIMAX_8K_X_NORMAL,
	PIMAX_8K_X_LARGE,
	WMR_EMULATOR,
	NUMBER_OF_HEADSETS
};

enum QualityType
{
	UNDEFINED_QUALITY = 0,
	POTATO,
	LOW,
	MEDIUM,
	HIGH,
	ULTRA,
	GODLIKE,
	NUMBER_OF_QUALITIES
};

class Configuration
{
public:
	Configuration();
	~Configuration();

	void Init(const HeadsetType& headsetType, const QualityType& qualityType, const float& resolutionFactor = 1.0f);

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
	void InitQuest3Resolution(const QualityType& qualityType);
	void InitPico4Resolution(const QualityType& qualityType);
	void InitPimaxCrystalResolution(const QualityType& qualityType);
	void InitPimax8KXResolution(const QualityType& qualityType);	

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