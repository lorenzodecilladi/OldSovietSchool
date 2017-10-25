GEANT
• Geant	3.21 – 1994	– Il	codice	è	stato	sviluppato	in	
FORTRAN,	la	versione	è	stabile	e	consente	di	
descrivere	con	ottima	approssimazione	la	geometria	
degli	apparati	sperimentali	
• Un	“wrapping”	di	geant3	in	ROOT	è	possibile	(in	
ROOT	TGeant3)	à in	questo	modo	il	nuovo	codice	
utente	può	essere	sviluppato	in	C++
• Geant	4:	codice	di	trasporto	scritto	in	C++.	Il	progetto	
è	gestito	da	una	collaborazione	internazionale	ed	è	
iniziato	nel	1995
(http://geant4.web.cern.ch/geant4/)
M.	Masera

T.A.N.S.

1

GEANT	4
Geometria:	user	class.	Inherits	
from	
G4VUserDetectorConstruction.

Elenco	delle	particelle,	processi	
da	usare	etc	:	user	class.	Inherits	
from	G4VUserPhysicsList	.
Generatore	delle	particelle	primarie:	
user	class.	Inherits	from	
G4VUserPrimaryGeneratorAction

M.	Masera

T.A.N.S.

2

GEANT	3
Durante	
l’inizializzazione	ed	il	
trasporto,	delle	
routines	scritte	
dall’utente	vengono	
eseguite	(e.g.	GUKINE,	
GUSTEP,	etc).	In	questo	
modo	è	possibile	
descrivere	il	caso	
particolare	che	si	deve	
simulare.

M.	Masera

T.A.N.S.

3

Elenco	dei	
processi	attivi	in	
Geant	3

M.	Masera

T.A.N.S.

4

Implementazione	
dello	scattering	
Compton	in	Geant	
(3.21	e	4)	

M.	Masera

T.A.N.S.

5

Scattering	Compton

e

0.1	MeV

1	MeV

e2
α=
c
10	MeV
 =1
c = 1100	MeV

K’

K

q

e2
α2
1 2
re =
⇒
=
re
2
m
2
2m
L’energia	del	fotone	diffuso	è

q

K

K'=
1+

K
(1− cosθ )
m

*−1
K' ' K
⇒ ε ≡ = )1+ (1− cos θ ),
+
K ( m

La	sezione	d’urto	differenziale	è	data	dalla	formula	di	Klein	e	Nishina

2€

dσ
α " K '%
=
'
2 $
dΩ 2m # K &
M.	Masera

2

"K' K
2 %
$ + − sin θ '
# K K'
&
T.A.N.S.

6

scattering	Compton	(2)
La	distribuzione	angolare	va	quindi	simulata	campionando	la	densità:
3
2
+
(
α %1 K ' . 1 K ' . 1 K ' .
2 %
dσ =
, + / , − / , sin θ ' sin θ dθ dϕ
2 */
2m %)0 K - 0 K - 0 K %&
2

Termine	dominante,	visto	che	K’<K

L’angolo	azimutale,	che	è	indipendente,	può	essere	estratto	da	una	
distribuzione	uniforme	tra	0	e	2p.	Per	l’angolo	polare,	si	può	
applicare	la	tecnica	dell’importance	sampling,	invertendo	la	
funzione	maggiorante:
α 2 1 K'.
α2
a
dσ =
, sin θ dθ dϕ =
2 /
2m 0 K 2m 2
M.	Masera

−1

+ K (
)*1 + m v &' dvdϕ con v = 1 − cosθ
T.A.N.S.

7

scattering	Compton	(3)
Il	metodo	dell’inversione,	applicato	alla	variabile	n nell’intervallo	
[0,2],	dà:
u
'
$
m .
K+
v = %,1 + 2 ) − 1" con u ∈ [0,1]
K %&m*
"#

Dimostrazione	nella	slide	
successiva

Si	noti	che	per	K>>m la	sezione	d’urto	ha	un	picco	ad	angoli	
piccoli.
Per	K<<m questa	procedura	non	genera	bene	n,	per	errori	
di	arrotondamento:	(1+2K/m)~1

