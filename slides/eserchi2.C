Test	del	c2 (di	Pearson)
q È	un	test	che	può	essere	applicato	ad	una	distribuzione	di	una	v.a.	x
q Si	ha	un	istogramma	con	N celle	e	con	ni dati	nella	cella	i-ma.	Il	numero	di	dati	
atteso	sia	ni
• Se	i	dati	in	ciascuna	cella	sono	distribuiti	indipendentemente	l’uno	dall’altro	
poissonianamente	con	parametri		ni e	se	ni	è	relativamente	grande	(ni	³ 5	" i),	
allora	la	statistica
2
N

χ =∑
2

i=1

(n i − ν i )
νi

che	quantifica	lo	scarto	dei	dati	rispetto	alle	attese, segue	la	distribuzione	c2 con	N	
gradi	di	libertà

€

M.	Masera

T.A.N.S.

1

Test	del	c2
• Il	valore	osservato	di	c2 fornisce	un	livello	di	significatività
∞

P=

∫ f ( x;N )dx =

χ2

1
N

∞

∫x

2 2 Γ( N /2) χ 2

N
x
−1 −
2
2

e

dx

• Visto	che	E[x]=N,	è	consuetudine	quotare	il	rapporto	c2 /N come	
misura del	livello di accordo anche se	il livello di significatività
2 sia da N	e pertanto è preferibile quotarli
dipende
sia
da
c
€
entrambi.
N
• Il	numero totale di ingressi ntot = ∑ ni può essere considerato esso
i =1
stesso come	una
v.a.	poissoniana
con	valore atteso
N
ν tot = ∑ν i
i=1

ntot invece fisso,	allora i contenuti delle celle ni sono
• Se								è
distribuiti secondo una multinomiale con	valori medi ν i = ntot pi
€
M.	Masera

T.A.N.S.

2

Test	del	c2
•In	questo	caso,	la	statistica
2
N
n i − npi )
(
2
χ =

∑
i=1

npi

segue	una	distribuzione	c2 con	N-1 gradi	di	
€
libertà.
In	generale	se	si	stimano	K	parametri	dai	dati,	il	
numero	di	gradi	di	libertà	si	riduce	di	K
M.	Masera

T.A.N.S.

3

Esempio	(1)
In	questo	esempio,	c2 =16,13	per	N=12	gradi	di	libertà.	
Tutte	le	celle	dell’istogramma	hanno	al	più	5	conteggi:	la	
statistica	c2 non segue	la	distribuzione	di...	c2 in	questo	
caso!!
FONDO
ATTESO

DATI
M.	Masera

T.A.N.S.

4

Esempio	(2)
• In	questi	casi,	il	test	di	Pearson può	ancora	essere	
effettuato,	ma	non	si	può	esprimere	il	livello	di	
significatività	osservato	ricorrendo	alla	densità	c2.
• Per	valutare	un	P-value,	occorre	costruire	la	
distribuzione	con	una	tecnica	Monte	Carlo:
– Si	generano	dei	conteggi	ni secondo	poissoniane di	
parametro	ni
– Si	valuta	il	c2
– Si	registra	il	risultato	in	un	istogramma
– Si	ripete	N volte,	con	N grande

• La	distribuzione	può	essere	integrata	numericamente	
per	valutare	la	probabilità.	
M.	Masera

T.A.N.S.

5

Risultato	della
simulazione.
Ci	sono	differenze	rilevanti
Soprattutto	nelle	code

c2 ,	12	gradi	di	libertà
simulazione

M.	Masera

T.A.N.S.

c26

La	differenza	è	evidente
se	si	adotta	la	scala
logaritmica!

M.	Masera

T.A.N.S.

c7 2

Esercizio
12	celle	da
0	(estremo	inferiore)	a	
24	(estremo	superiore)
Si	valuti	il	c2 ed	il	P	value,	usando	per
Il	fondo	atteso	la	funzione

0.169 × (10 − 0.01× x )
Si	generi	la	distribuzione	per	la	statistica	
c2
usando	una	tecnica	Monte	Carlo.
I	risultati	sono	quelli	mostrati	nelle	slide	
precedenti
M.	Masera

T.A.N.S.

Centro
della
cella

ni

1

1

3

3

5

1

7

4

9

3

11

5

13

2

15

1

17

1

19

0

21

1

23

3
8

Esercizio	(2)
Se	si	moltiplica	per	
1000	il	fattore	di	
normalizzazione	
della	curva	teorica,	si	
vede	che	una	
distribuzione	chi-2	a	
12	gradi	di	libertà	è	
perfettamente	
adeguata

M.	Masera

T.A.N.S.

9

Esercizio	(3)

M.	Masera

T.A.N.S.

10

