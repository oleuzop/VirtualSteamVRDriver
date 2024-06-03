#include "Configuration.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "driverlog.h"


Configuration::Configuration() {

	fpsRender = 72;
	resRenderX = 1024;
	resRenderY = 1024;

	left[0] = -(float(M_PI) / 4.0f);
	right[0] = (float(M_PI) / 4.0f);
	top[0] = -(float(M_PI) / 4.0f);
	bottom[0] = (float(M_PI) / 4.0f);

	left[1] = -(float(M_PI) / 4.0f);
	right[1] = (float(M_PI) / 4.0f);
	top[1] = -(float(M_PI) / 4.0f);
	bottom[1] = (float(M_PI) / 4.0f);

}

Configuration::~Configuration() {
}

void Configuration::InitQuest3Resolution(const QualityType& qualityType)
{

	switch (qualityType)
	{
	case QualityType::POTATO:
		resRenderX = 1440;
		resRenderY = 1536;
		break;
	case QualityType::LOW:
		resRenderX = 1728;
		resRenderY = 1824;
		break;
	case QualityType::MEDIUM:
		resRenderX = 2016;
		resRenderY = 2112;
		break;
	case QualityType::HIGH:
		resRenderX = 2496;
		resRenderY = 2592;
		break;
	case QualityType::ULTRA:
		resRenderX = 2688;
		resRenderY = 2784;
		break;
	case QualityType::GODLIKE:
		resRenderX = 3072;
		resRenderY = 3216;
		break;
	}
}

void Configuration::InitPico4Resolution(const QualityType& qualityType)
{
	switch (qualityType)
	{
	case QualityType::POTATO:
		resRenderX = 1488;
		resRenderY = 1488;
		break;
	case QualityType::LOW:
		resRenderX = 1776;
		resRenderY = 1776;
		break;
	case QualityType::MEDIUM:
		resRenderX = 2064;
		resRenderY = 2064;
		break;
	case QualityType::HIGH:
		resRenderX = 2544;
		resRenderY = 2544;
		break;
	case QualityType::ULTRA:
		resRenderX = 2736;
		resRenderY = 2736;
		break;
	case QualityType::GODLIKE:
		resRenderX = 3120;
		resRenderY = 3120;
		break;
	}
}

void Configuration::Init(
	const HeadsetType& headsetType,
	const QualityType& qualityType,
	const float& resolutionFactor /*= 1.0f*/
) {
	
	// https://risa2000.github.io/hmdgdb/
	switch (headsetType)
	{
	case HeadsetType::QUEST3:
		fpsRender = 72;

		//Left eye raw LRBT values :
		//	left: -1.376382
		//	right : 0.839100
		//	bottom : -1.428148
		//	top : 0.965689

		//Right eye raw LRBT values :
		//	left: -0.839100
		//	right : 1.376382
		//	bottom : -1.428148
		//	top : 0.965689

		left[0] = (float)atan(-1.376382f);
		right[0] = (float)atan(0.839100f);
		top[0] = (float)atan(-1.428148f);
		bottom[0] = (float)atan(0.965689f);

		left[1] = (float)atan(-0.839100f);
		right[1] = (float)atan(1.376382f);
		top[1] = (float)atan(-1.428148f);
		bottom[1] = (float)atan(0.965689f);

		InitQuest3Resolution(qualityType);
		break;

	case HeadsetType::QUEST_PRO:
		fpsRender = 72;

		//Left eye raw LRBT values :
		//	left: -1.376382
		//	right : 0.839100
		//	bottom : -1.376382
		//	top : 0.900404

		//Right eye raw LRBT values :
		//	left: -0.839100
		//	right : 1.376382
		//	bottom : -1.376382
		//	top : 0.900404

		left[0] = (float)atan(-1.376382f);
		right[0] = (float)atan(0.839100f);
		top[0] = (float)atan(-1.376382f);
		bottom[0] = (float)atan(0.900404f);

		left[1] = (float)atan(-0.839100f);
		right[1] = (float)atan(1.376382f);
		top[1] = (float)atan(-1.376382f);
		bottom[1] = (float)atan(0.900404f);

		InitQuest3Resolution(qualityType);
		break;

	case HeadsetType::PICO4:
		fpsRender = 72;

		//Left eye raw LRBT values :
		//	left: -1.279942
		//	right : 1.279942
		//	bottom : -1.279942
		//	top : 1.279942
		//
		//Right eye raw LRBT values :
		//	left: -1.279942
		//	right : 1.279942
		//	bottom : -1.279942
		//	top : 1.279942

		left[0] = (float)atan(-1.279942f);
		right[0] = (float)atan(1.279942f);
		top[0] = (float)atan(-1.279942f);
		bottom[0] = (float)atan(1.279942f);

		left[1] = (float)atan(-1.279942f);
		right[1] = (float)atan(1.279942f);
		top[1] = (float)atan(-1.279942f);
		bottom[1] = (float)atan(1.279942f);

		InitPico4Resolution(qualityType);
		break;

	case HeadsetType::WMR_EMULATOR:
		fpsRender = 90;

		left[0] = -1.0f;
		right[0] = 1.0f;
		top[0] = -1.0f;
		bottom[0] = 1.0f;

		left[1] = -1.0f;
		right[1] = 1.0f;
		top[1] = -1.0f;
		bottom[1] = 1.0f;

		InitPico4Resolution(qualityType);
		break;
	}

	DriverLog("resRender: [%d, %d],\tresolutionFactor: %f", resRenderX, resRenderY, resolutionFactor);

	resRenderX = int(resRenderX * resolutionFactor);
	resRenderY = int(resRenderY * resolutionFactor);

	DriverLog("Effective resolution: [%d, %d]", resRenderX, resRenderY);
}

Configuration gConfiguration;