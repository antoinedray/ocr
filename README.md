# OCR 404
### Projet S3 EPITA Promo 2021

### Responsabilities Repartition for final presentation
* Celian: Character recongnition
* Stan: Neural Network
* Antoine: UIs & Image Preprocessing
* Thibaut: Neural Network

## PLEASE NOTE !
UIs and image processing are done with GTK / SDL.

### Presentation report
Report must be 25 pages long. [Overleaf Link](https://www.overleaf.com/11590034ngnvhzczpsmr)

**No presentation of the subject**

## The structure of the project
### mysdl/ [COMPLETE]
Contains basic functions for mysdl given in the practical on SDL
### ui/ [COMPLETE]
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
