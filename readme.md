Działanie komendy dodawania drogi krajowej jest następujące:
 * Najpierw sprawdza numer tworzonej drogi krajowej oraz istnienie / możliwość wybudowania / wyremontowania odpowiednich odcinków dróg.
 * Następnie tworzy drogę krajową.
 * Na testach z tego repozytorium nie powinien wystąpić błąd przy alokowaniu pamięci i poprawność outów nie powinna zależeć od zachowania programów w tej sytuacji.

Każda linia powinna kończyć się linuksowym znakiem końca linii – w przeciwnym
przypadku zawsze zgłaszam błąd.

Skrypt testujący – należy jako pierwszy argument podać ścieżkę do pliku wykonywalnego, a jako drugi ścieżkę do folderu z testami.

Dodano testy od Michała Tyrolskiego i Macieja Procyka.
