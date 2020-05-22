# Points-Picker

Takes a Geoportail (https://www.geoportail.gouv.fr/) kml file and creates a matrix of correspondences between world and image points from a camera taken picture.

Provides an input matrix for https://github.com/rodolfoap/camera2world-h

## Build

```
mkdir -p build && pushd $_;
cmake ..
make
popd
```

## Define world points on Geoportail.gouv.fr

Visit https://www.geoportail.gouv.fr/ and generate a `.kml` file by selecting some points on the map and exporting the result (e.g. `placewilson/placewilson.kml`). Then:

```
./parsekml-geoportail.py placewilson/placewilson.kml > placewilson/placewilson.points

cat placewilson/placewilson.points
	43.605450023335436 1.4486315846443174 Fnac
	43.605024679081026 1.4480119943618774 c1
	43.6047916124607   1.448022723197937  c2
	43.60437306138812  1.4474125206470487 c3
	43.60436335019179  1.4472770690917967 c4
	43.60447017326533  1.4469015598297115 c5
	43.604535238135355 1.4468050003051756 c6
	43.60482414473066  1.44669771194458   c7
	43.60531940995173  1.44732266664505   c8
	43.60469013108758  1.448545753955841  pr
	43.604660997647386 1.4485940337181094 pl
```
You have just generated a usable format for the points-picker.

## Find corresponding image points

Now, select the equivalent points on the image (check the window title, the required point is shown).

```
./ppicker
Usage: ./ppicker [IMAGE_FILE POINTS_FILE MUSTACHE_TEMPLATE]

./ppicker placewilson/placewilson.jpg placewilson/placewilson.points points-matrix.tpl
Select point: Fnac
Select point: c1
Select point: c2
Select point: c3
Select point: c4
Select point: c5
Select point: c6
Select point: c7
Select point: c8
Select point: pr
Select point: pl
[DONE] Push Q to end and generate matrix.

%YAML:1.0
---
image_points: !!opencv-matrix
  rows: 11
  cols: 1
  dt: "2f"
  data: [
    85.198120, 639.537354,
    382.377197, 443.686584,
    370.205994, 315.537292,
    644.057007, 145.074646,
    703.898560, 134.194031,
    894.579956, 181.343292,
    946.307373, 213.985077,
    1027.448486, 349.388062,
    753.597412, 581.507507,
    99.397766, 278.059692,
    77.083984, 261.134338]
world_points: !!opencv-matrix
  rows: 11
  cols: 1
  dt: "3f"
  data: [
    43.605450, 1.448632, 0.0, # Fnac
    43.605026, 1.448012, 0.0, # c1
    43.604790, 1.448023, 0.0, # c2
    43.604374, 1.447412, 0.0, # c3
    43.604362, 1.447277, 0.0, # c4
    43.604469, 1.446902, 0.0, # c5
    43.604534, 1.446805, 0.0, # c6
    43.604824, 1.446698, 0.0, # c7
    43.605320, 1.447323, 0.0, # c8
    43.604691, 1.448546, 0.0, # pr
    43.604660, 1.448594, 0.0] # pl
```
