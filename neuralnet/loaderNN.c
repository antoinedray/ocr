#include"loaderNN.h"
#include <err.h>

void save_NN(struct NN *mynet, char * name)
{
    FILE * myfile;
    myfile = fopen(name,"w");
    fprintf(myfile, "%lu\n{",mynet->size);
    for(size_t i = 0; i < mynet->size;i++)
    {
        fprintf(myfile,"%lu",mynet->layersize[i]);
        if (i < mynet->size-1)
            fprintf(myfile,",");
    }
    fprintf(myfile,"}\n");
    for(size_t i = 0; i < mynet->size; i++)
    {
        for (size_t j = 0; j < mynet->layersize[i]; j++)
        {
            for(size_t k = 0; k < mynet->mat[i][j]->nb_inputs;k++)
            {
                fprintf(myfile,"%lf\n",mynet->mat[i][j]->weights[k]);
            }
            fprintf(myfile,"b\n%lf\n",mynet->mat[i][j]->bias);
        }
        fprintf(myfile,"$\n");
    }
    fclose(myfile);
}

/*
static size_t tosizet (char c, double pow)
{
    return (size_t)c * (size_t)pow;
}
*/

static double todouble(char *line, size_t len)
{
    double pow = 1;
    double res = 0;
    int lo = 0;
    for (size_t i = 0; i < len; i++)
    {
        if(line[i] == ',')
            lo = 1;
        else
        {
            if(!lo)
                res = res * 10 + (double)line[i];
            else
            {
                pow = pow /10;
                res += (double)line[i] * pow;
            }
        }
    }
    return res;
}

struct NN *load_NN(char *name)
{
	warn("1");
    FILE *file = fopen(name,"r");
    if (file == NULL) {
        printf("File does not exists");
        return NULL;
    }
    char line[100];
    size_t len = 0;
    size_t mynb = 0;
    double *myw = NULL;
    size_t lpos = 0;
    size_t posin = 0;
    int debug;
    //size_t linelen;
    debug =1;
    if(debug==1)
      debug=2;
	warn("2");
    debug = fscanf(file, "%s", line);
    mynb = (size_t)atoi(line);
	warn("3");
    debug = fscanf(file, "%s", line);
    size_t index = 0;
	warn("4");
    //size_t s = 0;
    size_t * layers = malloc(mynb * sizeof(size_t));
	warn("5");
    for (size_t i = 1; line[i] != '}';i++)
    {
        if (line[i] == ',')
        {
            layers[lpos] = posin;
            posin = 0;
            lpos += 1;
        }
        else
            posin = 10 * posin + (size_t)line[i];
    }
	warn("6");
    posin = 0;
    lpos = 0;
    struct NN *mynet = init_NN(layers, mynb);
	
    myw = calloc(mynet->layersize[lpos],sizeof(double));
    //handling the weights
    while(fscanf(file, "%s", line) != EOF)
    {
        if(line[0] == '$')
        {
            myw = calloc(mynet->layersize[lpos], sizeof(double));
            lpos += 1;
            posin = 0;
        }
        else if(line[0]=='b')
        {
            mynet->mat[lpos][posin]->weights = myw;
            debug = fscanf(file, "%s", line);
            mynet->mat[lpos][posin]->bias = todouble(line,len);
            posin += 1;
            index = 0;
        }
        else
        {
            myw[index] = todouble(line,len);
            index += 1;
        }
    }
    return mynet;
}
/*
    if (line[0] == "$")
    {
        mynet->mat
    }
    else
    {
        struct N **inp = malloc(sizeof(struct N*));
        struct N ***mymat = malloc(sizeof(inp) * mynet->size);
        struct N *myneu = malloc(sizeof(struct N));
        size_t posx = 0;
        size_t posy = 0;
        size_t i = 0;
                double pow = 1;
                int nex = 0;
                while(line[i] != "]" || line[i+1] == "[")
                {
                    if(line[i] == "]" || line[i] == "[")
                    {
                        nex = 1;
                    }
                    else
                    {
                        if (!nex)
                            posx = 10 * posx + (size_t)line[i];
                        else
                            posy = 10 * posy + (size_t)line[i];
                    }
                    i++;
                }
                i+=2;
                nex = 0;
                while(line[i] != "\n")
                {
                    if (line[i] == ".")
                    {
                        nex = 1;
                        pow = 1;
                    }
                    else
                    {

                    }
                }
            }
        }
    }






































=======


>>>>>>> 7658566c76a3c0b2224ad85d25efbbbaaafebbef
    while ((c = fgetc(file)) != EOF)
    {
        if (c=="\n"||c="{"||c=="}"||c=="["||c=="]"||c=="b"||c=="#")
        {
            prev = c;
            c = "";
        }
        else
        {
            if(prev=="#"||prev=="b")
            {
                if(sec==".")
                {
                    pow = pow/10;
                    w_b += pow * (double)c;
                }
                else
                {
                    pow = pow *10;
                    w_b = w_b *pow + (double)c;
                }
            }
        }
    }





    FILE * myfile;
    myfile = fopen(name,"r");
    char line = NULL
    struct NN *mynet = malloc(sizeof(struct NN));
    size_t mynet_size = 0;
    mynet_size = (size_t)fgetc(file);
    size_t s = 0;
    char c = "";
    struct
    for (int i = 0; i < 2; i++)
        fgetc(file);

    size_t * mynet_layers = malloc(mynet_size);

    for (size_t i =0; i < mynet_size; i++)
    {
        s = 0;
        c = "";
        while((c = fgetc(myfile) != "," && c != "]")
            s = 10 * s + (size_t)c;
        mynet_layers[i] = s;
    }
    fgetc(myfile);
    fgetc(myfile);


    for (size_t i = 0; i < mynet_size; i++)
    {
        size_t posx = 0;
        size_t posy = 0;
        double
        for (size_t j = 0; j < mynet_layers[i]; j++)
        {
            struct N *mynn = malloc(sizeof(struct N));
            s = 0;
            c = "";
            while((c = fgetc(myfile) != "]")
                s = 10 * s + (size_t)s;
            posx = s;
            s = 0;
            while((c = fgetc(myfile) != "]")
                s =
        }
    }
}

<<<<<<< HEAD
struct NN *load_NN_base(char *filename){
=======
struct NN *load_NN(char *filename){
>>>>>>> 5402d9839f12389c304bb8708d7c3f7ba615f973
    FILE *f = fopen(filename,"r");
    char *line = NULL;
    size_t len =0;
    size_t index = 0;
    int loc = 0;
    struct NN *MyNet = malloc(sizeof(struct NN));
    while(!feof(f)){
        getline(&line,&len,f);
        if (loc == 0){
            MyNet->size = atoi(line);
            loc +=1;
        }
        if (loc == 1){
            index = 1;
            for(size_t i = 0 ; line[i]!='\n';i++){
                if(line[i] == '|'){
                    index +=1;
                }
            }
        }
    }
    return MyNet;
<<<<<<< HEAD
}
=======
}
>>>>>>> 5402d9839f12389c304bb8708d7c3f7ba615f973
*/
