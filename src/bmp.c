#pragma pack(push, 1)
typedef struct tagBITMAPFILEHEAD
{
    WORD bfType;           //file type
    DWORD bfSize;          //size in bytes of the bitmap file
    WORD bfReserved1;      //reserved; must be 0
    WORD bfReserved2;      //reserved; must be 0
    DWORD bfOffBits;       //offset in bytes from the bitmapfileheader to the bitmap bits
}BITMAPFILEHEAD;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct tagBITMAPINFOHEAD
{
    DWORD biSize;          //bytes required by the struct
    LONG biWidth;          //width in pixels
    LONG biHeight;         //height in pixels
    WORD biPlanes;         //color planes, must be 1
    WORD biBitCount;       //bits per pixel
    DWORD biCompression;   //type of compression
    DWORD biSizeImage;     //size of image in bytes
    LONG biXPelsPerMeter;  //number of pixels per meter in x axis
    LONG biYPelsPerMeter;  //number of pixels per meter in y axis
    DWORD biClrUsed;       //number of colors used by the bitmap
    DWORD biClrImportant;  //number of colors that are important
}BITMAPINFOHEAD;
#pragma pack(pop)

unsigned char *LoadBitmapFle(char *filename, BITMAPINFOHEAD *bitmapInfoHeader)
{
    FILE *filePtr; 
    BITMAPFILEHEADER bitmapFileHeader; 
    unsigned char *bitmapImage;  
    int imageIdx=0;  
    unsigned char tempRGB; 
    filePtr = fopen(filename,"rb");
    if (filePtr == NULL)
        return NULL;
    fread(&bitmapFileHeader, sizeof(BITMAPFILEHEAD),1,filePtr);
    if (bitmapFileHeader.bfType !=0x4D42)
    {
        fclose(filePtr);
        return NULL;
    }
    fread(bitmapInfoHeader, sizeof(BITMAPINFOHEAD),1,filePtr); 
    fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);
	bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);
    if (!bitmapImage)
    {
        free(bitmapImage);
        fclose(filePtr);
        return NULL;
    }
    fread(bitmapImage,bitmapInfoHeader->biSizeImage,1,filePtr);
    if (bitmapImage == NULL)
    {
        fclose(filePtr);
        return NULL;
    }
    for (imageIdx = 0;imageIdx < bitmapInfoHeader->biSizeImage;imageIdx+=3)
    {
        tempRGB = bitmapImage[imageIdx];
        bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
        bitmapImage[imageIdx + 2] = tempRGB;
    }
    fclose(filePtr);
    return bitmapImage;
}