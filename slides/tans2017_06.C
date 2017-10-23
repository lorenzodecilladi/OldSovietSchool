Esercizio
• Scrivere	un	programma	che	genera	q secondo	la	
funzione:
−1
2
2
f (θ ) = (sin θ + a ⋅ cos θ ) per 0 ≤ θ ≤ 2π
• Usare	sia	la	tecnica	dell’inversione	che	quella	della	
reiezione
€ – Generare	100000	valori	con	ciascun	metodo	per	a=0.5 e	

a=0.001
– Paragonare	i	risultati	della	simulazione	con	la	funzione	di	
partenza
– Confrontare	i	tempi	di	CPU	(hint:	in	ROOT	si	può	usare	la	
classe	TStopwatch	)

M.	Masera

T.A.N.S.

1

Risultati
• Sono	stati	usati	i	metodi	di	inversione	e	
reiezione	e,	per	confronto,	il	metodo	di	
inversione	numerica implementato	in	ROOT	
(TF1::GetRandom())
• I	metodi	di	inversione	e	reiezione	sono	stati	
definiti	in	una	apposita	classe	(MyRandom)		
derivata	per	public	inheritance da	TRandom3	
M.	Masera

T.A.N.S.

2

a=0.5	;	200	bins;	50000	numeri	casuali	estratti.

(

2

2

f (θ ) = sin θ + a ⋅ cos θ

Inversion

−1

)

per 0 ≤ θ ≤ 2π

Rejection

Numerical	inversion	(TF1::GetRandom)
M.	Masera

T.A.N.S.

3

(

f (θ ) = sin 2 θ + a ⋅ cos 2 θ

Inversion

−1

)

per 0 ≤ θ ≤ 2π

Rejection

Numerical	inversion	(TF1::GetRandom)

T.A.N.S.
a=0.001	;	200	bins;	50000	numeri	casuali	estratti.

M.	Masera

4

TEMPI	DI	ESECUZIONE

M.	Masera

T.A.N.S.

5

Inversione	/	1
Come	vedremo,	la	funzione	integrale	contiene	le	funzioni	
tangente	e	arcotangente.
Occorre	fare	attenzione	all’implementazione	della	funzione	
arcotangente:	usualmente	restituisce	valori	tra	-p/2	e	p/2.	
Se	rappresentiamo	la	funzione	seguente	(con	parametro	1	e	con	
costante	1	per	semplicità)	ci	aspettiamo	la	retta	y=x

M.	Masera

T.A.N.S.

6

Inversione	/	2
• Invece	si	ottiene:

•Solo	nel	primo	quadrante	
(J<p/2)	la	funzione	si	
comporta	come	dovrebbe.	
•Questo	comportamento	
deriva	da	come	la	funzione	
arcotangente	è	
implementata

M.	Masera

T.A.N.S.

7

Funzioni	cumulative	
a=0,001

a=0,5

M.	Masera

T.A.N.S.

8

Inversione	/	3
La	funzione f è periodica con	periodo p e va integrata,	con	un	opportuno coefficiente di
normalizzazione k,	che si determina imponendo che l’integrale esteso a	tutto il dominio
valga 1
x

F ( x) = k ∫

π
−
2

dθ
k x
= ∫
2
2
acos θ + sin θ a − π

Si	effettua	la	seguente	sostituzione:

tan θ
z≡
a

⇒ dz =

2

dθ
# tan 2 θ &
cos θ %1+
(
a '
$
2

1
dθ
2
a cos θ

Si	ottiene:
tan x

k
F ( x) =
a
M.	Masera

a

∫
−∞

% tanx ( k π
dz
k
=
atan'
*+
2
1+ z
& a )
a
a 2
T.A.N.S.

9

Inversione	/	4
La	costante	di	normalizzazione	vale:

(

)

F x →π2 =

k π
k π
a
+
≡1 ⇒ k =
π
a 2
a 2

Se	si	estrae	un	numero	u	con	distribuzione	uniforme	tra	0	e	1,	si	può	ottenere	un	numero	
distribuito	secondo	la	funzione	data,	nell’intervallo	-p/2,p/2, nel	modo	seguente:

# tan x & 1
1
u = atan%
(+
π
$ a ' 2

⇒

+
#
π &.
x = atan- a tan%π u − (0
$
2 '/
,

La	trasposizione all’intervallo [0,2p] si può ottenere nel modo seguente:
1. Si	estrae un	secondo numero casuale w distribuito uniformemente tra 0	e 1
2. Se	w<0.5	allora x=x+p (secondo e terzo quadrante)
3. Altrimenti
1. Se	x<0	allora x=x+2p (quarto	quadrante)
2. Se	x>=0	allora x=x (primo	quadrante)
M.	Masera

T.A.N.S.

10

Simulazioni	multidimensionali
• Si	possono	utilizzare	le	densità	marginali,	che	
nel	caso	bidimensionale	sono:
f x ( x ) = ∫ f (x, y)dy
f y ( y ) = ∫ f (x, y)dx
• Un	caso	particolarmente	semplice	è	
rappresentato	da	variabili	scorrelate,	per	le	
€
quali	vale:
f (x, y) = f x (x) f y (y)
M.	Masera

Esercizio:	simulare	un	flusso	isotropo	di	particelle
T.A.N.S.

11

Flusso	isotropo
dn
=k
dΩ

dn = k dΩ = k1 sin θdθ k 2 dϕ

Normalizzazione
1
Fθ (θ ) =
2

2π

π

∫∫ dn ≡ 1

∫ k sinθdθ ∫ k dϕ = 1

⇒

1

0

2

0

θ

1
∫ sin(θ ')dθ '= 2 (1− cosθ ) = u1
€
0
ϕ
1
ϕ
'
Fϕ (ϕ ) =
d
ϕ
=
= u2
∫
2π 0
2π
€

Flusso isotropo emisferico

€

M.	Masera

θ = arccos(1− 2u1 )

ϕ = 2πu2
€
k1 = 1 ⇒ θ = arccos( u1 )
T.A.N.S.

€

#
1
k
=
% 1 2
%
%
1
$k2 =
2π
%
1
%
k
=
%&
4π

12

