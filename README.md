## C wrapper of the Basler Pylon C++ SDK, developed to be used in Unity
- The .NET SDK from Basler is not compatible with Unity, so this C wrapper of the Basler Pylon C++ SDK has been made to be compatible with Unity
- You can directly record videos from multiple Basler cameras simultaneously
- All video recording is done in a dedicated thread per camera, so the main thread is never blocked
- Developped and Tested with ***Visual Studio 2019 (v142)*** on Windows 10, with 2x [Basler acA1920-155uc](https://www.baslerweb.com/en/shop/aca1920-155uc/)
- This wrapper is used in the [BaslerPylonUnity](https://github.com/ebadier/BaslerPylonUnity) project

## Getting Started
#### 1. Plug your Basler cameras on your computer, and configure them using the [PylonViewer software](https://www.baslerweb.com/en/software/pylon/pylon-viewer/)
#### 2. Close the [PylonViewer software](https://www.baslerweb.com/en/software/pylon/pylon-viewer/), or at least close the camera devices inside it, because only one program can access the cameras at a time
#### 3. Build the Visual studio solution and run the program BaslerPylonWrapperTest

## Requirements
#### 1. Install [Pylon Software Suite for Windows](https://www2.baslerweb.com/en/downloads/software-downloads/software-pylon-7-5-0-windows/)
#### 2. Install [pylon Supplementary Package for MPEG-4 Windows](https://www2.baslerweb.com/en/downloads/software-downloads/pylon-supplementary-package-for-mpeg4-1-0-2-windows/)
