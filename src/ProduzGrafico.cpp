#include "ProduzGrafico.h"

void ProduzGrafico::dataToPng(string nomePNG, vector<double> xs, vector<double> ys) 
{
	const string nomeBaseArquivo = "Grafico";

    RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();

    DrawScatterPlot(imageReference, ProduzGrafico::xWindowSize, ProduzGrafico::yWindowSize, &xs, &ys);

	vector<double> *pngdata = ConvertToPNG(imageReference->image);
	WriteToFile(pngdata, nomeBaseArquivo + nomePNG);
	DeleteImage(imageReference->image);
}