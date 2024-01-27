# CLI Image Processing

CLI Image Processing is a command line image processing tool written in C. It provides functionalities to edit BMP images, save, insert, draw lines, rectangles, triangles, fill areas with color, and more, all from the command line.

## Features

- **Edit Images:** Open and edit images in BMP format.
- **Save Images:** Save the edited images back to BMP files.
- **Insert Images:** Insert one BMP image into another at a specified position.
- **Drawing:** Draw lines, rectangles, and triangles with customizable colors and line widths.
- **Fill:** Fill areas with color using a flood-fill algorithm.
- **Quit:** Safely exit the program, freeing up allocated resources.

## Installation

1. Clone the repository or download the source code.
2. Compile the code using the project's Makefile.

```bash
make build
```

## Usage

1. Launch the program from the command line by using the "run" rule of the Makefile.

```bash
make run
```

2. Follow the on-screen prompts to provide input as required by the chosen command.

- *edit*: Load a BMP image from your computer (you can add your pictures to the "images" directory)

```bash
edit images/your_image.bmp
```

- *save*: Save the currently edited image to a specified file.

```bash
save images/your_output.bmp
```

- *quit*: Exit the program, ensuring proper resource cleanup.

```bash
quit
```

- *insert*: Insert one BMP image into another at a specified position.

```bash
insert images/inserted_image.bmp y x
```

- *set*: Choose drawing color and width.

```bash
set draw_color R G B
set line_width x
```

- *draw*: Draw shapes on the image.

```bash
draw line y1 x1 y2 x2
draw rectangle y1 x1 width height
draw triangle y1 x1 y2 x2 y3 x3
```

- *fill*: Fill area of all pixels with the same color as the one selected

```bash
fill y x
```

## Example

Just for simplicity, you can use the already created "images" directory.

```bash
edit images/sample_image.bmp # load an image to the editor
set draw_color 0 255 0 # set color to green
set line_width 5 # set drawing width to 5 pixels
draw rectangle 50 50 100 200 # draw a green rectangle starting from (50, 50) of width 100 and height 200
save images/output_image.bmp # save the edited image
quit
```

Feel free to explore and experiment!


