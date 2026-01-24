## CoD1.1 client mod
Based on [vCoDMods' backup](https://vcodmods.com/client/iw1x-client-source)

**Focused on improving aiming and eyesight**

*-r* as my name meaning it's intended to provide only the features I'm currently interested about

Some features are:
- ADS sensitivity scale
- FOV scale
- Raw input
- Alt+Tab support
- `lookback` command
---
---
## Build and Run

Using Windows
- Install git: https://git-scm.com/ (leave default options)
- Install Visual Studio Community: https://visualstudio.microsoft.com/vs/community/

In Visual Studio Installer > Individual components, install these:

<img width="377" height="145" alt="vs components" src="https://github.com/user-attachments/assets/6e4336a1-e552-41ca-83ee-fb90e4b526af" />

(maybe Windows 10 SDK instead if you are on Win10)

Open a terminal on your desktop, then:

- `git clone https://github.com/cod1raph/iw1x-client-r.git`
- `cd iw1x-client-r`
- `git submodule update --init --recursive`
- Close terminal, open `generate.bat`
- In `build` folder, open `iw1x-client-r.sln`
- Ignore setup assistant
- Select the `Release` config on top (click Debug next to Win32)
- On top: Build > Build Solution
- Close VS, go to `iw1x-client-r\build\bin\Release`
- Copy `iw1x-r` app in CoD folder, next to `CoDMP`
- Run `iw1x-r`

**Menu key: Alt+Esc**

---
---
## References
- [Killtube](https://killtube.org/)
- The [reverse engineering Discord server](https://discord.com/invite/weKN5wb)
- [codextended-client](https://github.com/xtnded/codextended-client)
- [CoD4x_Client_pub](https://github.com/callofduty4x/CoD4x_Client_pub)
- [CoDPlusPlus](https://github.com/kartjom/CoDPlusPlus)
- [AlterWare](https://alterware.dev/) & [Aurora](https://auroramod.dev/)
- [Intro to x86 Assembly Language](https://www.youtube.com/playlist?list=PLmxT2pVYo5LB5EzTPZGfFN0c2GDiSXgQe)
- [RTCW-MP](https://github.com/id-Software/RTCW-MP/)
- [Ghidra](https://github.com/NationalSecurityAgency/ghidra) & [IDA Free](https://hex-rays.com/ida-free)
- [ChatGPT](https://chatgpt.com/)
