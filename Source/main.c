#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

// N - liczba punktów
// Road[N] - tablica indeksów kolejnych punktów
// Points[x][y] - tablica wspolrzednych puntków

double minimum(double** Points,int N)// funkcja obliczajaca minimum
{
    double min=Points[0][0];// ustawienie pierwszego elementu jako minimum
    for(int i=0;i<N;i++)// porównywanie kolejnych elementow, jezeli maja mniejsza wartosc zostaja przypisane do zmiennej min
    {
        if(min>=Points[i][0])
            min=Points[i][0];
        if(min>=Points[i][1])
            min=Points[i][1];
    }
    printf("\nWartosc minimalna: %f",min);// wyswietlenie wartosci minimalnej
    return min;// zwrocenie wartosci minimalnej
}

double maximum(double** Points,int N)// funkcja obliczajaca maksimum
{
    double max=Points[0][0];// ustawienie pierwszego elementu jako maksimum
    for(int i=0;i<N;i++)// porównywanie kolejnych elementow, jezeli maja wieksza wartosc zostaja przypisane do zmiennej max
    {
        if(max<=Points[i][0])
            max=Points[i][0];
        if(max<=Points[i][1])
            max=Points[i][1];
    }
    printf("\nWartosc maksymalna: %f",max);// wyswietlenie wartosci maksymalnej
    return max;// zwrocenie wartosci maksymalnej
}

void graphic(int N, double** Points,int* Road,int choose)// funkcja tworzaca grafike
{
    double z=1;// skalowanie ukladu wspolrzednych,wspolrzedna_punktu*z
    int p=0;// przesuwanie ukladu wspolrzednych,wspolrzedna_punktu+p
    double min=minimum(Points,N);// wartosc maksymalna wsrod wspolrzednych punktow
    double max=maximum(Points,N);// wartosc minimalna wsrod wspolrzednych punktow
    if(choose==1)// gdy uzytkownik sam wprowadza wspolrzedne odpowiednio skalujemy grafike, tak aby byla czytelna i miescila sie w calosci na ekranie
        {
        if(max<60&&min>0)
        z=10;
        if(max>600&&min>0)
        z=0.1;
        if(min<0)// gdy uzytkownik wprowadza wspolrzedne mniejsze od zera przesuwamy uklad wspolrzednych, tak ze poczatek ukladu wspolrzednych znajduje sie na srodku ekranu
	    {
                p=300;
                if(min<-300||max>300)
                z=0.1;
                if(min<-3000||max>3000)
                z=0.05;
                if(min>-30&&max<30)
                z=10;
            }
        }
    al_init();// wprowadzenie biblioteki allegro
    al_init_primitives_addon();// wprowadzenie dodatku obslugujacego rysowanie prostych ksztaltow
    ALLEGRO_DISPLAY *okno = al_create_display(600,600);// tworzenie okna
    al_set_window_title( okno,"Graficzna prezentacja");// nadanie nazwy okna
    al_clear_to_color(al_map_rgb(0,0,0));// wyczyszczenie ekranu
    al_install_keyboard();// wprowadzenie obslugi klawiatury
    ALLEGRO_KEYBOARD_STATE klawiatura;// wprowadzenie zmiennej obslugujacej klawiature
    ALLEGRO_COLOR kolor = al_map_rgb(255,255,102);// wprowadzenie koloru linii
    ALLEGRO_COLOR kolor1 = al_map_rgb(255,255,255);// wprowadzenie koloru punktu
    if(choose==0)// tryb gdy dane podawane sa pseudolosowo
    while(!al_key_down(&klawiatura, ALLEGRO_KEY_ESCAPE))// wyjscie poprzez wcisniecie ESCAPE
    {
        al_get_keyboard_state(&klawiatura);// pobranie wartosci z klawiatury
        for(int i=0;i<N-1;i++)
        {
            al_draw_filled_circle(Points[i][0],Points[i][1],3,kolor1);// rysowanie punktu
            al_draw_line(Points[Road[i]][0],Points[Road[i]][1],Points[Road[i+1]][0],Points[Road[i+1]][1],kolor,2);// rysowanie linii
        }
        al_draw_filled_circle(Points[N-1][0],Points[N-1][1],3,kolor1);// rysowanie ostatniego punktu
        al_flip_display();// wyswietlenie na ekran narysowanej grafiki
    }
    if(choose==1)// tryb gdy dane podawane sa przez uzytkownika
    while(!al_key_down(&klawiatura, ALLEGRO_KEY_ESCAPE))// wyjscie poprzez wcisniecie ESCAPE
    {
        al_get_keyboard_state(&klawiatura);// pobranie wartosci z klawiatury
        for(int i=0;i<N-1;i++)
        {
            al_draw_filled_circle(Points[i][0]*z+p,Points[i][1]*z+p,3,kolor1);// rysowanie punktu
            al_draw_line(Points[Road[i]][0]*z+p,Points[Road[i]][1]*z+p,Points[Road[i+1]][0]*z+p,Points[Road[i+1]][1]*z+p,kolor,2);// rysowanie linii
        }
        al_draw_filled_circle(Points[N-1][0]*z+p,Points[N-1][1]*z+p,3,kolor1);// rysowanie ostatniego punktu
        al_flip_display();// wyswietlenie na ekran narysowanej grafiki
    }
    al_destroy_display(okno);// zwalnianie pamieci
}

