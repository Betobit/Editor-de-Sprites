/*
    Editor de sprites
    Autor: Martínez Mendoza Jesús Alberto @betobitMX
*/

#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>

#define CIRCULO_TAM 14
#define HEIGHT 600
#define NCIRCULOS 9
#define WIDTH 700

typedef char String[50];

typedef struct {
    int color;
    int x;
    int y;
}TColor;

typedef struct {
    int x;
    int y;
}TBoton;

typedef struct
{
    int x;
    int y;
    String color;
}TCuadro;

void CreaUI();

/*** AREA DE COLORES ***/
void ColoresPrincipales(int xInicial, int yInicial);
void ColoresDinamicos(int xInicial, int yInicial, int color);

/*** AREA DIBUJO ***/
int  AsignaMemoria(TCuadro ***mat, int n, int m);void CreaMenu(TBoton *b);
int  CreaMatriz(TCuadro **mat, int n, int m, int x, int y); // Devuelve el tam del cuadrito
void PintaMatriz(TCuadro ***mat, int *n, int *m, int *tam); // Todo pasa por referencia para evitar un duplicado

/*** OTROS ELEMTNOS DE UI ***/
TCuadro** AbrirArchivo(String arc);
void CreaHerramientas();
void CreaMenu(TBoton *b);
void Guarda(TCuadro ***mat, int n, int m, String nombre);
void MuestraInput(String placeholder, String texto);
void VistaPrevia(TCuadro ***mat, int n, int m);


int main()
{
    TCuadro **matriz;
    int n=20, m=20, tam, i, j;
    char opcion = -1;
    String archivo;
    /*printf("\nIngresa n: ");
    scanf("%d", &n);
    printf("\nIngresa m: ");
    scanf("%d", &m);*/

    if(m>n)
    {
        tam = n;
        n = m;
        m = tam;
    }
    
    if(AsignaMemoria(&matriz, n, m))
    {
        CreaUI();
        int xm, ym, colorSel = 0;
        tam = CreaMatriz(matriz, n, m, 40, HEIGHT/10-CIRCULO_TAM);
        setfillstyle(1, WHITE);
        setlinestyle(0, 0, 3);
        rectangle(39, HEIGHT/10-CIRCULO_TAM-1, tam*n+41, HEIGHT/10-CIRCULO_TAM+tam*m+1);
        
        do
        {
            while(!ismouseclick(WM_LBUTTONDOWN));
            getmouseclick(WM_LBUTTONDOWN, &xm, &ym);
            
            // Zona de colores
            if( xm>WIDTH-150-CIRCULO_TAM && xm<WIDTH-40 && ym>HEIGHT/10-CIRCULO_TAM && ym<HEIGHT- 250 )
            {
                colorSel = getpixel(xm, ym);
                if(colorSel != 2899536)
                {
                    setcolor(COLOR(RED_VALUE(colorSel), GREEN_VALUE(colorSel), BLUE_VALUE(colorSel)));
                    setlinestyle(0, 0, 3);
                    rectangle(39, HEIGHT/10-CIRCULO_TAM-1, tam*n+41, HEIGHT/10-CIRCULO_TAM+tam*m+1);
                    if(xm < WIDTH - 80)
                        ColoresDinamicos(WIDTH-50, HEIGHT/10, colorSel);
                    setfillstyle(1, COLOR(RED_VALUE(colorSel), GREEN_VALUE(colorSel), BLUE_VALUE(colorSel)));
                }
                
            // Area de dibujo
            } else if (xm > 40 && xm <tam*n+40 && ym > HEIGHT/10-CIRCULO_TAM && ym < HEIGHT/10-CIRCULO_TAM+tam*m ) {
                setcolor(COLOR(44, 62, 80));
                setfillstyle(1, COLOR(RED_VALUE(colorSel), GREEN_VALUE(colorSel), BLUE_VALUE(colorSel)));
                setlinestyle(0, 1, 1);
                int x, y, puntos[8];
                for(i=0; i<m; i++)
                    for(j=0; j<n; j++)
                    {
                        x = (*(matriz+i)+j)->x;
                        y = (*(matriz+i)+j)->y;
                        if( xm>x && xm<x+tam && ym>y && ym<y+tam)
                        {
                            puntos[0] = (*(matriz+i)+j)->x;
                            puntos[1] = (*(matriz+i)+j)->y;
                            puntos[2] = (*(matriz+i)+j)->x+tam;
                            puntos[3] = (*(matriz+i)+j)->y;
                            puntos[4] = (*(matriz+i)+j)->x+tam;
                            puntos[5] = (*(matriz+i)+j)->y+tam;
                            puntos[6] = (*(matriz+i)+j)->x;
                            puntos[7] = (*(matriz+i)+j)->y+tam;
                            sprintf((*(matriz+i)+j)->color, "%d", colorSel);
                            i = m;
                            j = n;
                        }
                    }

                fillpoly(4, puntos);
                VistaPrevia(&matriz, n, m);
                
            // Botones de menu
            } else if (xm>0 && xm<WIDTH && ym>HEIGHT-textheight("A")*2-10) {
    
                for(i=0; i<5; i++)
                {
                    setcolor(COLOR(236, 240+i, 241));
                    if(getcolor() == getpixel(xm, ym))
                    {
                       opcion = i;
                        i = 5;
                    }
                }

                switch(opcion)
                {
                    case 0: MuestraInput("  N,  M", archivo);
                        break;
                    case 1: MuestraInput("Nombre del archivo", archivo);
                            matriz = AbrirArchivo(archivo);
                        break;
                    case 2: Guarda(&matriz, n, m, "holi");
                        break;
                    case 3: MuestraInput(" Nombre del archivo", archivo);
                            if(archivo[0]!='\0')
                                Guarda(&matriz, n, m, archivo);
                }
            // Herramientas
            } else if(xm>10 && xm<30) {
                for(i=0; i<2; i++)
                {
                    setcolor(COLOR(75, 100, 130+i));
                    if(getcolor() == getpixel(xm, ym))
                    {
                        opcion = i;
                        i = 2;
                    }
                }
                switch (opcion) {
                    case 0:
                        setcolor(COLOR(44, 62, 80));
                        colorSel = getcolor();
                        break;
                    case 1:
                        printf("\nCuadro"); break;
                }
            }
        } while (opcion !=4);
    } else
        printf("\nSin memoria");

    closegraph();
    return (0);
}

