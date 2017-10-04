TECNICHE	DI	ANALISI	NUMERICA	
E	SIMULAZIONE
Corso	di	Laurea	Magistrale	in Fisica
Anno	Accademico	2017/18

M.	Masera

T.A.N.S.

1

Presentazione	del	corso	(1)
• Docente:

Massimo	Masera
Dipartimento	di	Fisica	Sperimentale
Tel.	011	6707373	(Primo	piano,	Istituto	vecchio)
E-mail:		masera@to.infn.it
URL:	http://www.to.infn.it/~masera
Orario	delle	lezioni:	tutti	i	giorni	dalle	9	alle	11	in	Aula	
Informatica	B	(se	ci	stiamo)

Dovremmo	fare	lezione	nelle	nuove	aule	informatiche	al	primo	piano	
interrato… Tuttavia	i	lavori	di	sistemazione	non	sono	stati	ultimati	e	
navigheremo	a	vista
M.	Masera

T.A.N.S.

2

http://personalpages.to.infn.it/~masera/

Per	accedere al	
materiale:
Username:	tans09
Password:	Bayes2009

Presentazione	del	corso	(2)
• 6 crediti:	~60	ore	di	lezione	ed	esercitazione al	
computer.
• Scopi	del	corso:
– Interpretazione	dei	dati	sperimentali:	concetti	di	incertezza	
e	probabilità
– Simulazioni	mediante	metodi	Monte	Carlo
– Strumenti	statistici	per	l’analisi	dei	dati	
– Applicazioni	al	computer	
• ambiente	Unix:	Linux,	Mac	OS	X	(no	Windows)	
• uso	di	strumenti	quali	ROOT e	programmi	in	C/C++	utilizzati	nella	
Fisica	delle	Alte	Energie

M.	Masera

T.A.N.S.

4

Presentazione	del	corso	(3)
• Prima	approssimazione:	

– Questo non	è un	corso di programmazione

• Seconda approssimazione:

– Visto che si userà il C++	e l’ambiente ROOT	per	la	parte	pratica,	finiremo
per	(ri)vedere le	basi del	C++.	L’approccio sarà comunque di tipo “bottomup”	(traduzione:	“se	ho	questo problema come	lo	risolvo con	il C++	e
ROOT”)

• L’effettivo programma da	svolgere verrà definito strada facendo,	
come	sempre
• Modalità	di	esame:
– Prova	orale	sugli	argomenti	trattati	a	lezione
– Esecuzione	di	una	simulazione	MonteCarlo	(singoli	o	“gruppi”	di	2	
persone)	da	discutere	all’esame

• N.B.	il	programma,	insieme	a	una	breve relazione	che	lo	illustri	e	presenti	i	risultati	va	
consegnata	qualche	giorno	prima	dell’esame

• Sono in	debito con	il prof.	Ramello,	che tiene un	corso simile	per	
finalità e	contenuto al	Dottorato di	Ricerca in	Fisica
M.	Masera

T.A.N.S.

5

A	proposito	di	C++	e	ROOT
• In	principio	era	il	Fortran

– Primo	linguaggio	ad	alto	livello:	1956
– Versione	più	usata:	Fortran	77	(ISO	1539:1980)
– Ancora	usato	per	il	calcolo	scientifico,	anche	se	era	(a	torto)	
considerato	superato	quando	ho	cominciato	gli	studi	universitari
– L’ultima	revisione	dello	standard	è	del	2008	(ISO/IEC	1539-1:2010)

• I	limiti	del	Fortran	per	quanto	riguarda	il	trattamento	di	grandi	moli	
di	dati	e	la	nascita	di	nuovi	paradigmi	di	calcolo,	quali	la	
programmazione	ad	oggetti,	hanno	portato	all’adozione	del	C++
nella	Fisica,	in	particolare	nella	fisica	delle	alte	energie,	a	partire	
dalla	metà	degli	anni	90.
• Nel	corso	dell’ultimo	decennio	si	è	anche	imposto	l’uso	di	linguaggi	
più	semplici	e	flessibili	quali	il	Python in	particolare	per	l’analisi	dati

