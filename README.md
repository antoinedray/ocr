# OCR 404
### Projet S3 EPITA Promo 2021

### Responsabilities Repartition
* Celian: Presentation report (Writing skills)
* Stan: Presentation report (LaTeX skills) & Image Preprocessing
* Antoine: UIs & Image Preprocessing
* Thibaut: Neural network

## PLEASE NOTE !
UIs and image processing are done with GTK / SDL.

### Presentation report
Report must be 25 pages long. [Overleaf Link](https://www.overleaf.com/11590034ngnvhzczpsmr)

##### Report must be made of:
* Group
* The progress
* Researches
* Tools used
* Implementations

**No presentation of the subject**

## About what we've done so far
The structure of the program is:
* main.c : contains the main function and a function, run_convert which links gtk with sdl
* ui.c(.h) : contains all the function in gtk for the window where we can select the file we whant to convert
* pixel_operations.c(.h) : contains all the sdl functions for the preprocessing

## Requirements to run the project

#### Install sdl
* sudo apt-get install sdl
* sudo apt-get install sdl_image

#### Install GTK
* sudo apt-get install libgtk2.0-dev
* sudo apt-get install libgtk3.0-dev