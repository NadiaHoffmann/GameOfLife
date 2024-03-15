# Wprowadzenie
Stworzona przez Johna Conwaya [Gra w Życie](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) to automat komórkowy, czyli symulacja świata komórek.

Symulacja jest prowadzona na planszy, składającej się z nieskończenie wielu wierszy i nieskończenie wielu kolumn.
Wiersze i kolumny planszy są numerowane liczbami całkowitymi ze znakiem.

Na każdym polu planszy jest komórka w jednym z dwóch stanów: *żywa* lub *martwa*.

Łączny stan wszystkich komórek nazywamy *generacją*.

Przyjmujemy, że komórka w wierszu `w` i kolumnie `k` sąsiaduje na planszy z ośmioma innymi komórkami, które mają numer wiersza od `w - 1` do `w + 1` a numer kolumny od `k - 1` do `k + 1`.

Symulacja zaczyna się od pewnej generacji początkowej, na podstawie której liczymy następne.

W następnej generacji komórka będzie żywa wtedy i tylko wtedy, gdy:
- w bieżącej generacji jest żywa i ma dokładnie dwóch lub trzech żywych sąsiadów, albo
- w bieżącej generacji jest martwa i ma dokładnie trzech żywych sąsiadów.

# Polecenie
Napisz program, który symuluje Grę w Życie.

Program czyta z wejścia opis generacji początkowej. Następnie, w pętli, pokazuje fragment planszy, po czym czyta i wykonuje polecenie użytkownika.

Polecenia sterują liczeniem kolejnych generacji. Określają też fragment planszy, dalej nazywany oknem, którego zawartość jest pokazywana użytkownikowi.

Program jest parametryzowany dwiema dodatnimi liczbami całkowitymi:
- `WIERSZE` to liczba wierszy okna;
- `KOLUMNY` to liczba kolumn okna.
  
Wartości tych parametrów są określone za pomocą stałych symbolicznych, które można zdefiniować opcją `-D` kompilatora.
W kodzie programu są podane wartości domyślne:
- `WIERSZE` ma wartość `22`;
- `KOLUMNY` ma wartość `80`.
  
Pozycja okna na planszy jest określona przez pozycję jego lewego górnego rogu. Jeśli lewy górny róg okna jest w wierszu `w` i kolumnie `k`, to okno obejmuje komórki, które mają numer wiersza od `w` do `w + WIERSZE - 1` i numer kolumny od `k` do `k + KOLUMNY - 1`.

Początkowo lewy górny róg okna jest w wierszu numer `1` i kolumnie numer `1`.

# Postać danych
Na wejściu programu jest opis generacji początkowej i ciąg poleceń.

Opis generacji wskazuje komórki, które są żywe. Ma postać ciągu wierszy zaczynających się od znaku `'/'` (slash).

W ostatnim wierszu opisu generacji jest tylko znak `'/'`. We wszystkich pozostałych wierszach po znaku `'/'` jest liczba całkowita, będąca numerem wiersza planszy. Po niej jest uporządkowany rosnąco niepusty ciąg liczb całkowitych, będących numerami kolumn. Każda z tych liczb jest poprzedzona jedną spacją.

Wiersz postaci:

`/w k1 .. kn`

informuje, że w wierszu planszy o numerze w żyją komórki w kolumnach `k1`, .., `kn`.

W opisie generacji ciąg numerów wierszy, czyli liczb poprzedzonych znakami `'/'`, jest uporządkowany rosnąco.

Po opisie generacji początkowej, na wejściu programu jest ciąg jednowierszowych poleceń.

Program rozpoznaje polecenia:
- zakończenia pracy,

  Ma postać wiersza ze znakiem `'.'` (kropka).
  
  Przerywa pętlę czytającą polecenia i kończy pracę programu.
  
- obliczenia `N`-tej kolejnej generacji,

  Ma postać wiersza z dodatnią liczbą całkowitą `N`.
  
  Liczy N-tą kolejną generację, zaczynając od aktualnej. W szczególności, polecenie `1` powoduje obliczenie następnej generacji.
  
- obliczenia następnej generacji,
  
  Ma postać wiersza pustego. Jest równoważne poleceniu `1`.
  
- zrzutu stanu aktualnej generacji,
  
  Ma postać wiersza z liczbą `0` (zero).
  
  Generuje kompletny opis aktualnej generacji w takim samym formacie, w jakim był wczytany przez program opis generacji początkowej.
  
- przesunięcia okna.
  
  Ma postać wiersza z dwiema liczbami całkowitymi, `w` oraz `k`, rozdzielonymi spacją.
  
  Zmienia współrzędne lewego górnego rogu okna, umieszczając go w wierszu `w` i kolumnie `k`.

