Simulazione decadimento
radioattivo
• Si	tratta di	un	processo intrinsecamente casuale:	
la	probabilità di	decadimento è costante e	non	
dipende dall’età del	nucleo
• La	probabilità che un	nucleo decada nel tempo	Dt
è

p = ↵ t (per ↵ t ⌧ 1)

• Consideriamo un	sistema che abbia
inizialmente N0 nuclei	instabili.
• Come	varia il loro numero nel tempo?

Simulazione decadimento
radioattivo
• L’algoritmo da	implementare è il seguente:
LOOP from t=0 to T, step Dt
Reset the number of decayed nuclei (Ndec) in the current time bin
LOOP over each remaining parent nucleus (from 0 to Ntot)
Decide if the nucleus decays:
if(gRandom->Rndm()<aDt)
increment the number of decayed nuclei in this time bin
endif
END loop over nuclei
Ntot=Ntot-Ndec
Plot Ntot vs t
END loop over time
END

M.	Masera

T.A.N.S.

2

Esercizio
• Scrivere una macro	che implementi l’algoritmo della slide	
precedente.	Mostrare i risultati nei due	casi seguenti:
1.
2.

N0=1000,				a=0.01	s-1,			Dt=1	s
N0=50000,				a=0.03	s-1,			Dt=1	s

• Rappresentare i risultati in	scala lineare e	logaritmica per	
tempi	compresi tra 0	e	300	secondi
• Confrontare i risultati con	l’andamento atteso

dN =

N ↵dt

N = N0 e

↵t

Soluzione
• Quella	che	segue	è	una	possibile	soluzione
• Implementazione:	macro	di	ROOT
• Classi	di	ROOT	sono	utilizzate	per	la	
generazione	di	numeri	casuali,	per	gli	
istogrammi	e	per	l’input-output
• La	macro	(decay.C)	è	costituita	da	2	funzioni
• Può	essere	compilata	o	eseguita	mediante	
l’interprete	CINT	esistente	in	ROOT
M.	Masera

T.A.N.S.

4

Header	files,	necessari	per
compilare	la	macro.
La	compilazione	non	è	necessaria,
Si	può	usare	l’interprete	C++
esistente	in	ROOT

T.A.N.S.

5

Le	funzioni	sono	dichiarate	qui:
Possono	essere	forniti	dei	valori
di	default	per	gli	argomenti
T.A.N.S.

6

funzione	che	implementa	
l’esponenziale	nel	formato
idoneo	per	la	classe	TF1

Linea	continua:	curva	
esponenziale	attesa.	
Istogramma:	risultato	
della	simulazione

Risultato	per:	
N0=100,
a=1´10-2	s-1
Dt=1	s

Le	fluttuazioni	statistiche	
sono	importanti
M.	Masera

T.A.N.S.

8

Diverso	valore	iniziale	per	
il	seme	del	generatore	di	
numeri	casuali	rispetto	
all’esempio	precedente

Risultato	per:	
N0=100,
a=1´10-2		s-1
Dt=1	s

M.	Masera

T.A.N.S.

9

L’importanza	delle	
fluttuazioni	è	legata	al	
valore	di	N	(numero	dei	
nuclei	residui)

Risultato	per:	
N0=5000,
a=3´10-2	s-1
Dt=1	s

M.	Masera

T.A.N.S.

10

Risultato	per:	
N0=50000,
a=3´10-2	s-1
Dt=1	s

M.	Masera

T.A.N.S.

11

Quanti	decadimenti	in	un	tempo	fisso	T	?
• Il	tempo	T sia	tale	che	il	numero	di	nuclei	
sopravvisuti	non	diminuisca	in	modo	apprezzabile
• Si	considerino	m intervalli	di	tempo	di	durata	
Dt=T/m
– Probabilità	di	1	decadimento	in	Dt à p=aNDtºbDt
– bDt=bT/m<<1
– Questo	è	vero	solo	se	N non	varia	in	T
– La	probabilità	di	osservare	n decadimenti	nel	tempo	T
è	data	dalla	distribuzione	binomiale
M.	Masera

T.A.N.S.

12

