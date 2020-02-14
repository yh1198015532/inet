.. :orphan:

New events - filtering
======================

..  1. change or action
  2. phenomenon / effect
  3. solution
  4. example

Some changes in the model can add new events to the simulation. These events inevitably change the fingerprints but not necessarily invalidate the model. One option is to filter out the modules in which the new events take place. Taking into account the rest of the modules might show that the simulation trajectory in fact stayed that same.

To filter out modules, run the fingerprint test with the ``--fingerprint-modules`` command line option, e.g.:

.. TODO example

.. code-block:: bash

   $ inet_fingerprinttest -a --fingerprint-modules='"not fullPath=~**.wlan[*].mac.**"'

Filtering makes the simulations run slower because the filter expression needs to be evaluated at all events.

.. Then, update the fingerprints, make the change, and run the fingerprints again.

.. TODO when running the filtered fingerprints, the new fingerprints can be accepted, as there was no change in the model. When running the fingerprints after making the changes, they PASS...

.. TODO not here

.. TODO do this before making the change

.. TODO example

.. TODO the fingerprint-modules= can be added to the .csv file as well -> note

.. As a simplistic example, we will make changes to the Udp module that we expect not to alter its behavior.

.. so

  - we make change which creates additional events but we think it doesnt change the module's behavior
  - because of the additional events the fingerprints will change
  - so we dont use them
  - filter the module

As a simplistic example, we will make changes to the Udp module's code; the changes add new events, but doesn't change the module's behavior. However, the fingerprints will change; we will filter out the Udp module from the fingerprint calculation to verify the model/the correctness of the model/that there was no change in the model. Here is the workflow:

We run the fingerprint tests without taking the Udp module into account (the order of the quotes is important):

.. code-block:: fp

   $ inet_fingerprinttest -a --fingerprint-modules='"not fullPath=~**.udp"'
   . -f omnetpp.ini -c Wired -r 0  ... : FAILED (should be PASS)
   . -f omnetpp.ini -c Mixed -r 0  ... : FAILED (should be PASS)
   . -f omnetpp.ini -c Wireless -r 0  ... : FAILED (should be PASS)
   . -f omnetpp.ini -c WirelessNID -r 0  ... : PASS
   . -f omnetpp.ini -c WiredNID -r 0  ... : PASS
   . -f omnetpp.ini -c Ospf -r 0  ... : PASS
   . -f omnetpp.ini -c MixedNID -r 0  ... : PASS
   . -f omnetpp.ini -c WirelessDim -r 0  ... : FAILED (should be PASS)
   . -f omnetpp.ini -c WirelessNIDDim -r 0  ... : PASS

.. TODO the rest

.. TODO the order of the quotes is important

We can accept the fingerprints because there was no change in the model

.. code-block:: fp

   $ mv fingerprintshowcase.csv.UPDATED fingerprintshowcase.csv

Then we add a line to one of the functions in :cpp:`Udp.cc` which schedules a self message;
we also add a handleSelfMessage() function which just deletes the message when its received:

.. literalinclude:: ../Udp_mod.cc
   :diff: ../Udp_orig.cc

We run the fingerprint tests again without the Udp module:

.. TODO the same

.. code-block:: fp

  $ inet_fingerprinttest -a --fingerprint-modules='"not fullPath=~**.udp"'
  . -f omnetpp.ini -c Wired -r 0  ... : PASS
  . -f omnetpp.ini -c Mixed -r 0  ... : PASS
  . -f omnetpp.ini -c Wireless -r 0  ... : PASS
  . -f omnetpp.ini -c MixedNID -r 0  ... : PASS
  . -f omnetpp.ini -c WirelessNID -r 0  ... : PASS
  . -f omnetpp.ini -c WiredNID -r 0  ... : PASS
  . -f omnetpp.ini -c Ospf -r 0  ... : PASS
  . -f omnetpp.ini -c WirelessDim -r 0  ... : PASS
  . -f omnetpp.ini -c WirelessNIDDim -r 0  ... : PASS

The fingerprint tests PASS; the model is verified.

.. note:: The ``-fingerprint-module=""`` command line argument can be added to the .csv file as well.

.. this change introduces new events to the simulation, but doesn't alter the model.

.. After running the fingerprint tests, those configurations that has active :ned:`Udp` modules, fail:

.. TODO FAIL

.. .. code-block:: fp

  $ inet_fingerprinttest
  . -f omnetpp.ini -c Wired -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c Mixed -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c Wireless -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c WirelessNID -r 0  ... : PASS
  . -f omnetpp.ini -c WiredNID -r 0  ... : PASS
  . -f omnetpp.ini -c Ospf -r 0  ... : PASS
  . -f omnetpp.ini -c MixedNID -r 0  ... : PASS
  . -f omnetpp.ini -c WirelessDim -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c WirelessNIDDim -r 0  ... : PASS

.. TODO but default fingerprints change / tlx as well

.. TODO include the full output?

.. TODO filter

.. We revert the change, and run the fingerprint test again, filtering out the :ned:`Udp` module:

.. .. code-block:: fp

  $ inet_fingerprinttest -a --fingerprint-modules='"not fullPath=~**.Udp"'
  . -f omnetpp.ini -c WirelessNID -r 0  ... : PASS
  . -f omnetpp.ini -c WiredNID -r 0  ... : PASS
  . -f omnetpp.ini -c MixedNID -r 0  ... : PASS
  . -f omnetpp.ini -c Mixed -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c WirelessNIDDim -r 0  ... : PASS
  . -f omnetpp.ini -c Ospf -r 0  ... : PASS
  . -f omnetpp.ini -c Wired -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c Wireless -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c WirelessDim -r 0  ... : FAILED (should be PASS)

.. We update the fingerprints in the .csv file, make the change in the model, and run the fingerprint test.
   This time all tests pass. This indicates that the model works correctly after the change.

.. .. code-block:: fp

  $ inet_fingerprinttest -a --fingerprint-modules='"not fullPath=~**.Udp"'
  . -f omnetpp.ini -c WirelessNID -r 0  ... : PASS
  . -f omnetpp.ini -c WiredNID -r 0  ... : PASS
  . -f omnetpp.ini -c MixedNID -r 0  ... : PASS
  . -f omnetpp.ini -c Mixed -r 0  ... : PASS
  . -f omnetpp.ini -c WirelessNIDDim -r 0  ... : PASS
  . -f omnetpp.ini -c Ospf -r 0  ... : PASS
  . -f omnetpp.ini -c Wired -r 0  ... : PASS
  . -f omnetpp.ini -c Wireless -r 0  ... : PASS
  . -f omnetpp.ini -c WirelessDim -r 0  ... : PASS

  ----------------------------------------------------------------------
  Ran 9 tests in 346.879s
