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
### mysdl/
Contains basic functions for mysdl given in the practical on SDL
### ui/
Contains all the gtk+3 function for the ui
### preproc/
Contains functions for the preprocessing:
* Grayscale
* Otzu (black and white)
### segmentation/
Contains all the functions for segmentation and character recognition
### neuralnet/
Neural network

## Requirements to run the project

#### Install sdl
* sudo apt-get install sdl
* sudo apt-get install sdl_image

#### Install GTK
* sudo apt-get install libgtk2.0-dev
* sudo apt-get install libgtk3.0-dev
