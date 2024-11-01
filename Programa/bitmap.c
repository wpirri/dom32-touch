/***************************************************************************
    Copyright (C) 2024   Walter Pirri

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
***************************************************************************/
#include "bitmap.h"

#include <stdint.h>

#include "sd/fsio.h"
#include "display/display.h"
#include "log.h"

#pragma pack(push, 1)
typedef struct _BITMAPFILEHEADER
{
	uint16_t bfType;         /* (2 byte)	 Tipo de archivo, vale 'BM' */
	uint32_t bfSize;		 /* (4 byte)	 Tamaño del archivo en bytes. */
	uint16_t bfReserved1;	 /* (2 byte)	 Reservado. Todo ceros. */
	uint16_t bfReserved2;	 /* (2 byte)	 Reservado. Todo ceros. */
	uint32_t bfOffBits;	     /* (4 byte)	 Distancia en bytes entre BITMAPINFOHEADER y 
						       el mapa de bits (aBitmapBits[])
						       Si vale cero, significa que la estructura
						       RGBQUAD no está presente. No hay paleta
						       de colores. */
} BITMAPFILEHEADER;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _BITMAPINFOHEADER
{
    uint32_t biSize;		    /* (4 byte) Numero de bytes que ocupa esta estructura. */
    uint32_t biWidth;	        /* (4 byte) Anchura del bitmap */
    uint32_t biHeight;	        /* (4 byte) Altura del bitmap */
    uint16_t biPlanes;	        /* (2 byte) Numero de planos de color (siempre 1) */
    uint16_t biBitCount;        /* (2 byte) Bits por pixel (1,4,8,24) */
    uint32_t biCompression;	    /* (4 byte)	Compresion utilizada
                                    (=0) Sin compresión
                                    (=1) Compresión RLE4
                                    (=2) Compresión RLE8 */
    uint32_t biSizeImage;	    /*(4 byte) Tamaño en bytes de la imagen */
    uint32_t biXPelsPerMeter;   /*(4 byte) Pixels por metro. Resolución horizontal */
    uint32_t biYPelsPerMeter;   /*(4 byte) Pixels por metro. Resolución vertical */
    uint32_t biClrUsed;	        /*(4 byte) Numero de índides de color utilizados.
                                            Si biBitCount=24 no importa */
    uint32_t biClrImportant;	/*(4 byte) Colores importantes (=0 todos) */
} BITMAPINFOHEADER;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _bitmap_header
{

    BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;
} bitmap_header;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _color_table
{
    unsigned char b;
    unsigned char g;
    unsigned char r;
    unsigned char filler;
} color_table;
#pragma pack(pop)

int DrawBitmapTransparent(const char *filename, unsigned int x0, unsigned int y0)
{
    FSFILE *f;
    bitmap_header bmp;
    long x, y;
    unsigned char b[3];
    
    Log("[DrawBitmap] X: %u Y: %u file: %s", x0, y0, filename);
    
    f = FSfopen(filename, FS_READ);
    if(f)
    {
        /* Leo las dos partes de la cabecera */
        if(FSfread(&bmp, sizeof(bitmap_header), 1, f) != 1)
        {
            Log("[DrawBitmap] Error al leer HEADER de %s", filename);
            FSfclose(f);
            return (-10);
        }

        /* mime-type */
        if(bmp.bmfh.bfType != 0x4d42)
        {
            Log("[DrawBitmap] Archivo %s con formato invalido", filename);
            FSfclose(f);
            return (-11);
        }            
        /* No soporto compresion */
        if(bmp.bmih.biCompression != 0)
        {
            Log("[DrawBitmap] Compresion %lu no soportada para %s", bmp.bmih.biCompression, filename);
            FSfclose(f);
            return (-12);
        }            
        /* Soporto solamente 8 y 24 bits por pixel */
        if(bmp.bmih.biBitCount < 24)
        {
            Log("[DrawBitmap] %lu bits por pixel no soportado en %s", bmp.bmih.biBitCount, filename);
            FSfclose(f);
            return (-13);
        }            
        /* Si est� especificado un offset lo uso */
        if(bmp.bmfh.bfOffBits)
        {
            if(FSfseek(f, bmp.bmfh.bfOffBits, SEEK_SET) != 0)
            {
                Log("[DrawBitmap] Error al posicionarse en el mapa de bits de %s", filename);
                FSfclose(f);
                return (-14);
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
                    Log("[DrawBitmap] Error al leer mapa de bits de %s", filename);
                    FSfclose(f);
                    return (-15);
                }
                if(bmp.bmfh.bfOffBits)
                {
                    if(bmp.bmih.biBitCount == 24)
                    {
                        //if(b[0] != 0xFF || b[1] != 0xFF || b[2] != 0xFF)
                        if(b[0] != 0x00 || b[1] != 0x00 || b[2] != 0x00)
                        {
                            DrawPixel(x0+x, y0+bmp.bmih.biHeight-y, RGB(b[2],b[1],b[0]));
                        }
                    }
                    /* TODO: Uso paleta de colores */
                    
                }
                else
                {
                    if(bmp.bmih.biBitCount == 24)
                    {
                        //if(b[0] != 0xFF || b[1] != 0xFF || b[2] != 0xFF)
                        if(b[0] != 0x00 || b[1] != 0x00 || b[2] != 0x00)
                        {
                            DrawPixel(x0+x, y0+bmp.bmih.biHeight-y, RGB(b[2],b[1],b[0]));
                        }
                    }
                    /* TODO: bits por pixel <> de 24 */
                }
            }
        }
        FSfclose(f);
    }
    else
    {
        Log("[DrawBitmap] Error al abrir %s", filename);
    }
    return 0;
}

