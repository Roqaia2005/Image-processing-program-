// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name:				ImgProcessing
// Last Modification Date:	18/10/2023
// Author1 and ID and Group:	Roqaia Hassan Hassan , ID:20220129,email:roqaiahassanahmed@gmail.com
// Author2 and ID and Group:	Fatima Atef Mahmoud,ID: 20190769,email:Atiff3368@gmail.com
// Author3 and ID and Group:	Tasnim Gomaa Anter ,ID:20220089,email:Tasneemgomaa126@gmail.com
// Teaching Assistant:		    Dr:Mohammed El-Ramly
// Purpose:creating an image processing program with some different filters
// the Whole color image processing program


#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE][RGB];
unsigned char coloredImage[SIZE][SIZE][RGB];
unsigned char coloredImage2[SIZE][SIZE][RGB];
unsigned char black_white_image[SIZE][SIZE]; //black and white img
unsigned char flippedColoredImg[SIZE][SIZE][RGB];
unsigned char coloredInvertedImg[SIZE][SIZE][RGB];

unsigned char croppedColoredImage[SIZE][SIZE][RGB];

unsigned char mergeColoredImg[SIZE][SIZE][RGB];
unsigned char shrinkcoloredImg[SIZE][SIZE][RGB];

unsigned char darkerandlightercolorImage[SIZE][SIZE][RGB];
unsigned char blurColoredImg[SIZE][SIZE][RGB];
unsigned char skewverticallycoloredImg[SIZE][SIZE][RGB];
//Functions Declaration//
void loadColoredImage ();
void loadImage ();
void BlackAndWhiteColored(); //filter 1
void invertColored() ;//filter 2
void flipColored();//filter 4
void Rotated_color();//filter 5
void enlargeColoerd_quarter();//filter 8
void detectColored();//filter 7
void mirrorColored();//filter a
void Shuffle_ColoredImage();//filter b
void cropColored();//filter d
void skew_Coloredimage();//filter e
void mergedColored() ;//filter 3
void shrinkColored();//filter 9
void blurColored();//filter c
void choose();//filter 6
void darkercolored();//filter 6
void lighterColored();//filter 6
void skewverticallyColored();//filter f
//*****functions to save images after processing
void saveImage ();

void saveBlackWhite ();

void saveFlippedColoredImage () ;

void saveInvertedColoredImg();

