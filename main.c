/******************************************************************************
 * Conway's Game of Life
 *
 * Program zaliczeniowy nr 3 ze Wstępu do programowania
 *
 * Program służy do gry w Gre w zycie.
 *
 * Wczytuje zywe komorki z wejscia, a nastepnie kolejne instrukcje od 
 * uzytkownika.
 * Wypisuje aktualny stan planszy przy wpisaniu '0', kolejna generacje przy 
 * kliknieciu 'enter' oraz kolejna n-ta generacje przy wpisaniu liczby
 * naturalnej 'n'. Wpisanie dwoch liczb rozdzielonych spacja spowoduje 
 * przesuniecie lewego gornego rogu ekranu na wskazane wspolrzedne.
 * Program konczy dzialanie przy wpisaniu '.'.
 *
 * autorka: Nadia Hoffmann
 * nr albumu: 448252
 * data: 10/01/2022
 *****************************************************************************/

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/* ustawienia poczatkowe planszy */

/**
 * liczba wierszy planszy
 */
#ifndef WIERSZE
# define WIERSZE 22
#endif

/**
 * liczba kolumn planszy
 */
#ifndef KOLUMNY
# define KOLUMNY 80
#endif

/*
 * wspolrzedne lewego gornego rogu okna
 */
int okno_x = 1;
int okno_y = 1;


/* struktury i typy */

/*
 * lista komorek
 */
struct komorki {
    int x;
    int y;
    bool zywa;
    int liczba_wystapien;
    struct komorki *nast;
};

typedef struct komorki Tkomorki;

/*
 * lista wspolrzednych
 */
struct lista_wsp {
    int wsp;                            // wspolrzedna y wiersza
    struct lista_wsp *nast;
    Tkomorki *lista_kom;
};

typedef struct lista_wsp Tlista_wsp;


/* tworzenie nowych elementow list */

/*
 * tworzy atrapę komorki z danego wiersza - 
 * pierwsza komorke o wspolrzednej x rownej INT_MIN
 */
Tkomorki *utworz_pusta_kom(int y) {
    Tkomorki *lista;
    lista = malloc(sizeof(Tkomorki));
    lista -> x = INT_MIN;
    lista -> y = y;
    lista -> zywa = false;
    lista -> liczba_wystapien = 0;
    lista -> nast = NULL;
    
    return lista;
}

/*
 * tworzy pusta liste wsporzednych osi y z atrapa - 
 * y rowne INT_MIN
 */
void utworz_pusta_wsp(Tlista_wsp *lista) {
    lista -> wsp = INT_MIN;
    lista -> nast = NULL;
    lista -> lista_kom = utworz_pusta_kom(INT_MIN);    
}

/*
 * wstawia nowy element do listy wsporzednych osi y
 * wraz z atrapa komorki
 */
Tlista_wsp *wstaw_wsp_za(Tlista_wsp *wsk, int y) {
    Tlista_wsp *pom;
    pom = malloc(sizeof(Tlista_wsp));
    pom -> nast = wsk -> nast;
    pom -> wsp = y;
    pom -> lista_kom = utworz_pusta_kom(y);     // atrapa komorki z x = INT_MIN
    wsk -> nast = pom;

    return pom;
}

/*
 * wstawia nowy element do listy komorek
 * za wskazanym elementem
 */
Tkomorki *wstaw_kom_za(Tkomorki *wsk, int x, int y, bool zywa) {
    Tkomorki *pom;
    pom = malloc(sizeof(Tkomorki));
    pom -> x = x;
    pom -> y = y;
    pom -> zywa = zywa;
    pom -> liczba_wystapien = 0;
    pom -> nast = wsk -> nast;
    wsk -> nast = pom;

    return pom;
}


/* wyszukiwanie i wstawianie do list */

/*
 * wyszukuje, czy dana komorka juz wystapila
 * jesli nie, wstawia nowa komorke do listy
 * i przekazuje do niej wskaznik
 */
