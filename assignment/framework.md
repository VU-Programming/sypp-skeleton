# Installation

You can do this course on Windows, macOS (including M1) and Linux (including Chromebook). You do *not* need to install a virtual machine. 

For this course you need:
* A source-code editor such as [VSCode](https://code.visualstudio.com/). You are allowed to use any editor, but we recommend VSCode.
* A UNIX-like environment with the C compiler Clang and Make. On Linux and macOS this environment is available by default, you just need to install Clang and Make. On Windows, this environment is supplied by the Windows Subsystem for Linux (WSL).

## A note on git

The instructions below use `git` to clone the CoPP framework. The default instructions will allow you to use `git` locally, but do not allow to store your project at github. If you want to store your repository at github, do the following (*do not fork the project* as this is public by default) :
* Go to [https://github.com/VU-Programming/sypp-skeleton](https://github.com/VU-Programming/sypp-skeleton) and press the green "Use this template" button. Make a **private** new repository. Do not make a public repository as posting solutions online is not allowed and is considered plagiarism by the exam board!
* Afterward, on the main page of your new repository, press the green code button to get a git address (for example git@github.com:student/copp.git) that you can use instead of https://github.com/VU-Programming/sypp-skeleton.git in the instructions below. 


## OS-specific instructions

Please follow the instructions for your operating system:
* [Linux](#linux)
* [Windows](#windows)
* [macOS](#macos)
* [Chromebook](#chromebook)


## Linux

1. Open a terminal
2. Install clang/Make/valgrind/git/lldb/zip: `sudo apt-get install libc6-dev clang make valgrind git lldb zip` 
3. Install VSCode: `sudo snap install code --classic` 
4. Install framework (this will create a directory sypp-skeleton in the current directory): `git clone https://github.com/VU-Programming/sypp-skeleton.git` (Use your own git address instead of this one if you created your own repository on github as described in the [Note on git](#a-note-on-git) above). 
5. In the terminal, navigate to the `sypp-skeleton` directory by typing `cd sypp-skeleton`
6. Type `code .` to open VSCode 
7. When prompted, install workspace recommended extensions (C++, IJVM and task-shell output). You can install git support if you want to, but you do not have to.
8. You can now code through VSCode, the next time you open VSCode it will automatically open the project.

(We are assuming an Ubuntu or another debian-based distribution here.)

Done? Continue to [How to use the skeleton and test your installation](skeleton.md)

## Windows

If you are using Microsoft Windows, the UNIX tools will not be available by default. We will  build and run the framework by making use of [Windows Subsystem for Linux](https://en.wikipedia.org/wiki/Windows_Subsystem_for_Linux).

* Download and Install VSCode [VSCode](https://code.visualstudio.com/).
* Install WSL integration for VSCode
    1. Open VSCode
    2. In the left side-pane select the icon with the four blocks, one of which is just being added.
    3. Install the **WSL** extension (by Microsoft)
    4. Close VSCode
* Install WSL (skip this if you have done this before)
    1. Run Command Prompt (or PowerShell) **as administrator**
    2. Type `wsl --install` to install WSL. Answer Yes when prompted.
    3. Once the WSL installation is complete, restart your computer
    4. Once the Ubuntu installation is complete, set up your UNIX account
    5. Optionally, install Windows Terminal from Microsoft Store
* Install C compiler and framework    
    1. Open a WSL terminal (either run the command prompt and then type `wsl` or use Windows terminal)
    1. Type `sudo apt update && sudo apt upgrade` to update Ubuntu
    2. Install Clang/Make: `sudo apt-get install libc6-dev clang make valgrind git lldb zip` 
    4. Install framework (this will create a directory sypp-skeleton in the current directory): `git clone https://github.com/VU-Programming/sypp-skeleton.git`  (Use your own git address instead of this one if you created your own repository on github as described in the [Note on git](#a-note-on-git) above)
    5. In the terminal, navigate to the `sypp-skeleton` directory by typing `cd sypp-skeleton`
    6. Type `code .` to open VSCode(connected to WSL)
    7. When prompted, install workspace recommended extensions (C++, IJVM and task-shell output). You can install git support if you want to, but you do not have to.
    8. You can now code through VSCode, the next time you open VSCode it will automatically open the project.
  
To access WSL files on Windows, navigate to **\\\wsl$** using File Explorer and, conversely, to access Windows files on WSL, navigate to **/mnt/c** using Ubuntu.

**Note:** if your machine is running Windows 10, you might encounter the following error: `WSL 2 requires an update to its kernel component.`. To fix this, download and install the [latest Linux kernel update package](https://docs.microsoft.com/en-us/windows/wsl/install-manual#step-4---download-the-linux-kernel-update-package).

Done? Continue to  [How to use the skeleton and test your installation](skeleton.md)

## macOS 




1. Install homebrew (which installs the developer tools) by following the steps at [the homebrew website](https://brew.sh/)
2. Download and install [VSCode](https://code.visualstudio.com/download)
3. Install the framework by doing `git clone https://github.com/VU-Programming/sypp-skeleton.git`  (Use your own git address instead of this one if you created your own repository on github as described in the [Note on git](#a-note-on-git) above)
4. In the terminal, navigate to the `sypp-skeleton` directory by typing `cd sypp-skeleton`
5. Type `code .` to open the project in VSCode 

Done? Continue to  [How to use the skeleton and test your installation](skeleton.md)


## Chromebook
1. Setup Linux on your chromebook as described [here](https://support.google.com/chromebook/answer/9145439?hl=en)
2. Setup VSCode as described [here](https://code.visualstudio.com/blogs/2020/12/03/chromebook-get-started)
3. Open a linux terminal and Install Clang/Make/valgrind/git/lldb/zip: `sudo apt-get install libc6-dev clang make valgrind git lldb zip`
4. Install framework (this will create a directory sypp-skeleton in the current directory): `git clone https://github.com/VU-Programming/sypp-skeleton.git`  (Use your own git address instead of this one if you created your own repository on github as described in the [Note on git](#a-note-on-git) above)
5. In the terminal, navigate to the `sypp-skeleton` directory by typing `cd sypp-skeleton`
6. Type `code .` to open VSCode 
7. When prompted, install workspace recommended extensions (C++, IJVM and task-shell output). You can install git support if you want to, but you do not have to.
8. You can now code through VSCode, the next time you open VSCode it will automatically open the project.

Done? Continue to  [How to use the skeleton and test your installation](skeleton.md)
