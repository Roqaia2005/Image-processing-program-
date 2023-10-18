
// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name:				ImgProccesing.cpp
// Last Modification Date:	8/10/2023
// Author1 and ID and Group:	Roqaia Hassan Hassan , ID:20220129,email:roqaiahassanahmed@gmail.com
// Author2 and ID and Group:	Fatima Atef Mahmoud,ID: 20190769,email:Atiff3368@gmail.com
// Author3 and ID and Group:	Tasnim Gomaa Anter ,ID:20220089,email:Tasneemgomaa126@gmail.com
// Teaching Assistant:		    Dr:Mohammed El-Ramly
// Purpose:creating an image processing program with some different filters
// the Whole Gray_scale image processing program


#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char grayImage[SIZE][SIZE];
unsigned char darkImage[SIZE][SIZE];
unsigned char lightImage[SIZE][SIZE];
unsigned char image1[SIZE][SIZE];// img1 to merge
unsigned char image2[SIZE][SIZE];//img2 to merge with
unsigned char mergedImage[SIZE][SIZE];
unsigned char flippedImg[SIZE][SIZE];
unsigned char invertedImg[SIZE][SIZE];
unsigned char rotatedImage[SIZE][SIZE];
unsigned char croppedImage[SIZE][SIZE];


//Functions Declaration//
void loadGrayImage ();
void loadImage1 ();
void loadImage2 ();
void BlackAndWhite (); //filter 1
void invertGray() ;//filter 2
void merge(); //filter 3
void flipGray();//filter 4
void darken();void lighten(); //filter 5
void rotateGray();//filter 6
void detect();//filter 7
void mirrorGray();//filter a
void cropGray();//filter d
//*****functions to save images after processing

void saveMergedImage ();
void saveFlippedImage ();
void saveDarkImg ();
void saveLightImg ();
void saveInvertedImg ();
void saveRotatedImg ();
void saveGrayImg();
void savecroppedImg ();

void choose();//function choose that help user to choose what change he wants to make in image(darken or lighten)

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
                    loadGrayImage();
                    BlackAndWhite();
                    saveGrayImg();
                    showGSBMP(grayImage);
                    break;
                case'2': // filter 2 : Invert Filter
                    loadGrayImage();
                    invertGray();
                    saveInvertedImg();
                    showGSBMP(invertedImg);
                    break;
                case '3':  //filter 3 : Merge Filter

                    loadImage1();
                    loadImage2();
                    merge();
                    saveMergedImage();
                    showGSBMP(mergedImage);
                    break;
                case '4': //filter 4 : Flip Image
                    loadGrayImage();
                    flipGray();
                    saveFlippedImage();
                    showGSBMP(flippedImg);
                    break;
                case '5': //filter 5: Darken and Lighten Image
                    loadGrayImage();
                    choose();
                    break;
                case '6': //filter 6: Rotate Image
                    loadGrayImage();
                    rotateGray();
                    saveRotatedImg();
                    showGSBMP(rotatedImage);
                    break;
                case '7': //filter 7: Detect Image
                    loadGrayImage();
                    detect();
                    saveGrayImg();

                    showGSBMP(grayImage);
                    break;
                case 'a': //filter a: mirror Image
                    loadGrayImage();
                    mirrorGray();
                    saveGrayImg();
                    showGSBMP(grayImage);
                case 'd':
                    loadGrayImage();
                    cropGray();
                    savecroppedImg();
                    showGSBMP(croppedImage);

                    break;
                default:
                    cout<<"Invalid filter\n";

            }

        }


    }

  return 0;
}

//*****************Functions Definitions*******************//

