// JuegoEnemigosV2GST.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>

using namespace std;

int primerabaraja = 0;
string palos[4] = { "Picas", "Rombos", "Treboles", "Corazones" };
string valor[13] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
int puntuacion[13] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11 };
int arrayBaraja[4][13] = {};
bool cartaCorrecta = false;
int puntuacionJugador = 0;
int puntuacionCrupier = 0;
char opcion_carta = '0';
int plantarse = 0;


bool testHasPerdido()
{
    if (puntuacionJugador > 21) {
        return true;
    }

    else {
        return false;
    }
}

void Registro()
{
    cout << "\n¡BIENVENIDX A BLACKJACK WRX! \n \n";
    string characterName;
    cout << "Introduce un nombre de usuario: ";
    cin >> characterName;
}

struct Carta
{
    string palo;
    string valor;
    int puntuacion;
};

void rellenarArray()
{
    for (int i = 0; i < 4; i++)
    {
        for (int y = 0; y < 13; y++)
        {
            arrayBaraja[i][y] = 1;
        }
    }
}

Carta repartirCarta()
{
    int randPalo = 0;
    int randCarta = 0;
    cartaCorrecta = false;
    while (!cartaCorrecta)
    {
        randPalo = rand() % 4;
        randCarta = rand() % 13;
        if (arrayBaraja[randPalo][randCarta] == 1)
        {
            cartaCorrecta = true;
            arrayBaraja[randPalo][randCarta] = 0;
        }
    }

    Carta carta = Carta();
    carta.palo = palos[randPalo];
    carta.valor = valor[randCarta];
    carta.puntuacion = puntuacion[randCarta];

    return carta;
}

bool decisiones()
{
    cout << "Selecciona la jugada: \nS = Carta Extra \nN = Plantarse\n";

    cin >> opcion_carta;
    opcion_carta = tolower(opcion_carta);

    if (opcion_carta == 's') {
        return true;
    }
    else if (opcion_carta == 'n') {
        return false;
    }
    else if (puntuacionJugador == 21) {
        return false;
    }

    else {
        cout << "Opcion incorrecta, escoge S o N";
    }

    return false;
}

int main()
{
    srand(time(NULL));
    rellenarArray();
    Registro();
    cout << "\nPERFECTO, YA PUEDES EMPEZAR A JUGAR!!\n \n";
    cout << "\n" << "Crupier reparte la primera braraja: \n";
    Carta carta = repartirCarta();
    puntuacionJugador += carta.puntuacion;
    cout << "Tu primera carta es un " << carta.valor << " " << carta.palo << " (" << puntuacionJugador << " puntos)\n";
    carta = repartirCarta();
    puntuacionCrupier += carta.puntuacion;
    cout << "La primera carta del crupier es un " << carta.valor << " " << carta.palo << " (" << puntuacionCrupier << " puntos)\n";
    carta = repartirCarta();
    puntuacionJugador += carta.puntuacion;
    cout << "Crupier te reparte una segunda carta con valor: " << carta.valor << " " << carta.palo << " (" << puntuacionJugador << " puntos)\n";

    while (decisiones()) {
        carta = repartirCarta();
        puntuacionJugador += carta.puntuacion;
        cout << "La carta solicitada es igual a: " << carta.valor << " " << carta.palo << " (" << puntuacionJugador << " puntos)\n";
        if (puntuacionJugador > 21) {
            cout << "Te has pasado de puntuacion, el crupier ha ganado la partida.\n";
            break;
        }
        else if (puntuacionJugador == 21) {
            puntuacionCrupier += carta.puntuacion;
            carta = repartirCarta();
            cout << "El crupier se reparte una carta equivalente a: " << carta.valor << " " << carta.palo << " (" << puntuacionCrupier << " puntos)\n";
            if (puntuacionCrupier > 21)
                cout << "La puntuacion del crupier se ha pasado, por lo tanto has ganado.";
            break;
        }
    }

    if (testHasPerdido() == false)
    {
        carta = repartirCarta();
        puntuacionCrupier += carta.puntuacion;
        cout << "El crupier se reparte otra carta con valor " << carta.valor << " " << carta.palo << " (" << puntuacionCrupier << " puntos)\n";

        if (puntuacionCrupier > puntuacionJugador && puntuacionCrupier <= 21) {
            cout << "El crupier tiene una puntuación mayor, has perdido!\n";
        }

        else if (puntuacionCrupier <= 21) {

            while (puntuacionCrupier < 21) {
                carta = repartirCarta();
                puntuacionCrupier += carta.puntuacion;
                cout << "El crupier se reparte otra carta con valor " << carta.valor << " " << carta.palo << " (" << puntuacionCrupier << " puntos)\n";

                if (puntuacionCrupier > 21) {
                    cout << "La puntuacion del crupier se ha pasado, has ganado!\n";
                    break;
                }
            }
        }
    }
}