void saveCroppedColoredImg ();
void saveColoredImg ();
//**main program**//
int main()
{
    //***while loop make the user enter filter number he wants and 0 to exit***//
    while(true){
        cout<<"Please select a filter to apply or 0 to exit:\n";
        cout<<"1-Black & White Filter\n"
              "2-Invert Filter\n"
              "3-Merge Filter \n"
              "4-Flip Image\n"
              "5-Darken and Lighten Image \n"
              "6-Rotate Image\n"
              "7-Detect Image Edges \n"
              "8-Enlarge Image\n"
              "9-Shrink Image\n"
              "a-Mirror 1/2 Image\n"
              "b-Shuffle Image\n"
              "c-Blur Image\n"
              "d-Crop Image\n"
              "e-Skew Image Right  \n"
              "f-Skew Image Up  \n"
              "s- Save the image to a file\n"
              "0-Exit";
        char filter;
        cin>>filter;
        if(filter==0){
            break;
        }
        else{

            switch (filter) {

                case '0':
                    break;
                case '1': // filter 1 : Black & White Filter
                    loadColoredImage();
                    BlackAndWhiteColored();
                    saveBlackWhite();
                    showGSBMP(black_white_image);
                    break;
                case'2': // filter 2 : Invert Filter
                    loadColoredImage();
                    invertColored();
                    saveInvertedColoredImg();
                    showRGBBMP(coloredInvertedImg);
                    break;
                case '3':// filter to merge two color images together
                    loadColoredImage();
                    mergedColored();
                    saveColoredImg();
                    showRGBBMP(mergeColoredImg);
                    break;

                case '4': //filter 4 : Flip colored Image
                    loadColoredImage();
                    flipColored();
                    saveFlippedColoredImage();
                    showRGBBMP(flippedColoredImg);
                    break;
                case '5': //filter 6: Rotate colored Image()
                    loadImage ();
                    Rotated_color();
                    saveImage ();
                    showRGBBMP( image);
                case'6':// filter to make colored images reach 50% lighter or darker
                    loadColoredImage();
                    choose();
                    saveColoredImg();
                    showRGBBMP(darkerandlightercolorImage);
                    break;

                case '7': //filter 7: Detect colored Image
                    loadColoredImage();
                    detectColored();
                    saveColoredImg();
                    showRGBBMP(coloredImage);
                    break;
                case '8': //filter 8: enlarged colored Image()
                    loadImage ();
                    enlargeColoerd_quarter();
                    saveImage ();
                    showRGBBMP( image);
                case 'a': //filter a: mirror colored Image
                    loadColoredImage();
                    mirrorColored();
                    saveColoredImg();
                    showRGBBMP(coloredImage);
                    break;
                case 'b': //filter b: shuffle colored Image()
                    loadImage ();
                    Shuffle_ColoredImage();
                    saveImage ();
                    showRGBBMP( image);
                case'c':// filter to blur colored images
                    loadColoredImage();
                    blurColored();
                    saveColoredImg();
                    showRGBBMP(blurColoredImg);
                    break;

                case 'd': // filter d crop colored image
                    loadColoredImage();
                    cropColored();
                    saveCroppedColoredImg();
                    showRGBBMP(croppedColoredImage);
                    break;
                case 'e': //filter e:  skew colored Image horizontally()
                    loadImage ();
                    skew_Coloredimage();
                    saveImage ();
                    showRGBBMP( image);
                case 'f':
                    loadColoredImage();
                    skewverticallyColored();
                    saveColoredImg();
                    showRGBBMP(skewverticallycoloredImg);
                    break;
                default:
                    cout<<"Invalid filter\n";

            }

        }


    }

    return 0;
}

//*****************Functions Definitions*******************//
void loadImage () {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName, image);
}
//------------------------------------------------------

void saveImage () {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeRGBBMP(imageFileName, image);
}

//________________________________________
void loadColoredImage () { // function to load colored image we will make change on it
    char imageFileName[100];

    // Get  colored image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName, coloredImage);
}
//_________________________________________
//filter 1 convert colored image to black_white_image
void BlackAndWhiteColored() {

    //first convert colored image to grayscale image

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for(int k=0;k<RGB;k++) {

                int red = coloredImage[i][j][0];// first bit
                int green = coloredImage[i][j][1]; //second bit
                int blue = coloredImage[i][j][2]; //third bit
                int average = (red + green + blue) / 3;// average of each colored bit
                // Set RGB values to the average value
                coloredImage[i][j][0] = average;
                coloredImage[i][j][1] = average;
                coloredImage[i][j][2] = average;
            }

        }
    }
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            black_white_image[i][j]=coloredImage[i][j][0];//convert colored image to grayscale image

            if(black_white_image[i][j]>110) {
                black_white_image[i][j] = 255;
            }
            else{
                black_white_image[i][j]=0;
            }

        }


    }
}
//--------------------------------------------------------
void saveBlackWhite () { // function to save image after convert it to black_white_image
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");

    writeGSBMP(imageFileName,black_white_image);

}
//__________(filter 2 invert colored image)____________
void  invertColored() {
    for (int i = 0; i < SIZE; i++) {//nested loops to scan every pixel.
        for (int j = 0; j< SIZE; j++) {
            for(int k=0;k<RGB;k++)
                coloredInvertedImg[i][j][k] = 255 - coloredImage[i][j][k]; //subtract the maximum value of each pixel to get the inverse bit.

        }


    }
}
void saveInvertedColoredImg(){ //function to save inverted colored image
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");

    writeRGBBMP(imageFileName,coloredInvertedImg);

}
//____________________filter 3__________________________
// merge filter which take average of the two images i want to merge

