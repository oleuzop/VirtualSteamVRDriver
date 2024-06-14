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

## Installation and Virtual headset configuration

1. Steam & SteamVR must be selected
2. Open VS solution
3. Compile (Release preferred)
4. Go to project folder and execute ```install_driver_Release.bat``` (Debug version if compiled debug)
5. Inside ```C:\Program Files (x86)\Steam\steamapps\common\SteamVR\drivers\simplehmd\resources\settings\default.vrsettings``` it's possible to find which headset and resolution is chosen.
```
	"simplehmd_display": {
	    "headset_type": "QUEST3",         <== QUEST3/PICO4/PIMAX_CRYSTAL/WMR_EMULATOR
	    "quality_type": "POTATO",         <== POTATO/LOW/MEDIUM/HIGH/ULTRA/GODLIKE
	    "resolution_factor": 0.666666667  <== Resolution factor multiplyier (1.0 is no change)
	}
```

## Usage

1. Open SteamVR without any headset connected, then turn on "Display VR view" in SteamVR

![DisplayVrView](./static/DisplayVrView.png?raw=true)

2. You should see something as this:

![SteamVRView](./static/steamVrView.png?raw=true)

3. To look around use **Left Control + Mouse movement**

4. To move head position use **Left Control + Mouse Right Button + Mouse movement**

5. Launch your game with OpenXR or SteamVR selected and enjoy!

6. You can turn off Steam overlay from the hamburger button.

## License:
MIT -> https://en.wikipedia.org/wiki/MIT_License
Use at your own risk!! 