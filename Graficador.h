#ifndef GRAFICADOR_H_INCLUDED
#define GRAFICADOR_H_INCLUDED

#include <iostream>
#include <winbgim.h>
#include <math.h>

struct Punto
{
    int x,y;
    Punto():x(0),y(0){}

    Punto(const Punto &p)
    {
        x=p.x;
        y=p.y;
    }

    Punto(int x,int y):x(x),y(y){}
};
typedef const Punto & cPunto;
typedef const int & cInt;

inline Punto & CambioSignoY(Punto &p, cInt dy);
inline Punto & SinCambio(Punto &p,cInt dy);
inline Punto  SinCambio(Punto p,cPunto pO);
inline Punto  Inverso(Punto p,cPunto pO);


enum Origen{ CENTRO, ESQUINASI,ESQUINASD,ESQUINAII,ESQUINAID
};


//******************************************************************************************
//******************************************************************************************
//******************************************************************************************
class Graficador
{
public:

//******************************************************************************************
    /** \brief Constructor de la grafica
     *
     * \param TAM_X Ancho de la grafica
     * \param TAM_Y Alto de la grafica
     * \param origen Posicion donde se ubica el origen
     * \param 2 cInt sangria Espacio entre el origen y el centro
     *
     */
    Graficador(cInt TAM_X=1064, cInt TAM_Y=646, Origen origen=CENTRO,cInt sangria = 8,
               colors cEj=BLACK,colors cFondo=WHITE);
//******************************************************************************************
    /** \brief Destructor
     */
    ~Graficador();


//******************************************************************************************
    /** \brief Función para pintar una linea
     *
     * \param p1 Inicio de la linea
     * \param p2 Fin de la linea
     * \param col Color de la linea
     *
     */
    void Linea(cPunto p1, cPunto p2,colors col)const ;

//******************************************************************************************
    /** \brief Función para pintar una linea
     *
     * \param r Radio del circulo
     * \param col Color de la linea
     *
     */
    void Circulo(cInt r,colors col)const ;

//******************************************************************************************
    /** \brief Función para pintar una linea
     *
     * \param r Radio del circulo
     * \param col Color de la linea
     *
     */
    void Elipse(int a, int b,colors col)const ;

//******************************************************************************************
    /** \brief Función para pintar un pixel en la grafica
     *
     * \param p Cooredenadas del pixel
     * \param BLANCO colors Color del pixel
     *
     */
    inline void PintarPixel(cPunto p ,colors color)const;


//******************************************************************************************
//******************************************************************************************
//******************************************************************************************
private:

    int MAX_X,MAX_Y;
    colors ejes,fondo;
    Punto centro;
    Punto esquinaII,esquinaSD;

//******************************************************************************************
    /** \brief Funcón para pintar los ejes del origen
     */
    void PintarOrigen() const;

    /** \brief Desplazamiento de los puntos para los puntos en una recta
     */
    inline Punto PendienteR1(cInt x, cInt y) const;

    /** \brief Desplazamiento de los puntos para los puntos en una recta
     */
    inline Punto PendienteR2(cInt x, cInt y) const;

    /** \brief Desplazamiento de los puntos para los puntos en una recta
     */
    inline Punto PendienteR3(cInt x, cInt y) const;

    /** \brief Desplazamiento de los puntos para los puntos en una recta
     */
    inline Punto PendienteR4(cInt x, cInt y) const;

    /** \brief Pinta los 8 puntos del circulo
     */
    inline void Pinta8Puntos(cInt x,cInt y,colors col) const;

    /** \brief Pinta los 4 puntos de la elispe
     */
    inline void Pinta4Puntos(cInt x,cInt y,colors col) const;

    /** \brief Pinta una linea con pendiente m -> 0 <= m <1
     */
    inline void lineaBasica(Punto &x,Punto &y,colors col,cPunto pO,int & dx, int &dy,
                                Punto &(*transf)(Punto&,cInt),Punto (*inv)(Punto,cPunto)) const;


};

#endif // GRAFICADOR_H_INCLUDED
