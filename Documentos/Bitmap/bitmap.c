

typedef struct _BITMAPFILEHEADER
{
	UINT    bfType;		    /* (2 byte)	Tipo de archivo, vale 'BM' */
	DWORD   bfSize;		    /* (4 byte)	Tamaño del archivo en bytes. */
	UINT    bfReserved1;	/* (2 byte)	Reservado. Todo ceros. */
	UINT    bfReserved2;	/* (2 byte)	Reservado. Todo ceros. */
	DWORD   bfOffBits;	    /* (4 byte)	Distancia en bytes entre BITMAPINFOHEADER y 
						       el mapa de bits (aBitmapBits[])
						       Si vale cero, significa que la estructura
						       RGBQUAD no está presente. No hay paleta
						       de colores. */
} BITMAPFILEHEADER;

typedef struct _BITMAPINFOHEADER
{

    DWORD   biSize;		        /* (4 byte)	Numero de bytes que ocupa esta estructura. */
    LONG    biWidth;	        /* (4 byte)	Anchura del bitmap */
    LONG    biHeight;	        /* (4 byte)	Altura del bitmap */
    WORD    biPlanes;	        /* (2 byte)	Numero de planos de color (siempre 1) */
    WORD    biBitCount;	        /* (2 byte)	Bits por pixel (1,4,8,24) */
    DWORD   biCompression;	    /* (4 byte)	Compresion utilizada
                                    (=0) Sin compresión
                                    (=1) Compresión RLE4
                                    (=2) Compresión RLE8 */
    DWORD   biSizeImage;	    /*(4 byte)	Tamaño en bytes de la imagen */
    LONG    biXPelsPerMeter;    /*(4 byte)	Pixels por metro. Resolución horizontal */
    LONG    biYPelsPerMeter;    /*(4 byte)	Pixels por metro. Resolución vertical */
    DWORD   biClrUsed;	        /*(4 byte)	Número de índides de color utilizados.
                                Si biBitCount=24 no importa */
    DWORD   biClrImportant;	    /*(4 byte)	Colores importantes (=0 todos) */
} BITMAPINFOHEADER;

typedef struct _bitmap_header
{

    BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;
} bitmap_header;

typedef struct _color_table
{
    unsigned char b;
    unsigned char g;
    unsigned char r;
    unsigned char filler;
} color_table;

int DrawBitmap(const char *filename, unsigned int x0, unsigned int y0)
{
    FSFILE *f;
    bitmap_header bmp;
    color_table ct[16];
    unsigned int ct_len = 0;
    unsigned int bmp_len;
    long x, y;
    char b[3];

    f = FSfopen(fileName, FS_READ);
    if(f)
    {
        /* Leo las dos partes de la cabecera */
        if(FSfread(&bmp, sizeof(bitmap_header), 1, f) != 1)
        {
            FSfclose(f);
            return (-10);
        }
        ct_len = bmp.bmfh.bfOffBits;
        /* No soporto compresion */
        if(bmp.bmih.biCompression != 0)
        {
            FSfclose(f);
            return (-11);
        }            
        /* Soporto solamente 8 y 24 bits por pixel */
        if(bmp.bmih.biBitCount < 8)
        {
            FSfclose(f);
            return (-12);
        }            
        /* Si hay paleta de colores la leo */
        if(ct_len)
        {
            if(FSfread(&ct, sizeof(color_table), ct_len, f) != color_table)
            {
                FSfclose(f);
                return (-13);
            }
            
        }
        /* Leo el bitmap */
        for(y = 0; y < bmp.bmih.biHeight; y++)
        {
            /* Leo una línea */
            for(x = 0; x < bmp.bmih.biWidth; x++)
            {
                /* Leo de a un pixel */
                if(FSfread(&b, bmp.bmih.biBitCount/8, 1, f) != 1)
                {
                    FSfclose(f);
                    return (-14);
                }
                if(ct_len)
                {
                    
                }
                else
                {
                    
                }
            }
        }
    }
    return 0;
}