A	proposito	di	C++	e	ROOT
•
•
•
•
•
•
•
•
•
•

Il	C++	è	nato	come	estensione	del	C	(il	primo	nome	era	C	con	classi)	a	partire	dal	
1979	su	iniziativa	di	Bjarne Stroustrup che	lavorava	ai	Bell	Laboratories.
Nel	1985 B.S.	pubblicò	la	prima	edizione	del	The	C++	Programming	Language,	un	
libro	che	in	assenza	di	uno	standard	ufficiale	servì	come	documentazione	de	facto	di	
questo	linguaggio.
Il	primo	standard	è	il	C++98	(ISO/IEC	14882:1998)	
Una	major	revision del	linguaggio	è	il	C++11	(ISO/IEC	14882:2011)
Negli	esempi	userò	il	C++98,	ma	il	C++11	è	ormai	supportato	da	tutti	i	compilatori	e	
si	sta	imponendo	come	linguaggio	di	riferimento	negli	attuali	progetti	di	calcolo	che	
fanno	riferimento	al	C++
Il	C++	è	il	terzo	linguaggio	di	programmazione	per	diffusione,	dopo	il	C	e	il	Java
ROOT è	un	framework di	calcolo	sviluppato	al	CERN	a	partire	dalla	fine	degli	anni	90	
ad	opera	di	Rene	Brun e	Fons Rademakers
ROOT5	è	il	livello	più	avanzato	del	progetto	originale	e	incorpora	un	interprete	C++	
sviluppato	da	Masaru Goto
ROOT6	ha	un	interprete	basato	su	Clang	e	LLVM,	quindi	più	vicino	allo	standard	del	
linguaggio	C++.
Le	applicazioni	descritte	in	questo	corso	dovrebbero	funzionare	sia	con	ROOT5	che	
con	ROOT6

Presentazione	del	corso	(4)
•

(Iper)Testi	di	riferimento:

– G.	Cowan,	Statistical Data	Analysis,	Clarendon,	Oxford,	1998
– Root:	http://root.cern.ch

•

Si	vedano	anche:

