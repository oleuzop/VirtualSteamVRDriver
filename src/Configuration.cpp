#include "Configuration.h"

Configuration::Configuration() {


	/*
	Streaming Resolution
	Render Resolution per eye

	Quest
	Potato: 1200x1344
	Low: 1536x1728
	Medium: 1824x2016
	High: 2208x2400

	Quest 2/Pico Neo 3/Quest Pro/Quest 3
	Potato: 1440x1536
	Low: 1728x1824
	Medium: 2016x2112
	High: 2496x2592
	Ultra: 2688x2784
	Godlike: 3072x3216 (Quest Pro/Quest 3)

	Pico 4
	Potato: 1488x1488
	Low: 1776x1776
	Medium: 2064x2064
	High: 2544x2544
	Ultra: 2736x2736
	Godlike: 3120x3120
	*/

	// Godlike: 3072x3216 (Quest Pro/Quest 3)
	//resRenderX = 3072;
	//resRenderY = 3216;

	// Medium: 2016x2112
	//resRenderX = 2016;
	//resRenderY = 2112;

	// Low: 1728x1824
	//resRenderX = 1728;
	//resRenderY = 1824;

	// Potato: 1440x1536
	//resRenderX = 1440;
	//resRenderY = 1536;

	//resRenderX = 1440 / 2;
	//resRenderY = 1536 / 2;

	fpsRender = 72;
	resRenderX = 1440 / 3 * 2;
	resRenderY = 1536 / 3 * 2;
	
	//resRenderX = 3072;
	//resRenderY = 3216;
	//////////////////////////////////////////////////////////////////

	left[0] = -0.942477763f;
	right[0] = 0.698131680f;
	top[0] = -0.959931076f;
	bottom[0] = 0.767944872f;

	left[1] = -0.698131680f;
	right[1] = 0.942477763f;
	top[1] = -0.959931076f;
	bottom[1] = 0.767944872f;

	/*
	resRenderX = 1280;
	resRenderY = 1280;

	left[0] = -1.0f;
	right[0] = 1.0f;
	top[0] = -1.0f;
	bottom[0] = 1.0f;

	left[1] = -1.0f;
	right[1] = 1.0f;
	top[1] = -1.0f;
	bottom[1] = 1.0f;
	*/

	/*
	// WMR emulator
	if (eEye == vr::EVREye::Eye_Left) {
		*pfLeft = ;
		*pfRight = 1.0f;
		*pfTop = -1.0f;
		*pfBottom = 1.0f;
	}
	else {
		*pfLeft = -1.0f;
		*pfRight = 1.0f;
		*pfTop = -1.0f;
		*pfBottom = 1.0f;
	}

	// Quest 3
	if (eEye == vr::EVREye::Eye_Left) {
		*pfLeft = -0.942477763f;
		*pfRight = 0.698131680f;
		*pfTop = -0.959931076f;
		*pfBottom = 0.767944872f;
	}
	else {
		*pfLeft = -0.698131680f;
		*pfRight = 0.942477763f;
		*pfTop = -0.959931076f;
		*pfBottom = 0.767944872f;
	}
	*/

}

Configuration::~Configuration() {
}

Configuration gConfiguration;