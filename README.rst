======================================
mod_small_light (with GraphicskMagick)
======================================

mod_small_light_ is an Apache-module for dynamic image transformation, e.g. thumbnail generation. (originally hosted on google-code)

.. _mod_small_light: http://code.google.com/p/smalllight/

It supports only ImageMagick and Imlib2 as backends of image transformation.

So, here we added `GraphicsMagick`_ as its backend, because it runs faster than ImageMagick.

As a result **mod_small_light with GraphicsMagick outperformed one with ImageMagick in requests-per-second.**.

.. _GraphicsMagick: http://www.graphicsmagick.org/

Moreover we added some effects like rotation, oil-paint and contrast.


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

    * See original documentation here_.

      .. _here: http://code.google.com/p/smalllight/wiki/Install


    * Notice: additional parameters are


      ======== ===========================================================
      key      value
      ======== ===========================================================
      rotate   rotate image (0-360 degrees). set like "rotate=90" [number]
      oilpaint effect filter that simulates an oil painting. set radius of the circular neighborhood like "oilpaint=3" [number]
      contrast enhance/ contrast of image. set "contrast=1" or "contrast=-1" [number]
      ======== ===========================================================

* LICENSE

    * MIT License


* ACKNOWLEDGEMENT

    * Thanks for pixiv Inc. and @cubicdaiya. This work had been done during an internship at pixiv Inc.
