/*
    Editor de sprites
    Autor: Martínez Mendoza Jesús Alberto @betobitMX
*/

#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>

#define CIRCULO_TAM 14
#define HEIGHT 600
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

// AREA DE COLORES
void ColoresPrincipales(int xInicial, int yInicial);
void ColoresDinamicos(int xInicial, int yInicial, int color);
void CreaUI();

// UI
int AsignaMemoria(TCuadro ***mat, int n, int m);
void CreaMenu(TBoton *b);
int CreaMatriz(TCuadro **mat, int n, int m, int x, int y); // Devuelve el tam del cuadrito
void Guarda(TCuadro **mat, int n, int m, String nombre);
void LiberaMemoria(TCuadro **mat, int n);
void MuestraInput(String placeholder, String texto);
void VistaPrevia(TCuadro **mat, int n, int m);


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
        int colorSel = COLOR(254, 254, 254);
        tam = CreaMatriz(matriz, n, m, 40, HEIGHT/10-CIRCULO_TAM);
        setfillstyle(1, WHITE);
        
        do
        {
            while(!ismouseclick(WM_LBUTTONDOWN));
            int xm, ym;
            getmouseclick(WM_LBUTTONDOWN, &xm, &ym);
            colorSel = getpixel(xm, ym);
            
            // Zona de colores
            if( xm>WIDTH-150-CIRCULO_TAM && xm<WIDTH-40 && ym>HEIGHT/10-CIRCULO_TAM && ym<HEIGHT- 250 )
            {
                
                if(colorSel != 2899536)
                {
                    printf("\n%d", colorSel);
                    setcolor(-1);
                    setlinestyle(0, 0, 3);
                    rectangle(39, HEIGHT/10-CIRCULO_TAM-1, tam*n+41, HEIGHT/10-CIRCULO_TAM+tam*m+1);
                    if(xm < WIDTH - 80)
                        ColoresDinamicos(WIDTH-50, HEIGHT/10, colorSel);
                    setfillstyle(1, 5);
                }
            // Area de dibujo
            } else if (xm > 40 && xm <tam*n+40 && ym > HEIGHT/10-CIRCULO_TAM && ym < HEIGHT/10-CIRCULO_TAM+tam*m ) {
                setcolor(4);
                // Falta optimizar un monton, pero deadline is coming.... :I
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
                VistaPrevia(matriz, n, m);
                setfillstyle(1, colorSel);
            // Botones
            } else if (xm>0 && xm<WIDTH && ym>HEIGHT-textheight("A")*2-10) {
    
                for(i=0; i<5; i++)
                {
                    COLOR(236, 240+i, 241);
                    if(current_rgb_colour ==  getpixel(xm, ym))
                       opcion = i;
                }

                switch(opcion)
                {
                    case 0: MuestraInput(" N, M", archivo); break;
                    case 1: printf("ABRIR"); break;
                    case 2: Guarda(matriz, n, m, "holi");break;
                    case 3: MuestraInput(" Nombre del archivo", archivo);
                            if(archivo[0]!='\0')
                                Guarda(matriz, n, m, archivo);
                }
            }
        } while (opcion !=4);
    } else
        printf("\nSin memoria");

    closegraph();//LiberaMemoria(matriz, n);
    return (0);
}

int AsignaMemoria(TCuadro ***mat, int n, int m)
{
    int res = 1,i;

    *mat = (TCuadro**)malloc(sizeof(TCuadro*)*n);

    if(*mat)
    {
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
    }

    return res;
}
/******************************************
                COLORES
******************************************/
void ColoresPrincipales(int xInicial, int yInicial)
{
    setlinestyle(1, 0, 3);
    setcolor(COLOR(44, 62, 80));
    char j,
         i,
         numeroCirculos = 18;
    int colores[][3] = {
        {255, 214, 46}, // Amarillo
        {67, 30, 108},  // Morado
        {94, 52, 28},   // Café
        {254, 51, 28},  // Naranja
        {234, 20, 96},  // Rosa
        {15, 146, 245}, // Azul 1
        {11, 73, 112},  // Azul rey
        {0, 191, 0},    // Verde fuerte
        {0, 128, 0},    // Verde claro
        
        {79, 186, 138},
        {255, 206, 109},
        {255, 90, 60},
        {248,64, 69},
        {255, 17, 21},  // Rojo
        {155, 89, 182},
        {236, 240, 241},
        {127, 140, 141}
    };

    for(i=0; i<numeroCirculos;i++)
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
    
    char i, j, k,
         numeroCirculos = 9;
    int colorRGB[3],
        tinte[3];
    colorRGB[0] = RED_VALUE(color);
    colorRGB[1] = GREEN_VALUE(color);
    colorRGB[2] = BLUE_VALUE(color);
    
    for(k=0; k<3;k++)
        tinte[k] = colorRGB[k]/9;
    
    for(i=0; i<numeroCirculos;i++)
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
            rectangle(x, y, x+tam*j, y+tam);
        }
        x=40;
        y+=tam;
    }

    return tam;
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

void Guarda(TCuadro **mat, int n, int m, String nombre)
{
    FILE *f;
    int i, j;
    String aux;
    sprintf(aux, "%s.dat", nombre);
    f = fopen(aux, "wt");
    if(f)
    {
         fprintf(f,"%s\n",nombre);
         fprintf(f,"%d\n",n);
         fprintf(f,"%d\n",m);
         for(i=0; i<n; i++)
             for(j=0; j<m; j++)
             {
                 TCuadro cuadro = *(*(mat+i)+j);
                 fprintf(f,"%d %d %s\n",cuadro.x, cuadro.y, cuadro.color);
             }

        sprintf(aux, "\"%s\" guardado con exito", nombre);
    } else
        sprintf(aux, "No existe el  archivo\" %s\" ", nombre);

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

void LiberaMemoria(TCuadro **mat, int n)
{
    int i;

    for(i=0; i<n; i++)
        free(*(mat+i));
    free(mat);
}

void MuestraInput(String placeholder, String texto)
{
    int i,
        xi = WIDTH/2-textwidth(placeholder)/2,
        y = 8,
        tecla;
    char letra[2];
    setcolor(WHITE);
    for(i=0; i<textheight("A")*1.3; i++)
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
    for(i=textheight("A")*1.8; i>=0; i--)
        line(0, i, WIDTH, i);
}
void VistaPrevia(TCuadro **mat, int n, int m)
{
    int i, j,
        xi = WIDTH - 175,
        yi = HEIGHT- 235,
        tam = 140/n;
    setcolor(BLACK);
    setlinestyle(0, 1, 1);
    bar(xi, yi, xi+tam*n, yi+tam*m);

    for(i=0; i<m;i++)
    {
        for(j=0; j<n; j++)
        {
            if((*(mat+i)+j)->color)
            {
                setfillstyle(1, atoll((*(mat+i)+j)->color));
                bar(xi, yi, xi+tam, yi+tam);
            }
            xi+=tam;
        }
        xi =WIDTH - 175;
        yi+=tam;
    }
}