void loadGrayImage () { // function to load gray image we will make change on it
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, grayImage);
}
//_________________________________________//
// filter 1 convert grayscale image to black_white_image
void BlackAndWhite() {

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            if (grayImage[i][j] > 110) {

                grayImage[i][j] = 255; // white
            } else {
                grayImage[i][j] = 0; // black
            }
        }
    }
}
// filter 2 invert gray image
void  invertGray() {
    for (int i = 0; i < SIZE; i++) {//nested loops to scan every pixel.
        for (int j = 0; j< SIZE; j++) {
            invertedImg[i][j] = 255 - grayImage[i][j]; //subtract the maximum value of each pixel to get the inverse bit.

        }


    }
}
void saveInvertedImg () { //function to save inverted image
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");

    writeGSBMP(imageFileName,invertedImg);

}


// function to load first image to merge with another image
void loadImage1 () {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image1);
}
// function to load second image to merge with first image
void loadImage2() {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Please enter name of image file to merge with:  : ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image2);



}
//filter 3 merge filter which take average of the two images user want to merge
void merge(){
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){      //we make nested loop that loop over every pixel

            mergedImage[i][j] = (image1[i][j]+image2[i][j])/2; //we make summation between two images and divide it by 2 make them blending
        }
    }
}

// function to save merged image
void saveMergedImage () {
        char imageFileName[100];

        // Get gray scale image target file name
        cout << "Enter the target image file name: ";
        cin >> imageFileName;

        // Add to it .bmp extension and load image
        strcat (imageFileName, ".bmp");

        writeGSBMP(imageFileName,mergedImage);

}


//-----------------------------------------//

void flipGray(){ //filter 4 that flip gray image
    char mode ;
    cout<<"Flip (h)orizontally or (v)ertically ?";
    cin>>mode;
    if(mode=='H'|| mode=='h'){
        for(int i=0;i<SIZE;i++){
            for(int j=0;j<SIZE;j++){

                flippedImg[i][j]=grayImage[SIZE-i][j];

            }
        }


    }
    else if(mode=='V'||mode=='v'){

        for(int i=0;i<SIZE;i++){
            for(int j=0;j<SIZE;j++){
                flippedImg[i][j]=grayImage[i][SIZE-j];

            }
        }

    }
    else{
        cout<<" Invalid mode";
    }

}
void saveFlippedImage () { //function to save flipped image
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");

    writeGSBMP(imageFileName,flippedImg);

}

//filter 5//
void darken(){//darken filter which make the image darker to 50%
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            //we make nested loop that loop over every pixel
            darkImage[i][j]=grayImage[i][j]/2; //to make image darker we will reduce it to its half to reach its darker mode
        }
    }

}
void lighten() {//darken filter which make the image lighter to 50%
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {            //we make nested loop that loop over every pixel

            lightImage[i][j]= grayImage[i][j]+(255-grayImage[i][j])/2;// we make this equation to reach to the highest light for the image
        }

    }
}


void choose(){ //function choose that help user to choose what change he wants to make in image
    char type;
    cout<<"Do you want to (d)arken or (l)ighten?(enter one character d or l)"<<"\n";
    cin>>type;//the user will enter char d or l to choose the change he wants
    if(type=='d'){
        darken();
        saveDarkImg();
        showGSBMP(darkImage);
    }
    else if(type=='l'){
        lighten();
        saveLightImg();
        showGSBMP(lightImage);
    }
}

void saveDarkImg () { //function to save image after darken it
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");

    writeGSBMP(imageFileName,darkImage);

}
void saveLightImg () { //function to save image after lighten it
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");

    writeGSBMP(imageFileName,lightImage);

}







