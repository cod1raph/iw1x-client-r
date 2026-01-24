# CoD 1.1 client mod
**Focused on improving aiming and eyesight**

<details>
<summary>History</summary>
I created iw1x-client in January 2025, then deleted the GitHub repo around April.  
  
Thanks to Gatsby, an up to date backup got uploaded on vCoDMods, this new repo is based on it.  
The added -r stands for my name, meaning this new version is not intended to provide all the features players would like, but only the ones I use.
</details>

Some features are:
- ADS sensitivity scale
- FOV scale
- Raw input
- Alt+Tab support
- `lookback` command

**Menu key: Alt+Esc**

---
---

## Build instructions

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

The `iw1x-r` app is the new file to run to use the mod, it must be put in the same folder where `CoDMP` is

---
---

### References
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