void mergecolor(){
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            for(int k=0;k<RGB;k++){
                //we make nested loop that loop over every pixel

                mergeColoredImg[i][j][k] = (coloredImage[i][j][k]+coloredImage2[i][j][k])/2;//we make sumation betweem two images and divide it bu 2to make them blending
            }
        }
    }
}
//********************************//
// filter 4 flip colored image
void flipColored(){
    char mode ;
    cout<<"Flip (h)orizontally or (v)ertically ?";
    cin>>mode;
    if(mode=='H'|| mode=='h'){
        for(int i=0;i<SIZE;i++){
            for(int j=0;j<SIZE;j++){
                for(int k=0;k<RGB;k++){

                    flippedColoredImg[i][j][k]=coloredImage[SIZE-i][SIZE-j][k];
                }

            }
        }
    }
    else if(mode=='V'||mode=='v'){

        for(int i=0;i<SIZE;i++){
            for(int j=0;j<SIZE;j++){
                for(int k=0;k<RGB;k++){

                    flippedColoredImg[i][j][k]=coloredImage[i][SIZE-j][k];
                }

            }
        }

    }
    else{
        cout<<" Invalid mode";
    }

}

void saveFlippedColoredImage () { //function to save flipped colored  image
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");

    writeRGBBMP(imageFileName,flippedColoredImg);

}
//____________________________(filter 5 rotate color image)__________________________
void Rotated_color() {
    cout << "Enter the angle of rotation";//user enter angle of rotation.
    int angle;
    cin >> angle;
    unsigned char rotatedImage[SIZE][SIZE][RGB];
    if (angle == 90) {
        for (int i = 0; i < SIZE; i++) {// nested loops to iterate over the elements of the image array.
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; k++) {
                    rotatedImage[j][SIZE - i -1][k] = image[i][j][k];// this equation  rotates each element by 90 degrees clockwise.
                }
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; k++) {
                    image[i][j][k] = rotatedImage[i][j][k];//copy the rotated image back to the image array.
                }
            }
        }


    } else if (angle == 180) {

        for (int i = 0; i < SIZE; i++) {// nested loops to iterate over the elements of the image array.
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; k++) {
                    rotatedImage[SIZE - i - 1][SIZE - j -1][k] = image[i][j][k];//this equation  rotates each element by 180 degrees clockwise.
                }
            }
        }


        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; k++) {
                    image[i][j][k] = rotatedImage[i][j][k];//copy the rotated image back to the image array.
                }
            }
        }
    } else if (angle == 270) {

        for (int i = 0; i < SIZE; i++) {// nested loops to iterate over the elements of the image array.
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; k++) {

                    rotatedImage[j][i][k] = image[i][SIZE - j -1][k];// this equation  rotates each element by 270 degrees clockwise.
                }
            }
        }


        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; k++) {
                    image[i][j][k] = rotatedImage[i][j][k];//copy the rotated image back to the image array.
                }
            }
        }


    }
}

//filter 6__________
void darkercolor(){//darken filter it make the image darker to 50%
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            for(int k=0;k<RGB;k++){
                //we make nested loop that loop over every pixel
                darkerandlightercolorImage[i][j][k]+=coloredImage[i][j][k]/4;//to make image darker we will reduce it to its quarter to reach its darker mode
            }
        }
    }
}
void lightercolor(){ //darken filter it make the image lighter to 50%

    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            for(int k=0;k<RGB;k++){
                //we make nested loop that loop over every pixel
                darkerandlightercolorImage[i][j][k]+=coloredImage[i][j][k]+(255-coloredImage[i][j][k])/2;// we make this equation to reach to the highest light for the image
            }
        }
    }
}
void choose(){ //function choose that help user to choose what change he need to make in image

    cout<<"Do you want to (d)arken or (l)ighten?(enter one character dor l)"<<"\n";
    cin>>type;//the user will enter char d or l to choode the change he want
    if(type=='d'){
        darkercolored();
    }
    else lighterColored();
}

