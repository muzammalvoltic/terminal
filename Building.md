# Building Windows Terminal on Windows 11

This guide provides instructions for setting up your environment and building the Windows Terminal project on Windows 11.

## Prerequisites

### 16. Enable Developer Mode

You must enable Developer Mode in the Windows Settings app to locally install and run Windows Terminal.

- Go to **Settings > System > For developers** and toggle **Developer Mode** to **On**.

### 17. Install Required Tools

You can set up your environment automatically or manually.

#### Option A: Automatic Setup (Recommended)

After cloning the repository, run the following command in PowerShell to install Visual Studio 2022 and all required components:

```powershell
winget configure .config\configuration.winget
```

#### Option B: Manual Setup

If you prefer to install components manually, ensure you have the following:

- **Windows 11 SDK**: Version 10.0.22621.0 or later.
- **Visual Studio 2022**: Community, Professional, or Enterprise editions.
- **PowerShell 7**: [Download here](https://github.com/PowerShell/PowerShell/releases/latest).
- **Workloads in VS Installer**:
  - Desktop Development with C++
  - Universal Windows Platform Development
  - **Individual Components**:
    - C++ (v143) Universal Windows Platform Tools
    - .NET Framework Targeting Pack (for test projects)

## Building the Code

### 1. Restore Git Submodules

The project uses submodules for dependencies. Run this first:

```shell
git submodule update --init --recursive
```

### 2. Build via PowerShell

The most convenient way to build is using the provided PowerShell module:

```powershell
Import-Module .\tools\OpenConsole.psm1
Set-MsBuildDevEnvironment
Invoke-OpenConsoleBuild
```

### 3. Build via Visual Studio

1. Open `OpenConsole.slnx` in Visual Studio 2022.
2. Select the **x64** or **x86** platform (Note: "Any CPU" is not supported).
3. To build and run the Terminal, set the **CascadiaPackage** project as the Startup Project.
4. Press `F5` to build and debug.

### 4. Build via GitHub Actions (Easy & Fast)

If you don't want to set up a local build environment, you can use the GitHub Actions workflow:

1. **Trigger the Build**: The workflow is configured to run on every push to the `main` branch.
2. **Monitor Progress**: Navigate to the **Actions** tab in your GitHub repository to see the build running.
3. **Download Artifacts**: Once the build completes, the compiled packages are available for download in the workflow run's artifacts section.

> [!TIP]
> Using GitHub Actions is often faster than local builds and ensures a consistent, clean environment.

> [!NOTE]
> **No Installation Conflicts**: These builds use a distinct "Dev" identity (`Microsoft.WindowsTerminal.Dev`). You can install and run them side-by-side with your official Windows Terminal installation without any conflicts.

## Troubleshooting

- **Build Failures?**: Ensure you have restored submodules (`git submodule update --init --recursive`).
- **Cannot launch .exe?**: You cannot launch `WindowsTerminal.exe` directly. You must deploy and run it via the `CascadiaPackage` project in Visual Studio.
- **Registration Errors?**: If you see `DEP0700: Registration of the app failed`, try closing any running instances of Terminal and clean the solution before rebuilding.

For more detailed information, see [doc/building.md](./doc/building.md).
