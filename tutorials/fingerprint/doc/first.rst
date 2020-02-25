.. :orphan:

The first step
==============

all this fingerprint testing depends on repeatable deterministic simulations, random number generation, etc.
if it's not repeatable, e.g. emulation, than this whole stuff doesn't apply

default ingredients is good because there's always a fingerprint sensitive to changes ready-to-be-used for regression testing

  - the configs in the tutorial that will be used to demonstrate the fingerprint tests
  - the csv file
  - they are correct fingerprints
  - the changes are no contained in the tutorial
  - the user is expected to make them and run the fingerprint test to see the results

The tutorial contains several simulations, which will be used to demonstrate how various changes affect fingerprints:

TODO: a list of the configs (just an overview)

The ``fingerprintshowcase.csv`` file in the tutorial's directory containing the fingerprints TODO:

.. .. literalinclude:: ../fingerprintshowcase.csv
      :language: text

.. literalinclude:: ../fingerprintshowcase.csv
   :start-at: sim time limit
   :language: text

.. code-block:: text

  # working dir, cmd line args, sim time limit, fingerprint, expected result, tags

  .,        -f omnetpp.ini -c Wireless -r 0,        5s,         1160-9f52/tlx,  PASS,
  .,        -f omnetpp.ini -c Mixed -r 0,           5s,         0bf0-4adf/tlx,  PASS,
  .,        -f omnetpp.ini -c Wired -r 0,           5s,         65c4-d41e/tlx,  PASS,
  .,        -f omnetpp.ini -c WirelessNID -r 0,     5s,         d410-0d99/NID,  PASS,
  .,        -f omnetpp.ini -c WiredNID -r 0,        5s,         1145-0392/NID,  PASS,
  .,        -f omnetpp.ini -c MixedNID -r 0,        5s,         d2fb-2f48/NID,  PASS,
  .,        -f omnetpp.ini -c WirelessNIDDim -r 0,  5s,         d410-0d99/NID,  PASS,
  .,        -f omnetpp.ini -c WirelessDim -r 0,     5s,         1160-9f52/tlx,  PASS,
  .,        -f omnetpp.ini -c Ospf -r 0,            5000s,      e1cb-efa1/tlx,  PASS,

.. **V1** The .csv file contains the correct fingerprints **TODO** what does that mean?. The changes mentioned in the tutorial are not contained in the anywhere, the user is expected to make them and run the fingerprint tests to see how the model changes affect the fingerprints.

.. The .csv file contains the correct fingerprints **TODO** what does that mean?. The user is expected to make the changes and run the fingerprint tests to see how the model changes affect the fingerprints.

The .csv file contains the correct fingerprints, i.e. they all pass. To try the examples, the user is expected to make the changes described in the tutorial (or something similar/something else/some other changes/different changes) and run the fingerprint tests to see how the model changes affect the fingerprints.

TODO its for experimentation

The fingerprints can be run from the command line. Make sure to run ``. setenv`` in both the ``omnetpp`` and ``inet`` folders:

.. code-block:: bash

   $ cd ~/workspace/omnetpp
   $ . setenv
   $ cd ~/workspace/inet
   $ . setenv
   $ cd tutorials/fingerprint
   $ inet_fingerprinttest

TODO: the setenv and the fingerprinttest separately ?

The ``inet_fingerprinttest`` runs all simulations specified in all .csv files in the currect folder:

.. code-block::

  $ inet_fingerprinttest
  . -f omnetpp.ini -c Wired -r 0  ... : PASS
  . -f omnetpp.ini -c Mixed -r 0  ... : PASS
  . -f omnetpp.ini -c Wireless -r 0  ... : PASS
  . -f omnetpp.ini -c WirelessNID -r 0  ... : PASS
  . -f omnetpp.ini -c WiredNID -r 0  ... : PASS
  . -f omnetpp.ini -c Ospf -r 0  ... : PASS
  . -f omnetpp.ini -c MixedNID -r 0  ... : PASS
  . -f omnetpp.ini -c WirelessDim -r 0  ... : PASS
  . -f omnetpp.ini -c WirelessNIDDim -r 0  ... : PASS

  ----------------------------------------------------------------------
  Ran 9 tests in 23.646s

  OK

  Log has been saved to test.out
  Test results equals to expected results

.. figure:: media/1.png
   :width: 80%
   :align: center