Tkomorki *znajdz_wstaw_kom(Tkomorki *lista, int x, int y, bool zywa) {
    Tkomorki *akt, *next, *wynik;

    akt = lista;                            // atrapa/element juz sprawdzony
    next = akt -> nast;
                            // dopoki wspolrzedna x jest mniejsza od szukanej
    while (next != NULL && next -> x < x) {
        akt = next;
        next = akt -> nast;
    }
                            
    if (next == NULL || next -> x != x) {   // komorka nie wystepuje w liscie
        wynik = wstaw_kom_za(akt, x, y, zywa);
    }
    else {                                      // komorka wystepuje w liscie
        if (zywa) {                             // komorka jest zywa
            next -> zywa = true;
        }  

        // jesli komorka nie musi byc zywa jej stan nie jest zmieniany aby
        // uniknac "zabicia" komorek ktore byly wczesniej ustawione jako zywe

        wynik = next;
    }

    return wynik;
}


/*
 * wyszukuje, czy dana wspolrzedna juz wystapila
 * jesli nie, funkcja tworzy wspolrzedna
 * w kazdym wypadku funkcja wyznacza wskaznik do wspolrzednej
 */
Tlista_wsp *znajdz_wsp(Tlista_wsp *l, int x) {
    Tlista_wsp *akt, *next, *wynik;

    akt = l;                                // atrapa/element juz sprawdzony
    next = akt -> nast;

                            // szukana wspolrzedna jest mniejsza od nastepnej
    while (next != NULL && next -> wsp < x) {
        akt = next;
        next = akt -> nast;
    }

    if (next == NULL || next -> wsp != x) {     // wspolrzedna nie wystepuje
        wynik = wstaw_wsp_za(akt, x);
    }
    else {                                      // wspolrzedna wystapuje
        wynik = next;
    }
    
    return wynik;
}


/* obliczanie nowej generacji */

/*
 * zwieksza liczbe wystąpien szukanej komorki w siatce o 1
 * i wyznacza jej wskaznik, dzieki czemu nastepne wyszukiwanie
 * zaczyna sie od tego wskaznika, a nie poczatku wiersza
 */
Tkomorki *zwieksz_wystapienia(Tkomorki *lista, int szukana) { 
    if (lista != NULL) {
        Tkomorki *akt, *next, *wynik;
        akt = lista;
        next = akt -> nast;
                            // szukana wspolrzedna jest mniejsza od nastepnej
        while (next != NULL && next -> x < szukana) {
            akt = next;
            next = akt -> nast;
        }

        if (next == NULL) {                         // komorka nie wystepuje
            wynik = NULL;
        }
        else if (next -> x != szukana) {            // komorka nie wystepuje
            wynik = akt;
        }
        else {                                      // komorka wystepuje
            wynik = next;
            (next -> liczba_wystapien)++;
        }

        return wynik;
    }
    else {
        return lista;
    }
}

/*
 * oblicza liczbe wystapien w siatce 
 * kazdej zywej komorki i jej sasiadow
 */
void oblicz_wystapienia(Tlista_wsp *lista) {  
    Tlista_wsp *gorna, *dolna;
    Tkomorki *siatka[3][3];             // siatka wskaznikow do sasiadow komorki

    while (lista != NULL) {
        gorna = lista;              // atrapa - pewnosc, ze lista nie jest pusta
        lista = lista -> nast;
        siatka[0][0] = gorna -> lista_kom;

        if (lista != NULL) {                        // komorka istnieje
            dolna = lista -> nast;
            siatka[1][1] = lista -> lista_kom -> nast;
            siatka[1][0] = lista -> lista_kom;
        }
        else {                                      // komorka nie istnieje
            dolna = NULL;
            siatka[1][1] = NULL;
            siatka[1][0] = NULL;
        }

        if (siatka[1][1] != NULL) {                 // komorka istnieje
            siatka[1][2] = siatka[1][1] -> nast;            // sasiad z prawej
        }
        else {                              
            siatka[1][2] = NULL;
        }

        if (dolna != NULL) {                        // komorki ponizej istnieja
            siatka[2][0] = dolna -> lista_kom;
        }
        else {                                  // komorki ponizej nie istnieja
            siatka[2][0] = NULL;
        }

        while (siatka[1][1] != NULL) {
            if (siatka[1][1] -> zywa) {
                                // gorna ma indeks y sasiadow powyzej
                if (gorna -> wsp == lista -> wsp - 1) {
                    siatka[0][0] = zwieksz_wystapienia(siatka[0][0], 
                                        siatka[1][1] -> x - 1);
                    siatka[0][1] = siatka[0][0];

                    siatka[0][1] = zwieksz_wystapienia(siatka[0][1],
                                        siatka[1][1] -> x);
            
                    siatka[0][2] = siatka[0][1];
                    siatka[0][2] = zwieksz_wystapienia(siatka[0][2], 
                                        siatka[1][1] -> x + 1);
                }
                                // dolna istnieje i ma indeks y sasiadow ponizej
                if (dolna != NULL && dolna -> wsp == lista -> wsp + 1) {
                    siatka[2][0] = zwieksz_wystapienia(siatka[2][0],
                                        siatka[1][1] -> x - 1);
                    siatka[2][1] = siatka[2][0];
                    siatka[2][1] = zwieksz_wystapienia(siatka[2][1],
                                        siatka[1][1] -> x);
                    siatka[2][2] = siatka[2][1];
                    siatka[2][2] = zwieksz_wystapienia(siatka[2][1],
                                        siatka[2][2] -> x + 1);
                }

                                // sasiad z lewej ma indeks x mniejszy o 1
                if (siatka[1][0] -> x == siatka[1][1] -> x - 1) {
                    (siatka[1][0] -> liczba_wystapien)++;
                }

                                // sasiad z prawej ma indeks x wiekszy o 1
                if (siatka[1][2] != NULL && (siatka[1][2] -> x == 
                            siatka[1][1] -> x + 1)) {
                    (siatka[1][2] -> liczba_wystapien)++;
                }

                (siatka[1][1] -> liczba_wystapien)++;
            }

            // przesuniecie komorek w wierszu
            siatka[1][0] = siatka[1][1];
            siatka[1][1] = siatka[1][2];
    
            if (siatka[1][1] != NULL) {
                siatka[1][2] = siatka[1][1] -> nast;
            }
        }
    }
}

