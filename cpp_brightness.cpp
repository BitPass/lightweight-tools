// 	based on whatsacreel's youtube tutorial x64 Assembly and C++ Tutorial

Bitmap^ bmpFront;
unsigned char* bmpOriginal;	
static int imageSizeInBytes = -1;
static Rectangle imageRectangle;
BitmapData ^bmpData;
static double cppCount = 0.0;
static double cppTotal = 0.0;

void AdjustBrightness(unsigned char* bmp, short amount)
{
	for(int i = 0; i < imageSizeInBytes; i++)
	{
	if((short) bmpOriginal[i] + amount < 0) 
		bmp[i] = 0;
	else if ((short) bmpOriginal[i] + amount > 255) 
		bmp[i] = 255;
	else bmp[i] = bmpOriginal[i] + amount;
	}
}

void ClearOriginalImage()
{
	if(bmpOriginal != nullptr)
		delete[] bmpOriginal;
}


void SaveOriginalImage(System::Drawing::Bitmap ^bmp)
{
	ClearOriginalImage();
	imageSizeInBytes = bmp->Width * bmp->Height * 3;			
	bmpOriginal = new unsigned char [imageSizeInBytes];
	imageRectangle.Width = bmp->Width;
	imageRectangle.Height = bmp->Height;
	bmpData = bmp->LockBits(imageRectangle, ImageLockMode::ReadOnly, PixelFormat::Format24bppRgb);
	unsigned char*p = (unsigned char*) bmpData->Scan0.ToPointer();
	for(int i = 0; i < imageSizeInBytes; i++)
	{
		bmpOriginal[i] = *p++;
	}
	bmp->UnlockBits(bmpData);
}