// filter 7 detect colored image
void detectColored(){
    int avg=0;
    for(int i=0;i<SIZE;++i){
        for(int j=0;j<SIZE;++j){
            for(int k=0;k<RGB;k++){
                avg+=coloredImage[i][j][k];

            }

        }
    }  avg /= (SIZE*SIZE*3);
    for(int i=0;i<SIZE;++i){
        for(int j=0;j<SIZE;++j){
            for(int k=0;k<RGB;k++){
                if((coloredImage[i][j][k]>avg && coloredImage[i][j+1][k]<=avg )||(coloredImage[i][j][k]<=avg && coloredImage[i+1][j][k]>avg )
                   ||( coloredImage[i][j][k]<=avg &&coloredImage[i][j+1][k]>avg )|| (coloredImage[i][j][k]>avg && coloredImage[i+1][j][k]<=avg )
                   ||(coloredImage[i][j][k]>avg && coloredImage[i+1][j+1][k]<=avg )||(coloredImage[i][j][k]<=avg && coloredImage[i+1][j+1][k]>avg )){
                    coloredImage[i][j][k]=0;

                }
                else{
                    coloredImage[i][j][k]=255;

                }

            }



        }
    }

}
void saveColoredImg () { // function to save colored image
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");

    writeRGBBMP(imageFileName,coloredImage);

}
//__________________________________(filter 8 enlarge colored image)_______________
void enlargeColoerd_quarter() {
    int quarter;
    unsigned char arr[SIZE][SIZE][RGB];// declare a new array to fill the new enlarged image on it.
    cout << "Enter the quarter: ";//user enters the targeted quarter to be enlarged.
    cin >> quarter;

    int X, Y;// x and y defines the starting coordinates of each selected quarter in the original image.
    if (quarter == 1) { //the coordinates of each quarter.
        X = 0;
        Y = 0;
    } else if (quarter == 2) {
        X = 0;
        Y = SIZE / 2;
    } else if (quarter == 3) {
        X = SIZE / 2;
        Y = 0;
    } else if (quarter == 4) {
        X = SIZE / 2;
        Y = SIZE / 2;
    } else {
        cout << "Invalid quarter entered." << endl;
        return;
    }

    for (int i = X; i < X + SIZE / 2; i++) {//implement three nested loops to fill the new image.
        for (int j = Y; j < Y + SIZE / 2; j++) {
            for (int k = 0; k < RGB; k++) {
                arr[2 * (i - X)][2 * (j -Y)][k] = image[i][j][k];// each pixel at position (i, j,k) in the image array is replicated four times in the arr array,
                arr[2 * (i - X) + 1][2 * (j - Y)][k] = image[i][j][k];
                arr[2 * (i - X)][2 * (j - Y) + 1][k] = image[i][j][k];
                arr[2 * (i - X) + 1][2 * (j - Y) + 1][k]=image[i][j][k];
            }
        }
    }

    for (int i = 0; i < SIZE; i++) {// nested loops to copy the values from arr back to the image array.
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {
                image[i][j][k] = arr[i][j][k];
            }
        }
    }
}

//_____________________filter 9______________________

void shrinkColored(int d){
    if(d==1/4){
        void shrinkcolorquarter();
    }
    else if(d==1/3){
        void shrinkcolorthird();
    }
    else {
        void shrinkcolorhalf();
    }
}
// to shrink the image to its quarter the user give the amount of how toshrink
void shrinkcolorquarter(){
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            for(int k=0;k<RGB;k++){
                shrinkcoloredImg[i][j][k]=255; // give the pixel of the image white color by equal it to zero
            }
        }
    }

    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            for(int k=0;k<RGB;k++){
                // condition to avoid the image to be out of range
                if((i*4)<=255&&(j*4)<=255){
                    shrinkcoloredImg[i][j][k]=coloredImage[i*4][j*4][k]; // to reduce image to its quarter we multiply it by 4
                }
            }
        }
    }
}
// to shrink the image to its third the user give the amount of how toshrink