/*
 * zmienia stan kazdej komorki na ten z nowej generacji
 * obliczony na podstawie liczby wystapien w siatce
 */
void zmiana_statusu(Tlista_wsp *lista) {
    Tlista_wsp *pom_wsp;
    pom_wsp = lista;
    while (pom_wsp != NULL) {
        Tkomorki *pom_k;
        pom_k = pom_wsp -> lista_kom;
        while (pom_k != NULL) {
                    // jesli komorka byla sasiadem zywej 3 razy lub
                    // sama jest zywa i byla sasiadem innej zywej 2 lub 3 razy
            if ((pom_k -> liczba_wystapien == 4 && pom_k -> zywa) ||
                    (pom_k -> liczba_wystapien == 3)) {
                pom_k -> zywa = true;
            }
            else {
                pom_k -> zywa = false;
            }

            pom_k = pom_k -> nast;
        }

        pom_wsp = pom_wsp -> nast;
    }
}

/*
 * tworzy nowa liste z komorkami i ich sasiadami z nowej generacji
 */
Tlista_wsp *stworz_liste_nowej_generacji(Tlista_wsp *stara) { 
    Tlista_wsp *pom_y1, *pom_y2, *pom_y3, *nowa;
    nowa = malloc(sizeof(Tlista_wsp));
    utworz_pusta_wsp(nowa);
    pom_y1 = nowa;                      // wiersz sasiadow powyzej zywej komorki
    pom_y2 = nowa;                      // wiersz zywej komorki
    pom_y3 = nowa;                      // wiersz sasiadow ponizej zywej komorki
 
    while (stara != NULL) {             // dopoki w starej generacji sa wiersze
        bool zywe = false;
        Tkomorki *pom_kom_stara;
        pom_kom_stara = stara -> lista_kom;

        while (pom_kom_stara != NULL) {         // dopoki w wierszu sa komorki
            if (pom_kom_stara -> zywa) {        // jesli komorka ma byc zywa
                int y = pom_kom_stara -> y;

                if (!zywe) {        // w wierszu nie bylo jeszcze zywej komorki
                    pom_y1 = znajdz_wsp(pom_y1, y - 1);
                    pom_y2 = znajdz_wsp(pom_y2, y);
                    pom_y3 = znajdz_wsp(pom_y3, y + 1);
                    zywe = true;
                }

                Tkomorki *siatka[3][3];
                            // wszystkie komorki z siatki sa inicjalizowane 
                            // na poczatek wiersza
                for (int i = 0; i < 3; i++) {
                    siatka[0][i] = pom_y1 -> lista_kom;
                }

                for (int i = 0; i < 3; i++) {
                    siatka[1][i] = pom_y2 -> lista_kom;
                }

                for (int i = 0; i < 3; i++) {
                    siatka[2][i] = pom_y3 -> lista_kom;
                }
            
                int x = pom_kom_stara -> x;
                bool zywa;
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (i == 1 && j == 1) {     // komorka musi byc zywa
                            zywa = true;
                        }
                        else {                      // sasiad komorki
                            zywa = false;
                        }

                        siatka[i][j] = znajdz_wstaw_kom(siatka[i][j], x - 1 + j,
                                y - 1 + i, zywa);
                    }
                }
            }

            pom_kom_stara = pom_kom_stara -> nast;
        }
        
        stara = stara -> nast;
    }

    return nowa;
}

