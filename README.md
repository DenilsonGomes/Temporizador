***
<h1 align="center" > Temporizador de Proposito Geral<br>
<br>

1.Introdução
==========

<p>Esse projeto é um temporizador de proposito geral que conta até o tempo desejado, disparando um alarme
quando o tempo for alcançado. O mesmo pode ser utilizado para qualquer atividade que tenha necessidades
temporais.<p/>

2.Especificações
==========

<p>Esse temporizador usa um teclado matricial para a entrada
do tempo desejado, um botão play/pause, um botão reset, um display de 4 digitos para monitoramento
do tempo, um led e um buzzer para sinalizar visual e sonoramente o alarme. O prototipo foi montado usando um
Arduino Uno com Atmega 328p.<p/>

3.Visão Geral
-----------

<p></p>
<p>O sistema funciona contando o até o tempo desejado, que deve ser inserido com o teclado matricial.<p>
Para inserir o tempo é necessário deixar apertado o botão de pause, e em seguida apertar o "*" no teclado.</p>
Após digitar o "*" deve-se digitar o tempo em 4 digitos no formato minutos:segundos, logo dois digitos para
os minutos e dois digitos para os segundos.</p>
Após inserido, o tempo é exibido no display por 3 segundos, depois o display volta o valor que estava.</p>
Depois de voltar para o tempo atual, o temporizador está pronto para contar até o tempo desejado.</p>
Para iniciar a contagem basta apertar o play. O botão reset pode ser acionado sem a contagem estar pausada.</p>