void CreaUI()
{
    initwindow(WIDTH,HEIGHT);
    setfillstyle(1,COLOR(44, 62, 80));
    setcolor(COLOR(44, 62, 80));
    bar(0, 0, WIDTH, HEIGHT);
    setlinestyle(0, 0, 6); // Crea efecto de mancha en los colores.
    ColoresPrincipales(WIDTH-150, HEIGHT/10);
    TBoton botones[4];
    CreaMenu(botones);
    CreaHerramientas();
}

/*** AREA DE COLORES ***/
void ColoresPrincipales(int xInicial, int yInicial)
{
    setlinestyle(1, 0, 3);
    char i, j;
    int colores[][3] = {
        {255, 214, 0}, // Amarillo
        {0, 248, 248},  // Azul
        {183, 103, 0},  // CafŽ
        {255, 160, 60},  // Naranja
        {234, 20, 96},  // Rosa
        {15, 146, 245}, // Azul 1
        {0, 249, 148},  // Turquesa
        {0, 191, 0},    // Verde
        {168, 255, 76}, // Verde toxico
        
        {79, 186, 138},
        {0, 0, 255},
        {255, 127, 172},
        {248, 64, 69},
        {255, 17, 21},  // Rojo
        {155, 89, 182},
        {100, 70, 255},
        {255, 166, 243},
        {255, 255, 255}
    };
    
    for(i=0; i<NCIRCULOS*2; i++)
    {
        setfillstyle(1, COLOR (colores[i][0], colores[i][1], colores[i][2]));
        if(i==9)
        {
            xInicial += 50;
            yInicial -= CIRCULO_TAM/2*45;
        }
        for(j=0; j<CIRCULO_TAM; j++)
        {
            fillellipse(xInicial, yInicial, j, j);
            delay(3);
        }
        delay(2);
        yInicial += CIRCULO_TAM/2*5;
    }
}
void ColoresDinamicos(int xInicial, int yInicial, int color)
{
    setlinestyle(1, 0, 3);
    setcolor(COLOR(44, 62, 80));
    
    char i, j, k;
    int colorRGB[3],
    tinte[3];
    colorRGB[0] = RED_VALUE(color);
    colorRGB[1] = GREEN_VALUE(color);
    colorRGB[2] = BLUE_VALUE(color);
    
    for(k=0; k<3;k++)
        tinte[k] = colorRGB[k]/10;
    
    for(i=0; i<NCIRCULOS;i++)
    {
        setfillstyle(SOLID_FILL, COLOR(colorRGB[0], colorRGB[1], colorRGB[2]));
        for(k=0; k<3;k++)
            colorRGB[k] -= tinte[k];
        
        for(j=0;j<CIRCULO_TAM;j++)
        {
            fillellipse(xInicial, yInicial, j, j);
            delay(3);
        }
        delay(1);
        yInicial += CIRCULO_TAM/2*5;
    }
}