# Postać wyniku
Przed wczytaniem każdego polecenia program pokazuje zawartość okna, zaczynając od lewego górnego rogu.

Zawartość okna jest przedstawiona za pomocą `WIERSZE` wierszy, z których każdy ma długość `KOLUMNY`. Po ostatnim z nich następuje wiersz, w którym jest ciąg znaków `'='` (równość) o długości `KOLUMNY`.

Znak w wierszu zawartości okna określa stan komórki. Komórka żywa jest reprezentowana przez znak `'0'` (zero) a komórka martwa jest reprezentowana przez znak `.` (kropka).

# Przykłady
Poniższe przykłady są wynikiem działania programu skompilowanego poleceniem:

`gcc @opcje -DWIERSZE=22 -DKOLUMNY=80 zadanie3.c -o zadanie3`

Do treści zadania dołączone są pliki .in z przykładowymi danymi i pliki .out z wynikami wzorcowymi.
- Dla danych przyklad1.in poprawny wynik to przyklad1.out .
- Dla danych przyklad2.in poprawny wynik to przyklad2.out .
- Dla danych przyklad3.in poprawny wynik to przyklad3.out .

# Walidacja i testy
- Rozwiązania podlegają walidacji, wstępnie badającej zgodność ze specyfikacją.
  
  Walidacja sprawdza działanie programu na przykładach dołączonych do treści zadania.
  
  Pomyślne przejście walidacji jest warunkiem dopuszczenia programu do testów poprawności. Program, który walidacji nie przejdzie, dostaje zerową ocenę poprawności.
  
- Walidacja i testy są prowadzone na komputerze students.
- Programy są kompilowane poleceniem:
  
  `gcc @opcje ... nazwa.c -o nazwa`
  
  gdzie we fragmencie wykropkowanym mogą być opcje -D definiujące stałe WIERSZE i KOLUMNY, nazwa.c to nazwa pliku z kodem źródłowym, a plik opcje ma zawartość:
  
  `-std=c17`
  
  `-pedantic`
  
  `-Wall`
  
  `-Wextra`
  
  `-Wformat-security`
  
  `-Wduplicated-cond`
  
  `-Wfloat-equal`
  
  `-Wshadow`
  
  `-Wconversion`
  
  `-Wjump-misses-init`
  
  `-Wlogical-not-parentheses`
  
  `-Wnull-dereference`
  
  `-Wvla`

  `-Werror`
  
  `-fstack-protector-strong`
  
  `-fsanitize=undefined`
  
  `-fno-sanitize-recover`
  
  `-g`
  
  `-fno-omit-frame-pointer`
  
  `-O1`

    Opcje `-std=c17`, `-pedantic` wskazują, że kompilator ma dbać o zgodność kodu z aktualnym standardem języka C.
  
    Dzięki opcjom `-Wall`, `-Wextra` kompilator zgłosi zauważone usterki.
  
    Opcje `-Wformat-security`, `-Wduplicated-cond`, `-Wfloat-equal`, `-Wshadow`, `-Wconversion`, `-Wjump-misses-init`, `-Wlogical-not-parentheses`, `-Wnull-dereference` umożliwiają wykrywanie dodatkowych usterek.
  
    Opcja `-Wvla` sprawia, że użycie tablic zmiennej długości jest uznawane za usterkę.
  
    Opcja `-Werror` wskazuje, że kompilator ma uznać usterki za błędy.
  
    Dzięki opcji `-fstack-protector-strong`, podczas wykonania programu zostaną wykryte niektóre błędne odwołania do pamięci na stosie.
  
    Opcje `-fsanitize=undefined`, `-fno-sanitize-recover` umożliwiają wykrywanie operacji, które mają efekt nieokreślony.
  
    Opcje `-g`, `-fno-omit-frame-pointer` poprawiają jakość komunikatów o błędach wykonania.
  
    Opcja `-O1` włącza optymalizacje, co zwiększa prawdopodobieństwo ujawnienia się błędów.
  
    Wymagane są wszystkie wymienione opcje kompilatora. Nie będą do nich dodawane żadne inne.
  
    Zwracamy uwagę, że poszczególne wersje kompilatora `gcc` mogą się różnić sposobem obsługi tych samych opcji. Przed wysłaniem rozwiązania warto więc skompilować je i przetestować na `students` w sposób opisany powyżej.
  
