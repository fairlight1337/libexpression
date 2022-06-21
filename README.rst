=============
libexpression
=============

A C++ library to express (and evaluate) symbolic equations. See the documentation `here <https://libexpression.readthedocs.io/en/latest/#>`_.


------------------------
What this library can do
------------------------

This library allows you to formulate algorithmic functions with as little programmatic overhead as possible. Examples that this expression can be used for include, but are not limited to ``sha256``, ``ripemd160``, and others.


Simple example
==============

In this example, a short function ``a & b == 5`` is produced. The underlying data type used here is an unsigned integer with a total of 3 bits used for each unit.

.. code-block:: cpp

   using Expr = expression::Expression<uint32_t, 3>
   
   Expr a("a");
   Expr b("b");
   Expr c(5U);
   Expr formulation = (a & b == c);
   
   std::cout << formulation << std::endl;
   
This yields this output:

.. code-block:: bash

   [=(&(a2, b2), t), =(&(a1, b1), t), =(&(a0, b0), t)]

Where ``t`` represents a positive truth value (or ``1``) and ``f`` represents ``0``. The library supports another variable state ``u`` (undefined), which is not used here. As you can see here, the individual functions are propagated down onto bit level. Each subsequent top array entry can thus be evaluated solely based on one bit level.


Supported operations
====================

.. list-table::
   :widths: 25 25 50
   :header-rows: 1

   * - Operation
     - Operands
     - Description
   * - Logical AND (``&``)
     - ``2`` to ``n`` entities
     - Logically ANDs all operands.
   * - Logical OR (``|``)
     - ``2`` to ``n`` entities
     - Logically ORs all operands.
   * - Logical XOR (``^``)
     - ``2`` entities
     - Logically XORs the two operands.
   * - Logical NOT (``~``)
     - ``1`` entity
     - Logically inverts the operand.


--------------------
Building the project
--------------------

The ``libexpression`` project's build system is CMake based. In order to build it from source, run the following commands from your command line:

.. code-block:: bash

   git clone https://github.com/fairlight1337/libexpression.git
   cd libexpression
   mkdir build
   cd build
   cmake ..
   make

The resulting binary executables will then be in ``build/bin``. After building, run the main executable with:

.. code-block:: bash

   ./bin/libexpression-bin


-------------------
Development Roadmap
-------------------

The library is still in its infancy. Functionality is added bit by bit, but in general this is the coarse plan regarding future development:

V0.1.0
======

* Stable external class interface (single class entry via ``Expression<>``).

* First batch of examples to showcase what the library can do (e.g., ``sha256``, ``ripemd160``).

* First set of unit tests for individual logic operators, also integrated into the build process.

* Doxygen coverage for the most important parts.

* Fully integrated `clang-tidy` into the build process.

* Support for operators ``&``, ``|``, ``^``, ``~``.


VX.Y.Z
======

* First version of solver class to perform an educated iteration over available solutions of an expression.

* Full coverage via unit tests and example algorithms.

* Full Travis CI integration including automated tests.

* Full Doxygen coverage.

* Support for operator ``=``.

* Dynamic transformations (expression simplification).