/*** AREA DE DIBUJO ***/
int AsignaMemoria(TCuadro ***mat, int n, int m)
{
    int i, res = 1;

    *mat = (TCuadro**)malloc(sizeof(TCuadro*)*n);

    if(*mat)
        for(i=0; i<n && res==1; i++)
        {
            *(*mat + i) = (TCuadro*) malloc(sizeof(TCuadro)*m);
            if(*(*mat+i) == NULL)
            {
                res = 0;
                while(--i>0)
                    free(*(*mat+i));
                free(*mat);
            }
        }

    return res;
}

int CreaMatriz(TCuadro **mat, int n, int m, int x, int y)
{
    int i, j,
        tam = 470/n;

    setcolor(BLACK);
    setlinestyle(0, 1, 1);
    for(i=0; i<m; i++)
    {
        for(j=0; j<=n; j++)
        {
            (*(mat+i)+j)->x = x+tam*j;
            (*(mat+i)+j)->y = y;
            (*(mat+i)+j)->color[0] = '\0';
            rectangle(x, y, x+tam*j, y+tam);
        }
        x=40;
        y+=tam;
    }

    return tam;
}
void PintaMatriz(TCuadro ***mat, int *n, int *m, int *tam)
{
    int i, j, x, y, puntos[8];
    long unsigned color;
    setlinestyle(0, 1, 1);
    for(i=0; i<*m; i++)
        for(j=0; j<*n; j++)
        {
            x = (*(*mat+i)+j)->x;
            y = (*(*mat+i)+j)->y;
            puntos[0] = (*(*mat+i)+j)->x;
            puntos[1] = (*(*mat+i)+j)->y;
            puntos[2] = (*(*mat+i)+j)->x+(*tam);
            puntos[3] = (*(*mat+i)+j)->y;
            puntos[4] = (*(*mat+i)+j)->x+(*tam);
            puntos[5] = (*(*mat+i)+j)->y+(*tam);
            puntos[6] = (*(*mat+i)+j)->x;
            puntos[7] = (*(*mat+i)+j)->y+(*tam);
            color = atoi((*(*mat+i)+j)->color);
            printf("\n%s", (*(*mat+i)+j)->color);
            if(color)
            {
                setfillstyle(1, COLOR(RED_VALUE(color), GREEN_VALUE(color), BLUE_VALUE(color)));
                fillpoly(4, puntos);
            }
        }

}

