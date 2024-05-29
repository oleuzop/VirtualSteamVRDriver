//============ Copyright (c) Valve Corporation, All rights reserved. ============
#include "hmd_display_component.h"

#include "driverlog.h"
#include <string.h>

#include "Configuration.h"

//extern MixedVr::LastFrame lastFrame;

//-----------------------------------------------------------------------------
// DISPLAY DRIVER METHOD DEFINITIONS
//-----------------------------------------------------------------------------

MyHMDDisplayComponent::MyHMDDisplayComponent(const MyHMDDisplayDriverConfiguration &config)
	: config_( config ), frameCounter_(0) {
	
}

MyHMDDisplayComponent::~MyHMDDisplayComponent() {
}



//-----------------------------------------------------------------------------
// Purpose: To inform vrcompositor if this display is considered an on-desktop display.
//-----------------------------------------------------------------------------
bool MyHMDDisplayComponent::IsDisplayOnDesktop()
{
	return true;
}

//-----------------------------------------------------------------------------
// Purpose: To as vrcompositor to search for this display.
//-----------------------------------------------------------------------------
bool MyHMDDisplayComponent::IsDisplayRealDisplay()
{
	return false;
}

//-----------------------------------------------------------------------------
// Purpose: To inform the rest of the vr system what the recommended target size should be
//-----------------------------------------------------------------------------
void MyHMDDisplayComponent::GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight)
{
	*pnWidth = config_.render_width;
	*pnHeight = config_.render_height;
}

//-----------------------------------------------------------------------------
// Purpose: To inform vrcompositor how the screens should be organized.
//-----------------------------------------------------------------------------
void MyHMDDisplayComponent::GetEyeOutputViewport(vr::EVREye eEye, uint32_t* pnX, uint32_t* pnY, uint32_t* pnWidth, uint32_t* pnHeight)
{
	*pnY = 0;

	// Each eye will have half the window
	*pnWidth = config_.window_width / 2;

	// Each eye will have the full height
	*pnHeight = config_.window_height;

	if (eEye == vr::Eye_Left)
	{
		// Left eye viewport on the left half of the window
		*pnX = 0;
	}
	else
	{
		// Right eye viewport on the right half of the window
		*pnX = config_.window_width / 2;
	}
}

//-----------------------------------------------------------------------------
// Purpose: To inform the compositor what the projection parameters are for this HMD.
//-----------------------------------------------------------------------------
void MyHMDDisplayComponent::GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom)
{
	*pfLeft = gConfiguration.Left(eEye);
	*pfRight = gConfiguration.Right(eEye);
	*pfTop = gConfiguration.Top(eEye);
	*pfBottom = gConfiguration.Bottom(eEye);
}

//-----------------------------------------------------------------------------
// Purpose: To compute the distortion properties for a given uv in an image.
//-----------------------------------------------------------------------------
vr::DistortionCoordinates_t MyHMDDisplayComponent::ComputeDistortion(vr::EVREye eEye, float fU, float fV)
{
	vr::DistortionCoordinates_t coordinates{};
	coordinates.rfBlue[0] = fU;
	coordinates.rfBlue[1] = fV;
	coordinates.rfGreen[0] = fU;
	coordinates.rfGreen[1] = fV;
	coordinates.rfRed[0] = fU;
	coordinates.rfRed[1] = fV;
	return coordinates; 
}

//-----------------------------------------------------------------------------
// Purpose: To inform vrcompositor what the window bounds for this virtual HMD are.
//-----------------------------------------------------------------------------
void MyHMDDisplayComponent::GetWindowBounds(int32_t* pnX, int32_t* pnY, uint32_t* pnWidth, uint32_t* pnHeight)
{
	*pnX = config_.window_x;
	*pnY = config_.window_y;
	*pnWidth = config_.window_width;
	*pnHeight = config_.window_height;
}

bool MyHMDDisplayComponent::ComputeInverseDistortion(vr::HmdVector2_t* pResult, vr::EVREye eEye, uint32_t unChannel, float fU, float fV)
{
	return false;
}

void MyHMDDisplayComponent::Present(const vr::PresentInfo_t* pPresentInfo, uint32_t unPresentInfoSize) {
	frameCounter_++;
}

/** Block until the last presented buffer start scanning out. */
void MyHMDDisplayComponent::WaitForPresent() {
}

/** Provides timing data for synchronizing with display. */
bool MyHMDDisplayComponent::GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter) {

	*pfSecondsSinceLastVsync = 0.0f;
	*pulFrameCounter = frameCounter_;
	return true;
}
