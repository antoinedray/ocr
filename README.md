# OCR 404

### Projet S3 EPITA Promo 2021

#### Presentation report
Report must be 50 pages long. [Shared Latex](https://www.sharelatex.com/7144692721ntkmzppcsmnk)

## The structure of the project

| Parts         | State        | Possible upgrades ?  |
| ------------- |:------------:| --------------------:|
| MySDL         | Finished     | NO                   |
| UI            | Finished     | YES (priority 4)     |
| Preprocessing | Finished     | YES (priority 3)     |
| Segmentation  | Not finished | YES (priority 1)     |
| Neural Net    | Not finished | YES (priority 2)     |
| Data Base     | Finished     | NO                   |

### MySDL
Contains basic functions for mysdl given in the practical on SDL

### UI
Contains all the gtk+3 function for the ui

### Preproc
Contains functions for the preprocessing:
* Grayscale
* Otzu (black and white)

### Segmentation
Contains all the functions for segmentation and character recognition

### Neuralnet
The Neural Network has the following struct : It is a matrix of Nodes(see below).
A node is constituted of a set of inputs (previous layer) and a set of weights(vertices connecting nodes between them).
The neural net is saved in the following format (txt file):
```
/Node/
0.0
/Weights/
x.x
...
..
.
/Bias/
x.x
/Node/
0.1
/Weights/
x.x

etc...
```
The nodes are defined by their coordinates in the Neural Network matrix.

### Data Base
Generate the database of images for training.
### How to use the database generator
To use the generator, run `python3 gen.py <command>`
There are 3 commands:
* `-h` for help
* `-gen` to generate the database
* `-clean` to clean the database

To add more fonts, just add .ttf fonts in the fonts folder
