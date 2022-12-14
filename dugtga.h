//--------------------------------------------------------------------------------------------------
// Ce code source est du domaine publique.
// Auteur : Stephane Duguay, septembre 2014. s@binarez.com
//--------------------------------------------------------------------------------------------------

#ifndef DUGTGA_H
#define DUGTGA_H

//--------------------------------------------------------------------------------------------------
typedef		unsigned char		octet;

//--------------------------------------------------------------------------------------------------
template <typename T>
struct Pixel
{
	Pixel(void)
	: r(0), g(0), b(0) { }
	Pixel(T _r, T _g, T _b)
		: r(_r), g(_g), b(_b) { }

	// 1 pixel = Red-Green-Blue = Rouge-Vert-Bleu
	// octet = 8 bits = peut contenir des valeurs de 0 à 255 inclusivement.
	T		r;	// Rouge (0 -> 255)
	T		g;	// Vert (0 -> 255)
	T		b;	// Bleu (0 -> 255)
};


/*/-------------------------------------------------------------------------------------------------
Fonction ecrireTGA
nomFichier : le nom du fichier à produire sur le disque;
largeur : la largeur de l’image contenue dans le tableau de Pixel;
hauteur : la hauteur de l’image contenue dans le tableau de Pixel;
pPixels : le tableau de pixels en mémoire à écrire dans le fichier.
		(chacune des lignes de l'image se suivent dans le tableau, en partant de la ligne d'en haut)

La fonction retourne false si une erreur s’est produite et true autrement.
//------------------------------------------------------------------------------------------------*/
bool ecrireTGA(const char* nomFichier, int largeur, int hauteur, const Pixel<octet> pixels[]);

#endif // DUGTGA_H
