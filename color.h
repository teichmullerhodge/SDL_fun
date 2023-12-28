typedef unsigned int uint;
typedef unsigned char uchar;


typedef struct {

    uchar R;
    uchar G;
    uchar B;
    uchar A;
    uchar RGB[3];

} Color;



void randomColor(Color *color){

        color->R = rand() % 255;
        color->G = rand() % 255;
        color->B= rand() % 255;
        color->A = rand() % 255;

}


void setRGBColor(Color *color, uint R_VALUE, uint G_VALUE, uint B_VALUE, uint A_VALUE){


    color->R = R_VALUE;
    color->G = G_VALUE;
    color->B = B_VALUE;
    color->A = A_VALUE;

    color->RGB[0] = color->R;
    color->RGB[1] = color->G;
    color->RGB[2] = color->B;
    color->RGB[3] = color->A;

}