void shrinkcolorthird(){
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            for(int k=0;k<RGB;k++){
                shrinkcoloredImg[i][j][k]=255;
            }
        }
    }

    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            for(int k=0;k<RGB;k++){
                // condition to avoid the image to be out of range
                if((i*3)<=255&&(j*3)<=255){
                    shrinkcoloredImg[i][j][k]=coloredImage[i*3][j*3][k];// to reduce image to its third we multiply it by 4
                }
            }
        }
    }
}
// to shrink the image to its third the user give the amount of how toshrink

void shrinkcolorhalf() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {
                shrinkcoloredImg[i][j][k] = 255;
            }
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {
                // in this case we make it 1.95 not 2 as when multiply it by 2 it will not reduce to half of image as we need
                float x = 1.95;
                // condition to avoid the image to be out of range

                if (int(i * x) <= 255 && int(j * x) <= 255) {
                    shrinkcoloredImg[i][j][k] = coloredImage[int(i * x)][int(j * x)][k];
                }
            }
        }
    }
}
//*************************************//
// filter a mirror 1/2 colored image
void mirrorColored(){
    cout<<"Mirror (l)eft, (r)ight, (u)pper, (d)own side?";
    char side ;
    cin>>side;
    if(side=='l'){
        for(int i=0;i<SIZE;i++){
            for(int j=0;j<SIZE/2;j++){
                for(int k=0;k<RGB;k++){
                    coloredImage[i][SIZE-j][k]=coloredImage[i][j][k];

                }


            }
        }

    }
    else if(side=='r'){
        for(int i=0;i<SIZE;i++){
            for(int j=SIZE/2;j<SIZE;j++){
                for(int k=0;k<RGB;k++){
                    coloredImage[i][SIZE-j][k]=coloredImage[i][j][k];


                }



            }
        }

    }

    else if(side=='u') {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; k++) {

                    coloredImage[SIZE - i][j][k] = coloredImage[i][j][k];
                }

            }
        }
    }


    else if(side=='d'){
        for(int i=0;i<SIZE;i++){
            for(int j=0;j<SIZE;j++){
                for(int k=0;k<RGB;k++){
                    coloredImage[i][j][k]=coloredImage[SIZE-i][j][k];
                }
            }

        }

    }
}