– M.Loreti,	Teoria	degli	errori	e	fondamenti	di	statistica,	Decibel/Zanichelli	1998	(scaricabile	da		
http://wwwcdf.pd.infn.it/labo/book.pdf )
– L.	Lyons,	Statistics for Nuclear and	Particle Physics,	Cambridge	Univ.	Press	1986
– F.	James,	Monte	Carlo	Theory and	practice,	Reports on	Progress	in	Physics,	43,	1145-1189	
(1980)
– C.	Amsler et	al.	(Particle	Data	Group),	Physics	Letters	B667,	1	(2008),		capitoli	31	e	32,						
(http://pdg.lbl.gov )
– W.H.Press et Al,	Numerical Recipes in	C – The	Art	of Scientific Computing, 3rd Edition,	
Cambridge	Univ.	Press 2007	(http://www.nr.com )
– G.	D’Agostini,	Bayesian reasoning in	high-energy physics:	principles and	applications,	CERN	9903	19	July 1999	
– D.S.	Sivi,	Data	analysis	– A	Bayesian	tutorial,	second	edition,	Oxford	2006
– G.	Feldman,	R.	Cousins Unified approach to the	classical statistical analysis of small signals,	
Phys.	Rev.	D57	(1998)	3873
– S.Lippman,	J.	Lajole C++	Primer Third Edition,	Addison Wesley	1998	(1236	pagine)

M.	Masera

T.A.N.S.

8

Introduzione
•“The	result	of	this	experiment	was	inconclusive,	so	we	had	to	use	
statistics”	....	(L.Lyons,	op.	Cit.)
•“There	are	three	kinds	of	lies:	lies,	damn	lies	and	statistics”	(Benjamin	
Disraeli/Mark	Twain)

•...	In	effetti,	Lord	Rutherford	sosteneva	che	un	buon	esperimento	
non	ha	bisogno	della	statistica	!
•Questo	non	è	praticamente	mai	vero:	la	statistica	è	utilizzata	in	fisica	
principalmente	per
– per	passare	dai	dati	grezzi	ai	risultati	finali
– per	confrontare	i	risultati	con	modelli	e	teorie	

•Metodi	probabilistico	– statistici	vengono	usati	infine	per	la	
simulazione degli	apparati	sperimentali	mediante	tecniche	Monte	
Carlo	
M.	Masera

T.A.N.S.

9

La	manifestazione	di	leggi	fisiche	è	
caratterizzata	da	elementi	probabilistici	
legati	sia	alla	natura	probabilistica	delle	
leggi	stesse	sia	alla	risposta	non	
deterministica	degli	apparati	di	misura.	

T.A.N.S.

Statistica

M.	Masera

Probabilità

La	statistica	viene	usata,	all’inverso,	
per	effettuare	stime	di	parametri,	
per	quantificare	le	incertezze	sulle	
misure	e	per	effettuare	test	di	
ipotesi	(i.e.	validazione	di	modelli	e	
teorie).
L’inferenza	statistica	non	è	facile	da	
applicare	e	non	fornisce	sempre	
risposte	univoche

Leggi
fisiche

Osservazioni	
Sperimentali
10

Interpretazione	dei	dati
• In	fisica si è affermato nel XX	secolo l’approccio frequentista
sia per	quanto riguarda il concetto di probabilità sia per	
quanto riguarda l’interpretazione della misura
• Questo approccio è quello più usato ed è quello che viene
tradizionalmente insegnato nei corsi del	triennio
• Negli ultimi decenni,	soprattutto grazie	ad	esperimenti che
avevano come	risultato limiti a	processi fisici (e.g.	
decadimento del	protone,	rivelazione di monopoli magnetici)	
o fornivano risultati vicino ai limiti fisici (e.g.	massa del	
neutrino)	si è usato anche in	fisica delle alte energie un	
approccio diverso,	detto Bayesiano
• Il	dibattito sui	meriti e i limiti dei due	approcci è tutt’altro che
chiuso,	come	si vede dagli esempi delle slide	successive		

M.	Masera

T.A.N.S.

11

G.	D’Agostini,	“Telling	the	truth	with	statistics”	
CERN	Academic	Training	– febbraio	2005
Frequentista

Bayesiano

M.	Masera

T.A.N.S.

12

B.Efron,	1986

M.	Masera

T.A.N.S.

13

Fred	James,
CERN	2005

M.	Masera

T.A.N.S.

14

L’approccio	bayesiano	si	è	di	fatto	affermato	in	procedure	quali	
l’identificazione	di	particelle	(PID).
Tuttavia	l’applicazione	di	tecniche	bayesiane	in	fisica	non	è	banale	e	la	
discussione	continua,	come	si	è	visto	nelle	slide	precedenti.
Continua	anche	nella	vita	quotidiana,	come	potete	vedere	sotto….

M.	Masera

T.A.N.S.

15

Esempi	(1)
La	produzione	di	un	certo	numero	di	eventi	è	regolata	dalla	distribuzione	di	Poisson	
con	parametro	incognito	µ

µ ne−µ
P ( n) =
n!

(n = 0,1,2, )

La	probabilità	di	osservare	n=3	eventi	
dipende	dal	parametro	µ:
µ=1.0	à P(3)=0.0613
µ=2.0	à P(3)=0.1804
µ=3.0	à P(3)=0.2240
µ=4.0	à P(3)=0.1954
......														..............

M.	Masera

T.A.N.S.

Se	si	osserva	n=3	che	cosa	
si	può	dire	su	µ ?
Risposta:
Si	può	definire	un	intervallo	fiduciale.
Ma	su	questo	torneremo	più	avanti
16

Esempi	(2)
Nel	caso	di	un	lancio	di	una	moneta,	si	ha	probabilità	di	avere	Testa	P(T)=0.5.	Nel	caso	di	una	
moneta	truccata,	con	due	Teste,	la	probabilità	P(T)	è	naturalmente	1.	Si	possono	immaginare	
casi	intermedi	per	i	quali,	grazie	all’abilità	di	chi	lancia	la	moneta	e/o	grazie	ad	un’opportuna	
distribuzione	del	peso,	si	abbia	P(T)≠P(C)
Supponiamo	che	una	moneta	sia	lanciata	10	volte.	Se	si	osserva	la	sequenza:
CCTCTCTTTC
Che	cosa	si	può	dire	sulla	moneta?
E	se	si	osserva:		TTTTTTTTTT ?
Nel	caso	di	lanci	regolari	di	monete	regolari,	entrambe	le	sequenze	hanno	la	medesima	
probabilità	di	venire	osservate	(2-10),	come	del	resto	qualsiasi	altra	sequenza.	Non	si	può	
quindi	trarre	alcuna	conclusione	incontrovertibile sulla	regolarità	della	moneta	dopo	avere	
osservato	una	particolare	sequenza	di	lanci.	Le	valutazioni	di	tipo	inferenziale	hanno	
sempre	un	grado	di	incertezza.
M.	Masera

T.A.N.S.

17

G.	D’Agostini,	“Telling	the	truth	with	statistics”	CERN	Academic	Training	–
febbraio	2005
M.	Masera
T.A.N.S.

18

G.	D’Agostini,	“Telling	the	truth	with	statistics”	CERN	Academic	Training	–
febbraio	2005
M.	Masera
T.A.N.S.

19

Probabilità	(1)
Definizione	assiomatica
Sia	S un	insieme	(spazio	campione	« evento	certo)	con	sottoinsiemi	A,B,...	(A «
evento).	La	probabilità	è	una	funzione	reale	che	obbedisce	ai	seguenti	assiomi,	
proposti	da	Kolmogorov	nel	1933

$∀ A ⊂ S , 0 ≤ P( A) ≤ 1
!
#P( S ) = 1
!Se A ∩ B = ∅, P( A ∪ B) = P( A) + P( B)
"
Da	questi	assiomi	si	possono	derivare	altre	proprietà	della	probabilità,	
quali:

M.	Masera

T.A.N.S.

20

Probabilità	(2)
Proprietà:

P ( A ) = 1− P(A)
P(A ∪ A ) = 1
P(∅) = 0
Se A ⊆ B ⇒ P(A) ≤ P(B)
P(A ∪ B) = P(A) + P(B) − P(A ∩ B)
Probabilità	condizionata:	P(A|B) indica	la	probabilità	di	osservare	A,	posto	
che	si	sia	verificato	B	

€
M.	Masera

T.A.N.S.

21

Probabilità	(3)
P(A) ≡ P(A | S) = P(A ∩ S)

[
]
= P [( A ∩ B) ∪ ( A ∩ B )]
= P A ∩ (B ∪ B )

S è	lo	spazio	campione,	che	ha	probabilità	
unitaria,	pari	a	quella	dell’unione	tra	un	
evento	B e	la	sua	negazione
Questa	è	la	probabilità	che
A	e	B si	verifichino
contemporaneamente,	
normalizzata	all’intero	spazio	
campione

= P(A ∩ B) + P(A ∩ B )

P( A ∩ B) %
P( A | B) =
P( B) ""
$⇒ P( A | A) = P( B | B) = 1
P( A ∩ B) "
P( B | A) =
P( A) "#
P(A) e	P(B)≠0
M.	Masera

T.A.N.S.

Per	definire	la	
probabilità
condizionata,	la	
normalizzazione
è	rispetto	
all’evento	B	
22

Il	teorema	di	Bayes
Dalle	relazioni	precedenti:

P ( B ) P ( A | B ) = P ( A) P ( B | A) = P(A ∩ B )

P(A | B) > P(A) ⇒ A e B positivamente correlati
P(A | B) < P(A) ⇒ A e B negativamente correlati

P( A) P( B | A)
P( A | B) =
P( B)
Eventi	indipendenti:	
Indipendenti	non	
significa	disgiunti:
A∩ B = ∅
M.	Masera

P ( A | B ) = P ( A) e

Rev.	Thomas	Bayes
(1702-1761)

P ( B | A) = P ( B )

P ( A ∩ B ) = P ( A) P ( B )
T.A.N.S.

23

Legge	delle	probabilità	totali
Ai ⊂ S, ∀i ≠ j

(A ∩ A ) = ∅
i

j

∪i Ai = S
Se B ⊂ S ⇒ B = B ∩ S = B ∩ (∪i Ai ) = ∪i (B ∩ Ai )
P(B) = P [∪i (B ∩ Ai )] = ∑ P (B ∩ Ai )

visto che (B ∩ Ai ) sono disgiunti

i

P(B) = ∑ P (B | Ai )P(Ai )

Legge	delle	probabilità	totali

i

Il	teorema	di	Bayes	diventa:

Interpretazione:
A:	ipotesi	da	testare
Ai:	ipotesi	alternative
B:	evento	osservato

P(B | A)P(A)
P(A | B) =
∑ P (B | Ai )P(Ai )
i
M.	Masera

T.A.N.S.

24

Interpretazione	della	probabilità	(1)
Definizione	“classica”	(Laplace):	Rapporto	tra	numero	di	casi	favorevoli	e	
numero	di	casi	possibili,	purché	siano	ugualmente	probabili

Definizione		frequentista	(R.	von	Mises		1883-1953):	Sia	f(A;N)=n/N	la	

frequenza	relativa	con	cui	un	evento	si	è	presentato	in	un	numero	totale	N	di	casi	reali:	

P( A) = lim f ( A; N )
N →∞

Questa	definizione	è	consistente	con	gli	assiomi	di	Kolmogorov	ed	è	piuttosto	
naturale	in	molti	casi	fisici,	laddove	ha	senso	parlare	di	esperimenti	ripetuti.
Difetti:
• E’	basata	su	di	un	esperimento
• Si	presuppone	a	priori	la	convergenza	della	frequenza	relativa
• In	effetti,	il	limite	non	converge	in	generale	nel	senso	che	l’analisi	dà	a	questo	
termine:

∀ ε > 0 ∃M : N > M ⇒ | f ( A; N ) − P ( A) |< ε
M.	Masera

T.A.N.S.

25

Interpretazione	della	probabilità	(2)
La	convergenza	è	di	tipo	debole	o	stocastico:

∀ ε,δ > 0 ∃M : N > M ⇒ P [| f (A;N) − P(A) |≥ ε] ≤ δ
Con	N,M	naturali	e	e,d reali.

La	legge	dei	grandi	numeri	afferma	che	la	frequenza	
relativa	di	qualunque	evento	casuale	converge	
stocasticamente	alla	sua	probabilità	all’aumentare	del	
numero	delle	prove

M.	Masera

T.A.N.S.

26

Esempio

Talvolta,	la	probabilità	è	calcolabile	a	priori.	Ad	esempio	nel	caso	del	lancio	di	2	dadi,	
si	valuta	la	probabilità	di	ottenere	un	numero	come	somma	dei	2.	In	verde:	frequenza		
attesa,	in	rosso	frequenza	assoluta	dopo	N	prove.	Esempio	di	simulazione	Monte	
Carlo	(con	Root)
L’inferenza	
statistica,	per	
piccoli	campioni	
può	essere	
problematica	!!!

M.	Masera

T.A.N.S.

27

Interpretazione	della	probabilità	(3)
Definizione	di	probabilità	soggettiva	(o	bayesiana):

A,	B,	....	sono	ipotesi	(à Spazio	delle	ipotesi),	ossia	affermazioni,	mutuamente	
esclusive,	che	possono	essere	vere	o	false.
P(A) è	il	grado	di	fiducia	(degree	of	belief)	che	A sia	vero
Questa	definizione	soddisfa	gli	assiomi	di	Kolmogorov
Per	quanto	l’interpretazione	in	termini	di	frequenza	sia	spesso	più	naturale,	la	probabilità	
soggettiva	consente	di	trattare	fenomeni	non	ripetibili,	a	titolo	di	esempio:
• Errori	sistematici	(la	ripetizione	della	misura	non	giova...)
• Che	una	particella	in	un	certo	evento	sia	un	K+
• Che	la	Natura	sia	supersimmetrica
•Che	pioverà	dopodomani	(evento	futuro	incerto)
•Che	sia	piovuto	a	Passerano Marmorito il	3 Settembre	1704	(evento	passato	incerto)
M.	Masera

T.A.N.S.

28

Interpretazione	della	probabilità	(4)

R.	D’Agostino,	Op.	Cit.
M.	Masera

T.A.N.S.

29

Interpretazione	della	probabilità	(5)
• La	definizione	soggettiva	della	probabilità	è	adottata	dagli	
statistici	bayesiani.	La	legge	di	Bayes può	essere	scritta	come
(cfr.	slide	pag.	20)

P (teoria | dati ) ∝ P (dati | teoria ) × P (teoria )

• Dove:

– P(dati	|	teoria)	è	la	probabilità	di	osservare	il	dato	effettivamente	
riscontrato	posto	che	la	teoria	sia	valida	(likelihood)
– P(teoria)	è	la	probabilità	a	priori	(prior)	che	la	teoria	sia	valida	e	riflette	
lo	stato	delle	conoscenze	prima	della	misura.	E’	una	valutazione	
soggettiva dello	sperimentatore	che	viene	calibrata sulla	base	delle	
informazioni	disponibili.	
– P(teoria|dati)	è	la	probabilità	a	posteriori che	la	teoria	sia	valida	alla	
luce	dei	nuovi	dati

M.	Masera

T.A.N.S.

30

Le	valutazioni	di	grandezze	fisiche
sono	di	fatto	spesso	influenzate	da	
risultati	precedenti	o	da	predizioni	teoriche.
Esempio	tratto	dal
Particle	Data	Book	(1994)

Anno	di
Pubblicazione
Misure	di	vita	
media

M.	Masera

T.A.N.S.

31

Interpretazione	della	probabilità	(6)
• I	sottoinsiemi	dello	spazio	campione	possono	essere	
interpretati	come	ipotesi,	ossia	affermazioni	che	
possono	essere	vere	o	false
• L’affermazione:	“il	bosone	W	ha	massa		tra	80.3	e	
80.5	GeV/c2”	è	nell’approccio	classico	o	sempre	vera	
o	sempre	falsa;	ha	probabilità		0	o	1.	
• Nell’approccio	soggettivista	(bayesiano)	ha	invece	
senso	un’espressione	quale	
P(80.3£MW £80.5	GeV/c2)=0.68
M.	Masera

T.A.N.S.

32

Esempio	di	interpretazione	della	
probabilità

Supponiamo	che	per	una	persona	qualsiasi,	la	probabilità	a	priori di	avere	una	malattia	
sia	(Esempio	tratto	da	G.	Cowan,	i	valori	riportati	sotto	sono	fittizi):
P(malattia)=0.001					e	quindi	P(NO	malattia)=0.999
I	possibili	esiti	di	un	test	sono	+ o	-:
•P(+|malattia)=0.98				(identificazione	corretta)			P(-|malattia)=0.02	(falso	negativo)
•P(+|NO	malattia)=0.03	(falso	positivo)															P(-|NO	malattia)=0.97	(ident.	OK)
Se	il	risultato	del	test	di	una	persona	è	+,	quanto	deve	preoccuparsi?

P(+ | malattia ) P(malattia )
P(malattia | +) =
P(+ | malattia ) P(malattia ) + P(+ | NO malattia ) P( NO malattia )

0.98 × 0.001
P(malattia | +) =
= 0.032
0.98 × 0.001 + 0.03 × 0.999
M.	Masera

T.A.N.S.

33

Esempio	di	interpretazione	della	
probabilità
La	probabilità	a	posteriori	è	0.032	(>>	0.001,	ma	anche	<<1).
Il	punto	di	vista	della	persona	(soggettivo):	il	mio	grado	di	fiducia	
di	essere	malato	è	del	3.2%	à esprime	un	degree	of	belief
Il	punto	di	vista	del	medico	(frequentista):	il	3.2%	di	persone	come	
questa	sono	malate

Morale....	Un	test	che	funziona	nel	98%	e	ha	il	3%	di	falsi	positivi	va	
usato	con	cautela:	l’affidabilità	dei	test	di	screening	di	massa	deve	
essere	molto	alta.	In	caso	contrario	vanno	usati	su	persone	per	le	
quali	la	probabilità	a	priori sia	diversa	da	quella	della	popolazione	
generale
M.	Masera

T.A.N.S.

34