n
( m−n )
$
'
$
'
m!
m!
β
T
β
T
m−n
(
)
P(n;m, p) =
p n (1− p)
=
& ) &1− )
n!( m − n )!
n!( m − n )! % m ( %
m(

Nel	limite	di	m grande,	ossia	Dtà0	:
m
+
$ βT '
− βT
&1− ) → e %
m(
n
-$ βT '−n
βT ) − βT
(
e
&1− ) →1 , ⇒ P ( n;βT ) →
%
m(
n!
m!
n
→m ( m − n )!
-.

La	binomiale	tende	ad	una	poissoniana	di	
parametro µ = βT
M.	Masera

T.A.N.S.

13

Esercizio
• Modificare	il	programma	dell’esercizio	precedente	in	
modo	da	simulare	un	esperimento	di	conteggio	del	
numero	di	decadimenti	nel	tempo	T
• Permettere	la	ripetizione	degli	esperimenti
• Generare	1000	esperimenti	per	i	casi	seguenti
– N0=1000,	a=2.5´10-5 s-1,	Dt=1	s,	T=100	s
– N0=1000,	a=2´10-4 s-1,	Dt=1	s,	T=100	s

• Confrontare	la	distribuzione	di	n per	1000	
esperimenti	con	le	distribuzioni	poissoniana	e	
binomiale
M.	Masera

T.A.N.S.

14

Soluzione
• Quella	che	segue	è	una	possibile	soluzione
• Implementazione:	macro	di	ROOT
• Classi	di	ROOT	sono	utilizzate	per	la	
generazione	di	numeri	casuali,	per	gli	
istogrammi	e	per	l’input-output
• La	macro	(poisson.C)	è	costituita	da	5	funzioni
• Può	essere	compilata	o	eseguita	mediante	
l’interprete	CINT	esistente	in	ROOT
M.	Masera

T.A.N.S.

15

headers

Definizione	degli
istogrammi

Valutazione
Distribuzioni
teoriche

Loop	principale

Funzione	che	valuta
il	numero	di	nuclei
che	decadono	ne
tempo	T

Poissoniana
e	binomiale

∞

Γ(α ) =

∫ x(

α −1) −x

e dx ⇒ Γ(α + 1) = αΓ(α )

0

Γ( n + 1) = n!

€

Questa	funzione	è	tratta	dal	§ 6.1	di Numerical	
Recipes	e calcola il logaritmo della funzione
gamma.	Per	la	valutazione del	fattoriale in	ROOT	si
può usare TMath::Gamma(Double_t)

Risultato	per:	N0=1000,	a=2.5´10-5,	Dt=1	s,	T=100	s

binomiale
poissoniana

M.	Masera

T.A.N.S.

19

L’approssimazione	
poissoniana	alla	binomiale	
è,	in	questo	caso,	eccellente

M.	Masera

T.A.N.S.

20

Risultato	per:	N0=1000,	a=2´10-4,	Dt=1	s,	T=100	s

binomiale
poissoniana

M.	Masera

T.A.N.S.

21

Per	a=2´10-4 e	m=100,	si	
notano	differenze	tra	la	
poissoniana	e	la	binomiale	
anche	se	entrambe	sono	in	
accordo	con	la	simulazione

M.	Masera

T.A.N.S.

22

Distribuzioni	generali	(1)
• In	generale	non	è	sufficiente	utilizzare	sequenze	di	
numeri	casuali	distribuiti	uniformemente	à In	molti	
problemi	è	necessario	disporre	di	numeri	casuali	
estratti	da	densità	di	probabilità	diverse,	quali	la	
normale,	l’esponenziale,	la	poissoniana,	etc
• In	ROOT	sono	disponibili,	nella	classe	TRandom,	
generatori	per	le	densità:
–
–
–
–
–
M.	Masera

Gaussiana
Esponenziale
Binomiale
Poissoniana
Landau

T.A.N.S.

23

Distribuzioni	generali	(2)
• In	alternativa	si	possono	usare	i	metodi
– dell’inversione
– della	reiezione

• INVERSIONE
– Si	usa	quando	la	distribuzione	integrale	(cumulativa)	di	
probabilità	è	facilmente	invertibile
f (x) Densità	di	probabilità	in [ x1 , x2 ]

x

F ( x) = ∫ f (t )dt con F ( x2 ) = 1
La	funzione	cumulativa	di	probabilità	è
x
Visto	che	F(x)	ha	distribuzione	uniforme	tra	0	e	1,	si	estrae	un	numero	casuale	
con	distr.	uniforme	in	questo	intervallo	e	si	determina	x	come
1

x = F −1 (u )
M.	Masera

T.A.N.S.

24

inversione
Si	estrae	
uniformemente	u	tra	
0	e	1

u

F(x)=½Öx per	
0<x£4
x

f(x)=1/(4Öx) per	
0<x£4

M.	Masera

T.A.N.S.

Si	ricava	x	come
x=4´u2

25

Risultato	per	10000	estrazioni

f(x)µ1/(4Öx)

M.	Masera

T.A.N.S.

26

Reiezione
Obiettivo:	estrarre	numeri	casuali	distribuiti	secondo	la	densità

f (x )

x ∈ [xmin , xmax ]

[ ]

A	partire	da u1 , u 2 casuali con densità uniforme in 0,1
Si	estrare	la	coppia	xT,yT:

xT = xmin + ( xmax − xmin ) u1
yT = fbigu2

con

fbig ≥ f (x) ∀ x ∈ [ xmin , xmax ]

xT accettato se f ( xT ) > yT

fbig

[xT,yT]

M.	Masera

T.A.N.S.

27

Limiti	del	metodo	della	reiezione
• È	in	generale	un	metodo	poco	efficiente	dal	
punto	di	vista	dell’uso	della	potenza	di	calcolo
• Non	è	adatto	ad	essere	utlizzato	con	funzioni	
che	presentino	picchi	pronunciati	(Il	tempo	di	
CPU	aumenta	molto)
• Non	può	essere	applicato	se	ci	sono	poli	o	
estremi	di	integrazione	all’infinito

M.	Masera

T.A.N.S.

28

Importance	sampling
Si	può	migliorare	l’efficienza	del	metodo	effettuando	il	campionamento	non	in	
un	“rettangolo”	ma	in	una	regione	definita	da	una	funzione	g(x)	maggiorante	di	
f(x).
Se	si	è	in	grado	di	generare	numeri	casuali	distribuiti	secondo	g(x) per	esempio	
con	il	metodo	dell’inversione,	la	procedura	della	reiezione	diventa:

1. Si	estrae	x	secondo	g(x)	

con	la	tecnica	
dell’inversione
2. Si	estrae	u	con	
distribuzione	uniforme	tra	
0	e	g(x)
3. Se	u<f(x)	si	accetta	x
M.	Masera

f(x)

g(x)

Esempio di	importance	sampling

funzione da	campionare
2

sin x
f (x) =
x2

Funzione maggiorante

y = 0.05 se |x| > 2.6

y = 1 se |x|  2.6

Esempio di	importance	sampling

Esempio di	importance	sampling

Integrali
Il	metodo	della	reiezione	può	essere	usato	per	valutare	integrali
x max

I=

∫

f ( t )dt ≅

x min

NA
f big ( x max − x min )
NP

dove	NA è	il	numero	di	valori	accettati	e	NP il	numero	delle	prove.	L’accuratezza	del	
risultato	può	essere	stimata	a	partire	dall’errore	su	NA,	che	è	dato	dalla	distribuzione	
binomiale:
L’errore	su	I è	pertanto:
δN A = p(1− p) N P con p ≈ N A N
P
2
2
$
'
$
'
∂I
δN A 2
2
2
Da	cui,	si	trova:
(δI) = (δN A ) &
) =&
) I
% ∂N A ( % N A (
2
2
!δI $ !δNA $ NA ! NA $
1
1
NP
1 ! 1− p $
1− p)
=
& =
#1−
& NP 2 ≅
# & =#
(
#
&
" I % " NA % NP " NP %
NA NP
NA NP " p %

La	precisione	relativa	aumenta	lentamente	con	il	numero	delle	prove	 dI/Iµ1/ÖNP
M.	Masera

T.A.N.S.

33