//______________filter a________________________
void blurColored(){
// this function is used to take photo from user and blur it
    for(int i=1;i<SIZE;i++){
        for(int j=1;j<SIZE;j++){
            for(int k=0;k<RGB;k++){
                int x =-1,y=-1,sum=0,num =0;
                while(x<=20){
                    while(y<=20){
                        // to give strong blur we sum 20 pixels together
                        sum += coloredImage[i+x][j+y][k] ;
                        y++;
                        num++;
                    }
                    x++;
                }
                blurColoredImg[i-1][j-1][k]=sum/num;
// we make every pixel in range to be equal the average of 20 pixels
            }
        }

    }

}
//__________________________(filter b shuffle colored image)________________________
void Shuffle_ColoredImage() {//The function Shuffle_Image() is defined.
    cout <<"Enter your order of quarters";//The user is prompted to enter the order of quarters.

    int q_arr[4];//An integer array q_arr is declared to store the order of quarters.

    unsigned char new_shuffled[SIZE][SIZE][RGB];//A 3-dimensional integer array new_shuffled is declared to store the shuffled image.

    for (int i = 0; i < 4; i++) {//A loop is used to read and store the user's input for the order of quarters.
        cin >> q_arr[i];
    }
    for (int i = 0; i < 4; i++) {
        if (i == 0) {//A loop is used to iterate over each quarter specified in the q_arr array.
            if (q_arr[i] == 1) {//(if statements) to handle each quarter based on its index (i) and the value in q_arr[i].
                int m = 0, n = 0;
                for (int j = 0; j < SIZE / 2; j++) {//nested loop with specified coordinates that user decide
                    for (int k = 0; k < SIZE / 2; k++) {
                        for (int l = 0; l < RGB; l++) {
                            new_shuffled[m][n][l] = image[j][k][l];
                        }
                        n++;
                    }
                    n = 0;
                    m++;
                }
            }
            else if (q_arr[i] == 2) {

                int m = 0, n = 0;
                for (int j = 0; j < SIZE / 2; j++) {//nested loop with specified coordinates that user decide
                    for (int k = SIZE / 2; k < SIZE; k++) {
                        for (int l = 0; l < RGB; l++) {
                            new_shuffled[m][n][l] = image[j][k][l];
                        }
                        n++;
                    }
                    n = 0;
                    m++;
                }
            }
            else if (q_arr[i] == 3) {

                int m = 0, n = 0;
                for (int j = SIZE / 2; j < SIZE; j++) {//nested loop with specified coordinates that user decide
                    for (int k = 0; k < SIZE / 2; k++) {
                        for (int l = 0; l < RGB; l++) {
                            new_shuffled[m][n][l] = image[j][k][l];
                        }
                        n++;
                    }
                    n = 0;
                    m++;
                }
            }
            else if (q_arr[i] == 4) {

                int m = 0, n = 0;
                for (int j = SIZE / 2; j < SIZE; j++) {//nested loop with specified coordinates that user decide
                    for (int k = SIZE / 2; k < SIZE; k++) {
                        for (int l = 0; l < RGB; l++) {
                            new_shuffled[m][n][l] = image[j][k][l];
                        }
                        n++;
                    }
                    n = 0;
                    m++;
                }
            }
        }

        else if (i == 1) {//this means that we will Transfer the quarter that user want into the //second quarter// to the new image
            if (q_arr[i] == 1) {
                int m = 0, n = SIZE / 2;
                for (int j = 0; j < SIZE / 2; j++) {//nested loop with specified coordinates that user decide
                    for (int k = 0; k < SIZE / 2; k++) {
                        for (int l = 0; l < RGB; l++) {
                            new_shuffled[m][n][l] = image[j][k][l];
                        }
                        n++;
                    }
                    n = SIZE / 2;
                    m++;
                }
            }
            else if (q_arr[i] == 2) {

                int m = 0, n = SIZE / 2;
                for (int j = 0; j < SIZE / 2; j++) {//nested loop with specified coordinates that user decide
                    for (int k = SIZE / 2; k < SIZE; k++) {
                        for (int l = 0; l < RGB; l++) {
                            new_shuffled[m][n][l] = image[j][k][l];
                        }
                        n++;
                    }
                    n = SIZE / 2;
                    m++;
                }
            }
            else if (q_arr[i] == 3) {

                int m = 0, n = SIZE / 2;
                for (int j = SIZE / 2; j < SIZE; j++) {//nested loop with specified coordinates that user decide
                    for (int k = 0; k < SIZE / 2; k++) {
                        for (int l = 0; l < RGB; l++) {
                            new_shuffled[m][n][l] = image[j][k][l];
                        }
                        n++;
                    }
                    n = SIZE / 2;
                    m++;
                }
            }

            else if (q_arr[i] == 4) {

                int m = 0, n = SIZE/2;
                for (int j = SIZE / 2; j < SIZE; j++) {//nested loop with specified coordinates that user decide
                    for (int k = SIZE / 2; k < SIZE; k++) {
                        for (int l = 0; l < RGB; l++) {
                            new_shuffled[m][n][l] = image[j][k][l];
                        }
                        n++;
                    }
                    n = SIZE/2;
                    m++;
                }
            }
        }


        else if (i == 2) {//this means that we will Transfer the quarter that user want into the //third quarter// to the new image
            if (q_arr[i] == 1) {
                int m = SIZE / 2, n = 0;
                for (int j = 0; j < SIZE / 2; j++) {//nested loop with specified coordinates that user decide
                    for (int k = 0; k < SIZE / 2; k++) {
                        for (int l = 0; l < RGB; l++) {
                            new_shuffled[m][n][l] = image[j][k][l];
                        }
                        n++;
                    }
                    n = 0;
                    m++;
                }
            }
            else if (q_arr[i] == 2) {

                int m = SIZE / 2, n = 0;
                for (int j = 0; j < SIZE / 2; j++) {//nested loop with specified coordinates that user decide
                    for (int k = SIZE / 2; k < SIZE; k++) {
                        for (int l = 0; l < RGB; l++) {
                            new_shuffled[m][n][l] = image[j][k][l];
                        }
                        n++;
                    }
                    n = 0;
                    m++;
                }
            }
            else if (q_arr[i] == 3) {

                int m = SIZE / 2, n = 0;
                for (int j = SIZE / 2; j < SIZE; j++) {//nested loop with specified coordinates that user decide
                    for (int k = 0; k < SIZE / 2; k++) {
                        for (int l = 0; l < RGB; l++) {
                            new_shuffled[m][n][l] = image[j][k][l];
                        }
                        n++;
                    }
                    n = 0;
                    m++;
                }
            }
            else if (q_arr[i] == 4) {

                int m = SIZE / 2, n = 0;
                for (int j = SIZE / 2; j < SIZE; j++) {//nested loop with specified coordinates that user decide
                    for (int k = SIZE / 2; k < SIZE; k++) {
                        for (int l = 0; l < RGB; l++) {
                            new_shuffled[m][n][l] = image[j][k][l];
                        }
                        n++;
                    }
                    n = 0;
                    m++;
                }
            }
        }

        else if (i == 3) {//this means that we will Transfer the quarter that user want into the //forth quarter// to the new image
            if (q_arr[i] == 1) {
                int m = SIZE / 2, n = SIZE / 2;
                for (int j = 0; j < SIZE / 2; j++) {//nested loop with specified coordinates that user decide
                    for (int k = 0; k < SIZE / 2; k++) {
                        for (int l = 0; l < RGB; l++) {
                            new_shuffled[m][n][l] = image[j][k][l];
                        }
                        n++;
                    }
                    n = SIZE / 2;
                    m++;
                }
            }
            else if (q_arr[i] == 2) {

                int m = SIZE / 2, n = SIZE / 2;
                for (int j = 0; j < SIZE / 2; j++) {//nested loop with specified coordinates that user decide
                    for (int k = SIZE / 2; k < SIZE; k++) {
                        for (int l = 0; l < RGB; l++) {
                            new_shuffled[m][n][l] = image[j][k][l];
                        }
                        n++;
                    }
                    n = SIZE / 2;
                    m++;
                }
            }
            else if (q_arr[i] == 3) {

                int m = SIZE / 2, n = SIZE / 2;
                for (int j = SIZE / 2; j < SIZE; j++) {//nested loop with specified coordinates that user decide
                    for (int k = 0; k < SIZE / 2; k++) {
                        for (int l = 0; l < RGB; l++) {
                            new_shuffled[m][n][l] = image[j][k][l];
                        }
                        n++;
                    }
                    n = SIZE / 2;
                    m++;
                }
            }
            else if (q_arr[i] == 4) {

                int m = SIZE / 2,n= SIZE/2;
                for (int j = SIZE / 2; j < SIZE; j++) {//nested loop with specified coordinates that user decide
                    for (int k = SIZE / 2; k < SIZE; k++) {
                        for (int l = 0; l < RGB; l++) {
                            new_shuffled[m][n][l] = image[j][k][l];
                        }
                        n++;
                    }
                    n = SIZE/2;
                    m++;
                }
            }
        }


    }

    for (int i = 0; i < SIZE; i++) {// loop is used to copy the shuffled image from the new_shuffled array back into the image array.
        for (int j = 0; j < SIZE; j++) {
            for (int l = 0; l < RGB; l++) {
                image[i][j][l] =  new_shuffled[i][j][l];
            }
        }
    }
}
//filter d crop colored image
void cropColored() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {
                croppedColoredImage[i][j][k] = 255;
            }
        }
    }
    int x, y, w, l;
    cout << "Please enter x y l w: \n";
    cin >> x >> y >> l >> w;
    for (int i = x; i < l + x; i++) {
        for (int j = y; j < w + y; j++) {
            for (int k = 0; k < RGB; k++) {
                croppedColoredImage[i][j][k] = coloredImage[i][j][k];
            }
        }
    }
}



