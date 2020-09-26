# 3D-simulation-raycasting
Simulation of an interactive 3D environment using raycasting techniques

Requirements:

1. Linux OS (Tested in Ubuntu and Xubuntu).
2. [MinilibX](https://github.com/42Paris/minilibx-linux), which is an X-Window (X11-R6) programming API used in this project to create a window, create an image with addressable pixels to be represented in the window, convert the texture XPM files to images with addressable pixels that can be represented in the window, obtain the user's screen resolution and track the user's keyboard pressings.  

Usage instructions:

1. Open the computer terminal and execute the command `make` inside the project folder to compile the program.
2. Execute the command `./cub3D map.cub` to run the program.
3. Move through the 3D environment by pressing the keys **W, A, S** and **D**.
4. Rotate the view by pressing the right and left arrow keys.
5. Exit the program by pressing the `Esc` key, or by clicking the cross button located at the upper left or right (depending on the system) of the program window.
6. Configure **window resolution, wall textures, sprite (element different than walls, like a character or an object) texture, ceiling color, floor color** and **the map that will be represented** by modifying different values of the **map.cub** file.

Map configuration:

- Map legend:
	- 1 = WALL
	- 0 = ACCESIBLE SPACE
	- 2 = SPRITE
	- N = START POSITION of the player, looking at NORTH DIRECTION.
	- S = START POSITION of the player, looking at SOUTH DIRECTION.
	- W = START POSITION of the player, looking at WEST DIRECTION.
	- E = START POSITION of the player, looking at EAST DIRECTION.

- Valid map conditions:
	1. All ACCESIBLE SPACE must be surrounded by WALLs.
	2. A START POSITION is needed, and no more than one can be set.
