## CoD1.1 client mod
Based on [vCoDMods' backup](https://vcodmods.com/client/iw1x-client-source)

**Focused on improving aiming and eyesight**

*-r* as my name meaning it's intended to provide only the features I'm currently interested about

Some features are:
- ADS sensitivity scale
- FOV scale
- Raw mouse input
- Alt+Tab support
- `lookback` command
- Prevent server forcing downloading
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
  - Supportive people with great CoD2 knowledge
- The [reverse engineering Discord server](https://discord.com/invite/weKN5wb)
  - Receiving help when struggling hooking functions
- [codextended-client](https://github.com/xtnded/codextended-client)
  - To start practicing modifying existing modifications
- [CoD4x_Client_pub](https://github.com/callofduty4x/CoD4x_Client_pub)
  - Helped to make the "ADS sensitivity scale" feature
- [CoDPlusPlus](https://github.com/kartjom/CoDPlusPlus)
  - Helped to add the menu and to get some neat inline ASM code
- [AlterWare](https://alterware.dev/) & [Aurora](https://auroramod.dev/)
  - Offer modern CoD mod projects, used as a base for iw1x
- [Intro to x86 Assembly Language](https://www.youtube.com/playlist?list=PLmxT2pVYo5LB5EzTPZGfFN0c2GDiSXgQe)
  - To understand the basics of x86 ASM
- [RTCW-MP](https://github.com/id-Software/RTCW-MP/)
  - The source that most closely resembles CoD1, helps a lot to find and figure out stuff
- [Ghidra](https://github.com/NationalSecurityAgency/ghidra) & [IDA Free](https://hex-rays.com/ida-free)
  - To decompile CoD files
- [ChatGPT](https://chatgpt.com/)
  - Helps to create and clean source code
