libexpression
=============

A C++ library to express (and evaluate) symbolic equations. See the documentation `here
<https://libexpression.readthedocs.io/en/latest/#>`_.


What this library can do
------------------------

This library allows you to formulate algorithmic functions with as little programmatic overhead as
possible. Examples that this formulation can be used for include, but are not limited to `sha256`,
and others.


Building the project
--------------------

The `libexpression` project's buils system is CMake based. In order to build it from source, run the
following commands from your command line:

.. code-block:: bash

   git clone https://github.com/fairlight1337/libexpression.git
   cd libexpression
   mkdir build
   cd build
   cmake ..
   make

The resulting binary executables will then be in `build/bin`. After building, run the main
executable with:

.. code-block:: bash

   ./bin/libexpression-bin