void rotateGray(){ // filter 6 to rotate gray image
    cout<<"Enter the angle of rotation :(90-180-270)";//user enter angle of rotation.
    int angle;
    cin >> angle;

    if (angle == 90) {
        for (int i = 0; i < SIZE; i++) {// nested loops to iterate over the elements of the image array.
            for (int j = 0; j < SIZE; j++) {
                rotatedImage[j][SIZE - i - 1] = grayImage[i][j];// this equation  rotates each element by 90 degrees clockwise.
            }
        }for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                grayImage[i][j] = rotatedImage[i][j];//copy the rotated image back to the image array.
            }
        }
    }
    else if(angle==180){

        for (int i = 0; i < SIZE; i++) {// nested loops to iterate over the elements of the image array.
            for (int j = 0; j < SIZE; j++) {
                rotatedImage[SIZE - i - 1][SIZE - j - 1] = grayImage[i][j];//this equation  rotates each element by 180 degrees clockwise.
            }
        }


        for (int i = 0; i < SIZE; i++) {//copy the rotated image back to the image array.
            for (int j = 0; j < SIZE; j++) {
                grayImage[i][j] = rotatedImage[i][j];
            }
        }

    }
    else if(angle==270){

        for (int i = 0; i < SIZE; i++) {// nested loops to iterate over the elements of the image array.
            for (int j = 0; j < SIZE; j++) {
                rotatedImage[SIZE - j - 1][i] = grayImage[i][j];// this equation rotates each element by 270 degrees clockwise.
            }
        }



        for (int i = 0; i < SIZE; i++) {//copy the rotated image back to the image array.
            for (int j = 0; j < SIZE; j++) {
                grayImage[i][j] = rotatedImage[i][j];
            }
        }
    }


}

void saveRotatedImg () { // function to save rotated image
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");

    writeGSBMP(imageFileName,rotatedImage);

}


// filter 7 detect gray image
void detect(){
    int avg=0;
    for(int i=0;i<SIZE;++i){
        for(int j=0;j<SIZE;++j){
            avg+=grayImage[i][j];
        }
    }  avg /= (SIZE*SIZE);
    for(int i=0;i<SIZE;++i){
        for(int j=0;j<SIZE;++j){
            if((grayImage[i][j]>avg && grayImage[i][j+1]<=avg )||(grayImage[i][j]<=avg && grayImage[i+1][j]>avg )
               ||( grayImage[i][j]<=avg && grayImage[i][j+1]>avg )|| (grayImage[i][j]>avg && grayImage[i+1][j]<=avg )
               ||(grayImage[i][j]>avg && grayImage[i+1][j+1]<=avg )||(grayImage[i][j]<=avg && grayImage[i+1][j+1]>avg )){
                grayImage[i][j]=0;

            }
            else{
                grayImage[i][j]=255;

            }

        }
    }

}
//filter (a) to mirror 1/2 gray image
void mirrorGray(){
    cout<<"Mirror (l)eft, (r)ight, (u)pper, (d)own side?";
    char side ;
    cin>>side;
    if(side=='l'){
        for(int i=0;i<SIZE;i++){
            for(int j=0;j<SIZE/2;j++){
                grayImage[i][SIZE-j]=grayImage[i][j];

            }
        }

    }
    else if(side=='r'){
        for(int i=0;i<SIZE;i++){
            for(int j=SIZE/2;j<SIZE;j++){
                grayImage[i][SIZE-j]=grayImage[i][j];


            }
        }

    }

    else if(side=='u'){
        for(int i=0;i<SIZE;i++){
            for(int j=0;j<SIZE;j++){
                grayImage[SIZE-i][j]=grayImage[i][j];
            }

        }

    }

    else if(side=='d'){
        for(int i=0;i<SIZE;i++){
            for(int j=0;j<SIZE;j++){
                grayImage[i][j]=grayImage[SIZE-i][j];
            }

        }
        }

    }


void saveGrayImg () { // function to save gray image
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");

    writeGSBMP(imageFileName,grayImage);

}


// filter (d) to crop gray image
void cropGray(){
    int x,y,l,w;
    cout<<"Please enter x y l w:";
    cin>>x>>y>>l>>w;
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            croppedImage[i][j]=255;

        }

    }
    for(int i=x;i<=l+x;i++){
        for(int j=y;j<=y+w;j++){
            croppedImage[i][j]=grayImage[i][j];

        }

    }

}

void savecroppedImg () { // function to save cropped image
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");

    writeGSBMP(imageFileName,croppedImage);

}

