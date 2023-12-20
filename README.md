# **minRT**


## Installation and Usage:
Install the necessary packages for [MLX](https://github.com/codam-coding-college/MLX42#readme)

To create the executable:
```sh
make
```
To unpack the scene files:
```sh
make get_resources
```

To run the program:
```sh
./miniRT <scene> <resolution>
```

Features:
```
- Use WASD to move around
- Use the arrow keys to change the viewing direction
- Change the field of view using '[' and ']'
- Press 'C' to get the current camera postion and direction
- Press 'Z' or 'X' to change the exposure
- Press 'R' to reload the scene (camera stays in current position)
- Press 'P' to export the current view as a .bmp file
```

## Scene Description

Create a scene description file (e.g., `scene.rt`) to define the objects, lights, and camera in the scene. Refer to the provided examples for syntax and available options.

```plaintext
# Example Scene Description

  A  0.2          255,255,255                 # Ambient light
  C -50,0,20      0,0,1 70                    # Camera
  L -50,50,50     0.6           255,255,255   # Light
  
  sp 0,0,0 20     255,0,0                     # Sphere
  pl 0,0,0 0,1,0  255,255,255                 # Plane
  cy 0,0,20 0,0,1 10     5      255,255,0     # Cylinder
  
  tri 1.0,1.0,1.0  2.0,2.0,2.0   3.0,3.0,3.0  255,120,25  #Triangle

# This project is also able to parse triangulated OBJ files.
# To use them simply specify the file containing a mesh:

   objfile *.obj

# And then use the mesh at a specified loation, rotation and size:

  usemesh mesh	0,3.85,0  0,0,-1  0,-1,0	2

```

## Screenshots:

![Objects_1_8K](https://github.com/rvan-mee/miniRT/assets/92876462/109c0e45-463b-401c-a53f-2d19b889b584)



![Second_dragon_8K](https://github.com/rvan-mee/miniRT/assets/92876462/e726871f-5efc-4e0a-b056-e5cc8e0a20c1)



![Objects_2_8K](https://github.com/rvan-mee/miniRT/assets/92876462/508917e2-dd3b-4557-8c22-e9bd10d74110)



![Glass_sphere_8K](https://github.com/rvan-mee/miniRT/assets/92876462/5e711478-0206-4932-9884-ec2d0c0a0316)

