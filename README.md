Cours pratique sur le reverse engineering et l'exploitation de binaire
=====

Le contenu du cours nommé sera disponible dans ce dépôt git. Il contiendra
notamment:

 * Les slides
 * Des ressources/outils
 * Les travaux à rendre + corrigés 
 * Les binaires étudiés en classe ainsi que leur code source une fois terminé

Le plan du cours est détaillé dans les slides "0\_presentation" et se clotura
par un mini CTF sur ce qui aura été abordé.

N'hésitez pas à m'envoyer un mail si vous avez des difficultées ou des
questions!

# Slides

Les slides sont écrites en utilisant [reveal.js](https://github.com/hakimel/reveal.js) 
ainsi elles seront disponibles au format html ou pdf, selon votre préférence

# Outils

* [Ghidra](https://ghidra-sre.org/), l'outil principal de reverse que l'on
  utilisera
* [IDA Pro](https://www.hex-rays.com/), un outil de reverse professionel qui
  coute plus de 10k€+ par an avec tous les décompilateurs. Il est meilleur que
  Ghidra sur certains points très spécifiques mais la plupart du temps, même
  si vous obtenez IDA gratuitement grâce à l'aide d'un certain Jiang Ying, vous
  voudrez utiliser Ghidra. Une comparaison plus technique est disponible
  dessous.
* [radare2](https://github.com/radareorg/radare2), un autre outil de reverse en
  ligne de commande. Un GUI est aussi disponible appellé Cutter. Il
  est en général plus lent que les deux autres mais a le mérite d'être open
  source et gratuit. Si vous n'avez pas besoin d'un bon décompilateur et voulez
  juste regarder rapidement de l'assembleur(en graphe ou non) d'un binaire alors
  ça peux être utile. 
* [gdb-peda](https://github.com/longld/peda), un addon pour gdb aidant
  grandement l'exploitation. Si vous avez vos plugins préférés de ce type ou
  votre propre debugger custom ça marche aussi :D

# Ghidra vs IDA (Attention c'est technique)
  Ghidra entre autre a une architecture faisant en
  sorte que rajouter des décompilateurs et les modifier est très simple, comparé a
  IDA ou c'est impossible(des personnes ont du [transpilés une architecture
  custom vers ARM pour avoir un décompilateur](https://github.com/TeamMolecule/mep-wtf); 
  ils utilisent un langage qu'ils appellent SLEIGH qui définie comment parser
  une architecture mais aussi comment elle fonctionne de façon très succinte. 
  Sous IDA on doit faire des scripts pythons assez witchcraft pour que tout
  fonctionne.  
  Ghidra a un système de serveur pour faire de la RE collaborative intégrée, a
  un système pour patcher et assembler directement sur le fichier que vous
  regardez, est gratuit et open source libre(vous pouvez aider a fixer des bugs si
  c'est super urgent contrairement a IDA), et a des features comme la vue
  side-by-side assembleur décompilateur qu'IDA s'efforce de copier(pour vous dire,
  IDA a refuser d'intégrer un undo depuis des années en narguant que c'était
  beaucoup trop compliquéet quand Ghidra est sorti,
  miraculeusement au bout de 3 mois c'était fait).   
  Le système de plugin de Ghidra est mieux foutu et donne plus de libertées en
  général. Ghidra a des méthodes pour auto créer des structures qu'IDA n'a pas.
  Il est plus simple de définir des structures grâce à un GUI ou changer les
  calling conventions/registres utilisés par une fonction.

  La ou IDA a l'avantage c'est pour les binaires absolument énormes vu que
  Ghidra prends un peu plus de ressources qu'IDA, avoir une vue en graphe plus
  rapide(l'UX de Ghidra est super lente) et étudiez des trucs très spécifiques
  comme des bouts de code d'iOS avec PAC.

# Ressources

* [Compiler Explorer](https://godbolt.org/), un site aui permet de voir comment différents
  compilateurs compilent du code que vous donnez en temps réel, assez sympa pour
  commencer a avoir du feeling pour le reverse (ou à débugger des bugs de
  compilateur, ça arrive plus souvent que vous ne le croyez)
* [MicroCorruption](https://microcorruption.com/login), un CTF avec une archi
  custom qui explique les bases de la corruption de mémoire, je recommende
  fortement!
* [RootMe](https://www.root-me.org/), un site français qui a quelques crackmes
  sympa pour apprendre l'exploit/reverse
* [Rust](https://rust-lang.org/), un langage de programmation qui réduit quasi à
  néant le risque de corruption de mémoire par un système de code safe/unsafe, a
  regarder absolument si vous vous intéressez à la défense.
* [Un article emblématique de phrack](http://www.phrack.org/issues/49/14.html)
  une zine de sécurité informatique qui marque le début de l'apparition des
  exploits de type stack overflow.


Et dans le niveau plus technique, genre vraiment, il y'a très peu de chances que
vous arriviez à tout comprendre du premier coup:

* [Une analyse de chaine d'exploits iOS](https://googleprojectzero.blogspot.com/2019/08/a-very-deep-dive-into-ios-exploit.html), 
  Une analyse de chaines complètes d'exploits utilisés contre la population
  Uighur par les services chinois, vous visitez un site web et sans que vous le
  sachiez vos données personelles sont envoyées aux services automatiquement. 
* [PS3 Epic Fail](https://www.youtube.com/watch?v=5E0DkoQjCmI), 
  [Nintendo Hacking 2016](https://www.youtube.com/watch?v=8C5cn_Qj0G8), 
  [Methodically Defeating Nintendo Switch Security](https://arxiv.org/abs/1905.07643), 
  des résumés plus techniques de hack de console de A a Z. Les talks de
  fail0verflow sont particulièrement intéressants!
* [Un writeup sur un exploit de firefox](https://phoenhex.re/2017-06-21/firefox-structuredclone-refleak),
  un exploit qui en théorie permets d'exécuter du code choisi outre la sandbox
  de firefox juste en visitant un site web!


# Setup

Le cours sera centré autour de Linux et, pour la majeure partie afin d'aborder
le concept pédagogiquement, n'aura pas de majeures mitigations récentes(ie ASLR, stack
cookie, la stack ne SERA pas exécutable cependant).
J'aborderais ces sujets selon l'avancée de la classe. Du coup une machine linux
devrait suffir pour suivre tout le cours.
