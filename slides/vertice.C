Esercizio per l’esame

a.a. 2017/18

• Si consideri un esperimento ad un collider (e.g. collisioni
p-p)
• Le collisioni avvengono in una regione (collision diamond)
centrata nell’origine di un sistema di riferimento
cartesiano, nel quale z rappresenta la direzione del fascio
q La dispersione in z è di diversi centimetri
q La dispersione in x e y dell’ordine del decimo di millimetro

• Lo scopo dei rivelatori di vertice è quello di determinare la
posizione della collisione (“vertice primario”)
• Ci proponiamo qui di ricostruire la coordinata z del vertice

T.A.N.S.

1

Esercizio per l’esame

a.a. 2017/18

• Si suppone di avere un rivelatore di vertice
costituito da due piani di pixel al silicio, coassiali
con l’asse del fascio.
• Generalmente la regione di interazione è immersa
in campo magnetico. Si suppone che l’intensità del
campo e la prossimità dei rivelatori al vertice
primario siano tali da assumere localmente
rettilinee le traiettorie delle particelle cariche di
alta energia
q O, meglio, si assume di poter disporre di un numero
significativo di particelle di alto momento, con
traiettoria rettilinea T.A.N.S.

2

Layout

a.a. 2017/18

Layer 2

Layer 1

Beam pipe

T.A.N.S.

Illustrazioni: D.
3
Berzano

Visualizzazione di una
interazione

T.A.N.S.

a.a. 2017/18

4

•
•
•
•
•
•
•
•
•

Ipotesi di lavoro

a.a. 2017/18

Si simulino delle particelle di alto momento è traiettorie rettilinee,
almeno localmente
La simmetria dell’esperimento è cilindrica
La coordinata z del vertice ha una distribuzione normale con r.m.s. 5.3
cm
Le coordinate x e y hanno distribuzioni normali con r.m.s. 0.1 mm
Beam pipe di Berillio con raggio di 3 cm e spessore 0.8 mm
Primo layer: raggio di 4 cm. Spessore di 0.2 mm
Secondo layer: raggio di 7 cm.
I due rivelatori hanno estensione in z pari a 27 cm (corrispondenti a
un’accettanza pari a circa -1 <h<1 per particelle prodotte in collisioni
avvenute in −σ ≤ zvert ≤ σ )
Ricostruzione “fast” con smearing dei punti di impatto:
q 120 µm in direzione z
q 30 µm in direzione rf

• Si simuli lo scattering multiplo nella beam pipe e nel silicio
+ % θ (.
η = −ln-tan' *0
, & 2 )/

T.A.N.S.

5

Simulazione e ricostruzione

a.a. 2017/18

1. Simulazione:
q
q

Generazione gaussiana della posizione del vertice
Generazione della molteplicità di particelle cariche (e.g. da
distribuzione assegnata, uniforme, fissa,…)
Generazione della direzione associata ad ogni particella
(uniforme in azimut, con distribuzione assegnata in
pseudorapidità)
Trasporto delle particelle:

q
q
•
•
•

•

intersezione con la beam pipe
Scattering multiplo (spegnibile)
Posizione di impatto sui rivelatori

Ricostruzione:
q
q

Smearing gaussiano dei punti di impatto
Aggiunta di punti spuri ricostruiti (noise – particelle soft)
T.A.N.S.

6

Intersezione tracciarivelatore

a.a. 2017/18

Equazione parametrica della retta
c1 = sin ✓ cos '
x = x0 + c 1 t
c2 = sin ✓ sin '
y = y0 + c2 t dove
c3 = cos ✓
z = z0 + c 3 t
ü Il punto di coordinate x0,y0,z0 appartiene alla retta.
ü Visto che il cilindro ha asse coincidente con l’asse z, le eventuali
intersezioni tra la retta e il cilindro devono soddisfare alle seguenti
condizioni
2

2

x +y =R

2

H
H
z
2
2

Sostituendo nella prima le espressioni di x e y per la retta si trova
un’equazione di secondo grado in t:

c21 + c22 t2 + 2 (x0 c1 + y0 c2 ) t + x20 + y02
T.A.N.S.

R2 = 0
7

Intersezione tracciarivelatore

a.a. 2017/18

I valori di t che individuano le due intersezioni tra la retta e il cilindro
p
sono:

t=

con

(x0 c1 + y0 c2 ) ±
c21 + c22

= (x0 c1 + y0 c2 )

2

c21 + c22

x20 + y02

R2

ü Nel nostro caso il discriminante è sempre positivo perche il punto
utilizzato per descrivere l’equazione della retta è interno al cilindro
ü Per la stessa ragione, i due valori di t hanno segno diverso; visto
che la traiettoria di una particella è una semiretta orientata,
consideriamo il valore positivo di t.
ü Occorre verificare inoltre che:

H
H
 z0 + c 3 t 
2
2

T.A.N.S.

8

Scattering multiplo

T.A.N.S.