void alocate(int *N, double*** copy_Points,double*** Points)// tworzenie kopii tablicy Points[][]
{
    *copy_Points = (double**)malloc((*N) * sizeof(double*));// alokowanie pamieci dla tablicy wspolrzednych puntków
    for (int i = 0; i < *N; i++){
        (*copy_Points)[i] = (double*)malloc(2 * sizeof(double));}
        for(int i=0;i<*N;i++)// kopiowanie zawartosci tablicy Points do tablicy copy_Points
    {
        (*copy_Points)[i][0]=(*Points)[i][0];
        (*copy_Points)[i][1]=(*Points)[i][1];
    }
}

void road(int N, double** Points,int* Road)// funckja obliczajaca dlugosc drogi
{
    double wynik=0;
    double x1,x2,y1,y2;
    for(int i=0;i<N-1;i++)
    {
        x1=Points[Road[i]][0];// wspolrzedna x punktu nr 1
        y1=Points[Road[i]][1];// wspolrzedna y punktu nr 1
        x2=Points[Road[i+1]][0];// wspolrzedna x punktu nr 2
        y2=Points[Road[i+1]][1];// wspolrzedna y punktu nr 2
        wynik+=sqrt(pow(x2-x1,2)+pow(y2-y1,2));// obliczenie drogi
    }
    printf("\nDlugosc drogi: %f",wynik);// wyswietlenie dlugosci drogi
}

void fill(int* N, double*** Points)// wprowadzanie danych przez uzytkownika
{
    double x,y;
    int num;
    printf("Wprowadz ilosc punktow\n");
    scanf("%d", &num);
    if(num>0&&num<10000)// zabezpieczenie
        *N=num;// wprowadzenie ilosci punktow
        else
        {
            printf("Wprowadzono bledne dane\n");
            exit(0);
        }
    *Points = (double**)malloc((*N) * sizeof(double*));// alokowanie pamieci dla tablicy wspolrzednych puntków
    for (int i = 0; i < *N; i++)
        (*Points)[i] = (double*)malloc(2 * sizeof(double));
    for (int j = 0; j < *N; j++)
    {
        printf("Wprowadz wspolrzedne punktu nr: %d\n", j + 1);
        printf("x=");
        scanf("%lf", &x);
        if(x>-6000&&x<6000&&x!=0)// zabezpieczenie (w oknie z grafika mieszcza sie punkty jedynie z zakresu (-6000,6000))
        (*Points)[j][0]=x;// wprowadzenie wartosci wspolrzednej x dla danego punktu
        else
        {
            printf("Wprowadzono bledne dane\n");
            exit(0);
        }
        printf("y=");
        scanf("%lf", &y);
        if(y>-6000&&y<6000&&y!=0)// zabezpieczenie (w oknie z grafika mieszcza sie punkty jedynie z zakresu (-6000,6000))
        (*Points)[j][1]=y;// wprowadzenie wartosci wspolrzednej y dla danego punktu
        else
        {
            printf("Wprowadzono bledne dane\n");
            exit(0);
        }
    }
}

void randoms(int *N, double*** Points)// wprowadzanie danych pseudolosowo
{
    srand(time(0));
    int choose;
    printf("Aby wprowadzic ilosc punktow losowo wpisz 0, aby wprowadzic wlasna ilosc punktow wpisz 1\n");
    scanf("%d", &choose);// choose - wybor sposobu wprowadzania danych
    if(choose==0)
    *N = 2+rand() % 100;// wprowadzenie ilosci punktow
    if(choose==1)
    {
        printf("Wprowadz ilosc punktow\n");
        scanf("%d",N);
    }
    *Points = (double**)malloc((*N) * sizeof(double*));// alokowanie pamieci dla tablicy wspolrzednych puntków
    for (int i = 0; i < *N; i++)
        (*Points)[i] = (double*)malloc(2 * sizeof(double));
    for (int j = 0; j < *N; j++)// wypelnianie wspolrzednych punktow pseudolosowymi wartosciami
    {
        (*Points)[j][0] = ((double)rand()*600) / (double)RAND_MAX;
        (*Points)[j][1] = ((double)rand()*600) / (double)RAND_MAX;
    }
    printf("Ilosc punktow: %d\n",*N);// wyswietlenie wylosowanej ilosci punktow uzytkownikowi
    for (int r = 0; r < *N; r++)// wyswietlenie wylosowanych wspolrzednych punktow uzytkownikowi
    {
        printf("Wspolrzedne punktu nr: %d\n", r+1);
        printf("x=%f\n", (*Points)[r][0]);
        printf("y=%f\n", (*Points)[r][1]);
    }
}

