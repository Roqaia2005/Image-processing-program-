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
unsigned char image[SIZE][SIZE];
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
unsigned char blurImg[SIZE][SIZE];
unsigned char shrinkImg[SIZE][SIZE];
unsigned char skewverticalImg[SIZE][SIZE];


//Functions Declaration//
void loadGrayImage ();
void loadImage ();
void loadImage1 ();
void loadImage2 ();
void BlackAndWhite (); //filter 1
void invertGray() ;//filter 2
void merge(); //filter 3
void flipGray();//filter 4
void rotateGray();//filter 5
void darken();void lighten(); //filter 6
void detect();//filter 7
void enlarge_quarter();//filter 8
void shrink(int dimensiontochange);//filter 9
void mirrorGray();//filter a
void Shuffle_Image();//filter b
void blur();//filter c
void cropGray();//filter d
void skew_image();//filter e
void skew_vertically(double angletochange);//filter f



//*****functions to save images after processing
void saveImage ();
void saveMergedImage ();
void saveFlippedImage ();
void saveDarkImg ();
void saveLightImg ();
void saveInvertedImg ();
void saveRotatedImg ();
void saveGrayImg();
void savecroppedImg ();
void saveblurImg();
void saveshrinkImg();
void saveskewverticalImg();
void choose();//function choose that help user to choose what change he wants to make in image(darken or lighten)
void quartershrink();
void thirdshrink();
void halfshrink();
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
                case '8': //filter 8: enlarge a quarter of an image
                    loadImage ();
                    enlarge_quarter();
                    saveImage ();
                    showGSBMP( image);
                    break;
                case '9':// filter 9: shrink of an image
                    loadImage();
                    int changedeminison;
                    shrink(changedeminison);
                    saveshrinkImg();
                    showGSBMP(shrinkImg);
                    break;
                case 'a': //filter a: mirror Image
                    loadGrayImage();
                    mirrorGray();
                    saveGrayImg();
                    showGSBMP(grayImage);
                case 'b': //filter 8: enlarge a quarter of an image
                    loadImage ();
                    Shuffle_Image();
                    saveImage ();
                    showGSBMP(image);
                    break;
                case 'c':// filter c: blur of image
                    loadImage();
                    blur();
                    saveblurImg();
                    showGSBMP(blurImg);
                    break;
                case 'd':
                    loadGrayImage();
                    cropGray();
                    savecroppedImg();
                    showGSBMP(croppedImage);

                    break;
                case 'e': //filter e: skew an image horizontally
                    loadImage ();
                    skew_image();
                    saveImage ();
                    showGSBMP(image);
                    break;
                case 'f':// filter f: skew an image vertically
                    loadImage();
                    double angle;
                    cout<<"Enter the angle of skew";
                    cin>>angle;
                    skew_vertically(angle);
                    saveskewverticalImg();
                    showGSBMP(skewverticalImg);
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
    readGSBMP(imageFileName, image);
}
//_________________________________________
void saveImage () {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

//-----------------------------------------------------

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

char type;
void choose(){ //function choose that help user to choose what change he wants to make in image

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

//___________filter 9: shrink______________
void shrink(int dimension){ // function take amount of shrink from user and call the function of shrink of that amount
    if(dimension==1/4){
        quartershrink();
    }
    else if(dimension==1/3){
        thirdshrink();
    }
    else {
        halfshrink();
    }
}
void quartershrink(){
    // to shrink the image to its quarter the user give the amount of how toshrink
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            shrinkImg[i][j]=255;// give the pixel of the image white color by equal it to 255
        }
    }
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if((i*4)<=255&&(j*4)<=255){// condition to avoid the image to be out of range
                shrinkImg[i][j]=image[i*4][j*4];// to reduce image to its quarter we multiply it by 4
            }

        }
    }
}
// to shrink the image to its third the user give the amount of how toshrink
void thirdshrink(){
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            shrinkImg[i][j]=255;// give the pixel of the image white color by equal it to 255
        }
    }
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if((i*3)<=255&&(j*3)<=255){// condition to avoid the image to be out of range
                shrinkImg[i][j]=image[i*3][j*3];// to reduce image to its third we multiply it by 3
            }

        }
    }
}
// to shrink the image to its third the user give the amount of how toshrink
void halfshrink(){
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            shrinkImg[i][j]=255;// give the pixel of the image white color by equal it to 255
        }
    }
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
// in this case we make it 1.95 not 2 as when multiply it by 2 it will not reduce to half of image as we need

            float x= 1.95;
            if(int(i*x)<=255&&int(j*x)<=255){// condition to avoid the image to be out of range
                shrinkImg[i][j]=image[int(i*x)][int(j*x)];
            }

        }
    }
}
void saveshrinkImg(){ //function to save shrink image
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");

    writeGSBMP(imageFileName,shrinkImg);
}
void blur() {// this function is used to take photo from user and blur it
    for (int i = 1; i < SIZE; i++) {
        for (int j = 1; j < SIZE; j++) {
            int x = -1, y = -1, sum = 0, num = 0;
            while (x <= 10) {
                while (y <= 10) {// to give strong blur we sum 10 pixels together
                    sum += image[i + x][j + y];
                    y++;
                    num++;
                }
                x++;
            }
            blurImg[i - 1][j - 1] = sum / num; // we equal the pixel with new value which is average of 10 pixels
        }
    }
}
void saveblurImg(){ //function to save blur image
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");

    writeGSBMP(imageFileName,blurImg);
}
// skew vertical function which take the degree to skew photo fromthe user
unsigned imageone[SIZE][SIZE];
unsigned imagetwo[SIZE][SIZE];
void skew_vertically(double angletochange) {


        for (int i = 0; i < SIZE ; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                imageone[i][j] = 255;
                imagetwo[i][j] = 255;
            }
        }

    angletochange = (angletochange * 22) / (180 * 7);
        int oppositeside = (int)(SIZE / ( 1 + tan(angletochange)));
        double step = SIZE - oppositeside;
        double move = step/ SIZE;
        for (int i = 0; i < SIZE ; ++i) {
            for (int j = 0; j < SIZE ; ++j) {
                imageone[(i*oppositeside)/SIZE][j] = image[i][j];
            }
        }

        for (int i = 0; i <SIZE ; ++i) {
            for (int j = (int)step; j < step+oppositeside ; ++j) {
                imagetwo[j][i] = imageone[(int)(j-step)][i];
            }
            step -= move;
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                skewverticalImg[i][j] = imagetwo[i][j];
            }
        }
    }