void saveCroppedColoredImg () { // function to save cropped colored image
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");

    writeRGBBMP(imageFileName,croppedColoredImage);

}
//__________________________________(filter e skew colored image horizontally)__________________
void skew_Coloredimage() {
    unsigned char IMG_1[SIZE][SIZE][RGB];
    unsigned char IMG_2[SIZE][SIZE][RGB];//initializes two arrays to hold skew image during program
    for(int i=0;i<SIZE;++i){//nested loop to initializes all element to color scale
        for(int j=0;j<SIZE;++j){
            for(int k=0;k<RGB;k++) {
                IMG_1[i][j][k] = 255;
                IMG_2[i][j][k] = 255;
            }
        }
    }
    double ang;
    cout<<"Enter the angle of skew";//prompts the user to enter the angle of skew
    cin>>ang;
    ang=(ang*22)/(180*7);//angle is  converted to radians
    int x=(int)(SIZE/(1+1/tan(ang)));//This line calculates x that will be added to each row in the image
    double STP=SIZE-x;//These variables are used to control the positioning of the skewed image.
    double MOV=STP/SIZE;
    for(int i=0;i<SIZE;i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {//nested loops to copy each pixel in original image to  corresponding position in IMG_1
                IMG_1[i][(j * x) / SIZE][k] = image[i][j][k];
            }
        }
    }
    for(int i=0;i<SIZE;i++) {
        for (int j = (int) STP; j < STP + x; j++) {//The starting position (STP) is adjusted in each row,
            for (int k = 0; k < RGB; k++) { // and the pixels are assigned to the corresponding positions in IMG_2.
                IMG_2[i][j][k] = IMG_1[i][(int) (j - STP)][k];
            }
        }
        STP -= MOV;
    }
    for(int i=0;i<SIZE;i++) {//Finally,copy the skew image into original image 
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; k++) {
                image[i][j][k] = IMG_2[i][j][k];
            }
        }
    }


}


