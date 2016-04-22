#Computing For Animation 1 Assignment
This is the ray tracer I wrote for the CA1 assignment

##Features:
- Parsing Scene files using the boost spirit library
- Blinn shading
- Ray traced reflections and refractions
- Multi threading
- Anti aliasing using random samples
- Supports rendering of meshes in a .obj format
- Procedural mesh generation for spheres and planes
- Reads texture files for diffuse colours

example renders can be found in myRT/saves/

example scenes can be found in myRT/scenes/

#Usage
##Running the program
Clone the git repository:
```
$git clone git@github.com:NCCA/quentinjcm-CA1.git
```
Move move to the downloaded file:
```
$cd quentinjcm-CA1/FinalSubmission/myRT
```
Build the program:
```
$qmake
$make
```
To run the ray tracer, simply run the binary with:
```
$./myRT
```
This will open a UI where you can set general render settings to do with the camera, lighting and multi threading. Here you also specify a scene file to render. Some example scenes are included with the code in the scenes/ directory.

Once the Scene file has been chosen, the Load Scene button can be pressed. This will run the parser on the specified scene file and build the scene

Once the scene is built, the Render button can be pressed and this will pass the constructed scene, along with the current render settings, to a renderer to render the scene.

When the scene is rendered, the final image will appear in an sdl window. 's' can be pressed to save the image as a .bmp to the saves/ directory.

##Scene file syntax
Below is a full descriptition of the scene syntax that the parser understands:
```
# <- deontes a comment

#transformation types set and reset transformation from world coordinates
#TRANSLATE: <x> <y> <z>
#ROTATE: <x> <y> <z>

#creating geometry
#sphere and plane use procedurally generated triangle meshes with uvs and texture coordinates
#PLANE: <w> <h>
#SPHERE: <sd> <r>

#obj meshes can also be imported, make sure that meshes are triangulated before importing
#OBJ <path/to/file.obj>

#setting materials
#any geometry specified will have the last specified material attached to it, with a default material being used if nothing
#MATERIAL: <r> <g> <b> <smoothness> <ior> <isTransparent> <isReflective> (<textureFile>)

#adding lights
#only supports point lights so far
#positions are specified in world space
#LIGHT: <x> <y> <z> <r> <g> <b> <intensity>
```
