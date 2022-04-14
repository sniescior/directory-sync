# directory-sync
### Demon synchronizujący dwa podkatalogi
Program który otrzymuje co najmniej dwa argumenty: 
<ul>
  <li>ścieżkę źródłową</li>
  <li> ścieżkę docelowa. </li> 
</ul>
<p>
  <code>./main katalog katalog/sync</code>
  Jeżeli któraś ze ścieżek nie jest katalogiem program powraca natychmiast z komunikatem błędu.
  <br>W przeciwnym wypadku staje się demonem. </p>

### Demon wykonuje następujące czynności:
<ul>
  <li>
    śpi przez piec minut (czas spania można zmieniać przy pomocy dodatkowego opcjonalnego argumentu), po czym po obudzeniu się porównuje katalog źródłowy z katalogiem docelowym. Pozycje, które nie są zwykłymi plikami są ignorowane (np. katalogi i dowiązania symboliczne).
  </li>
  <li>
    Jeżeli demon (a) napotka na nowy plik w katalogu źródłowym, i tego pliku brak w katalogu docelowym lub (b) plik w katalogu docelowym ma późniejsza datę ostatniej modyfikacji demon wykonuje kopie pliku z katalogu źródłowego do katalogu docelowego - ustawiając w katalogu docelowym datę modyfikacji tak, aby przy kolejnym obudzeniu nie trzeba było wykonać kopii (chyba ze plik w katalogu źródłowym zostanie ponownie zmieniony).
  </li>
  <li>
    Jeżeli zaś odnajdzie plik w katalogu docelowym, którego nie ma w katalogu źródłowym to usuwa ten plik z katalogu docelowego.
  </li>
  <li>
    Możliwe jest również natychmiastowe obudzenie się demona poprzez wysłanie mu sygnału SIGUSR1.
  </li>
</ul>
<p>
  Wyczerpująca informacja o każdej akcji typu uśpienie/obudzenie się demona (naturalne lub w wyniku sygnału), wykonanie kopii lub usuniecie pliku jest przesłana do logu systemowego. Informacja ta zawiera aktualna datę.
</p>
<p>Operacje kopiowania wykonane za pomocą niskopoziomowych operacji read/write.</p>
