#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

//move cursor na posicao indicada
void posicaoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// limpa tela e volta o cursor a posição original
void limpa(void) {
    HANDLE TELA;
    DWORD ESCRITA = 0;
    COORD POS;
    TELA = GetStdHandle(STD_OUTPUT_HANDLE);
    POS.X = 0;
    POS.Y = 0;
    FillConsoleOutputCharacter(TELA, 32, 100 * 100, POS, &ESCRITA);
    posicaoXY(0, 0);
}

char matriz[3][3];

struct players {
    string nome;
    bool chave = true;
    char jogada;
    int pontos = 0;
};

players jogador1, jogador2;

void cabecalho(void) {
    cout << " Desenvolvido por Ricardo da Gloria" << endl;
    cout << "              JOGO DA              " << endl;
    cout << " XX  XX XXXXX XX    XX   XX    XX " << endl;
    cout << " XX  XX XX    XX    XX   XX   X  X" << endl;
    cout << " XX  XX XXXXX XX    XXXXXXX  XX  XX" << endl;
    cout << "  X  X  XX    XX    XX   XX  XXXXXX" << endl;
    cout << "   XX   XXXXX XXXXX XX   XX  XX  XX" << endl;
}

void tracajogo(void) {
    posicaoXY(12, 8);
    cout << matriz[2][0] << "  | " << matriz[2][1] << " |  " << matriz[2][2] << endl;
    posicaoXY(12, 9);
    cout << "---|---|---" << endl;
    posicaoXY(12, 10);
    cout << matriz[1][0] << "  | " << matriz[1][1] << " |  " << matriz[1][2] << endl;
    posicaoXY(12, 11);
    cout << "---|---|---" << endl;
    posicaoXY(12, 12);
    cout << matriz[0][0] << "  | " << matriz[0][1] << " |  " << matriz[0][2] << endl;
}

void instrucao(void) {
    posicaoXY(12, 8);
    cout << "7" << "  | " << "8" << " |  " << "9" << endl;
    posicaoXY(12, 9);
    cout << "---|---|---" << endl;
    posicaoXY(12, 10);
    cout << "4" << "  | " << "5" << " |  " << "6" << endl;
    posicaoXY(12, 11);
    cout << "---|---|---" << endl;
    posicaoXY(12, 12);
    cout << "1" << "  | " << "2" << " |  " << "3" << endl;
    posicaoXY(1, 14);
    cout << "Utilize o teclado numerico para fazer as jogadas. . .";
    posicaoXY(1, 15);
    cout << "Aperte qualquer tecla para comecar!!!";
    cin.get();
}

void esvazia(void) {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++)
            matriz[i][j] = ' ';
    }
}

void jogadores(void) {
    cout << endl;
    cout << "Entre o nome do jogador 1: ";
    getline(cin, jogador1.nome);
    jogador1.jogada = 'X';
    cout << "Entre o nome do jogador 2: ";
    getline(cin, jogador2.nome);
    jogador2.jogada = 'O';
    cout << endl;
}

void poenome(void) {
    posicaoXY(3, 14);
    cout << jogador1.nome << " jogue com <X>" << endl;
    posicaoXY(3, 15);
    cout << jogador2.nome << " jogue com <O>" << endl;
    posicaoXY(3, 17);
    cout << jogador1.nome << ": " << jogador1.pontos << endl;
    posicaoXY(3, 18);
    cout << jogador2.nome << ": " << jogador2.pontos << endl;
}

void addpontos(void) {
    if(jogador1.chave)
        jogador1.pontos++;
    else
        jogador2.pontos++;
}

bool verificador(char jogada) {
    //verticais
    if (matriz[0][0] == jogada and matriz[0][1] == jogada and matriz[0][2] == jogada)
        return true;
    if (matriz[1][0] == jogada and matriz[1][1] == jogada and matriz[1][2] == jogada)
        return true;
    if (matriz[2][0] == jogada and matriz[2][1] == jogada and matriz[2][2] == jogada)
        return true;

    //horizontais
    if (matriz[2][0] == jogada and matriz[1][0] == jogada and matriz[0][0] == jogada)
        return true;
    if (matriz[2][1] == jogada and matriz[1][1] == jogada and matriz[0][1] == jogada)
        return true;
    if (matriz[2][2] == jogada and matriz[1][2] == jogada and matriz[0][2] == jogada)
        return true;

    //diagonais
    if (matriz[0][0] == jogada and matriz[1][1] == jogada and matriz[2][2] == jogada)
        return true;
    if (matriz[2][0] == jogada and matriz[1][1] == jogada and matriz[0][2] == jogada)
        return true;

    return false;
}

void porjogada(int jogada, char jogadaJogador) {
    if(jogada == 1)
        matriz[0][0] = jogadaJogador;
    if(jogada == 2)
        matriz[0][1] = jogadaJogador;
    if(jogada == 3)
        matriz[0][2] = jogadaJogador;
    if(jogada == 4)
        matriz[1][0] = jogadaJogador;
    if(jogada == 5)
        matriz[1][1] = jogadaJogador;
    if(jogada == 6)
        matriz[1][2] = jogadaJogador;
    if(jogada == 7)
        matriz[2][0] = jogadaJogador;
    if(jogada == 8)
        matriz[2][1] = jogadaJogador;
    if(jogada == 9)
        matriz[2][2] = jogadaJogador;
}

void marcarjogada() {
    int jogada, contador = 0;
    bool vencedor = false;

    esvazia();
    while(contador < 9 and vencedor != true) {
        limpa();
        cabecalho();
        tracajogo();
        poenome();
        if(jogador1.chave) {
            posicaoXY(3, 21);
            cout << "*** X joga agora ***";
        } else {
            posicaoXY(3, 21);
            cout << "*** O joga agora ***";
        }
        do {
            posicaoXY(3, 19);
            cout << "Jogada: ";
            cin >> jogada;
        } while(jogada <= 0 or jogada >= 10);
        if(jogador1.chave) {
            porjogada(jogada, jogador1.jogada);
            if(verificador(jogador1.jogada)) {
                addpontos();
                vencedor = true;
            }
            contador++;
            jogador1.chave = false;
        } else {
            porjogada(jogada, jogador2.jogada);
            if(verificador(jogador2.jogada)) {
                addpontos();
                vencedor = true;
            }
            contador++;
            jogador1.chave = true;
        }
    }
    limpa();
    cabecalho();
    tracajogo();
    poenome();
}

void jogo(void) {
    char resp;
    jogadores();
    do {
        marcarjogada();
        posicaoXY(3, 22);
        cout << "Continuar Jogando? <S> para sim, <N> para nao: ";
        cin >> resp;
    } while(resp == 's' or resp == 'S');
}

int main() {
    cabecalho();
    instrucao();
    jogo();
    return 0;
}
