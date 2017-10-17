Il	metodo	Monte	Carlo
• Il	metodo	Monte	Carlo	è	una	tecnica	
impiegata	per	calcolare	probabilità	e	quantità	
correlate	impiegando	sequenze	di	numeri	
casuali.												Non	ha	senso	parlare	di	singoli	
numeri	casuali,	ma	di	sequenze
• Viene	utilizzato	per:
– simulazione	di	fenomeni	naturali
– simulazione	di	apparati	sperimentali
– calcolo	di	integrali
M.	Masera

T.A.N.S.

1

Monte	Carlo
Procedura	generale:
• si	estrae	una	sequenza	di	m numeri	casuali,	aventi	distribuzione	
uniforme	nell’intervallo	[0,1].
N.B.	Si	possono	usare	anche	numeri	interi	tra	0 e	un	 valore	
massimo,	di	solito	legato	alla	lunghezza	della	 word	
nell’elaboratore	utilizzato

x = (x1 ,, xn )
• Si	usa	la	sequenza	per	produrne	una	seconda																										
!
distribuita	secondo	la	funzione																a	cui	si	è	interessati
f x

• La	sequenza																							
x = (x1 ,, xn ) costituisce	il	pool	di	dati	simulati

()

M.	Masera

T.A.N.S.

2

Generatori	di	numeri	casuali	(1)
• In	una	sequenza	di	numeri	casuali,	oltre	
all’uniformità	della	distribuzione	nell’intervallo	[0,1],	
si	deve	avere	assenza	di	correlazione	tra	elementi	
successivi	nella	sequenza
– tiro	di	una	moneta	ripetuto	32	volte	per	avere	una	word	di	
32	bit.	Procedura	da	ripetere	N volte	per	ottenere	una	
sequenza	di	N termini	....	
– processi	intrinsecamente	casuali	(arrivo	di	raggi	cosmici,	
white	noise	di	un	fototubo,	decadimento	radioattivo)

• Esistono	tabelle	con	sequenze	di	alcuni	milioni	di	
numeri	casuali	
M.	Masera

T.A.N.S.

3

Generatori	di	numeri	casuali	(2)
• Generatori	di	numeri	pseudocasuali
– la	sequenza	è	riproducibile,	perché	l’algoritmo	di	
generazione	è	deterministico

• Caratteristiche	a	cui	un	generatore	deve	
sottostare:
– indipendenza	statistica
– Periodo	di	ripetizione	lungo	
– ...	la	sequenza	“sembra”		casuale
M.	Masera

T.A.N.S.

4

Generatore ANSI	C
#if !defined(__CINT__) || defined(__MAKECINT__)
#include<stdlib.h>
#endif
void rnInit(UInt_t seed = 1234){
srand(seed);
}
Double_t getrand(){
return rand()/((double)RAND_MAX+1);
}

M.	Masera

T.A.N.S.

5

Esempi	di	generatori
• Middle	square	(Von	Neumann,	1946)
In +1 = {m cifre centrali di In2 };

I0 numero a m cifre

Esempio:
5772156649

2

Þ 3331779238 0594909291
In+1

In
M.	Masera

m = 10

T.A.N.S.

6

v Vengono	generati	numeri	interi	a	m	cifre.	In	generale	gli	
algoritmi	producono	numeri	interi	tra	0	e	MAX	e	restituiscono	un	
valore	in	virgola	mobile	definito	da	rn=In/(MAX)
v Il	metodo	di	Von	Neumann	presenta	dei	problemi:
v se	m	è	piccolo,	la	sequenza	è	breve
6100 2 = 37210000

2100 2 = 4410000

Si	riottiene	6100	!

4100 = 16810000
2

8100 2 = 65610000
v0	ripete	se	stesso
vUsando	38	bit,	si	possono	avere	sequenze	fino	a	7.5´105	numeri
M.	Masera

T.A.N.S.

7

Metodi	lineari	congruenti
• Lehmer,	1948	(valore	di	partenza	I0 ,	detto	seme		della	
sequenza):
I n +1 = (aI n + c ) modulo m
a>0
c³0
m > I 0 , a, c

• La	scelta	dei	parametri	è	cruciale.	Per	esempio	a=c=	I0=7	e	
m=10	danno	la	sequenza:		7,6,9,0,7,6,9,0,.....			!!!!!!
• Se	c=0	l’algoritmo	è	un	po’	più		veloce	e	il	metodo	prende	il	
nome	di	moltiplicativo	congruente
M.	Masera

T.A.N.S.

