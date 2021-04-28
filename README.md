# RG62-catches-the-fly.

## :spider: Opis igre:
Zadatak igraca je da pauka dovede do svog rucka, pritom pokusavajuci da izbegne sve prepreke koje mu se javljaju na putu.

## :book: Uputstvo:
Igra je potezna. Svaki potez sastoji se od pomeranje pauka od strane igraca i automatskog pomeranja neprijatelja.
Igrac je u mogucnosti da pauka rotira u mestu kako bi izabrao platformu na koju zeli da se premesti kao i da pauka na tu platformu premesti. 
U slucaju da se na toj platformi nalazi neprijatelj on ce biti pojeden.
Nakon sto se pauk premesti na izabranu platformu, automatski se aktiviraju neprijatelji koji se premestaju na unapred odredjenu platformu.
Pauk ce biti pojeden u slucaju da je platforma na kojoj on boravi bas platforma na koju se premesta neki od neprijatelja.

## :video_game: Komande:
|Komanda   | Akcija  |
|---     |---|
| <kbd>W</kbd>  |Pomeranje unapred  |
| <kbd>A</kbd>  |Rotacija ulevo |
| <kbd>D</kbd>  |Rotacija udesno    | 
| <kbd>R</kbd>  |Ponovno pokretanje  |
| <kbd>ESC</kbd>  |Prekidanje igrice|

## :wrench: Instalacija[Linux]:
1.Pomocu terminala zadati komandu za kloniranje repozitorijuma: ```git clone https://github.com/MATF-RG19/RG62-catches-the-fly..git```  
2.Pozicionirajte se u direktorijum sa nazivom ``RG62-catches-the-fly.``  
3.Kreirajte direktorijum ```build``` i pozicionirajte se u njega  
4.Pomocu terminala izvrsiti komandu: ```cmake -G 'Unix Makefiles' ..```  
5.Pokrenite Makefile komandom ```make```  
6.Igricu iz terminala pokrenite komandom: ``./catches_the_fly``