- Podczas walidacji i testów, program nazwa jest uruchamiany pod kontrolą programu Valgrind poleceniem:
  
  `valgrind --leak-check=full -q --error-exitcode=1 ./nazwa argumenty`
  
  Jeśli Valgrind wykryje błąd, to nawet, gdyby wynik był prawidłowy, uznajemy, że program testu nie przeszedł.
  
  Opcja `-q` powoduje, że jedynymi informacjami, wypisywanymi przez program Valgrind, są komunikaty o błędach.
  
  Opcja `--leak-check=full` wskazuje Valgrindowi, że powinien, między innymi, szukać wycieków pamięci.
  
  Opcja `--error-exitcode=1` określa kod wyjścia programu w przypadku, gdy Valgrind wykryje błąd.
  
- Przyjmujemy, że niezerowy wynik funkcji `main()` informuje o błędzie wykonania programu.
- Poprawność wyniku sprawdzamy, przekierowując na wejście programu zawartość pliku `.in` i porównując rezultat, za pomocą programu `diff`, z plikiem `.out`, np.:
  
  `< przyklad.in ./nazwa | diff - przyklad.out`
  
  Ocena poprawności wyniku jest binarna. Wynik uznajemy za poprawny, jeżeli program `diff` nie wskaże żadnej różnicy względem wyniku wzorcowego.

# Uwagi
- Jako rozwiązanie należy wysłać plik tekstowy `.c` z kodem źródłowym w języku C.
- Wolno założyć, że dane są poprawne.
- Wolno założyć, że każdy wiersz danych, w tym ostatni, kończy się reprezentacją końca wiersza `'\n'`.
  Należy zadbać, by warunek ten spełniał także wynik programu.
- Wolno założyć, że wartości stałych `WIERSZE` i `KOLUMNY`, jeśli zostały określone podczas kompilacji, są dodatnimi liczbami całkowitymi.
- Rozwiązanie powinno mieć koszt pamięciowy liniowy względem liczby żywych komórek.
- Wolno założyć, że współrzędne okna i współrzędne żywych komórek mieszczą się w zakresie typu `int` a nawet, że są większe niż `INT_MIN` i mniejsze niż `INT_MAX`.
- Nie wolno ograniczać liczby żywych komórek. Można tylko założyć, że będzie ona w zakresie typu `int` i że reprezentacja żywych komórek zmieści się w pamięci dynamicznej programu.
- Podczas testów walidacyjnych i testów poprawności limit czasu będzie ustalony na 30 sekund.
  
  Rozwiązanie, w którym koszt czasowy obliczenia następnej generacji jest liniowy względem liczby żywych komórek, na pewno we wszystkich testach zmieści się w limicie czasu. Program mniej efektywny w niektórych testach może mieć z tym problem. Gwarantujemy jednak, że będzie co najmniej 6 testów poprawności, z którymi powinny sobie poradzić algorytmy o kwadratowym koszcie obliczenia następnej generacji.
  
  Rozwiązania o złożoności gorszej niż kwadratowa mogą nie przejść nawet testów walidacyjnych.

# Wskazówki
- Jeśli opis początkowej generacji jest w pliku `generacja.txt`, to program uruchomiony poleceniem:
  
  `cat generacja.txt - | ./zadanie3`
  
  wczyta generację a następnie będzie pobierał polecenia użytkownika z klawiatury.
  
- W przygotowaniu danych testowych może pomóc polecenie `tee`. Przesyła ono dane z wejścia na wyjście, jednocześnie zapisując ich kopię w pliku, którego nazwa jest argumentem polecenia.
  
  Wykonanie polecenia:
  
  `cat generacja.txt - | tee test.in | ./zadanie3`
  
  uruchomi program `zadanie3`, przekazując mu na wejście zawartość pliku `generacja.txt` a po niej to, co wpisze użytkownik. Jednocześnie wszystkie dane, które trafiają na wejście programu, zostaną też zapisane w pliku `test.in`.
  
  Test na tych samych danych będzie można powtórzyć poleceniem:
  
  `< test.in ./zadanie3 > test.out`
  
- Polecenie `0` umożliwia kontynuowanie, w następnej sesji, symulacji rozpoczątej w sesji poprzedniej. Jeżeli początkowo w pliku `generacja.txt` jest opis pierwszej generacji i jeżeli pracę z programem będziemy kończyć, wydając polecenia:
  
  `0`
  
  `.`
  
  to każdorazowe wykonanie poleceń:
  
  `cat generacja.txt - | ./zadanie3 | tee log.txt`
  
  `grep / log.txt > generacja.txt`
  
  rozpocznie symulację w stanie, w którym zakończyliśmy ją poprzednio.
  
