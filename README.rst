====================================
mod_small_light-with-GraphicskMagick
====================================

mod_small_light_ is an Apache-module for dynamic image transformation, e.g. dynamic thumbnail generation, and it originally hosted on google-code.

.. _mod_small_light: http://code.google.com/p/smalllight/

Here we extend mod_small_light-1.1.1 as `mod_small_light-with-GraphicskMagick`, so that it can use GraphicsMagick_ as its another backend of image transformation. (mod_small_light originally supports ImageMagick and Imlib2.)

As a result, **mod_small_light-with-GraphicsMagick outperformed one with ImageMagick in requests-per-second to generate thumbnails**.

.. _GraphicsMagick: http://www.graphicsmagick.org/

Moreover we added some effects like rotation, oil-paint effect and contrast control.

----

**Notice**: Following documentation is based on original documentation here_.

.. _here: http://code.google.com/p/smalllight/wiki/Install


* INSTALL

    #. Install apache2, imlib2, ImageMagick and GraphicsMagick.

    #. Install required Apache-modules. ::

        $ a2enmod rewrite proxy proxy_http

    #. Run configure script. ::

        $ ./configure --with-apxs=/path/to/apache2/bin/apxs \
        --with-imlib2-config=/path/to/bin/imlib2-config \
        --without-Wand \
        --with-GraphicsMagickWand-config=/path/to/bin/GraphicsMagickWand-config

        # Notice: GraphicsMagick cannot work with original ImageMagick.
        #         So set --without-Wand and --with-GraphicsMagickWand.


    #. Compile & Install::

        $ make
        $ sudo make install


* HOW TO USE

  * This module is implemented as an output filter. Use SetOutputFilter directive to activate it. After you set the output filter, your apache transforms an image by transformation pattern specified in the URI.

  * for local use, set Apache's config file like following: ::

         RewriteRule ^/images/(.+)$ /your/local/images/$1 [L]
         RewriteRule ^/resize/(.+)$ /small_light(dw=400,dh=400,ds=s)/$1 [P,L]
         RewriteRule ^/small_light[^/]*/(.+)$ /your/local/images/$1
         <LocationMatch ^/small_light[^/]*/>
           SetOutputFilter SMALL_LIGHT
         </LocationMatch>

  * The pattern string specifies as KEY=VALUE format in small_light() is described described here: PatternString_

    * **To use GraphicsMagick, set `e=graphicsmagick`.**

    * Parameters for the additional effects are:


        ======== ===========================================================
        KEY      VALUE
        ======== ===========================================================
        rotate   rotate image (0-360 degrees). set like "rotate=90" [number]
        oilpaint effect filter that simulates an oil painting. set radius of the circular neighborhood like "oilpaint=3" [number]
        contrast enhance/ contrast of image. set "contrast=1" or "contrast=-1" [number]
        ======== ===========================================================

.. _PatternString: http://code.google.com/p/smalllight/wiki/PatternString


* ACKNOWLEDGEMENT

    * Thanks for developers of mod_small_light_.

    * Thanks for pixiv Inc. and @cubicdaiya. This work had been done during an internship at pixiv Inc.