a.a. 2017/18

9

a.a. 2017/18

rms
Sono riportati nelle figure i valori di θ space

T.A.N.S.

approssimando b=1

10

q Si	indica	con	z’	la	direzione	della	particella	nel	sistema	di	
laboratorio

a.a. 2017/18

q Si	sceglie	un	secondo	sistema	di	riferimento	Ox’y’z’	avente	
l’asse	x’	appartenente	al	piano	xy
q L’asse	y’	si	determina	in	modo	univoco,	
imponendo	che	la	terna	x’y’z’	sia	positiva

q Il	vettore						rappresenta	la	nuova	
u
z’
direzione		della	particella,	che,	nel	sistema	
con	apici,	ha	angolo	polare						e	anomalia
ϕ'
ϑ'

u

€

OBIETTIVO
€
€

Esprimere	le	componenti	
della	nuova	direzione	della	
particella	nel	sistema	di	
riferimento	di	laboratorio

z
y’
y

ϑ'

O
€

€

2π − ϕ '

x

x’

€

Le	componenti	del	versore							nel	sistema	di	riferimento	di	
kˆ '
laboratorio	sono:

kˆ '= (sin ϑ cosϕ )iˆ + (sin ϑ sin ϕ ) ˆj + (cos ϑ ) kˆ
€
Imponiamo	che	il	versore						appartenga	al	piano	xy,	che	sia	
iˆ '
ortogonale	a						e	che	abbia	modulo	uno:
kˆ '
iˆ '= Aiˆ + Bˆj
iˆ '⋅ kˆ '= 0 ⇒ A(sin ϑ cos ϕ ) + B(sin ϑ sin ϕ ) = 0 ⇒ A = −Btan ϕ
€
1
2
iˆ '⋅iˆ€'= 1 ⇒ B 2 (1+ tan 2 ϕ ) = 1€ ⇒ B 2 =
=
cos
ϕ
2
1+ tan ϕ

iˆ '= Aiˆ + Bˆj = B −(tan ϕ )iˆ + ˆj = (cos ϕ ) −(tan ϕ )iˆ + ˆj

[

= −(sin ϕ )iˆ + (cosϕ ) ˆj

]

[

]

a.a. 2017/18

ˆj '
Il	versore						si	trova	imponendo	che	la	terna	Ox’y’z’	sia	positiva:

€

a.a. 2017/18

ˆj
iˆ
kˆ
ˆj '= kˆ '×iˆ '= sin ϑ cosϕ sin ϑ sin ϕ cosϑ =
−sin ϕ
cosϕ
0
= −(cosϕ cos ϑ )iˆ − (sin ϕ cosϑ ) ˆj + sin ϑ kˆ

Nel	sistema	Ox’y’z’	il	vettore	u ha	componenti:


u = (sin ϑ 'cos ϕ ')iˆ '+(sin ϑ 'sin ϕ ') ˆj '+ (cos ϑ ') kˆ '≡ αiˆ '+ βˆj '+ γkˆ '
€
= −α (sin ϕ )iˆ + α (cosϕ ) ˆj − β (cosϕ cos ϑ )iˆ − β (sin ϕ cosϑ ) ˆj + β sin ϑ kˆ +
+γ (sin ϑ cosϕ )iˆ + γ (sin ϑ sin ϕ ) ˆj + γ (cos ϑ ) kˆ
= [−α (sin ϕ ) − β (cosϕ cos ϑ ) + γ (sin ϑ cos ϕ )]iˆ +
+[α (cosϕ ) − β (sin ϕ cos ϑ ) + γ (sin ϑ sin ϕ )] ˆj + [β (sin ϑ ) + γ (cosϑ )] kˆ

In	notazione	matriciale,	le	componenti	del	vettore	u nel	sistema	
di	laboratorio	si	trovano	effettuando	il	prodotto:
%−sin ϕ −cosϕ cos ϑ sin ϑ cosϕ (%sin ϑ 'cos ϕ '(
'
*'
*
cos
ϕ
−sin
ϕ
cos
ϑ
sin
ϑ
sin
ϕ
sin
ϑ
'sin
ϕ
'
'
*'
*
'
*'
*
sin ϑ
cosϑ )& cosϑ ' )
& 0

€

a.a. 2017/18

Ricostruzione del vertice

a.a. 2017/18

Layer 2

• formazione di “tracklets” per
associazione di punti di impatto
ricostruiti sui due layer, aventi
piccola differenza in azimut
• Nel piano z-r, si trovano le
intersezione dei tracklet con
l’asse del fascio
• La posizione del vertice è
valutata come posizione più
probabile di intersezione dei
tracklets

Layer 1
Beam axis

T.A.N.S.Si

15

Esempio di risultato della
simulazione/ricostruzione

a.a. 2017/18

N.B. simulazione condotta
con risoluzione intrinseca
dei rivlatori inferiore a
quella proposta a voi
T.A.N.S.

16