int DrawBitmap(const char *filename, unsigned int x0, unsigned int y0)
{
    FSFILE *f;
    bitmap_header bmp;
    long x, y;
    unsigned char b[3];
    
    Log("[DrawBitmap] X: %u Y: %u file: %s", x0, y0, filename);
    
    f = FSfopen(filename, FS_READ);
    if(f)
    {
        /* Leo las dos partes de la cabecera */
        if(FSfread(&bmp, sizeof(bitmap_header), 1, f) != 1)
        {
            Log("[DrawBitmap] Error al leer HEADER de %s", filename);
            FSfclose(f);
            return (-10);
        }

        /* mime-type */
        if(bmp.bmfh.bfType != 0x4d42)
        {
            Log("[DrawBitmap] Archivo %s con formato invalido", filename);
            FSfclose(f);
            return (-11);
        }            
        /* No soporto compresion */
        if(bmp.bmih.biCompression != 0)
        {
            Log("[DrawBitmap] Compresion %lu no soportada para %s", bmp.bmih.biCompression, filename);
            FSfclose(f);
            return (-12);
        }            
        /* Soporto solamente 8 y 24 bits por pixel */
        if(bmp.bmih.biBitCount < 24)
        {
            Log("[DrawBitmap] %lu bits por pixel no soportado en %s", bmp.bmih.biBitCount, filename);
            FSfclose(f);
            return (-13);
        }            
        /* Si est� especificado un offset lo uso */
        if(bmp.bmfh.bfOffBits)
        {
            if(FSfseek(f, bmp.bmfh.bfOffBits, SEEK_SET) != 0)
            {
                Log("[DrawBitmap] Error al posicionarse en el mapa de bits de %s", filename);
                FSfclose(f);
                return (-14);
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
                    Log("[DrawBitmap] Error al leer mapa de bits de %s", filename);
                    FSfclose(f);
                    return (-15);
                }
                if(bmp.bmfh.bfOffBits)
                {
                    if(bmp.bmih.biBitCount == 24)
                    {
                        DrawPixel(x0+x, y0+bmp.bmih.biHeight-y, RGB(b[2],b[1],b[0]));
                    }
                    /* TODO: Uso paleta de colores */
                    
                }
                else
                {
                    if(bmp.bmih.biBitCount == 24)
                    {
                        DrawPixel(x0+x, y0+bmp.bmih.biHeight-y, RGB(b[2],b[1],b[0]));
                    }
                    /* TODO: bits por pixel <> de 24 */
                }
            }
        }
        FSfclose(f);
    }
    else
    {
        Log("[DrawBitmap] Error al abrir %s", filename);
    }
    return 0;
}

unsigned int GetBitmapW(const char *filename)
{
    FSFILE *f;
    bitmap_header bmp;

    f = FSfopen(filename, FS_READ);
    if(f)
    {
        /* Leo las dos partes de la cabecera */
        if(FSfread(&bmp, sizeof(bitmap_header), 1, f) == 1)
        {
            FSfclose(f);
            return bmp.bmih.biWidth;
        }
        FSfclose(f);
    }
    return 0;
}

unsigned int GetBitmapH(const char *filename)
{
    FSFILE *f;
    bitmap_header bmp;

    f = FSfopen(filename, FS_READ);
    if(f)
    {
        /* Leo las dos partes de la cabecera */
        if(FSfread(&bmp, sizeof(bitmap_header), 1, f) == 1)
        {
            FSfclose(f);
            return bmp.bmih.biHeight;
        }
        FSfclose(f);
    }
    return 0;
}
