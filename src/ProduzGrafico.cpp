#include "ProduzGrafico.h"

void ProduzGrafico::dataToPng(string nomePNG, vector<double> xs, vector<double> ys) 
{
    RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();

    DrawScatterPlot(imageReference, 600, 400, &xs, &ys);

	vector<double> *pngdata = ConvertToPNG(imageReference->image);
	WriteToFile(pngdata, nomePNG);
	DeleteImage(imageReference->image);
}