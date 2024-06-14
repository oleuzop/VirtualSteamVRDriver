# Virtual SteamVR driver

Virtual VR driver to develop easily without the need for a physical headset

![FalconBMS screenshot](./static/screenshot.png?raw=true)

## Prerequisites

- Steam & SteamVR installed in the computer
- If using OpenXR then SteamVR must be set as OpenXR default runtime

## Installation

1. Clone git repository

```
git clone https://github.com/oleuzop/VirtualSteamVRDriver.git
```

2. Init git repositories (to download openvr dependency)

```
git submodule update --init --recursive
```

## Virtual headset configuration

1. Open VS solution
2. Compile (Release preferred)
3. Go to project folder and execute ```install_driver_Release.bat``` (Debug version if compiled debug)
4. Inside ```C:\Program Files (x86)\Steam\steamapps\common\SteamVR\drivers\simplehmd\resources\settings\default.vrsettings``` it's possible to find which headset and resolution is chosen.
```
	"simplehmd_display": {
	    "headset_type": "QUEST3",         <== QUEST3/PICO4/PIMAX_CRYSTAL/WMR_EMULATOR
	    "quality_type": "POTATO",         <== POTATO/LOW/MEDIUM/HIGH/ULTRA/GODLIKE
	    "resolution_factor": 0.666666667  <== Resolution factor multiplyier (1.0 is no change)
	}
```

5. Open SteamVR without any headset connected, then turn on "Display VR view" in SteamVR 
![DisplayVrView](./static/DisplayVrView.png?raw=true)

6. You should see something as this:
![SteamVRView](./static/steamVrView.png?raw=true)

7. To look around use **Left Control + Mouse movement**

8. To move head position use **Left Control + Mouse Right Button + Mouse movement**

## License:
MIT -> https://en.wikipedia.org/wiki/MIT_License
Use at your own risk!! 