/*
 * Czysci kazda komorke z planszy
 */
void wyczysc_plansze(Tlista_wsp *lista) {
    Tlista_wsp *l_pom1, *l_pom2;
    Tkomorki *pom1, *pom2;
    l_pom1 = lista;
    pom1 = l_pom1 -> lista_kom;
    pom2 = pom1 -> nast;
    l_pom2 = l_pom1 -> nast;

    while (l_pom2 != NULL) {            // nastepnik wspolrzednej nie jest pusty
        while (pom2 != NULL) {              // nastepnik komorki nie jest pusty
            free(pom1);
            pom1 = pom2;
            pom2 = pom2 -> nast;
        }
        
        free(pom1);                             // ostatnia komorka z wiersza
        free(l_pom1);                           // poprzedni wiersz jest pusty
        l_pom1 = l_pom2;
        l_pom2 = l_pom2 -> nast;
        pom1 = l_pom1 -> lista_kom;
        pom2 = pom1 -> nast;
    }

    while (pom2 != NULL) {                      // ostatni wiersz planszy
        free(pom1);
        pom1 = pom2;
        pom2 = pom2 -> nast;
    }

    free(pom1);                                 // ostatnia komorka planszy
    free(l_pom1);                               // ostatnia wsporzedna planszy
}

/*
 * porzadkuje nowa generacje komorek
 */
Tlista_wsp *uporzadkuj_nowa_generacje(Tlista_wsp *stara) {
    Tlista_wsp *nowa;
    zmiana_statusu(stara);
    nowa = stworz_liste_nowej_generacji(stara);

    wyczysc_plansze(stara);                     // czyszczenie starej planszy
    stara = nowa;                               // nadpisywanie starej planszy
    nowa = NULL;

    return stara;
}


/* wypisywanie planszy */

/*
 * wypisuje obecny stan widocznej czesci planszy gry
 */
void wypisz_plansze(Tlista_wsp *lista) {
    Tlista_wsp *next;
    next = lista -> nast;

    for (int i = okno_y; i < WIERSZE + okno_y; i++) {
                    // dopoki wspolrzedne y nie mieszcza sie na ekranie
        while (next != NULL && next -> wsp < i) {
            lista = next;
            next = lista -> nast;
        }

        if (next != NULL && next -> wsp == i) {     // wspolrzedna wystepuje
            Tkomorki *k_akt;
            k_akt = next -> lista_kom;

            for (int j = okno_x; j < KOLUMNY + okno_x; j++) {
                    // dopoki wspolrzedne x nie mieszcza sie na ekranie
                while (k_akt != NULL && k_akt -> x < j) {
                    k_akt = k_akt -> nast;
                }

                                                // komorka istnieje i jest zywa
                if (k_akt != NULL && k_akt -> x == j && k_akt -> zywa) {
                    printf("0");
                }
                else {                      // komorka nie instnieje/jest martwa
                    printf(".");
                }
            }
        }
        else {                                      // wsporzedna nie wystepuje
            for (int j = okno_x; j < KOLUMNY + okno_x; j++) {
                printf(".");
            }
        }

        printf("\n");
    }

    for (int i = 0; i < KOLUMNY; i++) {         // dolna, oddzielajaca linijka
        printf("=");
    }

    printf("\n");

}

/*
 * wypisuje wszystkie komorki, ktore sa obecnie zywe
 */
