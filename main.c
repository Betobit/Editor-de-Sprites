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
    int n;
    int m;
    int **matriz; //x,y del elemento
}TMatriz;

// AREA DE COLORES
void ColoresPrincipales(int xInicial, int yInicial);
void ColoresDinamicos(int xInicial, int yInicial, int *color);
void CreaUI();

// UI
void CreaMenu(TBoton *b);
int CreaMatriz(TMatriz *m, int x, int y);

int main()
{
    TMatriz matriz = {15, 15, NULL};
    CreaUI();

    char opcion = -1;
    int colorSel;
    int tam = CreaMatriz(&matriz, 40, HEIGHT/10-CIRCULO_TAM);

    do
    {
        while(!ismouseclick(WM_LBUTTONDOWN));
        int xm, ym;
        getmouseclick(WM_LBUTTONDOWN, xm, ym);

        // Zona de colores
        if( xm > WIDTH-150 - CIRCULO_TAM && xm < WIDTH - 40 &&
            ym > HEIGHT/10 - CIRCULO_TAM && ym < HEIGHT - 250)
        {
            colorSel = getpixel(xm, ym);
            if(colorSel != 55590444)
            {
                setcolor(colorSel);
                setlinestyle(0, 1, 4);
                rectangle(40, HEIGHT/10-CIRCULO_TAM, tam*matriz.n+40, HEIGHT/10-CIRCULO_TAM+tam*matriz.m);
                ColoresDinamicos(WIDTH-50, HEIGHT/10, &colorSel);
            }
        } else if (xm > 40 && xm <tam*matriz.n+40 && ym > HEIGHT/10-CIRCULO_TAM && ym < HEIGHT/10-CIRCULO_TAM+tam*matriz.m   ) {
            setcolor(colorSel);
            bar(xm, ym,xm+40, ym+40);
        }
        // Zona de colores
    } while (opcion == -1);
    printf("fin");
    getch();
    return (0);
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
    int colores[] = {
        COLOR(255, 214, 46), // Amarillo
        COLOR(67, 30, 108),  // Morado
        COLOR(94, 52, 28),   // Café
        COLOR(254, 51, 28),  // Naranja
        COLOR(234, 20, 96),  // Rosa
        COLOR(15, 146, 245), // Azul 1
        COLOR(11, 73, 112),  // Azul rey
        COLOR(0, 191, 0),    // Verde fuerte
        COLOR(0, 128, 0),    // Verde claro

        COLOR(79, 186, 138),
        COLOR(255, 206, 109),
        COLOR(255, 90, 60),
        COLOR(248,64, 69),
        COLOR(255, 17, 21),  // Rojo
        COLOR(155, 89, 182),
        COLOR(236, 240, 241),
        COLOR(127, 140, 141)
    };

    for(i=0; i<numeroCirculos;i++)
    {
        setfillstyle(1, colores[i]);
        if(i==9)
        {
            xInicial += 50;
            yInicial -= (CIRCULO_TAM/2*5)*9;
        }
        for(j=0; j<CIRCULO_TAM; j++)
        {
            fillellipse(xInicial, yInicial, j, j);
            //delay(6);
        }
        //delay(4);
        yInicial += CIRCULO_TAM/2*5;
    }
}
void ColoresDinamicos(int xInicial, int yInicial, int *color)
{
    setlinestyle(1, 0, 3);
    char j,
         i,
         numeroCirculos = 9;

    setcolor(COLOR(44, 62, 80));
    int part[] = { color[0]/9, color[1]/9, color[2]/9 };
    for(i=0; i<numeroCirculos;i++)
    {
        setfillstyle(1, *color-=24);
        for(j=0;j<CIRCULO_TAM;j++)
        {
            fillellipse(xInicial, yInicial, j, j);
            delay(5);
        }
        delay(10);
        yInicial += CIRCULO_TAM/2*5;
    }
}

void CreaUI()
{
    initwindow(WIDTH,HEIGHT,"Editor de Sprites");
    setfillstyle(1,COLOR(44, 62, 80));
    setcolor(COLOR(44, 62, 80));
    bar(0, 0, WIDTH, HEIGHT);
    setlinestyle(0, 0, 6); // Crea efecto de mancha en los colores.
    ColoresPrincipales(WIDTH-150, HEIGHT/10);
    TBoton botones[4];
    CreaMenu(botones);
}

int CreaMatriz(TMatriz *m, int x, int y)
{
    int i, j,
        tam = 470/m->n;

    setcolor(BLACK);
    setlinestyle(0, 1, 1);
    for(i=0; i<m->m; i++)
    {
        for(j=0; j<=m->n; j++)
        {
            rectangle(x, y, x+tam*j, y+tam);
        }
        x = 40;
        y+=tam;
    }

    return tam;
}

void CreaMenu(TBoton *b)
{
    char i;
    int xi = 50;
    String opciones[] = {"Nuevo", "Abrir", "Guardar", "Salir" };
    setbkcolor(0x0066F4);
    setfillstyle(1, 0x0066F4);
    setcolor(0x003988);
    settextstyle(2, HORIZ_DIR, 8);
    for(i=0; i<sizeof(opciones)/50; i++)
    {
        bar( (b+i)->x = xi-10, HEIGHT-textheight("A")*2-10, xi+textwidth(opciones[i])+10, HEIGHT);
        outtextxy(xi, HEIGHT-textheight("A")*2, opciones[i]);
        xi += textwidth(opciones[i])+40;
    }
}
