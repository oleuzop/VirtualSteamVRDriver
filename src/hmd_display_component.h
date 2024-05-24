//============ Copyright (c) Valve Corporation, All rights reserved. ============
#pragma once

#include <openvr_driver.h>

enum MyComponent
{
	MyComponent_system_touch,
	MyComponent_system_click,

	MyComponent_MAX
};

struct MyHMDDisplayDriverConfiguration
{
	int32_t window_x;
	int32_t window_y;

	int32_t window_width;
	int32_t window_height;

	int32_t render_width;
	int32_t render_height;

	int32_t fps;
};

class MyHMDDisplayComponent : public vr::IVRDisplayComponent, public vr::IVRVirtualDisplay
{
public:
	explicit MyHMDDisplayComponent(const MyHMDDisplayDriverConfiguration& config);
	~MyHMDDisplayComponent();

	// ----- Functions to override vr::IVRDisplayComponent -----
	bool IsDisplayOnDesktop() override;
	bool IsDisplayRealDisplay() override;
	void GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight) override;
	void GetEyeOutputViewport(vr::EVREye eEye, uint32_t* pnX, uint32_t* pnY, uint32_t* pnWidth, uint32_t* pnHeight) override;
	void GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom) override;
	vr::DistortionCoordinates_t ComputeDistortion(vr::EVREye eEye, float fU, float fV) override;
	void GetWindowBounds(int32_t* pnX, int32_t* pnY, uint32_t* pnWidth, uint32_t* pnHeight) override;
	bool ComputeInverseDistortion(vr::HmdVector2_t* pResult, vr::EVREye eEye, uint32_t unChannel, float fU, float fV) override;

	void Present(const vr::PresentInfo_t* pPresentInfo, uint32_t unPresentInfoSize) override;
	void WaitForPresent() override;
	bool GetTimeSinceLastVsync(float* pfSecondsSinceLastVsync, uint64_t* pulFrameCounter) override;

private:
	MyHMDDisplayDriverConfiguration config_;
	int64_t frameCounter_;
};