void saveskewverticalImg(){//function to save skewvertically image
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");

    writeGSBMP(imageFileName,skewverticalImg);
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
//___________________________________________________(enlarge filter NO 8)_________________
void enlarge_quarter(){

    int quarter;
    int arr[256][256];//define new arr that will hold new enlarged quarter
    cout << "Enter the quarter ";//ask user and take the quarter wanted
    cin >> quarter;
    if (quarter == 1) {
        int x = 0, y = 0;//starting coordinates of new image
        for (int i = 0; i < SIZE / 2; i++) {//nested loop to take quarter 1 and enlarge it
            for (int j = 0; j < SIZE / 2; j += 1) {
                arr[x][y] = image[i][j];//each pixel enlarge to 4 pixels
                arr[x + 1][y] = image[i][j];
                arr[x][y + 1] = image[i][j];
                arr[x + 1][y + 1] = image[i][j];
                y += 2;
            }
            y = 0;
            x += 2;
        }
    }


    if(quarter==2){
        int x = 0, y = 0;//starting coordinates of new image
        for (int i = 0; i < SIZE/2; i++) {//nested loop to take quarter 2 and enlarge it
            for (int j = SIZE/2; j < SIZE ; j += 1) {
                arr[x][y] = image[i][j];//each pixel enlarge to 4 pixels
                arr[x + 1][y] = image[i][j];
                arr[x][y + 1] = image[i][j];
                arr[x + 1][y + 1] = image[i][j];
                y+=2;
            }
            y=0;
            x+=2;
        }

    }
    if (quarter == 3) {
        int x = 0, y = 0;//starting coordinates of new image
        for (int i = SIZE / 2; i < SIZE; i++) {//nested loop to take quarter 3 and enlarge it
            for (int j = 0; j < SIZE / 2; j += 1) {
                arr[x][y] = image[i][j];//each pixel enlarge to 4 pixels
                arr[x + 1][y] = image[i][j];
                arr[x][y + 1] = image[i][j];
                arr[x + 1][y + 1] = image[i][j];
                y += 2;
            }
            y = 0;
            x += 2;
        }
    }
    if(quarter==4){
        int x = 0, y = 0;//starting coordinates of new image
        for (int i = SIZE/2; i < SIZE; i++) {//nested loop to take quarter 4 and enlarge it
            for (int j = SIZE/2; j < SIZE ; j += 1) {
                arr[x][y] = image[i][j];//each pixel enlarge to 4 pixels
                arr[x + 1][y] = image[i][j];
                arr[x][y + 1] = image[i][j];
                arr[x + 1][y + 1] = image[i][j];
                y+=2;
            }
            y=0;
            x+=2;
        }

    }

    for (int i = 0; i < SIZE; i++) {// lastly nested loop to copy enlarged arr to image.
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = arr[i][j];
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
//_______________________________(shuffle image_filter(b))___________________

void Shuffle_Image() {//The function Shuffle_Image() is defined.
    cout <<"Enter your order of quarters";//The user is prompted to enter the order of quarters.

    int q_arr[4];//An integer array q_arr is declared to store the order of quarters.

    int new_shuffled[SIZE][SIZE];//A 2-dimensional integer array new_shuffled is declared to store the shuffled image.

    for (int i = 0; i < 4; i++) {//A loop is used to read and store the user's input for the order of quarters.
        cin >> q_arr[i];
    }
    for (int i = 0; i < 4; i++) {//A loop is used to iterate over indixes
        if (i == 0) {//this means that we will Transfer the quarter that user want into the //first quarter// in the new image
            if (q_arr[i] == 1) {//(if statements) to handle each quarter that user wants
                int m = 0, n = 0;//start coordinates of 1st quarter
                for (int j = 0; j < SIZE/2; j++) {//nested loop with specified coordinates that user decide
                    for (int k = 0; k < SIZE / 2; k++) {
                        new_shuffled[m][n] = image[j][k];//The elements  of the image array are copied into  new_shuffled array.
                        n++;
                    }
                    n = 0;
                    m++;
                }
            } else if (q_arr[i] == 2) {

                int m = 0, n = 0;
                for (int j = 0; j < SIZE / 2; j++) {//nested loop with specified coordinates that user decide
                    for (int k = SIZE / 2; k < SIZE; k++) {
                        new_shuffled[m][n] = image[j][k];
                        n++;
                    }
                    n = 0;
                    m++;
                }
            } else if (q_arr[i] == 3) {

                int m = 0, n = 0;
                for (int j = SIZE/2; j < SIZE; j++) {//nested loop with specified coordinates that user decide
                    for (int k = 0; k < SIZE / 2; k++) {
                        new_shuffled[m][n] = image[j][k];
                        n++;
                    }
                    n = 0;
                    m++;
                }
            } else if (q_arr[i] == 4) {

                int m = 0, n = 0;
                for (int j = SIZE / 2; j < SIZE; j++) {//nested loop with specified coordinates that user decide
                    for (int k = SIZE / 2; k < SIZE; k++) {
                        new_shuffled[m][n] = image[j][k];
                        n++;
                    }
                    n = 0;
                    m++;
                }
            }
        }

        else if (i == 1) {//this means that we will Transfer the quarter that user want into the //second quarter// to the new image
            if (q_arr[i] == 1) {//(if statements) to handle each quarter that user wants
                int m = 0, n = SIZE/2;//start coordinates of 2nd quarter
                for (int j = 0; j < SIZE/2; j++) {
                    for (int k = 0; k < SIZE / 2; k++) {
                        new_shuffled[m][n] = image[j][k];
                        n++;
                    }
                    n = SIZE/2;
                    m++;
                }
            } else if (q_arr[i] == 2) {

                int m = 0, n = SIZE/2;
                for (int j = 0; j < SIZE / 2; j++) {//nested loop with specified coordinates that user decide
                    for (int k = SIZE / 2; k < SIZE; k++) {
                        new_shuffled[m][n] = image[j][k];
                        n++;
                    }
                    n =SIZE/2;
                    m++;
                }
            } else if (q_arr[i] == 3) {

                int m = 0, n = SIZE/2;
                for (int j = SIZE / 2; j < SIZE; j++) {//nested loop with specified coordinates that user decide
                    for (int k = 0; k < SIZE / 2; k++) {
                        new_shuffled[m][n] = image[j][k];
                        n++;
                    }
                    n = SIZE/2;
                    m++;
                }
            } else if (q_arr[i] == 4) {

                int m = 0, n = SIZE/2;
                for (int j = SIZE / 2; j < SIZE; j++) {//nested loop with specified coordinates that user decide
                    for (int k = SIZE / 2; k < SIZE; k++) {
                        new_shuffled[m][n] = image[j][k];
                        n++;
                    }
                    n = SIZE/2;
                    m++;
                }
            }
        }


        else if (i == 2) {//this means that we will Transfer the quarter that user want into the //third quarter// to the new image
            if (q_arr[i] == 1) {//(if statements) to handle each quarter that user wants
                int m = SIZE / 2, n = 0;//start coordinates of 3rd quarter
                for (int j = 0; j < SIZE/2; j++) {//nested loop with specified coordinates that user decide
                    for (int k = 0; k < SIZE / 2; k++) {
                        new_shuffled[m][n] = image[j][k];
                        n++;
                    }
                    n = 0;
                    m++;
                }
            } else if (q_arr[i] == 2) {

                int m = SIZE / 2, n = 0;
                for (int j = 0; j < SIZE / 2; j++) {//nested loop with specified coordinates that user decide
                    for (int k = SIZE / 2; k < SIZE; k++) {
                        new_shuffled[m][n] = image[j][k];
                        n++;
                    }
                    n = 0;
                    m++;
                }
            } else if (q_arr[i] == 3) {

                int m = SIZE / 2, n = 0;
                for (int j = SIZE / 2; j < SIZE; j++) {//nested loop with specified coordinates that user decide
                    for (int k = 0; k < SIZE / 2; k++) {
                        new_shuffled[m][n] = image[j][k];
                        n++;
                    }
                    n = 0;
                    m++;
                }
            } else if (q_arr[i] == 4) {

                int m = SIZE / 2, n = 0;
                for (int j = SIZE / 2; j < SIZE; j++) {//nested loop with specified coordinates that user decide
                    for (int k = SIZE / 2; k < SIZE; k++) {
                        new_shuffled[m][n] = image[j][k];
                        n++;
                    }
                    n = 0;
                    m++;
                }
            }
        }

        else if (i == 3) {//this means that we will Transfer the quarter that user want into the //forth quarter// to the new image
            if (q_arr[i] == 1) {//(if statements) to handle each quarter that user wants
                int m = SIZE / 2,n= SIZE/2;//start coordinates of 4th quarter
                for (int j = 0; j < SIZE/2; j++) {//nested loop with specified coordinates that user decide
                    for (int k = 0; k < SIZE / 2; k++) {
                        new_shuffled[m][n] = image[j][k];
                        n++;
                    }
                    n = SIZE/2;
                    m++;
                }
            } else if (q_arr[i] == 2) {

                int m = SIZE / 2,n= SIZE/2;
                for (int j = 0; j < SIZE / 2; j++) {//nested loop with specified coordinates that user decide
                    for (int k = SIZE / 2; k < SIZE; k++) {
                        new_shuffled[m][n] = image[j][k];
                        n++;
                    }
                    n = SIZE/2;
                    m++;
                }
            } else if (q_arr[i] == 3) {

                int m = SIZE / 2, n=SIZE/2;
                for (int j = SIZE / 2; j < SIZE; j++) {//nested loop with specified coordinates that user decide
                    for (int k = 0; k < SIZE / 2; k++) {
                        new_shuffled[m][n] = image[j][k];
                        n++;
                    }
                    n = SIZE/2;
                    m++;
                }
            } else if (q_arr[i] == 4) {

                int m = SIZE / 2,n= SIZE/2;
                for (int j = SIZE / 2; j < SIZE; j++) {//nested loop with specified coordinates that user decide
                    for (int k = SIZE / 2; k < SIZE; k++) {
                        new_shuffled[m][n] = image[j][k];
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
            image[i][j] = new_shuffled[i][j];
        }
    }
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
//________________________(skew horizontally(filter e))________________________
void skew_image() {
    unsigned char IMG_1[SIZE][SIZE];
    unsigned char IMG_2[SIZE][SIZE];//initializes two arrays to hold skew image during program
    for(int i=0;i<SIZE;++i){
        for(int j=0;j<SIZE;++j){ //nested loop to initializes all element to grayscale
            IMG_1[i][j]=255;
            IMG_2[i][j]=255;
        }
    }
    double ang;
    cout<<"Enter the angle of skew";//prompts the user to enter the angle of skew
    cin>>ang;
    ang=(ang*22)/(180*7);//angle is  converted to radians
    int x=(int)(SIZE/(1+1/tan(ang)));//This line calculates x that will be added to each row in the image
    double STP=SIZE-x;//These variables are used to control the positioning of the skewed image.
    double MOV=STP/SIZE;
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){//nested loops to copy each pixle in original image to  corresponding position in IMG_1
            IMG_1[i][(j*x)/SIZE]=image[i][j];
        }
    }
    for(int i=0;i<SIZE;i++){//The starting position (STP) is adjusted in each row,
        // and the pixels are assigned to the corresponding positions in IMG_2.
        for(int j=(int)STP;j<STP+x;j++){
            IMG_2[i][j]=IMG_1[i][(int)(j-STP)];
        }
        STP-=MOV;
    }
    for(int i=0;i<SIZE;i++){//Finally,copy the skew image into original image .
        for(int j=0;j<SIZE;++j){
            image[i][j]=IMG_2[i][j];
        }
    }


}











































































































