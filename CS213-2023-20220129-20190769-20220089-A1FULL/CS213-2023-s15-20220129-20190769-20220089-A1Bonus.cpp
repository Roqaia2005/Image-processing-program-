
// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name:				ImgProcessing
// Last Modification Date:	8/10/2023
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
unsigned char coloredImage[SIZE][SIZE][RGB];

unsigned char black_white_image[SIZE][SIZE]; //black and white img
unsigned char flippedColoredImg[SIZE][SIZE][RGB];
unsigned char coloredInvertedImg[SIZE][SIZE][RGB];

unsigned char croppedColoredImage[SIZE][SIZE][RGB];


//Functions Declaration//
void loadColoredImage ();
void BlackAndWhiteColored(); //filter 1
void invertColored() ;//filter 2
void flipColored();//filter 4
void detectColored();//filter 7
void mirrorColored();//filter a
void cropColored();//filter d
//*****functions to save images after processing
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

                case '4': //filter 4 : Flip colored Image
                    loadColoredImage();
                    flipColored();
                    saveFlippedColoredImage();
                    showRGBBMP(flippedColoredImg);
                    break;

                case '7': //filter 7: Detect colored Image
                    loadColoredImage();
                    detectColored();
                    saveColoredImg();
                    showRGBBMP(coloredImage);
                    break;
               case 'a': //filter a: mirror colored Image
                   loadColoredImage();
                   mirrorColored();
                   saveColoredImg();
                   showRGBBMP(coloredImage);
                    break;

                case 'd': // filter d crop colored image
                    loadColoredImage();
                    cropColored();
                    saveCroppedColoredImg();
                    showRGBBMP(croppedColoredImage);
                    break;
                default:
                    cout<<"Invalid filter\n";

            }

        }


    }

    return 0;
}

//*****************Functions Definitions*******************//

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
// filter 2 invert colored image
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