//filterf________________
void skewverticallyColored(double angletochange) {
    double lenght = tan((angletochange * 22) / (7 * 180));//the lenght of side front of the angle

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for(int k=0;k<RGB;k++){skewverticallycoloredImg[i][j][k] = 255;}

        }
    }
// for loops to shrink the image
    double ans3 = SIZE / (SIZE - (256 * lenght));
    for (int k = 0; k < RGB; k++) {// the range to shrink the pixels
        for (int j = 0; j < SIZE; j++) {
            int cnt = 1 ;//move the new size after shrink
            for (int i = 0; i < SIZE && cnt <= (SIZE - (256 * lenght)) ; i++) {
                int sum = 0, num = 0;
                for (; i <= (ans3 * cnt) && i < SIZE ; i++) {

                    sum += coloredImage[i][j][k];// calculate sum of pixels to the range of shrink
                    num++;
                    if (i + 1 > (ans3 * cnt)) {
                        break;

                    }
                }
                coloredImage[cnt - 1][j][k] = sum / num; // the average which will be given to the newpixels
                cnt++;

            }

        }
    }
    // for loops to skew the image vertically
    double step = (lenght * 256);
    double move = step / SIZE;
    int anss = SIZE;
    for (int j = 0; j < SIZE; j++) {
        anss = SIZE - ((SIZE * lenght) - step);
        for (int i = step; i < anss; i++) {
            for(int k=0;k<RGB;k++){skewverticallycoloredImg[i][j][k] = coloredImage[int(i - step)][j][k];}

        }
        step -= move;
    }
}

