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

    * This module is implemented as an output filter. Use SetOutputFilter directive to activate it.

    * for local use. ::

        RewriteRule ^/images/(.+)$ /your/local/images/$1 [L]
        RewriteRule ^/resize/(.+)$ /small_light(dw=400,dh=400,ds=s)/$1 [P,L]
        RewriteRule ^/small_light[^/]*/(.+)$ /your/local/images/$1
        <LocationMatch ^/small_light[^/]*/>
          SetOutputFilter SMALL_LIGHT
        </LocationMatch>


    * for dedicated use. ::

        RewriteRule ^/images/(.+)$ http://img.example.com/your/images/$1 [P,L]
        RewriteRule ^/resize/(.+)$ /small_light(dw=400,dh=400,ds=s)/$1 [P,L]
        RewriteRule ^/small_light[^/]*/(.+)$ http://img.example.com/your/images/$1 [P,L]
        <LocationMatch ^/small_light[^/]*/>
          SetOutputFilter SMALL_LIGHT
        </LocationMatch>


    * After you set the output filter, your apache transforms an image by transformation pattern specified in the URI.


    * The pattern string specifies as KEY=VALUE format in small_light(). **To use GraphicsMagick, set `e=graphicsmagick`.**

      ========= ===========================================================
      KEY       VALUE [TYPE OF VALUE]
      ========= ===========================================================
      sx        source x [coord]
      sy        source y [coord]
      sw        source width [coord]
      sh        source height [coord]
      dx        destination x [coord]
      dy        destination y [coord]
      dw        destination width [coord]
      dh        destination height [coord]
      da        destination aspect ratio control [char]
                (s=short-edge l=long-edge n=nope default:l)
      ds        destination scaling control [char]
                (s=force scale n=no scale small image default:n)
      cw        canvas width [number]
      ch        canvas height [number]
      cc        canvas color(default:000000) [color]
      bw        border width [number]
      bh        border height [number]
      bc        border color(default:000000) [color]
      pt        pass through control [char]
                (ptss:pass through when size of src-image < dest.
                ptls:pass through when size of src-image > dest.
                n:none. default:n)
      q         quality(affects only jpeg or png, 0-100) [number]
      of        output format(jpeg,png,tiff,gif) [char] \*1
      inhexif   inherit EXIF [char] \*2
                (n:none y:inherit default:n)
      jpeghint  enable jpeg loading optimization [char]
                (n:none y:enable default:n)
      info      add transformation description to HTTP Header [number]
                (0:none 1:add default:0)
      p         pattern name(see below)
      e         engine name(graphicsmagick,imlib2,imagemagick,dummy) [char]
      sharpen   sharpen=radius [number]
      unsharp   unsharp=radius [number]
      blur      blur=radius [number]
      ========= ===========================================================

      \*1 of=gif is supported only when e=imagemagick

      \*2 inhexif is supported only when e=imlib2

    * TYPE OF VALUE

      ============= =====================================================
      coord         corrdinate. pixel, or percent by appending 'p'.
      char          character
      number        number
      color         rrggbb or rrggbbaa. ffffff as white, 000000 as black.
      ============= =====================================================


    * Pattern name

      You can use named pattern by using SmallLightPatternDefine directive. This will reduce length and complexity of your URI.::

        SmallLightPatternDefine <PATTERN_NAME> <PATTERN STRING>

    * Some examples here.::

        SmallLightPatternDefine THUMB_SMALL sx=5p,sy=5p,sw=90p,sh=90p,dw=40,dh=40,da=l,cw=40,ch=40,cc=ffffff,q=80,of=jpeg
        SmallLightPatternDefine THUMB_MEDIUM sx=5p,sy=5p,sw=90p,sh=90p,dw=96,dh=96,da=l,cw=96,ch=96,cc=ffffff,q=80,of=jpeg
        SmallLightPatternDefine THUMB_LARGE sx=5p,sy=5p,sw=90p,sh=90p,dw=200,dh=200,da=l,cw=200,ch=200,cc=ffffff,q=80,of=jpeg

    * To use named pattern, simply small_light(p=PATTERN_NAME). The pattern could be overridden by patterns followed.::

        small_light(p=THUMB_SMALL)

        OR

        small_light(p=THUMB_SMALL,q=80) * 'q' will be overridden to 80.


    * Parameters for the additional effects are:


      ======== ===========================================================
      KEY      VALUE
      ======== ===========================================================
      rotate   rotate image (0-360 degrees). set like "rotate=90" [number]
      oilpaint effect filter that simulates an oil painting. set radius of the circular neighborhood like "oilpaint=3" [number]
      contrast enhance/ contrast of image. set "contrast=1" or "contrast=-1" [number]
      ======== ===========================================================


* ACKNOWLEDGEMENT

    * Thanks for developers of mod_small_light_.

    * Thanks for pixiv Inc. and @cubicdaiya. This work had been done during an internship at pixiv Inc.
