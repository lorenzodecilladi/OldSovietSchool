Algoritmo di Metropolis

a.a. 2017/18

• E’ un metodo Monte Carlo basato su una catena di
Markov
• Si parte da un valore x0
• Si estrae un campione di valori xn, ciascuno dei
quali determinato a partire dal precedente xn-1, in
modo che nel limite di nè∞ la distribuzione dei
valori segua la distribuzione voluta p(x).
• Un processo di Markov è definito univocamente
dalla probabilità di transizione dallo stato x allo
stato x’, T(x’|x)
T.A.N.S.
Metodo proposto da N. Metropolis
et Al. nel 1953

1

Algoritmo di Metropolis

a.a. 2017/18

• Si può dimostrare che affinché valga
lim p(x, n) = p(x)
n!1

• è sufficiente che sia soddisfatta la condizione di
bilancio dettagliato
(1)
p(x)T (x0 |x) = p(x0 )T (x|x0 )

• che significa che la probabilità di essere nello stato x e
transire allo stato x’ deve essere pari alla probabilità
di essere nello stato x’ e transire allo stato x.
• Inoltre è necessario che la catena di Markov sia
ergodica, affinché la distribuzione stazionaria sia
unica
T.A.N.S.
2

Algoritmo di Metropolis

a.a. 2017/18

• L’algoritmo si costruisce a partire dalla condizione di
bilancio dettagliato (1):
T (x0 |x)
p (x0 )
=
0
T (x|x )
p (x)

• La probabilità di transizione può essere scritta come il
prodotto tra la probabilità di proporre lo stato x’ a
partire dallo stato x e la probabilità di accettare la
T (x0 |x) = pr (x0 |x) A (x0 |x)
transizione xà x’:
• che implica
A (x0 |x)
p (x0 ) p (x|x0 )
A (x|x0 )

=

r

p (x) pr

T.A.N.S.

(x0 |x)

(2)

3

Algoritmo di Metropolis

a.a. 2017/18

• Una scelta per la probabilità di accettazione che soddisfa la
condizione (2) è:
✓
◆
0
0
p (x ) pr (x|x )
A (x |x) = min 1,
p (x) pr (x0 |x)
• che si semplifica in
✓
◆
0
p (x )
A (x0 |x) = min 1,
p (x)
0

• se la distribuzione della proposta è simmetrica
q e.g. la probabilità di avere x’ da x può essere una gaussiana con media x
q la scelta della distribuzione della proposta non è definita dal metodo, non è
univoca, ma va in qualche modo “tunata” sulla distribuzione da simulare

• In questo modo uno stato x’ più probabile di x è sempre accettato,
mentre uno meno probabile è accettato con probabilità p(x’)/p(x)
T.A.N.S.

4

Algoritmo di Metropolis

a.a. 2017/18

1. Inizializzazione: si parte da un valore arbitrario x0
All’iterazione n :
1. Si estrae casualmente un valore x dalla distribuzione pr(x|xn-1)
che supponiamo simmetrica.
2. Si calcola il rapporto di accettazione a=p(x)/p(xn-1)
1.
2.

Se a>1 si pone xn=x
Se a≤1, si estrae casualmente un numero u con distribuzione uniforme tra
0 e 1.
1.
2.

Se u≤a si pone xn=x
Altrimenti si pone xn=xn-1

3. Si ripete dal punto 1, sostituendo xn a xn-1.
T.A.N.S.

5

