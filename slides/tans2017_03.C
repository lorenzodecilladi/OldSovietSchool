DISTRIBUZIONI	DI	PROBABILITÀ
Nelle	slides	che	seguono	sono	richiamate	le	definizioni	
delle	più	comuni	funzioni	densità	di	probabilità.
Per	le	dimostrazioni	cfr.	un	qualsiasi	testo	di	probabilità	
e	statistica	(e.g.	Loreti,	Galeotti,	etc.)

M.	Masera

T.A.N.S.

1

Distribuzione	uniforme
Una	variabile	aleatoria	reale	x	è	distribuita	uniformemente	su	di	
un	intervallo	reale	[a,b]	se:
ì 1
a £x£b
ï
f ( x;a , b ) = í b - a
ï0 altrimenti
î

µ=

σ

2

a +b
2

β − α)
(
=

2

12

M.	Masera

T.A.N.S.

2

Distribuzione	uniforme
Per	una	qualsiasi	variabile	aleatoria	con	densità	di	
probabilità	f(x) e	distribuzione	integrale	F(x),	la	variabile	
y=F(x)	ha	distribuzione	uniforme	nell’intervallo	[0,1].
Infatti	F(x)	ha	valori	tra	0	e	1	e	ha	densità	di	probabilità	
g(y)=1:
y ≡ F ( x) ⇒

dy d x
=
f ( t ) dt = f ( x )
∫
dx dx −∞

dx
dy
g( y ) = f ( x )
= f ( x)
dy
dx

−1

=1

(0 ≤ y ≤ 1)

Questa	è	una	proprietà	estremamente	importante	perché	fornisce	
il	mezzo	per	ottenere	numeri	casuali	con	densità	di	probabilità	f(x)
€
a	partire	da	numeri	casuali	distribuiti	uniformemente		à
metodi	
M.	Masera
T.A.N.S.
3
Monte	Carlo

Distribuzione	binomiale	(1)
Si	considerino	N prove	indipendenti	(bernoulliane)	che	possano	portare	
ciascuna	ad	un	risultato	S (successo)	con	probabilità	p.	
q=1-p è	la	probabilità	di	non	ottenere	S.	Il	numero	di	combinazioni	che	
portano	a	n successi	su	N prove	è
!N$
N!
N
Cn = # & =
" n % n!( N − n ) !
La	probabilità	di	ottenere	quindi	n successi	in	N prove	è

N!
( N−n)
n
f (n; N, p) =
p (1− p)
n!( N − n ) !
Questa	è	una	distribuzione	binomiale	nella	v.a.	discreta	n con	parametri	N e	
p
M.	Masera

T.A.N.S.

4

Distribuzione	binomiale	(2)
Sia	y il	numero	di	volte	in	cui	S	si	verifica	in	una	prova	(y=0	,1):

E
⇥ [y]
⇤
2
E y
V [y]

=
=
=

1⇥p+0⇥q =p
p
⇥ 2⇤
2
E y
E [y] = p

p2 = pq

Utilizzando	la	v.a.	ausiliaria	y,	il	numero	n di	successi	su	N prove	è														
N

n = ∑ yi
i=1

La	media	e	la	varianza	della	binomiale	si possono	esprimere	come:
€

$N ' N
µn ≡ E [ n ] = E &∑ y i ) = ∑ E [ y i ] = Np
% i=1 ( i=1

M.	Masera

N
N
$
'
σn2 = V &∑ y i ) = ∑V [ y i ] = Npq
% i=1 ( i=1
T.A.N.S.

5

Distribuzione	binomiale	(3)
Esempi	
di
binomiale

Applicazione:	si	osservano	N	decadimenti	di	J/y ,	di	cui	n	sono	J/y à µ+µ-.	Il	
numero	n	ha	distribuzione	binomiale	e	p	è	il	“branching	ratio”	della	J/y in	µ+µ-.	
M.	Masera

T.A.N.S.

6

Distribuzione	di	Poisson
La	distribuzione	binomiale,	nel	limite	di	infinite	prove	(Nà ¥)	e	
di	pà0,	con	µ=Npàn tende	a

ν n −ν
f ( n;ν ) = e
n!

n≥0

µn = σ n2 = ν
Rappresenta	la	probabilità	che	si	verifichino	esattamente	n
eventi	in	un	intervallo	x (spesso	di	tempo)	posto	che	questi	siano	
indipendenti	ed	abbiano	tasso	medio	n.	Ad	esempio	la	
probabilità	di	osservare	n decadimenti	in	una	massa	nota	di	
sostanza	radioattiva	in	un	tempo	t
M.	Masera

T.A.N.S.

7

Esempi
Di
poissoniana

M.	Masera

T.A.N.S.

8

Distribuzione	esponenziale
La	distribuzione	esponenziale	è	tipica	dei	processi	di	
decadimento	ed	è	caratterizzata	da	un	unico	parametro	che	
coincide	con	il	valor	medio.

1
f ( x;ξ ) = e
ξ
1
µ=
ξ

∫

1
σ =
ξ
2

∞
0

−

−

x
ξ

x
ξ

x e dx = ξ
∞

∫0 (x − ξ )

M.	Masera

x ≥0

2

−

x
ξ

e dx = ξ 2
T.A.N.S.

9

Distribuzione	normale
La	distribuzione	normale	(o	di	Gauss)	per	la	v.a.	continua	x,	con	
valor	medio	µ e	varianza	s2,	è	definita	da:

f ( x;µ,σ ) =
2

2
parametri

M.	Masera

1
2πσ

e
2

−

( x− µ )
2σ 2

2

Caso	particolare:
normale	ridotta.
µ=0	e	s=1	

normalizzazione

T.A.N.S.

10

Teorema	del	limite	centrale
La	somma	di	n	variabili	aleatorie	indipendenti	xi,	
dotate	di	densità	di	probabilità	arbitrarie	con	media	
e	varianza	finite,	segue	una	densità	di	probabilità	
gaussiana,	nel	limite	di	nà¥
n
#
& n
E % y = ∑ x i ( = ∑ µi
$
' i=1
i=1

Il	prodotto	di	n	variabili	
aleatorie	non	è	gaussiano,	ma	il	
suo	logaritmo	sì

n

V [ y ] = ∑σ i2
i=1
M.	Masera

T.A.N.S.

11

Teorema	del	limite	centrale:	esempio	con	somma	di	
distribuzioni	che	seguono	una	densità	uniforme	su	un	
dominio	non	connesso.

Fit	gaussiano

M.	Masera

T.A.N.S.

12

v Come	conseguenza	del	teorema	del	limite	centrale,	la	
distribuzione	di	Gauss	si	applica	a	tutti	quei	fenomeni	che	sono	
somma	di	diversi	contributi	indipendenti,	come	accade	di	solito	nel	
caso	degli	errori	statistici	di	misura.	
v Per	n	finito,	il	teorema	è	una	buona	approssimazione	se	non	ci	
sono	termini	della	somma	dominanti
v Approssimazione	accettabile:	deflessione	per	diffusione	multipla	
coulombiana	di	una	particella.	Singole	interazioni	danno	
occasionalmente	luogo	a	diffusioni	grandi	che	producono	code non	
gaussiane
v Approssimazione	non	accettabile:	perdita	di	energia	di	una	
particella	carica	in	un	mezzo	à distribuzione	di	Landau
M.	Masera

T.A.N.S.

13

Funzioni	caratteristiche	/	1

M.	Masera

T.A.N.S.

14

Funzioni	caratteristiche	/	2

M.	Masera

T.A.N.S.

15

Funzioni	caratteristiche	/	3

M.	Masera

T.A.N.S.

16

Funzioni	caratteristiche	/	4

M.	Masera

T.A.N.S.

17

Teorema	del	limite	centrale	/1
Si considerano n variabili aleatorie xj indipendenti con medie µj e
varianze s2 (il teorema vale anche se le varianze non sono uguali)

M.	Masera

T.A.N.S.

18

Teorema	del	limite	centrale	/2

M.	Masera

T.A.N.S.

19

Teorema	del	limite	centrale	/3

Se le varianze non sono uguali tra loro, la somma delle variabili
aleatorie xj è gaussiana con varianza data dalla somma delle
varianze sj2.
M.	Masera

T.A.N.S.

20

Distribuzione	normale	multivariata

Nel	caso	di	un	set	di	v.a.																										
x = (x1 ,, xn ) la	densità	di	probabilità	

è:	

 
f ( x;µ,V ) =

dove E [ x i ] = µi
€Per	n=2:

$ 1   T −1   '
n
1 exp&− ( x − µ) V ( x − µ))
(
(2π ) 2 V 2 % 2
1

e V è la matrice di covarianza :

Vij = cov[ x i , x j ]

f ( x1, x 2 ;µ1, µ2 ,σ1,σ 2 , ρ) =
2
2
24
,&
/64
)
&
)
&
)
&
)
1
1
x
−
µ
x
−
µ
x
−
µ
x
−
µ
2
1
1
2
2 1
.( 1 1 + + ( 2
=
exp
−
−
2
ρ
3
+
(
+
(
+7
2
2
' σ1 *' σ 2 *1048
45 2(1− ρ ) .-' σ1 * ' σ 2 *
2πσ1σ 2 1− ρ

cov[ x1, x 2 ]
con ρ =
σ1σ 2
€

M.	Masera

T.A.N.S.

21

Distribuzione	c2
La	distribuzione	c2 della	v.a.	continua	
x è	definita	da:
∞

dove Γ(α ) =

∫ x(

f ( x;n ) =

1
n

2 2 Γ( n /2)

x

n
x
−1 −
2
2

e

x ≥0

α −1) −x

e dx ⇒ Γ(α + 1) = αΓ(α )

0

€

E[x]=n e V[x]=2n con n=1,2,...
n è detto numero di gradi libertà

M.	Masera

T.A.N.S.

22

Distribuzione	c2
L’importanza	di	questa	distribuzione	deriva	dal	fatto	che,	nel	caso	
di	v.a.	xi indipendenti	gaussiane,	la	somma:
n

z=∑
i=1

( x i − µi )
σ i2

2

segue	una	distribuzione	c2 con	n gradi	di	
libertà

Per	grandi	valori	di	n,	la	distribuzione	tende	ad	una	gaussiana	con	
valor	medio	n e	varianza	2n
Viene	utilizzata	nelle	procedure	di	minimizzazione	à test	del	c2

M.	Masera

T.A.N.S.

23

Distribuzione	di	Breit-Wigner
La	distribuzione	di	Breit-Wigner	(o	Cauchy)	è	definita	come:
f ( x;ϑ ,d ) =

1
πd

Γ
2

1
1
=
% x − ϑ (2 π % Γ (2
2
1+ '
+
x
−
ϑ
*
' * (
)
& d )
&2)

G = 2d

La	funzione	integrale	è	definita	e	la	
condizione	di	normalizzazione	è	soddisfatta.	
Nessuno	dei	momenti	esiste

% x −ϑ (
1 1
F ( x;ϑ ,d ) = + arctan'
*
& d )
2 π
M.	Masera

T.A.N.S.

24

Distribuzione	di	Breit-Wigner
• Il	parametro	q è	il	valore	più	probabile	della	
distribuzione	(moda)
• Il	parametro	G=2d	è	un	parametro	di	
dispersione	ed	indica	la	larghezza	totale	a	
metà	altezza
• La	Breit-Wigner	è	usata	per	descrivere	lo	
spettro	in	massa	invariante	delle	risonanze	
(e.g.	r,	f,...):	q è	la	massa	e	G il	tasso	di	
decadimento	(reciproco	della	vita	media)
M.	Masera

T.A.N.S.

25

Distribuzione	di	Landau
La	densità	di	probabilità	per	la	perdita	di	energia	D da	parte	di	una	particella	carica	che	
attraversi	un	dato	spessore	di	materiale	è

Spessore	attraversato
Perdita	di	energia	più	probabile
con

Energia	di	ionizzazione

M.	Masera

Costante	di	Eulero:	0.5772

T.A.N.S.

26

Distribuzione	di	Landau
La	funzione	f è	stata	calcolata	da	Landau:

La	funzione	è	normalizzabile.
Tuttavia,	come	per	la	
distribuzione	
Breit-Wigner,	la	media	ed	i	
momenti	di	ordine	più	elevato	
non	sono	definiti

M.	Masera

T.A.N.S.

27

M.	Masera

T.A.N.S.

28

