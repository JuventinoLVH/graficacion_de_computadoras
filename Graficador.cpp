#include "Graficador.h"

//******************************************************************************************
Graficador::Graficador(cInt TAM_X/*=1064*/, cInt TAM_Y/*=846*/,Origen c/*=CENTRO*/
        ,cInt sangria /*8*/,colors cEj/*=NEGRO*/,colors cFondo/*BLANCO*/)
        : MAX_X(TAM_X-1),MAX_Y(TAM_Y-1),ejes(cEj),fondo(cFondo)
{
    initwindow(TAM_X,TAM_Y);
    setcolor (cEj);
    setbkcolor (cFondo);
    cleardevice();
    switch(c)
    {
        case CENTRO:
            this->centro = Punto(MAX_X/2,MAX_Y/2);
            esquinaII = Punto(-(MAX_X-centro.x),-(MAX_Y-centro.y));
            esquinaSD = Punto(MAX_X-centro.x , MAX_Y-centro.y);
            break;

        case ESQUINAID:
            this->centro = Punto( MAX_X-sangria , sangria);
            esquinaII = Punto(-(MAX_X-sangria),-(sangria));
            esquinaSD = Punto(sangria , MAX_Y-sangria);
            break;

        case ESQUINAII:
            this->centro = Punto( sangria , sangria);
            esquinaII = Punto(-sangria,-sangria);
            esquinaSD = Punto(MAX_X-centro.x , MAX_Y-centro.y);
            break;

        case ESQUINASD:
            this->centro = Punto( MAX_X-sangria , MAX_Y-sangria);
            esquinaII = Punto(-(MAX_X-sangria),-(MAX_Y-sangria));
            esquinaSD = Punto(sangria , sangria);
            break;

        default:/*ESQUINASI:*/
            this->centro = Punto(sangria , MAX_Y-sangria);
            esquinaII = Punto(-(sangria),-(MAX_Y-sangria));
            esquinaSD = Punto(MAX_X-sangria , sangria);
            break;
    }

    PintarOrigen();
}

//******************************************************************************************
Graficador::~Graficador()
{
    closegraph();
}


//******************************************************************************************
void Graficador::Linea(cPunto p1, cPunto p2,colors col) const
{
    Punto &(* trans)(Punto&,cInt) = SinCambio;
    Punto (* inv)(Punto,cPunto)= SinCambio;

    Punto P1,P2;
    P1 = (p1.x<=p2.x? p1:p2);
    P2 = (p1.x>p2.x? p1:p2);

    if(P1.y >P2.y )
    {
        int disY= (P1.y - P2.y)*2;
        P2.y = P2.y+disY;
        trans = CambioSignoY;
    }

    int dx = P2.x - P1.x;
    int dy = P2.y - P1.y;
    if(dy > dx)
    {
        inv = Inverso;

        P2.x=P1.x+dy;
        P2.y=P1.y+dx;

        dx = P2.x - P1.x;
        dy = P2.y - P1.y;
    }
    Punto PO(P1);
    lineaBasica(P1,P2,col,PO,dx,dy,trans,inv);

}

//******************************************************************************************
void Graficador::Circulo(cInt r,colors col) const
{

    int fin = (r/sqrt(2));

    int d=1-r;
    int este=3;
    int suroeste=-2*r +5;

    int x=0;
    int y=r;

    Pinta8Puntos(0,r,col);
    while(x<=fin)
    {
        if(d<0)
        {
            d = d+este;
            este = este+2;
            suroeste = suroeste+2;
            x = x+1;
        }
        else
        {
            d= d+suroeste;
            este=este+2;
            suroeste= suroeste+4;
            x = x+1;
            y = y-1;
        }
        Pinta8Puntos(x,y,col);
    }
}