void wypisz_zywe_komorki(Tlista_wsp *lista) {
    Tlista_wsp *l_pom;
    l_pom = lista -> nast;

    while (l_pom != NULL) {         // dopoki sa elementy w liscie
        Tkomorki *k_pom;
        k_pom = l_pom -> lista_kom;
        bool wyp = true;
        
        while (k_pom != NULL) {
            if (k_pom -> zywa) {
                if (wyp) {      // jeszcze nie bylo zywej komorki w tym wierszu
                    printf("/%d", l_pom -> wsp);
                    wyp = false;
                }

                printf(" %d", k_pom -> x);
            }

            k_pom = k_pom -> nast;
        }

        if (!wyp) {         // w tym wierszu byla co najmniej jedna zywa komorka
            printf("\n");
        }

        l_pom = l_pom -> nast;
    }

    printf("/\n");
}


/* obsługa danych wejsciowych */

/**
 * wczytywanie wartosci z wejscia programu
 */
void wczytaj_wsp(Tlista_wsp *lista_y) {
    int c = getchar();
    Tlista_wsp *pom_y1, *pom_y2;
    pom_y1 = lista_y;
    pom_y2 = lista_y;
 
    while (c == '/') {                              // linijki z wspolrzednymi
        c = getchar();
        if (c != '\n') {
            ungetc(c, stdin);
            int y;
            scanf("%d", &y);
            pom_y1 = znajdz_wsp(pom_y1, y - 1);         // wiersz nad komorka
            lista_y = znajdz_wsp(lista_y, y);           // wiersz komorki
            pom_y2 = znajdz_wsp(pom_y2, y + 1);         // wiersz pod komorka
            
            Tkomorki *siatka[3][3];
            for (int i = 0; i < 3; i++) {               // sasiedzi nad komorka
                siatka[0][i] = pom_y1 -> lista_kom;
            }

            for (int i = 0; i < 3; i++) {               // sasiedzi obok komorki
                siatka[1][i] = lista_y -> lista_kom;    // i komorka
            }

            for (int i = 0; i < 3; i++) {               // sasiedzi pod komorka
                siatka[2][i] = pom_y2 -> lista_kom;
            }
            
            c = getchar();
            while (c != '\n') {             // dopoki wiersz sie nie skonczyl
                ungetc(c, stdin);
                int x;
                scanf("%d", &x);
                bool zywa;
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (i == 1 && j == 1) {
                            zywa = true;            // komorka musi byc zywa
                        }
                        else {
                            zywa = false;           // sasiedzi
                        }

                        siatka[i][j] = znajdz_wstaw_kom(siatka[i][j], x - 1 + j,
                                y - 1 + i, zywa);
                    }
                }

                c = getchar();
            }

            c = getchar();
        }
    }
}

/*
 * ustawia rog planszy na nowe wspolrzedne
 */
void przesun_okno(int na_x, int na_y) {
    okno_x = na_x;
    okno_y = na_y;
}

/*
 * obsluguje komendy wejsciowye
 */
void graj(Tlista_wsp *lista) {
    wczytaj_wsp(lista);

    wypisz_plansze(lista);
    int x, y;

    int c = getchar();

    while (c != '.') {
        if (c == '\n') {                                // jedna generacja
            oblicz_wystapienia(lista);
            lista = uporzadkuj_nowa_generacje(lista);
            wypisz_plansze(lista);
        }
        else if (isdigit(c) || c == '-') {
            ungetc(c, stdin);
            scanf("%d", &y);
            c = getchar();

            if (c == ' ') {                 // zmiana wspolrzednych rogu ekranu
                scanf("%d", &x);
                przesun_okno(x, y);
                wypisz_plansze(lista);
                c = getchar();
            }
            else {                          // jedna liczba w linijce
                if (y == 0) {           // wypisywanie aktualnego stanu planszy
                    wypisz_zywe_komorki(lista);
                    wypisz_plansze(lista);
                }
                else {
                    for (int i = 1; i <= y; i++) {      // y generacji
                        oblicz_wystapienia(lista);
                        lista = uporzadkuj_nowa_generacje(lista);
                    }

                    wypisz_plansze(lista);
                }
            }
        }

        c = getchar();
    }

    wyczysc_plansze(lista);         // czyszczenie pamieci na koniec dzialania
}

/*
 * uruchamianie gry
 */
int main() {
    Tlista_wsp *lista_y;
    lista_y = malloc(sizeof(Tlista_wsp));
    utworz_pusta_wsp(lista_y);

    graj(lista_y);

    return 0;
}
