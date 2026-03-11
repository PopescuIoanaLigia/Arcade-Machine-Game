# Chicken Invaders – Editor de Navă 2D

Acest proiect implementează jocul Chicken Invaders cu un editor de navă spațială, folosind C++ și OpenGL (prin gfx-framework). Jucătorul își poate construi propria navă folosind blocuri modulare, iar apoi poate participa la jocul de tip shoot’em up.

![Gameplay](images/chicken_invaders.gif)

Funcționalități principale:

# 1. Editor de navă
Editorul permite construirea navei pe o grilă 2D folosind blocuri modulare.
Blocuri disponibile:
Bloc solid: pătrat 1×1
Tun: 3 linii × 1 coloană, cu țeava tunului și elemente decorative
Motor: pătrat 1×1 cu elemente decorative
Bumper: pătrat 1×1 cu semicerc deasupra
Constrângeri pentru navă:
Nava trebuie să aibă cel puțin 1 bloc și maxim 10 blocuri
Toate blocurile trebuie să fie conectate (vecinătate ortogonală)
Nu se poate plasa blocuri sub motor, peste tun sau peste bumper
Nu se pot plasa două blocuri bumper vecine
Tunul nu poate fi lângă bumper la o distanță de 1 bloc
Interacțiune cu editorul:
Drag & drop pentru plasarea blocurilor
Click dreapta pentru ștergerea blocurilor
Bara de stânga afișează blocurile disponibile
Numărul de blocuri disponibile este afișat prin pătrate verzi
Butonul Start pornește jocul doar dacă nava respectă constrângerile (verde dacă este validă, roșu altfel)

# 2. Joc Chicken Invaders
Jocul este un shoot’em up clasic, în care nava construită de jucător trebuie să distrugă inamicii înainte ca aceștia să ajungă josul ecranului.

Inamici:
Formație inițială de 2 linii × 5 coloane
Coborâre constantă și tragere de proiectile către jucător
Coliziuni: proiectil jucător → inamic, proiectil inamic → jucător
Pierdere joc dacă inamicul atinge baza sau nava este lovită

Nava jucătorului:
Se mișcă stânga-dreapta cu mouse-ul sau tastele săgeți
Trage proiectile din tunuri (proiectile verzi)
Viteza navei poate depinde de numărul de motoare plasate
Proiectile și coliziuni:
Proiectilele sunt rectangulare sau pătrate, iar inamicii aproximati prin cercuri
Detectarea coliziunilor și distrugerea obiectelor respective

Funcționalități vizuale:

Mișcare sinusoidală a inamicilor

Evidențiere vizuală a proiectilelor și blocurilor
