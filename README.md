# directory-sync
## Demon synchronizujący dwa podkatalogi
Program otrzymuje co najmniej dwa argumenty:
- ścieżkę źródłową,
- ścieżkę docelowa. 
```
$ ./main -s <source> -d <destination> [-R]
```  
Dodatkowe (opcjonalne) parametry:
- rozmiar większych plików (wartość powinna być podana w bajtach)
```
$ ./main -s <source> -d <destination> -b 10000000
```
- czas pomiędzy kolejnymi wybudzeniami demona (wartość powinna być w sekundach)
```
$ ./main -s <source> -d <destination> -t 600
```
- rekursywne przeglądanie katalogów
```
$ ./main -s <source> -d <destination> -R
```
Jeżeli któraś z podanych ścieżek nie jest katalogiem program powraca natychmiast z komunikatem błędu.  
W przeciwnym wypadku staje się demonem.

Więcej informacji o dodatkowych opcjach programu można znaleźć [niżej](#dodatkowe-opcje-programu).

### Demon wykonuje następujące czynności:
- śpi przez piec minut (czas spania można zmieniać przy pomocy dodatkowego opcjonalnego argumentu), po czym po obudzeniu się porównuje katalog źródłowy z katalogiem docelowym. Pozycje, które nie są zwykłymi plikami są ignorowane (np. katalogi i dowiązania symboliczne).
- Jeżeli demon (a) napotka na nowy plik w katalogu źródłowym, i tego pliku brak w katalogu docelowym lub (b) plik w katalogu docelowym ma późniejsza datę ostatniej modyfikacji demon wykonuje kopie pliku z katalogu źródłowego do katalogu docelowego - ustawiając w katalogu docelowym datę modyfikacji tak, aby przy kolejnym obudzeniu nie trzeba było wykonać kopii (chyba ze plik w katalogu źródłowym zostanie ponownie zmieniony).
- Jeżeli zaś odnajdzie plik w katalogu docelowym, którego nie ma w katalogu źródłowym to usuwa ten plik z katalogu docelowego.
- Możliwe jest również natychmiastowe obudzenie się demona poprzez wysłanie mu sygnału SIGUSR1.
Wyczerpująca informacja o każdej akcji typu uśpienie/obudzenie się demona (naturalne lub w wyniku sygnału), wykonanie kopii lub usuniecie pliku jest przesłana do logu systemowego. Informacja ta zawiera aktualna datę.  

Operacje kopiowania wykonane za pomocą niskopoziomowych operacji read/write.

### Dodatkowe opcje programu:
- Opcja -R pozwalająca na rekurencyjną synchronizację katalogów (teraz pozycje będące katalogami nie są ignorowane). W szczególności jeżeli demon stwierdzi w katalogu docelowym podkatalog którego brak w katalogu źródłowym usuwa go wraz z zawartością.
- Opcja -t pozwalająca na zmianę czasu braku aktywności programu (domyślnie - 5 minut). Wartość powinna być podana w sekundach.
- W zależności od rozmiaru plików dla małych plików wykonywane jest kopiowanie przy pomocy read/write a w przypadku dużych używany jest bardziej efektywny mechanizm, tj. mmap/write (plik źródłowy zostaje zamapowany w całości w pamięci). Próg dzielący pliki małe od dużych może być przekazywany jako opcjonalny argument (-b). Domyślnie 10MB.

### Instalacja i uruchomienie

```
$ clone git@github.com:sniescior/directory-sync.git
$ make 
$ ./main -s katalog -d katalog-sync -t 600 -R
```