void algorithm(int N, double** Points,int* Road)// algorytm
{
    double tmp = 0;
    int tmpint = 0, a = 0, b = 0;
    double Roadlen[N];
    int index[N], first = 0, Roadindex = 1, i = 0, cpyN = N;
    Road[0] = 0;// ystawienie pierwszego podanego punktu na punkt poczatkowy
    for (i = 0; i < N; i++)
    {
        if ((Points)[i][0] != 0.0)// sprawdzamy czy zostaly jeszcze punkty nie uwzglednione w trasie
        {
            Roadlen[i] = sqrt(pow((Points)[first][0] - (Points)[i][0], 2) + pow((Points)[first][1] - (Points)[i][1], 2));// obliczanie wartosci drog do poszczegolnych punktow
            index[i] = i;// tablica indeksow punktow do ktorych obliczono dlugosc drogi
        }
        if (i == N - 1)
        {
            {
                for (a = 0; a < N; a++)
                    for (b = N - 1; b > a; b--)
                        if (Roadlen[b - 1] < Roadlen[b])// sortowanie dlugosci drog, aby wybrac najkrotsza
                        {
                            tmp = Roadlen[b - 1];// zamieniamy kolejnosc elementow tablicy z dlugosciami drog
                            Roadlen[b - 1] = Roadlen[b];
                            Roadlen[b] = tmp;
                            tmpint = index[b - 1];// zamieniamy takze kolejnosc indeksow, aby moc zidentyfiowac punkty
                            index[b - 1] = index[b];
                            index[b] = tmpint;
                        }
            }
            (Points)[first][0] = 0;// zerowanie punktu, ktory juz byl odwiedzony
            (Points)[first][1] = 0;
            for (int p = 0; p < N; p++)
                if (Roadlen[p] != 0.0)
                {
                    Road[Roadindex] = index[p];// wprowadzamy indeks punktu dla ktorego wyznaczono najkrotsza droge do tablicy jako kolejny punkt na trasie
                    first = index[p];// ustawiamy punkt na punkt poczatkowy od ktorego bedziemy dalej prowadzic trase
                }
            Roadindex++;
            i = 0;
            for (int m = 0; m < N; m++)//zerujemy wartosci drog i indeksy punktow przed obliczaniem dlugosci drog od nastepnego punktu
            {
                Roadlen[m] = 0;
                index[m] = 0;
            }
            cpyN--;
            if (cpyN == 0)
                break;
        }
    }
    printf("Kolejnosc odwiedzania punktow:\n");// wyswietlenie uzytkownikowi wyznaczonej trasy
    for (int k = 0; k < N; k++)
        printf("%d ", Road[k]+1);
}

int main()
{
    int N;// liczba punktów
    int choose;// wybor sposobu wprowadzania danych
    int *Road;// tablica indeksów kolejnych punktów
    double** Points;// tablica wspolrzednych puntków
    double** copy_Points;// kopia tablicy wspolrzednych puntków
    printf("Aby wprowadzic dane losowo wpisz 0, aby wprowadzic wlasne dane wpisz 1\n");
    scanf("%d", &choose);// choose - wybor sposobu wprowadzania danych
    if (choose == 1)// wprowadzanie danych przez uzytkownika
        fill(&N, &Points);
    if (choose == 0)// wprowadzanie danych pseudolosowo
        randoms(&N, &Points);
    if(choose!=0&&choose!=1)// zabezpieczenie
    {
        printf("Wprowadzono bledne dane");
        return 0;
    }
    Road=(int*)malloc(N*sizeof(int));// alokowanie pamieci dla tablicy Road[]
    alocate(&N,&copy_Points,&Points);// wywolanie funkcji alocate
    algorithm(N,Points,Road);// wywolanie funkcji algorithm
    road(N,copy_Points,Road);// wywolanie funkcji road
    graphic(N,copy_Points,Road,choose);// wywolanie funkcji graphic
    free(Points);// zwalnianie pamieci tablicy Points
    free(copy_Points);// zwalnianie pamieci tablicy copy_Points
    free(Road);// zwalnianie pamieci tablicy Road
    return 0;
}
