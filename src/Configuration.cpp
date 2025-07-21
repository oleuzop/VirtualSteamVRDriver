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

void Configuration::InitHpG2Resolution(const QualityType& qualityType)
{

	switch (qualityType)
	{
	case QualityType::POTATO:
		resRenderX = int(2688 * 0.47692307692f);
		resRenderY = int(2784 * 0.47692307692f);
		break;
	case QualityType::LOW:
		resRenderX = int(2688 * 0.56923076923f);
		resRenderY = int(2784 * 0.56923076923f);
		break;
	case QualityType::MEDIUM:
		resRenderX = int(2688 * 0.66153846153f);
		resRenderY = int(2784 * 0.66153846153f);
		break;
	case QualityType::HIGH:
		resRenderX = int(2688 * 0.81538461538f);
		resRenderY = int(2784 * 0.81538461538f);
		break;
	case QualityType::ULTRA:
		resRenderX = int(2688 * 0.87692307692f);
		resRenderY = int(2784 * 0.87692307692f);
		break;
	case QualityType::GODLIKE:
		resRenderX = 2688;
		resRenderY = 2784;
		break;
	}
}

void Configuration::InitQuest3Resolution(const QualityType& qualityType)
{

	switch (qualityType)
	{
	case QualityType::POTATO:
		resRenderX = 2248;
		resRenderY = 2192;
		break;
	case QualityType::LOW:
		resRenderX = 2248;
		resRenderY = 2192;
		break;
	case QualityType::MEDIUM:
		resRenderX = 2248;
		resRenderY = 2192;
		break;
	case QualityType::HIGH:
		resRenderX = 2248;
		resRenderY = 2192;
		break;
	case QualityType::ULTRA:
		resRenderX = 2248;
		resRenderY = 2192;
		break;
	case QualityType::GODLIKE:
		resRenderX = 2248;
		resRenderY = 2192;
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

void Configuration::InitPimax8KXResolution(const QualityType& qualityType)
{
	switch (qualityType)
	{
	case QualityType::POTATO:
		resRenderX = int(4622 * 0.47692307692f);
		resRenderY = int(3948 * 0.47692307692f);
		break;
	case QualityType::LOW:
		resRenderX = int(4622 * 0.56923076923f);
		resRenderY = int(3948 * 0.56923076923f);
		break;
	case QualityType::MEDIUM:
		resRenderX = int(4622 * 0.66153846153f);
		resRenderY = int(3948 * 0.66153846153f);
		break;
	case QualityType::HIGH:
		resRenderX = int(4622 * 0.81538461538f);
		resRenderY = int(3948 * 0.81538461538f);
		break;
	case QualityType::ULTRA:
		resRenderX = int(4622 * 0.87692307692f);
		resRenderY = int(3948 * 0.87692307692f);
		break;
	case QualityType::GODLIKE:
		resRenderX = 4622;
		resRenderY = 3948;
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
	case HeadsetType::HP_G2:
		fpsRender = 90;

		//Left eye raw LRBT values:
		//    left:        -1.167639
		//    right:        0.991869
		//    bottom:      -1.056352
		//    top:          1.056971

		//Right eye raw LRBT values:
		//    left:        -0.993480
		//    right:        1.172087
		//    bottom:      -1.054743
		//    top:          1.056776

		left[0]   = -1.167639;
		right[0]  =  0.991869;
		top[0]    = -1.056352;
		bottom[0] =  1.056971;

		left[1]   = -0.993480;
		right[1]  =  1.172087;
		top[1]    = -1.054743;
		bottom[1] =  1.056776;

		InitHpG2Resolution(qualityType);
		break;

	case HeadsetType::HP_G2_ASYM:
		fpsRender = 90;


		///////////////////////////////////////////////////
		// views[0].fov.angleLeft = -0.859543;
		// views[0].fov.angleRight = 0.779103;
		// views[0].fov.angleUp = 0.809881;
		// views[0].fov.angleDown = -0.810649;
		// 
		// views[1].fov.angleLeft = -0.781263;
		// views[1].fov.angleRight = 0.858322;
		// views[1].fov.angleUp = 0.810965;
		// views[1].fov.angleDown = -0.809480;
		///////////////////////////////////////////////////
		// Sobo
		//left[0] = tan(-0.859543);
		//right[0] = tan(0.779103);
		//top[0] = tan(-0.810649);
		//bottom[0] = tan(0.809881);
		//left[1] = tan(-0.781263);
		//right[1] = tan(0.858322);
		//top[1] = tan(-0.809480);
		//bottom[1] = tan(0.810965);

		///////////////////////////////////////////////////
		//VR: views[0].fov.angleLeft : -0.862011
		//VR: views[0].fov.angleRight : 0.781368
		//VR: views[0].fov.angleUp : 0.815872
		//VR: views[0].fov.angleDown : -0.809352
		// 
		//VR: views[1].fov.angleLeft : -0.780843
		//VR: views[1].fov.angleRight : 0.862827
		//VR: views[1].fov.angleUp : 0.813915
		//VR: views[1].fov.angleDown : -0.811133
		// 
		//VR: center left : [-0.080769, 0.006529]
		//VR: center right : [0.082110, 0.002787]
		///////////////////////////////////////////////////
		// Topo
		left[0] = tan(-0.862011);
		right[0] = tan(0.781368);
		top[0] = tan(-0.809352);
		bottom[0] = tan(0.815872);
		left[1] = tan(-0.780843);
		right[1] = tan(0.862827);
		top[1] = tan(-0.811133);
		bottom[1] = tan(0.813915);


		//left[0] *= 0.5f;
		//right[0] *= 0.5f;
		//top[0] *= 0.5f;
		//bottom[0] *= 0.5f;
		//left[1] *= 0.5f;
		//right[1] *= 0.5f;
		//top[1] *= 0.5f;
		//bottom[1] *= 0.5f;

		InitHpG2Resolution(qualityType);
		break;

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

	case HeadsetType::PIMAX_8K_X_NORMAL:
		fpsRender = 90;

		//Left eye head FOV:
		//    left:       -70.14 deg
		//    right:       41.47 deg
		//    bottom:     -51.35 deg
		//    top:         51.35 deg
		//
		//Right eye head FOV:
		//    left:       -41.47 deg
		//    right:       70.14 deg
		//    bottom:     -51.35 deg
		//    top:         51.35 deg

		left[0]   = -70.14f * M_PI / 180.0f;
		right[0]  =  41.47f * M_PI / 180.0f;
		top[0]    = -51.35f * M_PI / 180.0f;
		bottom[0] =  51.35f * M_PI / 180.0f;

		left[1]   = -41.47 * M_PI / 180.0f;
		right[1]  =  70.14 * M_PI / 180.0f;
		top[1]    = -51.35 * M_PI / 180.0f;
		bottom[1] =  51.35 * M_PI / 180.0f;

		InitPimax8KXResolution(qualityType);
		break;

	case HeadsetType::PIMAX_8K_X_LARGE:
		fpsRender = 90;

		//Left eye head FOV:
		//    left:       -80.14 deg
		//    right:       41.45 deg
		//    bottom:     -51.35 deg
		//    top:         51.35 deg
		//
		//Right eye head FOV:
		//    left:       -41.45 deg
		//    right:       80.14 deg
		//    bottom:     -51.35 deg
		//    top:         51.35 deg

		left[0]   = -80.14f * M_PI / 180.0f;
		right[0]  = 41.47f * M_PI / 180.0f;
		top[0]    = -51.35f * M_PI / 180.0f;
		bottom[0] = 51.35f * M_PI / 180.0f;

		left[1]   = -41.47 * M_PI / 180.0f;
		right[1]  = 80.14 * M_PI / 180.0f;
		top[1]    = -51.35 * M_PI / 180.0f;
		bottom[1] = 51.35 * M_PI / 180.0f;

		InitPimax8KXResolution(qualityType);
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