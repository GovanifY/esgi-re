Cours pratique sur le reverse engineering et l'exploitation de binaire
=====

Le contenu du cours nommé sera disponible dans ce dépôt git. Il contiendra
notamment:

 * Les slides
 * Des ressources/outils
 * Les travaux à rendre + corrigés 
 * Les binaires étudiés en classe ainsi que leur code source une fois terminé

Le plan du cours est détaillé dans les slides "0\_presentation" et se clôtura
par un mini CTF sur ce qui aura été abordé.

N'hésitez pas à m'envoyer un mail si vous avez des difficultés ou des
questions!

# Slides

Les slides sont écrites en utilisant [reveal.js](https://github.com/hakimel/reveal.js) 
ainsi elles seront disponibles au format HTML ou PDF, selon votre préférence

# Setup

Le cours sera centré autour de Linux et, pour la majeure partie afin d'aborder
le concept pédagogiquement, n'aura pas de majeures mitigations récentes (i.e. ASLR, stack
cookies, la stack ne SERA pas exécutable cependant).

J'aborderais ces sujets selon l'avancée de la classe.

Du coup une machine Linux devrait suffire pour suivre tout le cours.

# Outils

* [Ghidra](https://ghidra-sre.org/), l'outil principal de reverse que l'on
  utilisera
* [IDA Pro](https://www.hex-rays.com/), un outil de reverse professionel qui
  coute plus de 10k€+ par an avec tous les décompilateurs. Il est meilleur que
  Ghidra sur certains points très spécifiques mais la plupart du temps, même
  si vous obtenez IDA gratuitement grâce à l'aide d'un certain Jiang Ying, vous
  voudrez utiliser Ghidra. Une comparaison plus technique est disponible
  ci-dessous.
* [radare2](https://github.com/radareorg/radare2), un autre outil de reverse en
  ligne de commande. Un GUI est aussi disponible appelé Cutter. Il
  est en général plus lent que les deux autres mais a le mérite d'être open
  source et gratuit. Si vous n'avez pas besoin d'un bon décompilateur et voulez
  juste regarder rapidement de l'assembleur(en graphe ou non) d'un binaire alors
  ça peux être utile. 
* [gdb-peda](https://github.com/longld/peda), un addon pour gdb aidant
  grandement l'exploitation. Si vous avez vos plugins préférés de ce type ou
  votre propre debugger custom ça marche aussi :D


# Ressources

* [Compiler Explorer](https://godbolt.org/), un site qui permet de voir comment différents
  compilateurs compilent du code que vous donnez en temps réel, assez sympa pour
  commencer a avoir du feeling pour le reverse (ou à debugger des bugs de
  compilateur, ça arrive plus souvent que vous ne le croyez)
* [MicroCorruption](https://microcorruption.com/login), un CTF avec une archi
  custom qui explique les bases de la corruption de mémoire, je recommande
  fortement!
* [RootMe](https://www.root-me.org/), un site français qui a quelques crackmes
  sympa pour apprendre l'exploit/reverse
* [Rust](https://rust-lang.org/), un langage de programmation qui réduit quasi à
  néant le risque de corruption de mémoire par un système de code safe/unsafe, a
  regarder absolument si vous vous intéressez à la défense.
* [Un article emblématique de phrack](http://www.phrack.org/issues/49/14.html)
  une zine de sécurité informatique qui marque le début de l'apparition des
  exploits de type stack overflow.


Et dans le niveau plus technique, genre vraiment, il y a très peu de chances que
vous arriviez à tout comprendre du premier coup:

* [Une analyse de chaine d'exploits iOS](https://googleprojectzero.blogspot.com/2019/08/a-very-deep-dive-into-ios-exploit.html), 
  Une analyse de chaines complètes d'exploits utilisés contre la population
  Uighur par les services chinois, vous visitez un site web et sans que vous le
  sachiez vos données personnelles sont envoyées aux services automatiquement. 
* [PS3 Epic Fail](https://www.youtube.com/watch?v=5E0DkoQjCmI), 
  [Nintendo Hacking 2016](https://www.youtube.com/watch?v=8C5cn_Qj0G8), 
  [Methodically Defeating Nintendo Switch Security](https://arxiv.org/abs/1905.07643), 
  des résumés plus techniques de hack de console de A à Z. Les talks de
  fail0verflow sont particulièrement intéressants!
* [Un writeup sur un exploit de firefox](https://phoenhex.re/2017-06-21/firefox-structuredclone-refleak),
  un exploit qui en théorie permets d'exécuter du code choisi outre la sandbox
  de Firefox juste en visitant un site web!

# Ghidra vs IDA (Attention c'est technique)

Contrairement à IDA, Ghidra est conçu de façon modulaire, ajouter ou changer un décompilateur est très facile.
En particulier, pour IDA, des équipes de RE ont dû écrire un transpilateur d'une architecture custom vers ARM
afin de pouvoir réutiliser le décompilateur d'IDA, c.f. <https://github.com/TeamMolecule/mep-wtf>.

Précisément, Ghidra utilise un langage appelé SLEIGH qui définit comment parser l'arcthitecture
mais aussi comment elle fonctionne de façon succinte.

Alors que sous IDA, il est monnaie courante d'écrire des tas de scripts Python obscurs pour obtenir
un environnement d'analyse décent.

Aussi, points non négligeables, Ghidra a:

* un système de serveur pour faire de la collaboration en RE
* un système pour patcher et assembler directement sur le fichier sur lequel vous travaillez
* une vue côte-à-côte assembleur/décompilateur qu'IDA refuse d'implémenter (dans la foulée, IDA refusait aussi d'ajouter une fonctionnalité d'undo, 3 mois après la sortie de Ghidra, la fonctionnalité est apparue magiquement.)
* un vrai système de plugin modulaire
* des méthodes d'auto-création des structures plus simples que celles d'IDA
* est gratuit; open-source; **libre** (ce qui a le bon goût de vous permettre d'aller vous même patcher Ghidra ou fixer les bugs qui sont urgents pour votre équipe)

Cependant, là où Ghidra pêche et IDA prend la main, c'est sur les binaires gigantesques.

Ghidra étant écrit en Java, tournant sous la JVM, il prend plus facilement qu'IDA écrit en C++/Qt.

Mais aussi, les fonctionnalités de calcul et d'affichage des graphes de flot de contrôle sont plus stables.

Enfin, IDA est aussi pratique pour l'étude de code exotique, e.g. l'analyse des instructions PAC sous iOS.