8

Scelta	dei	parametri
• m deve	essere	grande	in	quanto	il	periodo	non	può	
eccederne	il	valore.	A	32	bit,	m=231~2´109.
• M.	Greenberger	ha	provato	(1961)	che	la	sequenza	ha	
periodo	m se	e	solo	se	vengono	soddisfatte	le	condizioni
–
–
–
–

c	e	m sono	primi	fra	loro
(a-1) è	multiplo	di	tutti	i	divisori	primi	di	m
Se	m è	multiplo	di	4,	anche	(a-1) lo	è
Per	c=0 il	periodo	è	di	solito	~m/4 per	opportuna	scelta	del	
seme	e	di	m

• ...	La	scelta	dei	parametri	non	è	facile

M.	Masera

T.A.N.S.

9

RANDU
• RANDU	era	un	generatore	diffuso	sui	mainframe	IBM	
negli	anni	60
I n +1 = 65539 ´ I n modulo 2 31

• Questo	generatore	aveva	un	grave	problema:	c’erano	
correlazioni	tra	i	numeri	di	una	sequenza:	se	si	
usavano	3	numeri	in	sequenza	come	coordinate	di	
uno	spazio		3D,	si	osservava	che	i	numeri	si	
disponevano	in	15	piani
M.	Masera

T.A.N.S.

10

RANDU.	
Distribuzione	2D	è	
OK

M.	Masera

T.A.N.S.

11

A	3D,	si	osservano	dei	piani.
Nel	1968,	Marsaglia	ha	
dimostrato	che	questo	è	un	
problema	generale	per	tutti	i	
generatori	moltiplicativi	
congruenti.	I	limiti	massimi	
nel	numero	di	iperpiani	in	
uno	spazio	n	dimensionale	è	
2953	per	n=3,	ma	scende	a	
41	per	n=10.
RANDU	è	stato	sostituito	da:

I n +1 = 69069 ´ I n modulo 2 31
M.	Masera

T.A.N.S.

12

Minimal	Standard	Generator
• Proposto da Park	e Miller	nel 1969
–
–
–
–

Moltiplicativo congruente
a=75=16807						
m=231-1=2147483647
Periodo:	circa	2.1´109

• Esercizio:
– Implementare il generatore in	C/C++	
– CAVEAT:	non	si può implementare direttamente a	32	bit.	Si	
veda l’algoritmo di Schrage;	Num.	Recipes	Cap	7.1

M.	Masera

T.A.N.S.

13

Generatori	più	recenti
• Per	aumentare	il	periodo	si	può	aumentare	il	
numero	di	semi
• RANMAR	(1987)	ha	103	semi	e	sequenze	di	
periodo	1043	!	Implementato	nella	Cernlib
(V113)	in	fortran
• RANLUX	(Cernlib V115)	ha	periodo	>10171
M.Lusher,	F.James Computer	Phys.	Commun.	
79	(1994)	p.	100
• Altri:	ran2	(Numerical Recipes)	e	RANECU
M.	Masera

T.A.N.S.

14

Generatori	in	ROOT
• Sono	implementati	mediante	la	classe	TRandom:	generatore	
veloce	con	periodo	109 (breve!).	Basato	su	un	metodo	lineare	
congruente

• TRandom1	(eredita	da	TRandom)	implementa	RANLUX	
• TRandom2	(eredita	da	TRandom)
– ha	periodo	1026
– Ha	uno	stato	di	sole	3 word	da	32	bit

M.	Masera

T.A.N.S.

15

Generatori	in	ROOT
• TRandom3	(eredita	da	TRandom):

– implementa	il	generatore	Mersenne-Twister,	che	ha	periodo	219937-1	
(»106002).
– Supera	il	k-distribution	test	a	623	dimensioni	(cfr	Numerical	Recipes,	cap	7	
per	una	descizione	del	test)	à 623-tuple	su	un	intero	periodo	sono	
equidistribuite	sono	equidistribuite	su	un	ipercubo	a	623	dimensioni	(cfr.	
RANDU!!!)	vedi:	
http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html

• Il	Mersenne-Twister è	il	generatore	usato	in	molti	esperimenti	
attuali	per	le	simulazione	(e.g.	ALICE)

M.	Masera

T.A.N.S.

16

Generatori	in	ROOT

M.	Masera

T.A.N.S.

17

Mersenne-Twister

M.	Masera

T.A.N.S.

18

Distribuzioni	in	TRandom

Performance

BAD

SLOW

FAST

GOOD
(default)

