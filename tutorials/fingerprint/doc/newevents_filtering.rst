.. :orphan:

New events - filtering
======================

  1. change or action
  2. phenomenon / effect
  3. solution
  4. example

Some changes in the model can add new events to the simulation. These events inevitably change the fingerprints but not necessarily invalidate the model. One option is to filter out the modules in which the new events take place. Taking into account the rest of the modules might show that the simulation trajectory in fact stayed that same.

To filter out the modules, run the fingerprint test with the ``--fingerprint-modules`` command line option, e.g.:

.. TODO example

.. code-block:: bash

   $ inet_fingerprinttest -a --fingerprint-modules='"not fullPath=~**.wlan[*].mac.**"'

Then, update the fingerprints, make the change, and run the fingerprints again.

TODO when running the filtered fingerprints, the new fingerprints can be accepted, as there was no change in the model. When running the fingerprints after making the changes, they PASS...

TODO not here

TODO example

For example, we add a line to one of the functions in :cpp:`Udp.cc` which schedules a self message;
we also add a handleSelfMessage() function which just deletes the message when its received:

.. literalinclude:: ../Udp_mod.cc
   :diff: ../Udp_orig.cc

this change introduces new events to the simulation, but doesn't alter the model.

TODO but default fingerprints change / tlx as well

TODO filter

.. code-block:: fp

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

.. code-block:: fp

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
