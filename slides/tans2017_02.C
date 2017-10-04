Variabili	aleatorie
Se	il	risultato	di	una	misura	è	x (x individua	un	elemento	nello	spazio	
campione	e	come	tale	prende	il	nome	di	variabile	aleatoria),	la	funzione	
densità	di	probabilità	f(x) è	definita	dalla	relazione	seguente:

P ( x ∈ [ x, x + dx ]) = f (x)dx
+∞

La	condizione	di	normalizzazione	è:

∫

f ( x)dx = 1

−∞

La	funzione	cumulativa	di	probabilità	è F ( x) =

€

f i = P(x i )
i

∫ f (u )du

−∞

Nel	caso	discreto:

∑f

x

€
f(x)

F(x)

=1

i

F(x) =

∑f

i

x i <x
M.	Masera

1

I	risultati	delle	misure	vengono	spesso	rappresentati	
mediante	istogrammi,	che,	se	normalizzati	ad	area	unitaria,	
tendono	a	rappresentare	la	densità	di	probabilità	nel	limite	
di	infinito	numero	di	misure	e	di	larghezza	di	ciascun	
elemento	(cella	o	“bin”)	dell’istogramma	nulla

Nell’esempio	
riportato	in	figura,	
al	crescere	del	
campione,	la	
distribuzione	tende	
ad	assumere	la	
forma	di	una	
gaussiana
M.	Masera

T.A.N.S.

2

Una	misura	può	condurre	alla	determinazione	di	un	
set	di	parametri:	la	definizione	di	densità	di	
probabilità	può	essere	facilmente	estesa	al	caso	
multivariato.	
Nel	caso	bidimensionale		
f(x,y)dxdy è	la	probabilità	che	
x sia	compreso	tra	x e	x+dx e
che	y sia	compreso	tra	y e	y+dy

P( A ∩ B) = f ( x, y )dxdy

∫∫ f ( x, y)dxdy = 1
f(x1,x2,x3,...xn) è	detta	distribuzione	
congiunta	di	probabilità
M.	Masera

T.A.N.S.

3

La	proiezione	della	distribuzione	congiunta	su	
uno	degli	assi	xi è	detta	distribuzione	
marginale di	probabilità

∫
f ( y) = ∫
fx ( x) =
y

M.	Masera

f (x, y)dy
f (x, y)dx

T.A.N.S.

4

M.	Masera

T.A.N.S.

5

P(B | A) =

Dalla	definizione	di	probabilità	subordinata

P(A ∩ B ) f ( x, y )dxdy
=
P(A)
f x ( x)dx

Segue	la	definizione	di	densità	condizionale	di	
probabilità (e.g.	di	y	ad	x	fisso	o	viceversa):

f ( x, y )
h(y | x) =
f x (x)

e

f (x, y)
g(x | y) =
f y (y)

Se	le	variabili	aleatorie	x	e	y	sono	indipendenti,	si	ha

€

h( y | x ) = f y ( y ) e

g ( x | y ) = f x ( x) ⇒

f ( x, y ) = f x ( x ) f y ( y )

Il	teorema	di	Bayes	si	può	riscrivere	come:

g ( x | y) =

M.	Masera

h( y | x ) f x ( x )
f y ( y)
T.A.N.S.

6

Funzioni	di	variabili	aleatorie
Una	funzione	a(x) di	una	variabile	aleatoria	x (con	distribuzione	di	
probabilità	f(x))	è	essa	stessa	una	variabile	aleatoria.
Qual	è	la	distribuzione	di	probabilità	di	a? [indicata	con	g(a)]
Consideriamo	un	dominio	dS di x per	
cui	aÎ[a,a+da]		e	supponiamo	a
monotona:
g(a)da =

∫

f (x)dx ≅

dS

%
(
dx
≅ f [ x ( a)] 'x ( a) +
da − x ( a)* ⇒
da
&
)
dx
g(a) = f [ x ( a)]
da
M.	Masera

Il	valore	assoluto
assicura	che
l’integrale	sia
positivo
T.A.N.S.

dS

7

Caso	multivariato
Nel caso di una funzione di n variabili aleatorie a(x1,x2,…,xn) , la densità
congiunta di probabilità è

Come esempio si considerino 2 v.a. indipendenti distribuite secondo due f.d.p. g(x) e h(y). La
densità congiunta di probabilità è: g(x)h(y)
Si vuole trovare la densità di probabilità
del prodotto z=xy

da cui segue

xy=z+dz

dS
oppure
xy=z
M.	Masera

T.A.N.S.

8

Convoluzione
Il risultato raggiunto nell’ultima slide per la densità di probabilità del prodotto di
due variabili aleatorie indipendenti prende il nome di convoluzione di Mellin e
viene indicata spesso con f = g ⊗ h .
Analogamente, nel caso della somma di due v.a. indipendenti: z=x+y si ottiene:

Questa rappresenta la convoluzione di Fourier delle due funzione h e g e viene
ancora indicata con la notazione f = g ⊗ h

M.	Masera

