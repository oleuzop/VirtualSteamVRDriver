//============ Copyright (c) Valve Corporation, All rights reserved. ============
#include "hmd_device_driver.h"

#include "driverlog.h"
#include <string.h>

#include "Configuration.h"

// Let's create some variables for strings used in getting settings.
// This is the section where all of the settings we want are stored. A section name can be anything,
// but if you want to store driver specific settings, it's best to namespace the section with the driver identifier
// ie "<my_driver>_<section>" to avoid collisions
static const char *my_hmd_main_settings_section = "driver_simplehmd";
static const char *my_hmd_display_settings_section = "simplehmd_display";

MyHMDControllerDeviceDriver::MyHMDControllerDeviceDriver() {

	// Keep track of whether Activate() has been called
	is_active_ = false;

	// We have our model number and serial number stored in SteamVR settings. We need to get them and do so here.
	// Other IVRSettings methods (to get int32, floats, bools) return the data, instead of modifying, but strings are
	// different.
	char model_number[ 1024 ];
	vr::VRSettings()->GetString( my_hmd_main_settings_section, "model_number", model_number, sizeof( model_number ) );
	my_hmd_model_number_ = model_number;

	// Get our serial number depending on our "handedness"
	char serial_number[ 1024 ];
	vr::VRSettings()->GetString( my_hmd_main_settings_section, "serial_number", serial_number, sizeof( serial_number ) );
	my_hmd_serial_number_ = serial_number;

	// Here's an example of how to use our logging wrapper around IVRDriverLog
	// In SteamVR logs (SteamVR Hamburger Menu > Developer Settings > Web console) drivers have a prefix of
	// "<driver_name>:". You can search this in the top search bar to find the info that you've logged.
	DriverLog( "My Dummy HMD Model Number: %s", my_hmd_model_number_.c_str() );
	DriverLog( "My Dummy HMD Serial Number: %s", my_hmd_serial_number_.c_str() );

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	char headset_type[1024];
	vr::VRSettings()->GetString(my_hmd_display_settings_section, "headset_type", headset_type, sizeof(headset_type));
	std::string headset_type_str(headset_type);
	HeadsetType headsetType = HeadsetType::UNDEFINED_HEADSET;
	if (headset_type_str == "QUEST3") {
		headsetType = HeadsetType::QUEST3;
	}
	else if (headset_type_str == "PICO4") {
		headsetType = HeadsetType::PICO4;
	}
	else if (headset_type_str == "WMR_EMULATOR") {
		headsetType = HeadsetType::WMR_EMULATOR;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	char quality_type[1024];
	vr::VRSettings()->GetString(my_hmd_display_settings_section, "quality_type", quality_type, sizeof(quality_type));
	std::string quality_type_str(quality_type);
	QualityType qualityType = QualityType::UNDEFINED_QUALITY;
	if (quality_type_str == "POTATO") {
		qualityType = QualityType::POTATO;
	}
	else if (quality_type_str == "LOW") {
		qualityType = QualityType::LOW;
	}
	else if (quality_type_str == "MEDIUM") {
		qualityType = QualityType::MEDIUM;
	}
	else if (quality_type_str == "HIGH") {
		qualityType = QualityType::HIGH;
	}
	else if (quality_type_str == "ULTRA") {
		qualityType = QualityType::ULTRA;
	}
	else if (quality_type_str == "GODLIKE") {
		qualityType = QualityType::GODLIKE;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	float resolutionFactor = vr::VRSettings()->GetFloat(my_hmd_display_settings_section, "resolution_factor");

	gConfiguration.Init(headsetType, qualityType, resolutionFactor);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	display_configuration_.window_x = 0;
	display_configuration_.window_y = 0;
	display_configuration_.window_width = gConfiguration.ResWindowX();
	display_configuration_.window_height = gConfiguration.ResWindowY();
	display_configuration_.render_width = gConfiguration.ResRenderX();
	display_configuration_.render_height = gConfiguration.ResRenderY();
	display_configuration_.fps = gConfiguration.FpsRender();

	// Initiate my display component
	my_display_component_ = std::make_unique< MyHMDDisplayComponent >(display_configuration_);
}

MyHMDControllerDeviceDriver::~MyHMDControllerDeviceDriver() {
}

inline uint32_t vers2uint(uint8_t rel, uint8_t sub, uint16_t patch) {
	return rel << 24 | sub << 16 | patch;
}
#define PVR_SERVER_VERSION vers2uint(0, 6, 0)
#define PVR_CLIENT_VERSION vers2uint(0, 6, 0)

//-----------------------------------------------------------------------------
// Purpose: This is called by vrserver after our
//  IServerTrackedDeviceProvider calls IVRServerDriverHost::TrackedDeviceAdded.
//-----------------------------------------------------------------------------
vr::EVRInitError MyHMDControllerDeviceDriver::Activate( uint32_t unObjectId )
{

	// Let's keep track of our device index. It'll be useful later.
	// Also, if we re-activate, be sure to set this.
	device_index_ = unObjectId;

	// Set a member to keep track of whether we've activated yet or not
	is_active_ = true;

	// For keeping track of frame number for animating motion.
	frame_number_ = 0;

	// Properties are stored in containers, usually one container per device index. We need to get this container to set
	// The properties we want, so we call this to retrieve a handle to it.
	vr::PropertyContainerHandle_t container = vr::VRProperties()->TrackedDeviceToPropertyContainer( device_index_ );

	// Let's begin setting up the properties now we've got our container.
	// A list of properties available is contained in vr::ETrackedDeviceProperty.

	// First, let's set the model number.
	vr::VRProperties()->SetStringProperty( container, vr::Prop_ModelNumber_String, my_hmd_model_number_.c_str() );

	// Next, display settings

	// Get the ipd of the user from SteamVR settings
	float ipd = vr::VRSettings()->GetFloat( vr::k_pch_SteamVR_Section, vr::k_pch_SteamVR_IPD_Float );
	ipd = 0.060f;
	DriverLog((std::string("IPD: ") + std::to_string(ipd)).c_str());
	vr::VRProperties()->SetFloatProperty( container, vr::Prop_UserIpdMeters_Float, ipd );

	// The distance from the user's eyes to the display in meters. This is used for reprojection.
	//vr::VRProperties()->SetFloatProperty( container, vr::Prop_UserHeadToEyeDepthMeters_Float, 0.f );

	// How long from the compositor to submit a frame to the time it takes to display it on the screen.
	vr::VRProperties()->SetFloatProperty(container, vr::Prop_SecondsFromVsyncToPhotons_Float, 0.100f);

	// -------------------------------------------------------------------------------------------------
	vr::VRProperties()->SetStringProperty(container, vr::Prop_ManufacturerName_String, "Viritualis Res");
	vr::VRProperties()->SetBoolProperty(container, vr::Prop_DeviceIsWireless_Bool, true);
	vr::VRProperties()->SetBoolProperty(container, vr::Prop_DeviceIsCharging_Bool, false);
	vr::VRProperties()->SetFloatProperty(container, vr::Prop_DeviceBatteryPercentage_Float, 1); //TODO get from phone
	vr::VRProperties()->SetBoolProperty(container, vr::Prop_Firmware_UpdateAvailable_Bool, false);//TODO implement
	vr::VRProperties()->SetBoolProperty(container, vr::Prop_Firmware_ManualUpdate_Bool, true);
	vr::VRProperties()->SetBoolProperty(container, vr::Prop_BlockServerShutdown_Bool, false);
	vr::VRProperties()->SetBoolProperty(container, vr::Prop_CanUnifyCoordinateSystemWithHmd_Bool, true);
	vr::VRProperties()->SetBoolProperty(container, vr::Prop_ContainsProximitySensor_Bool, false);
	vr::VRProperties()->SetBoolProperty(container, vr::Prop_DeviceProvidesBatteryStatus_Bool, false); //TODO implement and then set to true
	vr::VRProperties()->SetBoolProperty(container, vr::Prop_DeviceCanPowerOff_Bool, false);
	//VRProperties()->SetInt32Property(container, Prop_DeviceClass_Int32, TrackedDeviceClass_HMD);
	vr::VRProperties()->SetBoolProperty(container, vr::Prop_HasCamera_Bool, false);
	vr::VRProperties()->SetStringProperty(container, vr::Prop_DriverVersion_String, (std::to_string(PVR_SERVER_VERSION >> 24) + "." + std::to_string((PVR_SERVER_VERSION >> 16) % 0x100)).c_str());
	vr::VRProperties()->SetBoolProperty(container, vr::Prop_Firmware_ForceUpdateRequired_Bool, false); //TODO implement
	//VRProperties()->SetBoolProperty(container, Prop_ViveSystemButtonFixRequired_Bool, false); // ??
	vr::VRProperties()->SetBoolProperty(container, vr::Prop_ReportsTimeSinceVSync_Bool, false);
	vr::VRProperties()->SetUint64Property(container, vr::Prop_CurrentUniverseId_Uint64, 0x808682); // <= P+V+R ascii
	vr::VRProperties()->SetBoolProperty(container, vr::Prop_DisplayAllowNightMode_Bool, true); // ??
	// -------------------------------------------------------------------------------------------------
	vr::VRProperties()->SetFloatProperty(container, vr::Prop_DisplayFrequency_Float, (float)display_configuration_.fps);
	// -------------------------------------------------------------------------------------------------

	// avoid "not fullscreen" warnings from vrmonitor
	vr::VRProperties()->SetBoolProperty( container, vr::Prop_IsOnDesktop_Bool, false );

	vr::VRProperties()->SetBoolProperty(container, vr::Prop_DisplayDebugMode_Bool, false);

	// Now let's set up our inputs
	// This tells the UI what to show the user for bindings for this controller,
	// As well as what default bindings should be for legacy apps.
	// Note, we can use the wildcard {<driver_name>} to match the root folder location
	// of our driver.
	vr::VRProperties()->SetStringProperty( container, vr::Prop_InputProfilePath_String, "{simplehmd}/input/mysimplehmd_profile.json" );

	// Let's set up handles for all of our components.
	// Even though these are also defined in our input profile,
	// We need to get handles to them to update the inputs.
	vr::VRDriverInput()->CreateBooleanComponent( container, "/input/system/touch", &my_input_handles_[ MyComponent_system_touch ] );
	vr::VRDriverInput()->CreateBooleanComponent( container, "/input/system/click", &my_input_handles_[ MyComponent_system_click ] );

	// We've activated everything successfully!
	// Let's tell SteamVR that by saying we don't have any errors.
	return vr::VRInitError_None;
}

//-----------------------------------------------------------------------------
// Purpose: This is called by vrserver when the device should deactivate.
// This is typically at the end of a session
// The device should free any resources it has allocated here.
//-----------------------------------------------------------------------------
void MyHMDControllerDeviceDriver::Deactivate()
{
	// Let's join our pose thread that's running
	// by first checking then setting is_active_ to false to break out
	// of the while loop, if it's running, then call .join() on the thread
	//if ( is_active_.exchange( false ) ) {
	//}

	// unassign our controller index (we don't want to be calling vrserver anymore after Deactivate() has been called
	device_index_ = vr::k_unTrackedDeviceIndexInvalid;
}

//-----------------------------------------------------------------------------
// Purpose: If you're an HMD, this is where you would return an implementation
// of vr::IVRDisplayComponent, vr::IVRVirtualDisplay or vr::IVRDirectModeComponent.
//-----------------------------------------------------------------------------
void *MyHMDControllerDeviceDriver::GetComponent( const char *pchComponentNameAndVersion )
{
	if (!_stricmp( pchComponentNameAndVersion, vr::IVRDisplayComponent_Version ))
	{
		return static_cast<vr::IVRDisplayComponent*>(my_display_component_.get());
	} 
	else if (!_stricmp(pchComponentNameAndVersion, vr::IVRVirtualDisplay_Version))
	{
		return static_cast<vr::IVRVirtualDisplay*>(my_display_component_.get());
	}

	return nullptr;
}

//-----------------------------------------------------------------------------
// Purpose: This is called by vrserver when a debug request has been made from an application to the driver.
// What is in the response and request is up to the application and driver to figure out themselves.
//-----------------------------------------------------------------------------
void MyHMDControllerDeviceDriver::DebugRequest( const char *pchRequest, char *pchResponseBuffer, uint32_t unResponseBufferSize )
{
	if ( unResponseBufferSize >= 1 )
		pchResponseBuffer[ 0 ] = 0;
}

//-----------------------------------------------------------------------------
// Purpose: This is never called by vrserver in recent OpenVR versions,
// but is useful for giving data to vr::VRServerDriverHost::TrackedDevicePoseUpdated.
//-----------------------------------------------------------------------------
vr::DriverPose_t MyHMDControllerDeviceDriver::GetPose()
{
	// Let's retrieve the Hmd pose to base our controller pose off.

	// First, initialize the struct that we'll be submitting to the runtime to tell it we've updated our pose.
	vr::DriverPose_t pose = { 0 };

	// These need to be set to be valid quaternions. The device won't appear otherwise.
	pose.qWorldFromDriverRotation.w = 1.f;
	pose.qDriverFromHeadRotation.w = 1.f;
	pose.qRotation.w = 1.f;

	pose.vecPosition[0] = 0.0f;
	pose.vecPosition[1] = sin(frame_number_ * 0.0025) * 0.01f + 1.0f; // slowly move the hmd up and down.
	pose.vecPosition[2] = 0.0f;

	// The pose we provided is valid.
	// This should be set is
	pose.poseIsValid = true;

	// Our device is always connected.
	// In reality with physical devices, when they get disconnected,
	// set this to false and icons in SteamVR will be updated to show the device is disconnected
	pose.deviceIsConnected = true;

	// The state of our tracking. For our virtual device, it's always going to be ok,
	// but this can get set differently to inform the runtime about the state of the device's tracking
	// and update the icons to inform the user accordingly.
	pose.result = vr::TrackingResult_Running_OK;

	// For HMDs we want to apply rotation/motion prediction
	pose.shouldApplyHeadModel = true;

	return pose;
}

//-----------------------------------------------------------------------------
// Purpose: This is called by vrserver when the device should enter standby mode.
// The device should be put into whatever low power mode it has.
// We don't really have anything to do here, so let's just log something.
//-----------------------------------------------------------------------------
void MyHMDControllerDeviceDriver::EnterStandby()
{
	DriverLog( "HMD has been put into standby." );
}

//-----------------------------------------------------------------------------
// Purpose: This is called by our IServerTrackedDeviceProvider when its RunFrame() method gets called.
// It's not part of the ITrackedDeviceServerDriver interface, we created it ourselves.
//-----------------------------------------------------------------------------
void MyHMDControllerDeviceDriver::MyRunFrame()
{
	vr::VRServerDriverHost()->TrackedDevicePoseUpdated(device_index_, GetPose(), sizeof(vr::DriverPose_t));

	frame_number_++;

	// update our inputs here
}


//-----------------------------------------------------------------------------
// Purpose: This is called by our IServerTrackedDeviceProvider when it pops an event off the event queue.
// It's not part of the ITrackedDeviceServerDriver interface, we created it ourselves.
//-----------------------------------------------------------------------------
void MyHMDControllerDeviceDriver::MyProcessEvent( const vr::VREvent_t &vrevent )
{
}


//-----------------------------------------------------------------------------
// Purpose: Our IServerTrackedDeviceProvider needs our serial number to add us to vrserver.
// It's not part of the ITrackedDeviceServerDriver interface, we created it ourselves.
//-----------------------------------------------------------------------------
const std::string &MyHMDControllerDeviceDriver::MyGetSerialNumber()
{
	return my_hmd_serial_number_;
}
