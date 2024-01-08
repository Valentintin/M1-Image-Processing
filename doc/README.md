# traitement_img_M1

https://docs.opencv.org/2.4.13.7/doc/user_guide/ug_mat.html?highlight=pixel

## Region Growing

1. Parcours du germe :
    - la croissance du germe amorcé à la main jusqu'a la région final

2. Distribution des germes :
    - On divise notre image en plusieurs régions justifier la partition faite
    - Pour chaque division on met une germe aléatoirement, ( si on a le temps : on met 1 germe au max et min de l'histogramme de l'image).

3. Structure de donnée :
    - chaque région est une image de la même taille afin de process le parcour en multi-thread
    - on rassemble l'image final et voilà !

## multi-thread
Cours sur le multi-thread C++ : 
https://asr-lyon1.gitlabpages.inria.fr/prog-concurrente/cm-threads/cm-threads-slides.pdf


## valgrind
pour regarder les fuites de mêmoire : 
```sh
valgrind --leak-check=full ./main 
```
pour regarder l'optimisation : 
```sh
valgrind --tool=callgrind ./main && callgrind_annotate callgrind.out.* >>optimisation
```
et penser à *rm callgrind.out** à la fin