//******************************************************************************************
void Graficador::Elipse(int a, int b,colors col) const
{

    long long powa = a*a;
    long long powb = b*b;
    long long d=powb-powa*b+(powa/4);

    long long x=0;
    long long y=b;

    Pinta4Puntos(x,y,col);
    while(powa*(y-0.5) > powb*(x+1))
    {
        if(d<0)
        {
            d = d+powb*(2*x+3);
            x = x+1;
        }
        else
        {
            d= d+powb*(2*x+3)+powa*(-2*y+2);
            x = x+1;
            y = y-1;
        }
        Pinta4Puntos(x,y,col);
    }

    d=powb*pow(double(x+0.5),2)+powa*pow(y-1,2)-powa*powb;
    while(y>0)
    {
        Pinta4Puntos(x,y,col);
        if(d<0)
        {
            d = d+powb*(2*x+2)+powa*(-2*y+3);
            x = x+1;
            y = y-1;
        }
        else
        {
            d= d+   powa*(-2*y+3);
            y = y-1;
        }
    }
    Pinta4Puntos(x,y,col);
}


//******************************************************************************************
inline void Graficador::PintarPixel(cPunto p,colors color) const
{
    putpixel(p.x+centro.x,MAX_Y-(p.y+centro.y),color);
}

void Graficador::PintarOrigen() const
{
    Linea(Punto(esquinaII.x,0),Punto(esquinaSD.x,0),RED);
    Linea(Punto(0,esquinaII.y),Punto(0,esquinaSD.y),GREEN);


    for(int i=esquinaII.x;i<esquinaSD.x;i+=10)
        Linea(Punto(0,0),Punto(i,esquinaII.y) , GREEN);

    for(int i=esquinaII.y;i<esquinaSD.y;++i)
        Linea(Punto(0,0),Punto(esquinaSD.x,i) , colors((i%6)+4));

    for(int i=esquinaSD.x;i>esquinaII.x;--i)
        Linea(Punto(0,0),Punto(i,esquinaSD.y) , colors((i%6)+4));

    for(int i=esquinaSD.y;i>esquinaII.y;--i)
        Linea(Punto(0,0),Punto(esquinaII.x,i) , colors((i%6)+4));

    //Linea(Punto(0,0) , esquinaSD,GREEN);
    //Linea(esquinaII, Punto(0,0),LIGHTRED);
    //Linea(Punto(0,0) , Punto(esquinaII.x,esquinaSD.y),BLUE);
    //Linea(Punto(esquinaSD.x,esquinaII.y) , Punto(0,0),CYAN);



}

inline void Graficador::Pinta8Puntos(cInt x,cInt y,colors col) const
{
    Pinta4Puntos(x,y,col);
    Pinta4Puntos(y,x,col);
}

inline void Graficador::Pinta4Puntos(cInt x,cInt y,colors col) const
{
    PintarPixel(Punto(-x,y),col);
    PintarPixel(Punto(x,-y),col);
    PintarPixel(Punto(x,y),col);
    PintarPixel(Punto(-x,-y),col);
}

inline void Graficador::lineaBasica(Punto &p1, Punto &p2,colors col,cPunto pO,
    int & dx, int &dy,Punto &(*transf)(Punto&,cInt),Punto (*inv)(Punto,cPunto)) const
{

    int este = 2*dy;
    int noroeste = 2*(dy-dx);
    int d = (2*dy)-dx;

    Punto a=inv(p1,pO);
    PintarPixel(transf(a,pO.y),col);
    while(p1.x<=p2.x)
    {
        if(d<0)
        {
            ++p1.x;
            d+=este;
        }
        else
        {
            ++p1.x;
            ++p1.y;
            d+=noroeste;
        }
        a=inv(p1,pO);
        PintarPixel(transf(a,pO.y),col);
    }
}

inline Punto  &CambioSignoY(Punto &p,cInt dy)
{
    p.y = p.y-(p.y-dy)*2;
    return p;
}

inline Punto  &SinCambio(Punto &p, cInt dy)
{
    return p;
}

inline Punto SinCambio(Punto p,cPunto pO)
{
    return p;
}

int _x;
int _y;
inline Punto Inverso(Punto p,cPunto pO)
{
    _x = p.x-pO.x;
    _y =p.y-pO.y;
    p.x=pO.x + _y;
    p.y=pO.y + _x;
    return p;
}
