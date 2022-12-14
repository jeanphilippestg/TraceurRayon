//--------------------------------------------------------------------------------------------------
// Ce code source est du domaine publique.
// Auteur : Stephane Duguay, septembre 2014. s@binarez.com
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "dugtga.h"
#include <fstream>

//--------------------------------------------------------------------------------------------------
template <typename T>
bool ecrireTGA(const char* nomFichier, int largeur, int hauteur, const Pixel<T> pixels[])
{
	if (largeur <= 0 || hauteur <= 0)
	{
		return false;
	}

	// Ouverture en binaire du fichier d'écriture
	std::ofstream o(nomFichier, std::ios::out | std::ios::binary);

	if (o.fail())
	{
		// Le destructeur du ofstream ferme le fichier pour nous
		return false;
	}

	// Écriture de l'entête TGA (header)
	// http://www.fileformat.info/format/tga/egff.htm
	o.put(0);
	o.put(0);
	o.put(2);                         // Le type est "uncompressed RGB"
	o.put(0); 	o.put(0);
	o.put(0); 	o.put(0);
	o.put(0);
	o.put(0); 	o.put(0);			// origine X
	o.put(0); 	o.put(0);           // origine Y
	o.put((largeur & 0x00FF));
	o.put(static_cast<char>((largeur & 0xFF00) / 256));
	o.put((hauteur & 0x00FF));
	o.put(static_cast<char>((hauteur & 0xFF00) / 256));
	o.put(24);						// Image 24-bit RGB
	o.put(0);						// Coin inferieur gauche de l'image est origine

	// Ecriture des pixels dans le fichier
	for (int y = hauteur - 1; y >= 0; --y)
	{
		// Ecriture des pixels dans le fichier
		for (int x = 0; x < largeur; ++x)
		{
			const int pixIndex = y * largeur + x;
			o.put(pixels[pixIndex].b);
			o.put(pixels[pixIndex].g);
			o.put(pixels[pixIndex].r);
		}
	}

	o.close();

	return true;
}