T.A.N.S.

9

Se	a(x) non	ammette	un	unico	inverso	(e.g.	a=x2),	dS va	
esteso	a	tutti	gli	intervalli	di	x che	corrispondono	a	da
Caso	multivariato-bis:	


f ( x ) , dove


x = ( x1, x 2 ,, x n )

Consideriamo	n	funzioni	linearmente	indipendenti:
 



y ( x ) = ( y1 ( x ), y 2 ( x ),, y n ( x ))
€

Che	siano	invertibili:	




x1 ( y ), x 2 ( y ),, x n ( y )

€

La	distr.	congiunta	di	probabilità	di	y è:
€
Dove	J è	il	determinante	
jacobiano	della	
trasformazione

M.	Masera

€
T.A.N.S.

∂x1
∂y1
∂x 2
J = ∂y1




g( y ) = J f ( x )
∂x1
∂y 2
∂x 2
∂y 2

∂x1
∂y n
∂x 2

∂y n

∂x n

∂y n


10

Momenti	di	una	distribuzione
Il	momento	di	ordine	n di	una	variabile	aleatoria	x è:

αn ≡ E[x

n

]= ∫

+∞
−∞

n

x f (x)dx

Il	momento	centrale	di	ordine	n (o	momento	rispetto	alla	media)	è:

[

n

]

mn ≡ E ( x − α1 ) =

€

+∞

n
x
−
α
f (x)dx
(
)
∫−∞
1

Caveat:	i	momenti	non	sono	una	funzione	di	x,	ma	
parametri della	densità	di	probabilità	f(x)
M.	Masera

T.A.N.S.

11

Media	e	varianza
I	momenti	più	utilizzati	sono	la	media	e	la	varianza,	definiti	
rispettivamente	come:
e

µ ≡ α1
2

σ ≡ V [ x] =

+∞

∫ ( x − µ)
−∞

2

f (x)dx =

∫

+∞
−∞

2

x f (x)dx + µ

2

∫

+∞
−∞

+∞

f (x)dx − 2 µ ∫ −∞ x f (x)dx

= α 2 − µ2

La	media	è	un’espressione	del	“centro	di	massa” della	distribuzione	
di	probabilità	mentre	la	varianza	è	il	quadrato	della	sua	larghezza.	
Come	stima	di	dispersione	si	usa	in	generale	la	deviazione	standard
sºÖs 2.
M.	Masera

T.A.N.S.

12

Covarianza	e	correlazione
Nel	caso	di	una	distribuzione	bivariata,	il	grado	di	
correlazione	tra	le	variabili	aleatorie	x e	y è	espresso	dalla	
covarianza:

[

]

cov[ x, y ] ≡ Vxy ≡ E ( x − µx )( y − µy ) = E [ xy ] − µx µy
Nel	caso	multivariato,	Vxy prende	il	nome	di	matrice	di	covarianza	o	
matrice	degli	errori.	Il	coefficiente	adimensionale	di	correlazione	è	
definito	come:
Vxy
Si	veda	appendice	C	del	testo	di	
ρ xy =
− 1 ≤ ρ xy ≤ 1
M.Loreti per	la	dimostrazione
σ xσ y
Se	x	e	y	sono	indipendenti:

E [xy ]= µ x µ y

⇒ cov[x, y ]= 0

Caveat:	Non	è	detto	che	2	variabili	scorrelate siano	indipendenti	!
M.	Masera

T.A.N.S.

13

Esempi	di	correlazione
Correlazione	negativa

Correlazione	positiva

M.	Masera

T.A.N.S.

14

Propagazione	degli	errori	(1)

x
= (x1 ,, xn )
Supponiamo	che	un	set	di	variabili	aleatorie																																						


f (x )

segua	una	distribuzione	congiunta	di	probabilità
eventualmente	non	nota,	ma	che	si	abbiano	stime	delle	


µ
=
E
x
[
].	
V
=
cov
x
,
x
covarianze																						
[ i j ] e	delle	medie		
ij

y( x)
Consideriamo	una	funzione								
•Qual	è	la	media	di	y ?	

€

€

V [ y] = E [ y 2 ] − E [ y]
•Qual	è	la	varianza	di	y ?			(																																			)
€
2

Il	momento	di	una	funzione	y della	variabile	aleatoria	x,	vale:	

E [ y ( x )] =

∞

∫
−∞

M.	Masera

€

 
yg( y )dy = ∫  ∫ y ( x ) f ( x ) dx1 dx n = µy
∞

∞

−∞

−∞
T.A.N.S.

15

Propagazione	degli	errori	(2)
Se	y	non	è nota,	si	può usare	l’espansione	al	prim’ordine	di	y	
attorno	a	µ:	(vedremo	dopo	i	limiti	di	questo	assunto)
n $


∂y '
y ( x ) ≅ y (µ) + ∑& ) ( x i −µ i )

i=1 % ∂x i (x = µ

In	altri	termini:

E [xi − µi ]= 0

n $
$ 
'

∂y '
E [ y ( x )] ≅ E & y (µ) + ∑& ) ( x i −µ i )) =

