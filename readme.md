Działanie komendy dodawania drogi krajowej jest następujące:
 * Najpierw sprawdza numer tworzonej drogi krajowej oraz istnienie / możliwość wybudowania / wyremontowania odpowiednich odcinków dróg.
 * Jeżeli w tym momencie wystąpi błąd, to funkcja nic nie zmienia w mapie.
 * Następnie dodaje odpowiednie miasta – jeżeli wtedy wystąpi błąd, to miasta w mapie pozostają.
 * Następnie tworzy lub remontuje odpowiednie odcinki dróg – jeżeli wtedy nie uda się zaalokować pamięci, to odcinki dróg zostają.
 * Na koniec tworzy z nich drogę krajową – jeżeli wystąpi błąd, to droga nie zostaje utworzona, ale utworzone miasta i odcinki dróg pozostają.

Każda linia powinna kończyć się linuksowym znakiem końca linii – w przeciwnym
przypadku zawsze zgłaszam błąd.
