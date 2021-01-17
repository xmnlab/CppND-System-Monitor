# CppND-System-Monitor

Starter code for System Monitor Project in the Object Oriented Programming Course of the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

Follow along with the classroom lesson to complete the project!

![System Monitor](images/monitor.png)

## Udacity Linux Workspace
[Udacity](https://www.udacity.com/) provides a browser-based Linux [Workspace](https://engineering.udacity.com/creating-a-gpu-enhanced-virtual-desktop-for-udacity-497bdd91a505) for students.

You are welcome to develop this project on your local machine, and you are not required to use the Udacity Workspace. However, the Workspace provides a convenient and consistent Linux development environment we encourage you to try.

## ncurses
[ncurses](https://www.gnu.org/software/ncurses/) is a library that facilitates text-based graphical output in the terminal. This project relies on ncurses for display output.

Within the Udacity Workspace, `.student_bashrc` automatically installs ncurses every time you launch the Workspace.

If you are not using the Workspace, install ncurses within your own Linux environment: `sudo apt install libncurses5-dev libncursesw5-dev`

## Make
This project uses [Make](https://www.gnu.org/software/make/). The Makefile has four main targets:
* `build` compiles the source code and generates an executable
* `format` applies [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) to style the source code
* `debug` compiles the source code and generates an executable, including debugging symbols
* `clean` deletes the `build/` directory, including all of the build artifacts

Check the Makefile to see the other targets available.

## Instructions

1. All the dependencies can be installed using conda. If you don't have miniconda installed, you can download it
    from https://docs.conda.io/en/latest/miniconda.html.

1. Install all the dependencies running the command (at the root of the project):
   `conda env create -n nd213-system-monitor --file environment.yaml  --force`

1. Now, in each new session that you want to build and run the monitor app, you need to activate the conda environment first:
   `conda activate nd213-system-monitor`

1. Clone the project repository: `git clone https://github.com/udacity/CppND-System-Monitor-Project-Updated.git`

1. Build the project: `make build`

1. Run the resulting executable: `./build/monitor`
![Starting System Monitor](images/starting_monitor.png)

1. Follow along with the lesson.

1. Implement the `System`, `Process`, and `Processor` classes, as well as functions within the `LinuxParser` namespace.

1. Submit!

## Acknowledges

Clang format file copied from https://github.com/pytorch/pytorch/blob/master/.clang-format
