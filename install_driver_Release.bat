xcopy "%cd%\Build\x64\Release\driver_simplehmd.dll" "%cd%\driver\simplehmd\bin\win64\driver_simplehmd.dll" /Y

rd /s /q "C:\Program Files (x86)\Steam\steamapps\common\SteamVR\drivers\simplehmd"

mkdir "C:\Program Files (x86)\Steam\steamapps\common\SteamVR\drivers\simplehmd"

xcopy "%cd%\driver\simplehmd\" "C:\Program Files (x86)\Steam\steamapps\common\SteamVR\drivers\simplehmd\" /E/H/Y
