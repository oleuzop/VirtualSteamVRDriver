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

void Configuration::InitPimaxCrystalResolution(const QualityType& qualityType)
{
	switch (qualityType)
	{
	case QualityType::POTATO:
		resRenderX = int(4312 * 0.47692307692f);
		resRenderY = int(5100 * 0.47692307692f);
		break;
	case QualityType::LOW:
		resRenderX = int(4312 * 0.56923076923f);
		resRenderY = int(5100 * 0.56923076923f);
		break;
	case QualityType::MEDIUM:
		resRenderX = int(4312 * 0.66153846153f);
		resRenderY = int(5100 * 0.66153846153f);
		break;
	case QualityType::HIGH:
		resRenderX = int(4312 * 0.81538461538f);
		resRenderY = int(5100 * 0.81538461538f);
		break;
	case QualityType::ULTRA:
		resRenderX = int(4312 * 0.87692307692f);
		resRenderY = int(5100 * 0.87692307692f);
		break;
	case QualityType::GODLIKE:
		resRenderX = 4312;
		resRenderY = 5100;
		break;
	}
}

void Configuration::InitPimax8KResolution(const QualityType& qualityType)
{
	switch (qualityType)
	{
	case QualityType::POTATO:
		resRenderX = int(3840 * 0.47692307692f);
		resRenderY = int(2160 * 0.47692307692f);
		break;
	case QualityType::LOW:
		resRenderX = int(3840 * 0.56923076923f);
		resRenderY = int(2160 * 0.56923076923f);
		break;
	case QualityType::MEDIUM:
		resRenderX = int(3840 * 0.66153846153f);
		resRenderY = int(2160 * 0.66153846153f);
		break;
	case QualityType::HIGH:
		resRenderX = int(3840 * 0.81538461538f);
		resRenderY = int(2160 * 0.81538461538f);
		break;
	case QualityType::ULTRA:
		resRenderX = int(3840 * 0.87692307692f);
		resRenderY = int(2160 * 0.87692307692f);
		break;
	case QualityType::GODLIKE:
		resRenderX = 3840;
		resRenderY = 2160;
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

		left[0] = -1.376382f;
		right[0] = 0.839100f;
		top[0] = -1.428148f;
		bottom[0] = 0.965689f;

		left[1] = -0.839100f;
		right[1] = 1.376382f;
		top[1] = -1.428148f;
		bottom[1] = 0.965689f;

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

		left[0] = -1.376382f;
		right[0] = 0.839100f;
		top[0] = -1.376382f;
		bottom[0] = 0.900404f;

		left[1] = -0.839100f;
		right[1] = 1.376382f;
		top[1] = -1.376382f;
		bottom[1] = 0.900404f;

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

		left[0] = -1.279942f;
		right[0] = 1.279942f;
		top[0] = -1.279942f;
		bottom[0] = 1.279942f;

		left[1] = -1.279942f;
		right[1] = 1.279942f;
		top[1] = -1.279942f;
		bottom[1] = 1.279942f;

		InitPico4Resolution(qualityType);
		break;

	case HeadsetType::PIMAX_CRYSTAL:
		fpsRender = 120;

		//Left eye raw LRBT values:
		//    left:        -1.264092
		//    right:        0.889501
		//    bottom:      -1.274264
		//    top:          1.274264
		//
		//Right eye raw LRBT values:
		//    left:        -0.889501
		//    right:        1.264092
		//    bottom:      -1.274264
		//    top:          1.274264

		left[0] = -1.264092f;
		right[0] = 0.889501f;
		top[0] = -1.274264f;
		bottom[0] = 1.274264f;

		left[1] = -0.889501f;
		right[1] = 1.264092f;
		top[1] = -1.274264f;
		bottom[1] = 1.274264f;

		InitPimaxCrystalResolution(qualityType);
		break;

	case HeadsetType::PIMAX_8K:
		fpsRender = 90;

//		Left eye raw LRBT values :
//		left:        -1.742203
//		right :       1.346154
//		bottom :     -1.306135
//		top :         1.306135
//		
//		Left eye raw FOV :
//		left:       -60.14 deg
//		right :      53.39 deg
//		bottom :    -52.56 deg
//		top :        52.56 deg
//		horiz. :    113.54 deg
//		vert. :     105.12 deg
//		
//		Left eye head FOV :
//		left:       -70.14 deg
//		right :      43.39 deg
//		bottom :    -52.14 deg
//		top :        52.14 deg
//		horiz. :    113.54 deg
//		vert. :     104.27 deg
//		
//		Right eye HAM mesh :
//		original vertices : 120, triangles : 40
//		optimized vertices : 48, n - gons : 4
//		mesh area : 8.73 %
//		
//		Right eye to head transformation matrix :
//		[[ 0.984808, -0., -0.173648, 0.033502],
//		[0., 1., -0., 0.],
//		[0.173648, 0., 0.984808, 0.]]
//		
//		Right eye raw LRBT values :
//		left:        -1.346154
//		right :       1.742203
//		bottom :     -1.306135
//		top :         1.306135
//		
//		Right eye raw FOV :
//		left:       -53,39 deg
//		right :      60,14 deg
//		bottom :    -52,56 deg
//		top :        52,56 deg
//		horiz. :    113,54 deg
//		vert. :     105,12 deg
//		
//		Right eye head FOV :
//		left:       -43,39 deg
//		right:       70,14 deg
//		bottom:     -52,14 deg
//		top:         52,14 deg
//		horiz.:     113,54 deg
//		vert.:      104,27 deg
//		
//		Total FOV :
//		horizontal: 140.29 deg
//		vertical :  104.27 deg
//		diagonal :  134.88 deg
//		overlap :    86.79 deg
//		
//		View geometry :
//		left view rotation : -10.0 deg
//		right view rotation : 10.0 deg
//		reported IPD : 67.0 mm

		left[0] = -1.742203f;
		right[0] = 1.346154f;
		top[0] = -1.306135f;
		bottom[0] = 1.306135f;

		left[1] = -1.346154f;
		right[1] = 1.742203f;
		top[1] = -1.306135f;
		bottom[1] = 1.306135f;

		//////////////////////////////////////////
		// Real rendering resolution
		//left[0]   = -2.768506888f;
		//right[0]  = 0.9453224349f;
		//top[0]    = -1.286408332f;
		//bottom[0] = 1.286408332f;
		//
		//left[1]   = -0.9453224349f;
		//right[1]  = 2.768506888f;
		//top[1]    = -1.286408332f;
		//bottom[1] = 1.286408332f;
		//////////////////////////////////////////

		InitPimax8KResolution(qualityType);
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