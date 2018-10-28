# Definició de ORB Features

La definició de ORB es una eina que s'utilitza en el sistema de "computer vision" i serveix per detectar rapidament punts de contrast en una imatge. Es a dir, es capaç de trobar x punts en una imatge que tingui un contrast bastant elevat. Això pot permetre la reconstrucció d'objectes.

Dins del sistema ORB hi ha moltes comandes per poder aconseguir diferents resultats. En aquest projecte hem aconseguit concentrar la búsqueda d'aquests features points en una zona concreta.

Una altre definició important en aquest ambit es el KeyPoints que en aquest projecte tambe sútilitza. Aquesta eina es la que dibuixa els punts trobat per la eina ORB Detector. Pots cambiar el Color i altre variables. En aquest projecte només canviem el color dels punts.

Les comandes que s'han utilitzat són:

```orb_detector->detectAndCompute(grayimage, Mask, point_set, descriptor_set);```
```cv::drawKeypoints(grayimage, point_set, grayimage, Color, cv::DrawMatchesFlags::DEFAULT );```

# Webcam_point_features program

Detecció dels ORB features de la webcam del PC.


Entrem en el nostre Github i fem un "fork" d'aquest Github https://github.com/beta-robots/webcam_point_features.git

Clonem aquest repositori a la carpeta que nosaltres volguem del nostre ordinador

Un cop creat la nostre carpeta de treball comencem a realitzar modificacions en el programa

La primera modificació que fem es pasar la imatge amb color a una escala de grisos

```cv::Mat grayimage;```
```cv::cvtColor( image, grayimage, CV_BGR2GRAY );```

Abans de començar a crear la màscara fem proves per cambiar el color de les KeyPoints

Declarem una variable Color que es "Scalar" i definim la intencitat de cada un dels color R + G + B per obtenir el color desitjat

En el nostre cas posem el valor (0,255,0) que es el color Green

```Scalar Color = Scalar(0,255,0);```

Per poder realitzar una zona exclusiva dins la imatge per posar els KeyPoints ho fem a través d'una mascara i una variable roi

A continuació es veuen les dos comandes que fem per realitzar un escaneig dels features points amb una mascar en forma de rectangle

```cv::Mat Mask;```
```cv::Mat roi;```

En aquest punt hem creat les variables que utilitzarem

```Mat Mask = Mat::zeros(image.size(), CV_8U);```

```Mat roi(Mask, cv::Rect(250,150,220,300));```

```Mat roi = Scalar(255);```

Col·loquem zeros en tota la imatge que capturem i li pasem una Mascara rectangular que té posició d'inici i el tamany

Només visualitzem KeyPoints en aquest Rectangle, Rect(X_position, Y_position, Mask_width, Mask_Height), La X i Y positions són les posicions on comença aqust rectangel i els altres dos valor són el tamany del rectangle

Un cop realitzades aquestes comandes compilem per veure que no hi hagi cap error i executem.

El resultat és la imatge de la web cam amb escala de grisos i una zona central de la imatge on només apareixen els KeyPoints. Aquesta zona és la que hem definit amb la posició + tamany del rectangle

El programa també disposa d'un detector de contorns amb la comanda Canny, s'ha buscat un exemple de com utilitzar la comanda Canny


```Canny(grayimage, edge, 50, 150, 3);```
```edge.convertTo(draw, CV_8U);```

En aquest cas mostrarem a la pantalla la imatge "draw" que és la que està procesada per detectar els contorns        

# Used References

Aqui adjuntem les principals referencies que hem utilitzat per poder realitzar aquesta modificació en el programa webcam_point_features

<ol>
  
<li>https://es.wikipedia.org/wiki/RGB</li>

<li>https://docs.opencv.org/3.3.0/d3/d96/tutorial_basic_geometric_drawing.html</li>

<li>https://docs.opencv.org/2.4/doc/tutorials/core/mat_the_basic_image_container/mat_the_basic_image_container.html</li>

<li>https://docs.opencv.org/3.1.0/d3/d63/classcv_1_1Mat.html</li>

<li>http://answers.opencv.org/question/10364/set-roi-in-cvmat/</li>

<li>http://opencvexamples.blogspot.com/2013/10/void-canny-inputarray-image-outputarray.html</li>

</ol>