/*** OTROS ELEMNTOS DE UI ***/
TCuadro** AbrirArchivo(String arc)
{
    int n, m, i, j, tam;
    FILE *f;
    TCuadro **matriz;
    sprintf(arc, "%s.dat", arc);
    f = fopen(arc, "rb");
    
    if(f)
    {
        /*read(&n, sizeof(int), 1, f);
        fread(&m, sizeof(int), 1, f);
        n*=m;*/
        fread(&**matriz, sizeof(TCuadro)*400, 1, f);
        PintaMatriz(&matriz, &n, &m, &tam);
        VistaPrevia(&matriz, n, m);
    }
    return matriz;
}
void CreaHerramientas() {
    int i;
    String herr[] = {
        "Borrar",
        "Cuadrado"
    };
    
    settextstyle(0, VERT_DIR, 1);
    setcolor(WHITE);
    for(i=0; i<sizeof(herr)/sizeof(String); i++)
    {
        setfillstyle(1, COLOR(75, 100, 130+i));
        bar(10, 45+70*i, 30, 55+70*i+textwidth(herr[i]));
        outtextxy(15, 50+i*70, herr[i]);
    }
    settextstyle(0, HORIZ_DIR, 1);
}
void CreaMenu(TBoton *b)
{
    char i;
    int xi = 50;
    String opciones[] = {"Nuevo", "Abrir", "Guardar", "Guardar como", "Salir" };
    setcolor(COLOR(231, 76, 60));//COLOR(52, 73, 94));
    settextstyle(8, HORIZ_DIR, 2);
    for(i=0; i<sizeof(opciones)/50; i++)
    {
        setbkcolor(COLOR(236, 240+i, 241));
        setfillstyle(1, COLOR(236, 240+i, 241));
        bar( (b+i)->x = xi-10, HEIGHT-textheight("A")*2-10, xi+textwidth(opciones[i])+10, HEIGHT);
        outtextxy(xi, HEIGHT-textheight("A")*2, opciones[i]);
        xi += textwidth(opciones[i])+40;
    }
}
void Guarda(TCuadro ***mat, int n, int m, String nombre)
{
    FILE *f;
    int i;
    String aux;
    sprintf(aux, "%s.dat", nombre);
    f = fopen(aux, "wb");
    if(f)
    {
        /*fwrite(&n, sizeof(int), 1, f);
        fwrite(&m, sizeof(int), 1, f);
        n*=m;*/
        fwrite(&***mat, sizeof(TCuadro), 400, f);
        sprintf(aux, "\"%s\" guardado con exito", nombre);
    }
    
    // Avisa que el archivo ha sido guardado.
    setcolor(COLOR(3, 166, 120));
    setbkcolor(COLOR(3, 166, 120));
    for(i=0; i<textheight("A")*1.8; i++)
    {
        line(WIDTH/2 - textwidth(aux)/2-2, i, WIDTH/2 + textwidth(aux)/2, i);
        delay(4);
    }
    setcolor(WHITE);
    outtextxy(WIDTH/2 - textwidth(aux)/2, 8, aux);
    delay(2000);
    setcolor(COLOR(44, 62, 80));
    for(i=textheight("A")*1.8; i>=0; i--)
    {
        line(0, i, WIDTH, i);
        delay(4);
    }
    fclose(f);
}
void MuestraInput(String placeholder, String texto)
{
    int i,
        xi = WIDTH/2-textwidth(placeholder)/2,
        y = 8,
        tecla;
    char letra[2];
    setcolor(WHITE);
    for(i=0; i<textheight("A")*2.5; i++)
    {
        line(WIDTH/2 - textwidth(placeholder)/2-2, i, WIDTH/2 + textwidth(placeholder)/2+2, i);
        delay(4);
    }
    setbkcolor(WHITE);
    setcolor(COLOR(200, 200, 200));
    outtextxy(WIDTH/2 - textwidth(placeholder)/2, 8, placeholder);
    i=0;
    do
    {
        do
        {
            setcolor(BLACK);
            outtextxy(xi, y, "_");
            delay(100);
            setcolor(WHITE);
            outtextxy(xi, y, "_");
            delay(100);
        }while(!kbhit());

        tecla = getch();
        if(tecla!=13 && tecla!='\b')
        {
            letra[0] = tecla;
            letra[1] = '\0';
            setcolor(BLACK);
            outtextxy(xi, y, letra);
            xi+=textwidth(letra);
            texto[i++] = letra[0];

        } else {
            if(tecla=='\b')
            {
                if(i>0)
                {
                    letra[0] = texto[--i];
                    letra[1] = '\0';
                    xi-=textwidth(letra);
                    outtextxy(xi, y, letra);
                } else {
                    tecla = 13;
                }
            }
        }
    }while(tecla!=13 && i<15);
    texto[i] = '\0';

    setcolor(COLOR(44, 62, 80));
    for(i=textheight("A")*2.6; i>=0; i--)
        line(0, i, WIDTH, i);
}
void VistaPrevia(TCuadro ***mat, int n, int m)
{
    int i, j,
        xi = WIDTH - 175,
        yi = HEIGHT- 235,
        tam = 140/n;
    long unsigned color = 2552555;
    setfillstyle(1, 0);
    setcolor(BLACK);
    setlinestyle(0, 1, 1);
    bar(xi, yi, xi+tam*n, yi+tam*m);
    for(i=0; i<m;i++)
    {
        for(j=0; j<n; j++)
        {
            if((*(*mat+i)+j)->color[0] != '\0')
            {
                color = atoi((*(*mat+i)+j)->color);
                if(color != 2899536)
                {
                    setfillstyle(1, COLOR(RED_VALUE(color), GREEN_VALUE(color), BLUE_VALUE(color)));
                    bar(xi, yi, xi+tam, yi+tam);
                }
            }
            xi+=tam;
        }
        xi =WIDTH - 175;
        yi+=tam;
    }
}
