# Toy Robot Challenge

A console application that simulates a toy robot moving on a square table top with a dimension of 5x5. There are no other obstructions on the table's surface, the robot is free to roam around the table, but must be prevented from falling to destruction. Any movement that would result in the robot falling from the table must be prevented, however further valid movement commands must still be allowed.

## Constraints
The toy robot must not fall off the table during movement. This also includes the initial placement of the toy robot. Any
move that would cause the robot to fall must be ignored.

## Supported Commands
* **PLACE X,Y,F**
  <br>Puts the toy robot on the table in position X, Y and facing NORTH, SOUTH, EAST or WEST. The origin (0,0) is the SOUTH WEST most corner of the table.
  <br>```PLACE must be invoked first before any other commands.```

* **MOVE**
  <br>Moves the toy robot one unit forward in the direction it is currently facing.

* **LEFT**
  <br>Rotates the robot 90 degrees to the left without changing the position of the
robot.

* **RIGHT**
  <br>Rotates the robot 90 degrees to the right without changing the position of the
robot.

* **REPORT**
  <br>Displays the current X, Y and F of the robot.
  <br>Example:
  ```0,0,NORTH```


## Prerequisites
1. Install GCC C++ compiler (g++).
    * For Windows, follow these steps:
      * Install Mingw-w64, see the **Installation** instructions on the <a href="https://www.msys2.org/">MSYS2</a>.
      * Install the Mingw-w64 toolchain by running the pacman command in a MSYS2 terminal.
        ```
        pacman -S --needed base-devel mingw-w64-x86_64-toolchain
        ```
      * Add the path to your Mingw-w64 bin folder to the Windows PATH environment variable.
    * For Linux/Ubuntu, execute the following commands:
      ```
      sudo apt-get update
      sudo apt-get install build-essential gdb
      ```
2. Install CMake 3.10 or later, see the <a href="https://cmake.org/install">CMake installation guide</a>.
3. Download GoogleTest <a href="https://github.com/google/googletest/archive/refs/tags/release-1.12.0.zip">v1.12.1</a>.
   <br>Extract the source files and copy it to lib/googletest/.

## Running the application and tests
1. Create build/ directory
2. Go to build/ directory
3. Build the application by running the following commands:
   * For Windows:
     ```
     cmake -G "MinGW Makefiles" ..
     mingw32-make.exe all
     ```
   * For Linux:
     ```
     cmake ..
     make
     ```
4. To run the application, go to build/src and run toy_robot.
   <br>The application will prompt for an input as shown below.

   Example:
    ```
    Please enter a command: PLACE 0,0,NORTH
    Please enter a command: MOVE
    Please enter a command: REPORT
    0,1,NORTH
    ```

    <br>```To exit the application, press ctrl+c.```

5. To run the tests, go to build/tests and run toy_robot_tests.
   <br>All test cases will automatically run via googletest.

   Example:
    ```
    [----------] 11 tests from IntegrationTest
    [ RUN      ] IntegrationTest.ConsecutivePlace
    [       OK ] IntegrationTest.ConsecutivePlace (6 ms)
    ...
    [ RUN      ] IntegrationTest.MoveNorthMaxY
    [       OK ] IntegrationTest.MoveNorthMaxY (5 ms)
    [----------] 11 tests from IntegrationTest (58 ms total)
    ```