&%
)(
i=1 % ∂x i (x = µ
n &
1/ 
∞
∞ / 
∂y )
= ∫  ∫ . y (µ) + ∑( + ( x i −µ i )2 f ( x ) dx1 dx n

/3
−∞
−∞ /
i=1 ' ∂x i *x = µ
0
n #
n #

∂y & ∞ ∞

∂y &

= y (µ) + ∑% ( ∫  ∫ x i f ( x ) dx1 dx n − ∑% ( µi = y (µ)


−∞
i=1 $ ∂x i 'x = µ −∞
i=1 $ ∂x i 'x = µ
M.	Masera

T.A.N.S.

16

Propagazione	degli	errori	(3)
3
n
5 E y 2 ( x ) ≅ y 2 (µ ) + 2y (µ ) $ ∂y ' E [ x −µ ] +
∑&%∂x )(  i i
]
5 [
i x=µ
i=1
5
0'
55 $- n $ '
n $
0- n $ ∂y '


∂y '
∂y
y ( x ) ≅ y (µ) + ∑& ) ( x i −µ i ) ⇒ 4+ E &//∑& ) ( x i −µ i )22/∑& ) ( x j −µ j )2) ⇒
/
2)

5 &%. i=1 % ∂x i (x = µ
i=1 % ∂x i (x = µ
1. j=1 % ∂x j (x = µ
1(
5
n $
5


∂y ∂y '
2
2
) Vij
5 E [ y ( x )] = y (µ) + ∑&
56
i, j=1% ∂x i ∂x j (  
x=µ

Espansione	al	primo
ordine

M.	Masera

T.A.N.S.

17

Propagazione	degli	errori	(4)
La	varianza	di	y è	quindi:

σ = E [ y ] − E [ y]
2
y

2

2

& ∂y ∂y )
≅ ∑(
+ Vij
i, j=1' ∂x i ∂x j *x = µ
n

Se	le	xi	sono	tra	loro	scorrelate,	si	ha:
2
n %
n %
% ∂y ∂y (
(
(
∂y ∂y
∂y
σ y2 ≅ ∑'
* Vij = ∑'
* σ i2δij = ∑' * σ i2

i, j=1& ∂x i ∂x j )x = µ
i, j=1& ∂x i ∂x j )x = µ
i=1 & ∂x i )x = µ
n

€

€
M.	Masera

T.A.N.S.

18

Propagazione	degli	errori	(5)
Nel	caso	in	cui	si	abbia,	in	luogo	di	una	funzione	reale	y,	un	set	di	
 



y
x
=
y
x
,
y
x
,,
y
x
( ) ( 1( ) 2 ( )
funzioni																																						
n ( )) le	formule	precedenti	possono	
essere	estese	come:
€

$∂y ∂y '
U kl = cov[ y k , y l ] ≅ ∑& k l ) Vij
∂x i ∂x j (  
i, j=1%
x=µ
n

O,	in	notazione	matriciale:
€

€M.	Masera

U = AVA

T

# ∂y &
dove Aij = % i (
$ ∂x j 'x = µ

T.A.N.S.

19

Propagazione	degli	errori	(6)
• Queste	relazioni,	che	propagano	le	covarianze	di	un	set	
di	variabili	aleatorie	a	variabili	aleatorie	derivate,	sono	
le	formule	di	propagazione	degli	errori,	in	quanto	
varianze	e	covarianze	sono	usate	generalmente	per	
esprimere	gli	errori	delle	grandezze	oggetto	di	misura.
 
•
Sono	valide	solo	se													è	lineare.	
y (x )
L’approssimazione	non	è	valida	se	la	funzione	non	è	
lineare	in	un	dominio	di	estensione	confrontabile	con										
σi

€
M.	Masera

T.A.N.S.

20

Esempi	(1)
y = x1 + x 2 ⇒ σy2 = σ12 + σ22 + 2⋅ cov[ x1, x 2 ]

⇒ σ y2 = x22σ 12 + x12σ 22 + 2 ⋅ x1 x2 cov[x1 , x2 ]

y = x1 x2

x
y= 1
x2

σy2 σ12 σ22
cov[ x1, x 2 ]
2 =
2 + 2 +2
y
x1 x 2
x1 x 2

2
1
x
x
⇒ σ y2 = 2 σ 12 + 14 σ 22 − 2 ⋅ 13 cov[x1 , x2 ]
x2
x2
x2

€

M.	Masera

T.A.N.S.

σy2 σ12 σ22
cov[ x1, x 2 ]
2 =
2 +
2 −2
y
x1 x 2
x1 x 2
21

Esempi	(2)
• Nel	caso	di	xi	scorrelate,	gli	errori	si	
sommano	in	quadratura	per	la	somma	o	la	
differenza
• Nel	caso	di	xi scorrelate,	gli	errori	relativi si	
sommano	in	quadratura	per	il	prodotto	o	il	
rapporto.
M.	Masera

T.A.N.S.

22

