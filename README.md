# OCR 404

### Projet S3 EPITA Promo 2021

## The structure of the project

| Parts         | State        | Possible upgrades ?  |
| ------------- | ------------ | -------------------- |
| MySDL         | Finished     | NO                   |
| UI            | Finished     | YES (priority 4)     |
| Preprocessing | Finished     | YES (priority 3)     |
| Segmentation  | Finished     | YES (priority 1)     |
| Neural Net    | Finished     | YES (priority 2)     |
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
/Size/ x
/Layers size/ {x,x,x,}
/Weights/
x.x
...
..
.
/Bias/
x.x
/Weights/
x.x

etc...
```
The nodes are defined by their coordinates in the Neural Network matrix.

### NN Training
This section explains how to train your NN
go to neuralnet/trainning.c
Choose the number of iterations (NUMBER_ITER)
Choose your learning rate (LEARNING_RATE)
Choose the name of your save file (NAME_OF_SAVE_FILE)
make and run ./training
Approximative iter / time  : 7500 / min
```C
int main(){
    size_t layers[3] = {256,128,66};
    struct NN *MyNet = init_NN(layers,3);
    OCR_NN(MyNet,NUMBER_ITER,LEARNING_RATE);
    save_NN(MyNet,"NN_savefiles/NAME_OF_SAVE_FILE");
}
```

#### How To Test your NN
choose your save file in main.c
make and run ./main
when done run: cat Text.txt
Take a screenchot and send it to OCR404
try once with the file data.png and once with img.png

```C
void OCR(struct letter **l, int nb_letters)
{
  FILE *fp = fopen("Text.txt","w");
  double resul_mat [16*16];
  struct NN *mynet = load_NN("neuralnet/NN_savefiles/NAME_OF_SAVE_FILE");
  for (int i = 0; i < nb_letters; i++)
  {
    resizePixels(l[i]->mat, resul_mat, l[i]->width, l[i]->height, 16, 16);
    double *output = feedforward(mynet, resul_mat);
    char tmp = get_char(66, output);
    fprintf(fp,"%c",tmp);
    if (l[i]->space_after)
      fprintf(fp,"%c",' ');
    if (l[i]->new_line)
      fprintf(fp,"%c",'\n');
  }
  fclose(fp);
}
```