M.	Masera

T.A.N.S.

8

La	funzione	da	campionare	è

1
f (ν ) =
K
1+ ν
m
2

1+2

K
m

dν
m
dβ m %
K(
La	normalizzazione	della	funzione	è
∫ K = K ∫ β = K ln'&1+ 2 m *)
0 1+
1
ν
€
m
#
K&
ln%1+ ν (
Si	può	estrarre	un	numero	u tra	0 e	1 e	
$
m'
porlo	uguale	a
u=
#
K&
ln%1+ 2 (
€
$
m'
u
u
#
#
K&
K&
K #
K&
ln%1+ ν ( = ln%1+ 2 ( ⇒ 1+ ν = %1+ 2 (
$
$
m'
m'
m $
m'
€
u
'
$
m .
K+
v = %,1 + 2 ) − 1" con u ∈ [0,1]
K %&m*
"#

Simulazione	del	trasporto	dei	fotoni
Unendo	al	codice	di	simulazione	della	diffusione	
Compton	quelli	degli	altri	processi	indotti	da	
fotoni,	quali	l’effetto	fotoelettrico	e	la	
produzione	di	coppie	elettrone/positrone,	è	
possibile	arrivare	ad	un	programma	che	simuli	la	
propagazione	dei	fotoni	nella	materia

M.	Masera

T.A.N.S.

10

Trasporto	dei	fotoni
• Lo	schema	di	principio	è	il	seguente
– Il	percorso	si	suddivide	in	piccoli	passi	(steps)
– Per	ogni	passo,	note	le	sezioni	d’urto	macroscopiche	dei	
singoli	processi,		si	decide	se	ha	luogo	un’interazione	e	se	
sì,	quale.
– Si	simula	l’interazione	(e.g.	Nuova	direzione	del	fotone	e	
nuovo	K)

• Programmi	di	trasporto	sono	stati	scritti	e	convalidati	
mediante	il	confronto	con	i	dati	sperimentali	(EGS	–
Electron	and	Gamma	shower-,	Fluka,	Geant,...)
M.	Masera

T.A.N.S.

11

Generatori	di	eventi
• Il	trasporto	si	effettua	su	particelle	stabili	per	
interazione	forte
• La	generazione	delle	particelle	primarie	viene	
effettuata	per	mezzo	di	programmi	Monte	Carlo	che	
forniscono	l’input	ai	programmi	di	trasporto
• I	generatori	implementano	o	modelli	microscopici	
dell’interazione	primaria	oppure	sono	delle	
parametrizzazioni	a	partire	da	dati	sperimentali
• Esiste	una	gran	varietà	di	generatori	disponibili	in	
Fisica	delle	Alte	Energie	(e.g.	Pythia,	Herwig,	Hijing,	
etc)
M.	Masera

T.A.N.S.

12

Event	display
Nelle	slide	che	seguono	sono	riportate	alcune	
visualizzazioni	di	eventi	simulati	con	GEANT	in	
esperimenti	al	LHC.	Si	tratta	di	una	semplice	
esemplificazione:	si	possono	trovare	facilmente	
su	web	figure	analoghe	tratte	dai	maggiori	
esperimenti	

M.	Masera

T.A.N.S.

13

CMS:		Higgs	à ZZ	à 4µ

CMS:		Higgs	à gg

M.	Masera

T.A.N.S.

14

CMS:		Reconstructed	tracks	
and	energy	deposition	in	the	
electromagnetic	calorimeter

M.	Masera

T.A.N.S.

15

M.	Masera

T.A.N.S.

16

ALICE:	TPC	+	ITS

ITS:	zoom	on	pixel	layers
M.	Masera

T.A.N.S.

17

Esempio	di	confronto	dati/MC
“Radiografia”	del	central	barrel	di	
ALICE:	è	stata	ottenuta	riportando	il	
punto	di	origine	di	tracce	relative	alla	
conversione	di	fotoni	nelle	
componenti	del	rivelatore

Distanza	dall’asse	del	fascio	dei	punti	
di	conversione	dei	fotoni:	confronto	
tra	dati	(nero)	e	Monte	Carlo	(rosso)

